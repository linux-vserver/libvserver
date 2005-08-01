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
#include <linux/types.h>

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
#define XID_SELF   (xid_t) -1 /*!< Point to current context ID */
#define XID_ADMIN  (xid_t)  0 /*!< Context ID of the admin context */
#define XID_WATCH  (xid_t)  1 /*!< Context ID of the observer context */

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
struct vx_create {
	uint64_t flags; /*!< Context flags */
};

/*!
 * @brief Create context
 * 
 * @param xid    Context ID
 * @param create Initial create data
 */
int vx_create(xid_t xid, struct vx_create *create);

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

#define VHIN_CONTEXT    0 /*!< Context name */
#define VHIN_SYSNAME    1 /*!< System name */
#define VHIN_NODENAME   2 /*!< Network node hostname */
#define VHIN_RELEASE    3 /*!< Kernel release */
#define VHIN_VERSION    4 /*!< Kernel version */
#define VHIN_MACHINE    5 /*!< Machine hardware name */
#define VHIN_DOMAINNAME 6 /*!< Network node domainname */

/*!
 * @brief VHI name information
 */
struct vx_vhi_name {
	uint32_t field;    /*!< Name field */
	char name[VHILEN]; /*!< Name value */
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
#define NID_SELF   (nid_t) -1 /*!< Point to current context ID */
#define NID_ADMIN  (nid_t)  0 /*!< Context ID of the admin context */
#define NID_WATCH  (nid_t)  1 /*!< Context ID of the observer context */

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
struct nx_create {
	uint64_t flags;  /*!< Context flags */
};

/*!
 * @brief Create context
 * 
 * @param nid    Context ID
 * @param create Initial create data
 */
int nx_create(nid_t nid, struct nx_create *create);

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
#define SCHED_KEEP (-2) /*!< Keep scheduler setting */

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
struct vx_kill {
	int32_t pid; /*!< Process ID */
	int32_t sig; /*!< Process signal */
};

/*!
 * @brief Kill a process
 * 
 * @param xid Context ID
 * @param kill Kill options
 */
int vx_kill(xid_t xid, struct vx_kill *kill);

/*!
 * @brief Wait options
 */
struct vx_wait {
	int32_t a; /*!< Process A */
	int32_t b; /*!< Process B */
};

/*!
 * @brief Wait for processes
 * 
 * @param xid Context ID
 * @param wait Wait options
 */
int vx_wait_exit(xid_t xid, struct vx_wait *wait);
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
