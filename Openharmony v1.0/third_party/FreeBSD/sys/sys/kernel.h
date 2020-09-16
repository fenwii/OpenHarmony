/*-
 * Copyright (c) 1995 Terrence R. Lambert
 * All rights reserved.
 *
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)kernel.h	8.3 (Berkeley) 1/21/94
 * $FreeBSD: releng/11.4/sys/sys/kernel.h 358936 2020-03-13 08:53:26Z hselasky $
 */

#ifndef _SYS_KERNEL_H_
#define	_SYS_KERNEL_H_

#define      __GNUCLIKE___SECTION 1
#include <sys/linker_set.h>

/*
 * Enumerated types for known system startup interfaces.
 *
 * Startup occurs in ascending numeric order; the list entries are
 * sorted prior to attempting startup to guarantee order.  Items
 * of the same level are arbitrated for order based on the 'order'
 * element.
 *
 * These numbers are arbitrary and are chosen ONLY for ordering; the
 * enumeration values are explicit rather than implicit to provide
 * for binary compatibility with inserted elements.
 *
 * The SI_SUB_LAST value must have the highest lexical value.
 */
enum sysinit_sub_id {
	SI_SUB_KMEM		= 0x1800000,	/* kernel memory*/
	SI_SUB_DRIVERS		= 0x3100000,	/* Let Drivers initialize */
	SI_SUB_CONFIGURE	= 0x3800000,	/* Configure devices */
	SI_SUB_ROOT_CONF	= 0xb000000,	/* Find root devices */
	SI_SUB_LAST		= 0xfffffff	/* final initialization */
};


/*
 * Some enumerated orders; "ANY" sorts last.
 */
enum sysinit_elem_order {
	SI_ORDER_FIRST		= 0x0000000,	/* first*/
	SI_ORDER_SECOND		= 0x0000001,	/* second*/
	SI_ORDER_THIRD		= 0x0000002,	/* third*/
	SI_ORDER_FOURTH		= 0x0000003,	/* fourth*/
	SI_ORDER_FIFTH		= 0x0000004,	/* fifth*/
	SI_ORDER_SIXTH		= 0x0000005,	/* sixth*/
	SI_ORDER_SEVENTH	= 0x0000006,	/* seventh*/
	SI_ORDER_EIGHTH		= 0x0000007,	/* eighth*/
	SI_ORDER_MIDDLE		= 0x1000000,	/* somewhere in the middle */
	SI_ORDER_ANY		= 0xfffffff	/* last*/
};


/*
 * A system initialization call instance
 *
 * At the moment there is one instance of sysinit.  We probably do not
 * want two which is why this code is if'd out, but we definitely want
 * to discern SYSINIT's which take non-constant data pointers and
 * SYSINIT's which take constant data pointers,
 *
 * The C_* macros take functions expecting const void * arguments
 * while the non-C_* macros take functions expecting just void * arguments.
 *
 * With -Wcast-qual on, the compiler issues warnings:
 *	- if we pass non-const data or functions taking non-const data
 *	  to a C_* macro.
 *
 *	- if we pass const data to the normal macros
 *
 * However, no warning is issued if we pass a function taking const data
 * through a normal non-const macro.  This is ok because the function is
 * saying it won't modify the data so we don't care whether the data is
 * modifiable or not.
 */

typedef void (*sysinit_nfunc_t)(void *);
typedef void (*sysinit_cfunc_t)(const void *);

struct sysinit {
	enum sysinit_sub_id	subsystem;	/* subsystem identifier*/
	enum sysinit_elem_order	order;		/* init order within subsystem*/
	sysinit_cfunc_t func;			/* function		*/
	const void	*udata;			/* multiplexer/argument */
};

/*
 * Default: no special processing
 *
 * The C_ version of SYSINIT is for data pointers to const
 * data ( and functions taking data pointers to const data ).
 * At the moment it is no different from SYSINIT and thus
 * still results in warnings.
 *
 * The casts are necessary to have the compiler produce the
 * correct warnings when -Wcast-qual is used.
 *
 */
#define	C_SYSINIT(uniquifier, subsystem, order, func, ident)	\
	static struct sysinit uniquifier ## _sys_init = {	\
		subsystem,					\
		order,						\
		func,						\
		(ident)						\
	};							\
	DATA_SET(sysinit_set,uniquifier ## _sys_init)

#define	SYSINIT(uniquifier, subsystem, order, func, ident)	\
	C_SYSINIT(uniquifier, subsystem, order,			\
	(sysinit_cfunc_t)(sysinit_nfunc_t)func, (void *)(ident))

/*
 * Called on module unload: no special processing
 */
#define	C_SYSUNINIT(uniquifier, subsystem, order, func, ident)	\
	static struct sysinit uniquifier ## _sys_uninit = {	\
		subsystem,					\
		order,						\
		func,						\
		(ident)						\
	};							\
	DATA_SET(sysuninit_set,uniquifier ## _sys_uninit)

#define	SYSUNINIT(uniquifier, subsystem, order, func, ident)	\
	C_SYSUNINIT(uniquifier, subsystem, order,		\
	(sysinit_cfunc_t)(sysinit_nfunc_t)func, (void *)(ident))
#endif /* !_SYS_KERNEL_H_*/
