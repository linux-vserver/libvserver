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
#include "linux/vserver/network_cmd.h"

#include "vserver.h"

int nx_create(nid_t nid, struct nx_flags *flags)
{
	struct vcmd_net_create res = {
		.flagword = 0,
	};
	
	if (flags != NULL)
		res.flagword = flags->flags;
	
	return sys_vserver(VCMD_net_create, nid, &res);
}

int nx_migrate(nid_t nid)
{
	return sys_vserver(VCMD_net_migrate, nid, NULL);
}

int nx_get_task_nid(pid_t pid)
{
	return sys_vserver(VCMD_task_nid, pid, NULL);
}

int nx_get_info(nid_t nid, struct nx_info *info)
{
	struct vcmd_nx_info_v0 res;
	
	int rc = sys_vserver(VCMD_nx_info, nid, &res);

	if (rc == -1)
		return rc;

	if (info != NULL)
		info->nid = res.nid;

	return rc;
}

int nx_add_addr(nid_t nid, struct nx_addr *addr)
{
	struct vcmd_net_addr_v0 res;

	res.type = addr->type;
	res.count = addr->count;
	memcpy(res.ip, addr->ip, sizeof res.ip);
	memcpy(res.mask, addr->mask, sizeof res.mask);

	return sys_vserver(VCMD_net_add, nid, &res);
}

int nx_rem_addr(nid_t nid, struct nx_addr *addr)
{
	struct vcmd_net_addr_v0 res;

	res.type = addr->type;
	res.count = addr->count;
	memcpy(res.ip, addr->ip, sizeof res.ip);
	memcpy(res.mask, addr->mask, sizeof res.mask);

	return sys_vserver(VCMD_net_remove, nid, &res);
}

int nx_set_flags(nid_t nid, struct nx_flags *flags)
{
	struct vcmd_net_flags_v0 res;

	res.flagword = flags->flags;
	res.mask     = flags->mask;

	return sys_vserver(VCMD_set_nflags, nid, &res);
}

int nx_get_flags(nid_t nid, struct nx_flags *flags)
{
	struct vcmd_net_flags_v0 res;
	
	int rc = sys_vserver(VCMD_get_nflags, nid, &res);

	if (rc == -1)
		return rc;

	flags->flags = res.flagword;
	flags->mask  = res.mask;

	return rc;
}

int nx_set_caps(nid_t nid, struct nx_caps *caps)
{
	struct vcmd_net_caps_v0 res;

	res.ncaps = caps->caps;
	res.cmask = caps->mask;

	return sys_vserver(VCMD_get_ncaps, nid, &res);
}

int nx_get_caps(nid_t nid, struct nx_caps *caps)
{
	struct vcmd_net_caps_v0 res;
	
	int rc = sys_vserver(VCMD_get_ncaps, nid, &res);

	if (rc == -1)
		return rc;

	caps->caps = res.ncaps;
	caps->mask = res.cmask;

	return rc;
}

int nx_get_sock_stat(nid_t nid, struct nx_sock_stat *stat)
{
	struct vcmd_sock_stat_v0 res;

	res.field = stat->id;

	int rc = sys_vserver(VCMD_sock_stat, nid, &res);
	
	if (rc == -1)
		return rc;
	
	stat->count[0] = res.count[0];
	stat->count[1] = res.count[1];
	stat->count[2] = res.count[2];
	
	stat->total[0] = res.total[0];
	stat->total[1] = res.total[1];
	stat->total[2] = res.total[2];
	
	return rc;
}
