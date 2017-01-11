/* tr46map.c - header file for IDNA2008 TR46
   Copyright (C) 2016 Tim Rühsen

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

#include <stdint.h>

typedef struct
{
  uint32_t cp1;
  uint16_t range;
  unsigned nmappings:5,		/* 0-18, # of uint32_t at <offset> */
    offset:14,			/* 0-16383, byte offset into mapdata */
    valid:1,
    mapped:1,
    ignored:1,
    deviation:1,
    disallowed:1,
    disallowed_std3_mapped:1,
    disallowed_std3_valid:1;
} IDNAMap;

typedef struct
{
  uint32_t cp1, cp2;
  char check;			/* 0=NO 2=MAYBE (YES if codepoint has no table entry) */
} NFCQCMap;

IDNAMap *get_idna_map (uint32_t c);
int get_map_data (uint32_t *dst, const IDNAMap *map);

NFCQCMap *get_nfcqc_map (uint32_t c);
