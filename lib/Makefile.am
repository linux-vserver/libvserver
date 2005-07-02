# set the include path found by configure
INCLUDES = $(all_includes) -I$(top_srcdir)

# the library search path.
include_HEADERS = libvserver.h

lib_LIBRARIES = libvserver.a
libvserver_a_SOURCES = context.c cvirt.c dlimit.c inode.c limit.c namespace.c network.c \
	sched.c signal.c switch.c
