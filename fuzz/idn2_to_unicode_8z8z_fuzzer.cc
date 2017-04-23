/*
 * Copyright (C) 2017 Red Hat, Inc.
 *
 * Author: Nikos Mavrogiannopoulos
 *
 * This file is part of libidn2.
 *
 * libidn2 is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libidn2 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "idn2.h"

extern "C" int
LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  int ret;
  char *in = (char*) malloc (size + 1);
  char *out;

  assert (in != NULL);

  /* null terminate */
  memcpy (in, data, size);
  in[size] = 0;

  ret = idn2_to_unicode_8z8z (in, &out, 0);
  if (ret != 0)
    goto cleanup;

  free (out);

cleanup:
  free (in);
  return 0;
}
