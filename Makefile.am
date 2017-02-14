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

SUBDIRS += lib idn2 src doc examples tests po
ACLOCAL_AMFLAGS = -I m4 -I unistring/m4
EXTRA_DIST = m4/gnulib-cache.m4

EXTRA_DIST += CONTRIBUTING

check-valgrind:
	TESTS_ENVIRONMENT="valgrind --error-exitcode=301 --leak-check=yes --show-reachable=yes --track-origins=yes" $(MAKE) check

LCOV_INFO=libidn2.info
check-coverage:
	CFLAGS=$$CFLAGS" --coverage -O0" LDFLAGS=$$LDFLAGS" --coverage" ./configure;
	$(MAKE) clean && $(MAKE)
	lcov --capture --initial --directory idn2/.libs --output-file $(LCOV_INFO)
	$(MAKE) check
	lcov --capture --directory idn2/.libs --output-file $(LCOV_INFO)
	genhtml --prefix . $(LCOV_INFO) --legend --title "libidn2" --output-directory=lcov
# now you can view lcov/index.html with your favorite browser

clean-local:
	rm -rf */*.gc?? */*/*.gc?? $(LCOV_INFO) lcov

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libidn2.pc

TMPDIR="headers.abi.tmp"
TMPFILE="abi-temp.xml"
abi-check: idn2/idn2.h idn2/libidn2.la
	@rm -f $(TMPFILE)
	@echo "Checking libidn2 ABI"
	@echo "<version>$(VERSION)</version>" >$(TMPFILE)
	@echo "<headers>$(srcdir)/idn2/idn2.h" >>$(TMPFILE)
	@echo "$(builddir)/idn2/idn2.h</headers>" >>$(TMPFILE)
	@echo "<libs>$(builddir)/idn2/.libs</libs>" >>$(TMPFILE)
	for i in 0.16;do \
	test ! -f "$(srcdir)/devel/ABI-$$i-$$(uname -m).dump" || \
		abi-compliance-checker -abi -lib libidn2 -old "$(srcdir)/devel/ABI-$$i-$$(uname -m).dump" -new $(TMPFILE); \
	done
	@rm -f $(TMPFILE)

abi-dump: idn2/idn2.h idn2/libidn2.la
	@rm -rf $(TMPDIR)
	@mkdir -p $(TMPDIR)
	@mkdir -p devel
	@cp idn2/idn2.h $(TMPDIR)
	@abi-dumper idn2/.libs/libidn2.so -o "./devel/ABI-$(VERSION)-$$(uname -m).dump" -public-headers $(TMPDIR)
	@rm -rf $(TMPDIR)

dist-hook: abi-check

.PHONY: abi-dump abi-check
