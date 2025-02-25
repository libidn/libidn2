/* test-compat-punycode.c --- Self test Libidn2 punycode internal symbols.
   Copyright (C) 2002-2025 Simon Josefsson

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

#include <idn2.h>

extern int _IDN2_API _idn2_punycode_decode (size_t input_length,
					    const char input[],
					    size_t *output_length,
					    uint32_t output[]);
extern int _IDN2_API _idn2_punycode_encode (size_t input_length,
					    const uint32_t input[],
					    size_t *output_length,
					    char output[]);

int
main (void)
{
  int rc;
  const uint32_t ucs4_input[] = { 0x00DF, 0x00E5 };	/* ßå */
  size_t output_length = 2;
  uint32_t ucs4_output[2];
  char ascii[4];

  output_length = 4;
  rc = _idn2_punycode_encode (2, ucs4_input, &output_length, ascii);
  if (rc != IDN2_OK)
    {
      printf ("FAIL: encode: %d: %s: %s\n",
	      rc, idn2_strerror_name (rc), idn2_strerror (rc));
      return EXIT_FAILURE;
    }

  if (output_length != 4)
    {
      printf ("FAIL: encode 4 != %lu\n", (unsigned long) output_length);
      return EXIT_FAILURE;
    }

  if (memcmp (ascii, "zcam", 4) != 0)
    {
      printf ("FAIL: encode: memcmp: %s\n", ascii);
      return EXIT_FAILURE;
    }

  printf ("PASS: ßå => zcam\n");

  rc = _idn2_punycode_decode (4, ascii, &output_length, ucs4_output);
  if (rc != IDN2_OK)
    {
      printf ("FAIL: decode: %d: %s: %s\n",
	      rc, idn2_strerror_name (rc), idn2_strerror (rc));
      return EXIT_FAILURE;
    }

  if (output_length != 2)
    {
      printf ("FAIL: decode 2 != %lu\n", (unsigned long) output_length);
      return EXIT_FAILURE;
    }

  if (memcmp (ucs4_output, ucs4_input, 2 * sizeof (uint32_t)) != 0)
    {
      printf ("FAIL: decode: memcmp: %s\n", ascii);
      printf ("ucs4_output[0] = %lX\n", (unsigned long) ucs4_output[0]);
      printf ("ucs4_output[1] = %lX\n", (unsigned long) ucs4_output[1]);
      return EXIT_FAILURE;
    }

  printf ("PASS: zcam => ßå\n");

  return EXIT_SUCCESS;
}
