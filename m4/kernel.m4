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

AC_DEFUN([AC_LV_CHECK_KERNEL_HEADERS],
[
	AC_MSG_CHECKING([for linux headers version])
	
	AC_LANG_PUSH(C)
	
	AC_LANG_CONFTEST([[
#include <linux/version.h>
kernel_version=LINUX_VERSION_CODE
	]])
	eval $(${CPP} conftest.c | ${EGREP} '^kernel_version=.*$')
	
	if test x"$kernel_version" = x; then
		AC_MSG_ERROR([Cannot determine linux headers version])
	elif test $kernel_version -lt 132616; then
		AC_MSG_ERROR([You need at least linux headers 2.6.8])
	else
		AC_MSG_RESULT([ok])
	fi
	
	AC_LANG_POP
])