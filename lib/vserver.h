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

/*!
 * @file vserver.h
 * @brief Interface to libvserver
 */
#ifndef _VSERVER_H_
#define _VSERVER_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdint.h>
#include <sys/types.h>

/// @cond
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
#else
# define BEGIN_C_DECLS /* empty */
# define END_C_DECLS /* empty */
#endif

BEGIN_C_DECLS
/// @endcond

/*!
 * @file syscall.c
 * @brief main vserver syscall interface
 */

/*!
 * @brief main vserver syscall interface
 */
int vserver(uint32_t cmd, uint32_t id, void *data);

/*!
 * @file  context.c
 * @brief Context related methods
 */

/*!
 * @def   XID_SELF
 * @brief Point to current xid
 */
/*!
 * @def   XID_ADMIN
 * @brief Admin/Host context id (usually 0)
 */
/*!
 * @def   XID_WATCH
 * @brief Id of the watch context
 */
#define XID_SELF   (xid_t) -1 
#define XID_ADMIN  (xid_t)  0
#define XID_WATCH  (xid_t)  1

/*!
 * @brief   Context id type
 */
typedef uint32_t xid_t;

/*!
 * @brief Return context id of process pid
 */
int vx_get_task_xid(pid_t pid);

/*!
 * @brief Structure containing data about a context (context id, initpid)
 */
struct vx_info {
	xid_t xid;
	pid_t initpid;
};

/*!
 * @brief Return information about a context
 */
int vx_get_info(xid_t xid, struct vx_info *info);

/*!
 * @brief Create context
 */
int vx_create(xid_t xid, uint64_t flags);

/*!
 * @brief Migrate to an existing context
 */
int vx_migrate(xid_t xid);

/*!
 * @brief Structure holding context flags
 */
struct vx_flags {
	uint64_t flags;
	uint64_t mask;
};

/*!
 * @brief vx_set_flags
 */
int vx_set_flags(xid_t xid, struct vx_flags *flags);

/*!
 * @brief vx_get_flags
 */
int vx_get_flags(xid_t xid, struct vx_flags *flags);

/*!
 * @brief vx_caps
 */
struct vx_caps {
	uint64_t bcaps;
	uint64_t bmask;
	uint64_t ccaps;
	uint64_t cmask;
};

/*!
 * @brief vx_set_caps
 */
int vx_set_caps(xid_t xid, struct vx_caps *caps);

/*!
 * @brief vx_get_caps
 */
int vx_get_caps(xid_t xid, struct vx_caps *caps);



/*!
 * @file cvirt.c
 * @brief Virtual host information related functions
 */

/*!
 * @brief Length of VHI name fields
 */
#define VHI_SIZE 65

/*!
 * @brief vhi_name_field
 */
#ifndef _VX_CVIRT_CMD_H /* Don't conflict with the kernel definition */
enum vhi_name_field {
	VHIN_CONTEXT=0,
	VHIN_SYSNAME,
	VHIN_NODENAME,
	VHIN_RELEASE,
	VHIN_VERSION,
	VHIN_MACHINE,
	VHIN_DOMAINNAME,
};
#endif

/*!
 * @brief vx_set_vhi_name
 */
int vx_set_vhi_name(xid_t xid, uint32_t field, char *name);

/*!
 * @brief vx_get_vhi_name
 */
int vx_get_vhi_name(xid_t xid, uint32_t field, char *name, size_t len);


/*!
 * @file debug.c
 * @brief Debugging functions
 */

/*!
 * @brief vx_dump_history
 */
int vs_dump_history();

/*!
 * @file dlimit.c
 * @brief Disk limit related functions
 */

/*!
 * @brief vx_add_dlimit
 */
int vx_add_dlimit(xid_t xid, const char *name, uint32_t flags);

/*!
 * @brief vx_rem_dlimit
 */
int vx_rem_dlimit(xid_t xid, const char *name);

/*!
 * @brief vx_dlimit
 */
struct vx_dlimit {
	uint32_t space_used;
	uint32_t space_total;
	uint32_t inodes_used;
	uint32_t inodes_total;
	uint32_t reserved;
	uint32_t flags;
};

/*!
 * @brief vx_set_dlimit
 */
int vx_set_dlimit(xid_t xid, const char *name, struct vx_dlimit *dlimit);

/*!
 * @brief vx_get_dlimit
 */
int vx_get_dlimit(xid_t xid, const char *name, struct vx_dlimit *dlimit);



/*!
 * @file inode.c
 * @brief XID tagging related functions
 */

/*!
 * @brief vx_iattr
 */
struct vx_iattr {
	xid_t xid;
	uint32_t flags;
	uint32_t mask;
};

/*!
 * @brief vx_get_dlimit
 */
int vx_set_iattr(const char *name, struct vx_iattr *iattr);

/*!
 * @brief vx_get_dlimit
 */
int vx_get_iattr(const char *name, struct vx_iattr *iattr);



/*!
 * @file limit.c
 * @brief Resource limits
 */

/*!
 * @brief vx_get_dlimit
 */
struct vx_rlimit {
	uint64_t minimum;
	uint64_t softlimit;
	uint64_t maximum;
};

/*!
 * @brief vx_get_dlimit
 */
int vx_set_rlimit(xid_t xid, uint32_t id, struct vx_rlimit *rlimit);

/*!
 * @brief vx_get_dlimit
 */
int vx_get_rlimit(xid_t xid, uint32_t id, struct vx_rlimit *rlimit);

/*!
 * @brief vx_get_dlimit
 */
struct vx_rlimit_mask {
	uint32_t minimum;
	uint32_t softlimit;
	uint32_t maximum;
};

/*!
 * @brief vx_get_dlimit
 */
int vx_get_rlimit_mask(struct vx_rlimit_mask *rmask);



/*!
 * @file namespace.c
 * @brief Filesystem Namespaces
 */

/*!
 * @brief vx_get_dlimit
 */
int vx_enter_namespace(xid_t xid);

/*!
 * @brief vx_get_dlimit
 */
int vx_cleanup_namespace();

/*!
 * @brief vx_get_dlimit
 */
int vx_set_namespace();



/*!
 * @file network.c
 * @brief Network contexts
 */

/*!
 * @def   NID_SELF
 * @brief Point to current xid
 */
/*!
 * @def   NID_ADMIN
 * @brief Point to current xid
 */
/*!
 * @def   NID_WATCH
 * @brief Point to current xid
 */
#define NID_SELF   (nid_t) -1
#define NID_ADMIN  (nid_t)  0
#define NID_WATCH  (nid_t)  1

/*!
 * @brief   Network context id type
 */
typedef uint32_t nid_t;

/*!
 * @brief vx_get_dlimit
 */
int nx_get_task_nid(pid_t pid);

/*!
 * @brief vx_get_dlimit
 */
struct nx_info {
	nid_t nid;
};

/*!
 * @brief vx_get_dlimit
 */
int nx_get_info(nid_t nid, struct nx_info *info);

/*!
 * @brief vx_get_dlimit
 */
int nx_create(nid_t nid, uint64_t flags);

/*!
 * @brief vx_get_dlimit
 */
int nx_migrate(nid_t nid);

/*!
 * @brief vx_get_dlimit
 */
struct nx_addr {
	uint16_t type;
	uint16_t count;
	uint32_t ip[4];
	uint32_t mask[4];
};

/*!
 * @brief vx_get_dlimit
 */
int nx_add_addr(nid_t nid, struct nx_addr *net);

/*!
 * @brief vx_get_dlimit
 */
int nx_rem_addr(nid_t nid, struct nx_addr *net);

/*!
 * @brief vx_get_dlimit
 */
struct nx_flags {
	uint64_t flags;
	uint64_t mask;
};

/*!
 * @brief vx_get_dlimit
 */
int nx_set_flags(nid_t nid, struct nx_flags *flags);

/*!
 * @brief vx_get_dlimit
 */
int nx_get_flags(nid_t nid, struct nx_flags *flags);

/*!
 * @brief vx_get_dlimit
 */
struct nx_caps {
	uint64_t caps;
	uint64_t mask;
};

/*!
 * @brief vx_get_dlimit
 */
int nx_set_caps(nid_t nid, struct nx_caps *caps);

/*!
 * @brief vx_get_dlimit
 */
int nx_get_caps(nid_t nid, struct nx_caps *caps);



/*!
 * @file sched.c
 * @brief Hard CPU scheduler
 */

/*!
 * @def   VXSM_FILL_RATE
 * @brief Point to current xid
 */
/*!
 * @def   VXSM_INTERVAL
 * @brief Point to current xid
 */
/*!
 * @def   VXSM_TOKENS
 * @brief Point to current xid
 */
/*!
 * @def   VXSM_TOKENS_MIN
 * @brief Point to current xid
 */
/*!
 * @def   VXSM_TOKENS_MAX
 * @brief Point to current xid
 */
/*!
 * @def   VXSM_PRIO_BIAS
 * @brief Point to current xid
 */
#define VXSM_FILL_RATE  0x0001
#define VXSM_INTERVAL   0x0002
#define VXSM_TOKENS     0x0010
#define VXSM_TOKENS_MIN 0x0020
#define VXSM_TOKENS_MAX 0x0040
#define VXSM_PRIO_BIAS  0x0100

/*!
 * @brief Keep scheduler setting
 */
#define SCHED_KEEP      (-2)

/*!
 * @brief vx_get_dlimit
 */
struct vx_sched {
	uint32_t set_mask;
	int32_t fill_rate;
	int32_t interval;
	int32_t tokens;
	int32_t tokens_min;
	int32_t tokens_max;
	int32_t priority_bias;
};

/*!
 * @brief vx_get_dlimit
 */
int vx_set_sched(xid_t xid, struct vx_sched *sched);



/*!
 * @file signal.c
 * @brief Context signals
 */

/*!
 * @brief vx_get_dlimit
 */
int vx_kill(xid_t xid, pid_t pid, int sig);

/*!
 * @brief vx_get_dlimit
 */
int vx_wait_exit(xid_t xid);



/*!
 * @file switch.c
 * @brief common functions
 */

/*!
 * @brief vx_get_dlimit
 */
int vs_get_version();

/*! @cond */
END_C_DECLS
/*! @endcond */

#endif /* _VSERVER_H_ */
