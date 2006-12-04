// Copyright 2005-2006 Benedikt Böhm <hollow@gentoo.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
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
#include <config.h>
#endif

#include <stdint.h>
#include <errno.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/cacct_cmd.h"
#include "linux/vserver/network_cmd.h"

#include "vserver.h"

/* we don't want to use those from libc, but don't want lucid either */
static inline
int str_len(const char *str)
{
	int i = 0;
	
	while (*str++)
		i++;
	
	return i;
}

static inline
void str_zero(void *str, int n)
{
	char *p = str;
	
	while (n--)
		*p++ = 0;
}

static inline
int str_cpyn(void *dst, const void *src, int n)
{
	char *d = dst;
	const char *s = src;
	
	while (n--)
		*d++ = *s++;
	
	return d - (char *) dst;
}

int nx_create(nid_t nid, nx_flags_t *data)
{
	struct vcmd_net_create kdata = {
		.flagword = 0,
	};
	
	if (data)
		kdata.flagword = data->flags;
	
	return sys_vserver(VCMD_net_create, nid, &kdata);
}

int nx_migrate(nid_t nid)
{
	return sys_vserver(VCMD_net_migrate, nid, NULL);
}

int nx_task_nid(pid_t pid)
{
	return sys_vserver(VCMD_task_nid, pid, NULL);
}

int nx_info(nid_t nid, nx_info_t *data)
{
	struct vcmd_nx_info_v0 kdata;
	
	int rc = sys_vserver(VCMD_nx_info, nid, &kdata);
	
	if (rc == -1)
		return rc;
	
	if (data)
		data->nid = kdata.nid;
	
	return rc;
}

int nx_addr_add(nid_t nid, nx_addr_t *data)
{
	struct vcmd_net_addr_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	kdata.type  = data->type;
	kdata.count = data->count;
	
	str_cpyn(kdata.ip,   data->ip,   sizeof(kdata.ip));
	str_cpyn(kdata.mask, data->mask, sizeof(kdata.mask));
	
	return sys_vserver(VCMD_net_add, nid, &kdata);
}

int nx_addr_remove(nid_t nid, nx_addr_t *data)
{
	struct vcmd_net_addr_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	kdata.type  = data->type;
	kdata.count = data->count;
	
	str_cpyn(kdata.ip,   data->ip,   sizeof(kdata.ip));
	str_cpyn(kdata.mask, data->mask, sizeof(kdata.mask));
	
	return sys_vserver(VCMD_net_remove, nid, &kdata);
}

int nx_flags_set(nid_t nid, nx_flags_t *data)
{
	struct vcmd_net_flags_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	kdata.flagword = data->flags;
	kdata.mask     = data->mask;
	
	return sys_vserver(VCMD_set_nflags, nid, &kdata);
}

int nx_flags_get(nid_t nid, nx_flags_t *data)
{
	struct vcmd_net_flags_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	int rc = sys_vserver(VCMD_get_nflags, nid, &kdata);

	if (rc == -1)
		return rc;

	data->flags = kdata.flagword;
	data->mask  = kdata.mask;

	return rc;
}

int nx_caps_set(nid_t nid, nx_flags_t *data)
{
	struct vcmd_net_caps_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;
	
	kdata.ncaps = data->flags;
	kdata.cmask = data->mask;

	return sys_vserver(VCMD_get_ncaps, nid, &kdata);
}

int nx_caps_get(nid_t nid, nx_flags_t *data)
{
	struct vcmd_net_caps_v0 kdata;
	
	if (!data)
		return errno = EINVAL, -1;
	
	int rc = sys_vserver(VCMD_get_ncaps, nid, &kdata);

	if (rc == -1)
		return rc;

	data->flags = kdata.ncaps;
	data->mask  = kdata.cmask;

	return rc;
}

int nx_sock_stat(nid_t nid, nx_sock_stat_t *data)
{
	struct vcmd_sock_stat_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;
	
	kdata.field = data->id;

	int rc = sys_vserver(VCMD_sock_stat, nid, &kdata);
	
	if (rc == -1)
		return rc;
	
	data->count[0] = kdata.count[0];
	data->count[1] = kdata.count[1];
	data->count[2] = kdata.count[2];
	
	data->total[0] = kdata.total[0];
	data->total[1] = kdata.total[1];
	data->total[2] = kdata.total[2];
	
	return rc;
}
