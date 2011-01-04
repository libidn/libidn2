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

# Gnulib
SUBDIRS = lib
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

AM_CPPFLAGS = -DLIBIDNA_BUILDING
AM_CPPFLAGS += -I$(srcdir)/lib -I$(builddir)/lib

lib_LTLIBRARIES = libidna.la

libidna_includedir=$(includedir)/libidna
libidna_include_HEADERS = libidna.h

libidna_la_SOURCES = libidna.map libidna.h
libidna_la_SOURCES += version.c
libidna_la_SOURCES += punycode.c
libidna_la_SOURCES += tables.c
libidna_la_SOURCES += nfc.c
libidna_la_SOURCES += free.c
libidna_la_SOURCES += idna.c
libidna_la_LIBADD = lib/libgnu.la
libidna_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -no-undefined

BUILT_SOURCES = tables.c
EXTRA_DIST += gen-tables-from-rfc5892.pl gen-tables-from-iana.pl
IANA_URL = http://www.iana.org/assignments/idnabis-tables/idnabis-tables.txt
RFC5892_URL = http://www.ietf.org/rfc/rfc5892.txt
tables.c: $(srcdir)/gen-tables-from-rfc5892.pl $(srcdir)/gen-tables-from-iana.pl
	wget -O - -q $(RFC5892_URL) | $(srcdir)/gen-tables-from-rfc5892.pl
	mv tables.c tmp.c
	wget -O - -q $(IANA_URL) | $(srcdir)/gen-tables-from-iana.pl
	diff -u tables.c tmp.c
	rm tmp.c

if HAVE_LD_VERSION_SCRIPT
libidna_la_LDFLAGS += -Wl,--version-script=$(srcdir)/libidna.map
else
libidna_la_LDFLAGS += -export-symbols-regex '^idna_.*'
endif

LDADD = libidna.la

TESTS = test-punycode test-nfc test-idna
check_PROGRAMS = test-punycode test-nfc test-idna
