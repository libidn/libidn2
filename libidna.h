/*
 * libidna.h - header file for libidna
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

#include <stdbool.h>		/* For bool. */
#include <stdint.h>		/* For uint64_t, SIZE_MAX. */
#include <string.h>		/* For size_t.t */
#include <time.h>		/* For time_t. */

/**
 * LIBIDNA_VERSION
 *
 * Pre-processor symbol with a string that describe the header file
 * version number.  Used together with libidna_check_version() to verify
 * header file and run-time library consistency.
 */
# define LIBIDNA_VERSION "1.4.0"

/**
 * LIBIDNA_VERSION_NUMBER
 *
 * Pre-processor symbol with a hexadecimal value describing the
 * header file version number.  For example, when the header version
 * is 1.2.3 this symbol will have the value 0x010203.
 */
# define LIBIDNA_VERSION_NUMBER 0x010400

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
} libidna_rc;

/* Global */

extern LIBIDNA_API const char *libidna_check_version (const char *req_version);

#endif /* LIBIDNA_H */
