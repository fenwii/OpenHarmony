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

#ifndef _LOS_MEMSTAT_PRI_H
#define _LOS_MEMSTAT_PRI_H

#include "los_typedef.h"
#include "los_memory.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct {
    UINT32 memUsed;
} TskMemUsedInfo;

extern VOID OsTaskMemUsedInc(UINT32 usedSize, UINT32 taskID);
extern VOID OsTaskMemUsedDec(UINT32 usedSize, UINT32 taskID);
extern UINT32 OsTaskMemUsage(UINT32 taskID);
extern VOID OsTaskMemClear(UINT32 taskID);
#define OS_MEM_ENABLE_MEM_STATISTICS

#ifdef LOS_MEM_SLAB
typedef struct {
    UINT32 slabUsed;
} TskSlabUsedInfo;

extern VOID OsTaskSlabUsedInc(UINT32 usedSize, UINT32 taskID);
extern VOID OsTaskSlabUsedDec(UINT32 usedSize, UINT32 taskID);
extern UINT32 OsTaskSlabUsage(UINT32 taskID);
#endif

#ifdef OS_MEM_ENABLE_MEM_STATISTICS
#define OS_MEM_ADD_USED(usedSize, taskID)    OsTaskMemUsedInc(usedSize, taskID)
#define OS_MEM_REDUCE_USED(usedSize, taskID) OsTaskMemUsedDec(usedSize, taskID)
#define OS_MEM_CLEAR(taskID)                 OsTaskMemClear(taskID)
#ifdef LOS_MEM_SLAB
#define OS_SLAB_ADD_USED(usedSize, taskID)    OsTaskSlabUsedInc(usedSize, taskID)
#define OS_SLAB_REDUCE_USED(usedSize, taskID) OsTaskSlabUsedDec(usedSize, taskID)
#endif
#else
#define OS_MEM_ADD_USED(usedSize, taskID)
#define OS_MEM_REDUCE_USED(usedSize, taskID)
#define OS_MEM_CLEAR(taskID)
#ifdef LOS_MEM_SLAB
#define OS_SLAB_ADD_USED(usedSize, taskID)
#define OS_SLAB_REDUCE_USED(usedSize, taskID)
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_MEMSTAT_PRI_H */
