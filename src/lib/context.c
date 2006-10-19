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
#include "linux/vserver/context_cmd.h"

int vx_get_task_xid(pid_t pid)
{
	return sys_vserver(VCMD_task_xid, pid, NULL);
}

int vx_get_info(xid_t xid, struct vx_info *info)
{
	struct vcmd_vx_info_v0 res;

	int rc = sys_vserver(VCMD_vx_info, xid, &res);

	if (rc == -1)
		return rc;

	if (info != NULL) {
		info->xid     = res.xid;
		info->initpid = res.initpid;
	}

	return rc;
}

int vx_get_stat(xid_t xid, struct vx_stat *stat)
{
	struct vcmd_ctx_stat_v0 res;

	int rc = sys_vserver(VCMD_ctx_stat, xid, &res);

	if (rc == -1)
		return rc;

	if (stat != NULL) {
		stat->usecnt = res.usecnt;
		stat->tasks  = res.tasks;
	}

	return rc;
}

int vx_create(xid_t xid, struct vx_create_flags *create_flags)
{
	struct vcmd_ctx_create res = {
		.flagword = 0,
	};

	if (create_flags != NULL)
		res.flagword = create_flags->flags;

	return sys_vserver(VCMD_ctx_create, xid, &res);
}

int vx_migrate(xid_t xid, struct vx_migrate_flags *migrate_flags)
{
	struct vcmd_ctx_migrate res = {
		.flagword = 0,
	};

	if (migrate_flags != NULL)
		res.flagword = migrate_flags->flags;

	return sys_vserver(VCMD_ctx_migrate, xid, &res);
}

int vx_set_flags(xid_t xid, struct vx_flags *flags)
{
	struct vcmd_ctx_flags_v0 res;

	res.flagword = flags->flags;
	res.mask     = flags->mask;

	return sys_vserver(VCMD_set_cflags, xid, &res);
}

int vx_get_flags(xid_t xid, struct vx_flags *flags)
{
	struct vcmd_ctx_flags_v0 res;

	int rc = sys_vserver(VCMD_get_cflags, xid, &res);

	if (rc == -1)
		return rc;

	flags->flags = res.flagword;
	flags->mask  = res.mask;

	return rc;
}

int vx_set_bcaps(xid_t xid, struct vx_bcaps *bcaps)
{
	struct vcmd_bcaps res;

	res.bcaps = bcaps->bcaps;
	res.bmask = bcaps->bmask;

	return sys_vserver(VCMD_set_bcaps, xid, &res);
}

int vx_get_bcaps(xid_t xid, struct vx_bcaps *bcaps)
{
	struct vcmd_bcaps res;

	int rc = sys_vserver(VCMD_get_bcaps, xid, &res);

	if (rc == -1)
		return rc;

	bcaps->bcaps = res.bcaps;
	bcaps->bmask = res.bmask;

	return rc;
}

int vx_set_ccaps(xid_t xid, struct vx_ccaps *ccaps)
{
	struct vcmd_ctx_caps_v1 res;

	res.ccaps = ccaps->ccaps;
	res.cmask = ccaps->cmask;

	return sys_vserver(VCMD_set_ccaps, xid, &res);
}

int vx_get_ccaps(xid_t xid, struct vx_ccaps *ccaps)
{
	struct vcmd_ctx_caps_v1 res;

	int rc = sys_vserver(VCMD_get_ccaps, xid, &res);

	if (rc == -1)
		return rc;

	ccaps->ccaps = res.ccaps;
	ccaps->cmask = res.cmask;

	return rc;
}
