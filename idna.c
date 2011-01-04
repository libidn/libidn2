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

#include <stdlib.h> /* getsubopt */
#include "unistr.h" /* u8_cpy_alloc */
#include "uninorm.h" /* u8_normalize */

enum
  {
    NFC = 0,
    THE_END
  };

static char *const opts[] = {
  "nfc",
  NULL
};

static int
process (char *opt,
	 const uint8_t *src, size_t srclen,
	 uint8_t **dst, size_t *dstlen)
{
  char *p = opt;
  char *value;
  uint8_t *tmp = u8_cpy_alloc (src, srclen);
  size_t tmplen = srclen;

  if (tmp == NULL)
    return LIBIDNA_MALLOC_ERROR;

  while (p != NULL && *p != '\0')
    {
      switch (getsubopt (&p, (char *const *) opts, &value))
	{
	case NFC:
	  {
	    uint8_t *p = u8_normalize (UNINORM_NFC, tmp, tmplen,
				       NULL, &tmplen);
	    free (tmp);
	    if (p == NULL)
	      return LIBIDNA_NFC_FAIL;
	    tmp = p;
	  }

	case -1:
	  if (!value)
	    break;

	default:
	  return LIBIDNA_UNKNOWN_WHAT;
	  break;
	}
    }

  *dst = tmp;
  *dstlen = tmplen;

  return LIBIDNA_OK;
}

int
libidna_process_u8 (const char *what,
		    const uint8_t *src, size_t srclen,
		    uint8_t **dst, size_t *dstlen)
{
  char *opt;
  int rc;

  if (what == NULL)
    return LIBIDNA_UNKNOWN_WHAT;

  opt = strdup (what);
  if (opt == NULL)
    return LIBIDNA_MALLOC_ERROR;

  rc = process (opt, src, srclen, dst, dstlen);

  free (opt);

  return rc;
}
