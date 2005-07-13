/***************************************************************************
 *   Copyright 2005 by the libvserver team                                 *
 *   See AUTHORS for details                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdint.h>
#include <errno.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/dlimit_cmd.h"

#include "vserver.h"

int vx_add_dlimit(xid_t xid, const char *name, uint32_t flags)
{
	struct vcmd_ctx_dlimit_base_v0 res;

	if (!name) {
		errno = EFAULT;
		return -1;
	}

	res.name = name;
	res.flags = flags;

	return vserver(VCMD_add_dlimit, xid, &res);
}

int vx_rem_dlimit(xid_t xid, const char *name)
{
	struct vcmd_ctx_dlimit_base_v0 res;

	res.name = name;

	return vserver(VCMD_rem_dlimit, xid, &res);
}

int vx_set_dlimit(xid_t xid, const char *name, struct vx_dlimit *dlimit)
{
	struct vcmd_ctx_dlimit_v0 res;

	if (!dlimit) {
		errno = EFAULT;
		return -1;
	}

	res.name         = name;
	res.space_used   = dlimit->space_used;
	res.space_total  = dlimit->space_total;
	res.inodes_used  = dlimit->inodes_used;
	res.inodes_total = dlimit->inodes_total;
	res.reserved     = dlimit->reserved;
	res.flags        = dlimit->flags;

	return vserver(VCMD_set_dlimit, xid, dlimit);
}

int vx_get_dlimit(xid_t xid, const char *name, struct vx_dlimit *dlimit)
{
	struct vcmd_ctx_dlimit_v0 res;

	if (!dlimit) {
		errno = EFAULT;
		return -1;
	}

	res.name = name;

	if (vserver(VCMD_get_dlimit, xid, dlimit) < 0)
		return -1;

	dlimit->space_used   = res.space_used;
	dlimit->space_total  = res.space_total;
	dlimit->inodes_used  = res.inodes_used;
	dlimit->inodes_total = res.inodes_total;
	dlimit->reserved     = res.reserved;
	dlimit->flags        = res.flags;

	return 0;
}
