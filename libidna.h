/* libidna.h - header file for libidna
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

#ifndef LIBIDNA_H
# define LIBIDNA_H

# ifndef LIBIDNA_API
#  if defined LIBIDNA_BUILDING && defined HAVE_VISIBILITY && HAVE_VISIBILITY
#   define LIBIDNA_API __attribute__((__visibility__("default")))
#  elif defined LIBIDNA_BUILDING && defined _MSC_VER && ! defined LIBIDNA_STATIC
#   define LIBIDNA_API __declspec(dllexport)
#  elif defined _MSC_VER && ! defined LIBIDNA_STATIC
#   define LIBIDNA_API __declspec(dllimport)
#  else
#   define LIBIDNA_API
#  endif
# endif

#include <stdint.h>		/* For uint32_t. */
#include <string.h>		/* For size_t.t */

/**
 * LIBIDNA_VERSION
 *
 * Pre-processor symbol with a string that describe the header file
 * version number.  Used together with libidna_check_version() to verify
 * header file and run-time library consistency.
 */
# define LIBIDNA_VERSION "1.0.0"

/**
 * LIBIDNA_VERSION_NUMBER
 *
 * Pre-processor symbol with a hexadecimal value describing the
 * header file version number.  For example, when the header version
 * is 1.2.3 this symbol will have the value 0x010203.
 */
# define LIBIDNA_VERSION_NUMBER 0x010000

/**
 * libidna_rc:
 * @LIBIDNA_OK: Successful return
 *
 * Return codes for LIBIDNA functions.  All return codes are negative
 * except for the successful code LIBIDNA_OK which are guaranteed to be
 * 0.  Positive values are reserved for non-error return codes.
 *
 * Note that the #libidna_rc enumeration may be extended at a later date
 * to include new return codes.
 */
typedef enum
{
  LIBIDNA_OK = 0,
  LIBIDNA_ENCODING_ERROR = -100,
  LIBIDNA_MALLOC_ERROR = -101,
  LIBIDNA_NOT_NFC = -102,
  LIBIDNA_2HYPHEN = -103,
  LIBIDNA_COMBINING = -104,
  LIBIDNA_DISALLOWED = -105,
  LIBIDNA_CONTEXTJ = -106,
  LIBIDNA_CONTEXTJ_RULE = -107,
  LIBIDNA_CONTEXTJ_NO_RULE = -108,
  LIBIDNA_CONTEXTO = -109,
  LIBIDNA_CONTEXTO_RULE = -110,
  LIBIDNA_CONTEXTO_NO_RULE = -111,
  LIBIDNA_UNASSIGNED = -112,
  LIBIDNA_NFC = -150,
  LIBIDNA_UNKNOWN_WHAT = -160
} libidna_rc;

/* Global */

extern LIBIDNA_API const char *libidna_check_version (const char *req_version);

/* IDNA */

extern LIBIDNA_API int
libidna_process_u8 (const char *what,
		    const uint8_t *src, size_t srclen,
		    uint8_t **dst, size_t *dstlen);

/* Punycode */

enum Libidna_punycode_status {
  LIBIDNA_PUNYCODE_SUCCESS,
  LIBIDNA_PUNYCODE_BAD_INPUT,   /* Input is invalid.                       */
  LIBIDNA_PUNYCODE_BIG_OUTPUT,  /* Output would exceed the space provided. */
  LIBIDNA_PUNYCODE_OVERFLOW     /* Input needs wider integers to process.  */
};

extern LIBIDNA_API int
libidna_punycode_encode (size_t input_length,
			 const uint32_t input[],
			 const unsigned char case_flags[],
			 size_t *output_length,
			 char output[]);

extern LIBIDNA_API int
libidna_punycode_decode(size_t input_length,
			const char input[],
			size_t *output_length,
			uint32_t output[],
			unsigned char case_flags[]);

#endif /* LIBIDNA_H */
