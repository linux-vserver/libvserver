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
#include "linux/vserver/inode_cmd.h"

#include "vserver.h"

int vx_get_iattr(const char *name, struct vx_iattr *iattr)
{
	struct vcmd_ctx_iattr_v1 res;

	res.name = name;

	if (vserver(VCMD_get_iattr, 0, &res) < 0)
		return -1;

	iattr->xid   = res.xid;
	iattr->flags = res.flags;
	iattr->mask  = res.mask;

	return 0;
}

int vx_set_iattr(const char *name, const struct vx_iattr *iattr)
{
	struct vcmd_ctx_iattr_v1 res;

	res.name = name;
	res.xid   = iattr->xid;
	res.flags = iattr->flags;
	res.mask  = iattr->mask;

	return vserver(VCMD_set_iattr, 0, &res);
}
