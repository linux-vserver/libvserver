#ifndef _VX_SCHED_H
#define _VX_SCHED_H

#define VXSM_FILL_RATE		0x0001
#define VXSM_INTERVAL		0x0002
#define VXSM_TOKENS		0x0010
#define VXSM_TOKENS_MIN		0x0020
#define VXSM_TOKENS_MAX		0x0040
#define VXSM_PRIO_BIAS		0x0100

#define SCHED_KEEP		(-2)


#ifdef	__KERNEL__

struct timespec;

void vx_vsi_uptime(struct timespec *, struct timespec *);


struct vx_info;

void vx_update_load(struct vx_info *);


struct task_struct;

int vx_effective_vavavoom(struct vx_info *, int);

int vx_tokens_recalc(struct vx_info *);

#endif	/* __KERNEL__ */
#else	/* _VX_SCHED_H */
#warning duplicate inclusion
#endif	/* _VX_SCHED_H */
