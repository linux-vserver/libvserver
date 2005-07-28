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

/*!
 * @file vserver-util.h
 * @brief Utility library ontop of libvserver
 */
#ifndef _VSERVER_UTIL_H_
#define _VSERVER_UTIL_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>

/*! @cond */
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
#else
# define BEGIN_C_DECLS /* empty */
# define END_C_DECLS /* empty */
#endif

BEGIN_C_DECLS
/*! @endcond */

/*!
 * @file list.c
 */
typedef struct list_node_s {
	char *key;  /* unique key identifier */
	void *data; /* any data associated with key */
} list_node_t;

typedef struct list_s {
	list_node_t *node; /* first node */
	size_t n;          /* number of nodes */
} list_t;

typedef struct list_link_s {
	list_t *p; /* prisitine list */
	list_t *d; /* descending list */
} list_link_t;

/* macro for data allocation using TYPE as data type */
#define LIST_DATA_ALLOC_TYPE(NAME, TYPE) \
static inline \
TYPE *NAME ## _list_data_alloc(TYPE value) \
{ \
	TYPE *data = (TYPE *)malloc(sizeof(TYPE)); \
	*data = value; \
	return data; \
}

/* TODO: doc! */
list_t *list_alloc(size_t n);
void list_dealloc(list_t *list);
char *list_key_alloc(char *str);
void list_set(list_node_t *node, char *key, void *data);
size_t list_ntokens(const char *str, const char delim);
char *list_parse(const char **str, const char delim);
list_t *list_parse_hash(const char *str, const char delim, const char kvdelim);
list_t *list_parse_list(const char *str, const char delim);
list_node_t *list_search(list_t *list, char *key);
int list_validate_flag(list_link_t *link, const char clmod);
int list_validate(list_link_t *link);
void list_list2flags(list_link_t *link, char clmod, uint64_t *flags, uint64_t *mask);

/*! @cond */
END_C_DECLS
/*! @endcond */

#endif /*_VSERVER_UTIL_H_*/
