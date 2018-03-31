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

DISTCHECK_CONFIGURE_FLAGS ?= --enable-gtk-doc --enable-gtk-doc-pdf --disable-gcc-warnings

SUBDIRS =

if !HAVE_LIBUNISTRING
SUBDIRS += unistring
endif

SUBDIRS += gl lib src examples tests fuzz po
ACLOCAL_AMFLAGS = -I m4 -I unistring/m4
EXTRA_DIST = m4/gnulib-cache.m4

if ENABLE_DOC
SUBDIRS += doc
endif

EXTRA_DIST += cfg.mk maint.mk CONTRIBUTING.md README.md COPYING COPYING.LESSERv3 \
	COPYING.unicode COPYINGv2 AUTHORS NEWS ChangeLog INSTALL

check-valgrind:
	$(MAKE) check LOG_COMPILER="valgrind --error-exitcode=301 --leak-check=yes --show-reachable=yes --track-origins=yes --suppressions=suppressions.valgrind"

clean-local:
	rm -rf */*.gc?? */*/*.gc??

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libidn2.pc

@CODE_COVERAGE_RULES@

local-code-coverage-output: code-coverage-capture
	@cat libidn2-$(VERSION)-coverage/index.html|grep headerCovTableEntryHi|head -1|sed 's/^.*>\([0-9]\+\.[0-9]\+\s*%\)<.*$$/ coverage lines: \1/' || true

ABI_TMPDIR="headers.abi.tmp"
ABI_TMPCLONEDIR="libidn2-prev-abi.tmp"
ABI_TMPFILE1="abi-temp-cur.xml"
ABI_TMPFILE2="abi-temp-prev.xml"
ABIREF := $(shell git for-each-ref --sort=taggerdate --format '%(refname)' refs/tags|tail -1)
ABIVER := $(shell git for-each-ref --sort=taggerdate --format '%(refname)' refs/tags|tail -1|cut -d '/' -f 3|sed -e 's/libidn2-//' -e 's/_/./g')
prev-tag-abi.stamp:
	@rm -rf $(ABI_TMPCLONEDIR)
	@git clone -l . $(ABI_TMPCLONEDIR)
	@echo "Creating ABI for $(ABIVER)"
	cd $(ABI_TMPCLONEDIR) && \
	  git checkout $(ABIREF) && git submodule update --init && \
	  sh bootstrap && CFLAGS="-g -Og" ./configure --disable-doc && \
	  $(MAKE) -j$$(nproc) -C unistring && $(MAKE) -j$$(nproc) -C gl && $(MAKE) -j$$(nproc) -C lib
	touch $@

# Checks the ABI stability between current git version and the previous tagged release.
abi-check: prev-tag-abi.stamp
	@rm -f $(ABI_TMPFILE1) $(ABI_TMPFILE2)
	@echo "Checking libidn2 ABI"
	@echo "<version>$(VERSION)</version>" >$(ABI_TMPFILE1)
	@echo "<headers>$(srcdir)/lib/idn2.h" >>$(ABI_TMPFILE1)
	@echo "$(builddir)/lib/idn2.h</headers>" >>$(ABI_TMPFILE1)
	@echo "<libs>$(builddir)/lib/.libs</libs>" >>$(ABI_TMPFILE1)
	@echo "<version>$(ABIVER)</version>" >$(ABI_TMPFILE2)
	@echo "<headers>$(builddir)/$(ABI_TMPCLONEDIR)/lib/idn2.h" >>$(ABI_TMPFILE2)
	@echo "$(builddir)/$(ABI_TMPCLONEDIR)/lib/idn2.h</headers>" >>$(ABI_TMPFILE2)
	@echo "<libs>$(builddir)/$(ABI_TMPCLONEDIR)/lib/.libs</libs>" >>$(ABI_TMPFILE2)
	PATH="/sbin$(PATH_SEPARATOR)$$PATH" \
	  abi-compliance-checker -abi -lib libidn2 -old $(ABI_TMPFILE2) -new $(ABI_TMPFILE1)
	@rm -f $(ABI_TMPFILE1) $(ABI_TMPFILE2)

# Dumps the current library ABI using abi-dump in the current directory
abi-dump:
	$(MAKE) -C gl
	$(MAKE) -C lib
	@rm -rf $(ABI_TMPDIR)
	@mkdir -p $(ABI_TMPDIR)
	@cp lib/idn2.h $(ABI_TMPDIR)
	@abi-dumper lib/.libs/libidn2.so -o "./ABI-$(VERSION)-$$(uname -m).dump" -public-headers $(ABI_TMPDIR)
	@rm -rf $(ABI_TMPDIR)

dist-hook:
	rm -f ChangeLog
	$(MAKE) ChangeLog

.PHONY: abi-dump abi-check

LCOV_INFO=libidn2.info
fuzz-coverage: clean
	$(MAKE) -C gl CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	$(MAKE) -C unistring CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	$(MAKE) -C lib CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	$(MAKE) -C fuzz check CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	lcov --capture --initial --directory lib --directory fuzz --output-file $(LCOV_INFO)
	lcov --capture --directory lib --directory fuzz --output-file $(LCOV_INFO)
#	lcov --remove $(LCOV_INFO) '*/test_linking.c' '*/css_tokenizer.lex' '*/<stdout>' -o $(LCOV_INFO)
	genhtml --prefix . --ignore-errors source $(LCOV_INFO) --legend --title "fuzz coverage" --output-directory=lcov
	@echo
	@echo "You can now view the coverage report with 'xdg-open lcov/index.html'"
