# Generic configuration
AC_PREREQ(2.59)
AC_INIT(libvserver, 0.2, [http://dev.croup.de/proj/libvserver])
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
AC_PROG_LIBTOOL
AC_PROG_EGREP

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([stdint.h unistd.h])

# Checks for typedefs
AC_CHECK_TYPES([uid_t,
                gid_t,
                pid_t,
                size_t])

# Checks for compiler characteristics.
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strpbrk])

# Compiler settings
CFLAGS="${CFLAGS} -W -Wall -std=c99 -pedantic"

# Site settings
VS_CHECK_SYSCALL_NR
VS_ENABLE_DIETLIBC


# Output
AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 tools/Makefile])
AC_OUTPUT
