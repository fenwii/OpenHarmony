/*-
 * Copyright (c) 1997 Berkeley Software Design, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Berkeley Software Design Inc's name may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BERKELEY SOFTWARE DESIGN INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL BERKELEY SOFTWARE DESIGN INC BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from BSDI $Id: mutex.h,v 2.7.2.35 2000/04/27 03:10:26 cp Exp $
 * $FreeBSD: releng/11.4/sys/sys/mutex.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef _SYS_MUTEX_H_
#define _SYS_MUTEX_H_

#include <pthread.h>

/*
 * Mutex types and options passed to mtx_init().  MTX_QUIET and MTX_DUPOK
 * can also be passed in.
 */
#define MTX_DEF         0x00000000      /* DEFAULT (sleep) lock */
#define MTX_SPIN        0x00000001      /* Spin lock (disables interrupts) */
#define MTX_RECURSE     0x00000004      /* Option: lock allowed to recurse */
#define MTX_NOWITNESS   0x00000008      /* Don't do any witness checking. */
#define MTX_NOPROFILE   0x00000020      /* Don't profile this lock */

#define MA_OWNED 1
#define MA_NOTOWNED 2

struct pthread_mutex;
#define mtx pthread_mutex


static inline void
mtx_init(pthread_mutex_t *mtx, const char *name, const char *type, int opts)
{
    pthread_mutexattr_t attr;
    (void)pthread_mutexattr_init(&attr);
    if ((unsigned int)opts & MTX_RECURSE)
        (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(mtx, &attr);
}

#define mtx_destroy(m)  (void)pthread_mutex_destroy((m))
#define mtx_lock(m)             (void)pthread_mutex_lock((m))
#define mtx_unlock(m)   (void)pthread_mutex_unlock((m))
#define mtx_lock_spin(m)
#define mtx_unlock_spin(m)
#define mtx_owned(m)  (((m)->owner == (void *)OsCurrTaskGet()) ? (1) : (0))

#define _mtx_assert(m, what) do {         \
    switch (what) {         \
        case MA_OWNED:  \
            /* if (!mtx_owned(m)){ panic("mtx assert at %s:%d\n", __FUNCTION__, __LINE__);}*/       \
            break;  \
        case MA_NOTOWNED:       \
            if (mtx_owned(m)){ panic("mtx assert at %s:%d\n", __FUNCTION__, __LINE__);}             \
            break;  \
        default:        \
            {panic("mtx assert at %s:%d\n", __FUNCTION__, __LINE__);}       \
        } \
} while (0)

#ifdef INVARIANTS
#define mtx_assert_(m, what, file, line)                                \
        _mtx_assert((m), (what), (file), (line))

#define GIANT_REQUIRED  mtx_assert_(&Giant, MA_OWNED, __FILE__, __LINE__)

#else   /* INVARIANTS */
#define mtx_assert_(m, what, file, line)        (void)0
#define GIANT_REQUIRED
#endif  /* INVARIANTS */

#define mtx_assert(m, what) mtx_assert_(m, what, __FILE__, __LINE__)

#define thread_lock(td) LOS_TaskLock()
#define thread_unlock(td) LOS_TaskUnlock()

#endif	/* _SYS_MUTEX_H_ */
