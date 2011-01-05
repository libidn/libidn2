/* check.c - IDNA table checking functions
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

#include "check.h"

#include <stdlib.h> /* abort */

#include "tables.h"

static int
property (uint32_t cp)
{
  const struct idna_table *p = idna_table;
  
  while (p->start != 0 || p->end != 0)
    {
      if (p->end == 0 && p->start == cp)
	return p->state;
      else if (p->start <= cp && p->end >= cp)
	return p->state;
      p++;
    }

  abort ();
}

int
_libidna_disallowed_p (uint32_t cp)
{
  return property (cp) == DISALLOWED;
}
