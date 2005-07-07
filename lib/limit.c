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

#include "syscall-vserver.h"
#include "linux/vserver/switch.h"
#include "linux/vserver/limit_cmd.h"

#include "vserver.h"

int vx_get_rlimit(xid_t xid, uint32_t id, struct vx_rlimit *rlimit)
{
	struct vcmd_ctx_rlimit_v0 res;

	if (!rlimit) {
		errno = EFAULT;
		return -1;
	}

	res.id = id;

	if (vserver(VCMD_get_rlimit, xid, &res) < 0)
		return -1;

	rlimit->minimum   = res.minimum;
	rlimit->softlimit = res.softlimit;
	rlimit->maximum   = res.maximum;

	return 0;
}

int vx_set_rlimit(xid_t xid, uint32_t id, struct vx_rlimit *rlimit)
{
	struct vcmd_ctx_rlimit_v0 res;

	if (!rlimit) {
		errno = EFAULT;
		return -1;
	}

	res.id        = id;
	res.minimum   = rlimit->minimum;
	res.softlimit = rlimit->softlimit;
	res.maximum   = rlimit->maximum;

	return vserver(VCMD_set_rlimit, xid, &res);
}

int vx_get_rlimit_mask(struct vx_rlimit_mask *rmask)
{
	struct vcmd_ctx_rlimit_mask_v0 res;

	if (!rmask) {
		errno = EFAULT;
		return -1;
	}

	if (vserver(VCMD_get_rlimit_mask, 0, &res) < 0)
		return -1;

	rmask->minimum   = res.minimum;
	rmask->softlimit = res.softlimit;
	rmask->maximum   = res.maximum;

	return 0;
}
