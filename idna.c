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
#include <errno.h> /* errno */

#include "unistr.h" /* u32_cpy_alloc */
#include "uninorm.h" /* u32_normalize */
#include "unistr.h" /* u32_normalize */

enum
  {
    CHECK_NFC,
    CHECK_2HYPHEN,
    CHECK_COMBINING,
    NFC,
    THE_END
  };

static char *const opts[] = {
  "check-nfc",
  "check-2hyphen",
  "check-combining",
  "nfc",
  NULL
};

static int
process1 (char *opt, uint32_t **str, size_t *strlen)
{
  char *p = opt;
  char *value;

  while (p != NULL && *p != '\0')
    {
      switch (getsubopt (&p, (char *const *) opts, &value))
	{
	case CHECK_NFC:
	  {
	    size_t plen;
	    uint32_t *p = u32_normalize (UNINORM_NFC, *str, *strlen,
				       NULL, &plen);
	    int ok;
	    if (p == NULL)
	      return LIBIDNA_NFC_FAIL;
	    ok = *strlen == plen && memcmp (*str, p, plen) == 0;
	    free (p);
	    if (!ok)
	      return LIBIDNA_CHECK_NFC_FAIL;
	    break;
	  }

	case CHECK_2HYPHEN:
	  if (*strlen >= 4 && (*str)[2] == '-' && (*str)[3] == '-')
	    return LIBIDNA_CHECK_2HYPHEN_FAIL;
	  break;

	case CHECK_COMBINING:
	  if (*strlen > 0 && uc_is_property_combining (*str[0]))
	    return LIBIDNA_CHECK_COMBINING_FAIL;
	  break;

	case NFC:
	  {
	    uint32_t *p = u32_normalize (UNINORM_NFC, *str, *strlen,
				       NULL, strlen);
	    if (p == NULL)
	      return LIBIDNA_NFC_FAIL;
	    free (*str);
	    *str = p;
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
	 const uint32_t *src, size_t srclen,
	 uint32_t **dst, size_t *dstlen)
{
  uint32_t *tmp = u32_cpy_alloc (src, srclen);
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
libidna_process_u32 (const char *what,
		     const uint32_t *src, size_t srclen,
		     uint32_t **dst, size_t *dstlen)
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

int
libidna_process_u8 (const char *what,
		     const uint8_t *src, size_t srclen,
		     uint8_t **dst, size_t *dstlen)
{
  size_t plen, u32dstlen;
  uint32_t *p = u8_to_u32 (src, srclen, NULL, &plen);
  uint32_t *u32dst = NULL;
  int rc;

  if (p == NULL)
    {
      if (errno == ENOMEM)
	return LIBIDNA_MALLOC_ERROR;
      return LIBIDNA_ENCODING_ERROR;
    }

  rc = libidna_process_u32 (what, p, plen, &u32dst, &u32dstlen);
  free (p);
  if (rc != LIBIDNA_OK)
    return rc;

  *dst = u32_to_u8 (u32dst, u32dstlen, NULL, dstlen);

  if (*dst == NULL)
    return LIBIDNA_MALLOC_ERROR;

  return LIBIDNA_OK;
}
