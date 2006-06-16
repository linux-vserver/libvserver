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
#include "linux/vserver/inode_cmd.h"

int vx_set_iattr(struct vx_iattr *iattr)
{
	struct vcmd_ctx_iattr_v1 res;

	res.name  = iattr->filename;
	res.xid   = iattr->xid;
	res.flags = iattr->flags;
	res.mask  = iattr->mask;

	return sys_vserver(VCMD_set_iattr, 0, &res);
}

int vx_get_iattr(struct vx_iattr *iattr)
{
	struct vcmd_ctx_iattr_v1 res;

	res.name = iattr->filename;
	int rc = sys_vserver(VCMD_get_iattr, 0, &res);
	
	if (rc == -1)
		return rc;

	iattr->xid   = res.xid;
	iattr->flags = res.flags;
	iattr->mask  = res.mask;

	return rc;
}
