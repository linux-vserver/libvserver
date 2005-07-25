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

#include "linux/vserver/context.h"
#include "vserver-util.h"

#include "list.h"

#define LIST_NAME ccaps

LIST_DECL(LIST_NAME)

LIST_START(LIST_NAME)

LIST_ENTRY(VXC, SET_UTSNAME)
LIST_ENTRY(VXC, SET_RLIMIT)
LIST_ENTRY(VXC, RAW_ICMP)
LIST_ENTRY(VXC, SYSLOG)
LIST_ENTRY(VXC, SECURE_MOUNT)
LIST_ENTRY(VXC, SECURE_REMOUNT)
LIST_ENTRY(VXC, BINARY_MOUNT)
LIST_ENTRY(VXC, QUOTA_CTL)

LIST_END(LIST_NAME)

LIST_CMP_HANDLER(LIST_NAME)

LIST_SEARCH(LIST_NAME)

LIST_FLAGPARSER(LIST_NAME)
