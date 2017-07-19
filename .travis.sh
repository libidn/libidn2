#!/bin/bash

set -e

CONFIGURE_OPTIONS=()
export CFLAGS="-O0 -g"

if [[ $TRAVIS_OS_NAME = 'osx' ]]; then
	CONFIGURE_OPTIONS+=("")
else
	CONFIGURE_OPTIONS+=("--enable-fsanitize-asan --enable-fsanitize-ubsan")
	CONFIGURE_OPTIONS+=("--enable-valgrind-tests")
fi

./bootstrap

# On OSX we are unable to find the idn2 dylibs without installing first
# However `make install` on linux systems fail due to insufficient permissions
if [[ $TRAVIS_OS_NAME = 'osx' ]]; then
	./configure --disable-doc
	make install -j3
	make check -j3 || (cat tests/test-suite.log && exit 1)
	exit 0
fi

for OPTS in "${CONFIGURE_OPTIONS[@]}"; do
	./configure -C $OPTS
	make clean check -j3 || (cat tests/test-suite.log && exit 1)
done

DISTCHECK_CONFIGURE_FLAGS=--disable-gtk-doc make distcheck -j3
