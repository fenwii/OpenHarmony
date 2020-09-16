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

#ifndef _LOS_OOM_H
#define _LOS_OOM_H
#include "los_typedef.h"

#define OOM_TASK_PRIORITY                   9
#define OOM_TASK_STACK_SIZE                 0x1000

#define OOM_CHECK_MIN                       10      /* 0.1s */
#define OOM_DEFAULT_CHECK_INTERVAL          100     /* 1s */
#define OOM_CHECK_MAX                       1000    /* 10s */

#define OOM_DEFAULT_LOW_MEM_THRESHOLD       0x80000  /* 512KByte */
#define OOM_DEFAULT_LOW_MEM_THRESHOLD_MIN   0        /* 0, means always no memory */
#define OOM_DEFAULT_LOW_MEM_THRESHOLD_MAX   0x100000 /* 1MByte */

#define OOM_DEFAULT_RECLAIM_MEM_THRESHOLD   0x500000 /* 5MByte */

typedef UINT32 (*OomFn)(UINTPTR param);

typedef struct {
    UINT32       lowMemThreshold;       /* byte */
    UINT32       reclaimMemThreshold;   /* byte */
    UINT32       checkInterval;         /* microsecond */
    OomFn        processVictimCB;       /* process victim process cb function */
    OomFn        scoreCB;               /* out of memory, the process score function */
    UINT16       swtmrID;
    BOOL         enabled;               /* oom is enabled or not */
} OomCB;

LITE_OS_SEC_TEXT_MINOR UINT32 OomTaskInit(VOID);
LITE_OS_SEC_TEXT_MINOR VOID OomInfodump(VOID);
LITE_OS_SEC_TEXT_MINOR VOID OomEnable(VOID);
LITE_OS_SEC_TEXT_MINOR VOID OomDisable(VOID);
LITE_OS_SEC_TEXT_MINOR VOID OomSetLowMemThreashold(UINT32 lowMemThreshold);
LITE_OS_SEC_TEXT_MINOR VOID OomSetReclaimMemThreashold(UINT32 reclaimMemThreshold);
LITE_OS_SEC_TEXT_MINOR VOID OomSetCheckInterval(UINT32 checkInterval);
LITE_OS_SEC_TEXT_MINOR BOOL OomCheckProcess(VOID);
#endif

