# set the include path found by configure
INCLUDES = $(all_includes) -I$(top_srcdir)

# the library search path.
noinst_HEADERS = syscall.h
include_HEADERS = vserver.h

lib_LTLIBRARIES = libvserver.la

libvserver_la_SOURCES = context.c \
                        cvirt.c \
                        debug.c \
                        dlimit.c \
                        inode.c \
                        limit.c \
                        namespace.c \
                        network.c \
                        sched.c \
                        signal.c \
                        switch.c \
                        syscall.c

libvserver_la_LDFLAGS = -version-info 1:0:0 \
                        -Wl,--version-script,$(srcdir)/versions -Wl,-O1 \
                        -export-dynamic
