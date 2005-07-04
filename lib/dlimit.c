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
#include "linux/vserver/dlimit_cmd.h"

#include "vserver.h"

/* TODO Convert to new API */
int vc_add_dlimit(xid_t xid, struct vcmd_ctx_dlimit_base_v0 *dbase)
{
	return vserver(VCMD_add_dlimit, xid, dbase);
}

int vc_rem_dlimit(xid_t xid, struct vcmd_ctx_dlimit_base_v0 *dbase)
{
	return vserver(VCMD_rem_dlimit, xid, dbase);
}

int vc_set_dlimit(xid_t xid, struct vcmd_ctx_dlimit_v0 *dlimit)
{
	return vserver(VCMD_set_dlimit, xid, dlimit);
}

int vc_get_dlimit(xid_t xid, struct vcmd_ctx_dlimit_v0 *dlimit)
{
	return vserver(VCMD_get_dlimit, xid, dlimit);
}
