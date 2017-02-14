/* bidi.c - IDNA right to left checking functions
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

#include <stdbool.h>

#include "bidi.h"

#include <unictype.h>

/* The entire bidi rule could be rewritten into an one-pass approach;
   the implementation below may in the worse case iterate through the
   string a few times.  However, recall Knuth and premature
   optimization is the root of all evil. */

static bool
rtl_ralanenescsetonbnnsm_ok (const uint32_t * label, size_t llen)
{
  int bc;

  for (; llen > 0; label++, llen--)
    {
      bc = uc_bidi_category (*label);

      switch (bc)
	{
	case UC_BIDI_R:
	case UC_BIDI_AL:
	case UC_BIDI_AN:
	case UC_BIDI_EN:
	case UC_BIDI_ES:
	case UC_BIDI_CS:
	case UC_BIDI_ET:
	case UC_BIDI_ON:
	case UC_BIDI_BN:
	case UC_BIDI_NSM:
	  break;

	default:
	  return false;
	}
    }

  return true;
}

static bool
rtl_ends_ok (const uint32_t * label, size_t llen)
{
  const uint32_t *p;
  int bc;

  for (p = label + llen - 1; llen > 0; llen--, p--)
    {
      bc = uc_bidi_category (*p);
      switch (bc)
	{
	case UC_BIDI_NSM:
	  continue;

	case UC_BIDI_R:
	case UC_BIDI_AL:
	case UC_BIDI_EN:
	case UC_BIDI_AN:
	  return true;

	default:
	  return false;
	}
    }

  return false;
}

static bool
rtl_enan_ok (const uint32_t * label, size_t llen)
{
  bool en = false;
  bool an = false;
  const uint32_t *p;
  int bc;

  for (p = label + llen - 1; llen > 0; llen--, p--)
    {
      bc = uc_bidi_category (*p);
      switch (bc)
	{
	case UC_BIDI_EN:
	  en = true;
	  break;

	case UC_BIDI_AN:
	  an = true;
	  break;
	}
    }

  return !(en && an);
}

static int
rtl (const uint32_t * label, size_t llen)
{
  if (rtl_ralanenescsetonbnnsm_ok (label, llen)
      && rtl_ends_ok (label, llen) && rtl_enan_ok (label, llen))
    return IDN2_OK;
  return IDN2_BIDI;
}

static bool
ltr_lenescsetonbnnsm_ok (const uint32_t * label, size_t llen)
{
  int bc;

  for (; llen > 0; label++, llen--)
    {
      bc = uc_bidi_category (*label);
      switch (bc)
	{
	case UC_BIDI_L:
	case UC_BIDI_EN:
	case UC_BIDI_ES:
	case UC_BIDI_CS:
	case UC_BIDI_ET:
	case UC_BIDI_ON:
	case UC_BIDI_BN:
	case UC_BIDI_NSM:
	  break;

	default:
	  return false;
	}
    }

  return true;
}

static bool
ltr_ends_ok (const uint32_t * label, size_t llen)
{
  const uint32_t *p;
  int bc;

  for (p = label + llen - 1; llen > 0; llen--, p--)
    {
      bc = uc_bidi_category (*p);
      switch (bc)
	{
	case UC_BIDI_NSM:
	  continue;

	case UC_BIDI_L:
	case UC_BIDI_EN:
	  return true;

	default:
	  return false;
	}
    }

  return false;
}

static int
ltr (const uint32_t * label, size_t llen)
{
  if (ltr_lenescsetonbnnsm_ok (label, llen) && ltr_ends_ok (label, llen))
    return IDN2_OK;
  return IDN2_BIDI;
}

static bool
bidi_p (const uint32_t * label, size_t llen)
{
  int bc;

  for (; llen > 0; label++, llen--)
    {
      bc = uc_bidi_category (*label);

      switch (bc)
	{
	case UC_BIDI_R:
	case UC_BIDI_AL:
	case UC_BIDI_AN:
	  return true;
	}
    }

  return false;
}

int
_idn2_bidi (const uint32_t * label, size_t llen)
{
  int bc;

  if (!bidi_p (label, llen))
    return IDN2_OK;

  bc = uc_bidi_category (*label);
  switch (bc)
    {
    case UC_BIDI_L:
      return ltr (label, llen);

    case UC_BIDI_R:
    case UC_BIDI_AL:
      return rtl (label, llen);
    }

  return IDN2_BIDI;
}
