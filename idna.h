/* idna.h - internal IDNA function prototypes
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

#include <stdint.h>

enum
  {
    ZERO = 0,
    CHECK_NFC,
    CHECK_2HYPHEN,
    CHECK_HYPHEN_STARTEND,
    CHECK_LEADING_COMBINING,
    CHECK_DISALLOWED,
    CHECK_CONTEXTJ, /* is code point a CONTEXTJ code point? */
    CHECK_CONTEXTJ_RULE, /* does code point pass CONTEXTJ rule? */
    CHECK_CONTEXTO, /* is code point a CONTEXTO code point? */
    CHECK_CONTEXTO_WITH_RULE, /* is there a CONTEXTO rule for code point? */
    CHECK_CONTEXTO_RULE, /* does code point pass CONTEXTO rule? */
    CHECK_UNASSIGNED,
    CHECK_BIDI,
    ACE,
    NFC
  };

int _idn2_domain_u8 (const int what[], const uint8_t *src, uint8_t **dst);
