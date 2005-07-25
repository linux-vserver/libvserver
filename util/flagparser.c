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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "vserver-util.h"

#define FLAGPARSER(TYPE)                                                       \
int flagparser_##TYPE(const char *str, size_t len, const char delim,           \
                      TYPE *flag, TYPE *mask,                      \
                      TYPE (*strhandler)(char const *))                        \
{                                                                              \
	if (len == 0)                                                              \
		len = strlen(str);                                                     \
	                                                                           \
	for (; len > 0;) {                                                         \
		const char *ptr = strchr(str, delim); /* get pointer to next delim */  \
		size_t     cnt  = 0;                                                   \
		TYPE       tmp  = 0;                                                   \
		bool       rem  = false;                                               \
		                                                                       \
		cnt = ptr ? (size_t) (ptr - str) : len; /* save delim position */      \
		                                                                       \
		/*printf("str=%s, cnt=%d, len=%d\n", str, cnt, len);*/                     \
		                                                                       \
		if (cnt == 0) { /* empty field */                                      \
			len--;                                                             \
			str = ++ptr;                                                       \
			continue;                                                          \
		}                                                                      \
		                                                                       \
		if (cnt >= len) { /* check end of list */                              \
			cnt = len;                                                         \
			len = 0;                                                           \
		}                                                                      \
		else                                                                   \
			len -= (cnt+1); /* skip token + delim */                           \
		                                                                       \
		if (*str == '-') {                                                     \
			rem = true;                                                        \
			cnt--;                                                             \
			str++;                                                             \
		}                                                                      \
		                                                                       \
		/*printf("str=%s, cnt=%d, len=%d\n", str, cnt, len);*/                     \
		                                                                       \
		char *substr = malloc(cnt);                                            \
		strncpy(substr, str, cnt);                                             \
		tmp = (*strhandler)(substr); /* get flag for token */                  \
		                                                                       \
		/*printf("substr=%s, tmp=%#x, rem=%d\n", substr, tmp, rem);*/              \
		                                                                       \
		if (tmp == 0) {                                                        \
			continue;                                                          \
		}                                                                      \
		                                                                       \
		if (!rem)                                                              \
			*flag |=  tmp; /* set negative flag */                             \
		else                                                                   \
			*flag &= ~tmp; /* set flag */                                      \
		                                                                       \
		if (mask != 0)                                                         \
			*mask |= tmp; /* set mask */                                       \
		                                                                       \
		if (ptr == 0) /* no more tokens */                                     \
			break;                                                             \
		                                                                       \
		str = ++ptr; /* skip token + delim */                                  \
	}                                                                          \
	                                                                           \
	return 0;                                                                  \
}

FLAGPARSER(uint32_t)
FLAGPARSER(uint64_t)
