/***************************************************************************
 *   Copyright 2005 The libvserver Team                                    *
 *   See AUTHORS for details                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <linux/capability.h>

#include "vserver-util.h"
#include "list.h"

LIST_DECL(bcaps)

LIST_START(bcaps)

LIST_ENTRY(CAP, CHOWN)
LIST_ENTRY(CAP, DAC_OVERRIDE)
LIST_ENTRY(CAP, DAC_READ_SEARCH)
LIST_ENTRY(CAP, FOWNER)
LIST_ENTRY(CAP, FSETID)
LIST_ENTRY(CAP, FS_MASK)
LIST_ENTRY(CAP, KILL)
LIST_ENTRY(CAP, SETGID)
LIST_ENTRY(CAP, SETUID)
LIST_ENTRY(CAP, SETPCAP)
LIST_ENTRY(CAP, LINUX_IMMUTABLE)
LIST_ENTRY(CAP, NET_BIND_SERVICE)
LIST_ENTRY(CAP, NET_BROADCAST)
LIST_ENTRY(CAP, NET_ADMIN)
LIST_ENTRY(CAP, NET_RAW)
LIST_ENTRY(CAP, IPC_LOCK)
LIST_ENTRY(CAP, IPC_OWNER)
LIST_ENTRY(CAP, SYS_MODULE)
LIST_ENTRY(CAP, SYS_RAWIO)
LIST_ENTRY(CAP, SYS_CHROOT)
LIST_ENTRY(CAP, SYS_PTRACE)
LIST_ENTRY(CAP, SYS_PACCT)
LIST_ENTRY(CAP, SYS_ADMIN)
LIST_ENTRY(CAP, SYS_BOOT)
LIST_ENTRY(CAP, SYS_NICE)
LIST_ENTRY(CAP, SYS_RESOURCE)
LIST_ENTRY(CAP, SYS_TIME)
LIST_ENTRY(CAP, SYS_TTY_CONFIG)
LIST_ENTRY(CAP, MKNOD)
LIST_ENTRY(CAP, LEASE)
LIST_ENTRY(CAP, AUDIT_WRITE)
LIST_ENTRY(CAP, AUDIT_CONTROL)

LIST_END(bcaps)

LIST_CMP_HANDLER(bcaps)

LIST_SEARCH(bcaps)

LIST_FLAGPARSER(bcaps)
