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

#include "vserver.h"
#include <linux/personality.h>

LIST_DATA_ALLOC_TYPE(pers, uint64_t)

/*!
 * @brief Macro for bcaps list allocation
 * @ingroup list_defaults
 */
#define LIST_ADD_PERS(TYPE, VALUE) \
list_set(p->node+(i++), \
         list_key_alloc(#VALUE), \
         pers_list_data_alloc(TYPE ## _ ## VALUE));
	
list_t *pers_list_init(void)
{
	list_t *p = list_alloc(23);
	
	int i = 0;
	LIST_ADD_PERS(PER, LINUX)
	LIST_ADD_PERS(PER, LINUX_32BIT)
	LIST_ADD_PERS(PER, LINUX_FDPIC)
	LIST_ADD_PERS(PER, SVR4)
	LIST_ADD_PERS(PER, SVR3)
	LIST_ADD_PERS(PER, SCOSVR3)
	LIST_ADD_PERS(PER, OSR5)
	LIST_ADD_PERS(PER, WYSEV386)
	LIST_ADD_PERS(PER, ISCR4)
	LIST_ADD_PERS(PER, BSD)
	LIST_ADD_PERS(PER, SUNOS)
	LIST_ADD_PERS(PER, XENIX)
	LIST_ADD_PERS(PER, LINUX32)
	LIST_ADD_PERS(PER, LINUX32_3GB)
	LIST_ADD_PERS(PER, IRIX32)
	LIST_ADD_PERS(PER, IRIXN32)
	LIST_ADD_PERS(PER, IRIX64)
	LIST_ADD_PERS(PER, RISCOS)
	LIST_ADD_PERS(PER, SOLARIS)
	LIST_ADD_PERS(PER, UW7)
	LIST_ADD_PERS(PER, OSF4)
	LIST_ADD_PERS(PER, HPUX)
	LIST_ADD_PERS(PER, MASK)
	
	return p;
}
