# Copyright (C) 2011-2014 Simon Josefsson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

SUBDIRS = gl . src doc examples tests
ACLOCAL_AMFLAGS = -I m4 -I gl/m4
EXTRA_DIST = gl/m4/gnulib-cache.m4

AM_CPPFLAGS = -DIDN2_BUILDING
AM_CPPFLAGS += -I$(srcdir)/gl -I$(builddir)/gl
AM_CFLAGS = $(WARN_CFLAGS)
AM_CFLAGS += $(CFLAG_VISIBILITY)

lib_LTLIBRARIES = libidn2.la

include_HEADERS = idn2.h

libidn2_la_SOURCES = idn2.map idn2.h
libidn2_la_SOURCES += idna.h idna.c
libidn2_la_SOURCES += lookup.c
libidn2_la_SOURCES += register.c
libidn2_la_SOURCES += bidi.h bidi.c
libidn2_la_SOURCES += version.c
libidn2_la_SOURCES += error.c
libidn2_la_SOURCES += punycode.h punycode.c
libidn2_la_SOURCES += free.c
libidn2_la_SOURCES += data.h data.c
libidn2_la_SOURCES += tables.h tables.c
libidn2_la_SOURCES += context.h context.c
libidn2_la_LIBADD = gl/libgnu.la
libidn2_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -no-undefined

BUILT_SOURCES = data.c
EXTRA_DIST += gen-tables-from-rfc5892.pl gen-tables-from-iana.pl
IANA_URL = ftp://ftp.iana.org/assignments/idna-tables-5.2.0/idna-tables-5.2.0.txt
RFC5892_URL = http://www.ietf.org/rfc/rfc5892.txt
data.c: $(srcdir)/gen-tables-from-rfc5892.pl $(srcdir)/gen-tables-from-iana.pl
	wget -O - $(RFC5892_URL) | $(srcdir)/gen-tables-from-rfc5892.pl
	mv data.c tmp
	wget -O - $(IANA_URL) | $(srcdir)/gen-tables-from-iana.pl
	diff -u tmp data.c
	rm -f tmp

TLD_URL = http://www.iana.org/domains/root/db/
tv.c: $(srcdir)/gen-idn-tld-tv.pl
	(cat tld-cache || wget -O - $(TLD_URL)) | $(srcdir)/gen-idn-tld-tv.pl

if HAVE_LD_VERSION_SCRIPT
libidn2_la_LDFLAGS += -Wl,--version-script=$(srcdir)/idn2.map
else
libidn2_la_LDFLAGS += -export-symbols-regex '^idn2_.*'
endif

backup:
	rsync -av . jas@yxa-vi.extundo.com:libidn2
