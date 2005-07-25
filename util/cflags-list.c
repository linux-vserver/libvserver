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

#include "linux/vserver/context.h"
#include "vserver-util.h"

#include "list.h"

LIST_DECL(cflags, uint64_t)

LIST_START(cflags)

LIST_ENTRY(VXF, INFO_LOCK)
LIST_ENTRY(VXF, INFO_SCHED)
LIST_ENTRY(VXF, INFO_NPROC)
LIST_ENTRY(VXF, INFO_PRIVATE)

LIST_ENTRY(VXF, INFO_INIT)
LIST_ENTRY(VXF, INFO_HIDE)
LIST_ENTRY(VXF, INFO_ULIMIT)
LIST_ENTRY(VXF, INFO_NSPACE)

LIST_ENTRY(VXF, SCHED_HARD)
LIST_ENTRY(VXF, SCHED_PRIO)
LIST_ENTRY(VXF, SCHED_PAUSE)

LIST_ENTRY(VXF, VIRT_MEM)
LIST_ENTRY(VXF, VIRT_UPTIME)
LIST_ENTRY(VXF, VIRT_CPU)
LIST_ENTRY(VXF, VIRT_LOAD)

LIST_ENTRY(VXF, HIDE_MOUNT)
LIST_ENTRY(VXF, HIDE_NETIF)

LIST_ENTRY(VXF, STATE_SETUP)
LIST_ENTRY(VXF, STATE_INIT)

LIST_ENTRY(VXF, STATE_HELPER)

LIST_ENTRY(VXF, FORK_RSS)
LIST_ENTRY(VXF, PROLIFIC)

LIST_ENTRY(VXF, IGNEG_NICE)

LIST_ENTRY(VXF, ONE_TIME)

LIST_ENTRY(VXF, INIT_SET)

LIST_END(cflags)

LIST_CMP_HANDLER(cflags)

LIST_SEARCH(cflags, uint64_t)

LIST_FLAGPARSER(cflags, uint64_t)
