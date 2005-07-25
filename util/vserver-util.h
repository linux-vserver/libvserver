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

#include <stdint.h>
#include <linux/types.h>

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
 * @file flagparser.c
 * @brief Parse flag strings
 */

/*!
 * @brief vs_flagparser_uint32_t
 */
int flagparser(const char *str, size_t len, const char delim,
               uint64_t *flag, uint64_t *mask,
               uint64_t (*strhandler)(const char *));

/*!
 * @file ccaps.c
 * @brief Context capabilities
 */

uint64_t bcaps_list_search(const char *key);

int bcaps_list_parse(const char *str, const char delim, 
                     uint64_t *flag, uint64_t *mask);


uint64_t ccaps_list_search(const char *key);

int ccaps_list_parse(const char *str, const char delim, 
                     uint64_t *flag, uint64_t *mask);

uint64_t cflags_list_search(const char *key);

int cflags_list_parse(const char *str, const char delim, 
                      uint64_t *flag, uint64_t *mask);


uint64_t iattr_list_search(const char *key);

int iattr_list_parse(const char *str, const char delim, 
                      uint64_t *flag, uint64_t *mask);


uint64_t nflags_list_search(const char *key);

int nflags_list_parse(const char *str, const char delim, 
                      uint64_t *flag, uint64_t *mask);

/*! @cond */
END_C_DECLS
/*! @endcond */

#endif /*_VSERVER_UTIL_H_*/
