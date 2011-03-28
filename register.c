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

#include "idna.h" /* _idn2_domain_u8 */
#include <errno.h> /* errno */
#include "uniconv.h" /* u8_strconv_from_locale */
#include <stdlib.h> /* free */

int
idn2_register_u8 (const uint8_t *ulabel, const uint8_t *alabel,
		  uint8_t **insertname, int flags)
{
  int rc;

  if (ulabel && strlen (ulabel) >= IDN2_LABEL_MAX_LENGTH)
    return IDN2_TOO_BIG_LABEL;
  if (alabel && strlen (alabel) >= IDN2_LABEL_MAX_LENGTH)
    return IDN2_TOO_BIG_LABEL;

  if (ulabel && alabel)
    {
    }
  else if (ulabel)
    {
      uint32_t *u32;
      size_t u32len;

      rc = _idn2_u8_to_u32_nfc (ulabel, strlen (ulabel), &u32, &u32len,
				flags & IDN2_NFC_INPUT);
    }
  else
    return -1;

  return 0;
}

int
idn2_register_ul (const char *ulabel, const char *alabel,
		  char **insertname, int flags)
{
  uint8_t *utf8ulabel = u8_strconv_from_locale (ulabel);
  if (utf8ulabel == NULL)
    {
      if (errno == ENOMEM)
	return IDN2_MALLOC;
      return IDN2_ICONV_FAIL;
    }

  int rc = idn2_register_u8 (utf8ulabel, (uint8_t *) alabel,
			     (uint8_t **) insertname,
			     flags | IDN2_NFC_INPUT);

  free (utf8ulabel);

  return rc;
}
