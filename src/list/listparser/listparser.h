// Copyright 2005 The util-vserver Developers
// See AUTHORS for details
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by  *
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the
// Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef _LIBVSERVER_LISTPARSER_H
#define _LIBVSERVER_LISTPARSER_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int listparser_uint32(char const *str, size_t len,
                      char const **err_ptr, size_t *err_len,
                      uint_least32_t *flag,
                      uint_least32_t *mask,
                      uint_least32_t (*func)(char const*, size_t, bool *));
  
int listparser_uint64(char const *str, size_t len,
                      char const **err_ptr, size_t *err_len,
                      uint_least64_t *flag,
                      uint_least64_t *mask,
                      uint_least64_t (*func)(char const*, size_t, bool *));

#endif // _LIBVSERVER_LISTPARSER_H
