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

# Re-add when we have translation
local-checks-to-skip += sc_unmarked_diagnostics sc_bindtextdomain
local-checks-to-skip += sc_immutable_NEWS
local-checks-to-skip += sc_prohibit_strcmp

# Ignore gnulib files.
VC_LIST_ALWAYS_EXCLUDE_REGEX = ^(src/gl|gl|m4)/.*$

# Explicit syntax-check exceptions.
exclude_file_name_regexp--sc_program_name = ^tests/.*\.c$$
exclude_file_name_regexp--sc_prohibit_empty_lines_at_EOF = ^doc/reference/version.xml.in$$
exclude_file_name_regexp--sc_space_tab = ^maint.mk$$
exclude_file_name_regexp--sc_trailing_blank = ^tests/IdnaTest.(txt|inc)$$

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

buildit:
	test -f configure || autoreconf --force --install
	test -f Makefile || ./configure $(CFGFLAGS)
	make

glimport:
	gnulib-tool --add-import

htmldir = ../www-$(PACKAGE)

my-coverage:
	ln -s . gl/uniconv/uniconv
	ln -s . gl/unictype/unictype
	ln -s . gl/uninorm/uninorm
	ln -s . gl/unistr/unistr
	$(MAKE) coverage

web-coverage:
	rm -fv `find $(htmldir)/coverage -type f`
	cp -rv $(COVERAGE_OUT)/* $(htmldir)/coverage/

upload-web-coverage:
	cd $(htmldir) && \
		git commit -m "Update." coverage

ChangeLog:
	git2cl > ChangeLog

release: prepare upload

tag = $(PACKAGE)-$(VERSION)
prepare:
	! git tag -l $(tag) | grep $(PACKAGE) > /dev/null
	$(MAKE) ChangeLog distcheck
	gpg -b $(distdir).tar.gz
	gpg --verify $(distdir).tar.gz.sig
	git tag -u b565716f! -m $(VERSION) $(tag)

upload:
	git push
	git push --tags
	cp $(distdir).tar.gz $(distdir).tar.gz.sig ../releases/$(PACKAGE)/
