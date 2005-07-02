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

int vc_get_iattr_v0(struct vcmd_ctx_iattr_v1 *iattr)
{
	if (iattr == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_get_iattr_v0, 0, iattr);
	return rc;
}

int vc_set_iattr_v0(struct vcmd_ctx_iattr_v1 *iattr)
{
	if (iattr == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_iattr_v0, 0, iattr);
	return rc;
}

int vc_get_iattr(struct vcmd_ctx_iattr_v0 *iattr)
{
	if (iattr == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_get_iattr, 0, iattr);
	return rc;
}

int vc_set_iattr(struct vcmd_ctx_iattr_v0 *iattr)
{
	if (iattr == 0) {
		errno = EFAULT;
		return -1;
	}
	
	int rc = vserver(VCMD_set_iattr, 0, iattr);
	return rc;
}
