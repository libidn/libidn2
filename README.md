![build status](https://gitlab.com/libidn/libidn2/badges/master/build.svg)
[![coverage status](https://gitlab.com/libidn/libidn2/badges/master/coverage.svg)](https://libidn.gitlab.io/libidn2/coverage)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/12080/badge.svg)](https://scan.coverity.com/projects/libidn2)


# Libidn2 README -- Introduction information
Copyright (C) 2011-2017 Simon Josefsson
See the end for copying conditions.

Libidn2 is a free software implementation of IDNA2008 and TR46.

 * [RFC 5890](https://tools.ietf.org/html/rfc5890)
 * [RFC 5891](https://tools.ietf.org/html/rfc5891)
 * [RFC 5892](https://tools.ietf.org/html/rfc5892)
 * [RFC 5893](https://tools.ietf.org/html/rfc5893)
 * [TR46](http://www.unicode.org/reports/tr46/)

Libidn2 is believed to be a complete IDNA2008 and TR46 implementation,
but has yet to be as extensively used as the IDNA2003 Libidn library.

# Obtaining the source

The homepage of libidn2: https://www.gnu.org/software/libidn/#libidn2

Software releases of libidn2 can be downloaded from
https://alpha.gnu.org/gnu/libidn/ and ftp://alpha.gnu.org/gnu/libidn/

Development of libidn2 is organized [through GitLab website](https://gitlab.com/libidn/libidn2),
and there is [an issue tracker for reporting bugs](https://gitlab.com/libidn/libidn2/issues).

# Dependencies

Libidn2 uses GNU libunistring for Unicode processing and GNU libiconv
for character set conversion.  See the following links for more
information on these packages:

 * [Unistring](https://www.gnu.org/software/libunistring/)
 * [iconv](https://www.gnu.org/software/libiconv/)

Note that the iconv dependency is optional, and required only for the
functions involving locale to UTF conversions.

# Estimating code coverage

Dependencies:
 * [lcov](http://linux-test-project.github.io/) (for code coverage)

To test the code coverage of the test suite use the following:
```
$ ./configure --enable-code-coverage
$ make && make check && make code-coverage-capture
```

# License

The installed C library libidn2 is dual-licensed under LGPLv3+|GPLv2+,
while the rest of the package is GPLv3+.  See the file [COPYING](COPYING)
for detailed information.


----------------------------------------------------------------------
This file is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file.  If not, see <https://www.gnu.org/licenses/>.
