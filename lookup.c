/* lookup.c - implementation of IDNA2008 lookup functions
   Copyright (C) 2011-2017 Simon Josefsson

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
#include <uninorm.h>		/* u32_normalize */
#include <unistr.h>		/* u8_to_u32 */

#include "idna.h"		/* _idn2_label_test */
#include "tr46map.h"		/* defintion for tr46map.c */

static int
label (const uint8_t * src, size_t srclen, uint8_t * dst, size_t * dstlen,
       int flags)
{
  size_t plen;
  uint32_t *p;
  int rc;
  size_t tmpl;

  if (_idn2_ascii_p (src, srclen))
    {
      if (flags & IDN2_ALABEL_ROUNDTRIP)
	/* FIXME implement this MAY:

	   If the input to this procedure appears to be an A-label
	   (i.e., it starts in "xn--", interpreted
	   case-insensitively), the lookup application MAY attempt to
	   convert it to a U-label, first ensuring that the A-label is
	   entirely in lowercase (converting it to lowercase if
	   necessary), and apply the tests of Section 5.4 and the
	   conversion of Section 5.5 to that form. */
	return -1;

      if (srclen > IDN2_LABEL_MAX_LENGTH)
	return IDN2_TOO_BIG_LABEL;
      if (srclen > *dstlen)
	return IDN2_TOO_BIG_DOMAIN;

      memcpy (dst, src, srclen);
      *dstlen = srclen;
      return IDN2_OK;
    }

  rc = _idn2_u8_to_u32_nfc (src, srclen, &p, &plen, flags & IDN2_NFC_INPUT);
  if (rc != IDN2_OK)
    return rc;

  rc = _idn2_label_test (TEST_NFC |
			 TEST_2HYPHEN |
			 TEST_LEADING_COMBINING |
			 TEST_DISALLOWED |
			 TEST_CONTEXTJ_RULE |
			 TEST_CONTEXTO_WITH_RULE |
			 TEST_UNASSIGNED | TEST_BIDI, p, plen);
  if (rc != IDN2_OK)
    {
      free (p);
      return rc;
    }

  dst[0] = 'x';
  dst[1] = 'n';
  dst[2] = '-';
  dst[3] = '-';

  tmpl = *dstlen - 4;
  rc = _idn2_punycode_encode (plen, p, NULL, &tmpl, (char *) dst + 4);
  free (p);
  if (rc != IDN2_OK)
    return rc;

  *dstlen = 4 + tmpl;

  return IDN2_OK;
}

#define TR46_TRANSITIONAL_CHECK \
  (TEST_NFC | TEST_2HYPHEN | TEST_HYPHEN_STARTEND | TEST_LEADING_COMBINING | TEST_TRANSITIONAL)
#define TR46_NONTRANSITIONAL_CHECK \
  (TEST_NFC | TEST_2HYPHEN | TEST_HYPHEN_STARTEND | TEST_LEADING_COMBINING | TEST_NONTRANSITIONAL)

static int
_tr46 (const uint8_t * domain_u8, uint8_t ** out, int transitional)
{
  size_t len, it;
  uint32_t *domain_u32;
  int err = IDN2_OK, rc;

  /* convert UTF-8 to UTF-32 */
  if (!
      (domain_u32 =
       u8_to_u32 (domain_u8, u8_strlen (domain_u8) + 1, NULL, &len)))
    {
      if (errno == ENOMEM)
	return IDN2_MALLOC;
      return IDN2_ENCODING_ERROR;
    }

  size_t len2 = 0;
  for (it = 0; it < len - 1; it++)
    {
      IDNAMap map;

      get_idna_map (domain_u32[it], &map);

      if (map_is (&map, TR46_FLG_DISALLOWED))
	{
	  if (domain_u32[it])
	    {
	      free (domain_u32);
	      return IDN2_DISALLOWED;
	    }
	  len2++;
	}
      else if (map_is (&map, TR46_FLG_MAPPED))
	{
	  len2 += map.nmappings;
	}
      else if (map_is (&map, TR46_FLG_VALID))
	{
	  len2++;
	}
      else if (map_is (&map, TR46_FLG_IGNORED))
	{
	  continue;
	}
      else if (map_is (&map, TR46_FLG_DEVIATION))
	{
	  if (transitional)
	    {
	      len2 += map.nmappings;
	    }
	  else
	    len2++;
	}
    }

  uint32_t *tmp = malloc ((len2 + 1) * sizeof (uint32_t));

  len2 = 0;
  for (it = 0; it < len - 1; it++)
    {
      uint32_t c = domain_u32[it];
      IDNAMap map;

      get_idna_map (c, &map);

      if (map_is (&map, TR46_FLG_DISALLOWED))
	{
	  tmp[len2++] = c;
	}
      else if (map_is (&map, TR46_FLG_MAPPED))
	{
	  len2 += get_map_data (tmp + len2, &map);
	}
      else if (map_is (&map, TR46_FLG_VALID))
	{
	  tmp[len2++] = c;
	}
      else if (map_is (&map, TR46_FLG_IGNORED))
	{
	  continue;
	}
      else if (map_is (&map, TR46_FLG_DEVIATION))
	{
	  if (transitional)
	    {
	      len2 += get_map_data (tmp + len2, &map);
	    }
	  else
	    tmp[len2++] = c;
	}
    }
  free (domain_u32);

  /* Normalize to NFC */
  tmp[len2] = 0;
  domain_u32 = u32_normalize (UNINORM_NFC, tmp, len2 + 1, NULL, &len);
  free (tmp);
  tmp = NULL;

  if (!domain_u32)
    {
      if (errno == ENOMEM)
	return IDN2_MALLOC;
      return IDN2_ENCODING_ERROR;
    }

  /* split into labels and check */
  uint32_t *e, *s;
  e = s = domain_u32;
  for (e = s = domain_u32; *e; s = e)
    {
      while (*e && *e != '.')
	e++;

      if (e - s >= 4 && s[0] == 'x' && s[1] == 'n' && s[2] == '-'
	  && s[3] == '-')
	{
	  /* decode punycode and check result non-transitional */
	  size_t ace_len;
	  uint32_t name_u32[IDN2_LABEL_MAX_LENGTH];
	  size_t name_len = IDN2_LABEL_MAX_LENGTH;
	  uint8_t *ace;

	  ace = u32_to_u8 (s + 4, e - s - 4, NULL, &ace_len);
	  if (!ace)
	    {
	      free (domain_u32);
	      if (errno == ENOMEM)
		return IDN2_MALLOC;
	      return IDN2_ENCODING_ERROR;
	    }

	  rc =
	    _idn2_punycode_decode (ace_len, (char *) ace, &name_len, name_u32,
				   NULL);

	  free (ace);

	  if (rc)
	    {
	      free (domain_u32);
	      return rc;
	    }

	  if ((rc =
	       _idn2_label_test (TR46_NONTRANSITIONAL_CHECK, name_u32,
				 name_len)))
	    err = rc;
	}
      else
	{
	  if ((rc =
	       _idn2_label_test (transitional ? TR46_TRANSITIONAL_CHECK :
				 TR46_NONTRANSITIONAL_CHECK, s, e - s)))
	    err = rc;
	}

      if (*e)
	e++;
    }

  if (err == IDN2_OK && out)
    {
      uint8_t *_out = u32_to_u8 (domain_u32, len, NULL, &len);
      free (domain_u32);

      if (!_out)
	{
	  if (errno == ENOMEM)
	    return IDN2_MALLOC;
	  return IDN2_ENCODING_ERROR;
	}

      *out = _out;
    }
  else
    free (domain_u32);

  return err;
}

/**
 * idn2_lookup_u8:
 * @src: input zero-terminated UTF-8 string in Unicode NFC normalized form.
 * @lookupname: newly allocated output variable with name to lookup in DNS.
 * @flags: optional #idn2_flags to modify behaviour.
 *
 * Perform IDNA2008 lookup string conversion on domain name @src, as
 * described in section 5 of RFC 5891.  Note that the input string
 * must be encoded in UTF-8 and be in Unicode NFC form.
 *
 * Pass %IDN2_NFC_INPUT in @flags to convert input to NFC form before
 * further processing.  Pass %IDN2_ALABEL_ROUNDTRIP in @flags to
 * convert any input A-labels to U-labels and perform additional
 * testing.  Pass %IDN2_TRANSITIONAL to enable Unicode TR46
 * transitional processing, and %IDN2_NONTRANSITIONAL to enable
 * Unicode TR46 non-transitional processing.  Multiple flags may be
 * specified by binary or:ing them together, for example
 * %IDN2_NFC_INPUT | %IDN2_NONTRANSITIONAL.
 *
 * After version 0.11: @lookupname may be NULL to test lookup of @src
 * without allocating memory.
 *
 * Returns: On successful conversion %IDN2_OK is returned, if the
 *   output domain or any label would have been too long
 *   %IDN2_TOO_BIG_DOMAIN or %IDN2_TOO_BIG_LABEL is returned, or
 *   another error code is returned.
 **/
int
idn2_lookup_u8 (const uint8_t * src, uint8_t ** lookupname, int flags)
{
  size_t lookupnamelen = 0;
  uint8_t _lookupname[IDN2_DOMAIN_MAX_LENGTH + 1];
  uint8_t _mapped[IDN2_DOMAIN_MAX_LENGTH + 1];
  int rc, tr46_mode = 0;

  if (src == NULL)
    {
      if (lookupname)
	*lookupname = NULL;
      return IDN2_OK;
    }

  if ((flags & (IDN2_TRANSITIONAL | IDN2_NONTRANSITIONAL)) ==
      (IDN2_TRANSITIONAL | IDN2_NONTRANSITIONAL))
    return IDN2_INVALID_FLAGS;

  if (flags & IDN2_TRANSITIONAL)
    tr46_mode = IDN2_TRANSITIONAL;
  else if (flags & IDN2_NONTRANSITIONAL)
    tr46_mode = IDN2_NONTRANSITIONAL;

  if (tr46_mode)
    {
      uint8_t *out;
      size_t outlen;

      rc = _tr46 (src, &out, tr46_mode == IDN2_TRANSITIONAL);
      if (rc != IDN2_OK)
	return rc;

      outlen = u8_strlen (out);
      if (outlen >= sizeof (_mapped))
	{
	  free (out);
	  return IDN2_TOO_BIG_DOMAIN;
	}

      memcpy (_mapped, out, outlen + 1);
      src = _mapped;
      free (out);
    }

  do
    {
      const uint8_t *end = (uint8_t *) strchrnul ((const char *) src, '.');
      /* XXX Do we care about non-U+002E dots such as U+3002, U+FF0E
         and U+FF61 here?  Perhaps when IDN2_NFC_INPUT? */
      size_t labellen = end - src;
      uint8_t tmp[IDN2_LABEL_MAX_LENGTH];
      size_t tmplen = IDN2_LABEL_MAX_LENGTH;

      rc = label (src, labellen, tmp, &tmplen, flags);
      if (rc != IDN2_OK)
	return rc;

      if (lookupnamelen + tmplen
	  > IDN2_DOMAIN_MAX_LENGTH - (tmplen == 0 && *end == '\0' ? 1 : 2))
	return IDN2_TOO_BIG_DOMAIN;

      memcpy (_lookupname + lookupnamelen, tmp, tmplen);
      lookupnamelen += tmplen;

      if (*end == '.')
	{
	  if (lookupnamelen + 1 > IDN2_DOMAIN_MAX_LENGTH)
	    return IDN2_TOO_BIG_DOMAIN;

	  _lookupname[lookupnamelen] = '.';
	  lookupnamelen++;
	}
      _lookupname[lookupnamelen] = '\0';

      src = end;
    }
  while (*src++);

  if (lookupname)
    {
      uint8_t *tmp = malloc (lookupnamelen + 1);

      if (tmp == NULL)
	return IDN2_MALLOC;

      memcpy (tmp, _lookupname, lookupnamelen + 1);
      *lookupname = tmp;
    }

  return IDN2_OK;
}

/**
 * idn2_lookup_ul:
 * @src: input zero-terminated locale encoded string.
 * @lookupname: newly allocated output variable with name to lookup in DNS.
 * @flags: optional #idn2_flags to modify behaviour.
 *
 * Perform IDNA2008 lookup string conversion on domain name @src, as
 * described in section 5 of RFC 5891.  Note that the input is assumed
 * to be encoded in the locale's default coding system, and will be
 * transcoded to UTF-8 and NFC normalized by this function.
 *
 * Pass %IDN2_ALABEL_ROUNDTRIP in @flags to convert any input A-labels
 * to U-labels and perform additional testing.  Pass
 * %IDN2_TRANSITIONAL to enable Unicode TR46 transitional processing,
 * and %IDN2_NONTRANSITIONAL to enable Unicode TR46 non-transitional
 * processing.  Multiple flags may be specified by binary or:ing them
 * together, for example %IDN2_ALABEL_ROUNDTRIP |
 * %IDN2_NONTRANSITIONAL.  The %IDN2_NFC_INPUT in @flags is always
 * enabled in this function.
 *
 * After version 0.11: @lookupname may be NULL to test lookup of @src
 * without allocating memory.
 *
 * Returns: On successful conversion %IDN2_OK is returned, if
 *   conversion from locale to UTF-8 fails then %IDN2_ICONV_FAIL is
 *   returned, if the output domain or any label would have been too
 *   long %IDN2_TOO_BIG_DOMAIN or %IDN2_TOO_BIG_LABEL is returned, or
 *   another error code is returned.
 **/
int
idn2_lookup_ul (const char *src, char **lookupname, int flags)
{
  uint8_t *utf8src = NULL;
  int rc;

  if (src)
    {
      utf8src = u8_strconv_from_locale (src);
      if (utf8src == NULL)
	{
	  if (errno == ENOMEM)
	    return IDN2_MALLOC;
	  return IDN2_ICONV_FAIL;
	}
    }

  rc = idn2_lookup_u8 (utf8src, (uint8_t **) lookupname,
		       flags | IDN2_NFC_INPUT);

  free (utf8src);

  return rc;
}
