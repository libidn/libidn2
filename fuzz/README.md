# Fuzzers

These are fuzzers designed for use with `libFuzzer` or `afl`. They can
be used to run on Google's OSS-Fuzz (https://github.com/google/oss-fuzz/).

The convention used here is that the initial values for each parser fuzzer
are taken from the $NAME.in directory.

# Running a fuzzer using AFL

Use the following commands on top dir:

```
$ CC="afl-gcc" ./configure
$ make -j$(nproc)
$ cd fuzz
$ make idn2_to_unicode_8z8z_fuzzer
$ ./run-afl.sh idn2_to_unicode_8z8z_fuzzer
```

# Enhancing the testsuite for issues found

For the following tests dropping a file to a subdirectory in tests is
sufficient:

|--------------------------------|--------------------------------|
|idn2_to_unicode_8z8z_fuzzer     | tests/ascii-8z-interesting     |
|idn2_to_ascii_8z_fuzzer         | tests/unicode-8z8z-interesting |
|--------------------------------|--------------------------------|

