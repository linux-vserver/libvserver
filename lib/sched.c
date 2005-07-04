/***************************************************************************
 *   Copyright 2005 by the libvserver team                                 *
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

#include "syscall-vserver.h"
#include "linux/vserver/switch.h"
#include "linux/vserver/sched_cmd.h"

#include "vserver.h"

int vc_set_sched_v2(xid_t xid, struct vcmd_set_sched_v2 *sched)
{
	if (sched == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_sched_v2, xid, sched);
	return rc;
}

int vc_set_sched(xid_t xid, struct vcmd_set_sched_v3 *sched)
{
	if (sched == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_sched, xid, sched);
	return rc;
}

