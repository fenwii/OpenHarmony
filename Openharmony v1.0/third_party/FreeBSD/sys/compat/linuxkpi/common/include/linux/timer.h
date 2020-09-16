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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/timer.h 335414 2018-06-20 06:38:03Z hselasky $
 */
#ifndef _LINUX_TIMER_H_
#define	_LINUX_TIMER_H_

#include "linux/kernel.h"
#include "los_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef unsigned long ULONG;

typedef struct timer_list {
    ULONG expires;
    VOID (*function)(ULONG);
    ULONG data;
    UINT16 timerid;
    UINT32 flag;
    BOOL created;
#define TIMER_VALID    0xABCDDCBA
#define TIMER_UNVALID  0xDCBAABCD
    SPIN_LOCK_S lock;
} timer_list_t;

static inline int timer_pending(const timer_list_t *timer)
{
    (void)timer;
    return 0;
}

#define init_timer(timer) \
    linux_init_timer(timer)

#define add_timer(timer) \
    linux_add_timer(timer)

#define del_timer(timer) \
    linux_del_timer(timer)

#define mod_timer(timer, expires) \
    linux_mod_timer(timer, expires)

#define del_timer_sync(timer) \
    linux_del_timer(timer)

extern void linux_init_timer(timer_list_t *timer);

extern void linux_add_timer(timer_list_t *timer);

extern int linux_del_timer(timer_list_t *timer);

extern int linux_mod_timer(timer_list_t *timer, ULONG expires);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LINUX_TIMER_H__ */
