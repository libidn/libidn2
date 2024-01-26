/* test-IdnaTest-txt.c --- Self-test Libidn2 on UTC's IdnaTest.txt
   Copyright (C) 2011-2024 Simon Josefsson
   Copyright (C) 2017-2024 Tim Ruehsen

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>

#include <idn2.h>

#include "unistr.h"		/* u32_to_u8, u8_to_u32 */

static int ok = 0, failed = 0;
static int break_on_error = 0;
static int verbose = 0;

static const char *
_nextField (char **line)
{
  char *s = *line, *e;

  if (!*s)
    return "";

  if (!(e = strpbrk (s, ";#")))
    {
      e = *line += strlen (s);
    }
  else
    {
      *line = e + (*e == ';');
      *e = 0;
    }

  // trim leading and trailing whitespace
  while (isspace (*s))
    s++;
  while (e > s && isspace (e[-1]))
    *--e = 0;

  return s;
}

static int
_scan_file (const char *fname, int (*scan) (char *))
{
  FILE *fp = fopen (fname, "r");
  char *buf = NULL, *linep;
  size_t bufsize = 0;
  ssize_t buflen;
  int ret = 0;

  printf ("Scanning file: %s\n", fname);

  if (!fp)
    {
      fprintf (stderr, "Failed to open %s (%d)\n", fname, errno);
      return -1;
    }

  while ((buflen = getline (&buf, &bufsize, fp)) >= 0)
    {
      linep = buf;

      while (isspace (*linep))
	linep++;		// ignore leading whitespace

      // strip off \r\n
      while (buflen > 0 && (buf[buflen] == '\n' || buf[buflen] == '\r'))
	buf[--buflen] = 0;

      if (!*linep || *linep == '#')
	continue;		// skip empty lines and comments

      if ((ret = scan (linep)))
	break;
    }

  free (buf);
  fclose (fp);

  return ret;
}

// decode embedded UTF-16/32 sequences
static uint8_t *
_decodeIdnaTest (const uint8_t *src_u8)
{
  size_t it2 = 0, len;
  uint32_t *src;

  // convert UTF-8 to UCS-4 (Unicode))
  if (!(src = u8_to_u32 (src_u8, u8_strlen (src_u8) + 1, NULL, &len)))
    {
      if (verbose)
	printf ("u8_to_u32(%s) failed (%d)\n", src_u8, errno);
      return NULL;
    }

  // replace escaped UTF-16 incl. surrogates
  for (size_t it = 0; it < len;)
    {
      if (src[it] == '\\' && src[it + 1] == 'u')
	{
	  src[it2] =
	    ((src[it + 2] >=
	      'A' ? src[it + 2] - 'A' + 10 : src[it + 2] - '0') << 12) +
	    ((src[it + 3] >=
	      'A' ? src[it + 3] - 'A' + 10 : src[it + 3] - '0') << 8) +
	    ((src[it + 4] >=
	      'A' ? src[it + 4] - 'A' + 10 : src[it + 4] - '0') << 4) +
	    (src[it + 5] >= 'A' ? src[it + 5] - 'A' + 10 : src[it + 5] - '0');
	  it += 6;

	  if (src[it2] >= 0xD800 && src[it2] <= 0xDBFF)
	    {
	      // high surrogate followed by low surrogate
	      if (src[it] == '\\' && src[it + 1] == 'u')
		{
		  uint32_t low =
		    ((src[it + 2] >=
		      'A' ? src[it + 2] - 'A' + 10 : src[it + 2] -
		      '0') << 12) + ((src[it + 3] >=
				      'A' ? src[it + 3] - 'A' + 10 : src[it +
									 3] -
				      '0') << 8) + ((src[it + 4] >=
						     'A' ? src[it + 4] - 'A' +
						     10 : src[it + 4] -
						     '0') << 4) + (src[it +
								       5] >=
								   'A' ?
								   src[it +
								       5] -
								   'A' +
								   10 : src[it
									    +
									    5]
								   - '0');
		  if (low >= 0xDC00 && low <= 0xDFFF)
		    src[it2] =
		      0x10000 + (src[it2] - 0xD800) * 0x400 + (low - 0xDC00);
		  else if (verbose)
		    printf ("Missing low surrogate\n");
		  it += 6;
		}
	      else
		{
		  it++;
		  if (verbose)
		    printf ("Missing low surrogate\n");
		}
	    }
	  it2++;
	}
      else
	src[it2++] = src[it++];
    }

  // convert UTF-32 to UTF-8
  uint8_t *dst_u8 = u32_to_u8 (src, it2, NULL, &len);
  if (!dst_u8 && verbose)
    printf ("u32_to_u8(%s) failed (%d)\n", src_u8, errno);

  free (src);
  return dst_u8;
}

static void
_check_toASCII (const char *source, const char *expected, int transitional,
		int expected_toASCII_failure)
{
  int rc;
  char *ace = NULL;

  rc =
    idn2_lookup_u8 ((uint8_t *) source, (uint8_t **) & ace,
		    transitional ? IDN2_TRANSITIONAL : IDN2_NONTRANSITIONAL);

  // printf("n=%d expected=%s t=%d got=%s, expected_failure=%d\n", n, expected, transitional, ace ? ace : "", expected_toASCII_failure);
  if (rc && expected_toASCII_failure)
    {
      if (verbose)
	printf ("OK\n");
      ok++;
    }
  else if (rc && !transitional && *expected != '[')
    {
      failed++;
      printf ("Failed: _check_toASCII(%s) -> %d (expected 0) %p\n", source,
	      rc, ace);
    }
  else if (rc == 0 && !transitional && *expected != '['
	   && strcmp (expected, ace))
    {
      failed++;
      printf ("Failed: _check_toASCII(%s) -> %s (expected %s) %p\n", source,
	      ace, expected, ace);
    }
  else
    {
      if (verbose)
	printf ("OK\n");
      ok++;
    }

  if (rc == IDN2_OK)
    idn2_free (ace);
}

#if HAVE_LIBUNISTRING
extern int _libunistring_version;
#endif

static int
test_IdnaTest (char *linep)
{
  char *source;
  const char *type, *toUnicode, *toASCII, *NV8, *org_source;
  int expected_toASCII_failure;

  type = _nextField (&linep);
  org_source = _nextField (&linep);
  toUnicode = _nextField (&linep);
  toASCII = _nextField (&linep);
  NV8 = _nextField (&linep);	// if set, the input should be disallowed for IDNA2008

  // sigh, these Unicode people really mix UTF-8 and UCS-2/4
  // quick and dirty translation of '\uXXXX' found in IdnaTest.txt including surrogate handling
  source = (char *) _decodeIdnaTest ((uint8_t *) org_source);
  if (!source)
    return 0;			// some Unicode sequences can't be encoded into UTF-8, skip them

  if (!*toUnicode)
    toUnicode = source;
  if (!*toASCII)
    toASCII = toUnicode;
  expected_toASCII_failure = NV8 && *NV8;

  if (verbose)
    printf ("##########%s#%s#%s#%s#%s#\n", type, org_source, toUnicode,
	    toASCII, NV8);

#if HAVE_LIBUNISTRING
  /* 3 tests fail with libunicode <= 0.9.3 - just skip them until we have a newer version installed */
  /* watch out, libunicode changed versioning scheme up from 0.9.4 */
  /* If !HAVE_LIBUNISTRING, we use internal gnulib code which works. */
  if (_libunistring_version <= 9)
    {
      if (!strcmp (toASCII, "xn--8jb.xn--etb875g"))
	{
	  free (source);
	  return 0;
	}
    }
#endif

  if (*type == 'B')
    {
      _check_toASCII (source, toASCII, 1, expected_toASCII_failure);
      _check_toASCII (source, toASCII, 0, expected_toASCII_failure);
    }
  else if (*type == 'T')
    {
      _check_toASCII (source, toASCII, 1, expected_toASCII_failure);
    }
  else if (*type == 'N')
    {
      _check_toASCII (source, toASCII, 0, expected_toASCII_failure);
    }
  else
    {
      printf ("Failed: Unknown type '%s'\n", type);
    }

  free (source);

  if (failed && break_on_error)
    return 1;

  return 0;
}

#ifdef SRCDIR
# define IDNATEST_TXT SRCDIR "/IdnaTest.txt"
#else
# define IDNATEST_TXT "IdnaTest.txt"
#endif

int
main (int argc, const char *argv[])
{
  const char *fname = IDNATEST_TXT;

  if (argc > 1 && strcmp (argv[1], "--verbose") == 0)
    {
      verbose = 1;
      if (argc > 2)
	fname = argv[2];
    }
  else if (argc > 1)
    fname = argv[1];

  if (verbose)
    {
      puts ("-----------------------------------------------------------"
	    "-------------------------------------");
      puts ("                                          IDNA2008 Lookup\n");
      puts ("  #  Result                    ACE output                  "
	    "             Unicode input");
      puts ("-----------------------------------------------------------"
	    "-------------------------------------");
    }

  if (_scan_file (fname, test_IdnaTest))
    return EXIT_FAILURE;

  if (verbose)
    puts ("-----------------------------------------------------------"
	  "-------------------------------------");

  if (failed)
    {
      printf ("INFO: test-IdnaTest-txt: %d out of %d tests failed\n", failed,
	      ok + failed);
      return EXIT_FAILURE;
    }

  if (ok == 0)
    {
      printf ("FAIL: test-IdnaTest-txt: no test vectors found\n");
      return EXIT_FAILURE;
    }

  printf ("PASS: test-IdnaTest-txt: All %d tests passed\n", ok + failed);

  return EXIT_SUCCESS;
}
