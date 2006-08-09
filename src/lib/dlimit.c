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
#include "linux/vserver/dlimit_cmd.h"

int vx_add_dlimit(xid_t xid, struct vx_dlimit_base *dlimit_base)
{
	struct vcmd_ctx_dlimit_base_v0 res;

	res.name  = dlimit_base->filename;
	res.flags = dlimit_base->flags;

	return sys_vserver(VCMD_add_dlimit, xid, &res);
}

int vx_rem_dlimit(xid_t xid, struct vx_dlimit_base *dlimit_base)
{
	struct vcmd_ctx_dlimit_base_v0 res;

	res.name = dlimit_base->filename;

	return sys_vserver(VCMD_rem_dlimit, xid, &res);
}

int vx_set_dlimit(xid_t xid, struct vx_dlimit *dlimit)
{
	struct vcmd_ctx_dlimit_v0 res;

	res.name         = dlimit->filename;
	res.space_used   = dlimit->space_used;
	res.space_total  = dlimit->space_total;
	res.inodes_used  = dlimit->inodes_used;
	res.inodes_total = dlimit->inodes_total;
	res.reserved     = dlimit->reserved;
	res.flags        = dlimit->flags;

	return sys_vserver(VCMD_set_dlimit, xid, &res);
}

int vx_get_dlimit(xid_t xid, struct vx_dlimit *dlimit)
{
	struct vcmd_ctx_dlimit_v0 res;

	res.name = dlimit->filename;
	int rc = sys_vserver(VCMD_get_dlimit, xid, &res);
	
	if (rc == -1)
		return rc;

	dlimit->space_used   = res.space_used;
	dlimit->space_total  = res.space_total;
	dlimit->inodes_used  = res.inodes_used;
	dlimit->inodes_total = res.inodes_total;
	dlimit->reserved     = res.reserved;
	dlimit->flags        = res.flags;

	return rc;
}
