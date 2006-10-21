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
#include <errno.h>
#include <string.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/context_cmd.h"
#include "linux/vserver/cvirt_cmd.h"
#include "linux/vserver/signal_cmd.h"

#include "vserver.h"

int vx_create(xid_t xid, struct vx_flags *flags)
{
	struct vcmd_ctx_create res = {
		.flagword = 0,
	};
	
	if (flags != NULL)
		res.flagword = flags->flags;
	
	return sys_vserver(VCMD_ctx_create, xid, &res);
}

int vx_migrate(xid_t xid, struct vx_flags *flags)
{
	struct vcmd_ctx_migrate res = {
		.flagword = 0,
	};
	
	if (flags != NULL)
		res.flagword = flags->flags;
	
	return sys_vserver(VCMD_ctx_migrate, xid, &res);
}

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
	int rc;
	struct vcmd_ctx_stat_v0 res1;
	struct vcmd_virt_stat_v0 res2;
	
	rc = sys_vserver(VCMD_ctx_stat, xid, &res1);
	
	if (rc == -1)
		return rc;
	
	rc = sys_vserver(VCMD_virt_stat, xid, &res2);

	if (rc == -1)
		return rc;

	if (stat != NULL) {
		stat->usecnt     = res1.usecnt;
		stat->tasks      = res1.tasks;
		stat->nr_threads = res2.nr_threads;
		stat->nr_running = res2.nr_running;
		stat->nr_unintr  = res2.nr_uninterruptible;
		stat->nr_onhold  = res2.nr_onhold;
		stat->nr_forks   = res2.nr_forks;
		stat->load[0]    = res2.load[0];
		stat->load[1]    = res2.load[1];
		stat->load[2]    = res2.load[2];
		stat->offset     = res2.offset;
		stat->uptime     = res2.uptime;
	}
	
	return rc;
}

int vx_set_bcaps(xid_t xid, struct vx_caps *caps)
{
	struct vcmd_bcaps res;
	
	res.bcaps = caps->caps;
	res.bmask = caps->mask;
	
	return sys_vserver(VCMD_set_bcaps, xid, &res);
}

int vx_get_bcaps(xid_t xid, struct vx_caps *caps)
{
	struct vcmd_bcaps res;
	
	int rc = sys_vserver(VCMD_get_bcaps, xid, &res);
	
	if (rc == -1)
		return rc;
	
	caps->caps = res.bcaps;
	caps->mask = res.bmask;
	
	return rc;
}

int vx_set_ccaps(xid_t xid, struct vx_caps *caps)
{
	struct vcmd_ctx_caps_v1 res;
	
	res.ccaps = caps->caps;
	res.cmask = caps->mask;
	
	return sys_vserver(VCMD_set_ccaps, xid, &res);
}

int vx_get_ccaps(xid_t xid, struct vx_caps *caps)
{
	struct vcmd_ctx_caps_v1 res;
	
	int rc = sys_vserver(VCMD_get_ccaps, xid, &res);
	
	if (rc == -1)
		return rc;
	
	caps->caps = res.ccaps;
	caps->mask = res.cmask;
	
	return rc;
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

int vx_set_uname(xid_t xid, struct vx_uname *uname)
{
	struct vcmd_vhi_name_v0 res;
	
	if (strlen(uname->value) > 64)
		return errno = EINVAL, -1;
	
	res.field = uname->id;
	
	bzero(res.name, sizeof res.name);
	memcpy(res.name, uname->value, sizeof res.name);
	
	return sys_vserver(VCMD_set_vhi_name, xid, &res);
}

int vx_get_uname(xid_t xid, struct vx_uname *uname)
{
	int rc;
	struct vcmd_vhi_name_v0 res;
	
	res.field = uname->id;
	
	rc = sys_vserver(VCMD_get_vhi_name, xid, &res);
	
	if (rc == -1)
		return rc;
	
	bzero(uname->value, sizeof uname->value);
	memcpy(uname->value, res.name, sizeof uname->value - 1);
	
	return rc;
}

int vx_kill(xid_t xid, pid_t pid, int sig)
{
	struct vcmd_ctx_kill_v0 res;
	
	res.pid = pid;
	res.sig = sig;
	
	return sys_vserver(VCMD_ctx_kill, xid, &res);
}

int vx_wait(xid_t xid, struct vx_wait_result *result)
{
	struct vcmd_wait_exit_v0 res;
	
	int rc, version = vs_get_version();
	
	if (version == -1)
		return -1;
	
	rc = sys_vserver(VCMD_wait_exit, xid, &res);
	
	if (rc == -1)
		return -1;
	
	if (result != NULL) {
		result->reboot_cmd = res.reboot_cmd;
		result->exit_code  = res.exit_code;
	}
	
	return rc;
}
