# Copyright (C) 2011-2024 Simon Josefsson

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

AC_INIT([Libidn2],
        m4_esyscmd([build-aux/git-version-gen .tarball-version]),
        [help-libidn@gnu.org],,
        [https://www.gnu.org/software/libidn/#libidn2])

# Library code modified:                              REVISION++
# Interfaces changed/added/removed:   CURRENT++       REVISION=0
# Interfaces added:                             AGE++
# Interfaces removed:                           AGE=0
AC_SUBST(LT_CURRENT, 3)
AC_SUBST(LT_REVISION, 8)
AC_SUBST(LT_AGE, 3)

DLL_VERSION=`expr ${LT_CURRENT} - ${LT_AGE}`
AC_SUBST(DLL_VERSION)

AC_SUBST([MAJOR_VERSION], [`echo $PACKAGE_VERSION|cut -d'.' -f1`])
AC_SUBST([MINOR_VERSION], [`echo $PACKAGE_VERSION|cut -d'.' -f2`])
AC_SUBST([PATCH_VERSION], [`echo $PACKAGE_VERSION|cut -d'.' -f3`])
AC_SUBST([NUMBER_VERSION], [`printf '0x%02x%02x%04x' $MAJOR_VERSION $MINOR_VERSION $PATCH_VERSION`])

AC_MSG_NOTICE([$PACKAGE_NAME $PACKAGE_VERSION $PACKAGE_TARNAME $MAJOR_VERSION.$MINOR_VERSION.$PATCH_VERSION $NUMBER_VERSION $LT_CURRENT:$LT_REVISION:$LT_AGE $DLL_VERSION])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.14 -Wall -Wno-portability subdir-objects])
AM_SILENT_RULES([yes])

AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS
gl_EARLY
unistring_EARLY
AM_MISSING_PROG(HELP2MAN, help2man, $missing_dir)
LT_INIT([win32-dll])
gl_INIT
unistring_INIT
AC_DEFINE([GNULIB_NO_VLA], 1, [Disable VLA usage in gettext.h.])

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

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.8])

AX_CODE_COVERAGE

AC_ARG_ENABLE([gcc-warnings],
  [AS_HELP_STRING([[--enable-gcc-warnings[=TYPE]]],
    [control generation of GCC warnings.  The TYPE 'no' disables
     warnings; 'yes' (default) generates cheap warnings;
     'expensive' in addition generates expensive warnings
     and 'error' also turn warnings into errors.])])

# https://www.gnu.org/software/gnulib//manual/html_node/manywarnings.html
AS_IF([test "$enable_gcc_warnings" != no],
  [
   # Set up the list of unwanted warning options.
   nw=
   if test "$enable_gcc_warnings" = yes; then
     nw="$nw -fanalyzer"
   fi
   nw="$nw -Wbad-function-cast" # Casting a function's result is not more
                                # dangerous than casting any other value.
   nw="$nw -Winline"            # It's OK to not inline.
   nw="$nw -Wsign-compare"      # Too many false alarms.
   nw="$nw -Wstrict-overflow"   # It's OK to optimize strictly.
   nw="$nw -Wsystem-headers"    # Don't warn in system headers.

   # https://github.com/pi-hole/FTL/pull/1428
   nw="$nw -Wsuggest-attribute=pure"
   nw="$nw -Wsuggest-attribute=const"

  dnl nw="$nw -Wundef"                # All compiler preprocessors support #if UNDEF
  dnl nw="$nw -Wtraditional"          # All compilers nowadays support ANSI C
  dnl nw="$nw -Wconversion"           # These warnings usually don't point to mistakes.
  dnl nw="$nw -Wpadded"               # Padding internal structs doesn't help.
  dnl nw="$nw -Wc++-compat"           # Compile using a C compiler.
  dnl nw="$nw -Wtraditional-conversion" # Too many complaints for now.
  dnl nw="$nw -Wunreachable-code"     # gcc bug 40412
  dnl nw="$nw -Wswitch-default"       # Nothing wrong with default-less switch?
  dnl nw="$nw -Wmissing-field-initializers" # Avoid spamming in tests/ directory
  dnl gl_WARN_ADD([-fdiagnostics-show-option])
  dnl gl_WARN_ADD([-fdiagnostics-color=always])      # colors even when using ccache

   if test "$enable_gcc_warnings" = error; then
     gl_WARN_ADD([-Werror], [WERROR_CFLAGS])
     gl_WARN_ADD([-Wno-error=analyzer-use-of-uninitialized-value], [WERROR_CFLAGS])
     gl_WARN_ADD([-Wno-error=missing-field-initializers], [WERROR_TESTS_CFLAGS])
     # GCC 11.4 false positive: test-glib.c: double-'free' of 'naemchen_bytes' [-Werror=analyzer-double-free]
     gl_WARN_ADD([-Wno-error=analyzer-double-free], [WERROR_TESTS_CFLAGS])
   fi

   # Setup the list of meaningful warning options for the C compiler.
   # The list comes from manywarnings.m4. Warning options that are not
   # generally meaningful have already been filtered out (cf.
   # build-aux/gcc-warning.spec).
   gl_MANYWARN_ALL_GCC([possible_warning_options])

   # Compute the list of warning options that are desired.
   gl_MANYWARN_COMPLEMENT([desired_warning_options],
                          [$possible_warning_options], [$nw])
   # Compute the list of remaining undesired warning options.
   # Namely those, that were not in manywarnings.m4 because they were
   # already listed in build-aux/gcc-warning.spec; this includes those
   # that are implied by -Wall.
   gl_MANYWARN_COMPLEMENT([remaining_undesired_warning_options],
                          [$nw], [$possible_warning_options])

   # Add the desired warning options to WARN_CFLAGS.
   for w in $desired_warning_options; do
     gl_WARN_ADD([$w])
   done

   # Add the opposites of the remaining undesired warning options to
   # WARN_CFLAGS.
   for w in `echo "$remaining_undesired_warning_options" | sed -e 's/-W/-Wno-/g'`; do
     gl_WARN_ADD([$w])
   done
])

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

AC_MSG_NOTICE([summary of main build options:

  Version:            ${VERSION}
  Libtool version     $LT_CURRENT:$LT_REVISION:$LT_AGE
  DLL version:        $DLL_VERSION
  Header version:     major $MAJOR_VERSION minor $MINOR_VERSION patch $PATCH_VERSION number $NUMBER_VERSION
  Build system:       ${build}
  Host/Target system: ${host}
  Install prefix:     ${prefix}
  Compiler:           ${CC}
  CFLAGS:             ${CFLAGS}
  CPPFLAGS:           ${CPPFLAGS}
  LDFLAGS:            ${LDFLAGS}
  Library types:      Shared=${enable_shared}, Static=${enable_static}

  Warning flags:      $enable_gcc_warnings
      WERROR_CFLAGS:  $WERROR_CFLAGS
WERROR_TESTS_CFLAGS:  $WERROR_TESTS_CFLAGS
        WARN_CFLAGS:  $WARN_CFLAGS

  Documentation:      ${enable_doc}

  nl_langinfo:        $gl_cv_header_langinfo_codeset
  Libiconv:           $am_cv_func_iconv_summary
         LTLIBICONV:  $LTLIBICONV
  Libunistring:       $ac_cv_libunistring
            VERSION:  $LIBUNISTRING_VERSION
     LTLIBUNISTRING:  $LTLIBUNISTRING

  Version script:     $have_ld_version_script

  Valgrind:           $gl_cv_prog_valgrind_works $VALGRIND_PROGRAM $DEFAULT_VALGRINDFLAGS $VALGRINDFLAGS
])
