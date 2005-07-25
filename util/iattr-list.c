/***************************************************************************
 *   Copyright 2005 The libvserver Team                                    *
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

#include <linux/vserver/inode.h>
#include "vserver-util.h"

#include "list.h"

LIST_DECL(iattr, uint32_t)

LIST_START(iattr)

LIST_ENTRY(IATTR, XID)
LIST_ENTRY(IATTR, ADMIN)
LIST_ENTRY(IATTR, WATCH)
LIST_ENTRY(IATTR, HIDE)
LIST_ENTRY(IATTR, FLAGS)
LIST_ENTRY(IATTR, BARRIER)
LIST_ENTRY(IATTR, IUNLINK)
LIST_ENTRY(IATTR, IMMUTABLE)

LIST_END(iattr)

LIST_CMP_HANDLER(iattr)

LIST_SEARCH(iattr, uint32_t)

LIST_FLAGPARSER(iattr, uint32_t)
