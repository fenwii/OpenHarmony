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

#ifndef _LOS_FUTEX_PRI_H
#define _LOS_FUTEX_PRI_H
#include "los_list.h"

#define FUTEX_WAIT        0
#define FUTEX_WAKE        1
#define FUTEX_REQUEUE     3
#define FUTEX_WAKE_OP     5
#define FUTEX_LOCK_PI     6
#define FUTEX_UNLOCK_PI   7
#define FUTEX_TRYLOCK_PI  8
#define FUTEX_WAIT_BITSET 9

#define FUTEX_PRIVATE     128
#define FUTEX_MASK        0x3U

typedef struct {
    UINTPTR      key;
    UINT32       index;
    UINT32       pid;
    LOS_DL_LIST  pendList;
    LOS_DL_LIST  queueList;
    LOS_DL_LIST  futexList;
} FutexNode;

extern UINT32 OsFutexInit(VOID);
extern VOID OsFutexNodeDeleteFromFutexHash(FutexNode *node, BOOL isDeleteHead, FutexNode **headNode, BOOL *queueFlags);
extern INT32 OsFutexWake(const UINT32 *userVaddr, UINT32 flags, INT32 wakeNumber);
extern INT32 OsFutexWait(const UINT32 *userVaddr, UINT32 flags, UINT32 val, UINT32 absTime);
extern INT32 OsFutexRequeue(const UINT32 *userVaddr, UINT32 flags, INT32 wakeNumber,
                            INT32 count, const UINT32 *newUserVaddr);
#endif
