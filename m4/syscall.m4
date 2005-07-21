AC_DEFUN([CHECK_SYSCALL_NR],
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
#define __NR_vserver	__m32r_NR_vserver
#elif	defined(__mc68000__)
#define __NR_vserver	278
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI32)
#define __NR_vserver	277
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI64)
#define __NR_vserver	240
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_NABI32)
#define __NR_vserver	236
#elif	defined(__hppa__)
#define __NR_vserver	__hppa_NR_vserver
#elif	defined(__powerpc__)
#define __NR_vserver	257
#elif	defined(__s390__)
#define __NR_vserver	263
#elif	defined(__sh__)
#define __NR_vserver	273
#elif	defined(__sparc__)
#define __NR_vserver	267
#elif	defined(__v850__)
#define __NR_vserver	__v850_NR_vserver
#elif	defined(__x86_64__)
#define __NR_vserver	236
#endif

syscall_nr=__NR_vserver
	])
	
	eval $(${CPP} conftest.c | ${EGREP} '^syscall_nr=.*$')
	
	if test x"$syscall_nr" = x; then
		AC_MSG_ERROR([Cannot determine vserver syscall number])
	else
		AC_DEFINE_UNQUOTED(__NR_vserver, $syscall_nr, [VServer syscall number])
		AC_MSG_RESULT([$syscall_nr])
	fi
	
	AC_LANG_POP
])


AC_DEFUN([ENABLE_ALT_SYSCALL],
[
	AC_MSG_CHECKING([whether to use alternative syscall])
	
	AC_ARG_ENABLE([alt-syscall],
	              AC_HELP_STRING([--enable-alt-syscall],
	                             [use alternative syscall (default: no)]),
	              [enable_alt_syscall=yes],
	              [enable_alt_syscall=no])
	
	if test "$enable_alt_syscall" = yes; then
		AC_DEFINE(ALT_SYSCALL, 1, [Define to 1 if alternative syscall should be used])
		AC_MSG_RESULT([yes])
	else
		AC_MSG_RESULT([no])
	fi
])
