## Copyright 2005-2006 Benedikt Böhm <hollow@gentoo.org>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the
## Free Software Foundation, Inc.,
## 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

SUBDIRS = src

noinst_HEADERS = linux/vserver/cacct_cmd.h \
                 linux/vserver/context_cmd.h \
                 linux/vserver/cvirt_cmd.h \
                 linux/vserver/debug_cmd.h \
                 linux/vserver/dlimit_cmd.h \
                 linux/vserver/inode_cmd.h \
                 linux/vserver/limit_cmd.h \
                 linux/vserver/monitor.h \
                 linux/vserver/network_cmd.h \
                 linux/vserver/sched_cmd.h \
                 linux/vserver/signal_cmd.h \
                 linux/vserver/space_cmd.h \
                 linux/vserver/switch.h \
                 linux/capability.h \
                 linux/sched.h

include aminclude.am

MOSTLYCLEANFILES = $(DX_CLEANFILES)
EXTRA_DIST = $(DX_CONFIG)

dist-hook: doxygen-doc
	rm -rf $(top_builddir)/$(DX_DOCDIR)/latex \
	       $(top_builddir)/$(DX_DOCDIR)/lucid.tag \
	       $(top_builddir)/$(DX_DOCDIR)/html/*.md5 \
	       $(top_builddir)/$(DX_DOCDIR)/html/*.map \
	       $(top_builddir)/$(DX_DOCDIR)/html/*.dot
	mv $(top_builddir)/$(DX_DOCDIR) $(distdir)/
