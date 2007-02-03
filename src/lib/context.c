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

#include <stdint.h>
#include <errno.h>

#include "linux/vserver/switch.h"
#include "linux/vserver/context_cmd.h"
#include "linux/vserver/cvirt_cmd.h"
#include "linux/vserver/signal_cmd.h"

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

int vx_create(xid_t xid, vx_flags_t *data)
{
	struct vcmd_ctx_create kdata = {
		.flagword = 0,
	};

	if (data)
		kdata.flagword = data->flags;

	return sys_vserver(VCMD_ctx_create, xid, &kdata);
}

int vx_migrate(xid_t xid, vx_flags_t *data)
{
	struct vcmd_ctx_migrate kdata = {
		.flagword = 0,
	};

	if (data)
		kdata.flagword = data->flags;

	return sys_vserver(VCMD_ctx_migrate, xid, &kdata);
}

int vx_task_xid(pid_t pid)
{
	return sys_vserver(VCMD_task_xid, pid, NULL);
}

int vx_info(xid_t xid, vx_info_t *data)
{
	struct vcmd_vx_info_v0 kdata;

	int rc = sys_vserver(VCMD_vx_info, xid, &kdata);

	if (rc == -1)
		return rc;

	if (data) {
		data->xid     = kdata.xid;
		data->initpid = kdata.initpid;
	}

	return rc;
}

int vx_stat(xid_t xid, vx_stat_t *data)
{
	int rc;
	struct vcmd_ctx_stat_v0 kdata1;
	struct vcmd_virt_stat_v0 kdata2;

	rc = sys_vserver(VCMD_ctx_stat, xid, &kdata1);

	if (rc == -1)
		return rc;

	rc = sys_vserver(VCMD_virt_stat, xid, &kdata2);

	if (rc == -1)
		return rc;

	if (data) {
		data->usecnt     = kdata1.usecnt;
		data->tasks      = kdata1.tasks;
		data->nr_threads = kdata2.nr_threads;
		data->nr_running = kdata2.nr_running;
		data->nr_unintr  = kdata2.nr_uninterruptible;
		data->nr_onhold  = kdata2.nr_onhold;
		data->nr_forks   = kdata2.nr_forks;
		data->load[0]    = kdata2.load[0];
		data->load[1]    = kdata2.load[1];
		data->load[2]    = kdata2.load[2];
		data->offset     = kdata2.offset;
		data->uptime     = kdata2.uptime;
	}

	return rc;
}

int vx_bcaps_set(xid_t xid, vx_flags_t *data)
{
	struct vcmd_bcaps kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.bcaps = data->flags;
	kdata.bmask = data->mask;

	return sys_vserver(VCMD_set_bcaps, xid, &kdata);
}

int vx_bcaps_get(xid_t xid, vx_flags_t *data)
{
	struct vcmd_bcaps kdata;

	if (!data)
		return errno = EINVAL, -1;

	int rc = sys_vserver(VCMD_get_bcaps, xid, &kdata);

	if (rc == -1)
		return rc;

	data->flags = kdata.bcaps;
	data->mask  = kdata.bmask;

	return rc;
}

int vx_ccaps_set(xid_t xid, vx_flags_t *data)
{
	struct vcmd_ctx_caps_v1 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.ccaps = data->flags;
	kdata.cmask = data->mask;

	return sys_vserver(VCMD_set_ccaps, xid, &kdata);
}

int vx_ccaps_get(xid_t xid, vx_flags_t *data)
{
	struct vcmd_ctx_caps_v1 kdata;

	if (!data)
		return errno = EINVAL, -1;

	int rc = sys_vserver(VCMD_get_ccaps, xid, &kdata);

	if (rc == -1)
		return rc;

	data->flags = kdata.ccaps;
	data->mask  = kdata.cmask;

	return rc;
}

int vx_flags_set(xid_t xid, vx_flags_t *data)
{
	struct vcmd_ctx_flags_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.flagword = data->flags;
	kdata.mask     = data->mask;

	return sys_vserver(VCMD_set_cflags, xid, &kdata);
}

int vx_flags_get(xid_t xid, vx_flags_t *data)
{
	struct vcmd_ctx_flags_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	int rc = sys_vserver(VCMD_get_cflags, xid, &kdata);

	if (rc == -1)
		return rc;

	data->flags = kdata.flagword;
	data->mask  = kdata.mask;

	return rc;
}

int vx_uname_set(xid_t xid, vx_uname_t *data)
{
	struct vcmd_vhi_name_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	if (str_len(data->value) >= sizeof(kdata.name))
		return errno = EINVAL, -1;

	kdata.field = data->id;

	str_zero(kdata.name, sizeof(kdata.name));
	str_cpyn(kdata.name, data->value, sizeof(kdata.name) - 1);

	return sys_vserver(VCMD_set_vhi_name, xid, &kdata);
}

int vx_uname_get(xid_t xid, vx_uname_t *data)
{
	int rc;
	struct vcmd_vhi_name_v0 kdata;

	if (!data)
		return errno = EINVAL, -1;

	kdata.field = data->id;

	rc = sys_vserver(VCMD_get_vhi_name, xid, &kdata);

	if (rc == -1)
		return rc;

	str_zero(data->value, sizeof(kdata.name));
	str_cpyn(data->value, kdata.name, sizeof(kdata.name) - 1);

	return rc;
}

int vx_kill(xid_t xid, pid_t pid, int sig)
{
	struct vcmd_ctx_kill_v0 kdata;

	kdata.pid = pid;
	kdata.sig = sig;

	return sys_vserver(VCMD_ctx_kill, xid, &kdata);
}

int vx_wait(xid_t xid, vx_wait_t *data)
{
	struct vcmd_wait_exit_v0 kdata;

	int rc;

	rc = sys_vserver(VCMD_wait_exit, xid, &kdata);

	if (rc == -1)
		return -1;

	if (data) {
		data->reboot_cmd = kdata.reboot_cmd;
		data->exit_code  = kdata.exit_code;
	}

	return rc;
}
