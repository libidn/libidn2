/*
 * idna.c - implementation of high-level IDNA processing function
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
#include "unistr.h" /* u8_normalize */

enum
  {
    CHECK_ENCODING = 0,
    CHECK_NFC,
    NFC,
    THE_END
  };

static char *const opts[] = {
  "check-encoding",
  "check-nfc",
  "nfc",
  NULL
};

static int
process1 (char *opt, uint8_t **str, size_t *strlen)
{
  char *p = opt;
  char *value;

  while (p != NULL && *p != '\0')
    {
      switch (getsubopt (&p, (char *const *) opts, &value))
	{
	case CHECK_ENCODING:
	  if (u8_check (*str, *strlen) != NULL)
	    return LIBIDNA_ENCODING_CHECK_FAIL;
	  break;

	case NFC:
	  {
	    uint8_t *p = u8_normalize (UNINORM_NFC, *str, *strlen,
				       NULL, strlen);
	    if (p == NULL)
	      return LIBIDNA_NFC_FAIL;
	    free (*str);
	    *str = p;
	  }

	case CHECK_NFC:
	  {
	    size_t plen;
	    uint8_t *p = u8_normalize (UNINORM_NFC, *str, *strlen,
				       NULL, &plen);
	    int ok;
	    if (p == NULL)
	      return LIBIDNA_NFC_FAIL;
	    ok = *strlen == plen && memcmp (*str, p, plen) == 0;
	    free (p);
	    if (!ok)
	      return LIBIDNA_NFC_CHECK_FAIL;
	    break;
	  }

	case -1:
	  if (!value)
	    break;

	default:
	  return LIBIDNA_UNKNOWN_WHAT;
	  break;
	}
    }

  return LIBIDNA_OK;
}

static int
process (char *opt,
	 const uint8_t *src, size_t srclen,
	 uint8_t **dst, size_t *dstlen)
{
  uint8_t *tmp = u8_cpy_alloc (src, srclen);
  size_t tmplen = srclen;
  int rc;

  if (tmp == NULL)
    return LIBIDNA_MALLOC_ERROR;

  rc = process1 (opt, &tmp, &tmplen);
  if (rc != LIBIDNA_OK)
    {
      free (tmp);
      return rc;
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
