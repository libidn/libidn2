# Copyright (C) 2011-2017 Simon Josefsson

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

AC_INIT([libidn2], [2.3.0], [help-libidn@gnu.org],,
  [https://www.gnu.org/software/libidn/#libidn2])

# Library code modified:                              REVISION++
# Interfaces changed/added/removed:   CURRENT++       REVISION=0
# Interfaces added:                             AGE++
# Interfaces removed:                           AGE=0
AC_SUBST(LT_CURRENT, 3)
AC_SUBST(LT_REVISION, 7)
AC_SUBST(LT_AGE, 3)

#
# Generate version defines for the include file
#
AC_SUBST([IDN2_VERSION_MAJOR], [`echo $PACKAGE_VERSION|cut -d'.' -f1`])
AC_SUBST([IDN2_VERSION_MINOR], [`echo $PACKAGE_VERSION|cut -d'.' -f2`])
AC_SUBST([IDN2_VERSION_PATCH], [`echo $PACKAGE_VERSION|cut -d'.' -f3`])
AC_SUBST([IDN2_VERSION_NUMBER], [`printf '0x%02x%02x%04x' $IDN2_VERSION_MAJOR $IDN2_VERSION_MINOR $IDN2_VERSION_PATCH`])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Wno-portability subdir-objects])
AC_CANONICAL_HOST

AC_PROG_CC
AM_CONDITIONAL(cross_compiling,[test "$cross_compiling" = yes])
AX_PROG_CC_FOR_BUILD
AC_USE_SYSTEM_EXTENSIONS
gl_EARLY
unistring_EARLY
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT([win32-dll])
gl_INIT
unistring_INIT

# Detect the target system
case "${host_os}" in
    linux-gnu)
        build_linux_gnu=yes
esac
AM_CONDITIONAL([TEST_GLIBC], [test "$build_linux_gnu" = "yes"])

dnl Ideally, this should attempt a link, but this requires a separate
dnl version file, so we only check for compiler support here.
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([
__attribute__((visibility("hidden")))
int
versioned_symbol_internal (void)
{
}
__typeof__ (versioned_symbol_internal) versioned_symbol
   __attribute__ ((visibility ("default"),
                   alias ("versioned_symbol_internal")));
__asm__ (".symver versioned_symbol, versioned_symbol@IDN2_0.0.0");
])], [AC_DEFINE([HAVE_SYMVER_ALIAS_SUPPORT], [1],
     [The toolchain supports aliases and .symver.])])

#
# check for gtk-doc
#
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])
# needed for some older versions of gtk-doc
m4_ifdef([GTK_DOC_USE_LIBTOOL], [], [
AM_CONDITIONAL([GTK_DOC_USE_LIBTOOL], false)
])

AM_GNU_GETTEXT(external)
AM_GNU_GETTEXT_VERSION(0.19.3)

AX_CODE_COVERAGE

# Non-verbose make
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_ARG_ENABLE([gcc-warnings],
  [AS_HELP_STRING([--enable-gcc-warnings],
		  [turn on lots of GCC warnings (for developers)])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for gcc-warnings option]) ;;
   esac
   gl_gcc_warnings=$enableval],
  [gl_gcc_warnings=yes]
)

if test "$gl_gcc_warnings" = yes; then
  gl_MANYWARN_ALL_GCC([warnings])
  nw=
  nw="$nw -Wsystem-headers"       # Don't let system headers trigger warnings
  nw="$nw -Wundef"                # All compiler preprocessors support #if UNDEF
  nw="$nw -Wtraditional"          # All compilers nowadays support ANSI C
  nw="$nw -Wconversion"           # These warnings usually don't point to mistakes.
  nw="$nw -Wpadded"               # Padding internal structs doesn't help.
  nw="$nw -Wc++-compat"           # Compile using a C compiler.
  nw="$nw -Wtraditional-conversion" # Too many complaints for now.
  nw="$nw -Wunreachable-code"     # gcc bug 40412
  nw="$nw -Wswitch-default"       # Nothing wrong with default-less switch?
  nw="$nw -Wmissing-field-initializers" # Avoid spamming in tests/ directory

  gl_MANYWARN_COMPLEMENT([warnings], [$warnings], [$nw])
  for w in $warnings; do
    gl_WARN_ADD([$w])
  done

  gl_WARN_ADD([-fdiagnostics-show-option])
  gl_WARN_ADD([-fdiagnostics-color=always])      # colors even when using ccache
  gl_WARN_ADD([-Wno-missing-field-initializers]) # # Avoid spamming in tests/ directory
fi

AC_ARG_ENABLE(doc,
  AS_HELP_STRING([--disable-doc], [don't generate any documentation]),
    enable_doc=$enableval, enable_doc=yes)
AM_CONDITIONAL(ENABLE_DOC, test "$enable_doc" != "no")

if test "$enable_doc" = "yes";then
  AC_CONFIG_FILES([
    doc/Makefile
    doc/reference/Makefile
    doc/reference/version.xml
  ])
fi

if test "$ac_cv_libunistring" = "yes";then
  AC_SEARCH_LIBS(uc_joining_type, unistring, [], [ac_cv_libunistring=no])
fi

AM_CONDITIONAL(HAVE_LIBUNISTRING, test "$ac_cv_libunistring" = "yes")

AC_CONFIG_FILES([
  Makefile
  examples/Makefile
  lib/idn2.h
  lib/Makefile
  unistring/Makefile
  gl/Makefile
  libidn2.pc
  po/Makefile.in
  src/Makefile
  tests/Makefile
  fuzz/Makefile
])
AC_OUTPUT

AC_MSG_NOTICE([Summary of build options:

  Version:           ${PACKAGE_VERSION}
  Host OS:           ${host_os}
  Install prefix:    ${prefix}
  Compiler:          ${CC}
  Warning flags:     ${WARN_CFLAGS}
  CFLAGS:            ${CFLAGS} ${CPPFLAGS}
  LDFlags:           ${LDFLAGS}
  Documentation:     ${enable_doc}
  Library types:     Shared=${enable_shared}, Static=${enable_static}
  Libiconv:          $am_cv_func_iconv $LTLIBICONV
  Libunistring:      $ac_cv_libunistring $LIBUNISTRING_VERSION $LTLIBUNISTRING
  Valgrind:          ${VALGRIND}
  Version script:    $have_ld_version_script
])
