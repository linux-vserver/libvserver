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

#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>
#include <search.h>
#include <string.h>

#include "vserver-util.h"


/* declare list structure */
#define LIST_DECL(NAME)                                                        \
struct NAME ## _list_entry {                                                   \
	const char *key;                                                       \
	uint64_t value;                                                        \
};

/* start list */
#define LIST_START(NAME)                                                       \
struct NAME ## _list_entry NAME ## _list[] = {

/* add list entry */
#define LIST_ENTRY(TYPE, NAME) { #NAME, TYPE ## _ ## NAME },

/* end list */
#define LIST_END(NAME)                                                         \
};                                                                             \
                                                                               \
size_t NAME ## _cnt = (sizeof NAME ## _list / sizeof NAME ## _list[0]);

/* default list comparision handler */
#define LIST_CMP_HANDLER(NAME)                                                 \
static inline                                                                  \
int NAME ## _list_keycmp(const void *a, const void *b)                         \
{                                                                              \
	return strcmp(((struct NAME ## _list_entry *)a)->key,                  \
	              ((struct NAME ## _list_entry *)b)->key);                 \
}

/* default str2value function */
#define LIST_SEARCH(NAME)                                                      \
uint64_t NAME ## _list_search(const char *key)                                 \
{                                                                              \
	struct NAME ## _list_entry needle, *res;                               \
	needle.key = key;                                                      \
	res = lsearch(&needle,                                                 \
	              &NAME ## _list,                                          \
	              &NAME ## _cnt,                                           \
	              sizeof needle,                                           \
	              NAME ## _list_keycmp);                                   \
	                                                                       \
	if (res)                                                               \
		return res->value;                                             \
	                                                                       \
	return 0;                                                              \
}

/* default flagparser */
#define LIST_FLAGPARSER(NAME)                                                  \
int NAME ## _list_parse(const char *str, const char delim,                     \
                        uint64_t *flag, uint64_t *mask)                        \
{                                                                              \
	return flagparser(str,                                                 \
	                  strlen(str),                                         \
	                  delim,                                               \
	                  flag,                                                \
	                  mask,                                                \
	                  NAME ## _list_search);                               \
}

#endif /*_LIST_H_*/
