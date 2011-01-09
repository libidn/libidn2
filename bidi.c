/* bidi.c - IDNA right to left checking functions
   Copyright (C) 2011 Simon Josefsson

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "config.h"

#include "libidna.h"

#include <stdbool.h>

#include "bidi.h"

#include "unictype.h"

static bool
bidi_p (uint32_t *label, size_t llen)
{
  int bc;

  for (; llen > 0; label++, llen--)
    {
      bc = uc_bidi_category (*label);

      switch (bc)
	{
	  /* An RTL label is a label that contains at least one
	     character of type R, AL, or AN. */
	case UC_BIDI_R:
	case UC_BIDI_AL:
	case UC_BIDI_AN:
	  return true;
	}
    }

  return false;
}

static bool
rtl_ralanenescsetonbnnsm_p (uint32_t *label, size_t llen)
{
  int bc;

  for (; llen > 0; label++, llen--)
    {
      bc = uc_bidi_category (*label);

      switch (bc)
	{
	  /* In an RTL label, only characters with the Bidi properties R, AL,
	     AN, EN, ES, CS, ET, ON, BN, or NSM are allowed. */
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

static int
_libidna_rtl (uint32_t *label, size_t llen)
{
  if (!rtl_ralanenescsetonbnnsm_p (label, llen))
    return LIBIDNA_BIDI;

  return LIBIDNA_OK;
}

static int
_libidna_ltr (uint32_t *label, size_t llen)
{
  return LIBIDNA_OK;
}

int
_libidna_bidi (uint32_t *label, size_t llen)
{
  int bc;

  /* A "Bidi domain name" is a domain name that contains at least one
     RTL label. */
  if (!bidi_p (label, llen))
    return LIBIDNA_OK;

  /* The first character must be a character with Bidi property L, R,
     or AL. */
  bc = uc_bidi_category (*label);
  switch (bc)
    {
    case UC_BIDI_L:
      return _libidna_ltr (label, llen);

    case UC_BIDI_R:
    case UC_BIDI_AL:
      return _libidna_rtl (label, llen);
    }

  return LIBIDNA_BIDI;
}
