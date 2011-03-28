/* test-register.c --- Self tests for IDNA processing
   Copyright (C) 2011 Simon Josefsson

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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include <idn2.h>

struct idna
{
  const uint8_t *alabel;
  const uint8_t *ulabel;
  const char *out;
  int rc;
  int flags;
};

static const struct idna idna[] = {
#if 0
  {"foo", "foo", "foo", IDN2_OK},
  {"foo", NULL, "foo", IDN2_OK},
#endif
  {NULL, "foo", "foo", IDN2_OK},
  {NULL, "räksmörgås", "xn--rksmrgs-5wao1o", IDN2_OK},
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
  size_t i;
  int rc;

  puts ("-----------------------------------------------------------"
	"-------------------------------------");
  puts ("                                          IDNA2008 Register\n");
  puts ("  #  Result                    Output                    A-label input             U-label input");
  puts ("-----------------------------------------------------------"
	"-------------------------------------");
  for (i = 0; i < sizeof (idna) / sizeof (idna[0]); i++)
    {
      rc = idn2_register_u8 (idna[i].ulabel, idna[i].alabel,
			     &out, idna[i].flags);
      printf ("%3d  %-25s %-25s %-25s %s\n", i, idn2_strerror_name (rc),
	      rc == IDN2_OK ? idna[i].out : "",
	      idna[i].alabel ? idna[i].alabel : "(null)",
	      idna[i].ulabel ? idna[i].ulabel : "(null)");
      if (rc != idna[i].rc)
	fail ("expected rc %d got rc %d\n", idna[i].rc, rc);
      else if (rc == IDN2_OK && strcmp (out, idna[i].out) != 0)
	fail ("expected: %s\ngot: %s\n", idna[i].out, out);
      if (rc == IDN2_OK)
	free (out);
    }

  return error_count;
}
