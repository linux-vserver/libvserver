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

#include <errno.h>

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/network.h"
#include "linux/vserver/legacy.h"

int vc_new_s_context(xid_t ctx, unsigned int remove_cap, unsigned int flags)
{
	struct vcmd_new_s_context_v1 res;
	res.remove_cap = remove_cap;
	res.flags      = flags;
	
	return sys_vserver(VCMD_new_s_context, ctx, &res);
}

int vc_set_ipv4root(uint32_t  bcast, size_t nb, struct vc_ip_mask_pair const *ips)
{
	struct vcmd_set_ipv4root_v3 res;
	size_t i;
	
	if (nb > NB_IPV4ROOT) {
		errno = -EOVERFLOW;
		return -1;
	}
	
	res.broadcast = bcast;
	
	for (i = 0; i < nb; ++i) {
		res.nx_mask_pair[i].ip   = ips[i].ip;
		res.nx_mask_pair[i].mask = ips[i].mask;
	}
	
	return sys_vserver(VCMD_set_ipv4root, nb, &res);
}
