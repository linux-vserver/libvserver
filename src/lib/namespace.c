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

#include "linux/sched.h"
#include "linux/vserver/switch.h"
#include "linux/vserver/space_cmd.h"

#include "vserver.h"

int ns_clone(int flags, void *child_stack)
{
	return sys_clone(flags|CLONE_NEWNS, child_stack);
}

int ns_enter(xid_t xid)
{
	return sys_vserver(VCMD_enter_space, xid, NULL);
}

int ns_set(xid_t xid)
{
	return sys_vserver(VCMD_set_space, xid, NULL);
}
