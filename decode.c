/* lookup.c - implementation of IDNA2008 lookup functions
   Copyright (C) 2011-2016 Simon Josefsson

   Libidn2 is free software: you can redistribute it and/or modify it
   under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version.

   or both in parallel, as here.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>

#include "idn2.h"

#include <errno.h>		/* errno */
#include <stdlib.h>		/* malloc, free */

#include "punycode.h"

#include <unitypes.h>
#include <uniconv.h>		/* u8_strconv_from_locale */
#include <unistr.h>		/* u8_to_u32 */

/**
 * idn2_fromASCII:
 * @src: input zero-terminated UTF-8 string in Unicode NFC normalized form.
 * @out: newly allocated output variable with name to lookup in DNS.
 *
 * Perform punycode decoding on domain name @src. Note that the input string
 * must be encoded in UTF-8.
 *
 * @out may be NULL to test lookup of @src without allocating memory.
 *
 * Returns: On successful conversion %IDN2_OK is returned, if the
 *   output domain or any label would have been too long
 *   %IDN2_TOO_BIG_DOMAIN or %IDN2_TOO_BIG_LABEL is returned, or
 *   another error code is returned.
 **/
int
idn2_fromASCII (const uint8_t * src, uint8_t ** out)
{
  size_t len;
  uint32_t *domain_u32;
  int rc;

  if (src == NULL)
    {
      if (out)
	*out = NULL;
      return IDN2_OK;
    }

  /* split into labels and check */
  uint32_t out_u32[IDN2_DOMAIN_MAX_LENGTH + 1];
  size_t out_len = 0;
  const uint8_t *e, *s;
  for (e = s = src; *e; s = e)
    {
      while (*e && *e != '.')
	e++;

      if (e - s >= 4 && s[0] == 'x' && s[1] == 'n' && s[2] == '-'
	  && s[3] == '-')
	{
	  uint32_t label_u32[IDN2_LABEL_MAX_LENGTH];
	  size_t label_len = IDN2_LABEL_MAX_LENGTH;

	  s += 4;

	  rc =
	    _idn2_punycode_decode (e - s, (char *) s, &label_len, label_u32,
				   NULL);
	  if (rc)
	    {
	      free (domain_u32);
	      return rc;
	    }

	  if (out_len + label_len + (*e == '.') > IDN2_DOMAIN_MAX_LENGTH)
	    {
	      free (domain_u32);
	      return IDN2_TOO_BIG_DOMAIN;
	    }

	  u32_cpy (out_u32 + out_len, label_u32, label_len);
	  out_len += label_len;
	  if (*e == '.')
	    out_u32[out_len++] = '.';
	}
      else
        {
	  uint32_t label_u32[IDN2_LABEL_MAX_LENGTH];
	  size_t label_len;

	  /* convert UTF-8 to UTF-32 */
	  if (!(domain_u32 = u8_to_u32 (s, e - s, NULL, &label_len)))
	    {
	      if (errno == ENOMEM)
		return IDN2_MALLOC;
	      return IDN2_ENCODING_ERROR;
	    }

	  if (label_len > IDN2_LABEL_MAX_LENGTH)
	    {
	      free (domain_u32);
	      return IDN2_TOO_BIG_DOMAIN;
	    }

	  if (out_len + label_len + (*e == '.') > IDN2_DOMAIN_MAX_LENGTH)
	    {
	      free (domain_u32);
	      return IDN2_TOO_BIG_DOMAIN;
	    }

	  u32_cpy (out_u32 + out_len, domain_u32, label_len);
	  out_len += label_len;
	  if (*e == '.')
	    out_u32[out_len++] = '.';
	  free (domain_u32);

	}

      if (*e)
	e++;
    }

  out_u32[out_len] = 0;

  uint8_t *_out = u32_to_u8 (out_u32, out_len + 1, NULL, &len);

  if (out)
    {
      if (!_out)
        {
	  if (errno == ENOMEM)
	    return IDN2_MALLOC;
	  return IDN2_ENCODING_ERROR;
	}

      *out = _out;
    }

  return IDN2_OK;
}
