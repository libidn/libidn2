# Copyright (C) 2011 Simon Josefsson

# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2.1 of the
# License, or (at your option) any later version.

# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301 USA

SUBDIRS = lib

ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -DLIBIDNA_BUILDING
AM_CPPFLAGS += -I$(srcdir)/lib -I$(builddir)/lib

lib_LTLIBRARIES = libidna.la

libidna_includedir=$(includedir)/libidna
libidna_include_HEADERS = libidna.h

libidna_la_SOURCES = libidna.map libidna.h
libidna_la_SOURCES += version.c
libidna_la_SOURCES += punycode.c
libidna_la_LIBADD = lib/libgnu.la
libidna_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -no-undefined

if HAVE_LD_VERSION_SCRIPT
libidna_la_LDFLAGS += -Wl,--version-script=$(srcdir)/libidna.map
else
libidna_la_LDFLAGS += -export-symbols-regex '^idna_.*'
endif

LDADD = libidna.la

TESTS = test-punycode
check_PROGRAMS = test-punycode
