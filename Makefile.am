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

SUBDIRS =

if !HAVE_LIBUNISTRING
SUBDIRS += unistring
endif

SUBDIRS += gl lib src examples tests po
ACLOCAL_AMFLAGS = -I m4 -I unistring/m4
EXTRA_DIST = m4/gnulib-cache.m4

if ENABLE_DOC
SUBDIRS += doc
endif

EXTRA_DIST += cfg.mk maint.mk CONTRIBUTING.md README.md COPYING COPYING.LESSERv3 \
	COPYING.unicode COPYINGv2 AUTHORS NEWS ChangeLog INSTALL

check-valgrind:
	TESTS_ENVIRONMENT="valgrind --error-exitcode=301 --leak-check=yes --show-reachable=yes --track-origins=yes" $(MAKE) check

clean-local:
	rm -rf */*.gc?? */*/*.gc??

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libidn2.pc

@CODE_COVERAGE_RULES@

local-code-coverage-output: code-coverage-capture
	@cat libidn2-$(VERSION)-coverage/index.html|grep headerCovTableEntryHi|head -1|sed 's/^.*>\([0-9]\+\.[0-9]\+\s*%\)<.*$$/ coverage lines: \1/' || true

TMPDIR="headers.abi.tmp"
TMPFILE="abi-temp.xml"
abi-check: lib/idn2.h lib/libidn2.la
	@rm -f $(TMPFILE)
	@echo "Checking libidn2 ABI"
	@echo "<version>$(VERSION)</version>" >$(TMPFILE)
	@echo "<headers>$(srcdir)/lib/idn2.h" >>$(TMPFILE)
	@echo "$(builddir)/lib/idn2.h</headers>" >>$(TMPFILE)
	@echo "<libs>$(builddir)/lib/.libs</libs>" >>$(TMPFILE)
	for i in 0.16;do \
	test ! -f "$(srcdir)/devel/ABI-$$i-$$(uname -m).dump" || \
		abi-compliance-checker -abi -lib libidn2 -old "$(srcdir)/devel/ABI-$$i-$$(uname -m).dump" -new $(TMPFILE); \
	done
	@rm -f $(TMPFILE)

abi-dump: lib/idn2.h lib/libidn2.la
	@rm -rf $(TMPDIR)
	@mkdir -p $(TMPDIR)
	@mkdir -p devel
	@cp lib/idn2.h $(TMPDIR)
	@abi-dumper lib/.libs/libidn2.so -o "./devel/ABI-$(VERSION)-$$(uname -m).dump" -public-headers $(TMPDIR)
	@rm -rf $(TMPDIR)

dist-hook: abi-check
	rm -f ChangeLog
	make ChangeLog

.PHONY: abi-dump abi-check
