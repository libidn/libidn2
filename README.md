# Libidn2 README -- Introduction information

Libidn2 is a free software implementation of IDNA2008, Punycode and
Unicode TR46.  Its purpose is to encode and decode internationalized
domain names.

For technical reference, see:

 * [IDNA2008 Framework](https://tools.ietf.org/html/rfc5890)
 * [IDNA2008 Protocol](https://tools.ietf.org/html/rfc5891)
 * [IDNA2008 Unicode tables](https://tools.ietf.org/html/rfc5892)
 * [IDNA2008 Bidi rule](https://tools.ietf.org/html/rfc5893)
 * [Punycode](https://tools.ietf.org/html/rfc3492)
 * [Unicode IDNA Compatibility Processing](https://www.unicode.org/reports/tr46/)

The library contains functionality to convert internationalized domain
names to and from ASCII Compatible Encoding (ACE).

The API consists of two main functions, `idn2_to_ascii_8z` for
converting data from UTF-8 to ASCII Compatible Encoding (ACE), and
`idn2_to_unicode_8z8z` to convert ACE names into UTF-8 format. There
are several variations of these main functions, which accept UTF-32,
or input in the local system encoding. All functions assume
zero-terminated strings.

This library is backwards (API) compatible with the [libidn
library](https://www.gnu.org/software/libidn/).  Replacing the
`idna.h` header with `idn2.h` into a program is sufficient to switch
the application from IDNA2003 to IDNA2008 as supported by this
library.

Libidn2 is believed to be a complete IDNA2008 and TR46 implementation,
it contains an extensive test-suite, and is included in the continuous
fuzzing project
[OSS-Fuzz](https://bugs.chromium.org/p/oss-fuzz/issues/list?q=libidn2).

You can check the current test code coverage
[here](https://libidn.gitlab.io/libidn2/coverage/index.html) and the
current fuzzing code coverage
[here](https://libidn.gitlab.io/libidn2/fuzz-coverage/index.html).


# License

The installed C library libidn2 is dual-licensed under LGPLv3+|GPLv2+,
while the rest of the package is GPLv3+.  See the file
[COPYING](COPYING) for detailed information.


# Online docs

[API reference](https://libidn.gitlab.io/libidn2/reference/api-index-full.html)

[Manual](https://libidn.gitlab.io/libidn2/manual/libidn2.html)


# Obtaining the source

Software releases of libidn2 can be downloaded from
https://ftp.gnu.org/gnu/libidn/ and ftp://ftp.gnu.org/gnu/libidn/

Development of libidn2 is organized [through GitLab
website](https://gitlab.com/libidn/libidn2), and there is [an issue
tracker for reporting bugs](https://gitlab.com/libidn/libidn2/issues).


# Dependencies

To build Libidn2 you will need a POSIX shell to run ./configure, the
Unix "make" tool, and a C compiler to build the library.

 * [Bash](https://www.gnu.org/software/bash/)
 * [Make](https://www.gnu.org/software/make/)
 * [C compiler](https://www.gnu.org/software/gcc/)

The shared libidn2 library may use GNU libunistring for Unicode
processing and GNU libiconv for character set conversion.  It is
recommended to install them before building and installing libidn2.
See the following links for more information on these packages:

 * [Unistring](https://www.gnu.org/software/libunistring/)
 * [iconv](https://www.gnu.org/software/libiconv/)

The iconv dependency is optional -- it is required for the functions
involving locale to UTF8 conversions -- but is recommended.

When the recommended libunistring is not available, libidn2 provides
replacement functionality which increases the size of the library.


# Contributing

See [the contributing document](CONTRIBUTING.md).


# Estimating code coverage

Dependencies:
 * [lcov](https://github.com/linux-test-project/lcov) (for code coverage)

To test the code coverage of the test suite use the following:
```
$ ./configure --enable-code-coverage
$ make && make check && make code-coverage-capture
```

The current coverage report can be found [here](https://libidn.gitlab.io/libidn2/coverage/).


# Fuzzing

Libidn2 is being continuously fuzzed by [OSS-Fuzz](https://github.com/google/oss-fuzz).

Of course you can do local fuzzing on your own, see `fuzz/README.md` for instructions.

The code coverage of our fuzzers can be found [here](https://libidn.gitlab.io/libidn2/fuzz-coverage/).
