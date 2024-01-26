#!/bin/sh

# Copyright (C) 2024 Simon Josefsson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# standalone.sh: build and run libidn2's C-based test suite.
#
# To check that system libidn2 behaves:
#
# tests/standalone.sh
#
# To specify the location of the libidn2 tests/ sub-directory use srcdir:
#
# srcdir=/home/user/src/libidn2/tests /usr/local/libexec/libidn2/standalone.sh
#
# If your system libidn2 is too old to pass certain tests, disable
# them using STANDALONE_DISABLE like this:
#
# STANDALONE_DISABLE='*punycode*' tests/standalone.sh
#
# To disable multiple tests, separate each glob pattern with whitespace:
#
# STANDALONE_DISABLE='*punycode* *register*' tests/standalone.sh
#
# To avoid glob patterns but use explicit names, use names relative to
# the $srcdir used:
#
# STANDALONE_DISABLE='tests/test-punycode.c tests/test-compat-punycode.c' tests/standalone.sh
#
# To specify a particular idn2 tool to test use the IDN2 variable, by
# default it searches for idn2 in your PATH using 'command -v'.
#
# IDN2=/usr/local/bin/idn2 tests/standalone.sh
#
# To check a newly built STATIC libidn WITH system -lunistring:
#
# env STANDALONE_CFLAGS="-Ilib lib/.libs/libidn2.a unistring/.libs/libunistring.a gl/.libs/libgnu.a -lunistring" tests/standalone.sh
#
# To check a newly built SHARED libidn WITH system -lunistring:
#
# env STANDALONE_CFLAGS="-Ilib -Wl,-rpath lib/.libs lib/.libs/libidn2.so unistring/.libs/libunistring.a gl/.libs/libgnu.a -lunistring" tests/standalone.sh
#
# To check a newly built STATIC libidn WITHOUT system -lunistring:
#
# env STANDALONE_CFLAGS="-DHAVE_CONFIG_H -I. -Ilib -Iunistring lib/.libs/libidn2.a unistring/.libs/libunistring.a gl/.libs/libgnu.a" tests/standalone.sh
#
# To check a newly built SHARED libidn WITHOUT system -lunistring:
#
# env STANDALONE_CFLAGS="-DHAVE_CONFIG_H -I. -Ilib -Iunistring -Wl,-rpath lib/.libs lib/.libs/libidn2.so unistring/.libs/libunistring.a gl/.libs/libgnu.a" tests/standalone.sh
#
# All variables can be combined to support combined behaviour.

set -e

srcdir="${srcdir:-$(dirname "$0")}"
STANDALONE_CC="${CC:-cc}"
STANDALONE_CFLAGS="${STANDALONE_CFLAGS:--lidn2 -lunistring}"
IDN2=${IDN2:-$(command -v idn2 || echo $srcdir/../src/idn2$EXEEXT)}; export IDN2

echo "srcdir=$srcdir"
echo "STANDALONE_CC: $STANDALONE_CC"
echo "STANDALONE_CFLAGS: $STANDALONE_CFLAGS"
echo "STANDALONE_DISABLE: $STANDALONE_DISABLE"
echo "IDN2: $IDN2"

rc=0

for f in "$srcdir"/test-*.c; do
    disable=
    set -o noglob
    for d in $STANDALONE_DISABLE; do
	set +o noglob
	case $f in
	    $d) disable=yes ;;
	esac
    done
    set +o noglob
    if test -n "$disable"; then
	echo "SKIP: $f"
	continue
    fi

    if $STANDALONE_CC -DSRCDIR=\"$srcdir\" -D'_GL_ATTRIBUTE_FORMAT_PRINTF_STANDARD(x,y)=' -o foo "$f" $STANDALONE_CFLAGS; then
        echo "PASS: cc $f"
        if ./foo; then
            echo "PASS: run $f"
        else
            echo "FAIL: run $f"
	    rc=1
        fi
    else
        echo "FAIL: cc $f"
	rc=1
    fi
    rm -f foo
done

for f in "$srcdir"/test-*.sh; do
    test -x "$f" || continue

    disable=
    set -o noglob
    for d in $STANDALONE_DISABLE; do
	set +o noglob
	case $f in
	    $d) disable=yes ;;
	esac
    done
    set +o noglob
    if test -n "$disable"; then
	echo "SKIP: $f"
	continue
    fi

    if $f; then
        echo "PASS: $f"
    else
        echo "FAIL: $f"
	rc=1
    fi
done

if test "$rc" != 0; then
    echo "FAIL: $0: error exit ($rc)"
    exit $rc
fi

echo "PASS: $0"
exit 0
