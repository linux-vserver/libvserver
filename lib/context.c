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
#include "linux/vserver/context_cmd.h"

#include "vserver.h"

int vx_get_task_xid(pid_t pid)
{
	return vserver(VCMD_task_xid, pid, NULL);
}

int vx_get_info(xid_t xid, struct vx_info *info)
{
	struct vcmd_vx_info_v0 vcmd;

	if (!info) {
		errno = EFAULT;
		return -1;
	}

	if (vserver(VCMD_vx_info, xid, &vcmd) < 0)
		return -1;
	
	info->xid = vcmd.xid;
	info->initpid = vcmd.initpid;
	
	return 0;
}

int vx_create(xid_t xid)
{
	return vserver(VCMD_ctx_create_v0, xid, NULL);
}

int vx_migrate(xid_t xid)
{
	return vserver(VCMD_ctx_migrate, xid, NULL);
}

int vx_set_flags(xid_t xid, const struct vx_flags *flags)
{
	struct vcmd_ctx_flags_v0 cflags;

	if (!flags) {
		errno = EFAULT;
		return -1;
	}
	
	cflags.flagword = flags->flags;
	cflags.mask     = flags->mask;
	
	return vserver(VCMD_set_cflags, xid, &cflags);
}

int vx_get_flags(xid_t xid, struct vx_flags *flags)
{
	struct vcmd_ctx_flags_v0 cflags;

	if (!flags) {
		errno = EFAULT;
		return -1;
	}
	
	if (vserver(VCMD_get_cflags, xid, &cflags))
		return -1;
	
	flags->flags = cflags.flagword;
	flags->mask  = cflags.mask;
	
	return 0;
}

int vx_set_caps(xid_t xid, const struct vx_caps *caps)
{
	struct vcmd_ctx_caps_v0 ccaps;

	if (!caps) {
		errno = EFAULT;
		return -1;
	}
	
	ccaps.bcaps = caps->bcaps;
	ccaps.ccaps = caps->ccaps;
	ccaps.cmask = caps->cmask;
	
	return vserver(VCMD_set_ccaps, xid, &ccaps);
}

int vx_get_caps(xid_t xid, struct vx_caps *caps)
{
	struct vcmd_ctx_caps_v0 ccaps;

	if (!caps) {
		errno = EFAULT;
		return -1;
	}
	
	if (vserver(VCMD_get_ccaps, xid, &ccaps) < 0)
		return -1;
	
	caps->bcaps = ccaps.bcaps;
	caps->ccaps = ccaps.ccaps;
	caps->cmask = ccaps.cmask;
	
	return 0;
}
