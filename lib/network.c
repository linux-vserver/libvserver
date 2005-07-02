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

#include "vserver.h"

#include "libvserver.h"

int vc_task_nid(pid_t pid)
{
	if (pid == 0) {
		errno = ESRCH;
		return -1;
	}
	
	return vserver(VCMD_task_nid, pid, NULL);
}

int vc_nx_info(nid_t nid, struct vcmd_nx_info_v0 *info)
{
	if (info == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_nx_info, nid, info);
}

int vc_net_create(nid_t nid)
{
	int rc = vserver(VCMD_net_create, nid, NULL);
	return rc;
}

int vc_net_migrate(nid_t nid)
{
	int rc = vserver(VCMD_net_migrate, nid, NULL);
	return rc;
}

int vc_net_add(nid_t nid, struct vcmd_net_nx_v0 *nx)
{
	if (nx == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_net_add, nid, nx);
	return rc;
}

int vc_net_remove(nid_t nid, struct vcmd_net_nx_v0 *nx)
{
	if (nx == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_net_remove, nid, nx);
	return rc;
}

int vc_get_nflags(nid_t nid, struct vcmd_net_flags_v0 *flags)
{
	if (flags == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_get_nflags, nid, flags);
	return rc;
}

int vc_set_nflags(nid_t nid, struct vcmd_net_flags_v0 *flags)
{
	if (flags == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_nflags, nid, flags);
	return rc;
}

int vc_get_ncaps(nid_t nid, struct vcmd_net_caps_v0 *caps)
{
	if (caps == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_get_ncaps, nid, caps);
	return rc;
}

int vc_set_ncaps(nid_t nid, struct vcmd_net_caps_v0 *caps)
{
	if (caps == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_ncaps, nid, caps);
	return rc;
}
