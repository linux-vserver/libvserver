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

#include "linux/vserver/context.h"

#define DECL(VAL) { #VAL, sizeof(#VAL)-1, VXC_ ## VAL }

static const
struct val2text_mapping_uint64 VALUES[] = {
	DECL(SET_UTSNAME),
	DECL(SET_RLIMIT),
	DECL(RAW_ICMP),
	DECL(SYSLOG),
	DECL(SECURE_MOUNT),
	DECL(SECURE_REMOUNT),
	DECL(BINARY_MOUNT),
	DECL(QUOTA_CTL),
};

uint_least64_t vc_text2ccap(const char *str, size_t len)
{
	ssize_t idx = text2val_uint64(str, len, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].val;
}

char const *vc_ccap2text(uint_least64_t *val)
{
	ssize_t idx = val2text_uint64(val, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].id;
}

static
uint_least64_t vc_text2ccap_err(const char *str, size_t len, bool *failed)
{
	uint_least64_t res = vc_text2ccap(str, len);
	
	if (res == 0) *failed = true;
	
	return res;
}

int vc_list2ccap(const char *str, size_t len,
                 struct vc_err_listparser *err, struct vc_ctx_caps *caps)
{
	return listparser_uint64(str, len,
	                              err ? &err->ptr : 0,
	                              err ? &err->len : 0,
	                              &caps->ccaps, &caps->cmask,
	                              vc_text2ccap_err);
}
