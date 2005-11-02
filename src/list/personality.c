// Copyright 2005 The libvserver Developers
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

#include "listparser/listparser.h"
#include "val2text/val2text.h"
#include "dimof.h"

#include "vserver.h"

#include <linux/personality.h>

#define DECL(VAL) { #VAL, sizeof(#VAL)-1, VAL }

static const
struct val2text_mapping_uint32 VALUES[] = {
	DECL(MMAP_PAGE_ZERO),
	DECL(READ_IMPLIES_EXEC),
	DECL(ADDR_LIMIT_32BIT),
	DECL(SHORT_INODE),
	DECL(WHOLE_SECONDS),
	DECL(STICKY_TIMEOUTS),
	DECL(ADDR_LIMIT_3GB),
};

uint_least32_t vc_text2personality(const char *str, size_t len)
{
	ssize_t idx = text2val_uint32(str, len, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].val;
}

char const *vc_personality2text(uint_least32_t *val)
{
	ssize_t idx = val2text_uint32(val, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].id;
}

static
uint_least32_t vc_text2personality_err(const char *str, size_t len, bool *failed)
{
	uint_least32_t res = vc_text2personality(str, len);
	
	if (res == 0) *failed = true;
	
	return res;
}

int vc_list2personality(const char *str, size_t len,
                        struct vc_err_listparser *err,
                        uint_least32_t *personality)
{
	return listparser_uint32(str, len,
	                              err ? &err->ptr : 0,
	                              err ? &err->len : 0,
	                              personality, 0,
	                              vc_text2personality_err);
}
