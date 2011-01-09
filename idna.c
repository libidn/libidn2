/* idna.c - implementation of high-level IDNA processing function
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

#include "config.h"

#include "libidna.h"

#include <stdlib.h> /* getsubopt */
#include <errno.h> /* errno */

#include "tables.h"
#include "context.h"

#include "unistr.h" /* u32_cpy_alloc */
#include "uninorm.h" /* u32_normalize */
#include "unistr.h" /* u32_normalize */

enum
  {
    CHECK_NFC,
    CHECK_2HYPHEN,
    CHECK_COMBINING,
    CHECK_DISALLOWED,
    CHECK_CONTEXTJ,
    CHECK_CONTEXTJ_RULE,
    CHECK_CONTEXTO,
    CHECK_CONTEXTO_WITH_RULE,
    CHECK_CONTEXTO_RULE,
    CHECK_UNASSIGNED,
    CHECK_BIDI,
    NFC,
    THE_END
  };

static char *const opts[] = {
  "check-nfc",
  "check-2hyphen",
  "check-combining",
  "check-disallowed",
  "check-contextj",
  "check-contextj-rule",
  "check-contexto",
  "check-contexto-with-rule",
  "check-contexto-rule",
  "check-unassigned",
  "check-bidi",
  "nfc",
  NULL
};

static int
process1 (char *opt, uint32_t **label, size_t *llen)
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
	    uint32_t *p = u32_normalize (UNINORM_NFC, *label, *llen,
					 NULL, &plen);
	    int ok;
	    if (p == NULL)
	      {
		if (errno == ENOMEM)
		  return LIBIDNA_MALLOC_ERROR;
		return LIBIDNA_NFC;
	      }
	    ok = *llen == plen && memcmp (*label, p, plen) == 0;
	    free (p);
	    if (!ok)
	      return LIBIDNA_NOT_NFC;
	    break;
	  }

	case CHECK_2HYPHEN:
	  if (*llen >= 4 && (*label)[2] == '-' && (*label)[3] == '-')
	    return LIBIDNA_2HYPHEN;
	  break;

	case CHECK_COMBINING:
	  if (*llen > 0 && uc_is_property_combining ((*label)[0]))
	    return LIBIDNA_COMBINING;
	  break;

	case CHECK_DISALLOWED:
	  {
	    size_t i;
	    for (i = 0; i < *llen; i++)
	      if (_libidna_disallowed_p ((*label)[i]))
		return LIBIDNA_DISALLOWED;
	  }
	  break;

	case CHECK_CONTEXTJ:
	  {
	    size_t i;
	    for (i = 0; i < *llen; i++)
	      if (_libidna_contextj_p ((*label)[i]))
		return LIBIDNA_CONTEXTJ;
	  }
	  break;

	case CHECK_CONTEXTJ_RULE:
	  {
	    size_t i;
	    int rc;

	    for (i = 0; i < *llen; i++)
	      {
		rc = _libidna_contextj_rule ((*label)[i], *label, *llen);
		if (rc != LIBIDNA_OK)
		  return rc;
	      }
	  }
	  break;

	case CHECK_CONTEXTO:
	  {
	    size_t i;
	    for (i = 0; i < *llen; i++)
	      if (_libidna_contexto_p ((*label)[i]))
		return LIBIDNA_CONTEXTJ;
	  }
	  break;

	case CHECK_CONTEXTO_WITH_RULE:
	  {
	    size_t i;
	    for (i = 0; i < *llen; i++)
	      if (_libidna_contexto_p ((*label)[i])
		  && !_libidna_contexto_with_rule ((*label)[i]))
		return LIBIDNA_CONTEXTO_NO_RULE;
	  }
	  break;

	case CHECK_CONTEXTO_RULE:
	  {
	    size_t i;
	    int rc;

	    for (i = 0; i < *llen; i++)
	      {
		rc = _libidna_contexto_rule ((*label)[i], *label, *llen);
		if (rc != LIBIDNA_OK)
		  return rc;
	      }
	  }
	  break;

	case CHECK_UNASSIGNED:
	  {
	    size_t i;
	    for (i = 0; i < *llen; i++)
	      if (_libidna_unassigned_p ((*label)[i]))
		return LIBIDNA_UNASSIGNED;
	  }
	  break;

	case CHECK_BIDI:
	  {
	    int rc = _libidna_bidi (*label, *llen);
	    if (rc != LIBIDNA_OK)
	      return rc;
	  }
	  break;

	case NFC:
	  {
	    uint32_t *p = u32_normalize (UNINORM_NFC, *label, *llen,
					 NULL, llen);
	    if (p == NULL)
	      return LIBIDNA_NFC;
	    free (*label);
	    *label = p;
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

  if (what == NULL || *what == '\0')
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
