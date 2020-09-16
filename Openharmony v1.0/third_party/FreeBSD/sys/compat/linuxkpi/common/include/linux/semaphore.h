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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/semaphore.h 328653 2018-02-01 13:01:44Z hselasky $
 */
#ifndef _LINUX_SEMAPHORE_H_
#define _LINUX_SEMAPHORE_H_

#include "los_sem_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define UNINIT_VALUE 0xFFFFFFFF
#define ERESTARTSYS 512 /* The return vlaue of down_interruptiable in Linux */

struct semaphore {
    LosSemCB *sem;
    int count;
};

typedef struct semaphore losMutexDef_t;
#define DECLARE_MUTEX(x) struct semaphore x = { (LosSemCB *)UNINIT_VALUE, 1 }
#define DECLARE_MUTEX_LOCKED(x) struct semaphore x = { (LosSemCB *)UNINIT_VALUE, 0 }
#define DEFINE_SEMAPHORE(x) DECLARE_MUTEX(x)

extern int _sema_lock(losMutexDef_t *sem);
extern int _sema_unlock(losMutexDef_t *sem);
extern int _sema_init(losMutexDef_t *sem, unsigned int value);
extern int _sema_destory(losMutexDef_t *sem);
extern int _sema_trylock(losMutexDef_t *sem);

#define init_MUTEX(sem)         _sema_init((losMutexDef_t*)(sem), 1)
#define destory_MUTEX(sem)      _sema_destory((losMutexDef_t*)(sem))
#define init_MUTEX_LOCKED(sem)  (VOID)_sema_init((losMutexDef_t*)(sem), 0);
#define down(sem)               _sema_lock((losMutexDef_t*)(sem))
#define down_interruptible(sem) _sema_lock((losMutexDef_t*)(sem))
#define down_trylock(sem)       _sema_trylock((losMutexDef_t*)(sem))
#define up(sem)                 _sema_unlock((losMutexDef_t*)(sem))

#define sema_init(sem, n) do {  \
    if ((n) == 1) {             \
        init_MUTEX(sem);        \
    } else {                    \
        init_MUTEX_LOCKED(sem); \
    }                           \
} while (0)

#define sema_destory(sem) do { \
    destory_MUTEX(sem);        \
} while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_SEMAPHORE_H_ */
