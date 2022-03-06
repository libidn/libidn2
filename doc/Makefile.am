# Copyright (C) 2011-2022 Simon Josefsson

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

SUBDIRS = reference

EXTRA_DIST = gdoc idn2.h2m
BUILT_SOURCES = idn2.1
info_TEXINFOS = libidn2.texi
libidn2_TEXINFOS = libidn2.texi example-tounicode.c example-toascii.c	\
	decode.c lookup.c register.c $(gdoc_TEXINFOS) idn2-help.texi

AM_MAKEINFOHTMLFLAGS = --no-split $(AM_MAKEINFOFLAGS)

decode.c: $(top_srcdir)/examples/decode.c
	tail -n +18 $< > $@.tmp
	mv $@.tmp $@

lookup.c: $(top_srcdir)/examples/lookup.c
	tail -n +18 $< > $@.tmp
	mv $@.tmp $@

register.c: $(top_srcdir)/examples/register.c
	tail -n +18 $< > $@.tmp
	mv $@.tmp $@

example-tounicode.c: $(top_srcdir)/examples/example-tounicode.c
	cp $< $@

example-toascii.c: $(top_srcdir)/examples/example-toascii.c
	cp $< $@

dist_man_MANS = $(gdoc_MANS)
dist_man_MANS += idn2.1

idn2.1: idn2.h2m $(top_srcdir)/src/idn2.c $(top_srcdir)/src/idn2.ggo \
		$(top_srcdir)/configure.ac
	$(HELP2MAN) --include=$(srcdir)/idn2.h2m \
		--output=$@ $(top_builddir)/src/idn2$(EXEEXT)

idn2-help.texi: $(top_srcdir)/src/idn2.c
	$(top_builddir)/src/idn2$(EXEEXT) --help | $(GREP) '^  *-' > tmp
	mv tmp idn2-help.texi

MAINTAINERCLEANFILES = $(dist_man_MANS) decode.c example-tounicode.c example-toascii.c lookup.c \
	register.c stamp-vti version.texi

# GDOC

gdoc_TEXINFOS =
gdoc_TEXINFOS += texi/idn2_to_unicode_8z4z.texi
gdoc_TEXINFOS += texi/idn2_to_unicode_4z4z.texi
gdoc_TEXINFOS += texi/idn2_to_unicode_44i.texi
gdoc_TEXINFOS += texi/idn2_to_unicode_8z8z.texi
gdoc_TEXINFOS += texi/idn2_to_unicode_8zlz.texi
gdoc_TEXINFOS += texi/idn2_to_unicode_lzlz.texi
gdoc_TEXINFOS += texi/idn2_lookup_u8.texi
gdoc_TEXINFOS += texi/idn2_lookup_ul.texi
gdoc_TEXINFOS += texi/idn2_to_ascii_4i.texi
gdoc_TEXINFOS += texi/idn2_to_ascii_4i2.texi
gdoc_TEXINFOS += texi/idn2_to_ascii_4z.texi
gdoc_TEXINFOS += texi/idn2_to_ascii_8z.texi
gdoc_TEXINFOS += texi/idn2_to_ascii_lz.texi
gdoc_TEXINFOS += texi/idn2_register_u8.texi
gdoc_TEXINFOS += texi/idn2_register_ul.texi
gdoc_TEXINFOS += texi/idn2_strerror.texi
gdoc_TEXINFOS += texi/idn2_strerror_name.texi
gdoc_TEXINFOS += texi/idn2_check_version.texi
gdoc_TEXINFOS += texi/idn2_free.texi
gdoc_MANS =
gdoc_MANS += man/idn2_to_unicode_8z4z.3
gdoc_MANS += man/idn2_to_unicode_4z4z.3
gdoc_MANS += man/idn2_to_unicode_44i.3
gdoc_MANS += man/idn2_to_unicode_8z8z.3
gdoc_MANS += man/idn2_to_unicode_8zlz.3
gdoc_MANS += man/idn2_to_unicode_lzlz.3
gdoc_MANS += man/idn2_lookup_u8.3
gdoc_MANS += man/idn2_lookup_ul.3
gdoc_MANS += man/idn2_to_ascii_4i.3
gdoc_MANS += man/idn2_to_ascii_4i2.3
gdoc_MANS += man/idn2_to_ascii_4z.3
gdoc_MANS += man/idn2_to_ascii_8z.3
gdoc_MANS += man/idn2_to_ascii_lz.3
gdoc_MANS += man/idn2_register_u8.3
gdoc_MANS += man/idn2_register_ul.3
gdoc_MANS += man/idn2_strerror.3
gdoc_MANS += man/idn2_strerror_name.3
gdoc_MANS += man/idn2_check_version.3
gdoc_MANS += man/idn2_free.3

BUILT_SOURCES += $(gdoc_MANS) $(gdoc_TEXINFOS)

GDOC_SRC = \
	$(top_srcdir)/lib/decode.c \
	$(top_srcdir)/lib/lookup.c \
	$(top_srcdir)/lib/register.c \
	$(top_srcdir)/lib/error.c \
	$(top_srcdir)/lib/version.c \
	$(top_srcdir)/lib/free.c

.PHONY: compare-makefile

compare-makefile:
	$(AM_V_GEN) \
	MANS=""; \
	TEXINFOS=""; \
	FUNCS=`$(srcdir)/gdoc -listfunc $(GDOC_SRC)`; \
	for i in $$FUNCS; do \
		MANS="$$MANS\ngdoc_MANS += man/$$i.3"; \
		TEXINFOS="$$TEXINFOS\ngdoc_TEXINFOS += texi/$$i.texi"; \
	done && \
	grep -v -e '^gdoc_MANS += ' -e '^gdoc_TEXINFOS += ' $(srcdir)/Makefile.am | \
		perl -p -e "s,^gdoc_MANS =,gdoc_MANS =$$MANS,;" | \
		perl -p -e "s,^gdoc_TEXINFOS =,gdoc_TEXINFOS =$$TEXINFOS,;" \
		> tmp-$@ && \
	diff -u $(srcdir)/Makefile.am tmp-$@ && \
	rm -f tmp-$@

EXTRA_DIST += stamp-gdoc

$(gdoc_MANS) $(gdoc_TEXINFOS): stamp-gdoc

clean-local:
	-rm -f stamp-gdoc

stamp-gdoc: $(top_srcdir)/.version $(GDOC_SRC)
	$(AM_V_at)$(MKDIR_P) man texi
	$(AM_V_GEN)for i in `$(srcdir)/gdoc -listfunc $(GDOC_SRC)`; do \
		$(srcdir)/gdoc -man \
			-bugsto $(PACKAGE_BUGREPORT) \
			-module $(PACKAGE) \
			-pkg-name "$(PACKAGE_NAME)" \
			-sourceversion $(VERSION) \
			-includefuncprefix \
			-seeinfo $(PACKAGE) \
			-verbatimcopying \
			-copyright "2002-2022 Simon Josefsson" \
			-function $$i \
			$(GDOC_SRC) > man/$$i.3 && \
		$(srcdir)/gdoc -texinfo -function $$i \
			$(GDOC_SRC) > texi/$$i.texi; \
	done
	$(AM_V_at)touch $@
