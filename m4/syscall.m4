## Copyright 2005-2006 Benedikt Böhm <hollow@gentoo.org>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the
## Free Software Foundation, Inc.,
## 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

AC_DEFUN([LV_NR_VSERVER],
[
	AC_MSG_CHECKING([for vserver syscall number])

	AC_LANG_PUSH(C)
	AC_LANG_CONFTEST([
#if 	defined(__alpha__)
#define __NR_vserver	428
#elif	defined(__arm__)
#define __NR_vserver	313
#elif	defined(__cris__)
#define __NR_vserver	273
#elif	defined(__frv__)
#define __NR_vserver	273
#elif	defined(__h8300__)
#define __NR_vserver	273
#elif	defined(__i386__)
#define __NR_vserver	273
#elif	defined(__ia64__)
#define __NR_vserver	1269
#elif	defined(__m32r__)
#define __NR_vserver	273
#elif	defined(__mc68000__)
#define __NR_vserver	278
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI32)
#define __NR_vserver	277
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI64)
#define __NR_vserver	236
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_NABI32)
#define __NR_vserver	240
#elif	defined(__hppa__)
#define __NR_vserver	263
#elif	defined(__powerpc__)
#define __NR_vserver	257
#elif	defined(__s390__)
#define __NR_vserver	263
#elif	defined(__sh__)
#define __NR_vserver	273
#elif	defined(__sparc__)
#define __NR_vserver	267
#elif	defined(__x86_64__)
#define __NR_vserver	236
#endif

lv_nr_vserver=__NR_vserver
	])

	eval $(${CPP} conftest.c | ${EGREP} '^lv_nr_vserver=.*$')

	if test x"$lv_nr_vserver" = x; then
		AC_MSG_ERROR([Cannot determine vserver syscall number])
	else
		AC_DEFINE_UNQUOTED(__NR_vserver, $lv_nr_vserver, [vserver syscall number])
		AC_MSG_RESULT([$lv_nr_vserver])
	fi

	AC_LANG_POP
])
AC_DEFUN([LV_NR_CLONE],
[
	AC_MSG_CHECKING([for clone syscall number])

	AC_LANG_PUSH(C)
	AC_LANG_CONFTEST([
#if 	defined(__alpha__)
#define __NR_clone	312
#elif	defined(__arm__)
#define __NR_clone	120
#elif	defined(__cris__)
#define __NR_clone	120
#elif	defined(__frv__)
#define __NR_clone	120
#elif	defined(__h8300__)
#define __NR_clone	120
#elif	defined(__i386__)
#define __NR_clone	120
#elif	defined(__ia64__)
#define __NR_clone	1128
#elif	defined(__m32r__)
#define __NR_clone	120
#elif	defined(__mc68000__)
#define __NR_clone	120
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI32)
#define __NR_clone	120
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI64)
#define __NR_clone	55
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_NABI32)
#define __NR_clone	55
#elif	defined(__hppa__)
#define __NR_clone	120
#elif	defined(__powerpc__)
#define __NR_clone	120
#elif	defined(__s390__)
#define __NR_clone	120
#elif	defined(__sh__)
#define __NR_clone	120
#elif	defined(__sparc__)
#define __NR_clone	217
#elif	defined(__v850__)
#define __NR_clone	120
#elif	defined(__x86_64__)
#define __NR_clone	56
#endif

lv_nr_clone=__NR_clone
	])

	eval $(${CPP} conftest.c | ${EGREP} '^lv_nr_clone=.*$')

	if test x"$lv_nr_clone" = x; then
		AC_MSG_ERROR([Cannot determine clone syscall number])
	else
		AC_DEFINE_UNQUOTED(__NR_clone, $lv_nr_clone, [clone syscall number])
		AC_MSG_RESULT([$lv_nr_clone])
	fi

	AC_LANG_POP
])
