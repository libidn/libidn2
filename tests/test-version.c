/* test-version.c --- Self tests for Libidn2 version handling.
   Copyright (C) 2002-2024 Simon Josefsson

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

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* EXIT_SUCCESS */
#include <string.h>		/* strcmp */

#include <idn2.h>

int
main (void)
{
  unsigned gvn = IDN2_VERSION_NUMBER;
  unsigned gvmmp = (IDN2_VERSION_MAJOR << 24)
    + (IDN2_VERSION_MINOR << 16) + IDN2_VERSION_PATCH;
  const char *check_version_null;
  char buf[BUFSIZ];
  int j;

  printf ("IDN2_VERSION: %s\n", IDN2_VERSION);
  printf ("IDN2_VERSION_MAJOR: %d\n", IDN2_VERSION_MAJOR);
  printf ("IDN2_VERSION_MINOR: %d\n", IDN2_VERSION_MINOR);
  printf ("IDN2_VERSION_PATCH: %d\n", IDN2_VERSION_PATCH);
  printf ("IDN2_VERSION_NUMBER: %x\n", gvn);
  printf ("IDN2_VERSION_MAJOR.IDN2_VERSION_MINOR."
	  "IDN2_VERSION_PATCH: %d.%d.%d\n",
	  IDN2_VERSION_MAJOR, IDN2_VERSION_MINOR, IDN2_VERSION_PATCH);

  check_version_null = idn2_check_version (NULL);
  if (!check_version_null)
    {
      printf ("FAIL: idn2_check_version (NULL)\n");
      return EXIT_FAILURE;
    }
  printf ("idn2_check_version (NULL): %s\n", check_version_null);

  j = snprintf (buf, sizeof buf, "%d.%d.%d", IDN2_VERSION_MAJOR,
		IDN2_VERSION_MINOR, IDN2_VERSION_PATCH);
  if (j < 0 || j == sizeof buf)
    {
      printf ("FAIL: snprintf: %d", j);
      return EXIT_FAILURE;
    }

  if (!idn2_check_version (buf))
    {
      printf ("FAIL: idn2_check_version(buf == %s)\n", buf);
      return EXIT_FAILURE;
    }

  /* IDN2_VERSION may look like "1.0.4.10-b872" but the derived string
     should be "1.0.4" anyway.  */
  if (strncmp (IDN2_VERSION, buf, strlen (buf)) != 0)
    {
      printf ("FAIL: strncmp (IDN2_VERSION, %s, strlen (%s))\n", buf, buf);
      return EXIT_FAILURE;
    }

  if (!idn2_check_version (IDN2_VERSION))
    {
      printf ("FAIL: idn2_check_version (IDN2_VERSION)\n");
      return EXIT_FAILURE;
    }

  if (check_version_null != idn2_check_version (NULL))
    {
      printf ("FAIL: check_version_null != idn2_check_version (NULL)\n");
      return EXIT_FAILURE;
    }

  if (idn2_check_version (IDN2_VERSION) != idn2_check_version (IDN2_VERSION))
    {
      printf ("FAIL: idn2_check_version (IDN2_VERSION) "
	      "!= idn2_check_version (IDN2_VERSION)\n");
      return EXIT_FAILURE;
    }

  if (!idn2_check_version ("1.0.1"))
    {
      printf ("FAIL: idn2_check_version (1.0.1)\n");
      return EXIT_FAILURE;
    }

  if (strcmp (IDN2_VERSION, check_version_null) != 0)
    {
      printf ("FAIL: strcmp (IDN2_VERSION, idn2_check_version (NULL))\n");
      return EXIT_FAILURE;
    }

  if (gvn != gvmmp)
    {
      printf ("FAIL: IDN2_VERSION_NUMBER != (IDN2_VERSION_MAJOR << 24) +"
	      " (IDN2_VERSION_MINOR << 16) + IDN2_VERSION_PATCH: %x\n",
	      gvmmp);
      return EXIT_FAILURE;
    }

  if (idn2_check_version ("100.100"))
    {
      printf ("FAIL: idn2_check_version(100.100)\n");
      return EXIT_FAILURE;
    }

  if (idn2_check_version ("4711.42.23"))
    {
      printf ("FAIL: idn2_check_version(4711.42.23)\n");
      return EXIT_FAILURE;
    }

  if (idn2_check_version ("UNKNOWN"))
    {
      printf ("FAIL: idn2_check_version (UNKNOWN)\n");
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
