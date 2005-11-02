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
#include "linux/vserver/context_cmd.h"

int vc_get_task_xid(pid_t pid)
{
	return sys_vserver(VCMD_task_xid, pid, 0);
}

int vc_get_vx_info(xid_t xid, struct vc_vx_info *info)
{
	if (xid == 0 || xid == 1) {
		info->xid     = xid;
		info->initpid = -1;
		
		return 0;
	}
	
	struct vcmd_vx_info_v0 res;
	
	int rc = sys_vserver(VCMD_vx_info, xid, &res);
	
	if (rc == -1)
		return rc;
	
	info->xid     = res.xid;
	info->initpid = res.initpid;
	
	return rc;
}

int vc_ctx_create(xid_t xid)
{
	return sys_vserver(VCMD_ctx_create_v0, xid, 0);
}

int vc_ctx_migrate(xid_t xid)
{
	return sys_vserver(VCMD_ctx_migrate, xid, 0);
}

int vc_get_cflags(xid_t xid, struct vc_ctx_flags *flags)
{
	struct vcmd_ctx_flags_v0 res;
	
	int rc = sys_vserver(VCMD_get_cflags, xid, &res);
	
	flags->flagword = res.flagword;
	flags->mask     = res.mask;
	
	return rc;
}

int vc_set_cflags(xid_t xid, struct vc_ctx_flags const *flags)
{
	struct vcmd_ctx_flags_v0 res;
	
	res.flagword = flags->flagword;
	res.mask     = flags->mask;
	
	return sys_vserver(VCMD_set_cflags, xid, &res);
}

int vc_get_ccaps(xid_t xid, struct vc_ctx_caps *caps)
{
	struct vcmd_ctx_caps_v0 res;
	
	int rc = sys_vserver(VCMD_get_ccaps, xid, &res);
	
	caps->bcaps = res.bcaps;
	caps->bmask = ~0ull;
	caps->ccaps = res.ccaps;
	caps->cmask = res.cmask;
	
	return rc;
}

int vc_set_ccaps(xid_t xid, struct vc_ctx_caps const *caps)
{
	struct vcmd_ctx_caps_v0 res;
	
	res.bcaps = caps->bcaps & caps->bmask;
	res.ccaps = caps->ccaps;
	res.cmask = caps->cmask;
	
	return sys_vserver(VCMD_set_ccaps, xid, &res);
}
