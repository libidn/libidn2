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

DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

SUBDIRS = lib . src doc examples tests po
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

EXTRA_DIST += CONTRIBUTING

AM_CPPFLAGS = -DIDN2_BUILDING -DSRCDIR=\"$(srcdir)\"
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

IDNA_TABLE = $(builddir)/idna-tables-6.3.0.txt
IANA_URL = https://ftp.iana.org/assignments/idna-tables-6.3.0/$(IDNA_TABLE)
TR46MAP = IdnaMappingTable.txt
TR46MAP_URL = http://www.unicode.org/Public/idna/6.3.0/IdnaMappingTable.txt
NFCQC = DerivedNormalizationProps.txt
NFCQC_URL = http://www.unicode.org/Public/6.3.0/ucd/DerivedNormalizationProps.txt

BUILT_SOURCES = data.c tr46map_data.c
DISTCLEANFILES =  tr46map_data.c
MAINTAINERCLEANFILES = $(IDNA_TABLE) $(TR46MAP) $(NFCQC)
EXTRA_DIST += gen-tables-from-iana.pl $(IDNA_TABLE) $(TR46MAP) $(NFCQC) tr46map_data.c data.c

data.c: $(srcdir)/gen-tables-from-iana.pl $(IDNA_TABLE)
	cat $(IDNA_TABLE) | $(srcdir)/gen-tables-from-iana.pl > $@.new
	mv $@.new $@

noinst_PROGRAMS = gentr46map
gentr46map_LDADD = $(LTLIBUNISTRING)

tr46map_data.c: gentr46map.c gentr46map$(EXEEXT) $(TR46MAP) $(NFCQC)
	$(builddir)/gentr46map$(EXEEXT) > $@.new
	mv $@.new $@

$(IDNA_TABLE):
	if ! echo "4ebaf0c72061474d20078897d254768d894507de $(IDNA_TABLE)" | sha1sum -c -; then \
	  rm -f $(IDNA_TABLE); \
	  wget -O$(IDNA_TABLE) $(IANA_URL); \
	  echo "4ebaf0c72061474d20078897d254768d894507de $(IDNA_TABLE)" | sha1sum -c -; \
	fi

$(TR46MAP):
	if ! echo "e852821860396e2b500e2c1661cc9fb14e1c2738 $(TR46MAP)" | sha1sum -c -; then \
	  rm -f $(TR46MAP); \
	  wget $(TR46MAP_URL); \
	  echo "e852821860396e2b500e2c1661cc9fb14e1c2738 $(TR46MAP)" | sha1sum -c -; \
	fi

$(NFCQC):
	if ! echo "8f220108eebacb130fe4b36469c25d6d2e613a97 $(NFCQC)" | sha1sum -c -; then \
	  rm -f $(NFCQC); \
	  wget $(NFCQC_URL); \
	  echo "8f220108eebacb130fe4b36469c25d6d2e613a97 $(NFCQC)" | sha1sum -c -; \
	fi

if HAVE_LD_VERSION_SCRIPT
libidn2_la_LDFLAGS += -Wl,--version-script=$(srcdir)/idn2.map
else
libidn2_la_LDFLAGS += -export-symbols-regex '^idn2_.*|_idn2_punycode_..code'
endif

check-valgrind:
	TESTS_ENVIRONMENT="valgrind --error-exitcode=301 --leak-check=yes --show-reachable=yes --track-origins=yes" $(MAKE) check

LCOV_INFO=libidn2.info
check-coverage:
	CFLAGS=$$CFLAGS" --coverage -O0" LDFLAGS=$$LDFLAGS" --coverage" ./configure;
	$(MAKE) clean && $(MAKE)
	lcov --capture --initial --directory . --output-file $(LCOV_INFO)
	$(MAKE) check
	lcov --capture --directory . --output-file $(LCOV_INFO)
	lcov --remove $(LCOV_INFO) 'lib/*' 'tests/*' -o $(LCOV_INFO)
	genhtml --prefix . $(LCOV_INFO) --legend --title "libidn2" --output-directory=lcov
# now you can view lcov/index.html with your favorite browser

clean-local:
	rm -rf */*.gc?? */*/*.gc?? $(LCOV_INFO) lcov
