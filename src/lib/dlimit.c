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

#include "linux/vserver/switch.h"
#include "linux/vserver/dlimit_cmd.h"

#include "vserver.h"

int dx_add_limit(xid_t xid, struct dx_limit *limit)
{
	struct vcmd_ctx_dlimit_base_v0 res;
	
	res.name  = limit->filename;
	res.flags = limit->flags;
	
	return sys_vserver(VCMD_add_dlimit, xid, &res);
}

int dx_rem_limit(xid_t xid, struct dx_limit *limit)
{
	struct vcmd_ctx_dlimit_base_v0 res;
	
	res.name = limit->filename;
	
	return sys_vserver(VCMD_rem_dlimit, xid, &res);
}

int dx_set_limit(xid_t xid, struct dx_limit *limit)
{
	struct vcmd_ctx_dlimit_v0 res;
	
	res.name         = limit->filename;
	res.space_used   = limit->space_used;
	res.space_total  = limit->space_total;
	res.inodes_used  = limit->inodes_used;
	res.inodes_total = limit->inodes_total;
	res.reserved     = limit->reserved;
	res.flags        = limit->flags;
	
	return sys_vserver(VCMD_set_dlimit, xid, &res);
}

int dx_get_limit(xid_t xid, struct dx_limit *limit)
{
	int rc;
	struct vcmd_ctx_dlimit_v0 res;
	
	res.name = limit->filename;
	
	rc = sys_vserver(VCMD_get_dlimit, xid, &res);
	
	if (rc == -1)
		return rc;

	limit->space_used   = res.space_used;
	limit->space_total  = res.space_total;
	limit->inodes_used  = res.inodes_used;
	limit->inodes_total = res.inodes_total;
	limit->reserved     = res.reserved;
	limit->flags        = res.flags;
	
	return rc;
}
