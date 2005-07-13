# set the include path found by configure
INCLUDES = $(all_includes) -I$(top_srcdir)

# the library search path.
include_HEADERS = vserver.h

lib_LTLIBRARIES = libvserver.la
libvserver_la_SOURCES = context.c cvirt.c dlimit.c inode.c limit.c namespace.c \
	network.c sched.c signal.c switch.c syscall.h syscall-vserver.h
libvserver_la_LDFLAGS = -version-info 0:2:0
