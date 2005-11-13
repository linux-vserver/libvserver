# Copyright 2005 The libvserver Developers
# See AUTHORS for details
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by  *
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the
# Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

INCLUDES = -I$(top_srcdir)

noinst_HEADERS = syscall.h
include_HEADERS = vserver.h

lib_LTLIBRARIES = libvserver.la

libvserver_la_SOURCES = bcaps-list.c \
                        ccaps-list.c \
                        cflags-list.c \
                        context.c \
                        cvirt.c \
                        debug.c \
                        dlimit.c \
                        iattr-list.c \
                        inode.c \
                        limit.c \
                        list.c \
                        namespace.c \
                        network.c \
                        nflags-list.c \
                        personalityflag-list.c \
                        personality-list.c \
                        rlimit-list.c \
                        sched-list.c \
                        sched.c \
                        signal.c \
                        switch.c \
                        syscall.c \
                        vhi-list.c

libvserver_la_LDFLAGS = -version-info 1:0:0 \
                        -Wl,--version-script,$(srcdir)/versions -Wl,-O1 \
                        -export-dynamic
