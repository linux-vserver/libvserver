AC_DEFUN([ENABLE_ALT_SYSCALL],
[
	AC_MSG_CHECKING([whether to use alternative syscall])
	
	AC_ARG_ENABLE([alt-syscall],
	              AC_HELP_STRING([--disable-alt-syscall],
	                             [use alternative syscall (default: yes)]),
	              [enable_alt_syscall=no],
	              [enable_alt_syscall=yes])
	
	if test "$enable_alt_syscall" = yes; then
		AC_DEFINE(ALT_SYSCALL, 1, [Define to 1 if alternative syscall should be used])
		AC_MSG_RESULT([yes])
	else
		AC_MSG_RESULT([no])
	fi
])
