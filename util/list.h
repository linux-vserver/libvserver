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

#include <stdbool.h>
#include <stdint.h>
#include <search.h>
#include <string.h>
#include <sys/types.h>

#include "vserver-util.h"

static inline
int listparser(const char *str, size_t len, const char delim,
               uint64_t *flag, uint64_t *mask,
               uint64_t (*cmphandler)(char const *))
{
	if (len == 0)
		len = strlen(str);
	
	for (; len > 0;) {
		const char *ptr     = strchr(str, delim); /* get pointer to next delim */
		size_t     cnt      = 0;
		uint64_t   num_flag = 0;
		bool       clear    = false;
		
		cnt = ptr ? (size_t) (ptr - str) : len; /* save delim position */
		
		if (cnt == 0) { /* empty field */
			len--;
			str = ++ptr;
			continue;
		}
		
		if (cnt >= len) { /* check end of list */
			cnt = len;
			len = 0;
		}
		else
			len -= (cnt+1); /* skip token + delim */
		
		if (*str == '~') { /* remove flag */
			clear = true;
			cnt--;
			str++;
		}
		
		char *substr = malloc(cnt);
		strncpy(substr, str, cnt);
		num_flag = (*cmphandler)(substr); /* get flag for token */
		
		if (num_flag == 0) { /* invalid token */
			continue;
		}

		if (clear) {
			*flag &= ~num_flag; /* clear flag */
			*mask |=  num_flag; /* set mask */
		}
		else {
			*flag |=  num_flag; /* set flag */
			*mask |=  num_flag; /* set mask */
		}

		if (ptr == 0) /* no more tokens */
			break;

		str = ++ptr; /* skip token + delim */
	}

	return 0;
}

/* declare list structure */
#define LIST_DECL(NAME)                                                        \
struct NAME ## _list_entry {                                                   \
	const char *key;                                                       \
	uint64_t value;                                                        \
};                                                                             \

/* start list */
#define LIST_START(NAME)                                                       \
struct NAME ## _list_entry NAME ## _list[] = {                                 \

/* add list entry */
#define LIST_ENTRY(TYPE, NAME) { #NAME, TYPE ## _ ## NAME },

/* end list */
#define LIST_END(NAME)                                                         \
};                                                                             \
                                                                               \
size_t NAME ## _cnt = (sizeof NAME ## _list / sizeof NAME ## _list[0]);        \

/* default list comparision handler */
#define LIST_CMP_HANDLER(NAME)                                                 \
static inline                                                                  \
int NAME ## _list_keycmp(const void *a, const void *b)                         \
{                                                                              \
	return strcmp(((struct NAME ## _list_entry *)a)->key,                  \
	              ((struct NAME ## _list_entry *)b)->key);                 \
}                                                                              \

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
}                                                                              \

/* default flagparser */
#define LIST_FLAGPARSER(NAME)                                                  \
int NAME ## _list_parse(const char *str, const char delim,                     \
                        uint64_t *flag, uint64_t *mask)                        \
{                                                                              \
	return listparser(str,                                                 \
	                  strlen(str),                                         \
	                  delim,                                               \
	                  flag,                                                \
	                  mask,                                                \
	                  NAME ## _list_search);                               \
}                                                                              \

#endif /*_LIST_H_*/
