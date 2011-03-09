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

CFGFLAGS ?= --enable-gtk-doc

ifeq ($(.DEFAULT_GOAL),abort-due-to-no-makefile)
.DEFAULT_GOAL := buildit
endif

# Re-add when we have translation
local-checks-to-skip += sc_unmarked_diagnostics sc_bindtextdomain
local-checks-to-skip += sc_immutable_NEWS

# Ignore gnulib files.
VC_LIST_ALWAYS_EXCLUDE_REGEX = ^(lib|m4)/.*$

update-copyright-env = UPDATE_COPYRIGHT_HOLDER="Simon Josefsson"

buildit:
	test -f configure || autoreconf --force --install
	test -f Makefile || ./configure $(CFGFLAGS)
	make

glimport:
	gnulib-tool --add-import

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
