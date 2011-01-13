/* test-idna.c --- Self tests for IDNA processing
 * Copyright (C) 2011 Simon Josefsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include <idn2.h>

struct idna_tv
{
  const char *what;
  int rc;
  size_t inlen;
  const uint8_t *in;
  size_t outlen;
  const uint8_t *out;
};

#define REKA "\x72\xc3\xa4\x6b\x73\x6d\xc3\xb6\x72\x67\xc3\xa5\x73"
#define REKA_LEN 13

static struct idna_tv tv[] = {
  {"", IDN2_UNKNOWN_WHAT, 0, NULL, 0, NULL},
  {"", IDN2_ENCODING_ERROR, 6, "\xd0\x94\xd0\xb0\xc1\x80", 0, NULL},
  {"foo", IDN2_UNKNOWN_WHAT, 0, NULL, 0, NULL},
  {"check-nfc", IDN2_NOT_NFC, 3, "\xe2\x84\xa6", 0, NULL},
  {"check-nfc", IDN2_OK, 2, "\xC3\x85", 2, "\xC3\x85"},
  {"check-nfc", IDN2_NOT_NFC, 3, "\xe2\x84\xa6", 0, NULL},
  {"check-nfc", IDN2_OK, 2, "\xce\xa9", 2, "\xce\xa9"},
  {"check-2hyphen", IDN2_2HYPHEN, 4, "ab--", 0, NULL},
  {"check-2hyphen", IDN2_OK, 2, "--", 2, "--"},
  {"check-hyphen-startend", IDN2_HYPHEN_STARTEND, 1, "-", 0, NULL},
  {"check-hyphen-startend", IDN2_HYPHEN_STARTEND, 2, "-a", 0, NULL},
  {"check-hyphen-startend", IDN2_HYPHEN_STARTEND, 2, "a-", 0, NULL},
  {"check-hyphen-startend", IDN2_HYPHEN_STARTEND, 3, "-a-", 0, NULL},
  {"check-hyphen-startend", IDN2_OK, 3, "foo", 3, "foo"},
  {"nfc", IDN2_OK, 3, "\xe2\x84\xab", 2, "\xC3\x85"},
  {"nfc", IDN2_OK, 3, "\xe2\x84\xa6", 2, "\xce\xa9"},
  /* CCC=0 GC=M */
  {"check-combining", IDN2_COMBINING, 2, "\xcd\x8f", 0, NULL},
  /* CCC=0 GC=M */
  {"check-combining", IDN2_COMBINING, 2, "\xd2\x88", 0, NULL},
  /* CCC!=0 GC=Mn */
  {"check-combining", IDN2_COMBINING, 2, "\xcc\x80", 0, NULL},
  /* CCC!=0 GC=Mc */
  {"check-combining", IDN2_COMBINING, 3, "\xe1\xad\x84", 0, NULL},
  {"check-disallowed", IDN2_DISALLOWED, 1, "\x00", 0, NULL},
  {"check-disallowed", IDN2_DISALLOWED, 2, "a\x00", 0, NULL},
  {"check-disallowed", IDN2_DISALLOWED, 2, "\xc2\xb8", 0, NULL},
  {"check-disallowed", IDN2_DISALLOWED, 4, "\xf4\x8f\xbf\xbf", 0, NULL},
  {"check-contextj", IDN2_CONTEXTJ, 3, "\xe2\x80\x8d", 0, NULL},
  {"check-contexto-with-rule", IDN2_OK, 2, "AA", 2, "AA"},
  {"check-contexto-with-rule", IDN2_OK, 2, "\xc2\xb7", 2, "\xc2\xb7"},
  {"check-unassigned", IDN2_UNASSIGNED, 2, "\xcd\xb8", 0, NULL},
  {"check-unassigned", IDN2_UNASSIGNED, 2, "\xcd\xb9", 0, NULL},
  /* Check that bidi handles ascii strings ok. */
  {"check-bidi", IDN2_OK, 3, "foo", 3, "foo"},
  /* Check that bidi handles non-bidi strings ok. */
  {"check-bidi", IDN2_OK, REKA_LEN, REKA, REKA_LEN, REKA },
  /* Check that bidi rejects leading non-L/R/AL characters in bidi strings */
  {"check-bidi", IDN2_BIDI, 3, "1\xde\x86", 0, NULL},
  /* check that ltr string cannot contain R character */
  {"check-bidi", IDN2_BIDI, 3, "f\xd7\x99", 0, NULL},
};

int debug = 1;
int error_count = 0;
int break_on_error = 1;

void
fail (const char *format, ...)
{
  va_list arg_ptr;

  va_start (arg_ptr, format);
  vfprintf (stderr, format, arg_ptr);
  va_end (arg_ptr);
  error_count++;
  if (break_on_error)
    exit (EXIT_FAILURE);
}

void
hexprint (const char *str, size_t len)
{
  size_t i;

  printf ("\t;; ");
  if (str && len)
    for (i = 0; i < len; i++)
      {
	printf ("%02x ", (str[i] & 0xFF));
	if ((i + 1) % 8 == 0)
	  printf (" ");
	if ((i + 1) % 16 == 0 && i + 1 < len)
	  printf ("\n\t;; ");
      }
  printf ("\n");
}

int
main (void)
{
  uint8_t *out;
  size_t outlen;
  size_t i;
  int rc;

  for (i = 0; i < sizeof (tv) / sizeof (tv[0]); i++)
    {
      if (debug)
	printf ("IDNA entry %d\n", i);

      out = NULL;
      outlen = 0;
      rc = idn2_process_u8 (tv[i].what, tv[i].in, tv[i].inlen,
			       &out, &outlen);
      if (rc != tv[i].rc)
	{
	  fail ("IDNA entry %d failed got %d expected %d\n", i, rc, tv[i].rc);
	  continue;
	}

      if (debug)
	{
	  uint32_t *t;
	  size_t len;

	  printf ("what: %s\n", tv[i].what);

	  printf ("in:\n");
	  hexprint (tv[i].in, tv[i].inlen);

	  if (rc == IDN2_OK)
	    {
	      printf ("got out:\n");
	      hexprint (out, outlen);
	    }

	  if (tv[i].out)
	    {
	      printf ("expected out:\n");
	      hexprint (tv[i].out, tv[i].outlen);
	    }
	}

      if (rc == IDN2_OK &&
	  (tv[i].outlen != outlen || memcmp (tv[i].out, out, outlen)) != 0)
	{
	  fail ("IDNA entry %d failed\n", i);
	  if (debug)
	    printf ("ERROR\n");
	  break;
	}
      else if (debug)
	printf ("OK\n");

      free (out);
    }

  rc = idn2_convert_u8 ("nfc,ace", "www.räksmörgås.com", &out);
  printf ("rc %d str %s\n", rc, rc == IDN2_OK ? out : "<null>");

  return error_count;
}
