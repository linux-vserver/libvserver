// Copyright 2005-2006 Benedikt Böhm <hollow@gentoo.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the
// Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/sched_cmd.h"

int vx_set_sched(xid_t xid, struct vx_sched *sched)
{
	struct vcmd_set_sched_v3 res3;
	struct vcmd_set_sched_v4 res4;
	
	int version = vs_get_version();
	
	if (version == -1)
		return -1;
	
	if (version >= 0x020100) {
		res4.set_mask      = sched->set_mask;
		res4.fill_rate     = sched->fill_rate;
		res4.interval      = sched->interval;
		res4.tokens        = sched->tokens;
		res4.tokens_min    = sched->tokens_min;
		res4.tokens_max    = sched->tokens_max;
		res4.prio_bias     = sched->prio_bias;
		res4.cpu_id        = sched->cpu_id;
		res4.bucket_id     = sched->bucket_id;
		
		return sys_vserver(VCMD_set_sched, xid, &res4);
	}
	
	else {
		res3.set_mask      = sched->set_mask & VXSM_V3_MASK;
		res3.fill_rate     = sched->fill_rate;
		res3.interval      = sched->interval;
		res3.tokens        = sched->tokens;
		res3.tokens_min    = sched->tokens_min;
		res3.tokens_max    = sched->tokens_max;
		res3.priority_bias = sched->prio_bias;
		
		return sys_vserver(VCMD_set_sched_v3, xid, &res3);
	}
}
