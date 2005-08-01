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

#include "vserver-util.h"
#include <linux/personality.h>

LIST_DATA_ALLOC_TYPE(persflag, uint64_t)

/*!
 * @brief Macro for bcaps list allocation
 * @ingroup list_defaults
 */
#define LIST_ADD_PERSFLAG(VALUE) \
list_set(p->node+(i++), \
         list_key_alloc(#VALUE), \
         persflag_list_data_alloc(VALUE));
	
list_t *persflag_list_init(void)
{
	list_t *p = list_alloc(10);
	
	int i = 0;
	LIST_ADD_PERSFLAG(ADDR_NO_RANDOMIZE)
	LIST_ADD_PERSFLAG(FDPIC_FUNCPTRS)
	LIST_ADD_PERSFLAG(MMAP_PAGE_ZERO)
	LIST_ADD_PERSFLAG(ADDR_COMPAT_LAYOUT)
	LIST_ADD_PERSFLAG(READ_IMPLIES_EXEC)
	LIST_ADD_PERSFLAG(ADDR_LIMIT_32BIT)
	LIST_ADD_PERSFLAG(SHORT_INODE)
	LIST_ADD_PERSFLAG(WHOLE_SECONDS)
	LIST_ADD_PERSFLAG(STICKY_TIMEOUTS)
	LIST_ADD_PERSFLAG(ADDR_LIMIT_3GB)
	
	return p;
}
