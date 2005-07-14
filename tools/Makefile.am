INCLUDES = -I$(top_srcdir)/lib -I$(top_srcdir)
METASOURCES = AUTO

sbin_PROGRAMS = vcontext vnamespace vlimit vsched vnetwork vdlimit vinfo vsignal vuname

noinst_HEADERS = tools.h

vcontext_SOURCES = vcontext.c
vcontext_LDADD = $(top_builddir)/lib/libvserver.la

vnamespace_SOURCES = vnamespace.c
vnamespace_LDADD = $(top_builddir)/lib/libvserver.la

vlimit_SOURCES = vlimit.c
vlimit_LDADD = $(top_builddir)/lib/libvserver.la

vsched_SOURCES = vsched.c
vsched_LDADD = $(top_builddir)/lib/libvserver.la

vnetwork_SOURCES = vnetwork.c
vnetwork_LDADD = $(top_builddir)/lib/libvserver.la

vdlimit_SOURCES = vdlimit.c
vdlimit_LDADD = $(top_builddir)/lib/libvserver.la

vinfo_SOURCES = vinfo.c
vinfo_LDADD = $(top_builddir)/lib/libvserver.la

vsignal_SOURCES = vsignal.c
vsignal_LDADD = $(top_builddir)/lib/libvserver.la

vuname_SOURCES = vuname.c
vuname_LDADD = $(top_builddir)/lib/libvserver.la
