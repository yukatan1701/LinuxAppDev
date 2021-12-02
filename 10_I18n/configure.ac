#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([guesser], [1.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.19.8)
GETTEXT_PACKAGE=guesser
AC_SUBST(GETTEXT_PACKAGE)
ALL_LINGUAS="ru"
AC_CONFIG_SRCDIR([src/guesser.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INTLTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_OUTPUT
