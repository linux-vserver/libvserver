# set the include path found by configure
INCLUDES = $(all_includes) -I$(top_srcdir)

# the library search path.
noinst_HEADERS = list.h
include_HEADERS = vserver-util.h

lib_LTLIBRARIES = libvserver-util.la

libvserver_util_la_SOURCES = bcaps-list.c \
                             ccaps-list.c \
                             cflags-list.c \
                             flagparser.c \
                             iattr-list.c \
                             nflags-list.c

libvserver_util_la_LDFLAGS = -version-info 0:0:0
