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
#include "linux/vserver/dlimit_cmd.h"

int vc_add_dlimit(char const *filename, xid_t xid, uint32_t flags)
{
	struct vcmd_ctx_dlimit_base_v0 res = {
		.name  = filename,
		.flags = flags,
	};
	
	return sys_vserver(VCMD_add_dlimit, xid, &res);
}

int vc_rem_dlimit(char const *filename, xid_t xid, uint32_t flags)
{
	struct vcmd_ctx_dlimit_base_v0 res = {
		.name  = filename,
		.flags = flags,
	};
	
	return sys_vserver(VCMD_rem_dlimit, xid, &res);
}

int vc_set_dlimit(char const *filename, xid_t xid,
                  uint_least32_t flags, struct vc_ctx_dlimit const *limits)
{
	struct vcmd_ctx_dlimit_v0 res = {
		.name         = filename,
		.flags        = flags,
		.space_used   = limits->space_used,
		.space_total  = limits->space_total,
		.inodes_used  = limits->inodes_used,
		.inodes_total = limits->inodes_total,
		.reserved     = limits->reserved,
	};
	
	return sys_vserver(VCMD_set_dlimit, xid, &res);
}

int vc_get_dlimit(char const *filename, xid_t xid,
                  uint_least32_t flags, struct vc_ctx_dlimit *limits)
{
	int rc;
	
	struct vcmd_ctx_dlimit_v0 res = {
		.name   = filename,
		.flags  = flags,
	};
	
	rc = sys_vserver(VCMD_get_dlimit, xid, &res);
	
	if (limits) {
		limits->space_used   = res.space_used;
		limits->space_total  = res.space_total;
		limits->inodes_used  = res.inodes_used;
		limits->inodes_total = res.inodes_total;
		limits->reserved     = res.reserved;
	}
	
	return rc;
}
