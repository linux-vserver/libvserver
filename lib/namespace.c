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

int vc_set_vhi_name(xid_t xid, struct vcmd_vx_vhi_name_v0 *vhiname)
{
	if (vhiname == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_vx_set_vhi_name, xid, vhiname);
}

int vc_get_vhi_name(xid_t xid, struct vcmd_vx_vhi_name_v0 *vhiname)
{
	if (vhiname == 0) {
		errno = EFAULT;
		return -1;
	}
	
	return vserver(VCMD_vx_get_vhi_name, xid, vhiname);
}

int vc_enter_namespace(xid_t xid)
{
	return vserver(VCMD_enter_namespace, xid, NULL);
}

int vc_cleanup_namespace()
{
	return vserver(VCMD_cleanup_namespace, 0, NULL);
}

int vc_set_namespace()
{
	return vserver(VCMD_set_namespace, 0, NULL);
}
