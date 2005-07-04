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

int vx_set_sched(xid_t xid, const struct vx_sched *sched)
{
	struct vcmd_set_sched_v3 res;

	if (!sched) {
		errno = EFAULT;
		return -1;
	}

	res.set_mask      = sched->set_mask;
	res.fill_rate     = sched->fill_rate;
	res.interval      = sched->interval;
	res.tokens        = sched->tokens;
	res.tokens_min    = sched->tokens_min;
	res.tokens_max    = sched->tokens_max;
	res.priority_bias = sched->priority_bias;

	return vserver(VCMD_set_sched, xid, &res);
}

