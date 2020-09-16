/*-
 * Copyright (c) 1982, 1986, 1991, 1993
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
 *	From: @(#)kern_clock.c	8.5 (Berkeley) 1/21/94
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/kern/kern_timeout.c 360633 2020-05-04 16:30:36Z jhb $");

#include <sys/callout.h>
#include <sys/mutex.h>
#include "los_swtmr.h"

/*
 * Note: Convert freebsd callout to Huawei LiteOS timeout, follow events would happen
 * 1. function handle must forece convert
 * 2. Huawei LiteOS timer expires scale is millisecond, so check input ticks is millisecond scale
 */

void
callout_init_mtx(struct callout *c, struct pthread_mutex *mtx, int flag)
{
        (void)flag;
        if (c != NULL) {
                c->tm_mtx = mtx;
                mtx_init(&c->callout_mtx,0,0,0);
                LOS_SpinInit(&c->lock);
                c->timer_id = OS_SWTMR_MAX_TIMERID;
        }
}

void
callout_function(void *arg)
{
        struct callout* callout = arg;

        (callout->callout_data.func)((uintptr_t)(callout->callout_data.arg));
}

void
callout_reset(struct callout *c, int to_ticks, void (*func)(void *), void *arg)
{
        uint32_t int_save;
        uint32_t ret;

        if (c != NULL) {
                callout_stop(c);
                LOS_SpinLockSave(&c->lock, &int_save);

                c->callout_data.func = (timer_func)func;
                c->callout_data.arg = arg;
                ret = LOS_SwtmrCreate((to_ticks==0 ? 1 : to_ticks),
                                      LOS_SWTMR_MODE_NO_SELFDELETE,
                                      (SWTMR_PROC_FUNC)callout_function,
                                      (unsigned short *)&c->timer_id,
                                      (uintptr_t)c);
                if (ret != LOS_OK) {
                        PRINTK("add_timer<error> timer create failed: %u \n", ret);
                } else {
                        ret = LOS_SwtmrStart(c->timer_id);
                        if (ret != LOS_OK) {
                                PRINTK("add_timer<error> timer start failed: %u \n", ret);
                        }
                }
                LOS_SpinUnlockRestore(&c->lock, int_save);
        }
}

void
callout_stop(struct callout *c)
{
        uint32_t int_save;
        if (c != NULL) {
                LOS_SpinLockSave(&c->lock, &int_save);
                (void)LOS_SwtmrDelete(c->timer_id);
                LOS_SpinUnlockRestore(&c->lock, int_save);
        }
}

void
callout_drain(struct callout *c)
{
        if(!c || !c->tm_mtx){
                return ;
        }
        mtx_lock(c->tm_mtx);
        callout_stop(c);
        mtx_unlock(c->tm_mtx);
}
