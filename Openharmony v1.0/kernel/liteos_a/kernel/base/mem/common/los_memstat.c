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

#include "los_memstat_pri.h"
#include "los_task_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

LITE_OS_SEC_BSS_MINOR STATIC TskMemUsedInfo g_tskMemUsedInfo[LOSCFG_BASE_CORE_TSK_LIMIT];

LITE_OS_SEC_TEXT_MINOR VOID OsTaskMemUsedInc(UINT32 usedSize, UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return;
    }
    if (OS_INT_ACTIVE) {
        return;
    }
    g_tskMemUsedInfo[taskID].memUsed += usedSize;
}

LITE_OS_SEC_TEXT_MINOR VOID OsTaskMemUsedDec(UINT32 usedSize, UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return;
    }
    if (OS_INT_ACTIVE) {
        return;
    }
    if (g_tskMemUsedInfo[taskID].memUsed < usedSize) {
        PRINT_WARN("mem used of current task '%s':0x%x, decrease size:0x%x\n",
                   OsCurrTaskGet()->taskName, g_tskMemUsedInfo[taskID].memUsed, usedSize);
        return;
    }
    g_tskMemUsedInfo[taskID].memUsed -= usedSize;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsTaskMemUsage(UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return LOS_NOK;
    }

    return g_tskMemUsedInfo[taskID].memUsed;
}

LITE_OS_SEC_TEXT_MINOR VOID OsTaskMemClear(UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return;
    }
    if (g_tskMemUsedInfo[taskID].memUsed != 0) {
        PRINT_WARN("mem used of task '%s' is:0x%x, not zero when task being deleted\n",
                   OsCurrTaskGet()->taskName, g_tskMemUsedInfo[taskID].memUsed);
    }
    g_tskMemUsedInfo[taskID].memUsed = 0;
}

#ifdef LOS_MEM_SLAB

LITE_OS_SEC_BSS_MINOR STATIC TskSlabUsedInfo g_tskSlabUsedInfo[LOSCFG_BASE_CORE_TSK_LIMIT];
LITE_OS_SEC_TEXT_MINOR VOID OsTaskSlabUsedInc(UINT32 usedSize, UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return;
    }

    g_tskSlabUsedInfo[taskID].slabUsed += usedSize;
}

LITE_OS_SEC_TEXT_MINOR VOID OsTaskSlabUsedDec(UINT32 usedSize, UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return;
    }

    g_tskSlabUsedInfo[taskID].slabUsed -= usedSize;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsTaskSlabUsage(UINT32 taskID)
{
    if (taskID >= LOSCFG_BASE_CORE_TSK_LIMIT) {
        return LOS_NOK;
    }

    return g_tskSlabUsedInfo[taskID].slabUsed;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */