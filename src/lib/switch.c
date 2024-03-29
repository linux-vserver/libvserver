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

#include "linux/vserver/switch.h"
#include "linux/vserver/debug_cmd.h"

#include "vserver.h"

int vs_get_version(void)
{
	return vserver(VCMD_get_version, 0, NULL);
}

int vs_get_config(void)
{
	return vserver(VCMD_get_vci, 0, NULL);
}
