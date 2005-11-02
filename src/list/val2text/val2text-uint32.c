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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>

#include "val2text.h"

static inline
ssize_t search_value(uint_least32_t val,
                     struct val2text_mapping_uint32 const *map, size_t map_len)
{
	size_t i;
	
	for (i = 0; i < map_len; ++i) {
		if (val == map[i].val) return i;
	}
	
	return -1;
}

ssize_t val2text_uint32(uint_least32_t *val,
                        struct val2text_mapping_uint32 const *map, size_t map_len)
{
	ssize_t idx;
	
	uint_least32_t del_val;
	
	if (*val == 0)
		return -1;
	
	del_val = *val;
	idx     = search_value(del_val, map, map_len);
	
	if (idx == -1) {
		size_t i;
		
		for (i = 0; i < sizeof(*val)*8 && (*val & (1 << i)) == 0; ++i) {}
		
		del_val = (1 << i);
		idx     = search_value(del_val, map, map_len);
	}
	
	*val &= ~del_val;
    return idx;
}

ssize_t text2val_uint32(char const *str, size_t len,
                        struct val2text_mapping_uint32 const *map,
                        size_t map_len)
{
	size_t i;
	
	if (len == 0) len = strlen(str);
	
	for (i = 0; i < map_len; ++i) {
		if (len == map[i].len && strncasecmp(map[i].id, str, len) == 0)
			return i;
	}
	
	return -1;
}
