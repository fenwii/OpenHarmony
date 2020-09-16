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

#include "vid_type.h"
#include "vid_api.h"
#include "los_memory.h"

UINT32 VidMapListInit(LosProcessCB *processCB)
{
    memset_s(&processCB->timerIdMap, sizeof(TimerIdMap), 0, sizeof(TimerIdMap));
    LOS_ListInit(&processCB->timerIdMap.head);
    processCB->timerIdMap.bitMap = (UINT32*)LOS_MemAlloc(m_aucSysMem0, sizeof(UINT32));
    if (processCB->timerIdMap.bitMap == NULL) {
        PRINT_ERR("%s %d, alloc memory failed\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }

    processCB->timerIdMap.mapCount = 1;
    (void)memset_s(processCB->timerIdMap.bitMap, sizeof(UINT32), 0, sizeof(UINT32));
    if (LOS_MuxInit(&processCB->timerIdMap.vidMapLock, NULL) != LOS_OK) {
        PRINT_ERR("%s %d, Create mutex for vmm failed\n", __FUNCTION__, __LINE__);
        LOS_MemFree(m_aucSysMem0, processCB->timerIdMap.bitMap);
        processCB->timerIdMap.bitMap = NULL;
        return LOS_NOK;
    }
    return LOS_OK;
}

void VidMapDestroy(LosProcessCB *processCB)
{
    TimerIdMapNode *idNode = NULL;
    TimerIdMapNode *idNodeNext = NULL;

    LOS_MuxLock(&processCB->timerIdMap.vidMapLock, LOS_WAIT_FOREVER);
    LOS_DL_LIST_FOR_EACH_ENTRY_SAFE(idNode, idNodeNext, &processCB->timerIdMap.head, TimerIdMapNode, node) {
        LOS_ListDelete(&idNode->node);
        LOS_MemFree(m_aucSysMem0, idNode);
    }

    LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);
    LOS_MemFree(m_aucSysMem0, processCB->timerIdMap.bitMap);
    LOS_MuxDestroy(&processCB->timerIdMap.vidMapLock);
}

static TimerIdMapNode *FindListNodeByVid(UINT16 vid)
{
    TimerIdMapNode *idNode = NULL;
    LosProcessCB *processCB = OsCurrProcessGet();

    LOS_MuxLock(&processCB->timerIdMap.vidMapLock, LOS_WAIT_FOREVER);
    LOS_DL_LIST_FOR_EACH_ENTRY(idNode, &processCB->timerIdMap.head, TimerIdMapNode, node) {
        if (vid == idNode->vid) {
            LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);
            return idNode;
        }
    }
    LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);

    return NULL;
}

static TimerIdMapNode *FindListNodeByRid(UINT32 rid)
{
    TimerIdMapNode *idNode = NULL;
    LosProcessCB *processCB = OsCurrProcessGet();

    LOS_MuxLock(&processCB->timerIdMap.vidMapLock, LOS_WAIT_FOREVER);
    LOS_DL_LIST_FOR_EACH_ENTRY(idNode, &processCB->timerIdMap.head, TimerIdMapNode, node) {
        if (rid == idNode->rid) {
            LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);
            return idNode;
        }
    }
    LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);

    return NULL;
}

static UINT16 GetFreeVid(VOID)
{
    UINT16 i, j;
    UINT32 num;
    UINT32 *tmp = NULL;
    LosProcessCB *processCB = OsCurrProcessGet();
    TimerIdMap *idMap = &processCB->timerIdMap;
    UINT16 mapMaxNum = idMap->mapCount;

    for (i = 0; i < mapMaxNum; i++) {
        num = idMap->bitMap[i];
        for (j = 0; j < INT_BIT_COUNT; j++) {
            if ((num & (1 << j)) == 0) {
                num |= 1 << j;
                idMap->bitMap[i] = num;
                return (INT_BIT_COUNT * i + j);
            }
        }
    }

    /* expand bit map */
    mapMaxNum++;
    if (mapMaxNum > VID_MAP_MAX_NUM) {
        PRINT_ERR("%s %d, timer vid run out\n", __FUNCTION__, __LINE__);
        return MAX_INVALID_TIMER_VID;
    }

    tmp = (UINT32*)LOS_MemAlloc(m_aucSysMem0, mapMaxNum * sizeof(UINT32));
    if (tmp == NULL) {
        PRINT_ERR("%s %d, alloc memory failed\n", __FUNCTION__, __LINE__);
        return MAX_INVALID_TIMER_VID;
    }

    (void)memcpy_s(tmp, mapMaxNum * sizeof(UINT32), idMap->bitMap, (mapMaxNum - 1) * sizeof(UINT32));
    idMap->bitMap = tmp;
    idMap->mapCount = mapMaxNum;
    idMap->bitMap[i] = 1;
    return (INT_BIT_COUNT * i);
}

static VOID ReleaseVid(UINT16 vid)
{
    UINT16 a, b;
    UINT32 *tmpMap = NULL;
    LosProcessCB *processCB = OsCurrProcessGet();
    TimerIdMap *idMap = &processCB->timerIdMap;
    UINT16 mapMaxNum = idMap->mapCount;

    if (vid >= (VID_MAP_MAX_NUM * INT_BIT_COUNT)) {
        return;
    }

    a = vid >> INT_BIT_SHIFT;
    b = vid & (INT_BIT_COUNT - 1);

    idMap->bitMap[a] &= ~(1 << b);

    /* shrink bit map */
    if (mapMaxNum > 1) {
        if (idMap->bitMap[mapMaxNum - 1] == 0) {
            mapMaxNum--;
            tmpMap = LOS_MemRealloc(m_aucSysMem0, idMap->bitMap, mapMaxNum * sizeof(UINT32));
            if (tmpMap) {
                idMap->bitMap = tmpMap;
                idMap->mapCount = mapMaxNum;
            }
        }
    }
}

UINT16 AddNodeByRid(UINT16 rid)
{
    TimerIdMapNode *tmp = NULL;
    LosProcessCB *processCB = OsCurrProcessGet();
    UINT16 vid;

    tmp = FindListNodeByRid(rid);
    if (tmp) {
        return tmp->vid;
    }

    LOS_MuxLock(&processCB->timerIdMap.vidMapLock, LOS_WAIT_FOREVER);
    vid = GetFreeVid();
    if (vid == MAX_INVALID_TIMER_VID) {
        LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);
        errno = ENOMEM;
        return MAX_INVALID_TIMER_VID;
    }
    tmp = (TimerIdMapNode *)LOS_MemAlloc(m_aucSysMem0, sizeof(TimerIdMapNode));
    if (tmp == NULL) {
        PRINT_ERR("%s %d, alloc memory failed\n", __FUNCTION__, __LINE__);
        LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);
        errno = ENOMEM;
        return MAX_INVALID_TIMER_VID;
    }
    tmp->rid = rid;
    tmp->vid = vid;

    LOS_ListTailInsert(&processCB->timerIdMap.head, &tmp->node);
    LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);

    return vid;
}

UINT16 GetRidByVid(UINT16 vid)
{
    TimerIdMapNode *tmp = FindListNodeByVid(vid);
    if (tmp) {
        return tmp->rid;
    }
    return 0xffff;
}

void RemoveNodeByVid(UINT16 vid)
{
    TimerIdMapNode *tmp = NULL;
    LosProcessCB *processCB = OsCurrProcessGet();

    tmp = FindListNodeByVid(vid);
    if (tmp == NULL) {
        return;
    }

    LOS_MuxLock(&processCB->timerIdMap.vidMapLock, LOS_WAIT_FOREVER);
    LOS_ListDelete(&tmp->node);
    ReleaseVid(tmp->vid);
    LOS_MuxUnlock(&processCB->timerIdMap.vidMapLock);
    LOS_MemFree(m_aucSysMem0, tmp);

    return;
}
