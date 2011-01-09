/* context.h - check contextual rule on label
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

#include <stdint.h>
#include <stdbool.h>

int
_libidna_contextj_rule (uint32_t cp, uint32_t *label, size_t llen);

int
_libidna_contexto_rule (uint32_t cp, uint32_t *label, size_t llen);

bool
_libidna_contexto_with_rule (uint32_t cp);
