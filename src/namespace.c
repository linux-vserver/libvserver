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

#include <sched.h>
#include <signal.h>

#include "vserver.h"

#include "linux/vserver/switch.h"
#include "linux/vserver/namespace_cmd.h"

int vx_clone_namespace(void)
{
	return sys_clone(CLONE_NEWNS|SIGCHLD, 0);
}

int vx_enter_namespace(xid_t xid)
{
	return sys_vserver(VCMD_enter_namespace, xid, NULL);
}

int vx_cleanup_namespace(void)
{
	return sys_vserver(VCMD_cleanup_namespace, 0, NULL);
}

int vx_set_namespace(xid_t xid)
{
	return sys_vserver(VCMD_set_namespace, xid, NULL);
}
