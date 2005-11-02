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

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/network_cmd.h"

int vc_get_task_nid(pid_t pid)
{
	return sys_vserver(VCMD_task_nid, pid, 0);
}

int vc_get_nx_info(nid_t nid, struct vc_nx_info *info)
{
	struct vcmd_nx_info_v0 res;
	
	int rc = sys_vserver(VCMD_nx_info, nid, &res);
	if (rc == -1) return -1;
	
	info->nid = res.nid;
	
	return rc;
}

int vc_net_create(nid_t nid)
{
	return sys_vserver(VCMD_net_create, nid, 0);
}

int vc_net_migrate(nid_t nid)
{
	return sys_vserver(VCMD_net_migrate, nid, 0);
}

int vc_net_add(nid_t nid, struct vc_net_nx const *info)
{
	struct vcmd_net_addr_v0 res;
	
	res.type  = info->type;
	res.count = info->count;
	
	return sys_vserver(VCMD_net_add, nid, &res);
}

int vc_net_remove(nid_t nid, struct vc_net_nx const *info)
{
	struct vcmd_net_addr_v0 res;
	
	res.type  = info->type;
	res.count = info->count;
	
	return sys_vserver(VCMD_net_remove, nid, &res);
}

int vc_get_nflags(nid_t nid, struct vc_net_flags *flags)
{
	struct vcmd_net_flags_v0 res;
	
	int rc = sys_vserver(VCMD_get_nflags, nid, &res);
	
	flags->flagword = res.flagword;
	flags->mask     = res.mask;
	
	return rc;
}

int vc_set_nflags(nid_t nid, struct vc_net_flags const *flags)
{
	struct vcmd_net_flags_v0 res;
	
	res.flagword = flags->flagword;
	res.mask     = flags->mask;
	
	return sys_vserver(VCMD_set_nflags, nid, &res);
}

int vc_get_ncaps(nid_t nid, struct vc_net_caps *caps)
{
	struct vcmd_net_caps_v0 res;
	
	int rc = sys_vserver(VCMD_get_ncaps, nid, &res);
	
	caps->ncaps = res.ncaps;
	caps->cmask = res.cmask;
	
	return rc;
}

int vc_set_ncaps(nid_t nid, struct vc_net_caps const *caps)
{
	struct vcmd_net_caps_v0 res;
	
	res.ncaps = caps->ncaps;
	res.cmask = caps->cmask;
	
	return sys_vserver(VCMD_set_ncaps, nid, &res);
}
