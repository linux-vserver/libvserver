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

#include "vserver-util.h"
#include <linux/capability.h>

LIST_DATA_ALLOC_TYPE(bcaps, uint64_t)

#define LIST_ADD(TYPE, VALUE) \
list_set(p->node+(i++), \
         list_key_alloc(#VALUE), \
         bcaps_list_data_alloc(TYPE ## _ ## VALUE));
	
list_t *bcaps_list_init()
{
	size_t np      = 32;
	list_t *p = list_alloc(np);
	
	int i = 0;
	
	LIST_ADD(CAP, CHOWN)
	LIST_ADD(CAP, DAC_OVERRIDE)
	LIST_ADD(CAP, DAC_READ_SEARCH)
	LIST_ADD(CAP, FOWNER)
	LIST_ADD(CAP, FSETID)
	LIST_ADD(CAP, FS_MASK)
	LIST_ADD(CAP, KILL)
	LIST_ADD(CAP, SETGID)
	LIST_ADD(CAP, SETUID)
	LIST_ADD(CAP, SETPCAP)
	LIST_ADD(CAP, LINUX_IMMUTABLE)
	LIST_ADD(CAP, NET_BIND_SERVICE)
	LIST_ADD(CAP, NET_BROADCAST)
	LIST_ADD(CAP, NET_ADMIN)
	LIST_ADD(CAP, NET_RAW)
	LIST_ADD(CAP, IPC_LOCK)
	LIST_ADD(CAP, IPC_OWNER)
	LIST_ADD(CAP, SYS_MODULE)
	LIST_ADD(CAP, SYS_RAWIO)
	LIST_ADD(CAP, SYS_CHROOT)
	LIST_ADD(CAP, SYS_PTRACE)
	LIST_ADD(CAP, SYS_PACCT)
	LIST_ADD(CAP, SYS_ADMIN)
	LIST_ADD(CAP, SYS_BOOT)
	LIST_ADD(CAP, SYS_NICE)
	LIST_ADD(CAP, SYS_RESOURCE)
	LIST_ADD(CAP, SYS_TIME)
	LIST_ADD(CAP, SYS_TTY_CONFIG)
	LIST_ADD(CAP, MKNOD)
	LIST_ADD(CAP, LEASE)
	LIST_ADD(CAP, AUDIT_WRITE)
	LIST_ADD(CAP, AUDIT_CONTROL)
	
	return p;
}
