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
#include "linux/vserver/namespace.h"

#include "vserver.h"

int vc_set_vhi_name(xid_t xid, uint32_t field, char *name)
{
	struct vcmd_vx_vhi_name_v0 vhiname;
	int ret;

	vhiname.field = field;
	strncpy(vhiname.name, name, sizeof(vhiname.name));
	return vserver(VCMD_vx_set_vhi_name, xid, &vhiname);
}

int vc_get_vhi_name(xid_t xid, uint32_t field, char *name, size_t length)
{
	struct vcmd_vx_vhi_name_v0 vhiname;
	int ret;

	vhiname.field = field;
	if ((ret = vserver(VCMD_vx_get_vhi_name, xid, &vhiname)) != -1) {
		strncpy(name, vhiname.name, length);
	}

	return ret;
}
