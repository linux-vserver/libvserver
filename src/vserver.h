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
/*! @} syscall_context */

/*!
 * @defgroup syscall_context Context commands
 * @{
 */
/*!
 * @file  context.c
 * @brief Context commands
 */

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


/*!
 * @defgroup list List functions
 * @{
 */
/*! 
 * @brief List node
 */
typedef struct list_node_s {
	char *key;  /*!< unique key identifier */
	void *data; /*!< any data associated with key */
} list_node_t;

/*!
 * @brief List
 */
typedef struct list_s {
	list_node_t *node; /*!< first node */
	size_t n;          /*!< number of nodes */
} list_t;

/*!
 * @brief Linked lists
 */
typedef struct list_link_s {
	list_t *p; /*!< prisitine list */
	list_t *d; /*!< descending list */
} list_link_t;

/*!
 * @file list.c
 * @brief List handling and parsing functions
 */
/*!
 * @defgroup list_alloc List allocation
 * @{
 */
/*!
 * @brief Allocate memory for a list
 * 
 * @param n Number of nodes
 * 
 * @return Pointer to empty list
 */
list_t *list_alloc(size_t n);

/*!
 * @brief Deallocate list memory
 * 
 * @param list List pointer
 */
void list_dealloc(list_t *list);

/*!
 * @brief Allocate memory for a list key
 * 
 * @param str Key to be allocated
 * 
 * @return Pointer to allocated memory
 * 
 * @see LIST_DATA_ALLOC_TYPE
 * @see list_set
 */
char *list_key_alloc(char *str);

/*!
 * @brief allocate memory for list data using TYPE
 * 
 * @see list_key_alloc
 * @see list_set
 */
#define LIST_DATA_ALLOC_TYPE(NAME, TYPE) \
static inline \
TYPE *NAME ## _list_data_alloc(TYPE value) \
{ \
	TYPE *data = (TYPE *)malloc(sizeof(TYPE)); \
	*data = value; \
	return data; \
}

/*!
 * @brief Set key/data pair
 * 
 * @param node Current list node
 * @param key  Key to be set
 * @param data Data to be set
 * 
 * @see list_key_alloc
 * @see LIST_DATA_ALLOC_TYPE
 */
void list_set(list_node_t *node, char *key, void *data);
/*! @} list_alloc */

/*!
 * @defgroup list_parse Token parser
 * @{
 */
/*!
 * @brief Count tokens
 * 
 * @param str   Token string
 * @param delim Token delimiter
 * 
 * @return Number of tokens
 */
size_t list_ntokens(const char *str, const char delim);

/*!
 * @brief Extract token and modify str to point to next token
 * 
 * @param str   Token string
 * @param delim Token delimiter 
 * 
 * @return Current token
 */
char *list_parse(const char **str, const char delim);

/*!
 * @brief Extract key/value pairs
 * 
 * @param str     Token string
 * @param delim   Token delimiter
 * @param kvdelim key/value delimiter
 * 
 * @return Token list pointer
 */
list_t *list_parse_hash(const char *str, const char delim, const char kvdelim);

/*!
 * @brief Extract tokens
 * 
 * @param str   Token string
 * @param delim Token delimiter
 * 
 * @return Token list pointer
 */
list_t *list_parse_list(const char *str, const char delim);
/*! @} list_parse */

/*!
 * @defgroup list_search List search
 * @{
 */
/*!
 * @brief Perform a linear search
 * 
 * @param list List pointer
 * @param key  Key to search for in \a list
 * 
 * @return Matching node pointer
 */
list_node_t *list_search(list_t *list, char *key);
/*! @} list_search */

/*!
 * @defgroup list_validate List validation
 * @{
 */
/*!
 * @brief Validate a token based flag list
 * 
 * @param link  Pointer to a linked flag list
 * @param clmod Clear flag modifier
 * 
 * @return 0 on success, -1 otherwise; errno will be set
 */
int list_validate_flag(list_link_t *link, const char clmod);

/*!
 * @brief Validate a token based list
 * 
 * @param link Pointer to a linked list
 * 
 * @return 0 on success, -1 otherwise; errno will be set
 */
int list_validate(list_link_t *link);
/*! @} list_validate */

/*!
 * @defgroup list_convert List converters
 * @{
 */
/*!
 * @brief Convert a token based flag list to flags and a set mask
 * 
 * @param link  Pointer to a linked list
 * @param clmod Clear flag modifier
 * @param flags Pointer to flags integer
 * @param mask  Pointer to mask integer
 */
void list_list2flags(list_link_t *link, const char clmod,
                     uint64_t *flags, uint64_t *mask);
/*! @} list_convert */

/*!
 * @defgroup list_defaults Default lists
 * @brief Default lists
 * 
 * @see list_alloc
 * @see list_key_alloc
 * @see LIST_DATA_ALLOC_TYPE
 * 
 * @{
 */
/*!
 * @file bcaps-list.c
 * @brief System capability list
 */
/*!
 * @brief Initialise system capability list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/capability.h">
 *     &lt;linux/capability.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all system capabilities
 */
list_t *bcaps_list_init(void);

/*!
 * @file ccaps-list.c
 * @brief Context capability list
 */
/*!
 * @brief Initialise context capability list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/context.h">
 *     &lt;linux/vserver/context.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all context capabilities
 */
list_t *ccaps_list_init(void);

/*!
 * @file cflags-list.c
 * @brief Context flag list
 */
/*!
 * @brief Initialise context flag list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/context.h">
 *     &lt;linux/vserver/context.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all context flags
 */
list_t *cflags_list_init(void);

/*!
 * @file iattr-list.c
 * @brief Inode attribute list
 */
/*!
 * @brief Initialise inode attribute list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/inode.h">
 *     &lt;linux/vserver/inode.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all inode attributes
 */
list_t *iattr_list_init(void);

/*!
 * @file nflags-list.c
 * @brief Network context flag list
 */
/*!
 * @brief Initialise network context flag list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/network.h">
 *     &lt;linux/vserver/network.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all network context flags
 */
list_t *nflags_list_init(void);

/*!
 * @file rlimit-list.c
 * @brief Resource limit list
 */
/*!
 * @brief Initialise resource limit list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/limit.h">
 *     &lt;linux/vserver/limit.h&gt;
 *   </a>
 * \endhtmlonly
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/sys/resource.h">
 *     &lt;sys/resource.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all resource limits
 */
list_t *rlimit_list_init(void);

/*!
 * @file sched-list.c
 * @brief Scheduler mask list
 */
/*!
 * @brief Initialise scheduler mask list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/sched_cmd.h">
 *     &lt;linux/vserver/sched_cmd.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all scheduler masks
 */
list_t *sched_list_init(void);

/*!
 * @file vhi-list.c
 * @brief VHI name list
 */
/*!
 * @brief Initialise VHI name list
 * 
 * @see \htmlonly
 *   <a class="el" href="file:///usr/include/linux/vserver/cvirt_cmd.h">
 *     &lt;linux/vserver/cvirt_cmd.h&gt;
 *   </a>
 * \endhtmlonly
 * 
 * @return List of all VHI names
 */
list_t *vhi_list_init(void);
/*! @} list_defaults */

/*!
 * @defgroup list_iter List iteration
 * @brief Iterate through a list
 * 
 * @{
 */
/*!
 * @brief Iterate through LIST using IDX as counter
 */
#define list_foreach(LIST, IDX) for (size_t IDX = 0; IDX < (LIST)->n; IDX++)
/*! @} list_iter */

/*! @} list */

#endif /* _VSERVER_H_ */