# Copyright (C) 2011-2025 Simon Josefsson

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

SUBDIRS = gl unistring lib src examples fuzz po

if ENABLE_DOC
SUBDIRS += doc
endif

SUBDIRS += tests

EXTRA_DIST = cfg.mk maint.mk CONTRIBUTING.md DEPENDENCIES.md README.md
EXTRA_DIST += COPYING COPYING.LESSERv3 COPYING.unicode COPYINGv2

check-valgrind:
	$(MAKE) check LOG_COMPILER="valgrind --error-exitcode=301 --leak-check=yes --show-reachable=yes --track-origins=yes --suppressions=suppressions.valgrind"

clean-local:
	rm -rf */*.gc?? */*/*.gc??

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libidn2.pc

include $(top_srcdir)/aminclude_static.am

local-code-coverage-output: code-coverage-capture
	@cat $(PACKAGE_NAME)-$(VERSION)-coverage/index.html|grep headerCovTableEntryHi|head -1|sed 's/^.*>\([0-9]\+\.[0-9]\+\s*%\)<.*$$/ coverage lines: \1/' || true

ABIDW_COMMON = --no-show-locs --no-corpus-path
LIBIDN2_ABI_LAST_FILE = "$(top_srcdir)/contrib/libidn2-latest-$$(uname -m).abi"
ABIGNORE_FILE = "$(top_srcdir)/contrib/libidn2.abignore"
abi-dump-versioned: lib/libidn2.la
	@echo "*************************************************"
	@echo "Generating versioned ABI files of current libidn2"
	@echo "*************************************************"
	@abidw lib/.libs/libidn2.so $(ABIDW_COMMON) --suppressions $(ABIGNORE_FILE) --out-file "$(srcdir)/contrib/libidn2-$(VERSION)-$$(uname -m).abi"

abi-dump-latest: lib/libidn2.la
	@echo "***************************************"
	@echo "Generating ABI files of current libidn2"
	@echo "***************************************"
	@abidw lib/.libs/libidn2.so $(ABIDW_COMMON) --suppressions $(ABIGNORE_FILE) --out-file $(LIBIDN2_ABI_LAST_FILE)
	@rm -f "./contrib/libidn2-latest-$$(uname -m).tmp"

abi-check-latest: lib/libidn2.la
	@echo "Checking whether the latest ABI dump matches"
	@abidiff --suppressions $(ABIGNORE_FILE) lib/.libs/libidn2.so $(LIBIDN2_ABI_LAST_FILE); if test $$? != 0;then \
		echo "*****************************************************"; \
		echo "libidn2 ABI has changed; use 'make abi-dump-latest'  "; \
		echo "and use 'git diff' to check correctness before commit"; \
		echo "*****************************************************"; \
		exit 1; \
	fi
	@echo "********************************"
	@echo "Current release matches ABI dump"
	@echo "********************************"

# Checks the ABI stability between current git version and the previous tagged release.
ABICHECK_COMMON = --no-added-syms
.PHONY: abi-check
abi-check: lib/libidn2.la
	@for file in $$(eval echo $(srcdir)/contrib/libidn2-*-$$(uname -m).abi);do \
		echo "Comparing libidn2 with $$file"; \
		abidiff $${file} lib/.libs/libidn2.so --suppressions $(ABIGNORE_FILE) $(ABICHECK_COMMON) --hd2 "$(srcdir)/lib/idn2.h"; \
		if test $$? != 0;then \
			echo "****************************************************************************"; \
			echo "ABI check failed; If intentional add suppression in contrib/libidn2.abignore"; \
			echo "****************************************************************************"; \
			exit 1; \
		fi; \
	done
	@echo "********************"
	@echo "ABI checks completed"
	@echo "********************"

# version-stamp
EXTRA_DIST += $(top_srcdir)/.version
BUILT_SOURCES = $(top_srcdir)/.version

# git-version-gen
dist-hook: dist-tarball-version
.PHONY: dist-tarball-version
dist-tarball-version:
	echo '$(VERSION)' > $(distdir)/.tarball-version

dist-hook: maybe-abi-check
.PHONY: maybe-abi-check
maybe-abi-check:
	if command -v abidiff > /dev/null && \
		test -d "$(top_srcdir)/contrib"; then \
		$(MAKE) -C $(top_builddir) abi-check-latest; \
	fi

dist-hook: po-CreationDate-to-mtime-NEWS
.PHONY: po-CreationDate-to-mtime-NEWS
po-CreationDate-to-mtime-NEWS: mtime-NEWS-to-git-HEAD
	$(AM_V_GEN)for p in $(distdir)/po/*.po $(distdir)/po/$(PACKAGE).pot; do \
	  if test -f "$$p"; then \
	    $(SED) -e 's,POT-Creation-Date: .*\\n",POT-Creation-Date: '"$$(env LC_ALL=C TZ=UTC0 stat --format=%y $(srcdir)/NEWS | cut -c1-16,31-)"'\\n",' < $$p > $$p.tmp && \
	    if cmp $$p $$p.tmp > /dev/null; then \
	      rm -f $$p.tmp; \
	    else \
	      mv $$p.tmp $$p; \
	    fi \
	  fi \
	done

dist-hook: srcdist
.PHONY: srcdist
srcdist:
	$(AM_V_GEN)if test -e $(srcdir)/.git \
			&& command -v git > /dev/null; then \
	 cd $(srcdir) && \
	   git archive --prefix=$(PACKAGE)-v$(VERSION)/ \
	       -o $(abs_builddir)/$(PACKAGE)-v$(VERSION)-src.tar.gz HEAD; \
	fi

dist-hook: mtime-NEWS-to-git-HEAD
.PHONY: mtime-NEWS-to-git-HEAD
mtime-NEWS-to-git-HEAD:
	$(AM_V_GEN)if test -e $(srcdir)/.git \
			&& command -v git > /dev/null; then \
		touch -m -t "$$(git log -1 --format=%cd --date=format-local:%Y%m%d%H%M.%S)" $(srcdir)/NEWS; \
	fi

dist-hook: texi-stamps-to-mtime-NEWS
.PHONY: texi-stamps-to-mtime-NEWS
texi-stamps-to-mtime-NEWS: mtime-NEWS-to-git-HEAD
	$(AM_V_GEN)touch -m -r $(srcdir)/NEWS $(srcdir)/doc/$(PACKAGE).texi

dist-hook: gen-ChangeLog
.PHONY: gen-ChangeLog
gen-ChangeLog:
	$(AM_V_GEN)if test -e $(srcdir)/.git; then			\
	  LC_ALL=en_US.UTF-8 TZ=UTC0					\
	    $(top_srcdir)/build-aux/gitlog-to-changelog			\
	      --srcdir=$(srcdir) --					\
	      v$(PREV_VERSION)~.. > $(distdir)/cl-t &&			\
	    { printf '\n\nSee the source repo for older entries\n'	\
	      >> $(distdir)/cl-t &&					\
	      rm -f $(distdir)/ChangeLog &&				\
	      mv $(distdir)/cl-t $(distdir)/ChangeLog; }		\
	fi

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
