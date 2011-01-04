/*
 * nfc.c - Unicode NFC
 * Copyright (C) 2011 Simon Josefsson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include "libidna.h"

#include <errno.h>

int
libidna_process_u8 (const char *what,
		    const uint8_t *src, size_t srclen,
		    uint8_t **dst, size_t *dstlen)
{
#if 0
  int rc;
  uint8_t *tmp;
  size_t tmplen;

  /* For char* version do lc->u8 conversion here. */

  tmp = NULL; tmplen = 0;
  rc = libidna_nfc_u8 (src, srclen, &tmp, &tmplen);
  if (rc != LIBIDNA_OK)
    return rc;
#endif

  return LIBIDNA_OK;  
}
