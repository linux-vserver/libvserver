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
#ifndef _VSERVER_H
#define _VSERVER_H

#include <stdint.h>
#include <sys/types.h>

/*!
 * @defgroup syscall System calls
 * @{
 */
/*!
 * @file syscall.c
 * @brief System calls
 */
/*!
 * @brief Main vserver syscall interface
 * 
 * @param cmd  Command number
 * @param id   Context ID (sometimes process id)
 * @param data Data structures
 * 
 * @return Syscall return code
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/switch.h">
 *     &lt;linux/vserver/switch.h&gt;
 *   </a>
 * \endhtmlonly
 */
int sys_vserver(uint32_t cmd, uint32_t id, void *data);

/*!
 * @brief Linux personality syscall interface
 * 
 * @param pers Personality type
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/personality.h">
 *     &lt;linux/personality.h&gt;
 *   </a>
 * \endhtmlonly
 */
int sys_personality(int pers);

/*!
 * @defgroup syscall_context Context commands
 * @{
 */
/*!
 * @file  context.c
 * @brief Context commands
 */

/* context flags */
#define VXF_INFO_LOCK    0x00000001
#define VXF_INFO_SCHED   0x00000002
#define VXF_INFO_NPROC   0x00000004
#define VXF_INFO_PRIVATE 0x00000008
#define VXF_INFO_INIT    0x00000010
#define VXF_INFO_HIDE    0x00000020
#define VXF_INFO_ULIMIT  0x00000040
#define VXF_INFO_NSPACE  0x00000080
#define VXF_SCHED_HARD   0x00000100
#define VXF_SCHED_PRIO   0x00000200
#define VXF_SCHED_PAUSE  0x00000400
#define VXF_VIRT_MEM     0x00010000
#define VXF_VIRT_UPTIME  0x00020000
#define VXF_VIRT_CPU     0x00040000
#define VXF_VIRT_LOAD    0x00080000
#define VXF_HIDE_MOUNT   0x01000000
#define VXF_HIDE_NETIF   0x02000000
#define VXF_STATE_SETUP  (1ULL<<32)
#define VXF_STATE_INIT   (1ULL<<33)
#define VXF_STATE_HELPER (1ULL<<36)
#define VXF_FORK_RSS     (1ULL<<48)
#define VXF_PROLIFIC     (1ULL<<49)
#define VXF_IGNEG_NICE   (1ULL<<52)
#define VXF_ONE_TIME     (0x0003ULL<<32)
#define VXF_INIT_SET     (VXF_STATE_SETUP|VXF_STATE_INIT)

/* context caps */
#define	VXC_CAP_MASK       0x00000000
#define VXC_SET_UTSNAME    0x00000001
#define VXC_SET_RLIMIT     0x00000002
#define VXC_RAW_ICMP       0x00000100
#define VXC_SYSLOG         0x00001000
#define VXC_SECURE_MOUNT   0x00010000
#define VXC_SECURE_REMOUNT 0x00020000
#define VXC_BINARY_MOUNT   0x00040000
#define VXC_QUOTA_CTL      0x00100000

typedef uint32_t xid_t; /*!< Context ID type */

/*!
 * @brief Get the context ID of a process
 * 
 * @param pid Process ID
 * 
 * @return Context ID
 */
int vx_get_task_xid(pid_t pid);

/*!
 * @brief Context information
 */
struct vx_info {
	xid_t xid; /*!< Context ID */
	pid_t initpid; /*!< Process ID of init */
};

/*!
 * @brief Get context information
 * 
 * @param xid  Context ID
 * @param info Empty information struct to be filled
 */
int vx_get_info(xid_t xid, struct vx_info *info);

/*!
 * @brief Initial Context flags
 */
struct vx_create_flags {
	uint64_t flags; /*!< Context flags */
};

/*!
 * @brief Create context
 * 
 * @param xid          Context ID
 * @param create_flags Initial create data
 */
int vx_create(xid_t xid, struct vx_create_flags *create_flags);

/*!
 * @brief Migrate to an existing context
 * 
 * @param xid Context ID
 */
int vx_migrate(xid_t xid);

/*!
 * @brief Context flags
 */
struct vx_flags {
	uint64_t flags; /*!< Context flags */
	uint64_t mask;  /*!< Set mask */
};

/*!
 * @brief Set context flags
 * 
 * @param xid   Context ID
 * @param flags Context flags
 */
int vx_set_flags(xid_t xid, struct vx_flags *flags);

/*!
 * @brief Get context flags
 * 
 * @param xid   Context ID
 * @param flags Empty flags struct to be filled
 */
int vx_get_flags(xid_t xid, struct vx_flags *flags);

/*!
 * @brief Context capabilities
 */
struct vx_caps {
	uint64_t bcaps; /*!< System capabilities */
	uint64_t bmask; /*!< System capability mask */
	uint64_t ccaps; /*!< Context capabilities */
	uint64_t cmask; /*!< Context capability mask */
};

/*!
 * @brief Set context capabilities
 * 
 * @param xid  Context ID
 * @param caps Context capabilities
 */
int vx_set_caps(xid_t xid, struct vx_caps *caps);

/*!
 * @brief Get context capabilities
 * 
 * @param xid Context ID
 * @param caps Empty caps struct to be filled
 */
int vx_get_caps(xid_t xid, struct vx_caps *caps);
/*! @} syscall_context */


/*!
 * @defgroup syscall_cvirt Virtualization commands
 * @{
 */
/*!
 * @file cvirt.c
 * @brief Virtualization commands
 */
#define VHILEN 65 /*!< Maximum VHI string length */

/* field types */
enum vhi_name_field {
	VHIN_CONTEXT=0,
	VHIN_SYSNAME,
	VHIN_NODENAME,
	VHIN_RELEASE,
	VHIN_VERSION,
	VHIN_MACHINE,
	VHIN_DOMAINNAME,
};

/*!
 * @brief VHI name information
 */
struct vx_vhi_name {
	uint32_t field; /*!< Name field */
	char name[VHILEN];  /*!< Name value */
};

/*!
 * @brief Set VHI names
 * 
 * @param xid Context ID
 * @param vhi_name VHI names
 */
int vx_set_vhi_name(xid_t xid, struct vx_vhi_name *vhi_name);

/*!
 * @brief Get VHI names
 * 
 * @param xid Context ID
 * @param vhi_name Empty VHI names struct to be filled
 */
int vx_get_vhi_name(xid_t xid, struct vx_vhi_name *vhi_name);
/*! @} syscall_cvirt */

/*!
 * @defgroup syscall_debug Debug commands
 * @{
 */
/*!
 * @file debug.c
 * @brief Debug commands
 */
/*!
 * @brief Dump command history
 * 
 * Dumps the current command history
 */
int vs_dump_history(void);
/*! @} syscall_debug */


/*!
 * @defgroup syscall_dlimit Disk limit commands
 * @{
 */
/*!
 * @file dlimit.c
 * @brief Disk limit commands
 */

/* special disk limit values */
#define CDLIM_UNSET     (0U)
#define CDLIM_INFINITY (~0U)
#define CDLIM_KEEP     (~1U)

/*!
 * @brief Disk limit information
 */
struct vx_dlimit_base {
	const char *filename; /*!< Mount point */
	uint32_t flags;       /*!< Disk limit flags */
};

/*!
 * @brief Add Disk limit entry
 * 
 * @param xid Context ID
 * @param dlimit_base Disk limit information
 */
int vx_add_dlimit(xid_t xid, struct vx_dlimit_base *dlimit_base);

/*!
 * @brief Remove Disk limit
 * 
 * @param xid Context ID
 * @param dlimit_base Disk limit information
 */
int vx_rem_dlimit(xid_t xid, struct vx_dlimit_base *dlimit_base);

/*!
 * @brief Disk limit values
 */
struct vx_dlimit {
	const char *filename;  /*!< Mount point */
	uint32_t space_used;   /*!< Currently used space */
	uint32_t space_total;  /*!< Total space */
	uint32_t inodes_used;  /*!< Currently used inodes */
	uint32_t inodes_total; /*!< Total inodes */
	uint32_t reserved;     /*!< Space reserved for the root user */
	uint32_t flags;        /*!< Disk limit flags */
};

/*!
 * @brief Set disk limit values
 * 
 * @param xid Context ID
 * @param dlimit Disk limit values
 */
int vx_set_dlimit(xid_t xid, struct vx_dlimit *dlimit);

/*!
 * @brief Get disk limit values
 * 
 * @param xid Context ID
 * @param dlimit Empty disk limit values struct to be filled
 */
int vx_get_dlimit(xid_t xid, struct vx_dlimit *dlimit);
/*! @} syscall_dlimit */


/*!
 * @defgroup syscall_inode Inode attribute commands
 * @{
 */
/*!
 * @file inode.c
 * @brief XID Inode attribute commands
 */

/* inode attributes */
#define IATTR_XID       0x01000000
#define IATTR_ADMIN     0x00000001
#define IATTR_WATCH     0x00000002
#define IATTR_HIDE      0x00000004
#define IATTR_FLAGS     0x00000007
#define IATTR_BARRIER   0x00010000
#define IATTR_IUNLINK   0x00020000
#define IATTR_IMMUTABLE 0x00040000

/*!
 * @brief Inode attributes
 */
struct vx_iattr {
	const char *filename; /*!< Filename */
	xid_t xid;            /*!< Context ID */
	uint32_t flags;       /*!< Inode flags */
	uint32_t mask;        /*!< Set mask */
};

/*!
 * @brief Set inode attributes
 * 
 * @param iattr Inode attributes
 */
int vx_set_iattr(struct vx_iattr *iattr);

/*!
 * @brief Get inode attributes
 * 
 * @param iattr Inode attributes
 */
int vx_get_iattr(struct vx_iattr *iattr);
/*! @} syscall_inode */


/*!
 * @defgroup syscall_limit Resource limit commands
 * @{
 */
/*!
 * @file limit.c
 * @brief Resource limit commands
 */

/* special resource limit values */
#define CRLIM_UNSET     (0ULL)
#define CRLIM_INFINITY (~0ULL)
#define CRLIM_KEEP     (~1ULL)

/*!
 * @brief Resource limits
 */
struct vx_rlimit {
	uint32_t id;        /*!< Limit ID */
	uint64_t minimum;   /*!< Minimum */
	uint64_t softlimit; /*!< Softlimit */
	uint64_t maximum;   /*!< Maximum */
};

/*!
 * @brief Set resource limit
 * 
 * @param xid Context ID
 * @param rlimit Resource limits
 */
int vx_set_rlimit(xid_t xid, struct vx_rlimit *rlimit);

/*!
 * @brief Get resource limits
 * 
 * @param xid Context ID
 * @param rlimit Empty resource limits struct to be filled
 */
int vx_get_rlimit(xid_t xid, struct vx_rlimit *rlimit);

/*!
 * @brief Resource limits mask
 */
struct vx_rlimit_mask {
	uint32_t minimum;   /*!< Minimum */
	uint32_t softlimit; /*!< Softlimit */
	uint32_t maximum;   /*!< Maximum */
};

/*!
 * @brief Get resource limits mask
 * 
 * @param rmask Empty resource limits mask struct to be filled
 */
int vx_get_rlimit_mask(struct vx_rlimit_mask *rmask);
/*! @} syscall_limit */


/*!
 * @defgroup syscall_namespace Filesystem namespace commands
 * @{
 */
/*!
 * @file namespace.c
 * @brief Filesystem namespace commands
 */
/*!
 * @brief Enter namespace
 * 
 * @param xid Context ID
 */
int vx_enter_namespace(xid_t xid);

/*!
 * @brief Cleanup namespace
 * 
 * Cleanup namespace
 */
int vx_cleanup_namespace(void);

/*!
 * @brief Set namespace
 * 
 * Make current namespace the namespace of current context
 */
int vx_set_namespace(void);
/*! @} syscall_namespace */


/*!
 * @defgroup syscall_network Network context commands
 * @{
 */
/*!
 * @file network.c
 * @brief Network context commands
 */

/* network flags */
#define NXF_STATE_SETUP  (1ULL<<32)
#define NXF_STATE_HELPER (1ULL<<36)
#define NXF_ONE_TIME     (0x0001ULL<<32)
#define NXF_INIT_SET     (0)

/* address types */
#define NXA_TYPE_IPV4 1
#define NXA_TYPE_IPV6 2
#define NXA_MOD_BCAST (1<<8)
#define NXA_TYPE_ANY  (~0)

typedef uint32_t nid_t; /*!< Network context ID type */

/*!
 * @brief Get the context ID of a process
 * 
 * @param pid Process ID
 * 
 * @return Context ID
 */
int nx_get_task_nid(pid_t pid);

/*!
 * @brief Context information
 */
struct nx_info {
	nid_t nid; /*!< Context ID */
};

/*!
 * @brief Get context information
 * 
 * @param nid  Context ID
 * @param info Empty information struct to be filled
 */
int nx_get_info(nid_t nid, struct nx_info *info);

/*!
 * @brief Initial Context flags
 */
struct nx_create_flags {
	uint64_t flags;  /*!< Context flags */
};

/*!
 * @brief Create context
 * 
 * @param nid          Context ID
 * @param create_flags Initial create data
 */
int nx_create(nid_t nid, struct nx_create_flags *create_flags);

/*!
 * @brief Migrate to an existing context
 * 
 * @param nid Context ID
 */
int nx_migrate(nid_t nid);

/*!
 * @brief Address information
 */
struct nx_addr {
	uint16_t type;    /*!< Address type */
	uint16_t count;   /*!< Count */
	uint32_t ip[4];   /*!< Adress */
	uint32_t mask[4]; /*!< Mask */
};

/*!
 * @brief Add context address
 * 
 * @param nid Context ID
 * @param net Address information
 */
int nx_add_addr(nid_t nid, struct nx_addr *net);

/*!
 * @brief Remove context address
 * 
 * @param nid Context ID
 * @param net Address information
 */
int nx_rem_addr(nid_t nid, struct nx_addr *net);

/*!
 * @brief Context flags
 */
struct nx_flags {
	uint64_t flags; /*!< Context flags */
	uint64_t mask;  /*!< Set mask */
};

/*!
 * @brief Set context flags
 * 
 * @param nid   Context ID
 * @param flags Context flags
 */
int nx_set_flags(nid_t nid, struct nx_flags *flags);

/*!
 * @brief Get context flags
 * 
 * @param nid   Context ID
 * @param flags Empty flags struct to be filled
 */
int nx_get_flags(nid_t nid, struct nx_flags *flags);

/*!
 * @brief Context capabilities
 */
struct nx_caps {
	uint64_t caps; /*!< Context capabilities */
	uint64_t mask; /*!< Context capability mask */
};

/*!
 * @brief Set context capabilities
 * 
 * @param nid  Context ID
 * @param caps Context capabilities
 */
int nx_set_caps(nid_t nid, struct nx_caps *caps);

/*!
 * @brief Get context capabilities
 * 
 * @param nid Context ID
 * @param caps Empty caps struct to be filled
 */
int nx_get_caps(nid_t nid, struct nx_caps *caps);
/*! @} syscall_network */


/*!
 * @defgroup syscall_sched CPU scheduler commands
 * @{
 */
/*!
 * @file sched.c
 * @brief CPU scheduler commands
 */

/* set mask */
#define VXSM_FILL_RATE  0x0001
#define VXSM_INTERVAL   0x0002
#define VXSM_TOKENS     0x0010
#define VXSM_TOKENS_MIN 0x0020
#define VXSM_TOKENS_MAX 0x0040
#define VXSM_PRIO_BIAS  0x0100

/*!
 * @brief Scheduler values
 */
struct vx_sched {
	uint32_t set_mask;     /*!< Set mask */
	int32_t fill_rate;     /*!< Fill rate */
	int32_t interval;      /*!< Interval between fills */
	int32_t tokens;        /*!< Number of tokens in the bucket */
	int32_t tokens_min;    /*!< Minimum tokens to unhold the context */
	int32_t tokens_max;    /*!< Maximum number of tokens in the bucket */
	int32_t priority_bias; /*!< Priority bias (unused) */
};

/*!
 * @brief Set scheduler values
 * 
 * @param xid Context ID
 * @param sched Scheduler values
 */
int vx_set_sched(xid_t xid, struct vx_sched *sched);
/*! @} syscall_sched */


/*!
 * @defgroup syscall_signal Process signal commands
 * @{
 */
/*!
 * @file signal.c
 * @brief Process signal commands
 */
/*!
 * @brief Kill options
 */
struct vx_kill_opts {
	int32_t pid; /*!< Process ID */
	int32_t sig; /*!< Process signal */
};

/*!
 * @brief Kill a process
 * 
 * @param xid       Context ID
 * @param kill_opts Kill options
 */
int vx_kill(xid_t xid, struct vx_kill_opts *kill_opts);

/*!
 * @brief Wait options
 */
struct vx_wait_opts {
	int32_t a; /*!< Process A */
	int32_t b; /*!< Process B */
};

/*!
 * @brief Wait for processes
 * 
 * @param xid       Context ID
 * @param wait_opts Wait options
 */
int vx_wait(xid_t xid, struct vx_wait_opts *wait_opts);
/*! @} syscall_signal */


/*!
 * @file switch.c
 * @brief Generic commands
 */
/*!
 * @brief Get vserver version
 * 
 * Get vserver API version of running kernel
 */
int vs_get_version(void);

/*! @} syscall */

#endif /* _VSERVER_H_ */
