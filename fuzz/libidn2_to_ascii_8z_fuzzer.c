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
 * This file is part of libidn2.
 */

#include <config.h>

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */

#include "idn2.h"
#include "fuzzer.h"

static int flags[] = {
	0,
	IDN2_NFC_INPUT,
	IDN2_TRANSITIONAL,
	IDN2_NONTRANSITIONAL,
	IDN2_TRANSITIONAL|IDN2_USE_STD3_ASCII_RULES,
	IDN2_NONTRANSITIONAL|IDN2_USE_STD3_ASCII_RULES
};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	char *domain;
	char *out;

	if (size > 1024)
		return 0;

	domain = (char *) malloc(size + 1);
	assert(domain != NULL);

	/* 0 terminate */
	memcpy(domain, data, size);
	domain[size] = 0;

	for (unsigned it = 0; it < sizeof(flags)/sizeof(flags[0]); it++) {
		if (idn2_to_ascii_8z(domain, &out, flags[it]) == IDNA_SUCCESS)
			idn2_free(out);
		if (idn2_to_ascii_lz(domain, &out, flags[it]) == IDNA_SUCCESS)
			idn2_free(out);
	}

	if ((size & 3) == 0) {
		uint32_t *u32 = (uint32_t *) malloc(size + 4);
		char *out2 = malloc(64);

		assert(u32 != NULL);
		assert(out2 != NULL);

		for (unsigned it = 0; it < sizeof(flags)/sizeof(flags[0]); it++)
			idn2_to_ascii_4i((uint32_t *) data, size / 4, out2, flags[it]);

		memcpy(u32, data, size);
		u32[size / 4] = 0;

		for (unsigned it = 0; it < sizeof(flags)/sizeof(flags[0]); it++)
			if (idn2_to_ascii_4z(u32, &out, flags[it]) == IDN2_OK)
			  idn2_free(out);

		free(out2);
		free(u32);
	}

	free(domain);
	return 0;
}
