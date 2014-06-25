/* idna.c - implementation of high-level IDNA processing function
   Copyright (C) 2011-2014 Simon Josefsson

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

#include <stdlib.h>		/* free */
#include <errno.h>		/* errno */

#include "bidi.h"
#include "tables.h"
#include "context.h"

#include <unictype.h>		/* uc_is_general_category, UC_CATEGORY_M */
#include <uninorm.h>		/* u32_normalize */
#include <unistr.h>		/* u8_to_u32 */

#include "idna.h"

int
_idn2_u8_to_u32_nfc (const uint8_t * src, size_t srclen,
		     uint32_t ** out, size_t * outlen, int nfc)
{
  uint32_t *p;
  size_t plen;

  p = u8_to_u32 (src, srclen, NULL, &plen);
  if (p == NULL)
    {
      if (errno == ENOMEM)
	return IDN2_MALLOC;
      return IDN2_ENCODING_ERROR;
    }

  if (nfc)
    {
      size_t tmplen;
      uint32_t *tmp = u32_normalize (UNINORM_NFC, p, plen, NULL, &tmplen);
      free (p);
      if (tmp == NULL)
	{
	  if (errno == ENOMEM)
	    return IDN2_MALLOC;
	  return IDN2_NFC;
	}

      p = tmp;
      plen = tmplen;
    }

  *out = p;
  *outlen = plen;
  return IDN2_OK;
}

bool
_idn2_ascii_p (const uint8_t * src, size_t srclen)
{
  size_t i;
  bool ascii = true;

  for (i = 0; i < srclen; i++)
    if (src[i] >= 0x80)
      ascii = false;

  return ascii;
}

int
_idn2_label_test (int what, const uint32_t * label, size_t llen)
{
  if (what & TEST_NFC)
    {
      size_t plen;
      uint32_t *p = u32_normalize (UNINORM_NFC, label, llen,
				   NULL, &plen);
      int ok;
      if (p == NULL)
	{
	  if (errno == ENOMEM)
	    return IDN2_MALLOC;
	  return IDN2_NFC;
	}
      ok = llen == plen && memcmp (label, p, plen * sizeof (*label)) == 0;
      free (p);
      if (!ok)
	return IDN2_NOT_NFC;
    }

  if (what & TEST_2HYPHEN)
    {
      if (llen >= 4 && label[2] == '-' && label[3] == '-')
	return IDN2_2HYPHEN;
    }

  if (what & TEST_HYPHEN_STARTEND)
    {
      if (llen > 0 && (label[0] == '-' || label[llen - 1] == '-'))
	return IDN2_HYPHEN_STARTEND;
    }

  if (what & TEST_LEADING_COMBINING)
    {
      if (llen > 0 && uc_is_general_category (label[0], UC_CATEGORY_M))
	return IDN2_LEADING_COMBINING;
    }

  if (what & TEST_DISALLOWED)
    {
      size_t i;
      for (i = 0; i < llen; i++)
	if (_idn2_disallowed_p (label[i]))
	  return IDN2_DISALLOWED;
    }

  if (what & TEST_CONTEXTJ)
    {
      size_t i;
      for (i = 0; i < llen; i++)
	if (_idn2_contextj_p (label[i]))
	  return IDN2_CONTEXTJ;
    }

  if (what & TEST_CONTEXTJ_RULE)
    {
      size_t i;
      int rc;

      for (i = 0; i < llen; i++)
	{
	  rc = _idn2_contextj_rule (label, llen, i);
	  if (rc != IDN2_OK)
	    return rc;
	}
    }

  if (what & TEST_CONTEXTO)
    {
      size_t i;
      for (i = 0; i < llen; i++)
	if (_idn2_contexto_p (label[i]))
	  return IDN2_CONTEXTO;
    }

  if (what & TEST_CONTEXTO_WITH_RULE)
    {
      size_t i;
      for (i = 0; i < llen; i++)
	if (_idn2_contexto_p (label[i])
	    && !_idn2_contexto_with_rule (label[i]))
	  return IDN2_CONTEXTO_NO_RULE;
    }

  if (what & TEST_CONTEXTO_RULE)
    {
      size_t i;
      int rc;

      for (i = 0; i < llen; i++)
	{
	  rc = _idn2_contexto_rule (label, llen, i);
	  if (rc != IDN2_OK)
	    return rc;
	}
    }

  if (what & TEST_UNASSIGNED)
    {
      size_t i;
      for (i = 0; i < llen; i++)
	if (_idn2_unassigned_p (label[i]))
	  return IDN2_UNASSIGNED;
    }

  if (what & TEST_BIDI)
    {
      int rc = _idn2_bidi (label, llen);
      if (rc != IDN2_OK)
	return rc;
    }

  return IDN2_OK;
}
