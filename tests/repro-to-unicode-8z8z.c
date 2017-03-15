/*
 * Copyright (C) 2017 Red Hat, Inc.
 *
 * Author: Nikos Mavrogiannopoulos
 *
 * This file is part of libidn2.
 *
 * libidn2 is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libidn2 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>

#include "idn2.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>


/* This program will load files from REPRO_DIR and try to convert
 * them to unicode using idn2_to_unicode_8z8z. It is intended to be used
 * with input that were found to be problematic (e.g., crash).
 */

#define REPRO_DIR "unicode-8z8z-interesting"

#include "repro-common.h"

int main(int argc, char **argv)
{
	int ret;
	DIR *dirp = NULL;
	char *input;
	char *output = NULL;

	while (getnextfile(&dirp, &input) == 0) {
		ret = idn2_to_unicode_8z8z(input, &output, 0);
		if (ret == 0) {
			idn2_free(output);
			output = NULL;
		}
		free(input);
	}

	return 0;
}
