/* test-IdnaTest-inc.c --- Self-test Libidn2 on IdnaTest.inc
   Copyright (C) 2011-2025 Simon Josefsson
   Copyright (C) 2017-2025 Tim Ruehsen

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

struct idna
{
  const char *in;
  const char *out;
  int rc;
  int flags;
};

static const struct idna idna[] = {
#include "IdnaTest.inc"
};

static int ok = 0, failed = 0;
static int break_on_error = 0;

static void
test_homebrewed (void)
{
  uint32_t dummy_u32[4] = { 'a', 'b', 'c', 0 };
  uint8_t *out;
  size_t i;
  int rc;

  for (i = 0; i < sizeof (idna) / sizeof (idna[0]); i++)
    {
      rc = idn2_lookup_u8 ((uint8_t *) idna[i].in, &out, idna[i].flags);
      printf ("%3d  %-25s %-40s %s\n", (int) i, idn2_strerror_name (rc),
	      rc == IDN2_OK ? idna[i].out : "", idna[i].in);

      if (rc != idna[i].rc && rc == IDN2_ENCODING_ERROR)
	{
	  printf ("utc bug\n");
	}
      else if (rc != idna[i].rc && idna[i].rc != -1)
	{
	  failed++;
	  printf ("expected rc %d got rc %d\n", idna[i].rc, rc);
	}
      else if (rc == IDN2_OK && strcmp ((char *) out, idna[i].out) != 0)
	{
	  failed++;
	  printf ("expected: %s\ngot: %s\n", idna[i].out, out);
	}
      else
	ok++;

      if (rc == IDN2_OK)
	idn2_free (out);

      /* Try the IDN2_NO_TR46 flag behavior */
      if (!(idna[i].flags & (IDN2_NONTRANSITIONAL | IDN2_TRANSITIONAL)))
	{
	  rc =
	    idn2_lookup_u8 ((uint8_t *) idna[i].in, &out,
			    idna[i].flags | IDN2_NO_TR46);
	  printf ("%3d  %-25s %-40s %s\n", (int) i, idn2_strerror_name (rc),
		  rc == IDN2_OK ? idna[i].out : "", idna[i].in);

	  if (rc != idna[i].rc && rc == IDN2_ENCODING_ERROR)
	    {
	      printf ("utc bug\n");
	    }
	  else if (rc != idna[i].rc && idna[i].rc != -1)
	    {
	      failed++;
	      printf ("expected rc %d got rc %d\n", idna[i].rc, rc);
	    }
	  else if (rc == IDN2_OK && strcmp ((char *) out, idna[i].out) != 0)
	    {
	      failed++;
	      printf ("expected: %s\ngot: %s\n", idna[i].out, out);
	    }
	  else
	    ok++;

	  if (rc == IDN2_OK)
	    idn2_free (out);
	}

      /* Try whether the default flags behave as NONTRANSITIONAL */
      if (!(idna[i].flags & (IDN2_NO_TR46 | IDN2_TRANSITIONAL)))
	{
	  rc =
	    idn2_lookup_u8 ((uint8_t *) idna[i].in, &out,
			    idna[i].flags | IDN2_NONTRANSITIONAL);
	  printf ("%3d  %-25s %-40s %s\n", (int) i, idn2_strerror_name (rc),
		  rc == IDN2_OK ? idna[i].out : "", idna[i].in);

	  if (rc != idna[i].rc && rc == IDN2_ENCODING_ERROR)
	    {
	      printf ("utc bug\n");
	    }
	  else if (rc != idna[i].rc && idna[i].rc != -1)
	    {
	      failed++;
	      printf ("expected rc %d got rc %d\n", idna[i].rc, rc);
	    }
	  else if (rc == IDN2_OK && strcmp ((char *) out, idna[i].out) != 0)
	    {
	      failed++;
	      printf ("expected: %s\ngot: %s\n", idna[i].out, out);
	    }
	  else
	    ok++;

	  if (rc == IDN2_OK)
	    idn2_free (out);
	}

      if (failed && break_on_error)
	exit (EXIT_FAILURE);
    }

  /* special calls to cover edge cases */
  if ((rc = idn2_lookup_u8 (NULL, NULL, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #1 failed with %d\n", rc);
    }
  else
    ok++;

  out = (uint8_t *) 0x123;
  if ((rc = idn2_lookup_u8 (NULL, &out, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #2 failed with %d\n", rc);
    }
  else if (out)
    {
      failed++;
      printf ("special #2 failed with out!=NULL\n");
    }
  else
    ok++;

  if ((rc = idn2_lookup_ul (NULL, NULL, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #3 failed with %d\n", rc);
    }
  else
    ok++;

  out = (uint8_t *) 0x123;
  if ((rc = idn2_lookup_ul (NULL, (char **) &out, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #4 failed with %d\n", rc);
    }
  else if (out)
    {
      failed++;
      printf ("special #4 failed with out!=NULL\n");
    }
  else
    ok++;

  if ((rc = idna_to_ascii_8z ("abc", (char **) &out, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #7 failed with %d\n", rc);
    }
  else
    {
      idn2_free (out);
      ok++;
    }

  if ((rc = idna_to_ascii_4z (dummy_u32, (char **) &out, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #8 failed with %d\n", rc);
    }
  else
    {
      idn2_free (out);
      ok++;
    }

  if ((rc = idn2_to_ascii_4i2 (dummy_u32, 4, (char **) &out, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #9 failed with %d\n", rc);
    }
  else
    {
      idn2_free (out);
      ok++;
    }

  if ((rc = idn2_to_ascii_4i2 (NULL, 4, (char **) &out, 0)) != IDN2_OK)
    {
      failed++;
      printf ("special #10 failed with %d\n", rc);
    }
  else
    {
      idn2_free (out);
      ok++;
    }
}

int
main (void)
{
  puts ("-----------------------------------------------------------"
	"-------------------------------------");
  puts ("                                          IDNA2008 Lookup\n");
  puts ("  #  Result                    ACE output                  "
	"             Unicode input");
  puts ("-----------------------------------------------------------"
	"-------------------------------------");

  test_homebrewed ();

  if (failed)
    {
      printf ("Summary: %d out of %d tests failed\n", failed, ok + failed);
      return EXIT_FAILURE;
    }

  printf ("Summary: All %d tests passed\n", ok + failed);

  return EXIT_SUCCESS;
}
