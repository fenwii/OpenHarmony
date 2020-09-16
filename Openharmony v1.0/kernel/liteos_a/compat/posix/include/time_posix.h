/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _TIME_PRI_H
#define _TIME_PRI_H

#include "time.h"
#include "errno.h"
#include "los_sys_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* internal functions */
STATIC INLINE BOOL ValidTimeSpec(const struct timespec *tp)
{
    /* Fail a NULL pointer */
    if (tp == NULL) {
        return FALSE;
    }

    /* Fail illegal nanosecond values */
    if ((tp->tv_nsec < 0) || (tp->tv_nsec >= OS_SYS_NS_PER_SECOND) || (tp->tv_sec < 0)) {
        return FALSE;
    }

    return TRUE;
}

STATIC INLINE UINT32 OsTimeSpec2Tick(const struct timespec *tp)
{
    UINT64 tick, ns;

    ns = (UINT64)tp->tv_sec * OS_SYS_NS_PER_SECOND + tp->tv_nsec;
    /* Round up for ticks */
    tick = (ns * LOSCFG_BASE_CORE_TICK_PER_SECOND + (OS_SYS_NS_PER_SECOND - 1)) / OS_SYS_NS_PER_SECOND;
    if (tick > LOS_WAIT_FOREVER) {
        tick = LOS_WAIT_FOREVER;
    }
    return (UINT32)tick;
}

STATIC INLINE VOID OsTick2TimeSpec(struct timespec *tp, UINT32 tick)
{
    UINT64 ns = ((UINT64)tick * OS_SYS_NS_PER_SECOND) / LOSCFG_BASE_CORE_TICK_PER_SECOND;
    tp->tv_sec = (time_t)(ns / OS_SYS_NS_PER_SECOND);
    tp->tv_nsec = (long)(ns % OS_SYS_NS_PER_SECOND);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* _TIME_PRI_H */