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
