/***************************************************************************
 *   Copyright 2005 by the libvserver team                                 *
 *   See AUTHORS for details                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <linux/compiler.h>

//#include "linux/vserver/context.h"
#include "linux/vserver/context_cmd.h"
//#include "linux/vserver/cvirt.h"
//#include "linux/vserver/cvirt_cmd.h"
//#include "linux/vserver/cvirt_def.h"
//#include "linux/vserver/dlimit.h"
#include "linux/vserver/dlimit_cmd.h"
//#include "linux/vserver/inode.h"
#include "linux/vserver/inode_cmd.h"
//#include "linux/vserver/limit.h"
#include "linux/vserver/limit_cmd.h"
//#include "linux/vserver/limit_def.h"
#include "linux/vserver/namespace.h"
//#include "linux/vserver/network.h"
#include "linux/vserver/network_cmd.h"
//#include "linux/vserver/sched.h"
#include "linux/vserver/sched_cmd.h"
//#include "linux/vserver/sched_def.h"
#include "linux/vserver/signal_cmd.h"
#include "linux/vserver/switch.h"
//#include "linux/vserver/xid.h"

#define CMD_VERSION \
	printf("%s %s -- %s\n", NAME, VERSION, DESCR); \
	printf("This program is part of libvserver %s\n\n", LIBVSERVER_VERSION); \
	\
	printf("Copyright (c) 2005 Benedikt Boehm <hollow@gentoo.org>\n"); \
	printf("This program is free software; you can redistribute it and/or\n"); \
	printf("modify it under the terms of the GNU General Public License\n"); \
	exit(0);


/* Constants */
#define LIBVSERVER_VERSION "0.1"

/* Type definitions */
typedef uint32_t xid_t;
typedef uint32_t nid_t;

/* context.c */
extern int vc_task_xid(pid_t pid);
extern int vc_vx_info(xid_t xid, struct vcmd_vx_info_v0 *info);
extern int vc_ctx_create(xid_t xid);
extern int vc_ctx_migrate(xid_t xid);
extern int vc_get_cflags(xid_t xid, struct vcmd_ctx_flags_v0 *cflags);
extern int vc_set_cflags(xid_t xid, struct vcmd_ctx_flags_v0 *cflags);
extern int vc_get_ccaps(xid_t xid, struct vcmd_ctx_caps_v0 *ccaps);
extern int vc_set_ccaps(xid_t xid, struct vcmd_ctx_caps_v0 *ccaps);

/* cvirt.c */
extern int vc_set_vhi_name(xid_t xid, struct vcmd_vx_vhi_name_v0 *vhiname);
extern int vc_get_vhi_name(xid_t xid, struct vcmd_vx_vhi_name_v0 *vhiname);

/* dlimit.c */
extern int vc_add_dlimit(xid_t xid, struct vcmd_ctx_dlimit_base_v0 *dbase);
extern int vc_rem_dlimit(xid_t xid, struct vcmd_ctx_dlimit_base_v0 *dbase);
extern int vc_set_dlimit(xid_t xid, struct vcmd_ctx_dlimit_v0 *dlimit);
extern int vc_get_dlimit(xid_t xid, struct vcmd_ctx_dlimit_v0 *dlimit);

/* inode.c */
extern int vc_get_iattr_v0(struct vcmd_ctx_iattr_v1 *iattr);
extern int vc_set_iattr_v0(struct vcmd_ctx_iattr_v1 *iattr);
extern int vc_get_iattr(struct vcmd_ctx_iattr_v0 *iattr);
extern int vc_set_iattr(struct vcmd_ctx_iattr_v0 *iattr);

/* limit.c */
extern int vc_get_rlimit(xid_t xid, struct vcmd_ctx_rlimit_v0 *rlimit);
extern int vc_set_rlimit(xid_t xid, struct vcmd_ctx_rlimit_v0 *rlimit);
extern int vc_get_rlimit_mask(xid_t xid, struct vcmd_ctx_rlimit_mask_v0 *rmask);

/* namespace.c */
extern int vc_enter_namespace(xid_t xid);
extern int vc_cleanup_namespace();
extern int vc_set_namespace();

/* network.c */
extern int vc_task_nid(pid_t pid);
extern int vc_nx_info(nid_t nid, struct vcmd_nx_info_v0 *info);
extern int vc_net_create(nid_t nid);
extern int vc_net_migrate(nid_t nid);
extern int vc_net_add(nid_t nid, struct vcmd_net_nx_v0 *nx);
extern int vc_net_remove(nid_t nid, struct vcmd_net_nx_v0 *nx);
extern int vc_get_nflags(nid_t nid, struct vcmd_net_flags_v0 *flags);
extern int vc_set_nflags(nid_t nid, struct vcmd_net_flags_v0 *flags);
extern int vc_get_ncaps(nid_t nid, struct vcmd_net_caps_v0 *caps);
extern int vc_set_ncaps(nid_t nid, struct vcmd_net_caps_v0 *caps);

/* sched.c */
extern int vc_set_sched_v2(xid_t xid, struct vcmd_set_sched_v2 *sched);
extern int vc_set_sched(xid_t xid, struct vcmd_set_sched_v3 *sched);

/* signal.c */
extern int vc_ctx_kill(xid_t xid, struct vcmd_ctx_kill_v0 *kill);
extern int vc_wait_exit(xid_t xid, struct vcmd_wait_exit_v0 *wait);

/* switch.c */
extern int vc_get_version();
