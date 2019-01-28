/*
 * Copyright(c) 2017 Tim Ruehsen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This file is part of libidn.
 */

#include <config.h>

#include <assert.h> /* assert */
#include <stdint.h> /* uint8_t, uint32_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */

#include "idn2.h"
#include "fuzzer.h"

#pragma GCC optimize ("O0")

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	char *domain;
	char *out;
	const char *x = "";

	if (size > 1024)
		return 0;

	domain = (char *) malloc(size + 1);
	assert(domain != NULL);

	// 0 terminate
	memcpy(domain, data, size);
	domain[size] = 0;

	if (size == 0) {
		x = idn2_check_version(NULL);

		for (int err = -500; err <= 0; err++) {
			if (idn2_strerror_name(err))
				x = NULL;
			if (idn2_strerror(err))
				x = NULL;
		}

		/*** test NULL input/output combinations ***/

		if (idn2_to_unicode_lzlz(NULL, &out, 0) == IDN2_OK)
			idn2_free(out);
		idn2_to_unicode_lzlz(NULL, NULL, 0);
		idn2_to_unicode_lzlz(domain, NULL, 0);

		{
			uint32_t *in32 = (uint32_t *) malloc(4);
			uint32_t *out32;
			in32[0] = 0;
			if (idn2_to_unicode_4z4z(NULL, &out32, 0) == IDN2_OK)
				idn2_free(out32);
			idn2_to_unicode_4z4z(NULL, NULL, 0);
			idn2_to_unicode_4z4z(in32, NULL, 0);
			free(in32);
		}

		{
			uint32_t *out32;
			if (idn2_to_unicode_8z4z(NULL, &out32, 0) == IDN2_OK)
				idn2_free(out32);
			idn2_to_unicode_8z4z(NULL, NULL, 0);
			idn2_to_unicode_8z4z(domain, NULL, 0);
		}

		{
			uint32_t *u32 = (uint32_t *) malloc(0);
			size_t u32len = 0;
			idn2_to_unicode_44i(NULL, 1, u32, &u32len, 0);
			u32len = 0;
			idn2_to_unicode_44i(NULL, 0, NULL, &u32len, 0);
			free(u32);
		}
	}

	// let's fuzz gnulib's strverscmp()
	if (idn2_check_version(domain))
		x = NULL;

	if (x)
		free(malloc(1)); // prevent compiler from optimizing out idn2_check_version()

	// internally calls idn2_to_unicode_8zlz(), idn2_to_unicode_8z8z(), idn2_to_unicode_8z4z()
	if (idn2_to_unicode_lzlz(domain, &out, 0) == IDN2_OK)
		idn2_free(out);

	if ((size & 3) == 0) {
		uint32_t *u32 = (uint32_t *) malloc(size);
		size_t u32len;

		assert(u32 != NULL);

		// internally calls idn2_to_unicode_4z4z(), idn2_to_unicode_8z4z()
		u32len = size / 4;
		idn2_to_unicode_44i((uint32_t *) data, size / 4, u32, &u32len, 0);

		free(u32);
	}

	free(domain);
	return 0;
}
