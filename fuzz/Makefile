# Copyright (C) 2016 Red Hat, Inc.
#
# This file is part of GnuTLS.
#
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This file is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

CC?=afl-gcc
CFLAGS?=-g -O2
COMMON=-I../lib/ -L../lib/.libs -Wl,-rpath=../lib/.libs -lidn2

TESTS = idn2_to_unicode_8z8z_fuzzer idn2_to_ascii_8z_fuzzer

all: $(TESTS)

%: %.cc
	$(CC) $(CFLAGS) main.c $^ $(COMMON) -o $@

clean:
	rm -f $(TESTS)
