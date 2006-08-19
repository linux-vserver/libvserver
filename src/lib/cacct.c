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
#include "linux/vserver/cacct_cmd.h"

#include "vserver.h"

int vx_get_sock_stat(xid_t xid, struct vx_sock_stat *sock_stat)
{
	struct vcmd_sock_stat_v0 res;

	res.field = sock_stat->field;

	int rc = sys_vserver(VCMD_sock_stat, xid, &res);
	
	if (rc == -1)
		return rc;
	
	sock_stat->count[0] = res.count[0];
	sock_stat->count[1] = res.count[1];
	sock_stat->count[2] = res.count[2];
	
	sock_stat->total[0] = res.total[0];
	sock_stat->total[1] = res.total[1];
	sock_stat->total[2] = res.total[2];
	
	return rc;
}
