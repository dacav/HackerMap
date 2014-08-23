dnl Process this file with autoconf to produce a configure script.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([hacker-map], [0.1], [dacav@openmailbox.org],,[http://example.com])

dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.11.1 readme-alpha parallel-tests])

dnl Minimum Autoconf version required.
AC_PREREQ([2.62])

dnl Where to generate output; srcdir location.
AC_CONFIG_HEADERS([config.h:config.in])
AC_CONFIG_SRCDIR([src/cortroller.cc])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

dnl Since we use gnulib: gl_EARLY must be called as soon as possible after
dnl the C compiler is checked.  The others could be later, but we just
dnl keep everything together.

dnl gl_EARLY
dnl gl_INIT

dnl Copyright will apply as long as these sources are in use, e.g., are
dnl being compiled, which is reasonable year to claim the copyright.
AC_DEFINE([COPYRIGHT_YEAR], [m4_esyscmd([date +%Y])], [year in copyright message])

dnl GNU help2man creates man pages from --help output; in many cases, this
dnl is sufficient, and obviates the need to maintain man pages separately.
dnl However, this means invoking executables, which we generally cannot do
dnl when cross-compiling, so we test to avoid that (the variable
dnl "cross_compiling" is set by AC_PROG_CC).

dnl AS_IF([test $cross_compiling = no], [
dnl  AM_MISSING_PROG([HELP2MAN], [help2man])
dnl], [
dnl  HELP2MAN=:
dnl])

dnl i18n support from GNU gettext.
dnl AM_GNU_GETTEXT_VERSION([0.18.1])
dnl AM_GNU_GETTEXT([external])

dnl           doc/Makefile
dnl           lib/Makefile
dnl           man/Makefile
dnl           po/Makefile.in
dnl           contrib/Makefile

AC_CONFIG_FILES([Makefile
    src/Makefile
    tests/Makefile])
AC_OUTPUT
