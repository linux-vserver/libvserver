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

#include <linux/capability.h>

#define DECL(VAL) { #VAL, sizeof(#VAL)-1, 1 << (CAP_ ## VAL) }

static const
struct val2text_mapping_uint64 VALUES[] = {
	DECL(CHOWN),
	DECL(DAC_OVERRIDE),
	DECL(DAC_READ_SEARCH),
	DECL(FOWNER),
	DECL(FSETID),
	DECL(KILL),
	DECL(SETGID),
	DECL(SETUID),
	DECL(SETPCAP),
	DECL(LINUX_IMMUTABLE),
	DECL(NET_BIND_SERVICE),
	DECL(NET_BROADCAST),
	DECL(NET_ADMIN),
	DECL(NET_RAW),
	DECL(IPC_LOCK),
	DECL(IPC_OWNER),
	DECL(SYS_MODULE),
	DECL(SYS_RAWIO),
	DECL(SYS_CHROOT),
	DECL(SYS_PTRACE),
	DECL(SYS_PACCT),
	DECL(SYS_ADMIN),
	DECL(SYS_BOOT),
	DECL(SYS_NICE),
	DECL(SYS_RESOURCE),
	DECL(SYS_TIME),
	DECL(SYS_TTY_CONFIG),
	DECL(MKNOD),
	DECL(LEASE),
	DECL(AUDIT_WRITE),
	DECL(AUDIT_CONTROL),
};

uint_least64_t vc_text2bcap(const char *str, size_t len)
{
	ssize_t idx = text2val_uint64(str, len, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].val;
}

char const *vc_bcap2text(uint_least64_t *val)
{
	ssize_t idx = val2text_uint64(val, VALUES, DIM_OF(VALUES));
	
	if (idx == -1) return 0;
	
	return VALUES[idx].id;
}

static
uint_least64_t vc_text2bcap_err(const char *str, size_t len, bool *failed)
{
	uint_least64_t res = vc_text2bcap(str, len);
	
	if (res == 0) *failed = true;
	
	return res;
}

int vc_list2bcap(const char *str, size_t len,
                 struct vc_err_listparser *err, struct vc_ctx_caps *caps)
{
	return listparser_uint64(str, len,
	                              err ? &err->ptr : 0,
	                              err ? &err->len : 0,
	                              &caps->bcaps, &caps->bmask,
	                              vc_text2bcap_err);
}
