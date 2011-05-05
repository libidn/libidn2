# Copyright (C) 2011 Simon Josefsson

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

CFGFLAGS ?= --enable-gtk-doc --enable-gcc-warnings

ifeq ($(.DEFAULT_GOAL),abort-due-to-no-makefile)
.DEFAULT_GOAL := buildit
endif

local-checks-to-skip += sc_unmarked_diagnostics sc_bindtextdomain # Re-add when we have translation
local-checks-to-skip += sc_immutable_NEWS
local-checks-to-skip += sc_prohibit_strcmp
local-checks-to-skip += sc_copyright_check

# Ignore gnulib files.
VC_LIST_ALWAYS_EXCLUDE_REGEX = ^(maint.mk|src/gl/.*|gl/.*|m4/.*)$$

# Explicit syntax-check exceptions.
exclude_file_name_regexp--sc_program_name = ^(tests|examples)/.*\.c$$
exclude_file_name_regexp--sc_prohibit_empty_lines_at_EOF = ^doc/reference/version.xml.in$$
exclude_file_name_regexp--sc_trailing_blank = ^(tests/IdnaTest.(txt|inc))|(doc/gdoc)$$
exclude_file_name_regexp--sc_require_config_h = ^examples/.*\.c$$
exclude_file_name_regexp--sc_require_config_h_first = ^examples/.*\.c$$

update-copyright-env = UPDATE_COPYRIGHT_HOLDER="Simon Josefsson"

INDENT_SOURCES = \
	bidi.c \
	bidi.h \
	context.c \
	context.h \
	data.h \
	error.c \
	free.c \
	idn2.h.in \
	idna.c \
	idna.h \
	lookup.c \
	punycode.h \
	register.c \
	src/blurbs.h \
	src/idn2.c \
	tables.c \
	tables.h \
	version.c

doc/Makefile.gdoc:
	printf "gdoc_MANS =\ngdoc_TEXINFOS =\n" > doc/Makefile.gdoc

buildit: doc/Makefile.gdoc
	test -f configure || autoreconf --force --install
	test -f Makefile || ./configure $(CFGFLAGS)
	make

glimport:
	gnulib-tool --add-import

htmldir = ../www-$(PACKAGE)

# Coverage

coverage-my:
	ln -s . gl/uniconv/uniconv
	ln -s . gl/unictype/unictype
	ln -s . gl/uninorm/uninorm
	ln -s . gl/unistr/unistr
	$(MAKE) coverage

coverage-web:
	rm -fv `find $(htmldir)/coverage -type f`
	cp -rv $(COVERAGE_OUT)/* $(htmldir)/coverage/

coverage-web-upload:
	cd $(htmldir) && \
		git commit -m "Update." coverage

# Clang analyzis.
clang:
	make clean
	scan-build ./configure
	rm -rf scan.tmp
	scan-build -o scan.tmp make
clang-web:
	rm -fv `find $(htmldir)/clang-analyzer -type f | grep -v CVS`
	cp -rv scan.tmp/*/* $(htmldir)/clang-analyzer/
clang-web-upload:
	cd $(htmldir) && \
		cvs add clang-analyzer/*.html || true && \
		cvs commit -m "Update." clang-analyzer

# Release

ChangeLog:
	git2cl > ChangeLog

release: syntax-check prepare upload

tag = $(PACKAGE)-$(VERSION)
prepare:
	! git tag -l $(tag) | grep $(PACKAGE) > /dev/null
	$(MAKE) ChangeLog distcheck
	gpg -b $(distdir).tar.gz
	gpg --verify $(distdir).tar.gz.sig
	git tag -u b565716f! -m $(VERSION) $(tag)
	git push
	git push --tags

upload:
	cp $(distdir).tar.gz $(distdir).tar.gz.sig ../releases/$(PACKAGE)/
