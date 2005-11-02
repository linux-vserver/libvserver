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

#include <linux/personality.h>

#define DECL(VAL) { #VAL, sizeof(#VAL)-1, PER_ ## VAL }

static const
struct val2text_mapping_uint32 VALUES[] = {
	DECL(LINUX),
	DECL(LINUX_32BIT),
	DECL(SVR4),
	DECL(SVR3),
	DECL(SCOSVR3),
	DECL(OSR5),
	DECL(WYSEV386),
	DECL(ISCR4),
	DECL(BSD),
	DECL(SUNOS),
	DECL(XENIX),
	DECL(LINUX32),
	DECL(LINUX32_3GB),
	DECL(IRIX32),
	DECL(IRIXN32),
	DECL(IRIX64),
	DECL(RISCOS),
	DECL(SOLARIS),
	DECL(UW7),
	DECL(OSF4),
	DECL(HPUX),
};

uint_least32_t vc_text2personalitytype(const char *str, size_t len)
{
	ssize_t idx = text2val_uint32(str, len, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return -1;
	
	return VALUES[idx].val;
}

char const *vc_personalitytype2text(uint_least32_t *val)
{
	ssize_t idx = val2text_uint32(val, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].id;
}
