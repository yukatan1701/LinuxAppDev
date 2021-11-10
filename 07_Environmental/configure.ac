#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

AC_CHECK_LIB([rhash],[rhash_file, rhash_msg, rhash_print_bytes, rhash_get_digest_size, rhash_library_init], [], [AC_MSG_ERROR([RHash is needed.])])
#AC_CHECK_LIB([readline],[readline])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h stdio.h errno.h rhash.h ctype.h])
#AC_CHECK_HEADERS([readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_ARG_WITH([readline],
  [AS_HELP_STRING([--without-readline],
    [disable support for readline])],
  [],
  [with_readline=yes])
  
LIBREADLINE=
AS_IF([test "x$with_readline" != xno],
  [
    AC_CHECK_LIB([readline], [readline])
    AC_CHECK_HEADERS([readline/readline.h])
  ])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
