# Libidn2 CONTRIBUTING -- Information for developers
Copyright (C) 2011-2017 Simon Josefsson
See the end for copying conditions.

This file contains instructions for developers and advanced users that
wants to build from version controlled sources.  You need to have
several tools installed, including:

 * [Make](https://www.gnu.org/software/make/)
 * [Automake](https://www.gnu.org/software/automake/)
 * [Autoconf](https://www.gnu.org/software/autoconf/)
 * [Libtool](https://www.gnu.org/software/libtool/)
 * [Gettext](https://www.gnu.org/software/gettext/)
 * [Texinfo](https://www.gnu.org/software/texinfo/)
 * [Gperf](https://www.gnu.org/software/gperf/)
 * [help2man](https://www.gnu.org/software/help2man/)
 * [Gengetopt](https://www.gnu.org/software/gengetopt/)
 * [Tar](https://www.gnu.org/software/tar/)
 * [Gzip](https://www.gnu.org/software/gzip/)
 * [Texlive & epsf](https://www.tug.org/texlive/) (for PDF manual)
 * [GTK-DOC](https://www.gtk.org/gtk-doc/) (for API manual)
 * [Git](https://git-scm.com/)
 * [Perl](https://www.cpan.org/) (HTTPS: www.cpan.org uses an invalid security certificate)
 * [Valgrind](http://valgrind.org/) (optional) (No HTTPS at all)
 * [libunistring](https://www.gnu.org/software/libunistring/)
 * [abi-compliance-checker]
 * [ronn](https://rtomayko.github.io/ronn/)

## Obtaining sources

The required software is typically distributed with your operating
system, and the instructions for installing them differ.  Here are
some hints.

gNewSense/Debian/Ubuntu:
```
apt-get install git autoconf automake libtool texinfo gperf git2cl
apt-get install libunistring-dev gtk-doc-tools valgrind gengetopt
apt-get install abi-compliance-checker ruby-ronn
```

Download the version controlled sources:
```
$ git clone https://gitlab.com/libidn/libidn2.git
$ cd libidn2
```

## Building the project

Prepare building with
```
$ ./bootstrap
$ ./configure --enable-gtk-doc --enable-gtk-doc-pdf --enable-gcc-warnings --enable-valgrind-tests
```

You may want to use --gnulib-srcdir=/foo/bar/gnulib to avoid having to
checkout gnulib every time.  Make sure the gnulib directory you point
to is up to date.

Then build the project normally:
```
$ make
$ make check
```

## Test suite:

New functionality should be accompanied by a test case which verifies
the correctness of the new functionality as well as under failure.
The libidn2 test suite is run on "make check".

When submitting patches it is recommended to open a new merge request
[on the gitlab site](https://gitlab.com/libidn/libidn2), to force the
changes to pass the automated test suite.

## Release process

The release process consists of:

 * Make sure version number is updated in configure.ac and idn2.h.in.
 * Make sure library version is updated in configure.ac.
 * Prepare NEWS.
 * Do 'make release'

Happy hacking!

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
