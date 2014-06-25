# Copyright (C) 2011-2014 Simon Josefsson

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

SUBDIRS = gl
ACLOCAL_AMFLAGS = -I ../m4 -I gl/m4
EXTRA_DIST = gl/m4/gnulib-cache.m4

AM_CPPFLAGS = -I.
AM_CPPFLAGS += -I$(srcdir)/.. -I$(builddir)/..
AM_CPPFLAGS += -I$(srcdir)/../gl -I$(builddir)/../gl
AM_CPPFLAGS += -I$(srcdir)/gl -I$(builddir)/gl
AM_CFLAGS = $(WARN_CFLAGS)

bin_PROGRAMS = idn2
idn2_SOURCES = idn2.c blurbs.h
idn2_LDADD = libidn2_cmd.la ../libidn2.la gl/libgnu.la

idn2.c: $(BUILT_SOURCES)

noinst_LTLIBRARIES = libidn2_cmd.la
libidn2_cmd_la_SOURCES =  idn2.ggo idn2_cmd.c idn2_cmd.h
libidn2_cmd_la_LIBADD = ../gl/libgnu.la gl/libgnu.la
libidn2_cmd_la_CFLAGS =

idn2_cmd.c idn2_cmd.h: idn2.ggo Makefile.am
	gengetopt --unamed-opts --no-handle-version --no-handle-help \
		--set-package="idn2" \
		--input $^ --file-name idn2_cmd
	perl -pi -e 's/\[OPTIONS\]/\[OPTION\]/g' idn2_cmd.c
	perl -pi -e 's/\[FILES\]/\[STRING\]/g' idn2_cmd.c

BUILT_SOURCES = idn2_cmd.c idn2_cmd.h
MAINTAINERCLEANFILES = $(BUILT_SOURCES)
