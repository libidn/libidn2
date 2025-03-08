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

manual_title = Internationalized Domain Names Library

old_NEWS_hash = 0202af5b41f5df95eabda4582471da31

guix = $(shell command -v guix > /dev/null && echo ,guix)
bootstrap-tools = gnulib,autoconf,automake,libtoolize,make,makeinfo,help2man,gperf,gengetopt,gtkdocize,tar,gzip$(guix)

upload_dest_dir_ = libidn

GNUPLOADFLAGS = --symlink-regex

# make syntax-check
local-checks-to-skip += sc_bindtextdomain
local-checks-to-skip += sc_prohibit_strcmp
local-checks-to-skip += sc_prohibit_gnu_make_extensions
VC_LIST_ALWAYS_EXCLUDE_REGEX = ^(fuzz/.*.(in|repro)/.*)$$
exclude_file_name_regexp--sc_program_name = ^(tests|examples)/.*\.c$$
exclude_file_name_regexp--sc_prohibit_empty_lines_at_EOF = ^doc/reference/version.xml.in$$
exclude_file_name_regexp--sc_trailing_blank = ^(m4/pkg.m4|gl/build-aux/gnu-web-doc-update.diff|gl/top/README-release.diff|tests/IdnaTest.(txt|inc))|(doc/gdoc)|(unistring/lib/uni.*diff)$$
exclude_file_name_regexp--sc_require_config_h = ^examples/.*\.c|^fuzz/main.c$$
exclude_file_name_regexp--sc_require_config_h_first = ^examples/.*\.c|^fuzz/main.c$$
exclude_file_name_regexp--sc_GPL_version = ^m4/ax_code_coverage.m4|m4/pkg.m4|COPYINGv2|lib/.*.(c|h|h.in)$$
exclude_file_name_regexp--sc_prohibit_atoi_atof = ^lib/gentr46map\.c$$
exclude_file_name_regexp--sc_makefile_at_at_check = ^Makefile.am|src/Makefile\.am|tests/Makefile.am$$
exclude_file_name_regexp--sc_prohibit_empty_lines_at_EOF = ^lib/IdnaMappingTable.txt|doc/reference/version.xml.in$$
exclude_file_name_regexp--sc_prohibit_undesirable_word_seq = ^lib/idna-tables-properties.csv$$
exclude_file_name_regexp--sc_fsf_postal = ^m4/pkg.m4$$
exclude_file_name_regexp--sc_prohibit_have_config_h = ^tests/.*.c$$
exclude_file_name_regexp--sc_unportable_grep_q = ^gl/top/README-release.diff$$

TAR_OPTIONS += --mode=go+u,go-w --mtime=$(abs_top_srcdir)/NEWS

announce_gen_args = --cksum-checksums
url_dir_list = https://ftp.gnu.org/gnu/libidn

DIST_ARCHIVES += $(shell \
	if test -e $(srcdir)/.git && command -v git > /dev/null; then \
		echo $(PACKAGE)-v$(VERSION)-src.tar.gz; \
	fi)

my-update-copyright:
	make update-copyright update-copyright-env='UPDATE_COPYRIGHT_HOLDER="Tim Ruehsen" UPDATE_COPYRIGHT_USE_INTERVALS=2'
	make update-copyright update-copyright-env='UPDATE_COPYRIGHT_HOLDER="Simon Josefsson" UPDATE_COPYRIGHT_USE_INTERVALS=2'
	perl -pi -e "s/2011-20..  Simon Josefsson/2011-`(date +%Y)`  Simon Josefsson/" lib/version.c
	perl -pi -e "s/2002-20.. Simon Josefsson/2002-`(date +%Y)` Simon Josefsson/" doc/Makefile.am

aximport:
	for f in m4/ax_*.m4; do \
		wget -O $$f "https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=$$f"; \
	done

update-po: refresh-po
	rm -fv po/*.po.in
	for f in `ls po/*.po | grep -v quot.po`; do \
		cp $$f $$f.in; \
	done
	git add po/*.po.in
	git commit po/*.po.in \
		-m "maint: Run 'make update-po' for new translations."

sc_codespell:
	@if `which codespell > /dev/null`; then \
		codespell -L tim,mitre,bu `git -C $(top_srcdir) ls-files | egrep -v '^po/.*\.po\.in|_fuzzer.in|_fuzzer.repro|gnulib|^lib/.*\.(csv|txt)$$'`; \
	fi
