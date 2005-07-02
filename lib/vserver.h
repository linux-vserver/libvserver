
#include <stdint.h>
#include <errno.h>

#include "syscall.h"

#if 	defined(__alpha__)
#define __NR_vserver	428
#elif	defined(__arm__)
#define __NR_vserver	313
#elif	defined(__cris__)
#define __NR_vserver	273
#elif	defined(__frv__)
#define __NR_vserver	273
#elif	defined(__h8300__)
#define __NR_vserver	273
#elif	defined(__i386__)
#define __NR_vserver	273
#elif	defined(__ia64__)
#define __NR_vserver	1269
#elif	defined(__m32r__)
#define __NR_vserver	__m32r_NR_vserver
#elif	defined(__mc68000__)
#define __NR_vserver	278
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI32)
#define __NR_vserver	277
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_ABI64)
#define __NR_vserver	240
#elif	defined(__mips__) && (_MIPS_SIM == _MIPS_SIM_NABI32)
#define __NR_vserver	236
#elif	defined(__hppa__)
#define __NR_vserver	__hppa_NR_vserver
#elif	defined(__powerpc__)
#define __NR_vserver	257
#elif	defined(__s390__)
#define __NR_vserver	263
#elif	defined(__sh__)
#define __NR_vserver	273
#elif	defined(__sparc__)
#define __NR_vserver	267
#elif	defined(__v850__)
#define __NR_vserver	__v850_NR_vserver
#elif	defined(__x86_64__)
#define __NR_vserver	236
#endif

static inline 
_syscall3(int, vserver, uint32_t, cmd, uint32_t, id, void *, data);
       
