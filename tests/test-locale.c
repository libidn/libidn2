/* test-locale.c --- Self tests for locale-related (iconv) IDNA processing
   Copyright (C) 2011-2022 Simon Josefsson

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

#include <idn2.h>

int
main (void)
{
  int error_count = 0;
  uint8_t *out;
  int rc;

  if ((rc = idn2_lookup_ul ("abc", NULL, 0)) != IDN2_OK)
    {
      printf ("special #5 failed with %d\n", rc);

      if (rc == IDN2_ICONV_FAIL)
	return 77;

      error_count++;
    }

  /* test libidn compatibility functions */
  if ((rc = idna_to_ascii_lz ("abc", (char **) &out, 0)) != IDN2_OK)
    {
      printf ("special #6 failed with %d\n", rc);
      error_count++;
    }
  else
    {
      idn2_free (out);
    }

  if ((rc = idn2_register_ul ("foo", NULL, NULL, 0)) != IDN2_OK)
    {
      printf ("special #6 failed with %d\n", rc);
      error_count++;
    }

  printf ("\nerror_count: %d\n", error_count);

  return !!error_count;
}
