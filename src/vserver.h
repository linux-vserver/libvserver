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
 * @brief Interface to the vserver syscalls
 */
#ifndef _VSERVER_H
#define _VSERVER_H

#include <sys/types.h>
#include <stdint.h>

#define LIBVSERVER_API_MAJOR 2  /*!< API major version */
#define LIBVSERVER_API_MINOR 0  /*!< API minor version */

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
 * @brief Get vserver version of running kernel
 * 
 * @return API version
 */
int vs_get_version(void);

/*!
 * @defgroup syscall_context Context commands
 * @{
 */
#ifndef _LINUX_CAPABILITY_H
#define CAP_CHOWN            0
#define CAP_DAC_OVERRIDE     1
#define CAP_DAC_READ_SEARCH  2
#define CAP_FOWNER           3
#define CAP_FSETID           4
#define CAP_FS_MASK          0x1f
#define CAP_KILL             5
#define CAP_SETGID           6
#define CAP_SETUID           7
#define CAP_SETPCAP          8
#define CAP_LINUX_IMMUTABLE  9
#define CAP_NET_BIND_SERVICE 10
#define CAP_NET_BROADCAST    11
#define CAP_NET_ADMIN        12
#define CAP_NET_RAW          13
#define CAP_IPC_LOCK         14
#define CAP_IPC_OWNER        15
#define CAP_SYS_MODULE       16
#define CAP_SYS_RAWIO        17
#define CAP_SYS_CHROOT       18
#define CAP_SYS_PTRACE       19
#define CAP_SYS_PACCT        20
#define CAP_SYS_ADMIN        21
#define CAP_SYS_BOOT         22
#define CAP_SYS_NICE         23
#define CAP_SYS_RESOURCE     24
#define CAP_SYS_TIME         25
#define CAP_SYS_TTY_CONFIG   26
#define CAP_MKNOD            27
#define CAP_LEASE            28
#define CAP_AUDIT_WRITE      29
#define CAP_AUDIT_CONTROL    30
#define CAP_CONTEXT          31
#endif

#ifndef _VX_CONTEXT_H
#define VXC_CAP_MASK       0x00000000  /*!< ?? */
#define VXC_SET_UTSNAME    0x00000001  /*!< Allow setdomainname(2) and sethostname(2) */
#define VXC_SET_RLIMIT     0x00000002  /*!< Allow setrlimit(2) */
#define VXC_RAW_ICMP       0x00000100  /*!< Allow raw ICMP sockets */
#define VXC_SYSLOG         0x00001000  /*!< Allow syslog(2) */
#define VXC_SECURE_MOUNT   0x00010000  /*!< Allow secure mount(2) */
#define VXC_SECURE_REMOUNT 0x00020000  /*!< Allow secure remount */
#define VXC_BINARY_MOUNT   0x00040000  /*!< Allow binary/network mounts */
#define VXC_QUOTA_CTL      0x00100000  /*!< Allow quota ioctl */

#define VXF_INFO_LOCK    0x00000001  /*!< Prohibit further context switches (L) */
#define VXF_INFO_SCHED   0x00000002  /*!< Account all processes as one (L) */
#define VXF_INFO_NPROC   0x00000004  /*!< Apply process limits to context (L) */
#define VXF_INFO_PRIVATE 0x00000008  /*!< Context cannot be entered (L) */
#define VXF_INFO_INIT    0x00000010  /*!< Show a fake init process */
#define VXF_INFO_HIDE    0x00000020  /*!< Hide context information in task status */
#define VXF_INFO_ULIMIT  0x00000040  /*!< Apply ulimits to context (L) */
#define VXF_INFO_NSPACE  0x00000080  /*!< Use private namespace (L) */
#define VXF_SCHED_HARD   0x00000100  /*!< Enable hard scheduler */
#define VXF_SCHED_PRIO   0x00000200  /*!< Enable priority scheduler */
#define VXF_SCHED_PAUSE  0x00000400  /*!< Pause context (unschedule) */
#define VXF_VIRT_MEM     0x00010000  /*!< Virtualize memory information */
#define VXF_VIRT_UPTIME  0x00020000  /*!< Virtualize uptime information */
#define VXF_VIRT_CPU     0x00040000  /*!< Virtualize cpu usage information */
#define VXF_VIRT_LOAD    0x00080000  /*!< Virtualize load average information */
#define VXF_HIDE_MOUNT   0x01000000  /*!< Hide entries in /proc/$pid/mounts */
#define VXF_HIDE_NETIF   0x02000000  /*!< Hide foreign network interfaces */
#define VXF_STATE_SETUP  (1ULL<<32)  /*!< Context is in setup state */
#define VXF_STATE_INIT   (1ULL<<33)  /*!< Context is in init state */
#define VXF_SC_HELPER    (1ULL<<36)  /*!< Context state change helper */
#define VXF_REBOOT_KILL  (1ULL<<37)  /*!< Kill all processes on reboot(2) */
#define VXF_PERSISTENT   (1ULL<<38)  /*!< Make context persistent */
#define VXF_FORK_RSS     (1ULL<<48)  /*!< Block fork when over RSS */
#define VXF_PROLIFIC     (1ULL<<49)  /*!< Allow context to create new contexts */
#define VXF_IGNEG_NICE   (1ULL<<52)  /*!< Ignore priority raise */

#define VXM_SET_INIT     0x00000001  /*!< Make current process the new init */
#define VXM_SET_REAPER   0x00000002  /*!< Make current process the new reaper */
#endif

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
	xid_t xid;     /*!< Context ID */
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
 * @param create_flags Initial context flags
 */
int vx_create(xid_t xid, struct vx_create_flags *create_flags);

/*!
 * @brief Process migration flags
 */
struct vx_migrate_flags {
	uint64_t flags; /*!< Process flags */
};

/*!
 * @brief Migrate to an existing context
 * 
 * @param xid           Context ID
 * @param migrate_flags Migration flags
 */
int vx_migrate(xid_t xid, struct vx_migrate_flags *migrate_flags);

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
 * @param xid  Context ID
 * @param caps Empty caps struct to be filled
 */
int vx_get_caps(xid_t xid, struct vx_caps *caps);
/*! @} syscall_context */


/*!
 * @defgroup syscall_cvirt Virtualization commands
 * @{
 */
/*!
 * @brief Valid VHI fields
 */
#ifndef _VX_CVIRT_CMD_H
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

#define VHILEN 65 /*!< Maximum VHI name length */

/*!
 * @brief VHI name information
 */
struct vx_vhi_name {
	uint32_t field;     /*!< VHI field */
	char name[VHILEN];  /*!< VHI value */
};

/*!
 * @brief Set VHI names
 * 
 * @param xid      Context ID
 * @param vhi_name VHI names
 */
int vx_set_vhi_name(xid_t xid, struct vx_vhi_name *vhi_name);

/*!
 * @brief Get VHI names
 * 
 * @param xid      Context ID
 * @param vhi_name Empty VHI names struct to be filled
 */
int vx_get_vhi_name(xid_t xid, struct vx_vhi_name *vhi_name);
/*! @} syscall_cvirt */

/*!
 * @defgroup syscall_debug Debug commands
 * @{
 */
/*!
 * @brief Dump command history
 */
int vs_dump_history(void);
/*! @} syscall_debug */


/*!
 * @defgroup syscall_dlimit Disk limit commands
 * @{
 */
#ifndef _VX_DLIMIT_CMD_H
#define CDLIM_UNSET    ((uint32_t)0UL)   /*!< Unset disk limit */
#define CDLIM_INFINITY ((uint32_t)~0UL)  /*!< Infinity (no limit) */
#define CDLIM_KEEP     ((uint32_t)~1UL)  /*!< Keep current value */
#endif

/*!
 * @brief Disk limit information
 */
struct vx_dlimit_base {
	const char *filename; /*!< Mount point */
	uint32_t flags;       /*!< Disk limit flags */
};

/*!
 * @brief Add disk limit entry
 * 
 * @param xid         Context ID
 * @param dlimit_base Disk limit information
 */
int vx_add_dlimit(xid_t xid, struct vx_dlimit_base *dlimit_base);

/*!
 * @brief Remove disk limit
 * 
 * @param xid         Context ID
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
 * @param xid    Context ID
 * @param dlimit Disk limit values
 */
int vx_set_dlimit(xid_t xid, struct vx_dlimit *dlimit);

/*!
 * @brief Get disk limit values
 * 
 * @param xid    Context ID
 * @param dlimit Empty disk limit values struct to be filled
 */
int vx_get_dlimit(xid_t xid, struct vx_dlimit *dlimit);
/*! @} syscall_dlimit */


/*!
 * @defgroup syscall_inode Inode attribute commands
 * @{
 */
#ifndef _VX_INODE_H
#define IATTR_TAG       0x01000000  /*!< File is xid tagged */
#define IATTR_ADMIN     0x00000001  /*!< Accessible in xid=0 (only for /proc) */
#define IATTR_WATCH     0x00000002  /*!< Accessible in xid=1 (only for /proc) */
#define IATTR_HIDE      0x00000004  /*!< Not Accessible in xid!=(0|1) (only for /proc) */
#define IATTR_FLAGS     0x00000007  /*!< Flag mask for /proc flags */
#define IATTR_BARRIER   0x00010000  /*!< Directory barrier */
#define IATTR_IUNLINK   0x00020000  /*!< Unlink file */
#define IATTR_IMMUTABLE 0x00040000  /*!< File is immutable */
#endif

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
#ifndef _VX_LIMIT_CMD_H
#define CRLIM_UNSET     (0ULL)  /*!< Unset resource limit */
#define CRLIM_INFINITY (~0ULL)  /*!< Infinity (no limit) */
#define CRLIM_KEEP     (~1ULL)  /*!< Keep current value */
#endif

#include <sys/resource.h>

#ifndef _VX_LIMIT_H
#define VLIMIT_NSOCK  16  /*!< Number of open sockets */
#define VLIMIT_OPENFD 17  /*!< Number of open file descriptors */
#define VLIMIT_ANON   18  /*!< Amount of anonymous memory */
#define VLIMIT_SHMEM  19  /*!< Amount of shared memory */
#define VLIMIT_SEMARY 20  /*!< Size of semary */
#define VLIMIT_NSEMS  21  /*!< Number of semaphores */
#endif

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
 * @param xid    Context ID
 * @param rlimit Resource limits
 */
int vx_set_rlimit(xid_t xid, struct vx_rlimit *rlimit);

/*!
 * @brief Get resource limits
 * 
 * @param xid    Context ID
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
 * @brief Enter namespace
 * 
 * @param xid Context ID
 */
int vx_enter_namespace(xid_t xid);

/*!
 * @brief Cleanup namespace
 */
int vx_cleanup_namespace(void);

/*!
 * @brief Set namespace
 * 
 * @param xid Context ID
 */
int vx_set_namespace(xid_t xid);
/*! @} syscall_namespace */


/*!
 * @defgroup syscall_network Network context commands
 * @{
 */
#ifndef _VX_NETWORK_H
#define NXF_STATE_SETUP (1ULL<<32)  /*!< Network context is in setup state */
#define NXF_SC_HELPER   (1ULL<<36)  /*!< Network state change helper */
#define NXF_PERSISTENT  (1ULL<<38)  /*!< Make network context persistent */

#define NXA_TYPE_IPV4  1      /*!< Address is IPv4 */
#define NXA_TYPE_IPV6  2      /*!< Address is IPv6 */
#define NXA_MOD_BCAST (1<<8)  /*!< Address is Broadcast*/
#define NXA_TYPE_ANY  (~0)    /*!< Matches any address */
#endif

typedef uint32_t nid_t; /*!< Network context ID type */

/*!
 * @brief Get the network context ID of a process
 * 
 * @param pid Process ID
 * 
 * @return Network context ID
 */
int nx_get_task_nid(pid_t pid);

/*!
 * @brief Network context information
 */
struct nx_info {
	nid_t nid; /*!< Network context ID */
};

/*!
 * @brief Get network context information
 * 
 * @param nid  Network context ID
 * @param info Empty information struct to be filled
 */
int nx_get_info(nid_t nid, struct nx_info *info);

/*!
 * @brief Initial network context flags
 */
struct nx_create_flags {
	uint64_t flags;  /*!< Network context flags */
};

/*!
 * @brief Create network context
 * 
 * @param nid          Network context ID
 * @param create_flags Initial network context flags
 */
int nx_create(nid_t nid, struct nx_create_flags *create_flags);

/*!
 * @brief Migrate to an existing network context
 * 
 * @param nid Network context ID
 */
int nx_migrate(nid_t nid);

/*!
 * @brief Network address information
 */
struct nx_addr {
	uint16_t type;    /*!< Address type */
	uint16_t count;   /*!< Number of addresses in ip/mask */
	uint32_t ip[4];   /*!< Up to four adresses */
	uint32_t mask[4]; /*!< Up to four netmasks */
};

/*!
 * @brief Add network context addresses
 * 
 * @param nid  Network context ID
 * @param addr Network address information
 */
int nx_add_addr(nid_t nid, struct nx_addr *addr);

/*!
 * @brief Remove network context addresses
 * 
 * @param nid  Network context ID
 * @param addr Address information
 */
int nx_rem_addr(nid_t nid, struct nx_addr *addr);

/*!
 * @brief Network context flags
 */
struct nx_flags {
	uint64_t flags; /*!< Network context flags */
	uint64_t mask;  /*!< Set mask */
};

/*!
 * @brief Set network context flags
 * 
 * @param nid   Network context ID
 * @param flags Network context flags
 */
int nx_set_flags(nid_t nid, struct nx_flags *flags);

/*!
 * @brief Get network context flags
 * 
 * @param nid   Network context ID
 * @param flags Empty flags struct to be filled
 */
int nx_get_flags(nid_t nid, struct nx_flags *flags);

/*!
 * @brief Network context capabilities
 */
struct nx_caps {
	uint64_t caps; /*!< Network context capabilities */
	uint64_t mask; /*!< Network context capability mask */
};

/*!
 * @brief Set network context capabilities
 * 
 * @param nid  Network context ID
 * @param caps Network context capabilities
 */
int nx_set_caps(nid_t nid, struct nx_caps *caps);

/*!
 * @brief Get network context capabilities
 * 
 * @param nid  Network context ID
 * @param caps Empty caps struct to be filled
 */
int nx_get_caps(nid_t nid, struct nx_caps *caps);
/*! @} syscall_network */


/*!
 * @defgroup syscall_sched CPU scheduler commands
 * @{
 */
#ifndef _VX_SCHED_CMD_H
#define VXSM_FILL_RATE  0x0001  /*!< Fill Rate */
#define VXSM_INTERVAL   0x0002  /*!< Interval */
#define VXSM_FILL_RATE2 0x0004  /*!< IDLE Fill Rate */
#define VXSM_INTERVAL2  0x0008  /*!< IDLE Interval */
#define VXSM_TOKENS     0x0010  /*!< Amount of tokens */
#define VXSM_TOKENS_MIN 0x0020  /*!< Minimum amount of tokens */
#define VXSM_TOKENS_MAX 0x0040  /*!< Maximum amount of tokens */
#define VXSM_PRIO_BIAS  0x0100  /*!< Priority bias */
#define VXSM_IDLE_TIME  0x0200  /*!< Use IDLE time settings */
#define VXSM_CPU_ID     0x1000  /*!< CPU ID (for SMP) */
#define VXSM_BUCKET_ID  0x2000  /*!< Bucket ID */

#define VXSM_V3_MASK    0x0173  /*!< Mask IDLE flags (for scheduler v3) */
#endif

/*!
 * @brief Scheduler values
 */
struct vx_sched {
	uint32_t set_mask;  /*!< Set mask */
	int32_t fill_rate;  /*!< Fill rate */
	int32_t interval;   /*!< Interval between fills */
	int32_t tokens;     /*!< Number of tokens in the bucket */
	int32_t tokens_min; /*!< Minimum tokens to unhold the context */
	int32_t tokens_max; /*!< Maximum number of tokens in the bucket */
	int32_t prio_bias;  /*!< Priority bias */
	int32_t cpu_id;     /*!< CPU ID (for SMP machines) */
	int32_t bucket_id;  /*!< Token Bucket ID */
};

/*!
 * @brief Set scheduler values
 * 
 * @param xid   Context ID
 * @param sched Scheduler values
 */
int vx_set_sched(xid_t xid, struct vx_sched *sched);
/*! @} syscall_sched */


/*!
 * @defgroup syscall_signal Process signal commands
 * @{
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
 * @brief Wait results
 */
struct vx_wait_result {
	int32_t reboot_cmd; /*!< context reboot command */
	int32_t exit_code;  /*!< context exit code */
};

/*!
 * @brief Wait for processes
 * 
 * @param xid         Context ID
 * @param wait_result Wait result
 */
int vx_wait(xid_t xid, struct vx_wait_result *wait_result);
/*! @} syscall_signal */

#endif /* _VSERVER_H_ */
