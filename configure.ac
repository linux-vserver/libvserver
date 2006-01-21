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
AC_INIT(libvserver, 1.0.3, [http://dev.croup.de/proj/libvserver])
AC_CONFIG_HEADER([config.h])
AC_GNU_SOURCE

# Automake
AM_INIT_AUTOMAKE([1.9 gnu dist-bzip2])
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
# HACK: see below why we do not check for libtool here
#AC_PROG_LIBTOOL
AC_PROG_EGREP

# check for dietlibc
case $host_cpu in
	(i*86|athlon) min_diet_ver=0.25;;
	(ia64|hppa*)  min_diet_ver=0.29;;
	(*)           min_diet_ver=0.28;;
esac

AC_LV_DIETLIBC([$min_diet_ver])

if test $ac_lv_have_dietlibc = yes; then
	# HACK: libtool does not have cmdline options to build only
	# static libraries; this can be done with the
	# '--disable-shared' ./configure option only. We have to set
	# this option which is evaluated by 'AC_PROG_LIBTOOL'
 	# below.  Therefore, this macro must not be called earlier.
	enable_shared=no
	enable_static=yes
	CC="${DIET} ${DIETFLAGS} ${CC}"
fi

# HACK: see comments at 'enable_static' above
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdint.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_C_CONST
AC_C_INLINE

# Checks for library functions.

# Compiler settings
CFLAGS="${CFLAGS} -fno-omit-frame-pointer -W -Wall -std=gnu99 -pedantic"

# Site settings
AC_LV_SYSCALL_NR
AC_LV_CHECK_KERNEL_HEADERS

# Final info page
AC_CONFIG_COMMANDS_PRE([SUMMARY="$PACKAGE_STRING configured successfully:

                       CC: $CC ($($CC --version | head -n1))
                 CPPFLAGS: '$CPPFLAGS'
                   CFLAGS: '$CFLAGS'

                   prefix: $prefix
               build/host: $build/$host
             use dietlibc: $ac_lv_have_dietlibc
           syscall number: $ac_lv_syscall_nr
"])

# Output
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

AC_MSG_NOTICE([$SUMMARY])
