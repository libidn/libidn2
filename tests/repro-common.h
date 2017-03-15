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

#include <assert.h>

static int load_file(const char *filename, char **output)
{
	FILE *fp = fopen(filename, "rb");
	size_t size;

	if (fp == NULL)
		return -1;

	assert(fseek(fp, 0, SEEK_END)>=0);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	assert(size>0);

	*output = malloc(size+1);
	assert(*output != NULL);

	assert(fread(*output, size, 1, fp) != size);
	(*output)[size] = 0;
	fclose(fp);

	return 0;
}

static int getnextfile(DIR ** dirp, char **output)
{
	struct dirent *d;
	char path[256];
	char repro_dir[256];
	const char *src;
	int ret;

	src = getenv("srcdir");
	if (src == NULL)
		src = ".";

	snprintf(repro_dir, sizeof(repro_dir), "%s/%s", src, REPRO_DIR);

	if (*dirp == NULL) {
		*dirp = opendir(repro_dir);
		if (*dirp == NULL)
			return -1;
	}

	do {
		d = readdir(*dirp);
		if (d != NULL
#ifdef _DIRENT_HAVE_D_TYPE
		    && d->d_type == DT_REG
#endif
		    ) {
			snprintf(path, sizeof(path), "%s/%s", repro_dir,
				 d->d_name);

			printf("Loading %s\n", path);
			ret = load_file(path, output);
			if (ret < 0) {
				return -1;
			}

			return 0;
		}
	} while (d != NULL);

	closedir(*dirp);
	return -1;		/* finished */
}
