
#ifndef __syscall_retval
#define __syscall_retval(v)	do { } while(0)
#endif

#ifndef __syscall_error
#define __syscall_error(e) 	do { errno = (e); } while(0)
#endif

#define	__check(pos, reg)						\
	".ifnc\t" pos ", " reg "\n\t"					\
	".err\t/* register assertion failed */\n\t"			\
	".endif\n\t"

#ifndef __stringify0
#define __stringify0(val)	#val
#endif

#ifndef __stringify
#define __stringify(val)	__stringify0(val)
#endif

#define	__comment(name)							\
	"\t/* kernel sys_" #name "[" __stringify(__NR_##name) "] */"


	/* argument concatenation */

#define __arglst_6(x,head,tail...)	__arglst_5(x,tail)x(6,head)
#define __arglst_5(x,head,tail...)	__arglst_4(x,tail)x(5,head)
#define __arglst_4(x,head,tail...)	__arglst_3(x,tail)x(4,head)
#define __arglst_3(x,head,tail...)	__arglst_2(x,tail)x(3,head)
#define __arglst_2(x,head,tail...)	__arglst_1(x,tail)x(2,head)
#define __arglst_1(x,head,tail...)	x(1,head)
#define __arglst_0(x,head,tail...)

	/* string concatenation */

#define __concat_6(x)	__concat_5(x)x(6)
#define __concat_5(x)	__concat_4(x)x(5)
#define __concat_4(x)	__concat_3(x)x(4)
#define __concat_3(x)	__concat_2(x)x(3)
#define __concat_2(x)	__concat_1(x)x(2)
#define __concat_1(x)	__concat_0(x)x(1)
#define __concat_0(x)	x(0)

	/* argument selection */

#define __arg_0(a0,a1,a2,a3,a4,a5,a6)	a0
#define __arg_1(a0,a1,a2,a3,a4,a5,a6)	a1
#define __arg_2(a0,a1,a2,a3,a4,a5,a6)	a2
#define __arg_3(a0,a1,a2,a3,a4,a5,a6)	a3
#define __arg_4(a0,a1,a2,a3,a4,a5,a6)	a4
#define __arg_5(a0,a1,a2,a3,a4,a5,a6)	a5
#define __arg_6(a0,a1,a2,a3,a4,a5,a6)	a6


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

#define __syscall_reg_ret	"$0"
#define __syscall_reg_err	"$19"
#define __syscall_reg_cid	"$0"
#define __syscall_cmd_seq	"callsys"
#define __syscall_clobbers						\
	"$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8",			\
	"$22", "$23", "$24", "$25", "$27", "$28", "memory" 		\

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "$16", "$17", "$18", "$19", "$20", "$21")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "$16", "$17", "$18", "memory", "$20", "$21")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1%2","%3","%4","%5","%6","%7","%8")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("$0$19$0","$16","$17","$18","$19","$20","$21")



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

#define __syscall_maxerrno	125
#define __syscall_regtype	long
#define __syscall_reg_res	"r0"
#define __syscall_imm_cid
#define __syscall_cmd_seq	"swi\t%1"
#define __syscall_clobbers	"memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r0", "r1", "r2", "r3", "r4", "r5")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "memory", "r1", "r2", "r3", "r4", "r5")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("r0","r0","r1","r2","r3","r4","r5")



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

#define __syscall_maxerrno	125
#define __syscall_reg_res	"r0"
#define __syscall_reg_cid	"r9"
#define __syscall_cmd_seq	"break 13"
#define __syscall_clobbers	"memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r10", "r11", "r12", "r13", "mof", "srp")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "memory", "r11", "r12", "r13", "memory", "memory")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("r9r10","r10","r11","r12","r13","mof","srp")

#ifndef _syscall5
#define _syscall5(type, name, type1, arg1, type2, arg2, type3, arg3,	\
    			      type4, arg4, type5, arg5)			\
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)	\
{									\
	____sc_results;							\
	{								\
		____sc_reg_ret;						\
		____sc_reg_cid(__NR_##name)				\
		____sc_regs(4, arg4, arg3, arg2, arg1);			\
		____sc_asm (						\
			____sc_check(4)					\
			"move\t%6,$mof\n\t"				\
			____sc_syscall(name)				\
		      : ____sc_output					\
		      : ____sc_input_cid(__NR_##name)			\
			____sc_input_4,					\
			"g"((__syscall_regtype)(arg5))			\
		      : ____sc_clobber_4				\
		);							\
		____sc_reg_results;					\
	}								\
	____sc_return(type)						\
}
#endif

#ifndef _syscall6
#define _syscall6(type, name, type1, arg1, type2, arg2, type3, arg3,	\
			type4, arg4, type5, arg5, type6, arg6)		\
type name (type1 arg1, type2 arg2, type3 arg3,				\
	   type4 arg4, type5 arg5, type6 arg6)				\
{									\
	____sc_results;							\
	{								\
		____sc_reg_ret;						\
		____sc_reg_cid(__NR_##name)				\
		____sc_regs(4, arg4, arg3, arg2, arg1);			\
		____sc_asm (						\
			____sc_check(4)					\
			"move\t%6,$mof\n\t"				\
			"move\t%7,$srp\n\t"				\
			____sc_syscall(name)				\
		      : ____sc_output					\
		      : ____sc_input_cid(__NR_##name)			\
			____sc_input_4,					\
			"g"((__syscall_regtype)(arg5)),			\
			"g"((__syscall_regtype)(arg6))			\
		      : ____sc_clobber_4				\
		);							\
		____sc_reg_results;					\
	}								\
	____sc_return(type)						\
}
#endif


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

#define __syscall_maxerrno	125
#define __syscall_reg_res	"gr8"
#define __syscall_reg_cid	"gr7"
#define __syscall_cmd_seq	"tra\tgr0,gr0"
#define __syscall_clobbers	"memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "gr8", "gr9", "gr10", "gr11", "gr12", "gr13")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "memory", "gr9", "gr10", "gr11", "gr12", "gr13")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("gr8gr7","gr8","gr9","gr10","gr11","gr12","gr13")


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

#define __syscall_maxerrno	125
#define __syscall_reg_res	"er0"
#define __syscall_imm_cid
#define __syscall_cmd_seq	"trapa\t#0"
#define __syscall_clobbers	"memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "memory", "er2", "er3", "er4", "er5", "memory")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("er0er0","er1","er2","er3","er4","er5","er6")

#define __sc_prep_0		"mov.l\t%1,er0\n\t"
#define __sc_prep_1		"mov.l\t%2,er1\n\t" __sc_prep_0
#define __sc_prep_2		"mov.l\t%3,er2\n\t" __sc_prep_1
#define __sc_prep_3		"mov.l\t%4,er3\n\t" __sc_prep_2
#define __sc_prep_4		"mov.l\t%5,er4\n\t" __sc_prep_3
#define __sc_prep_5		"mov.l\t%6,er5\n\t" __sc_prep_4
#define __sc_prep_6		"mov.l er6,@-sp\n\t"			\
				"mov.l\t%7,er6\n\t" __sc_prep_5

#define __sc_reg_arg_0(arg)
#define __sc_reg_arg_1(arg)	,"g"(arg)
#define __sc_reg_arg_2(arg)	,"g"(arg)
#define __sc_reg_arg_3(arg)	,"g"(arg)
#define __sc_reg_arg_4(arg)	,"g"(arg)
#define __sc_reg_arg_5(arg)	,"m"(arg)
#define __sc_reg_arg_6(arg)	,"m"(arg)

#define ____sc_reg_arg(n,arg)	__sc_reg_arg_##n(arg)

#define ____sc_body(numarg, type, name, args...)			\
{									\
	____sc_results;							\
	{								\
		____sc_reg_ret;						\
		____sc_asm (						\
			__sc_prep_##numarg				\
			____sc_sys(name,numarg)				\
		      : ____sc_output					\
		      : ____sc_input_cid(__NR_##name)			\
			____sc_regs(numarg,args)			\
		      : ____sc_clobber_##numarg				\
		);							\
		____sc_reg_results					\
	}								\
	____sc_return(type)						\
}


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

#define __syscall_maxerrno	129
#define __syscall_reg_res	"eax"
#define __syscall_reg_cid	"eax"
#define __syscall_cmd_seq	"int\t$0x80"
#define __syscall_clobbers	"memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "ebx", "ecx", "edx", "esi", "edi", "eax")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "ebx", "ecx", "edx", "esi", "edi", "memory")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("%%eax%%eax","%%ebx","%%ecx","%%edx","%%esi","%%edi","")

#ifndef _syscall6
#define _syscall6(type, name, type1, arg1, type2, arg2, type3, arg3,	\
			type4, arg4, type5, arg5, type6, arg6)		\
type name (type1 arg1, type2 arg2, type3 arg3,				\
	   type4 arg4, type5 arg5, type6 arg6)				\
{									\
	____sc_results;							\
	{								\
		____sc_reg_ret						\
		____sc_regs(6, arg6, arg5, arg4, arg3, arg2, arg1);	\
		____sc_asm (						\
			__check("%0%2%3%4%5%6%7",			\
				"%%eax%%ebx%%ecx%%edx%%esi%%edi%%eax")	\
			"push\t%%ebp\n\t"				\
			"movl\t%%eax,%%ebp\n\t"				\
			"movl\t%1,%%eax\n\t"				\
			____sc_syscall(name) "\n\t"			\
			"pop\t%%ebp"					\
		      : ____sc_output					\
		      : "i"(__NR_##name) ____sc_input_6			\
		      : ____sc_clobber_6				\
		);							\
		____sc_reg_results;					\
	}								\
	____sc_return(type)						\
}
#endif


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

#define __syscall_errcon(err)	(err == -1)

#define __syscall_reg_ret	"r8"
#define __syscall_reg_err	"r10"
#define __syscall_reg_cid	"r15"
#define __syscall_cmd_seq	"break.i\t0x100000"

#define __syscall_clobbers						\
	"out6", "out7", "r2", "r3", "r9", "r11", "r12", "r13",		\
	"r14", "r16", "r17", "r18", "r19", "r20", "r21", "r22", 	\
	"r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30",		\
	"r31", "p6", "p7", "p8", "p9", "p10", "p11", "p12", "p13",	\
	"p14", "p15", "f6", "f7", "f8", "f9", "f10", "f11", "f12",	\
	"f13", "f14", "f15", "f16", "b6", "b7", "cc", "memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "out0", "out1", "out2", "out3", "out4", "out5")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1%2","","","","","","")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("r8r10r15","","","","","","")


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

#define __syscall_maxerrno	125
#define __syscall_reg_res	"r0"
#define __syscall_reg_cid	"r7"
#define __syscall_cmd_seq	"trap #2"
#define __syscall_clobbers	"memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r0", "r1", "r2", "r3", "r4", "r5")
#define __syscall_clb_arg(n)	"memory"
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("r0r7","r0","r1","r2","r3","r4","r5")


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

#define __syscall_maxerrno	4095
#define __syscall_reg_res	"r28"
#define __syscall_imm_cid
#define __syscall_cmd_seq	"ble 0x100(%%sr2,%%r0)"
#define __syscall_cmd_fin	"ldi %1,%%r20"
#define __syscall_clobbers						\
	"r1", "r2", "r4", "r20", "r29", "r31", "memory" 

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r26", "r25", "r24", "r23", "r22", "r21")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("%%r28","%%r26","%%r25","%%r24","%%r23","%%r22","%%r21")


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


#define __syscall_errcon(err)	(err & 0x10000000)

#define __syscall_reg_ret	"r3"
#define __syscall_reg_err	"r0"
#define __syscall_reg_cid	"r0"
#define __syscall_cmd_seq	"sc"
#define __syscall_cmd_fin	"mfcr %0"
#define __syscall_clobbers						\
	"r9", "r10", "r11", "r12", "cr0", "ctr", "memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r3", "r4", "r5", "r6", "r7", "r8")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "memory", "r4", "r5", "r6", "r7", "r8")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0.%1.%2",".%3",".%4",".%5",".%6",".%7",".%8")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("3.0.0",".3",".4",".5",".6",".7",".8")


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

#define __syscall_maxerrno	4095
#define __syscall_regtype	unsigned long
#define __syscall_reg_res	"r2"
#define __syscall_reg_cid	"r1"
#define __syscall_cmd_seq	"svc\t0"
#define __syscall_clobbers	"memory" 

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r2", "r3", "r4", "r5", "r6", "r7")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "memory", "r3", "r4", "r5", "r6", "r7")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("%%r2%%r1","%%r2","%%r3","%%r4","%%r5","%%r6","%%r7")



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

#define __syscall_maxerrno	515
#define __syscall_reg_ret	"o0"
#define __syscall_reg_err	"l1"
#define __syscall_reg_cid	"g1"
#ifdef	__arch64__
#define __syscall_cmd_seq	"ta\t0x6d"
#else
#define __syscall_cmd_seq	"t\t0x10"
#endif
#define __syscall_cmd_fin	"addx\t%%g0,%%g0,%%l1"

#define __syscall_clobbers						\
	"g2", "g3", "g4", "g5", "g6",					\
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",		\
	"f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16",		\
	"f17", "f18", "f19", "f20", "f21", "f22", "f23", "f24",		\
	"f25", "f26", "f27", "f28", "f29", "f30", "f31", "f32",		\
	"f34", "f36", "f38", "f40", "f42", "f44", "f46", "f48",		\
	"f50", "f52", "f54", "f56", "f58", "f60", "f62",		\
	"cc", "memory" 

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "o0", "o1", "o2", "o3", "o4", "o5")
#define __syscall_clb_arg(n)	__arg_##n				\
	("", "memory", "o1", "o2", "o3", "o4", "o5")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1%2","%3","%4","%5","%6","%7","%8")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("%%o0%%l1%%g1","%%o0","%%o1","%%o2","%%o3","%%o4","%%o5")


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

#define __syscall_maxerrno	515
#define __syscall_reg_res	"r10"
#define __syscall_reg_cid	"r12"
#define __syscall_cmd_num(n)	__arg_##n				\
	("", "trap 0", "trap 0", "trap 0", "trap 0", "trap 1", "trap 1")

#define __syscall_clobbers						\
	"r1", "r5", "r11", "r15", "r16", "r17", "r18", "r19", "memory"

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "r6", "r7", "r8", "r9", "r13", "r14")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("r10r12","r6","r7","r8","r9","r13","r14")


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

#define __syscall_maxerrno	4095
#define __syscall_reg_res	"rax"
#define __syscall_reg_cid	"rax"
#define __syscall_cmd_seq	"syscall"

#define __syscall_clobbers						\
	"cc", "r11", "rcx", "memory" 

#define __syscall_reg_arg(n)	__arg_##n				\
	("", "rdi", "rsi", "rdx", "r10", "r8", "r9")
#define __syscall_reg_ckl(n)	__arg_##n				\
	("%0%1","%2","%3","%4","%5","%6","%7")
#define __syscall_reg_ckr(n)	__arg_##n				\
	("%%rax%%rax","%%rdi","%%rsi","%%rdx","%%r10","%%r8","%%r9")


#else
#error unknown kernel arch
#endif




#ifndef EMAXERRNO
#define EMAXERRNO		__syscall_maxerrno
#endif

#ifndef __syscall_regdef
#define __syscall_regdef(name, reg)					\
	register __syscall_regtype __sc_##name asm (reg)
#endif

#ifndef __syscall_regval
#define __syscall_regval(name, reg, val)				\
	register __syscall_regtype __sc_##name asm (reg) =		\
		(__syscall_regtype)(val)
#endif


#ifndef __syscall_reg_err	/* simple result */

#define ____sc_results		__syscall_regtype __res

#define ____sc_reg_ret							\
	__syscall_regdef(r0, __syscall_reg_res)

#define ____sc_output		"=r"(__sc_r0)
#define ____sc_return(type)	__syscall_return(type, __res)

#ifndef __syscall_stores
#define __syscall_stores	__res = __sc_r0;
#endif

#ifndef __syscall_errcon
#define __syscall_errcon(res)						\
	((unsigned long)(res) >= (unsigned long)(-(__syscall_maxerrno)))
#endif

#ifndef __syscall_return
#define __syscall_return(type, res)					\
	__syscall_retval(res);						\
	if (__syscall_errcon(res)) {					\
		int __err = -(res);					\
		__syscall_error(__err);					\
		res = -1;						\
	}								\
	return (type)(res);
#endif

#else				/* complex result */

#define ____sc_results		__syscall_regtype __ret, __err

#define ____sc_reg_ret							\
	__syscall_regdef(r0, __syscall_reg_ret);			\
	__syscall_regdef(e0, __syscall_reg_err)

#define ____sc_output		"=r"(__sc_r0), "=r"(__sc_e0)
#define ____sc_return(type)	__syscall_return(type, __ret, __err)

#ifndef __syscall_stores
#define __syscall_stores	__ret = __sc_r0; __err = __sc_e0;
#endif

#ifndef __syscall_errcon
#define __syscall_errcon(err)	(err)
#endif

#ifndef __syscall_return
#define __syscall_return(type, ret, err)				\
	__syscall_retval(ret);						\
	if (__syscall_errcon(err)) {					\
		int __err = (ret);					\
		__syscall_error(__err);					\
		ret = -1;						\
	}								\
	return (type)(ret);
#endif

#endif				/* simple/complex */


#ifndef __syscall_clb_arg
#define __syscall_clb_arg(n)	__syscall_reg_arg(n)
#endif

#ifndef __syscall_regtype
#define __syscall_regtype	long
#endif

#ifndef __syscall_reg_cid
#define ____sc_reg_cid(__cid)
#ifndef __syscall_imm_cid
#define ____sc_input_cid(__cid)
#else
#ifndef ____sc_input_cid
#define ____sc_input_cid(__cid)	"i"(__cid)
#endif
#endif
#else
#define ____sc_reg_cid(__cid)						\
	__syscall_regval(id, __syscall_reg_cid, __cid)
#ifndef ____sc_input_cid
#define ____sc_input_cid(__cid)	"r"(__sc_id)
#endif
#endif


#ifndef ____sc_reg_arg
#define ____sc_reg_arg(n,arg)	; __syscall_regval(a##n,		\
				__syscall_reg_arg(n), arg)
#endif

#ifndef ____sc_regs
#define ____sc_regs(n,args...)	__arglst_##n(____sc_reg_arg,args)
#endif

#define ____sc_check(n)		__check(				\
	__concat_##n(__syscall_reg_ckl),__concat_##n(__syscall_reg_ckr))


#ifndef ____sc_clobber_0
#define ____sc_clobber_6	__syscall_clobbers 
#define ____sc_clobber_5	__syscall_clb_arg(6), ____sc_clobber_6
#define ____sc_clobber_4	__syscall_clb_arg(5), ____sc_clobber_5
#define ____sc_clobber_3	__syscall_clb_arg(4), ____sc_clobber_4
#define ____sc_clobber_2	__syscall_clb_arg(3), ____sc_clobber_3
#define ____sc_clobber_1	__syscall_clb_arg(2), ____sc_clobber_2
#define ____sc_clobber_0	__syscall_clb_arg(1), ____sc_clobber_1
#endif

#ifndef ____sc_input_0
#define ____sc_input_6		____sc_input_5, "r"(__sc_a6)
#define ____sc_input_5		____sc_input_4, "r"(__sc_a5)
#define ____sc_input_4		____sc_input_3, "r"(__sc_a4)
#define ____sc_input_3		____sc_input_2, "r"(__sc_a3)
#define ____sc_input_2		____sc_input_1, "r"(__sc_a2)
#define ____sc_input_1		,"r"(__sc_a1)
#define ____sc_input_0		
#endif

#define ____sc_asm		asm volatile


#ifdef	__syscall_cmd_fin
#define ____sc_syscall(name)	__syscall_cmd_seq __comment(name) "\n\t"\
				__syscall_cmd_fin
#else
#define ____sc_syscall(name)	__syscall_cmd_seq __comment(name)
#endif

#define ____sc_reg_results	__syscall_stores


#ifndef __syscall_cmd_num
#define ____sc_sys(name,n)	____sc_syscall(name)
#else
#define ____sc_sys(name,n)	__syscall_cmd_num(n) __comment(name)
#endif

#ifndef ____sc_body
#define ____sc_body(numarg, type, name, args...)			\
{									\
	____sc_results;							\
	{								\
		____sc_reg_ret;						\
		____sc_reg_cid(__NR_##name)				\
		____sc_regs(numarg,args);				\
		____sc_asm (						\
			____sc_check(numarg)				\
			____sc_sys(name,numarg)				\
		      : ____sc_output					\
		      : ____sc_input_cid(__NR_##name)			\
			____sc_input_##numarg				\
		      : ____sc_clobber_##numarg				\
		);							\
		____sc_reg_results;					\
	}								\
	____sc_return(type)						\
}
#endif


#ifndef _syscall0
#define _syscall0(type, name)						\
type name(void)								\
____sc_body(0, type, name)
#endif

#ifndef _syscall1
#define _syscall1(type, name, type1, arg1)				\
type name(type1 arg1)							\
____sc_body(1, type, name, arg1)
#endif

#ifndef _syscall2
#define _syscall2(type, name, type1, arg1, type2, arg2)			\
type name(type1 arg1, type2 arg2)					\
____sc_body(2, type, name, arg2, arg1)
#endif

#ifndef _syscall3
#define _syscall3(type, name, type1, arg1, type2, arg2, type3, arg3)	\
type name(type1 arg1, type2 arg2, type3 arg3)				\
____sc_body(3, type, name, arg3, arg2, arg1)
#endif

#ifndef _syscall4
#define _syscall4(type, name, type1, arg1, type2, arg2, type3, arg3,	\
			      type4, arg4) 				\
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4)		\
____sc_body(4, type, name, arg4, arg3, arg2, arg1)
#endif

#ifndef _syscall5
#define _syscall5(type, name, type1, arg1, type2, arg2, type3, arg3,	\
    			      type4, arg4, type5, arg5)			\
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)	\
____sc_body(5, type, name, arg5, arg4, arg3, arg2, arg1)
#endif

#ifndef _syscall6
#define _syscall6(type, name, type1, arg1, type2, arg2, type3, arg3,	\
			type4, arg4, type5, arg5, type6, arg6)		\
type name (type1 arg1, type2 arg2, type3 arg3,				\
	   type4 arg4, type5 arg5, type6 arg6)				\
____sc_body(6, type, name, arg6, arg5, arg4, arg3, arg2, arg1)
#endif

