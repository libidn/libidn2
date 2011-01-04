/* test-nfc.c --- Self tests for Libidna NFC
 * Copyright (C) 2002, 2003, 2004, 2006, 2006, 2007, 2008, 2009, 2010, 2011
 * Simon Josefsson
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

#include <libidna.h>

struct nfc
{
  const uint8_t *in;
  const uint8_t *out;
};

static struct nfc nfc[] = {
  {"\xe2\x84\xab", "\xC3\x85"},
  {"\xe2\x84\xa6", "\xce\xa9"}
};

int debug = 0;
int error_count = 0;
int break_on_error = 0;

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

  for (i = 0; i < sizeof (nfc) / sizeof (nfc[0]); i++)
    {
      if (debug)
	printf ("NFC entry %d\n", i);

      out = NULL;
      outlen = 0;
      rc = libidna_nfc_u8 (nfc[i].in, strlen (nfc[i].in),
			   &out, &outlen);
      if (rc != LIBIDNA_OK)
	{
	  fail ("NFC entry %d failed fatally %d\n", i, rc);
	  continue;
	}

      if (debug)
	{
	  uint32_t *t;
	  size_t len;

	  printf ("in:\n");
	  hexprint (nfc[i].in, strlen (nfc[i].in));

	  printf ("out:\n");
	  hexprint (out, outlen);

	  printf ("expected out:\n");
	  hexprint (nfc[i].out, strlen (nfc[i].out));
	}

      if (out == NULL || outlen == 0)
	fail ("NFC entry %d returned NULL?!\n", i);
      else if (strlen (nfc[i].out) != outlen ||
	  memcmp (nfc[i].out, out, outlen) != 0)
	{
	  fail ("NFC entry %d failed\n", i);
	  if (debug)
	    printf ("ERROR\n");
	}
      else if (debug)
	printf ("OK\n");

      free (out);
    }

  return error_count;
}
