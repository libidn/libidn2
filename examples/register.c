/* register.c - example program to demonstrate IDNA2008 Register using Libidn2
   Copyright (C) 2011-2025 Simon Josefsson

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

#include <stdio.h>		/* printf, fflush, fgets, stdin, perror, fprintf */
#include <string.h>		/* strlen */
#include <locale.h>		/* setlocale */
#include <stdlib.h>		/* free */
#include <idn2.h>		/* idn2_register_ul, IDN2_OK, idn2_strerror, idn2_strerror_name */

int
main (int argc, char *argv[])
{
  int rc;
  char src[BUFSIZ];
  char *insertname;

  setlocale (LC_ALL, "");

  printf ("Enter (possibly non-ASCII) label to register: ");
  fflush (stdout);
  if (!fgets (src, sizeof (src), stdin))
    {
      perror ("fgets");
      return 1;
    }
  src[strlen (src) - 1] = '\0';

  rc = idn2_register_ul (src, NULL, &insertname, 0);
  if (rc != IDN2_OK)
    {
      fprintf (stderr, "error: %s (%s, %d)\n",
	       idn2_strerror (rc), idn2_strerror_name (rc), rc);
      return 1;
    }

  printf ("IDNA2008 label to register in DNS: %s\n", insertname);

  free (insertname);

  return 0;
}
