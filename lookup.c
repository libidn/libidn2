/* lookup.c - implementation of IDNA2008 lookup functions
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

/**
 * idn2_lookup_u8:
 * @src: input zero-terminated UTF-8 string in Unicode NFC normalized form.
 * @lookupname: newly allocated output variable with name to lookup in DNS.
 * @flags: optional #Idn2_flags to modify behaviour.
 *
 * Perform IDNA2008 lookup string conversion on input @src, as
 * described in section 5 of RFC 5891.  Note that the input string
 * must be encoded in UTF-8 and be in Unicode NFC form.
 *
 * Pass %IDN2_NFC_INPUT in @flags to convert input to NFC form before
 * further processing.  Pass %IDN2_ALABEL_ROUNDTRIP in @flags to
 * convert any input A-labels to U-labels and perform additional
 * testing.  Multiple flags may be specified by binary or:ing them
 * together, for example %IDN2_NFC_INPUT | %IDN2_ALABEL_ROUNDTRIP.
 *
 * Returns: On successful conversion %IDN2_OK is returned, otherwise
 *   an error code is returned.
 **/
int
idn2_lookup_u8 (const uint8_t *src, uint8_t **lookupname, int flags)
{
  const char *what = "check-nfc,check-2hyphen,check-combining,"
    "check-disallowed,check-contextj-rule,check-contexto-with-rule,"
    "check-unassigned,check-bidi,ace";
  int rc;

  if (flags & IDN2_ALABEL_ROUNDTRIP)
    /* FIXME: Conversion from the A-label and testing that the result is
       a U-label SHOULD be performed if the domain name will later be
       presented to the user in native character form */
    return IDN2_INTERNAL_ERROR;

  if (flags & IDN2_NFC_INPUT)
    what += strlen ("check-");

  rc = _idn2_domain_u8 (what, src, lookupname);

  return rc;
}

/**
 * idn2_lookup_ul:
 * @src: input zero-terminated locale encoded string.
 * @lookupname: newly allocated output variable with name to lookup in DNS.
 * @flags: optional #Idn2_flags to modify behaviour.
 *
 * Perform IDNA2008 lookup string conversion on input @src, as
 * described in section 5 of RFC 5891.  Note that the input is assumed
 * to be encoded in the locale's default coding system, and will be
 * transcoded to UTF-8 and NFC normalized by this function.
 *
 * Pass %IDN2_ALABEL_ROUNDTRIP in @flags to convert any input A-labels
 * to U-labels and perform additional testing.
 *
 * Returns: On successful conversion %IDN2_OK is returned, otherwise
 *   an error code is returned.
 **/
int
idn2_lookup_ul (const char *src, char **lookupname, int flags)
{
  uint8_t *utf8src = u8_strconv_from_locale (src);
  if (utf8src == NULL)
    {
      if (errno == ENOMEM)
	return IDN2_MALLOC;
      return IDN2_ICONV_FAIL;
    }

  int rc = idn2_lookup_u8 (utf8src, (uint8_t **) lookupname,
			   flags | IDN2_NFC_INPUT);

  free (utf8src);

  return rc;
}
