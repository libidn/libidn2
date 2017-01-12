/* tr46map.c - implementation of IDNA2008 TR46 functions
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

#include <config.h>
#include <stdint.h>
#include <stdlib.h>

#include "tr46map_data.c"

#define countof(a) (sizeof(a)/sizeof(*(a)))

static int
_compare_idna_map(uint32_t *c, IDNAMap *m2)
{
  if (*c < m2->cp1)
    return -1;
  if (*c > m2->cp1 + m2->range)
    return 1;
  return 0;
}

IDNAMap
*get_idna_map(uint32_t c)
{
  return bsearch(&c, idna_map, countof(idna_map), sizeof(IDNAMap), (int(*)(const void *, const void *))_compare_idna_map);
}

int
map_is(const IDNAMap *map, unsigned flags)
{
  return (idna_flags[map->flag_index] & flags) == flags;
}

static int
_compare_nfcqc_map(uint32_t *c, NFCQCMap *m2)
{
  if (*c < m2->cp1)
    return -1;
  if (*c > m2->cp2)
    return 1;
  return 0;
}

NFCQCMap
*get_nfcqc_map(uint32_t c)
{
  return bsearch(&c, nfcqc_map, countof(nfcqc_map), sizeof(NFCQCMap), (int(*)(const void *, const void *))_compare_nfcqc_map);
}

/* copy 'n' codepoints from mapdata stream */
int
get_map_data (uint32_t *dst, const IDNAMap *map)
{
  int n = map->nmappings;
  uint8_t *src = mapdata + map->offset;

  for (; (ssize_t) n > 0; n--)
    {
      uint32_t cp = 0;
      do
        cp = (cp << 7) | (*src & 0x7F);
      while (*src++ & 0x80);
      *dst++ = cp;
    }

  return map->nmappings;
}
