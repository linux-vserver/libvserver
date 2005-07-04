/***************************************************************************
 *   Copyright 2005 The libvserver Team                                    *
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

#ifndef VSERVER_H
#define VSERVER_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdint.h>
#include <sys/types.h>

/* Constants */
#define LIBVSERVER_VERSION "0.1"

#ifdef __cplusplus
extern "C" {
#endif
	
	/* type definitions */
	typedef uint32_t xid_t;
	typedef uint32_t nid_t;
	
	/* context.c */
	int vx_get_task_xid(pid_t pid);
	
	struct vx_info {
		xid_t xid;
		pid_t initpid;
	};
	
	int vx_get_info(xid_t xid, struct vx_info *info);
	
	int vx_create(xid_t xid);
	int vx_migrate(xid_t xid);
	
	struct vx_flags {
		uint64_t flags;
		uint64_t mask;
	};
	
	int vx_set_flags(xid_t xid, const struct vx_flags *flags);
	int vx_get_flags(xid_t xid, struct vx_flags *flags);
	
	struct vx_caps {
		uint64_t bcaps;
		uint64_t ccaps;
		uint64_t cmask;
	};
	
	int vx_set_caps(xid_t xid, const struct vx_caps *caps);
	int vx_get_caps(xid_t xid, struct vx_caps *caps);
	
	/* cvirt.c */
#ifndef _VX_NAMESPACE_H /* Don't conflict with the kernel definition */
	enum vx_vhi_name_field {
		VHIN_CONTEXT=0,
		VHIN_SYSNAME,
		VHIN_NODENAME,
		VHIN_RELEASE,
		VHIN_VERSION,
		VHIN_MACHINE,
		VHIN_DOMAINNAME,
	};
#endif

	int vx_set_vhi_name(xid_t xid, uint32_t field, const char *name);
	int vx_get_vhi_name(xid_t xid, uint32_t field, char *name, size_t len);
	
	/* dlimit.c */
	int vx_add_dlimit(xid_t xid, const char *name, uint32_t flags);
	int vx_rem_dlimit(xid_t xid, const char *name);
	
	struct vx_dlimit {
		uint32_t space_used;
		uint32_t space_total;
		uint32_t inodes_used;
		uint32_t inodes_total;
		uint32_t reserved;
	};
	
	int vx_set_dlimit(xid_t xid, const char *name, const struct vx_dlimit *dlimit);
	int vx_get_dlimit(xid_t xid, const char *name, struct vx_dlimit *dlimit);
	
	/* inode.c */
	struct vx_iattr {
		uint32_t flags;
		uint32_t mask;
	};
	
	int vx_set_iattr(const char *name, const struct vx_iattr *iattr);
	int vx_get_iattr(const char *name, struct vx_iattr *iattr);
	
	/* limit.c */
	struct vx_rlimit {
		uint32_t id;
		uint64_t minimum;
		uint64_t softlimit;
		uint64_t maximum;
	};
	
	int vx_set_rlimit(xid_t xid, const struct vx_rlimit *rlimit);
	int vx_get_rlimit(xid_t xid, struct vx_rlimit *rlimit);
	
	struct vx_rlimit_mask {
		uint32_t minimum;
		uint32_t softlimit;
		uint32_t maximum;
	};
	
	int vx_get_rlimit_mask(struct vx_rlimit_mask *rlimit_mask);
	
	/* namespace.c */
	int vx_enter_namespace(xid_t xid);
	int vx_cleanup_namespace();
	int vx_set_namespace();
	
	/* network.c */
	int nx_get_task_nid(pid_t pid, nid_t *nid);
	
	struct nx_info {
		nid_t nid;
	};
	
	int nx_info(nid_t nid, struct nx_info *info);
	
	int nx_create(nid_t nid);
	int nx_migrate(nid_t nid);
	
	struct nx_net {
		uint16_t type;
		uint16_t count;
		uint32_t ip[4];
		uint32_t mask[4];
	};
	
	int nx_add_net(nid_t nid, const struct nx_net *net);
	int nx_rem_net(nid_t nid, struct nx_net *net);
	
	struct nx_flags {
		uint64_t flags;
		uint64_t mask;
	};
	
	int nx_set_flags(nid_t nid, const struct nx_flags *flags);
	int nx_get_flags(nid_t nid, struct nx_flags *flags);
	
	struct nx_caps {
		uint64_t caps;
		uint64_t mask;
	};
	
	int nx_set_caps(nid_t nid, const struct nx_caps *caps);
	int nx_get_caps(nid_t nid, struct nx_caps *caps);

#define VXSM_FILL_RATE  0x0001
#define VXSM_INTERVAL   0x0002
#define VXSM_TOKENS     0x0010
#define VXSM_TOKENS_MIN 0x0020
#define VXSM_TOKENS_MAX 0x0040
#define VXSM_PRIO_BIAS  0x0100

#define SCHED_KEEP      (-2)

	/* sched.c */
	struct vx_sched {
		uint32_t set_mask;
		int32_t fill_rate;
		int32_t interval;
		int32_t tokens;
		int32_t tokens_min;
		int32_t tokens_max;
		int32_t priority_bias;
	};
	
	int vx_set_sched(xid_t xid, const struct vx_sched *sched);
	
	/* signal.c */
	int vx_kill(xid_t xid, pid_t pid, int sig);
	
	int vx_wait_exit(xid_t xid);
	
	/* switch.c */
	int vs_get_version();
	
#ifdef __cplusplus
}
#endif

#endif /* !VSERVER_H */
