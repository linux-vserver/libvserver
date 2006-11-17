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

int vx_sched_set(xid_t xid, vx_sched_t *data)
{
	struct vcmd_set_sched_v3 kdata3;
	struct vcmd_set_sched_v4 kdata4;
	
	int version = vs_get_version();
	
	if (version == -1)
		return -1;
	
	if (version >= 0x020100) {
		kdata4.set_mask      = data->set_mask;
		kdata4.fill_rate     = data->fill_rate;
		kdata4.interval      = data->interval;
		kdata4.tokens        = data->tokens;
		kdata4.tokens_min    = data->tokens_min;
		kdata4.tokens_max    = data->tokens_max;
		kdata4.prio_bias     = data->prio_bias;
		kdata4.cpu_id        = data->cpu_id;
		kdata4.bucket_id     = data->bucket_id;
		
		return sys_vserver(VCMD_set_sched, xid, &kdata4);
	}
	
	else {
		kdata3.set_mask      = data->set_mask & VXSM_V3_MASK;
		kdata3.fill_rate     = data->fill_rate;
		kdata3.interval      = data->interval;
		kdata3.tokens        = data->tokens;
		kdata3.tokens_min    = data->tokens_min;
		kdata3.tokens_max    = data->tokens_max;
		kdata3.priority_bias = data->prio_bias;
		
		return sys_vserver(VCMD_set_sched_v3, xid, &kdata3);
	}
}
