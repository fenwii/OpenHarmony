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

#include "los_memcheck.h"
#include "los_memory_pri.h"
#include "los_membox_pri.h"
#include "los_multipledlinkhead_pri.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if LOSCFG_PLATFORM_EXC == YES
extern UINT8 g_memMang[MEM_INFO_SIZE];
/*****************************************************************************
 Function    : LOS_MemExcInfoGet
 Description : Get the information of the exc memory
 Input       : uwMemNum
 Output      : pstMemExcInfo
 Return      : return 0
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemExcInfoGet(UINT32 memNum, MEM_INFO_S *memExcInfo)
{
    UINT32 idx = 0;
    UINT32 maxBlk = 0;
    UINT32 blkCnt = 0;
    UINT32 blkSize = 0;
    MEM_INFO *memInfo = NULL;
    LosMemDynNode *pstTmpNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *pPool = (LOS_MEM_POOL_INFO *)NULL;
    LOS_MEM_POOL_INFO *pstPoolInfo = (LOS_MEM_POOL_INFO *)NULL;
    UINT8 *pEndPool = NULL;

    if (memNum >= *(UINT32 *)g_memMang || memExcInfo == NULL) {
        return LOS_NOK;
    }
    memInfo = (MEM_INFO *)(VOID *)(g_memMang + sizeof(UINT32)) + memNum;
    memExcInfo->uwType = memInfo->uwType;
    memExcInfo->uwStartAddr = memInfo->uwStartAddr;
    memExcInfo->uwSize = memInfo->uwSize;
    memExcInfo->uwFree = 0;
    memExcInfo->uwBlockSize = 0;
    memExcInfo->uwErrorAddr = 0;
    memExcInfo->uwErrorLen = 0;
    memExcInfo->uwErrorOwner = 0;

    if (memInfo->uwType == MEM_MANG_MEMBOX) {
        (VOID)LOS_MemboxStatisticsGet((VOID *)(memInfo->uwStartAddr), &maxBlk, &blkCnt, &blkSize);
        memExcInfo->uwBlockSize = blkSize;
        memExcInfo->uwSize = maxBlk; // Block num
        memExcInfo->uwFree = maxBlk - blkCnt;
        pPool = (LOS_MEM_POOL_INFO *)m_aucSysMem0;
        pstPoolInfo = pPool;
        pEndPool = (UINT8 *)pPool + pstPoolInfo->uwPoolSize;
        while (memInfo->blkAddrArray != NULL && idx < maxBlk) {
            char *tmpPtr = ((char **)(memInfo->blkAddrArray))[idx];
            if (tmpPtr != NULL) {
                pstTmpNode = (LosMemDynNode *)(tmpPtr - OS_MEM_NODE_HEAD_SIZE);
                if (!OS_MEM_MAGIC_VALID(pstTmpNode->freeNodeInfo.pstPrev)) {
                    goto errout;
                }
            }
            idx++;
        }
    } else if (memInfo->uwType == MEM_MANG_MEMORY) {
        memExcInfo->uwFree = memInfo->uwSize - LOS_MemTotalUsedGet((VOID *)(memInfo->uwStartAddr)) - OS_DLNK_HEAD_SIZE
                             - LOS_MemFreeBlksGet((VOID *)(memInfo->uwStartAddr)) * OS_MEM_NODE_HEAD_SIZE - sizeof(LOS_MEM_POOL_INFO);

        memExcInfo->uwBlockSize = 0;
        pPool = (LOS_MEM_POOL_INFO *)memInfo->uwStartAddr;
        if (pPool == NULL) {
            return LOS_OK;
        }
        pstPoolInfo = pPool;
        pEndPool = (UINT8 *)pPool + pstPoolInfo->uwPoolSize;

        for (pstTmpNode = (LosMemDynNode *)OS_MEM_FIRST_NODE(pPool); pstTmpNode < (LosMemDynNode *)OS_MEM_END_NODE(pPool, pstPoolInfo->uwPoolSize);
            pstTmpNode = (LosMemDynNode *)OS_MEM_NEXT_NODE(pstTmpNode)) {
            memExcInfo->uwBlockSize++;
            if (OS_MEM_NODE_GET_USED_FLAG(pstTmpNode->sizeAndFlag)) {
                if (!OS_MEM_MAGIC_VALID(pstTmpNode->freeNodeInfo.pstPrev)) {
                    goto errout;
                }
            }
            else { //is free node, check free node range
                if (!OS_MEM_MIDDLE_ADDR_OPEN_END(pPool, pstTmpNode->freeNodeInfo.pstPrev, pEndPool)) {
                    goto errout;
                }
                if (!OS_MEM_MIDDLE_ADDR_OPEN_END(pPool, pstTmpNode->freeNodeInfo.pstNext, pEndPool)) {
                    goto errout;
                }
            }

        }
    }
    return LOS_OK;
errout:
        memExcInfo->uwErrorAddr = (UINT32)(UINTPTR)((char*)pstTmpNode + OS_MEM_NODE_HEAD_SIZE);
        memExcInfo->uwErrorLen = (UINT32)OS_MEM_NODE_GET_SIZE(pstTmpNode->sizeAndFlag) - OS_MEM_NODE_HEAD_SIZE;
        memExcInfo->uwErrorOwner = (UINT32)(UINTPTR)(pstTmpNode->freeNodeInfo.pstNext);
        return LOS_OK;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
