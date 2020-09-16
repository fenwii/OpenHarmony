/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2017 Mellanox Technologies, Ltd.
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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/spinlock.h 331756 2018-03-30 02:04:46Z emaste $
 */
#ifndef	_LINUX_SPINLOCK_H_
#define	_LINUX_SPINLOCK_H_

#include "los_typedef.h"
#include "sys_config.h"
#include "los_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct Spinlock spinlock_t;

#define DEFINE_SPINLOCK(x) spinlock_t x = SPIN_LOCK_INITIALIZER(x)

#define SPIN_MACRO_START do {
#define SPIN_MACRO_END   } while (0)

#define SPIN_EMPTY_STATEMENT SPIN_MACRO_START SPIN_MACRO_END

#define SPIN_UNUSED_PARAM(_type_, _name_) SPIN_MACRO_START      \
    _type_ __tmp1 = (_name_);                                     \
    _type_ __tmp2 = __tmp1;                                       \
    __tmp1 = __tmp2;                                              \
SPIN_MACRO_END

#define spin_lock_bh(lock)               \
SPIN_MACRO_START;                         \
SPIN_UNUSED_PARAM(spinlock_t *, lock);    \
SPIN_MACRO_END

#define spin_unlock_bh(lock)             \
SPIN_MACRO_START;                         \
SPIN_UNUSED_PARAM(spinlock_t *, lock);    \
SPIN_MACRO_END

#if (LOSCFG_KERNEL_SMP == YES)
#define spin_lock_init(lock) do {LOS_SpinInit(lock);} while (0)
#define spin_lock(lock) do {LOS_SpinLock(lock);} while (0)
#define spin_unlock(lock) do {LOS_SpinUnlock(lock);} while (0)

#define spin_lock_irqsave(lock, flags)  do {LOS_SpinLockSave(lock, (UINT32 *)&flags);} while (0)
#define spin_unlock_irqrestore(lock, flags)  do {LOS_SpinUnlockRestore(lock, (UINT32)flags);} while (0)
#else

#define spin_lock_init(lock)             \
SPIN_MACRO_START;                         \
SPIN_UNUSED_PARAM(spinlock_t *, lock);    \
SPIN_MACRO_END

#define spin_lock(lock) do {(void)(lock);LOS_TaskLock();} while (0)
#define spin_unlock(lock) do {(void)(lock);LOS_TaskUnlock();} while (0)

#define spin_lock_irqsave(lock, flags)  do {flags = LOS_IntLock();spin_lock(lock);} while (0)
#define spin_unlock_irqrestore(lock, flags)  do {spin_unlock(lock);LOS_IntRestore(flags);} while (0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_SPINLOCK_H_ */
