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

#include "vserver.h"
#include <linux/capability.h>

#include <stdlib.h>

LIST_DATA_ALLOC_TYPE(bcaps, uint64_t)

/*!
 * @brief Macro for bcaps list allocation
 * @ingroup list_defaults
 */
#define LIST_ADD_BCAP(TYPE, VALUE) \
list_set(p->node+(i++), \
         list_key_alloc(#VALUE), \
         bcaps_list_data_alloc(TYPE ## _ ## VALUE));
	
list_t *bcaps_list_init(void)
{
	list_t *p = list_alloc(30);
	
	int i = 0;
	LIST_ADD_BCAP(CAP, CHOWN)
	LIST_ADD_BCAP(CAP, DAC_OVERRIDE)
	LIST_ADD_BCAP(CAP, DAC_READ_SEARCH)
	LIST_ADD_BCAP(CAP, FOWNER)
	LIST_ADD_BCAP(CAP, FSETID)
	LIST_ADD_BCAP(CAP, FS_MASK)
	LIST_ADD_BCAP(CAP, KILL)
	LIST_ADD_BCAP(CAP, SETGID)
	LIST_ADD_BCAP(CAP, SETUID)
	LIST_ADD_BCAP(CAP, SETPCAP)
	LIST_ADD_BCAP(CAP, LINUX_IMMUTABLE)
	LIST_ADD_BCAP(CAP, NET_BIND_SERVICE)
	LIST_ADD_BCAP(CAP, NET_BROADCAST)
	LIST_ADD_BCAP(CAP, NET_ADMIN)
	LIST_ADD_BCAP(CAP, NET_RAW)
	LIST_ADD_BCAP(CAP, IPC_LOCK)
	LIST_ADD_BCAP(CAP, IPC_OWNER)
	LIST_ADD_BCAP(CAP, SYS_MODULE)
	LIST_ADD_BCAP(CAP, SYS_RAWIO)
	LIST_ADD_BCAP(CAP, SYS_CHROOT)
	LIST_ADD_BCAP(CAP, SYS_PTRACE)
	LIST_ADD_BCAP(CAP, SYS_PACCT)
	LIST_ADD_BCAP(CAP, SYS_ADMIN)
	LIST_ADD_BCAP(CAP, SYS_BOOT)
	LIST_ADD_BCAP(CAP, SYS_NICE)
	LIST_ADD_BCAP(CAP, SYS_RESOURCE)
	LIST_ADD_BCAP(CAP, SYS_TIME)
	LIST_ADD_BCAP(CAP, SYS_TTY_CONFIG)
	LIST_ADD_BCAP(CAP, MKNOD)
	LIST_ADD_BCAP(CAP, LEASE)
	
	return p;
}
