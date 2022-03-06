# Fuzzers

These are fuzzers designed for use with `libFuzzer` or `afl`. They can
be used to run on Google's OSS-Fuzz (https://github.com/google/oss-fuzz/).

The convention used here is that the initial values for each parser fuzzer
are taken from the $NAME.in directory.

Crash reproducers from OSS-Fuzz are put into $NAME.repro directory for
regression testing with top dir 'make check' or 'make check-valgrind'.

The ./configure runs below are for libidn2.


# Running a fuzzer using clang

Use the following commands on top dir:
```
export CC=clang-6.0
export CFLAGS="-O1 -g -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=undefined,integer,nullability -fsanitize=address -fsanitize-address-use-after-scope -fsanitize-coverage=trace-pc-guard,trace-cmp"
ASAN_OPTIONS=detect_leaks=0 ./configure --enable-static --disable-doc --disable-gcc-warnings
make clean
make -j$(nproc)
cd fuzz

# run libwget_xml_parse_buffer_fuzzer
UBSAN_OPTIONS=print_stacktrace=1 ASAN_SYMBOLIZER_PATH=/usr/lib/llvm-6.0/bin/llvm-symbolizer \
  ./run-clang.sh libidn2_to_ascii_8z_fuzzer
```


# Running a fuzzer using AFL

Use the following commands on top dir:

```
$ CC=afl-clang-fast ./configure --disable-doc
$ make -j$(nproc) clean all
$ cd fuzz
$ ./run-afl.sh libidn2_to_ascii_8z_fuzzer
```

# Fuzz code coverage using the corpus directories *.in/

Code coverage reports currently work best with gcc+lcov+genhtml.

In the top directory:
```
CC=gcc CFLAGS="-O0 -g" ./configure --disable-doc
make coverage
xdg-open doc/coverage/index.html
```

Each fuzzer target has it's own functions to cover, e.g.
`libidn2_to_ascii_8z_fuzzer` covers idn2_to_ascii_8z().

To work on corpora for better coverage, `cd fuzz` and use e.g.
`./view-coverage.sh libidn_toascii_fuzzer`.


# Enhancing the testsuite for issues found

Each reproducer file should be dropped into the appropriate *.repro/
directory.

# License

Copyright (c) 2017-2022 Tim Ruehsen

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
