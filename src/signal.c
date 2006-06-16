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
#include "linux/vserver/signal_cmd.h"

int vx_kill(xid_t xid, struct vx_kill_opts *kill_opts)
{
	struct vcmd_ctx_kill_v0 res;

	res.pid = kill_opts->pid;
	res.sig = kill_opts->sig;

	return sys_vserver(VCMD_ctx_kill, xid, &res);
}

int vx_wait(xid_t xid, struct vx_wait_result *wait_result)
{
	struct vcmd_wait_exit_v0 res;
	
	int rc, version = vs_get_version();
	
	if (version == -1)
		return -1;
	
	rc = sys_vserver(VCMD_wait_exit, xid, &res);
	
	if (rc == -1)
		return -1;
	
	if (wait_result != NULL) {
		wait_result->reboot_cmd = res.reboot_cmd;
		wait_result->exit_code  = res.exit_code;
	}
	
	return rc;
}
