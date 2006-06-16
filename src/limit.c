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

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/limit_cmd.h"

int vx_set_rlimit(xid_t xid, struct vx_rlimit *rlimit)
{
	struct vcmd_ctx_rlimit_v0 res;

	res.id        = rlimit->id;
	res.minimum   = rlimit->minimum;
	res.softlimit = rlimit->softlimit;
	res.maximum   = rlimit->maximum;

	return sys_vserver(VCMD_set_rlimit, xid, &res);
}

int vx_get_rlimit(xid_t xid, struct vx_rlimit *rlimit)
{
	struct vcmd_ctx_rlimit_v0 res;

	res.id = rlimit->id;
	int rc = sys_vserver(VCMD_get_rlimit, xid, &res);
	
	if (rc == -1)
		return rc;

	rlimit->minimum   = res.minimum;
	rlimit->softlimit = res.softlimit;
	rlimit->maximum   = res.maximum;

	return rc;
}

int vx_get_rlimit_mask(struct vx_rlimit_mask *rmask)
{
	struct vcmd_ctx_rlimit_mask_v0 res;
	
	int rc = sys_vserver(VCMD_get_rlimit_mask, 0, &res);

	if (rc == -1)
		return rc;

	rmask->minimum   = res.minimum;
	rmask->softlimit = res.softlimit;
	rmask->maximum   = res.maximum;

	return rc;
}
