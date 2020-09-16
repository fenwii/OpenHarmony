/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013, 2014 Mellanox Technologies, Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/module.h 335435 2018-06-20 06:59:39Z hselasky $
 */
#ifndef	_LINUX_MODULE_H_
#define	_LINUX_MODULE_H_

#include <sys/cdefs.h>
#include <sys/kernel.h>
#include <sys/types.h>

#include <linux/list.h>
#include <linux/compiler.h>
#include <linux/moduleparam.h>
#include "linux/kernel.h"

#define MODULE_AUTHOR(name)
#define MODULE_DESCRIPTION(name)
#define	MODULE_INFO(tag, info)
#define	MODULE_FIRMWARE(firmware)
#define MODULE_VERSION(version)

struct module {
};

#define	THIS_MODULE	((struct module *)0)

#define	__MODULE_STRING(x) __stringify(x)

/* OFED pre-module initialization */
#define	SI_SUB_OFED_PREINIT	(SI_SUB_ROOT_CONF - 2)
/* OFED default module initialization */
#define	SI_SUB_OFED_MODINIT	(SI_SUB_ROOT_CONF - 1)
#define SI_SUB_POST_CORE_INIT	(SI_SUB_DRIVERS + 1)
#define SI_SUB_ARCH_INIT	(SI_SUB_DRIVERS + 2)
#define SI_SUB_SUBSYS_INIT	(SI_SUB_DRIVERS + 3)

static inline void
_module_run(void *arg)
{
	int (*fn)(void);
	fn = arg;
	if (fn == NULL) {
		PRINTK("_module_run null ptr! \n");
		return;
	}
	int ret = fn();
	if (ret) {
		PRINTK("_module_run function callback ret:%d! \n", ret);
	}
}

#define	module_init(fn)							\
	SYSINIT(fn, SI_SUB_OFED_MODINIT, SI_ORDER_FIRST, _module_run, (fn))

#define	module_exit(fn)						\
	SYSUNINIT(fn, SI_SUB_OFED_MODINIT, SI_ORDER_SECOND, _module_run, (fn))

/*
 * The following two macros are a workaround for not having a module
 * load and unload order resolver:
 */
#define	module_init_order(fn, order)					\
	SYSINIT(fn, SI_SUB_OFED_MODINIT, (order), _module_run, (fn))

#define	module_exit_order(fn, order)				\
	SYSUNINIT(fn, SI_SUB_OFED_MODINIT, (order), _module_run, (fn))

#define	module_get(module)
#define	module_put(module)
#define	try_module_get(module)	1

/*
 * The sysinit table itself.  Items are checked off as the are run.
 * If we want to register new sysinit types, add them to newsysinit.
 */
SET_DECLARE(sysinit_set, struct sysinit);
#define postcore_initcall(fn)   SYSINIT(fn, SI_SUB_POST_CORE_INIT, SI_ORDER_FIRST, _module_run, (fn))
#define arch_initcall(fn)       SYSINIT(fn, SI_SUB_ARCH_INIT, SI_ORDER_FIRST, _module_run, (fn))
#define subsys_initcall(fn)     SYSINIT(fn, SI_SUB_SUBSYS_INIT, SI_ORDER_FIRST, _module_run, (fn))

static inline void mi_startup(enum sysinit_sub_id sub_id)
{
	struct sysinit **sipp = NULL;	/* system initialization*/
	struct sysinit **xipp = NULL;	/* interior loop of sort*/
	struct sysinit *save = NULL;	/* bubble*/
	struct sysinit **sysinit = SET_BEGIN(sysinit_set);
	struct sysinit **sysinit_end = SET_LIMIT(sysinit_set);

	/*
	 * Perform a bubble sort of the system initialization objects by
	 * their subsystem (primary key) and order (secondary key).
	 */
	for (sipp = sysinit; sipp < sysinit_end; sipp++) {
		for (xipp = sipp + 1; xipp < sysinit_end; xipp++) {
			if ((*sipp)->subsystem < (*xipp)->subsystem ||
				((*sipp)->subsystem == (*xipp)->subsystem &&
				(*sipp)->order <= (*xipp)->order))
				continue;	/* skip*/
			save = *sipp;
			*sipp = *xipp;
			*xipp = save;
		}
	}

	/*
	 * Traverse the (now) ordered list of system initialization tasks.
	 * Perform each task, and continue on to the next task.
	 */
	for (sipp = sysinit; sipp < sysinit_end; sipp++) {
		if ((*sipp)->subsystem > sub_id) {
			break;
		}
		/* Call function */
		(*((*sipp)->func))((*sipp)->udata);
	}
}

#endif	/* _LINUX_MODULE_H_ */
