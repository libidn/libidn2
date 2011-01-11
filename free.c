/* free.c - implement stub free() caller, typically for Windows
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

#include <config.h>

#include "idn2.h"

#include <stdlib.h> /* free */

/**
 * idn2_free:
 * @ptr: pointer to deallocate
 *
 * Call free(3) on the given pointer.
 **/
void
idn2_free (void *ptr)
{
  free (ptr);
}
