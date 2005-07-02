/***************************************************************************
 *   Copyright (C) 2005 by Benedikt Boehm                                  *
 *   hollow@gentoo.org                                                     *
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

#include "libvserver.h"

int vc_task_xid(pid_t pid)
{
	return vserver(VCMD_task_xid, pid, NULL);
}

int vc_vx_info(xid_t xid, struct vcmd_vx_info_v0 *info)
{
	return vserver(VCMD_vx_info, xid, info);
}

int vc_ctx_create(xid_t xid)
{
	return vserver(VCMD_ctx_create, xid, NULL);
}

int vc_ctx_migrate(xid_t xid)
{
	return vserver(VCMD_ctx_migrate, xid, NULL);
}

int vc_get_cflags(xid_t xid, struct vcmd_ctx_flags_v0 *cflags)
{
	if (cflags == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_get_cflags, xid, cflags);
}

int vc_set_cflags(xid_t xid, struct vcmd_ctx_flags_v0 *cflags)
{
	if (cflags == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_set_cflags, xid, cflags);
}

int vc_get_ccaps(xid_t xid, struct vcmd_ctx_caps_v0 *ccaps)
{
	if (ccaps == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_get_ccaps, xid, ccaps);
}

int vc_set_ccaps(xid_t xid, struct vcmd_ctx_caps_v0 *ccaps)
{
	if (ccaps == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_set_ccaps, xid, ccaps);
}
