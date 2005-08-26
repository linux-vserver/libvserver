# set the include path found by configure
INCLUDES = $(all_includes) -I$(top_srcdir)

# the library search path.
include_HEADERS = vserver-util.h

lib_LTLIBRARIES = libvserver-util.la

libvserver_util_la_SOURCES = list.c \
                             bcaps-list.c \
                             ccaps-list.c \
                             cflags-list.c \
                             iattr-list.c \
                             nflags-list.c \
                             personalityflag-list.c \
                             personality-list.c \
                             sched-list.c \
                             vhi-list.c

libvserver_util_la_LDFLAGS = -version-info 0:0:0
