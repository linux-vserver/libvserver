AC_DEFUN([VS_CHECK_KERNEL_HEADERS],
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
	elif test $kernel_version -lt 132620; then
		AC_MSG_ERROR([You need at least linux headers 2.6.12])
	else
		AC_MSG_RESULT([ok])
	fi
	
	AC_LANG_POP
])
