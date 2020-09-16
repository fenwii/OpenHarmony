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

#include <string.h>
#include "securec.h"
#include "los_hwi.h"
#include "los_typedef.h"
#include "los_membox.h"
#include "los_memory.h"
#include "los_memcheck_pri.h"

#if (LOSCFG_PLATFORM_EXC == YES) || (LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK == YES)
UINT8 g_memMang[MEM_INFO_SIZE];
#endif

UINT32 LOS_MemboxInit(VOID *boxMem, UINT32 boxSize, UINT32 blkSize)
{
    UINTPTR intSave;
#ifdef LOS_MEMBOX_CHECK
    UINT32 *memCount = (UINT32 *)g_memMang;
    MEM_INFO *memInfo = (MEM_INFO *)(g_memMang + sizeof(UINT32));
    UINT8 loop;
#endif

    if (boxMem == NULL) {
        return OS_ERROR;
    }

    /* Initialize memory block system, returns 0 if OK, 1 if fails. */
    if (blkSize == 0) {
        return OS_ERROR;
    }
    if (boxSize == 0) {
        return OS_ERROR;
    }

#ifdef LOS_MEMBOX_CHECK
    intSave = LOS_IntLock();
    for (loop = 0; loop < *memCount; loop++) {
        if (memInfo->uwStartAddr == (UINTPTR)boxMem) {
            (*memCount)--;
            break;
        }
        memInfo++;
    }
    if (*memCount < OS_SYS_MEM_NUM) {
        memInfo->uwType = MEM_MANG_MEMBOX;
        memInfo->uwStartAddr = (UINTPTR)boxMem;
        memInfo->uwSize = boxSize;
        UINT32 allocSize = boxSize / blkSize * sizeof(VOID *);
        VOID *ptr = LOS_MemAlloc(m_aucSysMem0, allocSize);
        if (ptr == NULL) {
            PRINT_ERR("LOS_MemAlloc return fail!\n");
            return LOS_NOK;
        } else {
            UINT32 ret = memset_s(ptr, allocSize, 0, allocSize);
            if (ret != LOS_OK) {
                (VOID)LOS_MemFree(m_aucSysMem0, ptr);
                PRINT_ERR("memset return fail!\n");
                return LOS_NOK;
            }
        }
        memInfo->blkAddrArray = ptr;
        (*memCount)++;
    }
    LOS_IntRestore(intSave);
#endif

    /* Create a Memory structure. */
    intSave = LOS_IntLock();
    ((OS_MEMBOX_S_P)boxMem)->uwMaxBlk = boxSize / blkSize;
    ((OS_MEMBOX_S_P)boxMem)->uwBlkSize = blkSize;
    ((OS_MEMBOX_S_P)boxMem)->uwBlkCnt = 0;
    LOS_IntRestore(intSave);

    return LOS_OK;
}

/* --------------------------- LOS_MemboxAlloc ---------------------------------- */
VOID *LOS_MemboxAlloc(VOID *boxMem)
{
    VOID *ret = NULL;
    UINTPTR intSave;

    intSave = LOS_IntLock();
    if (((OS_MEMBOX_S_P)boxMem)->uwBlkCnt < ((OS_MEMBOX_S_P)boxMem)->uwMaxBlk) {
        ret = LOS_MemAlloc(m_aucSysMem0, ((OS_MEMBOX_S_P)boxMem)->uwBlkSize);
        if (ret != NULL) {
            ((OS_MEMBOX_S_P)boxMem)->uwBlkCnt++;
#ifdef LOS_MEMBOX_CHECK
            UINT32 *memCount = (UINT32 *)g_memMang;
            MEM_INFO *memInfo = (MEM_INFO *)(VOID *)(g_memMang + sizeof(UINT32));
            UINT8 loop;
            UINT8 idx;
            for (loop = 0; loop < *memCount; loop++) {
                if (memInfo->uwStartAddr == (UINTPTR)boxMem) {
                    if (memInfo->blkAddrArray != NULL) {
                        for (idx = 0; idx < ((OS_MEMBOX_S_P)boxMem)->uwMaxBlk; idx++) {
                            if (((VOID **)(memInfo->blkAddrArray))[idx] == NULL) {
                                ((VOID **)(memInfo->blkAddrArray))[idx] = ret;
                                break;
                            }
                        }
                    }
                    break;
                }
                memInfo++;
           }
#endif
        } else {
            PRINT_ERR("LOS_AllocMem return fail!\n");
        }
    }
    LOS_IntRestore(intSave);
    return ret;
}

/* --------------------------- LOS_MemboxFree ---------------------------------- */
UINT32 LOS_MemboxFree(const VOID *boxMem, VOID *box)
{
    UINT32 freeRes;
    UINTPTR intSave;

    freeRes = LOS_MemFree(m_aucSysMem0, box);
    if (freeRes == LOS_OK) {
        intSave = LOS_IntLock();
        if (((OS_MEMBOX_S_P)boxMem)->uwBlkCnt) {
            ((OS_MEMBOX_S_P)boxMem)->uwBlkCnt--;
#ifdef LOS_MEMBOX_CHECK
            UINT32 *memCount = (UINT32 *)g_memMang;
            MEM_INFO *memInfo = (MEM_INFO *)(VOID *)(g_memMang + sizeof(UINT32));
            UINT8 loop;
            UINT8 idx;
            for (loop = 0; loop < *memCount; loop++) {
                if (memInfo->uwStartAddr == (UINTPTR)boxMem) {
                    if (memInfo->blkAddrArray != NULL) {
                        for (idx = 0; idx < ((OS_MEMBOX_S_P)boxMem)->uwMaxBlk; idx++) {
                            if (((VOID **)(memInfo->blkAddrArray))[idx] == box) {
                                ((VOID **)(memInfo->blkAddrArray))[idx] = NULL;
                                break;
                            }
                        }
                    }
                    break;
                }
                memInfo++;
            }
#endif
        }
        LOS_IntRestore(intSave);
    }
    return freeRes;
}

/* --------------------------- LOS_MemboxClr ---------------------------------- */
VOID LOS_MemboxClr(const VOID *boxMem, VOID *box)
{
    // Ignore the return code when matching CSEC rule 6.6(2).
    (VOID)memset_s(box, ((OS_MEMBOX_S_P)boxMem)->uwBlkSize, 0, ((OS_MEMBOX_S_P)boxMem)->uwBlkSize);
}

UINT32 LOS_MemboxStatisticsGet(const VOID *boxMem, UINT32 *maxBlk, UINT32 *blkCnt, UINT32 *blkSize)
{
    if ((boxMem == NULL) || (maxBlk == NULL) || (blkCnt == NULL) || (blkSize == NULL)) {
        return LOS_NOK;
    }

    *maxBlk = ((OS_MEMBOX_S_P)boxMem)->uwMaxBlk;
    *blkCnt = ((OS_MEMBOX_S_P)boxMem)->uwBlkCnt;
    *blkSize = ((OS_MEMBOX_S_P)boxMem)->uwBlkSize;

    return LOS_OK;
}

