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

#include <string.h>

#include "syscall-vserver.h"
#include "linux/vserver/switch.h"
#include "linux/vserver/cvirt_cmd.h"

#include "vserver.h"

int vx_set_vhi_name(xid_t xid, uint32_t field, const char *name)
{
	struct vcmd_vhi_name_v0 vhiname;
	size_t len = sizeof(vhiname.name);

	if (!name) {
		errno = EFAULT;
		return -1;
	}

	vhiname.field = field;
	strncpy(vhiname.name, name, len-1);
	vhiname.name[len] = '\0';

	return vserver(VCMD_set_vhi_name, xid, &vhiname);
}

int vx_get_vhi_name(xid_t xid, uint32_t field, char *name, size_t len)
{
	struct vcmd_vhi_name_v0 vhiname;

	if (!name) {
		errno = EFAULT;
		return -1;
	}

	vhiname.field = field;
	if (vserver(VCMD_get_vhi_name, xid, &vhiname) < 0)
		return -1;

	strncpy(name, vhiname.name, len-1);
	name[len] = '\0';

	return 0;
}
