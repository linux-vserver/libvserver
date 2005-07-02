/***************************************************************************
 *   Copyright (C) 2005 by Benedikt Boehm                                  *
 *   hollow@gentoo.org                                                     *
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

#include "libvserver.h"

int vc_add_dlimit(xid_t xid, struct vcmd_ctx_dlimit_base_v0 *dbase)
{
	if (dbase == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_add_dlimit, xid, dbase);
	return rc;
}

int vc_rem_dlimit(xid_t xid, struct vcmd_ctx_dlimit_base_v0 *dbase)
{
	if (dbase == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_rem_dlimit, xid, dbase);
	return rc;
}

int vc_set_dlimit(xid_t xid, struct vcmd_ctx_dlimit_v0 *dlimit)
{
	if (dlimit == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_dlimit, xid, dlimit);
	return rc;
}

int vc_get_dlimit(xid_t xid, struct vcmd_ctx_dlimit_v0 *dlimit)
{
	if (dlimit == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_get_dlimit, xid, dlimit);
	return rc;
}
