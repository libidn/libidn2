# Copyright (C) 2011-2017 Simon Josefsson

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

AM_CPPFLAGS =

AM_CPPFLAGS += -DIDN2_BUILDING -DSRCDIR=\"$(srcdir)\"
AM_CPPFLAGS += -I$(top_builddir)/gl -I$(top_srcdir)/gl
AM_CFLAGS = $(WARN_CFLAGS)
AM_CFLAGS += $(CFLAG_VISIBILITY) $(CODE_COVERAGE_CFLAGS)

if !HAVE_LIBUNISTRING
AM_CPPFLAGS += -I$(top_srcdir)/unistring/ -I$(top_builddir)/unistring/
endif

lib_LTLIBRARIES = libidn2.la

include_HEADERS = idn2.h

libidn2_la_SOURCES = idn2.map idn2.h
libidn2_la_SOURCES += idna.h idna.c
libidn2_la_SOURCES += lookup.c decode.c
libidn2_la_SOURCES += register.c
libidn2_la_SOURCES += bidi.h bidi.c
libidn2_la_SOURCES += version.c
libidn2_la_SOURCES += error.c
libidn2_la_SOURCES += punycode.h puny_encode.c puny_decode.c
libidn2_la_SOURCES += free.c
libidn2_la_SOURCES += data.h data.c
libidn2_la_SOURCES += tr46map.h tr46map.c
libidn2_la_SOURCES += tables.h tables.c
libidn2_la_SOURCES += context.h context.c
libidn2_la_LIBADD = $(LTLIBICONV) $(LTLIBINTL) $(LTLIBUNISTRING) ../gl/libgnu.la

if !HAVE_LIBUNISTRING
libidn2_la_LIBADD += ../unistring/libunistring.la
endif

libidn2_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -no-undefined $(CODE_COVERAGE_LDFLAGS)

IDNA_TABLE = idna-tables-properties.csv
IANA_URL = https://www.iana.org/assignments/idna-tables-11.0.0/idna-tables-properties.csv
IDNA_TABLE_SHA1 = 6d224090e6b1d3bef6632e932d5f38fd7fb2356a

TR46MAP = IdnaMappingTable.txt
TR46MAP_URL = http://www.unicode.org/Public/idna/11.0.0/IdnaMappingTable.txt
TR46MAP_SHA1 = 9892c962ce97db7b7151427df675bd1ebd0eeb99

NFCQC = DerivedNormalizationProps.txt
NFCQC_URL = http://www.unicode.org/Public/11.0.0/ucd/DerivedNormalizationProps.txt
NFCQC_SHA1 = 4b1620b7a54ed761720345b5367932d5a029a279

BUILT_SOURCES = data.c tr46map_data.c
DISTCLEANFILES = $(BUILT_SOURCES)
CLEANFILES = gendata$(BUILD_EXEEXT) gentr46map$(BUILD_EXEEXT)
MAINTAINERCLEANFILES = $(IDNA_TABLE) $(TR46MAP) $(NFCQC)
EXTRA_DIST = $(IDNA_TABLE) $(TR46MAP) $(NFCQC) data.c gendata.c tr46map_data.c gentr46map.c

# Note: We do not want to list any gen* as a dep of *data.c because it will
# cause it to be regenerated for every build.  We only need that when the real
# source text files are updated.
gendata$(BUILD_EXEEXT): gendata.c
	$(CC_FOR_BUILD) $(AM_CPPFLAGS) $(CFLAGS_FOR_BUILD) $< -o $@
data.c: $(srcdir)/gendata.c $(IDNA_TABLE)
	$(MAKE) gendata$(BUILD_EXEEXT)
	$(builddir)/gendata$(BUILD_EXEEXT) < $(IDNA_TABLE) > $@.new
	mv $@.new $@

gentr46map$(BUILD_EXEEXT): gentr46map.c
	$(CC_FOR_BUILD) $(AM_CPPFLAGS) $(CFLAGS_FOR_BUILD) $< -o $@
tr46map_data.c: $(srcdir)/gentr46map.c $(TR46MAP) $(NFCQC)
	$(MAKE) gentr46map$(BUILD_EXEEXT)
	$(builddir)/gentr46map$(BUILD_EXEEXT) > $@.new
	mv $@.new $@

$(IDNA_TABLE):
	if ! echo "$(IDNA_TABLE_SHA1) $(IDNA_TABLE)" | sha1sum -c -; then \
	  rm -f $(IDNA_TABLE); \
	  wget -O$(IDNA_TABLE) $(IANA_URL); \
	  echo "$(IDNA_TABLE_SHA1) $(IDNA_TABLE)" | sha1sum -c -; \
	fi

$(TR46MAP):
	if ! echo "$(TR46MAP_SHA1) $(TR46MAP)" | sha1sum -c -; then \
	  rm -f $(TR46MAP); \
	  wget $(TR46MAP_URL); \
	  echo "$(TR46MAP_SHA1) $(TR46MAP)" | sha1sum -c -; \
	fi

$(NFCQC):
	if ! echo "$(NFCQC_SHA1) $(NFCQC)" | sha1sum -c -; then \
	  rm -f $(NFCQC); \
	  wget $(NFCQC_URL); \
	  echo "$(NFCQC_SHA1) $(NFCQC)" | sha1sum -c -; \
	fi

if HAVE_LD_VERSION_SCRIPT
libidn2_la_LDFLAGS += -Wl,--version-script=$(srcdir)/idn2.map
else
libidn2_la_LDFLAGS += -export-symbols-regex '^idn2_.*'
endif
