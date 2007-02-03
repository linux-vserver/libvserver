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

#include <stdint.h>
#include <errno.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/dlimit_cmd.h"

#include "vserver.h"

int dx_limit_add(xid_t xid, dx_limit_t *data)
{
	struct vcmd_ctx_dlimit_base_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.name  = data->filename;
	kdata.flags = data->flags;

	return sys_vserver(VCMD_add_dlimit, xid, &kdata);
}

int dx_limit_remove(xid_t xid, dx_limit_t *data)
{
	struct vcmd_ctx_dlimit_base_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.name = data->filename;

	return sys_vserver(VCMD_rem_dlimit, xid, &kdata);
}

int dx_limit_set(xid_t xid, dx_limit_t *data)
{
	struct vcmd_ctx_dlimit_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.name         = data->filename;
	kdata.space_used   = data->space_used;
	kdata.space_total  = data->space_total;
	kdata.inodes_used  = data->inodes_used;
	kdata.inodes_total = data->inodes_total;
	kdata.reserved     = data->reserved;
	kdata.flags        = data->flags;

	return sys_vserver(VCMD_set_dlimit, xid, &kdata);
}

int dx_limit_get(xid_t xid, dx_limit_t *data)
{
	int rc;
	struct vcmd_ctx_dlimit_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.name = data->filename;

	rc = sys_vserver(VCMD_get_dlimit, xid, &kdata);

	if (rc == -1)
		return rc;

	data->space_used   = kdata.space_used;
	data->space_total  = kdata.space_total;
	data->inodes_used  = kdata.inodes_used;
	data->inodes_total = kdata.inodes_total;
	data->reserved     = kdata.reserved;
	data->flags        = kdata.flags;

	return rc;
}
