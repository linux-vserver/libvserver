// Copyright 2005 The libvserver Developers
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
#include "linux/vserver/signal_cmd.h"

int vc_ctx_kill(xid_t ctx, pid_t pid, int sig)
{
	struct vcmd_ctx_kill_v0 res = {
		.pid = pid,
		.sig = sig,
	};
	
	return sys_vserver(VCMD_ctx_kill, ctx, &res);
}

int vc_wait_exit(xid_t ctx)
{
	struct vcmd_wait_exit_v0 res = {
		.a = 0,
		.b = 0,
	};
	
	return sys_vserver(VCMD_wait_exit, ctx, &res);
}
