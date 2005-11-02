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

#ifndef _VSERVER_H
#define _VSERVER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

/* typedefs */
typedef uint32_t xid_t;
typedef uint32_t nid_t;

/* syscall.c */
int sys_vserver(uint32_t cmd, xid_t xid, void *data);
int sys_personality(int pers);
int sys_clone(int flags, void *child_stack);

/* context.c */
struct vc_vx_info {
	xid_t xid;
	pid_t initpid;
};

int vc_get_task_xid(pid_t pid);
int vc_get_vx_info(xid_t xid, struct vc_vx_info *info);

int vc_ctx_create(xid_t xid);
int vc_ctx_migrate(xid_t xid);

struct vc_ctx_flags {
	uint_least64_t flagword;
	uint_least64_t mask;
};

struct vc_ctx_caps {
	uint_least64_t bcaps;
	uint_least64_t bmask;
	uint_least64_t ccaps;
	uint_least64_t cmask;
};

int vc_get_cflags(xid_t xid, struct vc_ctx_flags *);
int vc_set_cflags(xid_t xid, struct vc_ctx_flags const *);

int vc_get_ccaps(xid_t xid, struct vc_ctx_caps *);
int vc_set_ccaps(xid_t xid, struct vc_ctx_caps const *);

/* cvirt.c */
typedef enum {
	vcVHI_CONTEXT,
	vcVHI_SYSNAME,
	vcVHI_NODENAME,
	vcVHI_RELEASE,
	vcVHI_VERSION,
	vcVHI_MACHINE,
	vcVHI_DOMAINNAME
} vc_uts_type;

int vc_set_vhi_name(xid_t xid, vc_uts_type type, const char *val, size_t len);
int vc_get_vhi_name(xid_t xid, vc_uts_type type, char *val, size_t len);

/* dlimit.c */
struct vc_ctx_dlimit {
	uint_least32_t space_used;
	uint_least32_t space_total;
	uint_least32_t inodes_used;
	uint_least32_t inodes_total;
	uint_least32_t reserved;
};

int vc_add_dlimit(const char *filename, xid_t xid, uint_least32_t flags);
int vc_rem_dlimit(const char *filename, xid_t xid, uint_least32_t flags);

int vc_set_dlimit(const char *filename, xid_t xid, uint_least32_t flags, struct vc_ctx_dlimit const *limits);
int vc_get_dlimit(const char *filename, xid_t xid, uint_least32_t flags, struct vc_ctx_dlimit *limits);

/* inode.c */
int vc_get_iattr(const char *filename, xid_t * xid, uint_least32_t *flags, uint_least32_t *mask);
int vc_set_iattr(const char *filename, xid_t xid, uint_least32_t flags, uint_least32_t mask);

/* legacy.c */
struct vc_ip_mask_pair {
	uint32_t ip;
	uint32_t mask;
};

int vc_new_s_context(xid_t ctx, unsigned int remove_cap, unsigned int flags);
int vc_set_ipv4root(uint32_t bcast, size_t nb, struct vc_ip_mask_pair const *ips);

/* limit.c */
typedef uint_least64_t vc_limit_t;
struct vc_rlimit {
	vc_limit_t min;
	vc_limit_t soft;
	vc_limit_t hard;
};

struct vc_rlimit_mask {
	uint_least32_t min;
	uint_least32_t soft;
	uint_least32_t hard;
};

int vc_get_rlimit(xid_t xid, int resource, struct vc_rlimit *lim);
int vc_set_rlimit(xid_t xid, int resource, struct vc_rlimit const *lim);
int vc_get_rlimit_mask(xid_t xid, struct vc_rlimit_mask *lim);

/* namespace.c */
int vc_enter_namespace(xid_t xid);
int vc_cleanup_namespace();
int vc_set_namespace();

/* network.c */
struct vc_nx_info {
	nid_t nid;
};

int vc_get_task_nid(pid_t pid);
int vc_get_nx_info(nid_t nid, struct vc_nx_info *);

int vc_net_create(nid_t nid);
int vc_net_migrate(nid_t nid);

struct vc_net_nx {
	uint16_t type;
	size_t count;
	uint32_t ip;
	uint32_t mask;
};

int vc_net_add(nid_t nid, struct vc_net_nx const *info);
int vc_net_remove(nid_t nid, struct vc_net_nx const *info);

struct vc_net_flags {
	uint_least64_t flagword;
	uint_least64_t mask;
};

int vc_get_nflags(nid_t, struct vc_net_flags *);
int vc_set_nflags(nid_t, struct vc_net_flags const *);

struct vc_net_caps {
	uint_least64_t ncaps;
	uint_least64_t cmask;
};

int vc_get_ncaps(nid_t, struct vc_net_caps *);
int vc_set_ncaps(nid_t, struct vc_net_caps const *);

/* sched.c */
struct vc_set_sched {
	uint_least32_t set_mask;
	int_least32_t fill_rate;
	int_least32_t interval;
	int_least32_t tokens;
	int_least32_t tokens_min;
	int_least32_t tokens_max;
	int_least32_t priority_bias;
};

int vc_set_sched(xid_t xid, struct vc_set_sched const *);

/* signal.c */
int vc_ctx_kill(xid_t ctx, pid_t pid, int sig);
int vc_wait_exit(xid_t xid);

/* switch.c */
int vc_get_version();

/* list */
struct vc_err_listparser {
	const char *ptr;
	size_t len;
};

/* list/bcaps.c */
uint_least64_t vc_text2bcap(const char *str, size_t len);
char const *vc_bcap2text(uint_least64_t *val);
int vc_list2bcap(const char *str, size_t len, struct vc_err_listparser *err, struct vc_ctx_caps *cap);

/* list/ccaps.c */
uint_least64_t vc_text2ccap(const char *str, size_t len);
char const *vc_ccap2text(uint_least64_t *val);
int vc_list2ccap(const char *str, size_t len, struct vc_err_listparser *err, struct vc_ctx_caps *);

/* list/cflags.c */
uint_least64_t vc_text2cflag(const char *str, size_t len);
char const *vc_cflag2text(uint_least64_t *val);
int vc_list2cflag(const char *str, size_t len, struct vc_err_listparser *err, struct vc_ctx_flags *flags);

/* list/ncaps.c */
uint_least64_t vc_text2ncap(const char *str, size_t len);
char const *vc_ncap2text(uint_least64_t *val);
int vc_list2ncap(const char *str, size_t len, struct vc_err_listparser *err, struct vc_net_caps *);

/* list/nflags.c */
uint_least64_t vc_text2nflag(const char *str, size_t len);
char const *vc_nflag2text(uint_least64_t *val);
int vc_list2nflag(const char *str, size_t len, struct vc_err_listparser *err, struct vc_net_flags *flags);

/* list/personality.c */
uint_least32_t vc_text2personality(const char *str, size_t len);
char const *vc_personality2text(uint_least32_t *val);
int vc_list2personality(const char *str, size_t len, struct vc_err_listparser *err, uint_least32_t *personality);

/* list/personalitytype.c */
uint_least32_t vc_text2personalitytype(const char *str, size_t len);
char const *vc_personalitytype2text(uint_least32_t *val);

#endif
