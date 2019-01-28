/*
 * Copyright(c) 2019 Tim Ruehsen
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

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	char *ulabel, *alabel;
	char *out;

	if (size > 1024)
		return 0;

	ulabel = (char *) malloc(size + 1);
	assert(ulabel != NULL);

	/* 0 terminate */
	memcpy(ulabel, data, size);
	ulabel[size] = 0;

	if (size == 0) {
		/*** test NULL input/output combinations ***/

		if (idn2_register_ul(NULL, NULL, &out, 0) == IDN2_OK)
			idn2_free(out);
		idn2_register_ul(ulabel, NULL, NULL, 0);
	}

	if (idn2_register_ul(ulabel, NULL, &out, 0) == IDN2_OK)
		idn2_free(out);

	free(ulabel);

	alabel = (char *) malloc(size + 4 + 1);
	assert(alabel != NULL);

	/* 0 terminate */
	memcpy(alabel, "xn--", 4);
	memcpy(alabel + 4, data, size);
	alabel[size] = 0;

	if (idn2_register_ul(NULL, alabel, &out, 0) == IDN2_OK)
		idn2_free(out);

	/*** test NULL input/output combinations ***/
	if (size == 0)
		idn2_register_ul(NULL, alabel, NULL, 0);

	free(alabel);

	return 0;
}
