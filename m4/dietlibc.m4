AC_DEFUN([VS_ENABLE_DIETLIBC],
[
	AC_MSG_CHECKING([whether to use dietlibc])
	
	AC_ARG_VAR(DIET,      [The dietlibc wrapper command (default: diet)])
	AC_ARG_VAR(DIETFLAGS, [Flags to the dietlibc wrapper (default: -Os)])
	
	: ${DIET:=diet}
	: ${DIETFLAGS:=-Os}
	
	AC_ARG_ENABLE([dietlibc],
	              AC_HELP_STRING([--enable-dietlibc],
	                             [use dietlibc (default: no)]),
	              [enable_dietlibc=yes],
	              [enable_dietlibc=no])
	
	if test "$enable_dietlibc" = yes; then
		dietlibc_version=$($DIET 2>&1 | head -n1)
		dietlibc_version=${dietlibc_version/*dietlibc-}
		AC_DEFINE(DIETLIBC_VERSION, [$dietlibc_version], [Dietlibc version found on this system])
		
		CC="${DIET} ${DIETFLAGS} ${CC}"
		
		AC_MSG_RESULT([yes ($dietlibc_version)])
	else
		AC_MSG_RESULT([no])
	fi
])
