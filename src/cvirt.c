// Copyright 2005 The util-vserver Developers
// See AUTHORS for details
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by  *
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
#  include <config.h>
#endif

#include <string.h>
#include <errno.h>

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/cvirt_cmd.h"

int vc_set_vhi_name(xid_t xid, vc_uts_type type, char const *val, size_t len)
{
	struct vcmd_vhi_name_v0 res;
	
	if (len == (size_t)(-1)) len = strlen(val);
	
	if (len >= sizeof(res.name)) {
		errno = E2BIG;
		return -1;
	}
	
	res.field = type;
	memcpy(res.name, val, len);
	res.name[len] = '\0';
	
	return sys_vserver(VCMD_set_vhi_name, xid, &res);
}

int vc_get_vhi_name(xid_t xid, vc_uts_type type, char *val, size_t len)
{
	struct vcmd_vhi_name_v0 res;
	
	res.field = type;
	int rc = sys_vserver(VCMD_get_vhi_name, xid, &res);
	
	if (rc == -1) return -1;
	
	memcpy(val, res.name, len);
	
	return rc;
}
