/* register.c - implementation of IDNA2008 register functions
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

#include "idn2.h"

#include <langinfo.h> /* nl_langinfo */

#include "idna.h"

#include "striconv.h" /* str_iconv */

int
idn2_register_u8 (const uint8_t *ulabel, const uint8_t *alabel,
		  uint8_t **lookupname, int flags)
{
  /* FIXME */
  return 0;
}

int
idn2_register_ul (const char *ulabel, const char *alabel,
		  char **lookupname, int flags)
{
  char *locale_codeset = nl_langinfo (CODESET);

  if (locale_codeset == NULL || *locale_codeset == '\0')
    return IDN2_NO_CODESET;

  uint8_t *utf8ulabel = str_iconv (ulabel, locale_codeset, "UTF-8");
  if (utf8ulabel == NULL)
    return IDN2_ICONV_FAIL;

  int rc = idn2_register_u8 (utf8ulabel, alabel, lookupname,
			     flags | IDN2_NFC_INPUT);

  free (utf8ulabel);

  return rc;
}
