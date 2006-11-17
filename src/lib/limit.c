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

#include <stdint.h>
#include <errno.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/limit_cmd.h"

#include "vserver.h"

int vx_limit_mask_get(vx_limit_t *data)
{
	int rc;
	struct vcmd_ctx_rlimit_mask_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	rc = sys_vserver(VCMD_get_rlimit_mask, 0, &kdata);
	
	if (rc == -1)
		return rc;
	
	data->minimum   = kdata.minimum;
	data->softlimit = kdata.softlimit;
	data->maximum   = kdata.maximum;
	
	return rc;
}

int vx_limit_set(xid_t xid, vx_limit_t *data)
{
	struct vcmd_ctx_rlimit_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	kdata.id        = data->id;
	kdata.minimum   = data->minimum;
	kdata.softlimit = data->softlimit;
	kdata.maximum   = data->maximum;
	
	return sys_vserver(VCMD_set_rlimit, xid, &kdata);
}

int vx_limit_get(xid_t xid, vx_limit_t *data)
{
	int rc;
	struct vcmd_ctx_rlimit_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	kdata.id = data->id;
	
	rc = sys_vserver(VCMD_get_rlimit, xid, &kdata);
	
	if (rc == -1)
		return rc;
	
	data->minimum   = kdata.minimum;
	data->softlimit = kdata.softlimit;
	data->maximum   = kdata.maximum;
	
	return rc;
}

int vx_limit_stat(xid_t xid, vx_limit_stat_t *data)
{
	int rc;
	struct vcmd_rlimit_stat_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	kdata.id = data->id;
	
	rc = sys_vserver(VCMD_rlimit_stat, xid, &kdata);
	
	if (rc == -1)
		return rc;
	
	data->hits    = kdata.hits;
	data->value   = kdata.value;
	data->minimum = kdata.minimum;
	data->maximum = kdata.maximum;
	
	return rc;
}

int vx_limit_reset(xid_t xid)
{
	return sys_vserver(VCMD_reset_minmax, xid, NULL);
}
