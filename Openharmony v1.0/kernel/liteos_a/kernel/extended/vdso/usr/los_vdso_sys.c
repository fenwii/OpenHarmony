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

#include "asm/page.h"
#include "time.h"
#include "sys/time.h"
#include "los_typedef.h"
#include "los_vdso_datapage.h"

STATIC INT32 VdsoGetRealtimeCoarse(struct timespec *ts, const VdsoDataPage *usrVdsoDataPage)
{
    do {
        if (!usrVdsoDataPage->lockCount) {
            ts->tv_sec = usrVdsoDataPage->realTimeSec;
            ts->tv_nsec = usrVdsoDataPage->realTimeNsec;
            return 0;
        }
    } while (1);
}

STATIC INT32 VdsoGetMonotimeCoarse(struct timespec *ts, const VdsoDataPage *usrVdsoDataPage)
{
    do {
        if (!usrVdsoDataPage->lockCount) {
            ts->tv_sec = usrVdsoDataPage->monoTimeSec;
            ts->tv_nsec = usrVdsoDataPage->monoTimeNsec;
            return 0;
        }
    } while (1);
}

STATIC size_t LocVdsoStart(size_t vdsoStart, const CHAR *elfHead, const size_t len)
{
    CHAR *head = NULL;
    INT32 i;
    INT32 loop;

    for (i = 1; i <= MAX_PAGES; i++) {
        head = (CHAR *)((UINTPTR)vdsoStart);
        for (loop = len; loop >= 1; loop--) {
            if (*head++ != *(elfHead + len - loop)) {
                break;
            }
        }
        if (loop) {
            vdsoStart -= PAGE_SIZE;
        } else {
            break;
        }
    }

    if (i > MAX_PAGES) {
        return 0;
    }
    return (vdsoStart - PAGE_SIZE);
}

INT32 VdsoClockGettime(clockid_t clk, struct timespec *ts)
{
    INT32 ret;
    size_t vdsoStart;

    __asm__ __volatile__("mov %0, pc" : "=r"(vdsoStart));
    vdsoStart = vdsoStart - (vdsoStart & (PAGE_SIZE - 1));
    vdsoStart = LocVdsoStart(vdsoStart, ELF_HEAD, ELF_HEAD_LEN);
    if (vdsoStart == 0) {
        return -1;
    }

    VdsoDataPage *usrVdsoDataPage = (VdsoDataPage *)(UINTPTR)vdsoStart;

    switch (clk) {
        case CLOCK_REALTIME_COARSE:
            ret = VdsoGetRealtimeCoarse(ts, usrVdsoDataPage);
            break;
        case CLOCK_MONOTONIC_COARSE:
            ret = VdsoGetMonotimeCoarse(ts, usrVdsoDataPage);
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}
