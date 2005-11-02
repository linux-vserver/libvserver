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

#ifndef _LIBVSERVER_VAL2TEXT_H
#define _LIBVSERVER_VAL2TEXT_H

#include <stdlib.h>
#include <stdint.h>

struct val2text_mapping_uint32 {
	char const * const id;
	size_t len;
	uint_least32_t val;
};

struct val2text_mapping_uint64 {
	char const * const id;
	size_t len;
	uint_least64_t val;
};
  
ssize_t val2text_uint32(uint_least32_t *val,
                        struct val2text_mapping_uint32 const *map,
                        size_t map_len);

ssize_t	text2val_uint32(char const *str,
                        size_t len,
                        struct val2text_mapping_uint32 const *map,
                        size_t map_len);

ssize_t val2text_uint64(uint_least64_t *val,
                        struct val2text_mapping_uint64 const *map,
                        size_t map_len);

ssize_t	text2val_uint64(char const *str,
                        size_t len,
                        struct val2text_mapping_uint64 const *map,
                        size_t map_len);

#endif // _LIBVSERVER_VAL2TEXT_H
