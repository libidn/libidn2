/* context.c - check contextual rule on label
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

#include "context.h"

int
_libidna_contextj_rule (uint32_t cp, uint32_t *label, size_t llen)
{
  if (!_libidna_contextj_p (cp))
    return LIBIDNA_OK;

  switch (cp)
    {
    case 0x200C:
      /* ZERO WIDTH NON-JOINER */
    case 0x200D:
      /* ZERO WIDTH JOINER */
      break;
    }

  return LIBIDNA_CONTEXTJ_NO_RULE;
}

int
_libidna_contexto_rule (uint32_t cp, uint32_t *label, size_t llen)
{
  if (!_libidna_contexto_p (cp))
    return LIBIDNA_OK;

  switch (cp)
    {
    case 0x00B7:
      /* MIDDLE DOT */
    case 0x0375:
      /* GREEK LOWER NUMERAL SIGN (KERAIA) */
    case 0x05F3:
      /* HEBREW PUNCTUATION GERESH */
    case 0x05F4:
      /* HEBREW PUNCTUATION GERSHAYIM */
    case 0x0660:
    case 0x0661:
    case 0x0662:
    case 0x0663:
    case 0x0664:
    case 0x0665:
    case 0x0666:
    case 0x0667:
    case 0x0668:
    case 0x0669:
      /* ARABIC-INDIC DIGITS */
    case 0x06F0:
    case 0x06F1:
    case 0x06F2:
    case 0x06F3:
    case 0x06F4:
    case 0x06F5:
    case 0x06F6:
    case 0x06F7:
    case 0x06F8:
    case 0x06F9:
      /* EXTENDED ARABIC-INDIC DIGITS */
    case 0x30FB:
      /* KATAKANA MIDDLE DOT */
      break;
    }

  return LIBIDNA_CONTEXTO_NO_RULE;
}

bool
_libidna_has_contexto_rule (uint32_t cp)
{
  switch (cp)
    {
    case 0x00B7:
      /* MIDDLE DOT */
    case 0x0375:
      /* GREEK LOWER NUMERAL SIGN (KERAIA) */
    case 0x05F3:
      /* HEBREW PUNCTUATION GERESH */
    case 0x05F4:
      /* HEBREW PUNCTUATION GERSHAYIM */
    case 0x0660:
    case 0x0661:
    case 0x0662:
    case 0x0663:
    case 0x0664:
    case 0x0665:
    case 0x0666:
    case 0x0667:
    case 0x0668:
    case 0x0669:
      /* ARABIC-INDIC DIGITS */
    case 0x06F0:
    case 0x06F1:
    case 0x06F2:
    case 0x06F3:
    case 0x06F4:
    case 0x06F5:
    case 0x06F6:
    case 0x06F7:
    case 0x06F8:
    case 0x06F9:
      /* EXTENDED ARABIC-INDIC DIGITS */
    case 0x30FB:
      /* KATAKANA MIDDLE DOT */
      return true;
      break;
    }

  return false;
}
