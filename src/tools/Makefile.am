## Copyright 2006 Benedikt Böhm <hollow@gentoo.org>
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

if ENABLE_TOOLS

INCLUDES = -I$(top_srcdir)/src/lib

noinst_HEADERS = tools.h

man_MANS = dx.8 \
           ix.8 \
           ns.8 \
           nx.8 \
           vr.8 \
           vx.8

EXTRA_DIST = $(man_MANS)

sbin_PROGRAMS = dx \
                ix \
                ns \
                nx \
                vr \
                vx

TOOLLIBS = $(LUCID_LIBS) \
           $(top_builddir)/src/lib/libvserver.la

dx_SOURCES = dx.c msg.c
dx_LDADD = $(TOOLLIBS)

ix_SOURCES = ix.c msg.c lists.c
ix_LDADD = $(TOOLLIBS)

ns_SOURCES = ns.c msg.c
ns_LDADD = $(TOOLLIBS)

nx_SOURCES = nx.c msg.c lists.c
nx_LDADD = $(TOOLLIBS)

vr_SOURCES = vr.c msg.c
vr_LDADD = $(TOOLLIBS)

vx_SOURCES = vx.c msg.c lists.c
vx_LDADD = $(TOOLLIBS)

endif
