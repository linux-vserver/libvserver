# Copyright 2005 The libvserver Developers
# See AUTHORS for details
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by  *
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the
# Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

# Generic configuration
AC_PREREQ(2.59)
AC_INIT(libvserver, 2.0, hollow@gentoo.org)
AC_CONFIG_HEADER([config.h])
AC_GNU_SOURCE

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# Automake
AM_INIT_AUTOMAKE([1.9 gnu dist-bzip2])
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_EGREP

# Parts to build
AC_ARG_ENABLE([tools],
              [AC_HELP_STRING([--disable-tools],
                              [Disable the command line tools])],
              [case "${enableval}" in
                yes) enable_tools=true;;
                no)  enable_tools=false;;
                *)   AC_MSG_ERROR(bad value ${enableval} for --enable-tools);;
              esac],
              [enable_tools=true])
AM_CONDITIONAL(ENABLE_TOOLS, test x$enable_tools = xtrue)

# Checks for libraries.
if test x$enable_tools = xtrue; then
AC_CHECK_LIB(ucid, flist32_to_str,
	LUCID_LIBS="-lucid", AC_MSG_ERROR([lucid not found]),)
fi

AC_SUBST(LUCID_LIBS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([errno.h sys/resource.h sys/syscall.h],
                 [], AC_MSG_ERROR([Required headers not found]))

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE

# Checks for library functions.

# Compiler settings
CFLAGS="${CFLAGS} -std=gnu99 -pedantic -fno-omit-frame-pointer"
CFLAGS="${CFLAGS} -Wall -Wpointer-arith -Wcast-qual -Winline"
CFLAGS="${CFLAGS} -Wredundant-decls -Wcast-align -Wno-unused-parameter"

# Site settings
AC_LV_SYSCALL_NR

# Final info page
AC_CONFIG_COMMANDS_PRE([SUMMARY="$PACKAGE_STRING configured successfully:

                       CC: $CC ($($CC --version | head -n1))
                 CPPFLAGS: '$CPPFLAGS'
                   CFLAGS: '$CFLAGS'
                    build: $build
                     host: $host
                   target: $target

                   prefix: $prefix
           syscall number: $ac_lv_syscall_nr
"])

# Output
AC_CONFIG_FILES([Makefile
                 src/lib/Makefile
                 src/tools/Makefile
                 src/Makefile])
AC_OUTPUT

AC_MSG_NOTICE([$SUMMARY])
