#ifndef	__SYSCALL_NEW_H
#define	__SYSCALL_NEW_H


#define	____sc_asm		__asm__
#define	____sc_asm_vol		__asm__ __volatile__

#ifndef	__syscall_retval
#define	__syscall_retval(v)	do { } while(0)
#endif

#ifndef	__syscall_error
#define	__syscall_error(e)	do { errno = (e); } while(0)
#endif

#ifndef	__stringify0
#define	__stringify0(val)	#val
#endif

#ifndef	__stringify
#define	__stringify(val)	__stringify0(val)
#endif


#define	__comment(name)							\
	"\t/* kernel sys_" #name "[" __stringify(__NR_##name) "] */"



#define	__casm(n,a,r,v,w)	__casm_##n##a(v,w,r)

#ifdef	__PIC__
#define	__pasm(n,a,r,v,w)	__casm(n,a,r,v,w)
#define	__Pasm(n,a,r,v,w)
#else
#define	__pasm(...)
#define	__Pasm(n,a,r,v,w)	__casm(n,a,r,v,w)
#endif

#define	__casm_use_10(v)
#define	__casm_use_11(v)	v
#define	__casm_use_12(v)
#define	__casm_use_13(v)	v

#define	__casm_use_20(v)
#define	__casm_use_21(v)
#define	__casm_use_22(v)	v
#define	__casm_use_23(v)	v

#define	__casm_use(q,r,v)	v __casm_use_##q##r("\n\t")

#define	__casm_00(v,w,r)	__casm_use(1,r,v)
#define	__casm_01(v,w,r)	__casm_use(2,r,w)
#define	__casm_02(v,w,r)	__casm_use(2,r,w)
#define	__casm_03(v,w,r)	__casm_use(2,r,w)
#define	__casm_04(v,w,r)	__casm_use(2,r,w)
#define	__casm_05(v,w,r)	__casm_use(2,r,w)
#define	__casm_06(v,w,r)	__casm_use(2,r,w)
#define	__casm_07(v,w,r)	__casm_use(2,r,w)

#define	__casm_10(v,w,r)	__casm_use(1,r,v)
#define	__casm_11(v,w,r)	__casm_use(1,r,v)
#define	__casm_12(v,w,r)	__casm_use(2,r,w)
#define	__casm_13(v,w,r)	__casm_use(2,r,w)
#define	__casm_14(v,w,r)	__casm_use(2,r,w)
#define	__casm_15(v,w,r)	__casm_use(2,r,w)
#define	__casm_16(v,w,r)	__casm_use(2,r,w)
#define	__casm_17(v,w,r)	__casm_use(2,r,w)

#define	__casm_20(v,w,r)	__casm_use(1,r,v)
#define	__casm_21(v,w,r)	__casm_use(1,r,v)
#define	__casm_22(v,w,r)	__casm_use(1,r,v)
#define	__casm_23(v,w,r)	__casm_use(2,r,w)
#define	__casm_24(v,w,r)	__casm_use(2,r,w)
#define	__casm_25(v,w,r)	__casm_use(2,r,w)
#define	__casm_26(v,w,r)	__casm_use(2,r,w)
#define	__casm_27(v,w,r)	__casm_use(2,r,w)

#define	__casm_30(v,w,r)	__casm_use(1,r,v)
#define	__casm_31(v,w,r)	__casm_use(1,r,v)
#define	__casm_32(v,w,r)	__casm_use(1,r,v)
#define	__casm_33(v,w,r)	__casm_use(1,r,v)
#define	__casm_34(v,w,r)	__casm_use(2,r,w)
#define	__casm_35(v,w,r)	__casm_use(2,r,w)
#define	__casm_36(v,w,r)	__casm_use(2,r,w)
#define	__casm_37(v,w,r)	__casm_use(2,r,w)

#define	__casm_40(v,w,r)	__casm_use(1,r,v)
#define	__casm_41(v,w,r)	__casm_use(1,r,v)
#define	__casm_42(v,w,r)	__casm_use(1,r,v)
#define	__casm_43(v,w,r)	__casm_use(1,r,v)
#define	__casm_44(v,w,r)	__casm_use(1,r,v)
#define	__casm_45(v,w,r)	__casm_use(2,r,w)
#define	__casm_46(v,w,r)	__casm_use(2,r,w)
#define	__casm_47(v,w,r)	__casm_use(2,r,w)

#define	__casm_50(v,w,r)	__casm_use(1,r,v)
#define	__casm_51(v,w,r)	__casm_use(1,r,v)
#define	__casm_52(v,w,r)	__casm_use(1,r,v)
#define	__casm_53(v,w,r)	__casm_use(1,r,v)
#define	__casm_54(v,w,r)	__casm_use(1,r,v)
#define	__casm_55(v,w,r)	__casm_use(1,r,v)
#define	__casm_56(v,w,r)	__casm_use(2,r,w)
#define	__casm_57(v,w,r)	__casm_use(2,r,w)

#define	__casm_60(v,w,r)	__casm_use(1,r,v)
#define	__casm_61(v,w,r)	__casm_use(1,r,v)
#define	__casm_62(v,w,r)	__casm_use(1,r,v)
#define	__casm_63(v,w,r)	__casm_use(1,r,v)
#define	__casm_64(v,w,r)	__casm_use(1,r,v)
#define	__casm_65(v,w,r)	__casm_use(1,r,v)
#define	__casm_66(v,w,r)	__casm_use(1,r,v)
#define	__casm_67(v,w,r)	__casm_use(1,r,w)



	/* argument list */

#define	__lst_6(x,a1,a2,a3,a4,a5,a6)	__lst_5(x,a1,a2,a3,a4,a5),x(6,a6)
#define	__lst_5(x,a1,a2,a3,a4,a5)	__lst_4(x,a1,a2,a3,a4),x(5,a5)
#define	__lst_4(x,a1,a2,a3,a4)		__lst_3(x,a1,a2,a3),x(4,a4)
#define	__lst_3(x,a1,a2,a3)		__lst_2(x,a1,a2),x(3,a3)
#define	__lst_2(x,a1,a2)		__lst_1(x,a1),x(2,a2)
#define	__lst_1(x,a1)			__lst_0(x,*)x(1,a1)
#define	__lst_0(x,a0)

	/* argument selection */

#define	__arg_0(...)			
#define	__arg_1(a1,...)			a1
#define	__arg_2(a1,a2,...)		a2
#define	__arg_3(a1,a2,a3,...)		a3
#define	__arg_4(a1,a2,a3,a4,...)	a4
#define	__arg_5(a1,a2,a3,a4,a5,...)	a5
#define	__arg_6(a1,a2,a3,a4,a5,a6)	a6




/*	*****************************************
	ALPHA	ALPHA	ALPHA	ALPHA		*
	alpha kernel interface 			*/
	
#if 	defined(__alpha__)

/*	The Alpha calling convention doesn't use the stack until 
	after the first six arguments have been passed in registers.
	
	scnr:	a0($0)
	args:	a1($16), a2($17), a3($18), a4($19), a5($20), a6($21)
	sret:	r0($0)
	serr:	e0($19) (!=0, err=sret)
	call:	callsys
	clob:	memory
*/

#define	__syscall_complex
#define	__syscall_reg_cid	"$0"
#define	__syscall_reg_ret	"$0"
#define	__syscall_reg_err	"$17"
#define	__syscall_cmd_seq	"callsys"

#define	__syscall_reg(n)	__arg_##n				\
	("$16", "$17", "$18", "$19", "$20", "$21")

#define	__syscall_clobbers	__syscall_regs,				\
	"$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8",			\
	"$22", "$23", "$24", "$25", "$27", "$28", "memory" 		\

#define	__syscall_load(r,a)	"ldq "r","a
#define	__syscall_store(r,a)	"stq "r","a



/*	*****************************************
	ARM	ARM	ARM	ARM		*
	arm kernel interface 			*/

#elif	defined(__arm__)

/*	The Arm calling convention uses stack args after four arguments
	but the Linux kernel gets up to seven arguments in registers.
	
	scnr:	imm
	args:	a1(r0), a2(r1), a3(r2), a4(r3), a5(r4), a6(r5), 
	sret:	r0(r0)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	swi
	clob:	memory
*/

#define	__syscall_maxerrno	125
#define	__syscall_reg_res	"r0"
#define	__syscall_cmd_seq	"swi	%0"

#define	__syscall_reg(n)	__arg_##n				\
	("r0", "r1", "r2", "r3", "r4", "r5")

#define	__syscall_clobbers	__syscall_regs, "memory"

#define	__syscall_load(r,a)	"ldr	"r","a
#define	__syscall_store(r,a)	"str	"r","a



/*	*****************************************
	CRIS	CRIS	CRIS	CRIS		*
	cris v10 kernel interface 		*/

#elif	defined(__cris__)

/*	The Cris calling convention uses stack args after four arguments
	but the Linux kernel gets up to six arguments in registers.
	
	scnr:	id(r9)
	args:	a1(r10), a2(r11), a3(r12), a4(r13), a5(mof), a6(srp), 
	sret:	r0(r10)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	break 13
	clob:	memory
*/

#define	__syscall_maxerrno	125
#define	__syscall_reg_cid	"r9"
#define	__syscall_reg_res	"r0"
#define	__syscall_cmd_seq	"break 13"

#define	__syscall_reg(n)	__arg_##n				\
	("r10", "r11", "r12", "r13", "$mov", "$srp")

#define	__syscall_clobbers	"r10", "r11", "r12", "r13", "memory"

#define	__syscall_load(r,a)	"move	"a","r
#define	__syscall_store(r,a)	"move	"r","a



/*	*****************************************
	FRV	FRV	FRV	FRV		*
	frv kernel interface 		*/

#elif	defined(__frv__)

/*	The C calling convention on FR-V uses the gr8-gr13 registers
	for the first six arguments, the remainder is spilled onto the
	stack. the linux kernel syscall interface does so too.
	
	scnr:	id(gr7)
	args:	a1(gr8), a2(gr9), a3(gr10), a4(gr11), a5(gr12), a6(gr13) 
	sret:	r0(gr8)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	tra gr0,gr0
	clob:	memory
*/

#define	__syscall_maxerrno	125
#define	__syscall_reg_cid	"gr7"
#define	__syscall_reg_res	"gr8"
#define	__syscall_cmd_seq	"tra	gr0,gr0"

#define	__syscall_reg(n)	__arg_##n				\
	("gr8","gr9","gr10","gr11","gr12","gr13")

#define	__syscall_clobbers	__syscall_regs, "memory"

#define	__syscall_load(r,a)	"ldi "a","r
#define	__syscall_store(r,a)	"sti "r","a



/*	*****************************************
	H8300	H8300	H8300	H8300		*
	h8/300 kernel interface 		*/

#elif	defined(__H8300__)

/*	The H8/300 C calling convention passes the first three 
	arguments in registers. However the linux kernel calling
	convention passes the first six arguments in registers
	er1-er6
	
	scnr:	id(er0)
	args:	a1(er1), a2(er2), a3(er3), a4(er4), a5(er5), a6(er6) 
	sret:	r0(er0)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	trapa #0
	clob:	memory
*/

#define	__syscall_maxerrno	125
#define	__syscall_reg_res	"er0"

#define	__syscall_clobbers	"memory"

#define	____sc_asm_reg(n, ...)	____sc_asm	(			\
	__casm(n,1,1,	"mov.l	%0,er1"		,			)\
	__casm(n,2,1,	"mov.l	%1,er2"		,			)\
	__casm(n,3,1,	"mov.l	%2,er3"		,			)\
	__casm(n,4,1,	"mov.l	%3,er4"		,			)\
	__casm(n,5,1,	"mov.l	%4,er5"		,			)\
	__casm(n,6,1,	"mov.l	er6,@-sp"	,			)\
	__casm(n,6,1,	"mov.l	%5,er6"		,			)\
	""::__input_regs(n,__VA_ARGS__))

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,1,1,	"mov.l	%0,er0"		,			)\
	__casm(n,0,0,	"trapa	#0"		,			)\
	__casm(n,0,1,	__comment(name)		,			)\
	__casm(n,6,1,	"mov.l	@sp+,er6"	,			)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#define	__syscall_store(r,a)	"mov.l	"r","a



/*	*****************************************
	HPPA	HPPA	HPPA	HPPA		*
	hppa/64 kernel interface 		*/

#elif	defined(__hppa__)

/*	The hppa calling convention uses r26-r23 for the first 4
	arguments, the rest is spilled onto the stack. However the
	Linux kernel passes the first six arguments in the registers
	r26-r21. 
	
	The system call number MUST ALWAYS be loaded in the delay 
	slot of the ble instruction, or restarting system calls 
	WILL NOT WORK.
	
	scnr:	id(r20)
	args:	a1(r26), a2(r25), a3(r24), a4(r23), a5(r22), a6(r21)
	sret:	r0(r28)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	ble  0x100(%%sr2, %%r0)
	clob:	r1, r2, r4, r20, r29, r31, memory
*/

#define	__syscall_maxerrno	4095
#define	__syscall_reg_res	"r28"

#define	__syscall_reg(n)	__arg_##n				\
	("r26", "r25", "r24", "r23", "r22", "r21")

#define	__syscall_clobbers	__syscall_regs,				\
	"r1", "r2", "r4", "r20", "r29", "r31", "memory" 

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,0,0,	"ble 0x100(%%sr2,%%r0)"	,			)\
	__casm(n,0,1,	__comment(name)		,			)\
	__casm(n,0,1,	"ldi %0,%%r20"		,			)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#define	__syscall_load(r,a)	"ldw "a","r
#define	__syscall_store(r,a)	"stw "r","a



/*	*****************************************
	I386	I386	I386	I386		*
	i386 kernel interface 			*/

#elif	defined(__i386__)

/*	The x86 calling convention uses stack args for all arguments,
	but the Linux kernel passes the first six arguments in the
	following registers: ebx, ecx, edx, esi, edi, ebp.
	
	scnr:	id(eax)
	args:	a1(ebx), a2(ecx), a3(edx), a4(esi), a5(edi), a6(ebp) 
	sret:	r0(eax)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	int 0x80
	clob:	memory
*/

#define	__syscall_maxerrno	129
#define	__syscall_reg_res	"%%eax"
#define	__syscall_clobbers	"memory"

#define	____sc_asm_reg(n, ...)	____sc_asm	(			\
	__casm(n,6,1,	"movl	%5,%%eax"	,			)\
	__casm(n,5,1,	"movl	%4,%%edi"	,			)\
	__casm(n,4,1,	"movl	%3,%%esi"	,			)\
	__casm(n,3,1,	"movl	%2,%%edx"	,			)\
	__casm(n,2,1,	"movl	%1,%%ecx"	,			)\
	__pasm(n,1,1,	"pushl	%%ebx"		,			)\
	__casm(n,1,1,	"movl	%0,%%ebx"	,			)\
	__casm(n,6,1,	"pushl	%%ebp"		,			)\
	""::__input_regs(n,__VA_ARGS__))

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,6,1,	"movl	%%eax,%%ebp"	,			)\
	__casm(n,0,1,	"movl	%0,%%eax"	,			)\
	__casm(n,0,0,	"int	$0x80"		,			)\
	__casm(n,0,1,	__comment(name)		,			)\
	__casm(n,6,1,	"popl	%%ebp"		,			)\
	__pasm(n,1,1,	"popl	%%ebx"		,			)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#define	__syscall_store(r,a)	"movl "r","a


/*	*****************************************
	IA64	IA64	IA64	IA64		*
	ia64 kernel interface 			*/

#elif	defined(__ia64__)

/*	The ia64 calling convention uses out0-out7 to pass the first
	eight arguments (mapped via register windows).
	
	scnr:	id(r15)
	args:	a1(out0), a2(out1), ... a5(out4), a6(out5) 
	sret:	r0(r8)
	serr:	e0(r10)
	call:	break 0x100000
	clob:	out6/7, r2/3/9, r11-r14, r16-r31, p6-p15, f6-f15, b6/7
*/


#define	__syscall_complex
#define	__syscall_reg_ret	"r8"
#define	__syscall_reg_err	"r10"
#define	__syscall_reg_cid	"r15"
#define	__syscall_cmd_seq	"break.i	0x100000"

#define	__syscall_errcon(err)	(err == -1)

#define	__syscall_reg(n)	__arg_##n				\
	("out0", "out1", "out2", "out3", "out4", "out5")

#define	__syscall_clobbers	__syscall_regs,				\
	"out6", "out7", "r2", "r3", "r9", "r11", "r12", "r13",		\
	"r14", "r16", "r17", "r18", "r19", "r20", "r21", "r22", 	\
	"r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30",		\
	"r31", "p6", "p7", "p8", "p9", "p10", "p11", "p12", "p13",	\
	"p14", "p15", "f6", "f7", "f8", "f9", "f10", "f11", "f12",	\
	"f13", "f14", "f15", "f16", "b6", "b7", "cc", "memory"

#define	__syscall_load(r,a)	"ld8 "r" = "a
#define	__syscall_store(r,a)	"st8 "a" = "r



/*	*****************************************
	M32R	M32R	M32R	M32R		*
	m32r kernel interface 			*/

#elif	defined(__m32r__)

/*	The m32r calling convention uses r0-r7 to pass the first
	eight arguments (mapped via register windows).
	
	scnr:	id(r0)
	args:	a1(r1), a2(r2), a3(r3), a4(r4), a5(r5), a6(r6) 
	sret:	r0(r0)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	trap #2
	clob:	out6/7, r2/3/9, r11-r14, r16-r31, p6-p15, f6-f15, b6/7
*/

#define	__syscall_maxerrno	125
#define	__syscall_reg_cid	"r7"
#define	__syscall_reg_res	"r0"
#define	__syscall_cmd_seq	"trap #2"

#define	__syscall_reg(n)	__arg_##n				\
	("r0", "r1", "r2", "r3", "r4", "r5")

#define	__syscall_clobbers	__syscall_regs, "memory"

#define	__syscall_load(r,a)	"ld "r","a
#define	__syscall_store(r,a)	"st "a","r



/*	*****************************************
	M68K	M68K	M68K	M68K		*
	m68k kernel interface 			*/

#elif	defined(__m68000__)

#warning syscall arch m68k not implemented yet



/*	*****************************************
	MIPS	MIPS	MIPS	MIPS		*
	mips kernel interface 			*/

#elif	defined(__mips__)

#warning syscall arch mips not implemented yet



/*	*****************************************
	PPC	PPC	PPC	PPC		*
	ppc/64 kernel interface 		*/

#elif	defined(__powerpc__)

/*	The powerpc calling convention uses r3-r10 to pass the first
	eight arguments, the remainder is spilled onto the stack.
	
	scnr:	id(r0)
	args:	a1(r3), a2(r4), a3(r5), a4(r6), a5(r7), a6(r8)
	sret:	r0(r3)
	serr:	(carry)
	call:	sc
	clob:	cr0, ctr
*/


#define	__syscall_complex
#define	__syscall_reg_cid	"r0"
#define	__syscall_reg_ret	"r3"
#define	__syscall_reg_err	"r0"

#define	__syscall_errcon(err)	(err & 0x10000000)

#define	__syscall_reg(n)	__arg_##n				\
	("r3", "r4", "r5", "r6", "r7", "r8")

#define	__syscall_clobbers	__syscall_regs,				\
	"r9", "r10", "r11", "r12", "cr0", "ctr", "memory"

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,0,1,	"li r0,%0"		,			)\
	__casm(n,0,0,	"sc"			,			)\
	__casm(n,0,1,	__comment(name)		,			)\
	__casm(n,0,1,	"mfcr r0"		,			)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#define	__syscall_load(r,a)	"lw "r","a
#define	__syscall_store(r,a)	"stw "r","a



/*	*****************************************
	S390	S390	S390	S390		*
	s390/x kernel interface 		*/

#elif	defined(__s390__)

/*	The s390x calling convention passes the first five arguments
	in r2-r6, the remainder is spilled onto the stack. However 
	the Linux kernel passes the first six arguments in r2-r7.
	
	scnr:	imm, id(r1)
	args:	a1(r2), a2(r3), a3(r4), a4(r5), a5(r6), a6(r7)
	sret:	r0(r2)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	svc
	clob:	memory
*/

#define	__syscall_maxerrno	4095
#define	__syscall_reg_res	"r2"
#define	__syscall_reg_cid	"r1"
#define	__syscall_cmd_seq	"svc	0"

#define	__syscall_regtype	unsigned long

#define	__syscall_reg(n)	__arg_##n				\
	("r2", "r3", "r4", "r5", "r6", "r7")

#define	__syscall_clobbers	__syscall_regs, "memory" 

#define	__syscall_load(r,a)	"l	"r","a
#define	__syscall_store(r,a)	"st	"r","a



/*	*****************************************
	SH	SH	SH	SH		*
	sh kernel interface 			*/

#elif	defined(__sh__) && !defined(__SH5__)

#warning syscall arch sh not implemented yet



/*	*****************************************
	SH64	SH64	SH64	SH64		*
	sh64 kernel interface 			*/

#elif defined(__sh__) && defined(__SH5__)

#warning syscall arch sh64 not implemented yet



/*	*****************************************
	SPARC64	SPARC64	SPARC64	SPARC64		*
	sparc64 kernel interface 		*/

#elif	defined(__sparc__)

/*	The sparc/64 calling convention uses o0-o5 to pass the first
	six arguments (mapped via register windows).
	
	scnr:	id(g1)
	args:	a1(o0), a2(o1), a3(o2), a4(o3), a5(o4), a6(o5) 
	sret:	r0(o0)
	serr:	(carry)
	call:	ta 0x6d, t 0x10
	clob:	g1-g6, g7?, o7?, f0-f31, cc
*/

#define	__syscall_complex
#define	__syscall_maxerrno	515
#define	__syscall_reg_cid	"g1"
#define	__syscall_reg_ret	"o0"
#define	__syscall_reg_err	"l1"

#ifdef	__arch64__
#define	__syscall_cmd_seq	"ta	0x6d"
#else
#define	__syscall_cmd_seq	"t	0x10"
#endif

#define	__syscall_reg(n)	__arg_##n				\
	("o0", "o1", "o2", "o3", "o4", "o5")

#define	__syscall_clobbers	__syscall_regs,				\
	"g2", "g3", "g4", "g5", "g6",					\
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",		\
	"f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16",		\
	"f17", "f18", "f19", "f20", "f21", "f22", "f23", "f24",		\
	"f25", "f26", "f27", "f28", "f29", "f30", "f31", "f32",		\
	"f34", "f36", "f38", "f40", "f42", "f44", "f46", "f48",		\
	"f50", "f52", "f54", "f56", "f58", "f60", "f62",		\
	"cc", "memory" 

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,0,1,	__syscall_load(__syscall_reg_cid,"%0"),		)\
	__casm(n,0,0,	__syscall_cmd_seq	,			)\
	__casm(n,0,1,	__comment(name)		,			)\
	__casm(n,0,1,	"addx	%%g0,%%g0,%%l1"	,			)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#define	__syscall_load(r,a)	"ld	"a","r
#define	__syscall_store(r,a)	"st	"r","a



/*	*****************************************
	V850	V850	V850	V850		*
	v850 kernel interface 			*/

#elif	defined(__v850__)

/*	The V850 calling convention passes the first four arguments
	in registers r6-r9, the rest is spilled onto the stack.
	but the Linux kernel interface uses r6-r9 and r13/14.
	
	scnr:	id(r12)
	args:	a1(r6), a2(r7), a3(r8), a4(r9), a5(r13), a6(r14) 
	sret:	r0(r10)
	serr:	(sret >= (unsigned)-EMAXERRNO)
	call:	trap 0, trap 1
	clob:	r1, r5, r11, r15-r19
*/

#define	__syscall_maxerrno	515
#define	__syscall_reg_cid	"r12"
#define	__syscall_reg_res	"r10"

#define	__syscall_reg(n)	__arg_##n				\
	("r6", "r7", "r8", "r9", "r13", "r14")

#define	__syscall_clobbers	__syscall_regs,				\
	"r1", "r5", "r11", "r15", "r16", "r17", "r18", "r19", "memory"

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,0,1,	__syscall_load(__syscall_reg_cid,"%0"),		)\
	__casm(n,4,0,	"trap 1"		,"trap 0"		)\
	__casm(n,0,1,	__comment(name)		,			)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#define	__syscall_load(r,a)	"ld.w	"a","r
#define	__syscall_store(r,a)	"st.w	"r","a



/*	*****************************************
	X86_64	X86_64	X86_64	X86_64		*
	x86_64 kernel interface 		*/

#elif	defined(__x86_64__)

/*	The x86_64 calling convention uses rdi, rsi, rdx, rcx, r8, r9
	but the Linux kernel interface uses rdi, rsi, rdx, r10, r8, r9.
	
	scnr:	id(rax)
	args:	a1(rdi), a2(rsi), a3(rdx), a4(r10), a5(r8), a6(r9) 
	sret:	r0(rax)
	serr:	(err= sret > (unsigned)-EMAXERRNO)
	call:	syscall
	clob:	rcx, r11
*/

#define	__syscall_maxerrno	4095
#define	__syscall_reg_cid	"rax"
#define	__syscall_reg_res	"rax"
#define	__syscall_cmd_seq	"syscall"

#define	__syscall_reg(n)	__arg_##n				\
	("rdi", "rsi", "rdx", "r10", "r8", "r9")

#define	__syscall_clobbers	__syscall_regs,				\
	"cc", "r11", "rcx", "memory" 

#define	__syscall_load(r,a)	"movq	"a","r
#define	__syscall_store(r,a)	"movq	"r","a


#else
#error unknown kernel arch
#endif


	/* list of all registers */

#define	__syscall_reg_list(x)	x(1), x(2), x(3), x(4), x(5), x(6)
#define	__syscall_regs		__syscall_reg_list(__syscall_reg)

#ifndef	__syscall_regtype
#define	__syscall_regtype	long
#endif


	/* default asm constructs */

#ifndef	____sc_asm_reg
#define	____sc_asm_reg(n, ...)	____sc_asm	(			\
	__casm(n,1,1,	__syscall_load(__syscall_reg(1),"%0"),		)\
	__casm(n,2,1,	__syscall_load(__syscall_reg(2),"%1"),		)\
	__casm(n,3,1,	__syscall_load(__syscall_reg(3),"%2"),		)\
	__casm(n,4,1,	__syscall_load(__syscall_reg(4),"%3"),		)\
	__casm(n,5,1,	__syscall_load(__syscall_reg(5),"%4"),		)\
	__casm(n,6,1,	__syscall_load(__syscall_reg(6),"%5"),		)\
	""::__input_regs(n,__VA_ARGS__))
#endif

#ifndef	____sc_asm_sys
#ifdef	__syscall_reg_cid	/* register call id */

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,0,1,	__syscall_load(__syscall_reg_cid,"%0"),		)\
	__casm(n,0,1,	__syscall_cmd_seq __comment(name),		)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#else				/* immediate call id */

#define	____sc_asm_sys(n, name)	____sc_asm_vol	(			\
	__casm(n,0,1,	__syscall_cmd_seq __comment(name),		)\
	""::"i"(__NR_##name) : __syscall_clobbers)

#endif
#endif

#ifndef	____sc_asm_res
#ifdef	__syscall_complex	/* complex result */

#define	____sc_asm_res(n)	____sc_asm	(			\
	__casm(n,0,1,	__syscall_store(__syscall_reg_ret,"%0"),	)\
	__casm(n,0,1,	__syscall_store(__syscall_reg_err,"%1"),	)\
	"":"=g"(__ret), "=g"(__err))

#else				/* simple result */

#define	____sc_asm_res(n)	____sc_asm	(			\
	__casm(n,0,1,	__syscall_store(__syscall_reg_res,"%0"),	)\
	"":"=g"(__res))

#endif				/* simple/complex */
#endif


	/* register constraints */

#define	__reg_cast(v)		((__syscall_regtype)(v))

#define	__gen_reg(n,v)		"g"__reg_cast(v)
#define	__con_reg(n,v)		__syscall_reg_con(n)__reg_cast(v)

#ifndef	__syscall_reg_con
#define	__input_regs(n,...)	__lst_##n(__gen_reg,__VA_ARGS__)
#else
#define	__input_regs(n,...)	__lst_##n(__con_reg,__VA_ARGS__)
#endif



#ifdef	__syscall_complex	/* complex result */

#define	____sc_results		__syscall_regtype __ret, __err
#define	____sc_return(type)	__syscall_return(type, __ret, __err)

#ifndef	__syscall_errcon
#define	__syscall_errcon(err)   (err)
#endif

#ifndef	__syscall_return
#define	__syscall_return(type, ret, err)				\
	__syscall_retval(ret);						\
	if (__syscall_errcon(err)) {					\
		int __err = (ret);					\
		__syscall_error(__err);					\
		ret = -1;						\
	}								\
	return (type)(ret);
#endif

#else				/* simple result */

#define	____sc_results		__syscall_regtype __res
#define	____sc_return(type)	__syscall_return(type, __res)

#ifndef	__syscall_errcon
#define	__syscall_errcon(res)						\
	((unsigned long)(res) >= (unsigned long)(-(__syscall_maxerrno)))
#endif

#ifndef	__syscall_return
#define	__syscall_return(type, res)					\
	__syscall_retval(res);						\
	if (__syscall_errcon(res)) {					\
		int __err = -(res);					\
		__syscall_error(__err);					\
		res = -1;						\
	}								\
	return (type)(res);
#endif

#endif				/* simple/complex */




#define	____sc_body(n, type, name, ...)					\
{									\
	____sc_results;							\
	____sc_asm_reg(n, __VA_ARGS__);					\
	____sc_asm_sys(n, name);					\
	____sc_asm_res(n);						\
	____sc_return(type)						\
}


#define _syscall0(type, name)						\
type name(void)								\
____sc_body(0, type, name, *)

#define _syscall1(type, name, type1, arg1)				\
type name(type1 arg1)							\
____sc_body(1, type, name, arg1)

#define _syscall2(type, name, type1, arg1, type2, arg2)			\
type name(type1 arg1, type2 arg2)					\
____sc_body(2, type, name, arg1, arg2)

#define _syscall3(type, name, type1, arg1, type2, arg2, type3, arg3)	\
type name(type1 arg1, type2 arg2, type3 arg3)				\
____sc_body(3, type, name, arg1, arg2, arg3)

#define _syscall4(type, name, type1, arg1, type2, arg2, type3, arg3,	\
			      type4, arg4)				\
type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4)		\
____sc_body(4, type, name, arg1, arg2, arg3, arg4)

#define _syscall5(type, name, type1, arg1, type2, arg2, type3, arg3,	\
    			      type4, arg4, type5, arg5)			\
type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)	\
____sc_body(5, type, name, arg1, arg2, arg3, arg4, arg5)

#define _syscall6(type, name, type1, arg1, type2, arg2, type3, arg3,	\
			type4, arg4, type5, arg5, type6, arg6)		\
type name(type1 arg1, type2 arg2, type3 arg3,				\
	  type4 arg4, type5 arg5, type6 arg6)				\
____sc_body(6, type, name, arg1, arg2, arg3, arg4, arg5, arg6)


#endif	/* __SYSCALL_NEW_H */
