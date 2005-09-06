#ifndef _VX_CVIRT_H
#define _VX_CVIRT_H

enum vhi_name_field {
	VHIN_CONTEXT=0,
	VHIN_SYSNAME,
	VHIN_NODENAME,
	VHIN_RELEASE,
	VHIN_VERSION,
	VHIN_MACHINE,
	VHIN_DOMAINNAME,
};

#ifdef	__KERNEL__

struct timespec;

void vx_vsi_uptime(struct timespec *, struct timespec *);


struct vx_info;

void vx_update_load(struct vx_info *);


int vx_uts_virt_handler(struct ctl_table *ctl, int write, xid_t xid,
	void **datap, size_t *lenp);


int vx_do_syslog(int, char __user *, int);

#endif	/* __KERNEL__ */
#else	/* _VX_CVIRT_H */
#warning duplicate inclusion
#endif	/* _VX_CVIRT_H */
