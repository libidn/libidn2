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

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)
AM_LDFLAGS = -static

LDADD = ../libidn2.la

TESTS = test-punycode test-lookup test-register
check_PROGRAMS = test-punycode test-lookup test-register

EXTRA_DIST = IdnaTest.c

TESTS_ENVIRONMENT = $(VALGRIND)

IdnaTest.txt: $(srcdir)/gen-utc-test.pl
	test -f IdnaTest.txt || \
		wget http://www.unicode.org/Public/idna/6.0.1/IdnaTest.txt

IdnaTest.c: IdnaTest.txt
	$(srcdir)/gen-utc-test.pl < IdnaTest.txt > IdnaTest.c
