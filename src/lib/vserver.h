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
#ifndef SWIG
int vserver(uint32_t cmd, uint32_t id, void *data);
#endif

/*!
 * @brief Clone system call
 *
 * @param flags         Clone flags
 * @param child_stack   Child stack
 *
 * @return Process ID in parent, 0 in child, -1 on error
 *
 * @see clone(2)
 */
#ifndef SWIG
#if defined (__s390__)
int clone(void *child_stack, int flags);
#else
int clone(int flags, void *child_stack);
#endif
#endif

/*!
 * @brief Get vserver version of running kernel
 *
 * @return Kernel version
 */
int vs_get_version(void);

/*!
 * @brief Get vserver configuration of running kernel
 *
 * @return Kernel configuration
 */
int vs_get_config(void);



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
#define VXC_SET_UTSNAME    0x00000001  /*!< Allow setdomainname(2) and sethostname(2) */
#define VXC_SET_RLIMIT     0x00000002  /*!< Allow setrlimit(2) */
#define VXC_RAW_ICMP       0x00000100  /*!< Allow raw ICMP sockets */
#define VXC_SYSLOG         0x00001000  /*!< Allow syslog(2) */
#define VXC_SECURE_MOUNT   0x00010000  /*!< Allow secure mount(2) */
#define VXC_SECURE_REMOUNT 0x00020000  /*!< Allow secure remount */
#define VXC_BINARY_MOUNT   0x00040000  /*!< Allow binary/network mounts */
#define VXC_QUOTA_CTL      0x00100000  /*!< Allow quota ioctl */
#define VXC_ADMIN_MAPPER   0x00200000  /*!< Allow access to device mapper */
#define VXC_ADMIN_CLOOP    0x00400000  /*!< Allow access to loop devices */

#define VXF_INFO_SCHED   0x00000002  /*!< Account all processes as one (L) */
#define VXF_INFO_NPROC   0x00000004  /*!< Apply process limits to context (L) */
#define VXF_INFO_PRIVATE 0x00000008  /*!< Context cannot be entered */
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
#define VXF_VIRT_TIME    0x00100000  /*!< Allow per guest time offsets */
#define VXF_HIDE_MOUNT   0x01000000  /*!< Hide entries in /proc/$pid/mounts */
#define VXF_HIDE_NETIF   0x02000000  /*!< Hide foreign network interfaces */
#define VXF_HIDE_VINFO   0x04000000  /*!< Hide context information in task status */
#define VXF_STATE_SETUP  (1ULL<<32)  /*!< Enable setup state */
#define VXF_STATE_INIT   (1ULL<<33)  /*!< Enable init state */
#define VXF_STATE_ADMIN  (1ULL<<34)  /*!< Enable admin state */
#define VXF_SC_HELPER    (1ULL<<36)  /*!< Context state change helper */
#define VXF_REBOOT_KILL  (1ULL<<37)  /*!< Kill all processes on reboot(2) */
#define VXF_PERSISTENT   (1ULL<<38)  /*!< Make context persistent */
#define VXF_FORK_RSS     (1ULL<<48)  /*!< Block fork when over RSS */
#define VXF_PROLIFIC     (1ULL<<49)  /*!< Allow context to create new contexts */
#define VXF_IGNEG_NICE   (1ULL<<52)  /*!< Ignore priority raise */

#define VXM_SET_INIT     0x00000001  /*!< Make current process the new init */
#define VXM_SET_REAPER   0x00000002  /*!< Make current process the new reaper */
#endif

#ifndef _VX_CVIRT_CMD_H
#define VHIN_CONTEXT     0
#define VHIN_SYSNAME     1
#define VHIN_NODENAME    2
#define VHIN_RELEASE     3
#define VHIN_VERSION     4
#define VHIN_MACHINE     5
#define VHIN_DOMAINNAME  6
#endif

typedef uint32_t xid_t; /*!< Context ID type */

/*!
 * @brief Context information
 */
typedef struct _vx_info {
	xid_t xid;     /*!< Context ID */
	pid_t initpid; /*!< Process ID of init */
} vx_info_t;

/*!
 * @brief Context statistics
 */
typedef struct _vx_stat {
	uint32_t usecnt;     /*!< Number of context references */
	uint32_t tasks;      /*!< Number of tasks */
	uint32_t nr_threads; /*!< Total number of threads */
	uint32_t nr_running; /*!< Number of running threads */
	uint32_t nr_unintr;  /*!< Number of uninterruptible threads */
	uint32_t nr_onhold;  /*!< Number of threads being held */
	uint32_t nr_forks;   /*!< Total number of forks since context startup */
	uint32_t load[3];    /*!< Load average */
	uint64_t offset;     /*!< Offset to the system time */
	uint64_t uptime;     /*!< Context uptime */
} vx_stat_t;

/*!
 * @brief Context/migration flags
 */
typedef struct _vx_flags {
	uint64_t flags; /*!< Flags */
	uint64_t mask;  /*!< Set mask */
} vx_flags_t;

/*!
 * @brief Virtual system information data
 */
typedef struct _vx_uname {
	uint32_t id;    /*!< Name ID */
	char value[65]; /*!< Name value */
} vx_uname_t;

/*!
 * @brief Wait results
 */
typedef struct _vx_wait {
	int32_t reboot_cmd; /*!< Context reboot command */
	int32_t exit_code;  /*!< Context exit code */
} vx_wait_t;

/*!
 * @brief Create a new context
 *
 * @param xid  Context ID
 * @param data Initial context flags
 */
int vx_create(xid_t xid, vx_flags_t *data);

/*!
 * @brief Migrate to an existing context
 *
 * @param xid  Context ID
 * @param data Migration flags
 */
int vx_migrate(xid_t xid, vx_flags_t *data);

/*!
 * @brief Get the context ID of a process
 *
 * @param pid Process ID
 *
 * @return Context ID
 */
int vx_task_xid(pid_t pid);

/*!
 * @brief Get context information
 *
 * @param xid  Context ID
 * @param data Empty vx_info_t struct to be filled
 */
int vx_info(xid_t xid, vx_info_t *data);

/*!
 * @brief Get context statistics
 *
 * @param xid  Context ID
 * @param data Empty vx_stat_t struct to be filled
 */
int vx_stat(xid_t xid, vx_stat_t *data);

/*!
 * @brief Set system capabilities
 *
 * @param xid  Context ID
 * @param data System capabilities
 */
int vx_bcaps_set(xid_t xid, vx_flags_t *data);

/*!
 * @brief Get system capabilities
 *
 * @param xid  Context ID
 * @param data Empty vx_flags_t struct to be filled
 */
int vx_bcaps_get(xid_t xid, vx_flags_t *data);

/*!
 * @brief Set context capabilities
 *
 * @param xid  Context ID
 * @param data Context capabilities
 */
int vx_ccaps_set(xid_t xid, vx_flags_t *data);

/*!
 * @brief Get context capabilities
 *
 * @param xid  Context ID
 * @param data Empty vx_flags_t struct to be filled
 */
int vx_ccaps_get(xid_t xid, vx_flags_t *data);

/*!
 * @brief Set context flags
 *
 * @param xid  Context ID
 * @param data Context flags
 */
int vx_flags_set(xid_t xid, vx_flags_t *data);

/*!
 * @brief Get context flags
 *
 * @param xid   Context ID
 * @param data Empty vx_flags_t struct to be filled
 */
int vx_flags_get(xid_t xid, vx_flags_t *data);

/*!
 * @brief Set virtual system information
 *
 * @param xid  Context ID
 * @param data Virtual system information data
 */
int vx_uname_set(xid_t xid, vx_uname_t *data);

/*!
 * @brief Get virtual system information
 *
 * @param xid  Context ID
 * @param data Empty vx_uname_t struct to be filled
 */
int vx_uname_get(xid_t xid, vx_uname_t *data);

/*!
 * @brief Kill one or more processes
 *
 * @param xid Context ID
 * @param pid Process ID
 * @param sig Signal number
 */
int vx_kill(xid_t xid, pid_t pid, int sig);

/*!
 * @brief Wait for context death
 *
 * @param xid  Context ID
 * @param data Empty vx_wait_t struct to be filled
 */
int vx_wait(xid_t xid, vx_wait_t *data);
/*! @} syscall_context */



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
#define VXSM_FORCE      0x0400  /*!< Force scheduler reload (SMP only) */
#define VXSM_CPU_ID     0x1000  /*!< CPU ID (SMP only) */
#define VXSM_BUCKET_ID  0x2000  /*!< Bucket ID */
#define VXSM_MSEC       0x4000  /*!< ?? */

#define VXSM_V3_MASK    0x0173  /*!< Mask all fields for scheduler v3 */
#define VXSM_SET_MASK   0x01FF  /*!< Mask all fields for set_sched */
#endif

/*!
 * @brief Scheduler values
 */
typedef struct _vx_sched {
	uint32_t mask;        /*!< Set mask */
	int32_t cpu_id;       /*!< CPU ID (for SMP machines) */
	int32_t bucket_id;    /*!< Token Bucket ID */
	int32_t fill_rate[2]; /*!< Fill rate */
	int32_t interval[2];  /*!< Interval between fills */
	int32_t tokens;       /*!< Number of tokens in the bucket */
	int32_t tokens_min;   /*!< Minimum tokens to unhold the context */
	int32_t tokens_max;   /*!< Maximum number of tokens in the bucket */
	int32_t prio_bias;    /*!< Priority bias */
} vx_sched_t;

/*!
 * @brief Scheduler information
 */
typedef struct _vx_sched_info {
	int32_t cpu_id;
	int32_t bucket_id;
	uint64_t user_msec;
	uint64_t sys_msec;
	uint64_t hold_msec;
	uint32_t token_usec;
	int32_t vavavoom;
} vx_sched_info_t;

/*!
 * @brief Set scheduler values
 *
 * @param xid  Context ID
 * @param data Scheduler values
 */
int vx_sched_set(xid_t xid, vx_sched_t *data);

/*!
 * @brief Get scheduler values
 *
 * @param xid  Context ID
 * @param data Scheduler values
 */
int vx_sched_get(xid_t xid, vx_sched_t *data);

/*!
 * @brief Get scheduler information
 *
 * @param xid  Context ID
 * @param data Scheduler information
 */
int vx_sched_info(xid_t xid, vx_sched_info_t *data);


/*! @} syscall_sched */



/*!
 * @defgroup syscall_rlimit Resource limit commands
 * @{
 */
#ifndef _VX_LIMIT_CMD_H
#define CRLIM_UNSET     (0ULL)  /*!< Unset resource limit */
#define CRLIM_INFINITY (~0ULL)  /*!< Infinity (no limit) */
#define CRLIM_KEEP     (~1ULL)  /*!< Keep current value */
#endif

#ifndef _VX_LIMIT_H
#define VLIMIT_NSOCK  16  /*!< Number of open sockets */
#define VLIMIT_OPENFD 17  /*!< Number of open file descriptors */
#define VLIMIT_ANON   18  /*!< Amount of anonymous memory */
#define VLIMIT_SHMEM  19  /*!< Amount of shared memory */
#define VLIMIT_SEMARY 20  /*!< Size of semary */
#define VLIMIT_NSEMS  21  /*!< Number of semaphores */
#define VLIMIT_DENTRY 22  /*!< Size of the dentry cache */
#define VLIMIT_MAPPED 23  /*!< ?? */
#endif

/*!
 * @brief Resource limits
 */
typedef struct _vx_limit {
	uint32_t id;        /*!< Limit ID */
	uint64_t minimum;   /*!< Minimum */
	uint64_t softlimit; /*!< Softlimit */
	uint64_t maximum;   /*!< Maximum */
} vx_limit_t;

/*!
 * @brief Resource limit accounting
 */
typedef struct _vx_limit_stat {
	uint32_t id;      /*!< Limit ID */
	uint32_t hits;    /*!< Number of hits */
	uint64_t value;   /*!< Current value */
	uint64_t minimum; /*!< Minimum value */
	uint64_t maximum; /*!< Maximum value */
} vx_limit_stat_t;

/*!
 * @brief Get resource limits mask
 *
 * @param data Empty vx_limit_t struct to be filled
 */
int vx_limit_mask_get(vx_limit_t *data);

/*!
 * @brief Set resource limit
 *
 * @param xid  Context ID
 * @param data Resource limits
 */
int vx_limit_set(xid_t xid, vx_limit_t *data);

/*!
 * @brief Get resource limits
 *
 * @param xid  Context ID
 * @param data Empty vx_limit_t struct to be filled
 */
int vx_limit_get(xid_t xid, vx_limit_t *data);

/*!
 * @brief Get resource limit accounting data
 *
 * @param xid  Context ID
 * @param data Empty vx_limit_stat_t struct to be filled
 */
int vx_limit_stat(xid_t xid, vx_limit_stat_t *data);

/*!
 * @brief Reset resource limit accounting data
 *
 * @param xid Context ID
 */
int vx_limit_reset(xid_t xid);
/*! @} syscall_rlimit */



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
 * @brief Disk limit values
 */
typedef struct _dx_limit {
	char *filename;        /*!< Mount point */
	uint32_t space_used;   /*!< Currently used space */
	uint32_t space_total;  /*!< Total space */
	uint32_t inodes_used;  /*!< Currently used inodes */
	uint32_t inodes_total; /*!< Total inodes */
	uint32_t reserved;     /*!< Space reserved for the root user */
	uint32_t flags;        /*!< Disk limit flags */
} dx_limit_t;

/*!
 * @brief Add disk limit entry
 *
 * @param xid  Context ID
 * @param data Disk limit information
 */
int dx_limit_add(xid_t xid, dx_limit_t *data);

/*!
 * @brief Remove disk limit
 *
 * @param xid  Context ID
 * @param data Disk limit information
 */
int dx_limit_remove(xid_t xid, dx_limit_t *data);

/*!
 * @brief Set disk limit values
 *
 * @param xid  Context ID
 * @param data Disk limit values
 */
int dx_limit_set(xid_t xid, dx_limit_t *data);

/*!
 * @brief Get disk limit values
 *
 * @param xid  Context ID
 * @param data Empty dx_limit_t struct to be filled
 */
int dx_limit_get(xid_t xid, dx_limit_t *data);
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
typedef struct _ix_attr {
	char *filename; /*!< Filename */
	xid_t xid;      /*!< Context ID */
	uint32_t flags; /*!< Inode flags */
	uint32_t mask;  /*!< Set mask */
} ix_attr_t;

/*!
 * @brief Set inode attributes
 *
 * @param data Inode attributes
 */
int ix_attr_set(ix_attr_t *data);

/*!
 * @brief Get inode attributes
 *
 * @param data Empty ix_attr_t struct to be filled
 */
int ix_attr_get(ix_attr_t *data);
/*! @} syscall_inode */



/*!
 * @defgroup syscall_space Namespace commands
 * @{
 */
#ifndef _LINUX_SCHED_H
#define CLONE_VM        0x00000100
#define CLONE_FS        0x00000200
#define CLONE_FILES     0x00000400
#define CLONE_SIGHAND   0x00000800
#define CLONE_PTRACE    0x00002000
#define CLONE_VFORK     0x00004000
#define CLONE_PARENT    0x00008000
#define CLONE_THREAD    0x00010000
#define CLONE_NEWNS     0x00020000
#define CLONE_SYSVSEM   0x00040000
#define CLONE_SETTLS    0x00080000
#define CLONE_PARENT_SETTID     0x00100000
#define CLONE_CHILD_CLEARTID    0x00200000
#define CLONE_DETACHED          0x00400000
#define CLONE_UNTRACED          0x00800000
#define CLONE_CHILD_SETTID      0x01000000
#define CLONE_STOPPED           0x02000000
#define CLONE_NEWUTS            0x04000000
#define CLONE_NEWIPC            0x08000000
#define CLONE_KTHREAD           0x10000000
#endif

/*!
 * @brief Clone the current namespace (FS/IPC/UTS)
 *
 * @param flags       Clone flags
 * @param child_stack Child stack
 */
#ifndef SWIG
int ns_clone(int flags, void *child_stack);
#endif

/*!
 * @brief Enter namespace
 *
 * @param xid Context ID
 */
int ns_enter(xid_t xid, uint64_t mask);

/*!
 * @brief Set namespace
 *
 * @param xid Context ID
 */
int ns_set(xid_t xid, uint64_t mask);
/*! @} syscall_namespace */



/*!
 * @defgroup syscall_network Network context commands
 * @{
 */
#ifndef _VX_NETWORK_H
#define NXF_INFO_PRIVATE 0x00000008  /*!< Network context cannot be entered */
#define NXF_STATE_SETUP  (1ULL<<32)  /*!< Network context is in setup state */
#define NXF_STATE_ADMIN  (1ULL<<34)  /*!< Context is in admin state */
#define NXF_SC_HELPER    (1ULL<<36)  /*!< Network state change helper */
#define NXF_PERSISTENT   (1ULL<<38)  /*!< Make network context persistent */

#define NXA_TYPE_IPV4  1              /*!< Address is IPv4 */
#define NXA_TYPE_IPV6  2              /*!< Address is IPv6 */
#define NXA_MOD_BCAST (1<<8)          /*!< Address is Broadcast*/
#define NXA_TYPE_ANY  ((uint16_t)-1)  /*!< Matches any address */
#endif

#ifndef _VX_CACCT_H
#define VXA_SOCK_UNSPEC 0
#define VXA_SOCK_UNIX   1
#define VXA_SOCK_INET   2
#define VXA_SOCK_INET6  3
#define VXA_SOCK_PACKET 4
#define VXA_SOCK_OTHER  5
#endif

#define NXA_SOCK_UNSPEC VXA_SOCK_UNSPEC
#define NXA_SOCK_UNIX   VXA_SOCK_UNIX
#define NXA_SOCK_INET   VXA_SOCK_INET
#define NXA_SOCK_INET6  VXA_SOCK_INET6
#define NXA_SOCK_PACKET VXA_SOCK_PACKET
#define NXA_SOCK_OTHER  VXA_SOCK_OTHER

typedef uint32_t nid_t; /*!< Network context ID type */

/*!
 * @brief Network context information
 */
typedef struct _nx_info {
	nid_t nid; /*!< Network context ID */
} nx_info_t;

/*!
 * @brief Network address information
 */
typedef struct _nx_addr {
	uint16_t type;    /*!< Address type */
	uint16_t count;   /*!< Number of addresses in ip/mask */
	uint32_t ip[4];   /*!< Up to four adresses */
	uint32_t mask[4]; /*!< Up to four netmasks */
} nx_addr_t;

/*!
 * @brief Network context flags
 */
typedef struct _nx_flags {
	uint64_t flags; /*!< Network context flags */
	uint64_t mask;  /*!< Set mask */
} nx_flags_t;

/*!
 * @brief Accounting data
 */
typedef struct _nx_sock_stat {
	uint32_t id;       /*!< Socket type ID */
	uint32_t count[3]; /*!< Number of packets */
	uint64_t total[3]; /*!< Number of bytes */
} nx_sock_stat_t;

/*!
 * @brief Create network context
 *
 * @param nid  Network context ID
 * @param data Initial network context flags
 */
int nx_create(nid_t nid, nx_flags_t *data);

/*!
 * @brief Migrate to an existing network context
 *
 * @param nid Network context ID
 */
int nx_migrate(nid_t nid);

/*!
 * @brief Get the network context ID of a process
 *
 * @param pid Process ID
 *
 * @return Network context ID
 */
int nx_task_nid(pid_t pid);

/*!
 * @brief Get network context information
 *
 * @param nid  Network context ID
 * @param data Empty nx_info_t struct to be filled
 */
int nx_info(nid_t nid, nx_info_t *data);

/*!
 * @brief Add network context addresses
 *
 * @param nid  Network context ID
 * @param data Network address information
 */
int nx_addr_add(nid_t nid, nx_addr_t *data);

/*!
 * @brief Remove network context addresses
 *
 * @param nid  Network context ID
 * @param data Network address information
 */
int nx_addr_remove(nid_t nid, nx_addr_t *data);

/*!
 * @brief Set network context flags
 *
 * @param nid  Network context ID
 * @param data Network context flags
 */
int nx_flags_set(nid_t nid, nx_flags_t *data);

/*!
 * @brief Get network context flags
 *
 * @param nid  Network context ID
 * @param data Empty nx_flags_t struct to be filled
 */
int nx_flags_get(nid_t nid, nx_flags_t *data);

/*!
 * @brief Set network context capabilities
 *
 * @param nid  Network context ID
 * @param data Network context capabilities
 */
int nx_caps_set(nid_t nid, nx_flags_t *data);

/*!
 * @brief Get network context capabilities
 *
 * @param nid  Network context ID
 * @param data Empty nx_flags_t struct to be filled
 */
int nx_caps_get(nid_t nid, nx_flags_t *data);

/*!
 * @brief Get network socket accounting data
 *
 * @param nid  Network context ID
 * @param data Empty nx_sock_stat_t struct to be filled
 */
int nx_sock_stat(nid_t nid, nx_sock_stat_t *data);
/*! @} syscall_network */

#endif /* _VSERVER_H_ */
