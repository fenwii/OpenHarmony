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

#include "securec.h"
#include "los_memory_pri.h"
#include "los_memstat_pri.h"
#include "los_multipledlinkhead_pri.h"
#include "los_task_pri.h"
#include "los_exc.h"
#include "los_printf.h"
#ifdef LOS_MEM_LEAK_CHECK
#include "los_membox_pri.h"
#endif
#if (LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK == YES)
#include "los_memcheck_pri.h"
#endif
#ifdef LOSCFG_LIB_LIBC
#include "string.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_MEM_MUL_POOL == YES)
VOID *g_memPoolHead = NULL;
#endif

#if (LOSCFG_BASE_CORE_TASKSTACK_INDEPENDENT == YES)
__attribute__((section(".data"))) UINT32 g_sysStackAddrEnd;
#endif

UINT8 *g_sysNoCacheMem0 = (UINT8 *)NULL;
__attribute__((section(".data.init"))) UINT32 g_sysMemAddrEnd;
#ifdef OS_MEM_CHECK_DEBUG
static UINT8 g_checkMemLevel = (UINT8)LOS_MEM_CHECK_LEVEL_DEFAULT;
#endif

#ifdef LOS_MEM_LEAK_CHECK
MEM_CHECK_INFO g_checkInfo[CHECK_MAXCOUNT] = {0};
int g_memCount = 0;
int g_memPeakCount = 0;
int g_memCheckFlag = 0;
#endif

#ifdef LOSCFG_MEM_MUL_MODULE
UINT32 g_memInfo[MEM_MODULE_MAX + 1] = {0};
#endif

MALLOC_HOOK g_mallocHook = (MALLOC_HOOK)(UINTPTR)NULL;
LITE_OS_SEC_TEXT_INIT UINT32 OsMemSystemInit()
{
    UINT32 ret;
    UINT32 memSize;
    m_aucSysMem0 = (UINT8 *)(UINTPTR)(((UINT32)(UINTPTR)m_aucSysMem0 + (OS_MEM_NODE_ALIGN_SIZE - 1)) &
        ~(OS_MEM_NODE_ALIGN_SIZE - 1));
    memSize = ((UINT32)g_sysMemAddrEnd) - OS_SYS_NOCACHEMEM_SIZE - (UINT32)(UINTPTR)m_aucSysMem0;
    ret = LOS_MemInit(m_aucSysMem0, memSize);
    PRINT_INFO("LiteOS heap memory address:0x%x,size:0x%x\n", m_aucSysMem0, memSize);
    return ret;
}
#if (LOSCFG_BASE_CORE_TASKSTACK_INDEPENDENT == YES)
LITE_OS_SEC_TEXT_INIT UINT32 OsSysStackInit(UINT32 memStart)
{
    UINT32 ret;
    UINT32 memSize;
    UINT8 *sysStackAddr = NULL;
    sysStackAddr = (UINT8 *)((memStart + (OS_MEM_NODE_ALIGN_SIZE - 1)) & ~(OS_MEM_NODE_ALIGN_SIZE - 1));
    memSize = ((UINTPTR)g_sysStackAddrEnd) - (UINTPTR)sysStackAddr;
    ret = LOS_MemInit(sysStackAddr, memSize);
    PRINT_INFO("LiteOS stack memory address:0x%x,size:0x%x\n", sysStackAddr, memSize);
    return ret;
}
#endif

#if OS_SYS_NOCACHEMEM_SIZE
UINT32 OsNocacheMemSystemInit(VOID)
{
    UINT32 ret;
    g_sysNoCacheMem0 = (g_sysMemAddrEnd - OS_SYS_NOCACHEMEM_SIZE);
    ret = LOS_MemInit(g_sysNoCacheMem0, OS_SYS_NOCACHEMEM_SIZE);
    return ret;
}
#endif

VOID OsMemInfoPrint(VOID *pool);
VOID *OsMemFindNodeCtrl(VOID *headPtr);

/*****************************************************************************
 Function    : OsMemFindSuitableFreeBlock
 Description : find suitable free block use "best fit" algorithm
 Input       : pool       --- Pointer to memory pool
               allocSize  --- Size of memory in bytes which note need allocate
 Output      : None
 Return      : NULL       --- no suitable block found
               tmpNode    --- pointer a suitable free block
*****************************************************************************/
STATIC_INLINE LosMemDynNode *OsMemFindSuitableFreeBlock(VOID *pool, UINT32 allocSize)
{
    LOS_DL_LIST *listHead = (LOS_DL_LIST *)NULL;

    for (listHead = OS_MEM_HEAD(pool, allocSize); listHead != NULL;
         listHead = OS_DLNK_NEXT_HEAD(OS_MEM_HEAD_ADDR(pool), listHead)) {
        LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
        LOS_DL_LIST_FOR_EACH_ENTRY(tmpNode, listHead, LosMemDynNode, freeNodeInfo) {
            if (tmpNode->sizeAndFlag >= allocSize) {
                return tmpNode;
            }
        }
    }

    return (LosMemDynNode *)NULL;
}

/*****************************************************************************
 Function    : OsMemClearNode
 Description : clear a mem Node , set every member to NULL
 Input       : node    --- Pointer to the mem node which will be cleared up
 Output      : None
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemClearNode(LosMemDynNode *node)
{
    node->freeNodeInfo.pstPrev = (LOS_DL_LIST *)NULL;
    node->freeNodeInfo.pstNext = (LOS_DL_LIST *)NULL;
    node->preNode = (LosMemDynNode *)NULL;
}

/*****************************************************************************
 Function    : OsMemMergeNode
 Description : merge this node and pre node ,then clear this node info
 Input       : node    --- Pointer to node which will be merged
 Output      : None
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemMergeNode(LosMemDynNode *node)
{
    LosMemDynNode *nextNode = (LosMemDynNode *)NULL;

    node->preNode->sizeAndFlag += node->sizeAndFlag;
    nextNode = (LosMemDynNode *)((UINTPTR)node + node->sizeAndFlag);
    nextNode->preNode = node->preNode;
    OsMemClearNode(node);
}

/*****************************************************************************
 Function    : OsMemSpitNode
 Description : spit new node from allocNode, and merge remainder mem if necessary
 Input       : pool      --- Pointer to memory pool
               allocNode --- the source node which new node be spit from to.
                             After pick up it's node info, change to point the new node
               allocSize --- the size of new node
 Output      : allocNode --- save new node addr
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemSpitNode(VOID *pool, LosMemDynNode *allocNode, UINT32 allocSize)
{
    LosMemDynNode *newFreeNode = (LosMemDynNode *)NULL;
    LosMemDynNode *nextNode = (LosMemDynNode *)NULL;
    LOS_DL_LIST *listHead = (LOS_DL_LIST *)NULL;

    newFreeNode = (LosMemDynNode *)((UINT8 *)allocNode + allocSize);
    newFreeNode->preNode = allocNode;
    newFreeNode->sizeAndFlag = allocNode->sizeAndFlag - allocSize;
    allocNode->sizeAndFlag = allocSize;
    nextNode = OS_MEM_NEXT_NODE(newFreeNode);
    nextNode->preNode = newFreeNode;
    if (!OS_MEM_NODE_GET_USED_FLAG(nextNode->sizeAndFlag)) {
        LOS_ListDelete(&(nextNode->freeNodeInfo));
        OsMemMergeNode(nextNode);
    }

    listHead = OS_MEM_HEAD(pool, newFreeNode->sizeAndFlag);
    if (listHead == NULL) {
        PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
        return;
    }

    LOS_ListAdd(listHead, &(newFreeNode->freeNodeInfo));
}

/*****************************************************************************
 Function    : OsMemFreeNode
 Description : free the node from memory & if there are free node beside, merger them.
               at last update "listHead' which saved all free node control head
 Input       : node --- the node which need be freed
               pool --- Pointer to memory pool
 Output      : None
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemFreeNode(LosMemDynNode *node, VOID *pool)
{
    LosMemDynNode *nextNode = (LosMemDynNode *)NULL;
    LOS_DL_LIST *listHead = (LOS_DL_LIST *)NULL;

#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    poolInfo->uwPoolCurUsedSize -= OS_MEM_NODE_GET_SIZE(node->sizeAndFlag);
#endif
    if (pool == (VOID *)OS_SYS_MEM_ADDR) {
        OS_MEM_REDUCE_USED(OS_MEM_NODE_GET_SIZE(node->sizeAndFlag), OS_MEM_TASKID_GET(node));
    }

    node->sizeAndFlag = OS_MEM_NODE_GET_SIZE(node->sizeAndFlag);
    if ((node->preNode != NULL) &&
        (!OS_MEM_NODE_GET_USED_FLAG(node->preNode->sizeAndFlag))) {
        LosMemDynNode *preNode = node->preNode;
        OsMemMergeNode(node);
        nextNode = OS_MEM_NEXT_NODE(preNode);
        if (!OS_MEM_NODE_GET_USED_FLAG(nextNode->sizeAndFlag)) {
            LOS_ListDelete(&(nextNode->freeNodeInfo));
            OsMemMergeNode(nextNode);
        }

        LOS_ListDelete(&(preNode->freeNodeInfo));
        listHead = OS_MEM_HEAD(pool, preNode->sizeAndFlag);
        if (listHead == NULL) {
            PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
            return;
        }

        LOS_ListAdd(listHead, &(preNode->freeNodeInfo));
    } else {
        nextNode = OS_MEM_NEXT_NODE(node);
        if (!OS_MEM_NODE_GET_USED_FLAG(nextNode->sizeAndFlag)) {
            LOS_ListDelete(&(nextNode->freeNodeInfo));
            OsMemMergeNode(nextNode);
        }

        listHead = OS_MEM_HEAD(pool, node->sizeAndFlag);
        if (listHead == NULL) {
            PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
            return;
        }

        LOS_ListAdd(listHead, &(node->freeNodeInfo));
    }
}

STATIC_INLINE LosMemDynNode *OsMemGetNodeFromPtr(VOID *ptr)
{
    UINT32 gapSize;
    gapSize = *((UINT32 *)((UINTPTR)ptr - OS_MEM_NODE_DATA_SIZE));
    if (OS_MEM_NODE_GET_ALIGNED_FLAG(gapSize)) {
        gapSize = OS_MEM_NODE_GET_ALIGNED_GAPSIZE(gapSize);
        ptr = (VOID *)((UINTPTR)ptr - gapSize);
    }
    return (LosMemDynNode *)((UINTPTR)ptr - OS_MEM_NODE_HEAD_SIZE);
}

/*****************************************************************************
 Function    : OsMemCheckUsedNode
 Description : check the result if pointer memory node belongs to pointer memory pool
 Input       : pool --- Pointer to memory pool
               node --- the node which need be checked
 Output      : None
 Return      : LOS_OK or LOS_NOK
*****************************************************************************/
#ifdef LOS_DLNK_SAFE_CHECK
STATIC_INLINE UINT32 OsMemCheckUsedNode(VOID *pool, LosMemDynNode *node)
{
    LosMemDynNode *tmpNode = NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LosMemDynNode *end = OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);

    for (tmpNode = OS_MEM_FIRST_NODE(pool); tmpNode < end; tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if ((tmpNode == node) && OS_MEM_NODE_GET_USED_FLAG(tmpNode->sizeAndFlag)) {
            return LOS_OK;
        } else if (tmpNode > node) {
            return LOS_NOK;
        }
    }

    return LOS_NOK;
}

#elif defined(LOS_DLNK_SIMPLE_CHECK)
STATIC_INLINE UINT32 OsMemCheckUsedNode(VOID *pool, LosMemDynNode *node)
{
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LosMemDynNode *startNode = OS_MEM_FIRST_NODE(pool);
    LosMemDynNode *endNode = OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
    if (!OS_MEM_MIDDLE_ADDR_OPEN_END(startNode, node, endNode)) {
        return LOS_NOK;
    }

    if (!OS_MEM_NODE_GET_USED_FLAG(node->sizeAndFlag)) {
        return LOS_NOK;
    }

    if (!OS_MEM_MAGIC_VALID(node->freeNodeInfo.pstPrev)) {
        return LOS_NOK;
    }

    return LOS_OK;
}

#else
STATIC_INLINE BOOL OsMemIsNodeValid(const LosMemDynNode *node, const LosMemDynNode *startNode,
    const LosMemDynNode *endNode, const UINT8 *startPool, const UINT8 *endPool)
{
    if (!OS_MEM_MIDDLE_ADDR(startNode, node, endNode)) {
        return FALSE;
    }

    if (OS_MEM_NODE_GET_USED_FLAG(node->sizeAndFlag)) {
        if (!OS_MEM_MAGIC_VALID(node->freeNodeInfo.pstPrev)) {
            return FALSE;
        }
        return TRUE;
    }

    if (!OS_MEM_MIDDLE_ADDR_OPEN_END(startPool, node->freeNodeInfo.pstPrev, endPool)) {
        return FALSE;
    }

    return TRUE;
}

STATIC_INLINE UINT32 OsMemCheckUsedNode(VOID *pool, LosMemDynNode *node)
{
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LosMemDynNode *startNode = OS_MEM_FIRST_NODE(pool);
    LosMemDynNode *endNode = OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
    UINT8 *endPool = (UINT8 *)pool + poolInfo->uwPoolSize;
    const LosMemDynNode *nextNode = (const LosMemDynNode *)NULL;
    if (OsMemIsNodeValid(node, startNode, endNode, (UINT8 *)pool, endPool) != TRUE) {
        return LOS_NOK;
    }

    if (!OS_MEM_NODE_GET_USED_FLAG(node->sizeAndFlag)) {
        return LOS_NOK;
    }

    nextNode = OS_MEM_NEXT_NODE(node);
    if (OsMemIsNodeValid(nextNode, startNode, endNode, (UINT8 *)pool, endPool) != TRUE) {
        return LOS_NOK;
    }

    if (nextNode->preNode != node) {
        return LOS_NOK;
    }

    if (node != startNode) {
        if (OsMemIsNodeValid(node->preNode, startNode, endNode, (UINT8 *)pool, endPool) != TRUE) {
            return LOS_NOK;
        }

        if (OS_MEM_NEXT_NODE(node->preNode) != node) {
            return LOS_NOK;
        }
    }

    return LOS_OK;
}

#endif

/*****************************************************************************
 Function    : OsMemSetMagicNumAndTaskid
 Description : set magic & taskid
 Input       : node --- the node which will be set magic &  taskid
 Output      : None
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemSetMagicNumAndTaskid(LosMemDynNode *node)
{
    OS_MEM_SET_MAGIC(node->freeNodeInfo.pstPrev);

    /* In the process of dynamic memory initialization, direct use of uninitialized global variable which
     * initialized in task initialization. Need to exclude this scene, make the value of
     * node->freeNodeInfo.pstNext to 0xffffffff */
    if ((g_losTask.runTask != NULL) && OS_INT_INACTIVE)  {
        OS_MEM_TASKID_SET(node, g_losTask.runTask->taskID);
    }  else {
        node->freeNodeInfo.pstNext = (LOS_DL_LIST *)0xffffffff; /* If the task mode does not initialize,
                                                                 * the field is the 0xffffffff */
    }
}

STATIC_INLINE VOID OsMemIntegrityCheckErrout(LosMemDynNode *curNode, LosMemDynNode *prevNode)
{
    UINT32 taskID;
    LosTaskCB *taskCB = NULL;

    /* print the 4 UINT32 of the current memory node head */
    PRINTK("broken node head: 0x%x  0x%x  0x%x  0x%x\n",
           *(UINT32 *)curNode, *((UINT32 *)curNode + 1), *((UINT32 *)curNode + 2), *((UINT32 *)curNode + 3));

    taskID = OS_MEM_TASKID_GET(prevNode);
    do {
        if (taskID >= g_taskMaxNum) {
            LOS_Panic("Task ID %d in pre node is invalid!\n", taskID);
            break;
        }
        taskCB = OS_TCB_FROM_TID(taskID);

        if ((taskCB->taskStatus & OS_TASK_STATUS_UNUSED) ||
            (taskCB->taskEntry == NULL) ||
            (taskCB->taskName == NULL)) {
            LOS_Panic("\r\nTask ID %d in pre node is not created!\n", taskID);
            break;
        }
        LOS_Panic("cur node: 0x%x\n"
                  "pre node: 0x%x\n"
                  "pre node was allocated by task:%s\n",
                  (UINTPTR)curNode, (UINTPTR)prevNode, taskCB->taskName);
    } while (0);
}

/*****************************************************************************
 Function    : LOS_MemIntegrityCheck
 Description : memory pool integrity checking
 Input       : pool   --- Pointer to memory pool
 Output      : None
 Return      : LOS_OK --- memory pool integrate  or LOS_NOK --- memory pool impaired
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemIntegrityCheck(VOID *pool)
{
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    LosMemDynNode *prevNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    UINT8 *endPool = NULL;
    UINTPTR intSave;

    if (pool == NULL) {
        return LOS_NOK;
    }

    endPool = (UINT8 *)pool + poolInfo->uwPoolSize;

    intSave = LOS_IntLock();
    prevNode = OS_MEM_FIRST_NODE(pool);
    for (tmpNode = OS_MEM_FIRST_NODE(pool);
         tmpNode < OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
         tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if (OS_MEM_NODE_GET_USED_FLAG(tmpNode->sizeAndFlag)) {
            if (!OS_MEM_MAGIC_VALID(tmpNode->freeNodeInfo.pstPrev)) {
                PRINT_ERR("[%s], %d, memory check error!\n"
                          "memory used but magic num wrong, freeNodeInfo.pstPrev(magic num):0x%x \n",
                          __FUNCTION__, __LINE__, (UINT32)(UINTPTR)(tmpNode->freeNodeInfo.pstPrev));
                goto ERROUT;
            }
        } else { /* is free node, check free node range */
            if (!OS_MEM_MIDDLE_ADDR_OPEN_END(pool, tmpNode->freeNodeInfo.pstPrev, endPool)) {
                PRINT_ERR("[%s], %d, memory check error!\n"
                          "freeNodeInfo.pstPrev:0x%x is out of legal mem range[0x%x, 0x%x]\n",
                          __FUNCTION__, __LINE__,
                          (UINT32)(UINTPTR)(tmpNode->freeNodeInfo.pstPrev), (UINTPTR)pool, (UINTPTR)endPool);
                goto ERROUT;
            }
            if (!OS_MEM_MIDDLE_ADDR_OPEN_END(pool,
                                             (UINT32)(UINTPTR)(tmpNode->freeNodeInfo.pstNext),
                                             (UINTPTR)endPool)) {
                PRINT_ERR("[%s], %d, memory check error!\n"
                          "freeNodeInfo.pstNext:0x%x is out of legal mem range[0x%x, 0x%x]\n",
                          __FUNCTION__, __LINE__,
                          (UINT32)(UINTPTR)(tmpNode->freeNodeInfo.pstNext), (UINTPTR)pool, (UINTPTR)endPool);
                goto ERROUT;
            }
        }

        prevNode = tmpNode;
    }
    LOS_IntRestore(intSave);
    return LOS_OK;

ERROUT:
    OsMemIntegrityCheckErrout(tmpNode, prevNode);
    LOS_IntRestore(intSave);
    return LOS_NOK;
}

/*****************************************************************************
 Function    : OsMemAllocWithCheck
 Description : Allocate node from Memory pool
 Input       : pool  --- Pointer to memory pool
               size  --- Size of memory in bytes to allocate
 Output      : None
 Return      : Pointer to allocated memory
*****************************************************************************/
STATIC_INLINE VOID *OsMemAllocWithCheck(VOID *pool, UINT32 size)
{
    LosMemDynNode *allocNode = (LosMemDynNode *)NULL;
    UINT32 allocSize;
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
#endif
    if (g_mallocHook != NULL) {
        g_mallocHook();
    }

#ifdef OS_MEM_ENABLE_ALLOC_CHECK
    if (LOS_MemIntegrityCheck(pool) != LOS_OK) {
        PRINT_ERR("Memory Pool Integrity Checking Failed!\n");
    }
#endif

    allocSize = OS_MEM_ALIGN(size + OS_MEM_NODE_HEAD_SIZE, OS_MEM_ALIGN_SIZE);
    allocNode = OsMemFindSuitableFreeBlock(pool, allocSize);
    if (allocNode == NULL) {
        PRINT_ERR("--------------------------------------------------------------------------------------\n");
        OsMemInfoPrint(pool);
        PRINT_ERR("[%s] No suitable free block, require free node size: 0x%x\n", __FUNCTION__, allocSize);
        PRINT_ERR("--------------------------------------------------------------------------------------\n");
        return NULL;
    }
    if ((allocSize + OS_MEM_NODE_HEAD_SIZE + OS_MEM_ALIGN_SIZE) <= allocNode->sizeAndFlag) {
        OsMemSpitNode(pool, allocNode, allocSize);
    }
    LOS_ListDelete(&(allocNode->freeNodeInfo));
    OsMemSetMagicNumAndTaskid(allocNode);
    OS_MEM_NODE_SET_USED_FLAG(allocNode->sizeAndFlag);
    if (pool == (VOID *)OS_SYS_MEM_ADDR) {
        OS_MEM_ADD_USED(OS_MEM_NODE_GET_SIZE(allocNode->sizeAndFlag), OS_MEM_TASKID_GET(allocNode));
    }
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    poolInfo->uwPoolCurUsedSize += OS_MEM_NODE_GET_SIZE(allocNode->sizeAndFlag);
    if (poolInfo->uwPoolCurUsedSize > poolInfo->uwPoolWaterLine) {
        poolInfo->uwPoolWaterLine = poolInfo->uwPoolCurUsedSize;
    }
#endif
    return (allocNode + 1);
}

/*****************************************************************************
 Function    : OsMemReAllocSmaller
 Description : reAlloc a smaller memory node
 Input       : pool       --- Pointer to memory pool
               allocSize  --- the size of new node which will be alloced
               node       --- the node which wille be realloced
               nodeSize   --- the size of old node
 Output      : node       --- pointer to the new node after realloc
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemReAllocSmaller(VOID *pool, UINT32 allocSize, LosMemDynNode *node, UINT32 nodeSize)
{
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
#endif
    if ((allocSize + OS_MEM_NODE_HEAD_SIZE + OS_MEM_ALIGN_SIZE) <= nodeSize) {
        node->sizeAndFlag = nodeSize;
        OsMemSpitNode(pool, node, allocSize);
        OS_MEM_NODE_SET_USED_FLAG(node->sizeAndFlag);
        if (pool == (VOID *)OS_SYS_MEM_ADDR) {
            OS_MEM_REDUCE_USED(nodeSize - allocSize, OS_MEM_TASKID_GET(node));
        }
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
        poolInfo->uwPoolCurUsedSize -= (nodeSize - allocSize);
#endif
    }
}

/*****************************************************************************
 Function    : OsMemMergeNodeForReAllocBigger
 Description : reAlloc a Bigger memory node after merge node and nextNode
 Input       : pool       --- Pointer to memory pool
               allocSize  --- the size of new node which will be alloced
               node       --- the node which wille be realloced
               nodeSize   --- the size of old node
               nextNode   --- pointer next node which will be merged
 Output      : node       --- pointer to the new node after realloc
 Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsMemMergeNodeForReAllocBigger(VOID *pool, UINT32 allocSize,
    LosMemDynNode *node, UINT32 nodeSize, LosMemDynNode *nextNode)
{
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
#endif
    node->sizeAndFlag = nodeSize;
    LOS_ListDelete(&(nextNode->freeNodeInfo));
    OsMemMergeNode(nextNode);
    if ((allocSize + OS_MEM_NODE_HEAD_SIZE + OS_MEM_ALIGN_SIZE) <= node->sizeAndFlag) {
        OsMemSpitNode(pool, node, allocSize);
    }
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    poolInfo->uwPoolCurUsedSize += (node->sizeAndFlag - nodeSize);
    if (poolInfo->uwPoolCurUsedSize > poolInfo->uwPoolWaterLine) {
        poolInfo->uwPoolWaterLine = poolInfo->uwPoolCurUsedSize;
    }
#endif
    if (pool == (VOID *)OS_SYS_MEM_ADDR) {
        OS_MEM_ADD_USED(node->sizeAndFlag - nodeSize, OS_MEM_TASKID_GET(node));
    }
    OS_MEM_NODE_SET_USED_FLAG(node->sizeAndFlag);
}

STATIC_INLINE VOID *OsMemReallocMem(VOID *pool, const VOID *ptr, UINT32 size, LosMemDynNode *node)
{
    errno_t rc;
    VOID *newPtr = NULL;
    UINT32 allocSize, nodeSize;
    LosMemDynNode *nextNode = NULL;

    allocSize = OS_MEM_ALIGN(size + OS_MEM_NODE_HEAD_SIZE, OS_MEM_ALIGN_SIZE);
    nodeSize = OS_MEM_NODE_GET_SIZE(node->sizeAndFlag);
    if (nodeSize >= allocSize) {
        OsMemReAllocSmaller(pool, allocSize, node, nodeSize);
        return (VOID *)ptr;
    }

    nextNode = OS_MEM_NEXT_NODE(node);
    if ((!OS_MEM_NODE_GET_USED_FLAG(nextNode->sizeAndFlag)) &&
        ((nextNode->sizeAndFlag + nodeSize) >= allocSize)) {
        OsMemMergeNodeForReAllocBigger(pool, allocSize, node, nodeSize, nextNode);
        return (VOID *)ptr;
    }

    newPtr = OsMemAllocWithCheck(pool, size);
    if (newPtr != NULL) {
        rc = memcpy_s(newPtr, size, ptr, nodeSize - OS_MEM_NODE_HEAD_SIZE);
        if (rc != EOK) {
            PRINT_ERR("%s[%d] memcpy_s failed, error type = %d\n", __FUNCTION__, __LINE__, rc);
        }
        OsMemFreeNode(node, pool);
    }
    return newPtr;

}
/*****************************************************************************
 Function    : LOS_MemPoolSizeGet
 Description : get the memory pool's size
 Input       : pool                  --- Pointer to memory pool
 Output      : LOS_NOK & Other value --- The size of the memory pool.
 Return      : the size of the memory pool
*****************************************************************************/
UINT32 LOS_MemPoolSizeGet(const VOID *pool)
{
    if (pool == NULL) {
        return LOS_NOK;
    }
    return ((LOS_MEM_POOL_INFO *)pool)->uwPoolSize;
}

STATIC_INLINE UINT32 OsMemMulPoolInit(VOID *pool, UINT32 size)
{
    VOID *next = g_memPoolHead;
    VOID *cur = NULL;
    UINT32 poolEnd;

    while (next != NULL) {
        poolEnd = (UINTPTR)next + LOS_MemPoolSizeGet(next);
        if ((((pool <= next) && ((UINTPTR)pool + size)) > (UINTPTR)next) ||
            (((UINTPTR)pool < poolEnd) && (((UINTPTR)pool + size) >= poolEnd))) {
            PRINT_ERR("pool [0x%x, 0x%x) conflict with pool [0x%x, 0x%x)\n",
                      (UINT32)(UINTPTR)pool, (UINT32)(UINTPTR)pool + size,
                      (UINT32)(UINTPTR)next, (UINT32)(UINTPTR)next + LOS_MemPoolSizeGet(next));
            return OS_ERROR;
        }
        cur = next;
        next = ((LOS_MEM_POOL_INFO *)next)->pNextPool;
    }

    if (g_memPoolHead == NULL) {
        g_memPoolHead = pool;
    } else {
        ((LOS_MEM_POOL_INFO *)cur)->pNextPool = pool;
    }

    ((LOS_MEM_POOL_INFO *)pool)->pNextPool = NULL;
    return LOS_OK;
}
/*****************************************************************************
 Function    : LOS_MemInit
 Description : Initialize Dynamic Memory pool
 Input       : pool   --- Pointer to memory pool
               size   --- Size of memory in bytes to allocate
 Output      : None
 Return      : LOS_OK --- Ok, OS_ERROR --- Error
*****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_MemInit(VOID *pool, UINT32 size)
{
    LosMemDynNode *newNode = (LosMemDynNode *)NULL;
    LosMemDynNode *endNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)NULL;
    UINTPTR intSave;
    LOS_DL_LIST *listHead = (LOS_DL_LIST *)NULL;
#if (LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK == YES)
    UINT32 *memCount = (UINT32 *)g_memMang;
    MEM_INFO *memInfo = (MEM_INFO *)(g_memMang + sizeof(UINT32));
    UINT8 loop;
#endif

    if ((pool == NULL) || (size < OS_MEM_MIN_POOL_SIZE)) {
        return OS_ERROR;
    }

#if (LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK == YES)
    intSave = LOS_IntLock();
    for (loop = 0; loop < *memCount; loop++) {
        if (memInfo->uwStartAddr == (UINT32)(UINTPTR)pool) {
            (*memCount)--;
            break;
        }
        memInfo++;
    }
    if (*memCount < OS_SYS_MEM_NUM) {
        memInfo->uwType = MEM_MANG_MEMORY;
        memInfo->uwStartAddr = (UINT32)(UINTPTR)pool;
        memInfo->uwSize = size;
        (*memCount)++;
    }
    LOS_IntRestore(intSave);
#endif
    intSave = LOS_IntLock();

    poolInfo = (LOS_MEM_POOL_INFO *)pool;
    poolInfo->pPoolAddr = pool;
    poolInfo->uwPoolSize = size;
    OS_DLNK_INIT_HEAD(OS_MEM_HEAD_ADDR(pool));
    newNode = OS_MEM_FIRST_NODE(pool);
    newNode->sizeAndFlag = ((size - ((UINTPTR)newNode - (UINTPTR)pool)) - OS_MEM_NODE_HEAD_SIZE);
    newNode->preNode = (LosMemDynNode *)NULL;
    listHead = OS_MEM_HEAD(pool, newNode->sizeAndFlag);
    if (listHead == NULL) {
        LOS_IntRestore(intSave);
        return OS_ERROR;
    }

    LOS_ListTailInsert(listHead, &(newNode->freeNodeInfo));
    endNode = (LosMemDynNode *)OS_MEM_END_NODE(pool, size);
    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)memset_s(endNode, sizeof(*endNode), 0, sizeof(*endNode));
    endNode->preNode = newNode;
    endNode->sizeAndFlag = OS_MEM_NODE_HEAD_SIZE;
    OS_MEM_NODE_SET_USED_FLAG(endNode->sizeAndFlag);
    OsMemSetMagicNumAndTaskid(endNode);
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    poolInfo->uwPoolCurUsedSize = sizeof(LOS_MEM_POOL_INFO) +
        OS_MULTI_DLNK_HEAD_SIZE + OS_MEM_NODE_GET_SIZE(endNode->sizeAndFlag);
    poolInfo->uwPoolWaterLine = poolInfo->uwPoolCurUsedSize;
#endif

#if (LOSCFG_MEM_MUL_POOL == YES)
    UINT32 ret = OsMemMulPoolInit(pool, size);
    if (ret != LOS_OK) {
        LOS_IntRestore(intSave);
        return ret;
    }
#endif

    LOS_IntRestore(intSave);

    return LOS_OK;
}

#if (LOSCFG_MEM_MUL_POOL == YES)
LITE_OS_SEC_TEXT_INIT UINT32 LOS_MemDeInit(const VOID *pool)
{
    UINTPTR intSave;
    UINTPTR ret = LOS_NOK;
    VOID *next = NULL;
    VOID *cur = NULL;

    intSave = LOS_IntLock();
    do {
        if (pool == NULL) {
            break;
        }

        if (pool == g_memPoolHead) {
            g_memPoolHead = ((LOS_MEM_POOL_INFO *)g_memPoolHead)->pNextPool;
            ret = LOS_OK;
            break;
        }

        cur = g_memPoolHead;
        next = g_memPoolHead;

        while (next != NULL) {
            if (pool == next) {
                ((LOS_MEM_POOL_INFO *)cur)->pNextPool = ((LOS_MEM_POOL_INFO *)next)->pNextPool;
                ret = LOS_OK;
                break;
            }
            cur = next;
            next = ((LOS_MEM_POOL_INFO *)next)->pNextPool;
        }
    } while (0);

    LOS_IntRestore(intSave);
    return ret;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_MemPoolList(VOID)
{
    VOID *next = g_memPoolHead;
    UINT32 index = 0;
    while (next != NULL) {
        PRINTK("pool%u :\n", index);
        index++;
        OsMemInfoPrint(next);
        next = ((LOS_MEM_POOL_INFO *)next)->pNextPool;
    }
    return index;
}
#endif

#ifdef LOS_MEM_LEAK_CHECK
LITE_OS_SEC_TEXT VOID LOS_CheckMaxcount(VOID)
{
    if (g_memCheckFlag == 1) {
        PRINTK("\nIt's checking the maxcount now, please waiting!\n");
        return;
    }
    PRINTK("\nthe max malloc count :%d\nplease set the CHECK_MAXCOUNT bigger than %d!\n",
        g_memPeakCount, g_memPeakCount);
}

LITE_OS_SEC_TEXT VOID LOS_MemLeakCheckStart(VOID)
{
    UINT32 ret;
    UINTPTR intSave;
    errno_t rc;

    intSave = LOS_IntLock();
    rc = memset_s(g_checkInfo, CHECK_MAXCOUNT, 0, MEM_CHECK_MAX_SIZE);
    if (rc != EOK) {
        PRINT_ERR("%s[%d] memset_s failed, error type = %d\n", __FUNCTION__, __LINE__, rc);
        LOS_IntRestore(intSave);
        return;
    }
    ret = LOS_MemboxInit(g_checkInfo, MEM_CHECK_MAX_SIZE, MEM_CHECK_SIZE);
    if (ret != LOS_OK) {
        PRINT_ERR("\nLOS_MemboxInit failed!\n");
        LOS_IntRestore(intSave);
        return;
    }
    g_memCount = 0;
    g_memPeakCount = 0;
    g_memCheckFlag = 1;
    LOS_IntRestore(intSave);
}

INLINE VOID OsMemCheckinfoCreate(VOID *ptr, UINT32 size)
{
    UINT32 fp;
    UINT32 i = 0;
    UINT32 tmpFp;
    UINT32 backLR;
    MEM_CHECK_INFO *check = NULL;
    UINTPTR intSave;

    fp = Get_Fp();
    intSave = LOS_IntLock();
    g_memCount++;
    if (g_memCount > g_memPeakCount) {
        g_memPeakCount = g_memCount;
    }
    LOS_IntRestore(intSave);

    check = (MEM_CHECK_INFO *)LOS_MemboxAlloc(g_checkInfo);
    if (check == NULL) {
        PRINTK("memboxalloc is failure:%s[%d]\r\n", __FUNCTION__, __LINE__);
        return;
    }

    (void)memset_s(check, sizeof(MEM_CHECK_INFO), 0, sizeof(MEM_CHECK_INFO));
    check->pPoolAddr = ptr;
    while ((fp > OS_SYS_FUNC_ADDR_START) && (fp < OS_SYS_FUNC_ADDR_END)) {
        tmpFp = fp;
        backLR = *((UINT32 *)(fp));
        fp = *((UINT32 *)(tmpFp - OS_MEM_NODE_DATA_SIZE));
        if (i > 0) {
            check->fp[i - 1] = backLR;
        }
        i++;
        if (i == (OS_MEM_NODE_DATA_SIZE + 1)) {
            break;
        }
    }
    check->flag = 1;
    check->uwAddrSize = size;
    return;
}

INLINE VOID OsMemCheckinfoDel(VOID *nodePtr)
{
    UINT32 i;
    UINT32 ret;
    UINTPTR intSave;
    LOS_MEMBOX_INFO *boxInfo = (LOS_MEMBOX_INFO *)g_checkInfo;
    LOS_MEMBOX_NODE *node = (LOS_MEMBOX_NODE *)NULL;

    intSave = LOS_IntLock();
    g_memCount--;
    node = (LOS_MEMBOX_NODE *)(boxInfo + 1);
    for (i = 0; i < boxInfo->uwBlkNum; ++i, node = OS_MEMBOX_NEXT(node, boxInfo->uwBlkSize)) {
        if (*(UINT32 *)((UINTPTR)node + OS_CHECK_FLAG) != 1) {
            continue;
        }

        if ((UINTPTR)nodePtr == *((UINT32 *)node)) {
            ret = LOS_MemboxFree(g_checkInfo, node);
            if (ret != LOS_OK) {
                PRINTK("free membox failed!\n");
            }
            *(UINT32 *)((UINTPTR)node + OS_CHECK_FLAG) = 0;
            LOS_IntRestore(intSave);
            return;
        }
    }
    LOS_IntRestore(intSave);
}

LITE_OS_SEC_TEXT VOID LOS_MemLeakCheckEnd(VOID)
{
    UINTPTR intSave;

    intSave = LOS_IntLock();
    g_memCheckFlag = 0;
    LOS_IntRestore(intSave);
}

LITE_OS_SEC_TEXT VOID LOS_MemLeakCheckShow(VOID)
{
    UINT32 i;
    UINT32 j;
    UINTPTR intSave;
    LOS_MEMBOX_INFO *boxInfo = (LOS_MEMBOX_INFO *)g_checkInfo;
    LOS_MEMBOX_NODE *node = (LOS_MEMBOX_NODE *)NULL;

    intSave = LOS_IntLock();

    if (g_memCheckFlag == 1) {
        PRINTK("\nIt's checking mem used now, please waiting!\n");
        LOS_IntRestore(intSave);
        return;
    }

    PRINTK("\n\n        **********************all mem used list**********************\r\n");
    PRINTK(" ID  lr0          lr1          lr2          lr3          MemSize      MemAddr\n");
    PRINTK("---------------------------------------------------------------------------------\n");
    node = (LOS_MEMBOX_NODE *)(boxInfo + 1);
    for (i = 0, j = 0; i < boxInfo->uwBlkNum; ++i, node = OS_MEMBOX_NEXT(node, boxInfo->uwBlkSize)) {
        if ((*(UINT32 *)((UINTPTR)node + OS_CHECK_FLAG)) == 1) {
            PRINTK(" %-3d 0x%-11x0x%-11x0x%-11x0x%-11x0x%-11x0x%-11x\n", j,
                   *(UINT32 *)((UINTPTR)node + OS_CHECK_FP0), *(UINT32 *)((UINTPTR)node + OS_CHECK_FP1),
                   *(UINT32 *)((UINTPTR)node + OS_CHECK_FP2), *(UINT32 *)((UINTPTR)node + OS_CHECK_FP3),
                   *(UINT32 *)((UINTPTR)node + OS_ADDR_SIZE), *(UINT32 *)(UINTPTR)node);
            j++;
        }
    }
    LOS_IntRestore(intSave);
    if (j == 0) {
        PRINTK("************************no mem leak!!!************************\n");
        return;
    }
    PRINTK("---------------------------------------------------------------------------------\n");
}

#endif

/*****************************************************************************
 Function    : LOS_MemAlloc
 Description : Allocate node from Memory pool
 Input       : pool    --- Pointer to memory pool
               size    --- Size of memory in bytes to allocate
 Output      : None
 Return      : Pointer to allocated memory node
*****************************************************************************/
LITE_OS_SEC_TEXT VOID *LOS_MemAlloc(VOID *pool, UINT32 size)
{
    VOID *ptr = NULL;
    UINTPTR intSave = LOS_IntLock();

    do {
        if ((pool == NULL) || (size == 0)) {
            break;
        }

        if (OS_MEM_NODE_GET_USED_FLAG(size)) {
            break;
        }

        ptr = OsMemAllocWithCheck(pool, size);

#ifdef LOS_MEM_LEAK_CHECK
        if (g_memCheckFlag == 1) {
            OsMemCheckinfoCreate(ptr, size);
        }
#endif
    } while (0);

    LOS_IntRestore(intSave);
    return ptr;
}

/*****************************************************************************
 Function    : LOS_MemAllocAlign
 Description : align size then allocate node from Memory pool
 Input       : pool     --- Pointer to memory pool
               size     --- Size of memory in bytes to allocate
               boundary --- align form
 Output      : None
 Return      : Pointer to allocated memory node
*****************************************************************************/
LITE_OS_SEC_TEXT VOID *LOS_MemAllocAlign(VOID *pool, UINT32 size, UINT32 boundary)
{
    UINT32 useSize;
    UINT32 gapSize;
    VOID *ptr = NULL;
    VOID *alignedPtr = NULL;
    UINTPTR intSave = LOS_IntLock();

    do {
        if ((pool == NULL) || (size == 0) || (boundary < sizeof(VOID *)) || !IS_ALIGNED(boundary)) {
            break;
        }

        useSize = size + boundary + 4; /* 4bytes stores offset between alignedPtr and ptr */

        if ((useSize < size) || OS_MEM_NODE_GET_USED_FLAG(useSize)) {
            break;
        }

        ptr = OsMemAllocWithCheck(pool, useSize);

        alignedPtr = (VOID *)(UINTPTR)OS_MEM_ALIGN(ptr, boundary);

        if (ptr == alignedPtr) {
            break;
        }

        gapSize = (UINTPTR)alignedPtr - (UINTPTR)ptr; /* store gapSize in address (ptr -4),
                                                         it will be checked while free */
        OS_MEM_NODE_SET_ALIGNED_FLAG(gapSize);
        *((UINT32 *)((UINTPTR)alignedPtr - OS_MEM_NODE_DATA_SIZE)) = gapSize;

        ptr = alignedPtr;

#ifdef LOS_MEM_LEAK_CHECK
        if (g_memCheckFlag == 1) {
            OsMemCheckinfoCreate(ptr, size);
        }
#endif
    } while (0);

    LOS_IntRestore(intSave);

    return ptr;
}

/*****************************************************************************
 Function    : LOS_MemFree
 Description : free the node from memory & if there are free node beside, merger them.
               at last update "listHead" which saved all free node control head
 Input       : pool   --- Pointer to memory pool
               ptr    --- the node which need be freed
 Output      : None
 Return      : LOS_OK --- OK,  LOS_NOK --- failed
*****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_MemFree(VOID *pool, VOID *ptr)
{
    UINT32 ret = LOS_NOK;
    UINTPTR intSave = LOS_IntLock();
#ifdef LOS_MEM_LEAK_CHECK
    VOID *p = ptr;
#endif
    do {
        LosMemDynNode *node = (LosMemDynNode *)NULL;

        if ((pool == NULL) || (ptr == NULL)) {
            break;
        }

        node = OsMemGetNodeFromPtr(ptr);

        ret = OsMemCheckUsedNode(pool, node);
        if (ret == LOS_OK) {
            OsMemFreeNode(node, pool);
#ifdef LOS_MEM_LEAK_CHECK
            if (g_memCheckFlag == 1) {
                OsMemCheckinfoDel(p);
            }
#endif
        }

    } while (0);

    LOS_IntRestore(intSave);
    return ret;
}

/*****************************************************************************
 Function    : LOS_MemRealloc
 Description : reAlloc memory node
 Input       : pool    --- Pointer to memory pool
               ptr     --- pointer to memory node which will be realloced
               size    --- the size of new node
 Output      : None
 Return      : Pointer to allocated memory
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID *LOS_MemRealloc(VOID *pool, VOID *ptr, UINT32 size)
{
    VOID *newPtr = NULL;

    if ((INT32)size < 0) {
        return NULL;
    }

    UINTPTR intSave = LOS_IntLock();

    do {
        LosMemDynNode *node = (LosMemDynNode *)NULL;
        UINT32 ret;

        if (size == 0) {
            (VOID)LOS_MemFree((VOID *)pool, (VOID *)ptr);
            break;
        }

        if (ptr == NULL) {
            newPtr = LOS_MemAlloc((VOID *)pool, (UINT32)size);
            if (newPtr == NULL) {
                break;
            }
            (VOID)memset_s(newPtr, (UINT32)size, 0, (UINT32)size);
            break;
        }

        node = OsMemGetNodeFromPtr(ptr);

        ret = OsMemCheckUsedNode(pool, node);
        if (ret != LOS_OK) {
            break;
        }
        newPtr = OsMemReallocMem(pool, ptr, size, node);

    } while (0);

    LOS_IntRestore(intSave);
    return newPtr;
}

/*****************************************************************************
 Function    : LOS_MemTotalUsedGet
 Description : figure the pointer memory pool for it's total mem used
 Input       : pool    --- Pointer to memory pool
 Output      : None
 Return      : the size of the pool has been used
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemTotalUsedGet(VOID *pool)
{
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    UINT32 memUsed = 0;
    UINTPTR intSave;

    if (pool == NULL) {
        return LOS_NOK;
    }

    intSave = LOS_IntLock();

    for (tmpNode = OS_MEM_FIRST_NODE(pool); tmpNode <= OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
         tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if (OS_MEM_NODE_GET_USED_FLAG(tmpNode->sizeAndFlag)) {
            memUsed += OS_MEM_NODE_GET_SIZE(tmpNode->sizeAndFlag);
        }
    }

    LOS_IntRestore(intSave);

    return memUsed;
}

/*****************************************************************************
 Function    : LOS_MemUsedBlksGet
 Description : get the number of used node
 Input       : pool    --- Pointer to memory pool
 Output      : None
 Return      : the number of used node
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemUsedBlksGet(VOID *pool)
{
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    UINT32 blkNums = 0;
    UINTPTR intSave;

    if (pool == NULL) {
        return LOS_NOK;
    }

    intSave = LOS_IntLock();

    for (tmpNode = OS_MEM_FIRST_NODE(pool); tmpNode <= OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
         tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if (OS_MEM_NODE_GET_USED_FLAG(tmpNode->sizeAndFlag)) {
            blkNums++;
        }
    }

    LOS_IntRestore(intSave);

    return blkNums;
}

/*****************************************************************************
 Function    : LOS_MemTaskIdGet
 Description : get a memory node's taskID if pointer node is "used node"
 Input       : ptr    --- pointer to aim node
 Output      : None
 Return      : taskID --- Ok or OS_INVALID --- pointer node is illegal or free node
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemTaskIdGet(const VOID *ptr)
{
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)OS_SYS_MEM_ADDR;
    UINTPTR intSave;

    if ((ptr == NULL) ||
        (ptr < (VOID *)OS_MEM_FIRST_NODE(OS_SYS_MEM_ADDR)) ||
        (ptr > (VOID *)OS_MEM_END_NODE(OS_SYS_MEM_ADDR, poolInfo->uwPoolSize))) {
        PRINT_ERR("input ptr 0x%x is out of system memory range[0x%x, 0x%x]\n",
                  (UINTPTR)ptr,
                  (UINTPTR)(OS_MEM_FIRST_NODE(OS_SYS_MEM_ADDR)),
                  (UINTPTR)(OS_MEM_END_NODE(OS_SYS_MEM_ADDR, poolInfo->uwPoolSize)));
        return OS_INVALID;
    }

    intSave = LOS_IntLock();

    for (tmpNode = OS_MEM_FIRST_NODE(OS_SYS_MEM_ADDR);
         tmpNode <= OS_MEM_END_NODE(OS_SYS_MEM_ADDR, poolInfo->uwPoolSize); tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if ((UINTPTR)ptr < (UINTPTR)tmpNode) {
            if (OS_MEM_NODE_GET_USED_FLAG(tmpNode->preNode->sizeAndFlag)) {
                UINTPTR tmpValue = (UINTPTR)(tmpNode->preNode->freeNodeInfo.pstNext);
                LOS_IntRestore(intSave);
                return tmpValue;
            } else {
                LOS_IntRestore(intSave);
                PRINT_ERR("input ptr 0x%x is belong to a free mem node\n", (UINTPTR)ptr);
                return OS_INVALID;
            }
        }
    }

    LOS_IntRestore(intSave);
    return OS_INVALID;
}

/*****************************************************************************
 Function    : LOS_MemFreeBlksGet
 Description : get the number of free node
 Input       : pool    --- Pointer to memory pool
 Output      : None
 Return      : the number of free node
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemFreeBlksGet(VOID *pool)
{
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    UINT32 blkNum = 0;
    UINTPTR intSave;

    if (pool == NULL) {
        return LOS_NOK;
    }

    intSave = LOS_IntLock();

    for (tmpNode = OS_MEM_FIRST_NODE(pool); tmpNode <= OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
         tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if (!OS_MEM_NODE_GET_USED_FLAG(tmpNode->sizeAndFlag)) {
            blkNum++;
        }
    }

    LOS_IntRestore(intSave);

    return blkNum;
}

/*****************************************************************************
 Function    : LOS_MemLastUsedGet
 Description : get the address of last used node(except end node)
 Input       : pool    --- Pointer to memory pool
 Output      : None
 Return      : address of last node offset sizeof(LosMemDynNode), if last node is freeNode
               address of the end node, if last node is usedNode
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemLastUsedGet(VOID *pool)
{
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LosMemDynNode *node = NULL;

    if (pool == NULL) {
        return LOS_NOK;
    }

    node = OS_MEM_END_NODE(pool, poolInfo->uwPoolSize)->preNode;

    if (OS_MEM_NODE_GET_USED_FLAG(node->sizeAndFlag)) {
        return (UINTPTR)node + OS_MEM_NODE_GET_SIZE(node->sizeAndFlag) + sizeof(LosMemDynNode);
    } else {
        return (UINTPTR)node + sizeof(LosMemDynNode);
    }
}

/*****************************************************************************
 Function    : OsMemResetEndNode
 Description : reset "end node"
 Input       : None
 Output      : endNode --- pointer to "end node"
 Return      : the number of free node
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID OsMemResetEndNode(UINT32 preAddr)
{
    LosMemDynNode *endNode = (LosMemDynNode *)OS_MEM_END_NODE(OS_SYS_MEM_ADDR, OS_SYS_MEM_SIZE);
    endNode->sizeAndFlag = OS_MEM_NODE_HEAD_SIZE;
    if (preAddr != (UINT32)NULL) {
        endNode->preNode = (LosMemDynNode *)(UINTPTR)(preAddr - sizeof(LosMemDynNode));
    }
    OS_MEM_NODE_SET_USED_FLAG(endNode->sizeAndFlag);
    OsMemSetMagicNumAndTaskid(endNode);
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemInfoGet(VOID *pool, LOS_MEM_STATUS *status)
{
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    UINT32 totalUsedSize = 0;
    UINT32 totalFreeSize = 0;
    UINT32 maxFreeNodeSize = 0;
    UINT32 usedNodeNum = 0;
    UINT32 freeNodeNum = 0;
    UINTPTR intSave;

    if ((poolInfo == NULL) || ((UINTPTR)pool != (UINTPTR)poolInfo->pPoolAddr)) {
        PRINT_ERR("wrong mem pool addr: 0x%x, line:%d\n", (UINTPTR)poolInfo, __LINE__);
        return LOS_NOK;
    }

    if (status == NULL) {
        PRINT_ERR("wrong status addr: 0x%x, line:%d\n", (UINTPTR)status, __LINE__);
        return LOS_NOK;
    }

    tmpNode = (LosMemDynNode *)OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
    tmpNode = (LosMemDynNode *)(UINTPTR)OS_MEM_ALIGN(tmpNode, OS_MEM_ALIGN_SIZE);

    if (!OS_MEM_MAGIC_VALID(tmpNode->freeNodeInfo.pstPrev)) {
        PRINT_ERR("wrong mem pool addr: 0x%x, line:%d\n", (UINTPTR)poolInfo, __LINE__);
        return LOS_NOK;
    }

    intSave = LOS_IntLock();

    for (tmpNode = OS_MEM_FIRST_NODE(pool); tmpNode <= OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
         tmpNode = OS_MEM_NEXT_NODE(tmpNode)) {
        if (!OS_MEM_NODE_GET_USED_FLAG(tmpNode->sizeAndFlag)) {
            ++freeNodeNum;
            totalFreeSize += OS_MEM_NODE_GET_SIZE(tmpNode->sizeAndFlag);
            if (maxFreeNodeSize < OS_MEM_NODE_GET_SIZE(tmpNode->sizeAndFlag)) {
                maxFreeNodeSize = OS_MEM_NODE_GET_SIZE(tmpNode->sizeAndFlag);
            }
        } else {
            ++usedNodeNum;
            totalUsedSize += OS_MEM_NODE_GET_SIZE(tmpNode->sizeAndFlag);
        }
    }

    LOS_IntRestore(intSave);

    status->usedSize = totalUsedSize;
    status->freeSize = totalFreeSize;
    status->totalSize = maxFreeNodeSize;
    status->allocCount = usedNodeNum;
    status->freeCount = freeNodeNum;
#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    status->uwUsageWaterLine = poolInfo->uwPoolWaterLine;
#endif
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR VOID OsMemInfoPrint(VOID *pool)
{
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LOS_MEM_STATUS status = {0};

    if (LOS_NOK == LOS_MemInfoGet(pool, &status)) {
        return;
    }

#if defined(OS_MEM_WATERLINE) && (OS_MEM_WATERLINE == YES)
    PRINTK("pool addr    pool size    used size     free size"
           "    max free node size   used node num     free node num      UsageWaterLine\n"
           "---------    --------     -------       --------"
           "     --------------       -------------      ------------      ------------\n"
           "0x%-8x   0x%-8x   0x%-8x    0x%-8x   0x%-16x   0x%-13x    0x%-13x    0x%-13x\n",
           poolInfo->pPoolAddr, poolInfo->uwPoolSize, status.usedSize, status.freeSize,
           status.totalSize, status.allocCount, status.freeCount, status.uwUsageWaterLine);

#else
    PRINTK("pool addr    pool size    used size     free size"
           "    max free node size   used node num     free node num\n"
           "---------    --------     -------       --------"
           "     --------------       -------------      ------------\n"
           "0x%-8x   0x%-8x   0x%-8x    0x%-8x   0x%-16x   0x%-13x    0x%-13x\n",
           (UINT32)(UINTPTR)(poolInfo->pPoolAddr), poolInfo->uwPoolSize, status.usedSize, status.freeSize,
           status.totalSize, status.allocCount, status.freeCount);
#endif
    return;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemFreeNodeShow(VOID *pool)
{
    LOS_DL_LIST *listHead = (LOS_DL_LIST *)NULL;
    LosMultipleDlinkHead *headAddr = (LosMultipleDlinkHead *)((UINTPTR)pool + sizeof(LOS_MEM_POOL_INFO));
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    LosMemDynNode *tmpNode = (LosMemDynNode *)NULL;
    UINT32 count, idx;
    UINT32 countNum[OS_MEM_NODE_COUNT_NUM] = {0};
    UINTPTR intSave;
    INT32 i, j;

    if ((poolInfo == NULL) || ((UINTPTR)pool != (UINTPTR)poolInfo->pPoolAddr)) {
        PRINT_ERR("wrong mem pool addr: 0x%x, line:%d\n", (UINTPTR)poolInfo, __LINE__);
        return LOS_NOK;
    }

    tmpNode = (LosMemDynNode *)OS_MEM_END_NODE(pool, poolInfo->uwPoolSize);
    tmpNode = (LosMemDynNode *)(UINTPTR)OS_MEM_ALIGN(tmpNode, OS_MEM_ALIGN_SIZE);

    if (!OS_MEM_MAGIC_VALID(tmpNode->freeNodeInfo.pstPrev)) {
        PRINT_ERR("wrong mem pool addr: 0x%x\n, line:%d", (UINTPTR)poolInfo, __LINE__);
        return LOS_NOK;
    }
    PRINTK("\n   ************************ left free node number**********************\n    block size:  ");
    intSave = LOS_IntLock();

    for (idx = 0, j = 0; idx <= (OS_MAX_MULTI_DLNK_LOG2 - OS_MIN_MULTI_DLNK_LOG2); idx++, j++) {
        for (count = 0, listHead = headAddr->listHead[idx].pstNext; listHead != &(headAddr->listHead[idx]);
                listHead = listHead->pstNext) {
            ++count;
        }
        PRINTK("2^%-5d", idx + OS_MEM_NODE_DATA_SIZE);
        if ((idx == 0) || ((((idx + 1) % OS_MEM_NODE_COUNT_NUM) != 0) && (idx != OS_MULTI_DLNK_SIZE))) {
            goto NEXT;
        }
        PRINTK("\n    node number:");
        for (i = 0; i < OS_MEM_NODE_COUNT_NUM; i++) {
            PRINTK("  %-5u", countNum[i]);
            if ((i == OS_MEM_NODE_NUM) && (idx == (OS_MAX_MULTI_DLNK_LOG2 - OS_MIN_MULTI_DLNK_LOG2))) {
                break;
            }
        }
        if (idx != (OS_MAX_MULTI_DLNK_LOG2 - OS_MIN_MULTI_DLNK_LOG2)) {
            PRINTK("\n\n    block size:  ");
        }
NEXT:
        j = idx % OS_MEM_NODE_COUNT_NUM;
        countNum[j] = count;
    }
    LOS_IntRestore(intSave);
    PRINTK("\n   ********************************************************************\n\n");

    return LOS_OK;
}

#ifdef OS_MEM_CHECK_DEBUG

/*****************************************************************************
  Function   : LOS_MemNodeSizeCheck
  Description: get a pNode's(ptr) size ,include total size and available size
  Input      : pool      --- which pool doesn't your ptr belong to
               ptr       --- point to source node
  Output     : totalSize --- save total size
               availSize --- save availabe size
  Return     : errorID or LOS_OK
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemNodeSizeCheck(VOID *pool, VOID *ptr, UINT32 *totalSize, UINT32 *availSize)
{
    VOID *head = NULL;
    LOS_MEM_POOL_INFO *poolInfo = (LOS_MEM_POOL_INFO *)pool;
    UINT8 *endPool = NULL;

    if (g_checkMemLevel == LOS_MEM_CHECK_LEVEL_DISABLE) {
        return OS_ERRNO_MEMCHECK_DISABLED;
    }

    if ((pool == NULL) || (ptr == NULL)) {
        return OS_ERRNO_MEMCHECK_PARA_NULL;
    }

    endPool = (UINT8 *)pool + poolInfo->uwPoolSize;
    if (!(OS_MEM_MIDDLE_ADDR_OPEN_END(pool, (UINT8 *)ptr, endPool))) {
        return OS_ERRNO_MEMCHECK_OUTSIDE;
    }

    if (g_checkMemLevel == LOS_MEM_CHECK_LEVEL_HIGH) {
        head = OsMemFindNodeCtrl(ptr);
        if ((head == NULL) || ((((LosMemDynNode *)head)->sizeAndFlag & (~OS_MEM_NODE_USED_FLAG)) <
            ((UINTPTR)ptr - (UINTPTR)head))) {
            return OS_ERRNO_MEMCHECK_NO_HEAD;
        }
        *totalSize = (((LosMemDynNode *)head)->sizeAndFlag - sizeof(LosMemDynNode)) & (~OS_MEM_NODE_USED_FLAG);
        *availSize = (((LosMemDynNode *)head)->sizeAndFlag - ((UINTPTR)ptr - (UINTPTR)head)) &
            (~OS_MEM_NODE_USED_FLAG);
        return LOS_OK;
    }
    if (g_checkMemLevel == LOS_MEM_CHECK_LEVEL_LOW) {
        if (ptr != (VOID *)OS_MEM_ALIGN(ptr, OS_MEM_ALIGN_SIZE)) {
            return OS_ERRNO_MEMCHECK_NO_HEAD;
        }
        head = (VOID *)((UINTPTR)ptr - sizeof(LosMemDynNode));
        if (OS_MEM_MAGIC_VALID(((LosMemDynNode *)head)->freeNodeInfo.pstPrev)) {
            *totalSize = (((LosMemDynNode *)head)->sizeAndFlag - sizeof(LosMemDynNode)) & (~OS_MEM_NODE_USED_FLAG);
            *availSize = (((LosMemDynNode *)head)->sizeAndFlag - sizeof(LosMemDynNode)) & (~OS_MEM_NODE_USED_FLAG);
            return LOS_OK;
        } else {
            return OS_ERRNO_MEMCHECK_NO_HEAD;
        }
    }

    return OS_ERRNO_MEMCHECK_WRONG_LEVEL;
}

/*****************************************************************************
Function     : OsMemFindNodeCtrl
Description  : get a pool's memCtrl
Input        : headPtr --- point to source ptr
Output       : None
Return       : search forward for headPtr's memCtrl or "NULL"
@attention   : this func couldn't ensure the return memCtrl belongs to ptr
               it just find forward the most nearly one
*******************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID *OsMemFindNodeCtrl(VOID *headPtr)
{
    UINT8 *head = (UINT8 *)headPtr;

    if (headPtr == NULL) {
        return NULL;
    }

    head = (UINT8 *)OS_MEM_ALIGN((VOID *)head, OS_MEM_ALIGN_SIZE);
    while (!OS_MEM_MAGIC_VALID(((LosMemDynNode *)head)->freeNodeInfo.pstPrev)) {
        head -= OS_MEM_NODE_DATA_SIZE;
    }
    return head;
}

/*****************************************************************************
 Function    : LOS_MemCheckLevelSet
 Description : setting g_checkMemLevel which decide the manner of memcheck
 Input       : level                         --- waht level want to set
 Output      : None
 Return      : LOS_OK                        --- setting succeed
               OS_ERRNO_MEMCHECK_WRONG_LEVEL --- setting failed due to illegal parameter
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MemCheckLevelSet(UINT8 level)
{
    if (level == LOS_MEM_CHECK_LEVEL_LOW) {
        PRINTK("%s: LOS_MEM_CHECK_LEVEL_LOW \n", __FUNCTION__);
    } else if (level == LOS_MEM_CHECK_LEVEL_HIGH) {
        PRINTK("%s: LOS_MEM_CHECK_LEVEL_HIGH \n", __FUNCTION__);
    } else if (level == LOS_MEM_CHECK_LEVEL_DISABLE) {
        PRINTK("%s: LOS_MEM_CHECK_LEVEL_DISABLE \n", __FUNCTION__);
    } else {
        PRINTK("%s: wrong para, setting failed !! \n", __FUNCTION__);
        return OS_ERRNO_MEMCHECK_WRONG_LEVEL;
    }
    g_checkMemLevel = level;
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT8 LOS_MemCheckLevelGet(VOID)
{
    return g_checkMemLevel;
}

#endif /* OS_MEM_CHECK_DEBUG */

UINT32 OsMemSysNodeCheck(VOID *dst, VOID *src, UINT32 length, UINT8 pos)
{
#ifdef OS_MEM_CHECK_DEBUG
    UINT32 ret;
    UINT32 totalSize = 0;
    UINT32 availSize = 0;

    if (pos == 0) { /* if this func was called by memset */
        ret = LOS_MemNodeSizeCheck(m_aucSysMem0, dst, &totalSize, &availSize);
        if ((ret == LOS_OK) && (length > availSize)) {
            PRINT_ERR("---------------------------------------------\n");
            PRINT_ERR("memset: dst inode availSize is not enough"
                      " availSize = 0x%x length = 0x%x\n",
                      availSize, length);
            OsBackTrace();
            PRINT_ERR("---------------------------------------------\n");
            return LOS_NOK;
        }
    } else if (pos == 1) { /* if this func was called by memcpy */
        ret = LOS_MemNodeSizeCheck(m_aucSysMem0, dst, &totalSize, &availSize);
        if ((ret == LOS_OK) && (length > availSize)) {
            PRINT_ERR("---------------------------------------------\n");
            PRINT_ERR("memcpy: dst inode availSize is not enough availSize = 0x%x length = 0x%x\n",
                      availSize, length);
            OsBackTrace();
            PRINT_ERR("---------------------------------------------\n");
            return LOS_NOK;
        }
        ret = LOS_MemNodeSizeCheck(m_aucSysMem0, src, &totalSize, &availSize);
        if ((ret == LOS_OK) && (length > availSize)) {
            PRINT_ERR("---------------------------------------------\n");
            PRINT_ERR("memcpy: src inode availSize is not enough availSize = 0x%x length = 0x%x\n",
                      availSize, length);
            OsBackTrace();
            PRINT_ERR("---------------------------------------------\n");
            return LOS_NOK;
        }
    }
#endif
    return LOS_OK;
}

#ifdef LOSCFG_MEM_MUL_MODULE
INLINE UINT32 OsMemModCheck(UINT32 module)
{
    if (module > MEM_MODULE_MAX) {
        PRINT_ERR("error module ID input!\n");
        return LOS_NOK;
    }
    return LOS_OK;
}

INLINE VOID *OsMemPtrToNode(VOID *ptr)
{
    UINT32 gapSize;
    LosMemDynNode *node = NULL;
    gapSize = *((UINT32 *)((UINTPTR)ptr - OS_MEM_NODE_DATA_SIZE));
    if (OS_MEM_NODE_GET_ALIGNED_FLAG(gapSize)) {
        gapSize = OS_MEM_NODE_GET_ALIGNED_GAPSIZE(gapSize);
        ptr = (VOID *)((UINTPTR)ptr - gapSize);
    }

    return (VOID *)((UINTPTR)ptr - OS_MEM_NODE_HEAD_SIZE);
}

INLINE UINT32 OsMemNodeSizeGet(VOID *ptr)
{
    LosMemDynNode *node;
    node = (LosMemDynNode *)OsMemPtrToNode(ptr);

    return ((node->sizeAndFlag) & (~OS_MEM_NODE_USED_FLAG));
}

VOID *LOS_MemMalloc(VOID *pool, UINT32 size, UINT32 module)
{
    UINTPTR intSave;
    VOID *ptr = NULL;
    if (OsMemModCheck(module) == LOS_NOK) {
        return NULL;
    }
    ptr = LOS_MemAlloc(pool, size);
    if (ptr != NULL) {
        intSave = LOS_IntLock();
        g_memInfo[module] += OsMemNodeSizeGet(ptr);
        OS_MEM_MODID_SET(OsMemPtrToNode(ptr), module);
        LOS_IntRestore(intSave);
    }
    return ptr;
}

VOID *LOS_MemMallocAlign(VOID *pool, UINT32 size, UINT32 boundary, UINT32 module)
{
    UINTPTR intSave;
    VOID *ptr = NULL;
    if (OsMemModCheck(module) == LOS_NOK) {
        return NULL;
    }
    ptr = LOS_MemAllocAlign(pool, size, boundary);
    if (ptr != NULL) {
        intSave = LOS_IntLock();
        g_memInfo[module] += OsMemNodeSizeGet(ptr);
        OS_MEM_MODID_SET(OsMemPtrToNode(ptr), module);
        LOS_IntRestore(intSave);
    }
    return ptr;
}

UINT32 LOS_MemMfree(VOID *pool, VOID *ptr, UINT32 module)
{
    UINTPTR intSave;
    UINT32 ret;
    UINT32 size;

    if ((OsMemModCheck(module) == LOS_NOK) || (ptr == NULL)) {
        return LOS_NOK;
    }

    size = OsMemNodeSizeGet(ptr);

    if (module != OS_MEM_MODID_GET(OsMemPtrToNode(ptr))) {
        PRINT_ERR("node[%p] alloced in module %d, but free in module %d\n node's taskID: 0x%x\n",
                  ptr, OS_MEM_MODID_GET(OsMemPtrToNode(ptr)), module, OS_MEM_TASKID_GET(OsMemPtrToNode(ptr)));
    }

    ret = LOS_MemFree(pool, ptr);
    if (ret == LOS_OK) {
        intSave = LOS_IntLock();
        g_memInfo[module] -= size;
        LOS_IntRestore(intSave);
    }
    return ret;
}

VOID *LOS_MemMrealloc(VOID *pool, VOID *ptr, UINT32 size, UINT32 module)
{
    VOID *newPtr = NULL;
    UINT32 oldSize;
    UINTPTR intSave;

    if (OsMemModCheck(module) == LOS_NOK) {
        return NULL;
    }

    if (ptr == NULL) {
        return LOS_MemMalloc(pool, size, module);
    }

    if (module != OS_MEM_MODID_GET(OsMemPtrToNode(ptr))) {
        PRINT_ERR("a node[%p] alloced in module %d, but realloc in module %d\n node's taskID: %d\n",
                  ptr, OS_MEM_MODID_GET(OsMemPtrToNode(ptr)), module, OS_MEM_TASKID_GET(OsMemPtrToNode(ptr)));
    }

    if (size == 0) {
        if (LOS_MemMfree(pool, ptr, module) != LOS_OK) {
            PRINT_ERR("Mem Free Failed!\n");
        }
        return NULL;
    }

    oldSize = OsMemNodeSizeGet(ptr);
    newPtr = LOS_MemRealloc(pool, ptr, size);
    if (newPtr != NULL) {
        intSave = LOS_IntLock();
        g_memInfo[module] += OsMemNodeSizeGet(newPtr);
        g_memInfo[module] -= oldSize;
        OS_MEM_MODID_SET(OsMemPtrToNode(newPtr), module);
        LOS_IntRestore(intSave);
    }
    return newPtr;
}

UINT32 LOS_MemMusedGet(UINT32 module)
{
    if (OsMemModCheck(module) == LOS_NOK) {
        return LOS_NOK;
    }
    return g_memInfo[module];
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
