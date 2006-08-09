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
#include <string.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/cvirt_cmd.h"

#include "vserver.h"

int vx_set_vhi_name(xid_t xid, struct vx_vhi_name *vhi_name)
{
	struct vcmd_vhi_name_v0 res;

	res.field = vhi_name->field;
	memcpy(res.name, vhi_name->name, sizeof res.name);

	return sys_vserver(VCMD_set_vhi_name, xid, &res);
}

int vx_get_vhi_name(xid_t xid, struct vx_vhi_name *vhi_name)
{
	struct vcmd_vhi_name_v0 res;

	res.field = vhi_name->field;
	int rc = sys_vserver(VCMD_get_vhi_name, xid, &res);
	
	if (rc == -1)
		return rc;

	memcpy(vhi_name->name, res.name, sizeof vhi_name->name);

	return rc;
}
