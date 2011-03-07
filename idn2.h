/* idn2.h - header file for idn2
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

#ifndef IDN2_H
# define IDN2_H

# ifndef IDN2_API
#  if defined IDN2_BUILDING && defined HAVE_VISIBILITY && HAVE_VISIBILITY
#   define IDN2_API __attribute__((__visibility__("default")))
#  elif defined IDN2_BUILDING && defined _MSC_VER && ! defined IDN2_STATIC
#   define IDN2_API __declspec(dllexport)
#  elif defined _MSC_VER && ! defined IDN2_STATIC
#   define IDN2_API __declspec(dllimport)
#  else
#   define IDN2_API
#  endif
# endif

#include <stdint.h> /* uint32_t */
#include <string.h> /* size_t */

/**
 * IDN2_VERSION
 *
 * Pre-processor symbol with a string that describe the header file
 * version number.  Used together with idn2_check_version() to verify
 * header file and run-time library consistency.
 */
# define IDN2_VERSION "0.0.0"

/**
 * IDN2_VERSION_NUMBER
 *
 * Pre-processor symbol with a hexadecimal value describing the
 * header file version number.  For example, when the header version
 * is 1.2.3 this symbol will have the value 0x010203.
 */
# define IDN2_VERSION_NUMBER 0x000000

/* IDNA2008 flags */

/**
 * idn2_flags:
 * @IDN2_NFC_INPUT: Normalize input string using normalization form C.
 * @IDN2_ALABEL_ROUNDTRIP: Perform optional IDNA2008 roundtrip check.
 *
 * Flags to IDNA2008 functions, to be binary or:ed together.  Specify
 * only 0 if you want the default behaviour.
 */
typedef enum
  {
    IDN2_NFC_INPUT = 1,
    IDN2_ALABEL_ROUNDTRIP = 2,
  } idn2_flags;

/* IDNA2008 with UTF-8 input. */

extern IDN2_API int
idn2_register_u8 (const uint8_t *ulabel, const uint8_t *alabel,
		  uint8_t **lookupname, int flags);

extern IDN2_API int
idn2_lookup_u8 (const uint8_t *src, uint8_t **lookupname, int flags);

/* IDNA2008 with locale encoded inputs. */

extern IDN2_API int
idn2_register_ul (const char *ulabel, const char *alabel,
		  char **lookupname, int flags);

extern IDN2_API int
idn2_lookup_ul (const char *src, char **lookupname, int flags);

/**
 * idn2_rc:
 * @IDN2_OK: Successful return
 * @IDN2_INTERNAL_ERROR: Indicates an internal error in the library.
 *
 * Return codes for IDN2 functions.  All return codes are negative
 * except for the successful code IDN2_OK which are guaranteed to be
 * 0.  Positive values are reserved for non-error return codes.
 *
 * Note that the #idn2_rc enumeration may be extended at a later date
 * to include new return codes.
 */
typedef enum
{
  IDN2_OK = 0,
  IDN2_INTERNAL_ERROR = -1,
  IDN2_ENCODING_ERROR = -100,
  IDN2_MALLOC = -101,
  IDN2_NOT_NFC = -102,
  IDN2_2HYPHEN = -103,
  IDN2_HYPHEN_STARTEND = -104,
  IDN2_COMBINING = -105,
  IDN2_DISALLOWED = -106,
  IDN2_CONTEXTJ = -107,
  IDN2_CONTEXTJ_NO_RULE = -108,
  IDN2_CONTEXTO = -109,
  IDN2_CONTEXTO_NO_RULE = -110,
  IDN2_UNASSIGNED = -111,
  IDN2_BIDI = -112,
  IDN2_PUNYCODE_BAD_INPUT = -200,
  IDN2_PUNYCODE_BIG_OUTPUT = -201,
  IDN2_PUNYCODE_OVERFLOW = -202,
  IDN2_NFC = -300
} idn2_rc;

/* Auxilliary functions. */

extern IDN2_API const char *idn2_strerror (int rc);
extern IDN2_API const char *idn2_strerror_name (int rc);

extern IDN2_API const char *idn2_check_version (const char *req_version);

extern IDN2_API void idn2_free (void *ptr);

#endif /* IDN2_H */
