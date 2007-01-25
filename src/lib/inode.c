// Copyright 2005-2006 Benedikt Böhm <hollow@gentoo.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the
// Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdint.h>
#include <errno.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/inode_cmd.h"

#include "vserver.h"

int ix_attr_set(ix_attr_t *data)
{
	struct vcmd_ctx_iattr_v1 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.name  = data->filename;
	kdata.xid   = data->xid;
	kdata.flags = data->flags;
	kdata.mask  = data->mask;

	return sys_vserver(VCMD_set_iattr, 0, &kdata);
}

int ix_attr_get(ix_attr_t *data)
{
	int rc;
	struct vcmd_ctx_iattr_v1 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.name = data->filename;

	rc = sys_vserver(VCMD_get_iattr, 0, &kdata);

	if (rc == -1)
		return rc;

	data->xid   = kdata.xid;
	data->flags = kdata.flags;
	data->mask  = kdata.mask;

	return rc;
}
