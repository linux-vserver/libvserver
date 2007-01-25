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

#include <errno.h>

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/sched_cmd.h"

int vx_sched_get(xid_t xid, vx_sched_t *data)
{
	struct vcmd_sched_v5 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.cpu_id    = data->cpu_id;
	kdata.bucket_id = data->bucket_id;
	kdata.mask      = data->mask;

	int rc = sys_vserver(VCMD_get_sched, xid, &kdata);

	if (rc == -1)
		return -1;

	data->fill_rate[0] = kdata.fill_rate[0];
	data->fill_rate[1] = kdata.fill_rate[1];
	data->interval[0]  = kdata.interval[0];
	data->interval[1]  = kdata.interval[1];
	data->tokens       = kdata.tokens;
	data->tokens_min   = kdata.tokens_min;
	data->tokens_max   = kdata.tokens_max;
	data->prio_bias    = kdata.prio_bias;

	return rc;
}

int vx_sched_set(xid_t xid, vx_sched_t *data)
{
	struct vcmd_sched_v5 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.mask         = data->mask;
	kdata.cpu_id       = data->cpu_id;
	kdata.fill_rate[0] = data->fill_rate[0];
	kdata.fill_rate[1] = data->fill_rate[1];
	kdata.interval[0]  = data->interval[0];
	kdata.interval[1]  = data->interval[1];
	kdata.tokens       = data->tokens;
	kdata.tokens_min   = data->tokens_min;
	kdata.tokens_max   = data->tokens_max;
	kdata.prio_bias    = data->prio_bias;

	return sys_vserver(VCMD_set_sched, xid, &kdata);
}

int vx_sched_info(xid_t xid, vx_sched_info_t *data)
{
	struct vcmd_sched_info kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.cpu_id = data->cpu_id;
	kdata.bucket_id = data->bucket_id;

	int rc = sys_vserver(VCMD_sched_info, xid, &kdata);

	if (rc == -1)
		return -1;

	data->user_msec  = kdata.user_msec;
	data->sys_msec   = kdata.sys_msec;
	data->hold_msec  = kdata.hold_msec;
	data->token_usec = kdata.token_usec;
	data->vavavoom   = kdata.vavavoom;

	return rc;
}
