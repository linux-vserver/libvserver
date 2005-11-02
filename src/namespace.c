// Copyright 2005 The libvserver Developers
// See AUTHORS for details
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by  *
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
#  include <config.h>
#endif

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/namespace_cmd.h"

int vc_enter_namespace(xid_t xid)
{
	return sys_vserver(VCMD_enter_namespace, xid, 0);
}

int vc_cleanup_namespace()
{
	return sys_vserver(VCMD_cleanup_namespace, 0, 0);
}

int vc_set_namespace(int tmp)
{
	return sys_vserver(VCMD_set_namespace, 0, 0);
}
