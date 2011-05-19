/* punycode.h - prototypes for internal punycode functions
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

extern int _idn2_punycode_encode (size_t input_length,
				  const uint32_t input[],
				  const unsigned char case_flags[],
				  size_t * output_length, char output[]);

extern int _idn2_punycode_decode (size_t input_length,
				  const char input[],
				  size_t * output_length,
				  uint32_t output[],
				  unsigned char case_flags[]);
