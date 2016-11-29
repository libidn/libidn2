# Copyright (C) 2011-2016 Simon Josefsson

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

SUBDIRS = lib . src doc examples tests po
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

AM_CPPFLAGS = -DIDN2_BUILDING
AM_CPPFLAGS += -I$(top_builddir)/lib -I$(top_srcdir)/lib
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
libidn2_la_SOURCES += tr46map.h tr46map.c
libidn2_la_SOURCES += tables.h tables.c
libidn2_la_SOURCES += context.h context.c
libidn2_la_LIBADD = $(LTLIBICONV) $(LTLIBINTL) $(LTLIBUNISTRING) lib/libgnu.la
libidn2_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -no-undefined

BUILT_SOURCES = data.c tr46map.c
EXTRA_DIST += gen-tables-from-iana.pl gentr46map.c
IDNA_TABLE = idna-tables-6.3.0.txt
IANA_URL = https://ftp.iana.org/assignments/idna-tables-6.3.0/$(IDNA_TABLE)
TR46MAP = IdnaMappingTable.txt
TR46MAP_URL = http://www.unicode.org/Public/idna/6.3.0/IdnaMappingTable.txt
NFCQC = DerivedNormalizationProps.txt
NFCQC_URL = http://www.unicode.org/Public/6.3.0/ucd/DerivedNormalizationProps.txt

data.c: $(srcdir)/gen-tables-from-iana.pl $(IDNA_TABLE)
	cat $(IDNA_TABLE) | $(srcdir)/gen-tables-from-iana.pl

$(IDNA_TABLE):
	rm -f $(IDNA_TABLE)
	wget $(IANA_URL)

$(TR46MAP):
	rm -f $(TR46MAP)
	wget $(TR46MAP_URL)

$(NFCQC):
	rm -f $(NFCQC)
	wget $(NFCQC_URL)

tr46map.c: $(srcdir)/gentr46map $(TR46MAP) $(NFCQC)
	$(srcdir)/gentr46map >tr46map.c

gentr46map: $(srcdir)/gentr46map.c
	$(CC) -Wall gentr46map.c -o gentr46map

TLD_URL = https://www.iana.org/domains/root/db/
tv.c: $(srcdir)/gen-idn-tld-tv.pl
	(cat tld-cache || wget -O - $(TLD_URL)) | $(srcdir)/gen-idn-tld-tv.pl

if HAVE_LD_VERSION_SCRIPT
libidn2_la_LDFLAGS += -Wl,--version-script=$(srcdir)/idn2.map
else
libidn2_la_LDFLAGS += -export-symbols-regex '^idn2_.*|_idn2_punycode_..code'
endif

backup:
	rsync -av . jas@yxa-vi.extundo.com:libidn2
