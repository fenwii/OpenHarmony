/* $FreeBSD: releng/11.4/stand/kshim/bsd_kernel.c 315221 2017-03-14 02:06:03Z pfg $ */
/*-
 * Copyright (c) 2013 Hans Petter Selasky. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "implementation/global_implementation.h"

#ifdef LOSCFG_DRIVERS_USB_HOST_DRIVER
extern volatile uint8_t g_device_is_ready;
#endif

#undef USB_DEBUG_VAR
#define	USB_DEBUG_VAR usb_debug

/*------------------------------------------------------------------------*
 * Implementation of mutex API
 *------------------------------------------------------------------------*/

struct mtx Giant = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
struct mtx Gcall = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

/*------------------------------------------------------------------------*
 * Implementation of device API
 *------------------------------------------------------------------------*/

#ifdef LOSCFG_USB_DEBUG
static uint8_t
devclass_equal(const char *a, const char *b)
{
	char ta, tb;

	if (a == b)
		return (1);
	if(!a || !b)
		return (0);
	while (1) {
		ta = *a;
		tb = *b;
		if (ta != tb)
			return (0);
		if (ta == 0)
			break;
		a++;
		b++;
	}
	return (1);
}

static TAILQ_HEAD(, debug_module_data) debug_module_head =
	    TAILQ_HEAD_INITIALIZER(debug_module_head);

void
debug_module_register(void *data)
{
	struct debug_module_data *mdata = data;
	TAILQ_INSERT_TAIL(&debug_module_head, mdata, entry);
}

void
debug_module_unregister(void *data)
{
	struct debug_module_data *mdata = data;
	TAILQ_REMOVE(&debug_module_head, mdata, entry);
}

struct debug_module_data *
get_debug_module(const char *modname)
{
	static struct debug_module_data *mod;

	TAILQ_FOREACH(mod, &debug_module_head, entry) {
		if (devclass_equal(mod->mod_name, modname)) {
			return (mod);
		}
	}
	return (NULL);
}

void
debug_module_dump(void)
{
	const struct debug_module_data *mod;

	TAILQ_FOREACH(mod, &debug_module_head, entry) {
		PRINTK("%s\n", mod->mod_name);
	}
}
#endif
#undef USB_DEBUG_VAR
