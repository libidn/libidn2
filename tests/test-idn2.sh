#!/bin/sh

# Copyright (C) 2022 Simon Josefsson
#
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

srcdir="${srcdir:-.}"

IDN2="${IDN2:-../src/idn2$EXEEXT}"

TMPFILE="idn2.$$.tmp"
trap 'rm -f "$TMPFILE" "$TMPFILE-2"' EXIT QUIT

if ! test -z "${LOG_VALGRIND}";then
    LOG_VALGRIND="${LIBTOOL:-libtool} --mode=execute ${LOG_VALGRIND} --error-exitcode=7"
fi

# Sanity check, does it run at all?

$IDN2 --version
rc=$?
if test $rc != 0; then
    echo "FAIL: $0: $IDN2 --version: rc $rc"
    exit 1
fi

# Check that we can work under valgrind:

$LOG_VALGRIND $IDN2 --version
rc=$?
if test $rc != 0; then
    echo "FAIL: $0: valgrind $IDN2 --version: rc $rc"
    exit 1
fi

# Code coverage trigger:

$LOG_VALGRIND $IDN2 --help
rc=$?
if test $rc != 0; then
    echo "FAIL: $0: valgrind $IDN2 --help: rc $rc"
    exit 1
fi

# Actually convert something, even though it is the empty string.
# Mostly to catch locale/iconv-related issues.

$LOG_VALGRIND $IDN2 ''
rc=$?
if test $rc != 0; then
    echo "FAIL: $0: $IDN2 '': rc $rc"
    exit $rc
fi

echo "PASS: $0: $IDN2 ''"

# Does it handle a simple ASCII string on the command-line?

$LOG_VALGRIND $IDN2 example.org > $TMPFILE 2> $TMPFILE-2
rc=$?
OUTSTR="$(cat $TMPFILE | tr -d '\r')"
ERRSTR="$(cat $TMPFILE-2)"

if test $rc != 0; then
    echo "FAIL: $0: $IDN2 example.org: rc $rc"
    echo "OUT: $OUTSTR"
    echo "ERR: $ERRSTR"
    exit 1
fi

if test "$OUTSTR" != example.org; then
    echo "FAIL: $0: $IDN2 example.org: expected example.org got $OUTSTR"
    echo "OUT: $OUTSTR"
    echo "ERR: $ERRSTR"
    exit 1
fi

if test "$ERRSTR" != ""; then
    echo "FAIL: $0: $IDN2 example.org: stderr: $ERRSTR"
    echo "OUT: $OUTSTR"
    echo "ERR: $ERRSTR"
    test -z "$EXEEXT" && exit 1
fi

rm -f $TMPFILE

echo "PASS: $0: $IDN2 example.org"

# Does it handle a simple ASCII string on standard input?

echo example.org | $LOG_VALGRIND $IDN2 > $TMPFILE 2> $TMPFILE-2
rc=$?
OUTSTR="$(cat $TMPFILE | tr -d '\r')"
ERRSTR="$(cat $TMPFILE-2)"

if test $rc != 0; then
    echo "FAIL: $0: echo example.org | $IDN2: rc $rc"
    echo "OUT: $OUTSTR"
    echo "ERR: $ERRSTR"
    exit 1
fi

if test "$OUTSTR" != example.org; then
    echo "FAIL: $0: echo example.org | $IDN2: expected example.org got $OUTSTR"
    echo "OUT: $OUTSTR"
    echo "ERR: $ERRSTR"
    exit 1
fi

if test "$ERRSTR" != ""; then
    echo "FAIL: $0: echo example.org | $IDN2: stderr: $ERRSTR"
    echo "OUT: $OUTSTR"
    echo "ERR: $ERRSTR"
    test -z "$EXEEXT" && exit 1
fi

rm -f $TMPFILE

echo "PASS: $0: echo example.org | $IDN2"

exit 0
