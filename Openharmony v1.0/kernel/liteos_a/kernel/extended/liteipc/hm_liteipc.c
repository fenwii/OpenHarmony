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

#include "hm_liteipc.h"
#include "linux/kernel.h"
#include <fs/fs.h>
#include "los_mp.h"
#include "los_mux.h"
#include "los_process_pri.h"
#include "los_spinlock.h"
#include "los_task_pri.h"
#if (LOSCFG_KERNEL_TRACE == YES)
#include "los_trace.h"
#endif
#include "los_vm_map.h"
#include "los_vm_phys.h"
#include "los_vm_page.h"
#include "los_vm_lock.h"

#define USE_TASKID_AS_HANDLE YES
#define USE_MMAP YES
#define IPC_MSG_DATA_SZ_MAX 1024
#define IPC_MSG_OBJECT_NUM_MAX 256

#define LITE_IPC_POOL_NAME "liteipc"
#define LITE_IPC_POOL_PAGE_MAX_NUM 64 /* 256KB */
#define LITE_IPC_POOL_PAGE_DEFAULT_NUM 16 /* 64KB */
#define LITE_IPC_POOL_MAX_SIZE (LITE_IPC_POOL_PAGE_MAX_NUM << PAGE_SHIFT)
#define LITE_IPC_POOL_DEFAULT_SIZE (LITE_IPC_POOL_PAGE_DEFAULT_NUM << PAGE_SHIFT)
#define LITE_IPC_POOL_UVADDR 0x10000000
#define INVAILD_ID (-1)

#define LITEIPC_TIMEOUT_MS 5000UL
#define LITEIPC_TIMEOUT_NS 5000000000ULL

typedef struct {
    LOS_DL_LIST list;
    VOID *ptr;
} IpcUsedNode;

LosMux g_serviceHandleMapMux;
#if (USE_TASKID_AS_HANDLE == YES)
HandleInfo g_cmsTask;
#else
HandleInfo g_serviceHandleMap[MAX_SERVICE_NUM];
#endif
STATIC LOS_DL_LIST g_ipcPendlist;
STATIC LOS_DL_LIST g_ipcUsedNodelist[LOSCFG_BASE_CORE_PROCESS_LIMIT];

/* ipc lock */
SPIN_LOCK_INIT(g_ipcSpin);
#define IPC_LOCK(state)       LOS_SpinLockSave(&g_ipcSpin, &(state))
#define IPC_UNLOCK(state)     LOS_SpinUnlockRestore(&g_ipcSpin, state)

STATIC int LiteIpcOpen(FAR struct file *filep);
STATIC int LiteIpcClose(FAR struct file *filep);
STATIC int LiteIpcIoctl(FAR struct file *filep, int cmd, unsigned long arg);
STATIC int LiteIpcMmap(FAR struct file* filep, LosVmMapRegion *region);
STATIC UINT32 LiteIpcWrite(IpcContent *content);
STATIC UINT32 GetTid(UINT32 serviceHandle, UINT32 *taskID);
STATIC UINT32 HandleSpecialObjects(UINT32 dstTid, IpcListNode *node, BOOL isRollback);


STATIC const struct file_operations_vfs g_liteIpcFops = {
    LiteIpcOpen,   /* open */
    LiteIpcClose,  /* close */
    NULL,          /* read */
    NULL,          /* write */
    NULL,          /* seek */
    LiteIpcIoctl,  /* ioctl */
    LiteIpcMmap,   /* mmap */
#ifndef CONFIG_DISABLE_POLL
    NULL,          /* poll */
#endif
    NULL,          /* unlink */
};

#if (LOSCFG_KERNEL_TRACE == YES)
const char *g_operStr[OPERATION_NUM] = {"WRITE", "WRITE_DROP", "TRY_READ", "READ", "READ_DROP", "READ_TIMEOUT"};
const char *g_msgTypeStr[MT_NUM] = {"REQUEST", "REPLY", "DEATH_NOTIFY"};
const char *g_ipcStatusStr[2] = {"NOT_PEND", "PEND"};

LITE_OS_SEC_TEXT STATIC UINT16 IpcTraceHook(UINT8 *inputBuffer, UINT32 id, UINT32 msg)
{
    IpcTraceFrame *ipcInfo = NULL;
    if (inputBuffer == NULL) {
        return 0;
    }

    ipcInfo = (IpcTraceFrame *)inputBuffer;
    ipcInfo->idInfo = id;
    ipcInfo->msgInfo = msg;
    ipcInfo->timestamp = LOS_CurrNanosec();

    return sizeof(IpcTraceFrame);
}

LITE_OS_SEC_TEXT STATIC VOID IpcTrace(IpcMsg *msg, UINT32 operation, UINT32 ipcStatus, UINT32 msgType)
{
    UINT32 curTid = LOS_CurTaskIDGet();
    UINT32 curPid = LOS_GetCurrProcessID();
    UINT32 dstTid;
    UINT32 ret = (msg == NULL) ? INVAILD_ID : GetTid(msg->target.handle, &dstTid);
    IdArg id = {INVAILD_ID, INVAILD_ID, INVAILD_ID, INVAILD_ID};
    MsgArg msgArg;
    if (operation <= WRITE_DROP) {
        id.srcTid = curTid;
        id.srcPid = curPid;
        id.dstTid = ret ? INVAILD_ID : dstTid;
        id.dstPid = ret ? INVAILD_ID : OS_TCB_FROM_TID(dstTid)->processID;
    } else {
        id.srcTid = (msg == NULL) ? INVAILD_ID : msg->taskID;
        id.srcPid = (msg == NULL) ? INVAILD_ID : msg->processID;
        id.dstTid = curTid;
        id.dstPid = curPid;
    }
    msgArg.msgType = msgType;
    msgArg.code = (msg == NULL) ? INVAILD_ID : msg->code;
    msgArg.operation = operation;
    msgArg.ipcStatus = ipcStatus;

    VOID *ptr1 = &id;
    VOID *ptr2 = &msgArg;
    LOS_Trace(LOS_TRACE_IPC, *((UINT32 *)ptr1), *((UINT32 *)ptr2));
}

UINT32 IpcInfoCheck(IpcTraceFrame *ipcInfo)
{
    MsgArg *msgArg = NULL;

    if (ipcInfo == NULL) {
        return LOS_NOK;
    }

    msgArg = (MsgArg *)&ipcInfo->msgInfo;
    if ((msgArg->operation >= OPERATION_NUM) ||
        (msgArg->msgType >= MT_NUM)) {
        return LOS_NOK;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC VOID IpcTracePrint(UINT32 cpuID, IpcTraceFrame *ipcInfo)
{
    IdArg *idArg = (IdArg *)&ipcInfo->idInfo;
    MsgArg *msgArg = (MsgArg *)&ipcInfo->msgInfo;

    if (IpcInfoCheck(ipcInfo) != LOS_OK) {
        return;
    }

    PRINTK("[LiteIPCTrace]timestamp:%016lld", ipcInfo->timestamp);
    PRINTK(" cpuID:%02d", cpuID);
    PRINTK(" operation:%13s", g_operStr[msgArg->operation]);
    PRINTK(" msgType:%12s", g_msgTypeStr[msgArg->msgType]);
    UINT32 isPend = (msgArg->ipcStatus & IPC_THREAD_STATUS_PEND) == IPC_THREAD_STATUS_PEND;
    PRINTK(" ipcStatus:%9s", g_ipcStatusStr[isPend]);
    PRINTK(" code:%03d", msgArg->code);
    PRINTK(" srcTid:%03d", idArg->srcTid);
    PRINTK(" srcPid:%03d", idArg->srcPid);
    PRINTK(" dstTid:%03d", idArg->dstTid);
    PRINTK(" dstPid:%03d\n", idArg->dstPid);
}

VOID IpcBacktrace(VOID)
{
    INT32 pos;
    INT32 i;
    TraceBuffer buff;
    for (i = 0; i < LOSCFG_KERNEL_CORE_NUM; i++) {
        LOS_TraceBufGet(&buff, i);
        pos = buff.tracePos;
        while (pos >= sizeof(IpcTraceFrame) + LOS_TRACE_TAG_LENGTH) {
            UINT32 *traceType = (UINT32 *)(buff.dataBuf + pos - LOS_TRACE_TAG_LENGTH);
            pos -= sizeof(IpcTraceFrame) + LOS_TRACE_TAG_LENGTH;
            switch (*traceType) {
                case LOS_TRACE_IPC: {
                    IpcTraceFrame *ipcInfo = (IpcTraceFrame *)(buff.dataBuf + pos);
                    IpcTracePrint(i, ipcInfo);
                    break;
                }
                default:
                    PRINTK("other module trace\n");
                    break;
            }
        }
    }
}
#endif

LITE_OS_SEC_TEXT_INIT UINT32 LiteIpcInit(VOID)
{
    UINT32 ret, i;
#if (USE_TASKID_AS_HANDLE == YES)
    g_cmsTask.status = HANDLE_NOT_USED;
#else
    memset_s(g_serviceHandleMap, sizeof(g_serviceHandleMap), 0, sizeof(g_serviceHandleMap));
#endif
    ret = LOS_MuxInit(&g_serviceHandleMapMux, NULL);
    if (ret != LOS_OK) {
        return ret;
    }
    ret = (UINT32)register_driver(LITEIPC_DRIVER, &g_liteIpcFops, DRIVER_MODE, NULL);
    if (ret != LOS_OK) {
        PRINT_ERR("register lite_ipc driver failed:%d\n", ret);
    }
    LOS_ListInit(&(g_ipcPendlist));
    for (i = 0; i < LOSCFG_BASE_CORE_PROCESS_LIMIT; i++) {
        LOS_ListInit(&(g_ipcUsedNodelist[i]));
    }
#if (LOSCFG_KERNEL_TRACE == YES)
    ret = LOS_TraceUserReg(LOS_TRACE_IPC, IpcTraceHook, sizeof(IpcTraceFrame));
    if (ret != LOS_OK) {
        PRINT_ERR("liteipc LOS_TraceUserReg failed:%d\n", ret);
    }
#endif
    return ret;
}

LITE_OS_SEC_TEXT STATIC int LiteIpcOpen(FAR struct file *filep)
{
    return 0;
}

LITE_OS_SEC_TEXT STATIC int LiteIpcClose(FAR struct file *filep)
{
    return 0;
}

LITE_OS_SEC_TEXT STATIC BOOL IsPoolMapped(VOID)
{
    LosProcessCB *pcb = OsCurrProcessGet();
    return (pcb->ipcInfo.pool.uvaddr != NULL) && (pcb->ipcInfo.pool.kvaddr != NULL) &&
        (pcb->ipcInfo.pool.poolSize != 0);
}

LITE_OS_SEC_TEXT STATIC INT32 DoIpcMmap(LosProcessCB *pcb, LosVmMapRegion *region)
{
    UINT32 i;
    INT32 ret = 0;
    PADDR_T pa;
    UINT32 uflags = VM_MAP_REGION_FLAG_PERM_READ | VM_MAP_REGION_FLAG_PERM_USER;
    LosVmPage *vmPage = NULL;
    VADDR_T uva = (VADDR_T)(UINTPTR)pcb->ipcInfo.pool.uvaddr;
    VADDR_T kva = (VADDR_T)(UINTPTR)pcb->ipcInfo.pool.kvaddr;

    (VOID)LOS_MuxAcquire(&pcb->vmSpace->regionMux);

    for (i = 0; i < (region->range.size >> PAGE_SHIFT); i++) {
        pa = LOS_PaddrQuery((VOID *)(UINTPTR)(kva + (i << PAGE_SHIFT)));
        if (pa == 0) {
            PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
            ret = -EINVAL;
            break;
        }
        vmPage = LOS_VmPageGet(pa);
        if (vmPage == NULL) {
            PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
            ret = -EINVAL;
            break;
        }
        STATUS_T err = LOS_ArchMmuMap(&pcb->vmSpace->archMmu, uva + (i << PAGE_SHIFT), pa, 1, uflags);
        if (err < 0) {
            ret = err;
            PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
            break;
        }
        LOS_AtomicInc(&vmPage->refCounts);
    }
    /* if any failure happened, rollback */
    if (i != (region->range.size >> PAGE_SHIFT)) {
        while (i--) {
            pa = LOS_PaddrQuery((VOID *)(UINTPTR)(kva + (i << PAGE_SHIFT)));
            vmPage = LOS_VmPageGet(pa);
            (VOID)LOS_ArchMmuUnmap(&pcb->vmSpace->archMmu, uva + (i << PAGE_SHIFT), 1);
            LOS_PhysPageFree(vmPage);
        }
    }

    (VOID)LOS_MuxRelease(&pcb->vmSpace->regionMux);
    return ret;
}

LITE_OS_SEC_TEXT STATIC int LiteIpcMmap(FAR struct file* filep, LosVmMapRegion *region)
{
    int ret = 0;
    LosVmMapRegion *regionTemp = NULL;
    LosProcessCB *pcb = OsCurrProcessGet();
    if ((region == NULL) || (region->range.size > LITE_IPC_POOL_MAX_SIZE) ||
            (!LOS_IsRegionPermUserReadOnly(region)) || (!LOS_IsRegionFlagPrivateOnly(region))) {
        ret = -EINVAL;
        goto ERROR_REGION_OUT;
    }
    if (IsPoolMapped()) {
        return -EEXIST;
    }
    if (pcb->ipcInfo.pool.uvaddr != NULL) {
        regionTemp = LOS_RegionFind(pcb->vmSpace, (VADDR_T)(UINTPTR)pcb->ipcInfo.pool.uvaddr);
        if (regionTemp != NULL) {
            (VOID)LOS_RegionFree(pcb->vmSpace, regionTemp);
        }
    }
    pcb->ipcInfo.pool.uvaddr = (VOID *)(UINTPTR)region->range.base;
    if (pcb->ipcInfo.pool.kvaddr != NULL) {
        LOS_VFree(pcb->ipcInfo.pool.kvaddr);
        pcb->ipcInfo.pool.kvaddr = NULL;
    }
    /* use vmalloc to alloc phy mem */
    pcb->ipcInfo.pool.kvaddr = LOS_VMalloc(region->range.size);
    if (pcb->ipcInfo.pool.kvaddr == NULL) {
        ret = -ENOMEM;
        goto ERROR_REGION_OUT;
    }
    /* do mmap */
    ret = DoIpcMmap(pcb, region);
    if (ret) {
        goto ERROR_MAP_OUT;
    }
    /* ipc pool init */
    if (LOS_MemInit(pcb->ipcInfo.pool.kvaddr, region->range.size) != LOS_OK) {
        ret = -EINVAL;
        goto ERROR_MAP_OUT;
    }
    pcb->ipcInfo.pool.poolSize = region->range.size;
    return 0;
ERROR_MAP_OUT:
    LOS_VFree(pcb->ipcInfo.pool.kvaddr);
ERROR_REGION_OUT:
    pcb->ipcInfo.pool.uvaddr = NULL;
    pcb->ipcInfo.pool.kvaddr = NULL;
    return ret;
}

LITE_OS_SEC_TEXT_INIT UINT32 LiteIpcPoolInit(ProcIpcInfo *ipcInfo)
{
    ipcInfo->pool.uvaddr = NULL;
    ipcInfo->pool.kvaddr = NULL;
    ipcInfo->pool.poolSize = 0;
    ipcInfo->ipcTaskID = INVAILD_ID;
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LiteIpcPoolReInit(ProcIpcInfo *child, const ProcIpcInfo *parent)
{
    child->pool.uvaddr = parent->pool.uvaddr;
    child->pool.kvaddr = NULL;
    child->pool.poolSize = 0;
    child->ipcTaskID = INVAILD_ID;
    return LOS_OK;
}

LITE_OS_SEC_TEXT VOID LiteIpcPoolDelete(ProcIpcInfo *ipcInfo)
{
    UINT32 intSave;
    IpcUsedNode *node = NULL;
    UINT32 processID = LOS_GetCurrProcessID();
    if (ipcInfo->pool.kvaddr != NULL) {
        LOS_VFree(ipcInfo->pool.kvaddr);
        ipcInfo->pool.kvaddr = NULL;
        IPC_LOCK(intSave);
        while (!LOS_ListEmpty(&g_ipcUsedNodelist[processID])) {
            node = LOS_DL_LIST_ENTRY(g_ipcUsedNodelist[processID].pstNext, IpcUsedNode, list);
            LOS_ListDelete(&node->list);
            free(node);
        }
        IPC_UNLOCK(intSave);
    }
    /* remove process access to service */
    for (UINT32 i = 0; i < MAX_SERVICE_NUM; i++) {
        if (ipcInfo->access[i] == TRUE) {
            ipcInfo->access[i] = FALSE;
            OS_TCB_FROM_TID(i)->accessMap[processID] = FALSE;
        }
    }
}

/* Only when kernenl no longer access ipc node content, can user free the ipc node */
LITE_OS_SEC_TEXT STATIC VOID EnableIpcNodeFreeByUser(UINT32 processID, VOID *buf)
{
    UINT32 intSave;
    IpcUsedNode *node = (IpcUsedNode *)malloc(sizeof(IpcUsedNode));
    if (node != NULL) {
        node->ptr = buf;
        IPC_LOCK(intSave);
        LOS_ListAdd(&g_ipcUsedNodelist[processID], &node->list);
        IPC_UNLOCK(intSave);
    }
}

LITE_OS_SEC_TEXT STATIC VOID* LiteIpcNodeAlloc(UINT32 processID, UINT32 size)
{
    VOID *ptr = LOS_MemAlloc(OS_PCB_FROM_PID(processID)->ipcInfo.pool.kvaddr, size);
    PRINT_INFO("LiteIpcNodeAlloc pid:%d, pool:%x buf:%x size:%d\n",
               processID, OS_PCB_FROM_PID(processID)->ipcInfo.pool.kvaddr, ptr, size);
    return ptr;
}

LITE_OS_SEC_TEXT STATIC UINT32 LiteIpcNodeFree(UINT32 processID, VOID *buf)
{
    PRINT_INFO("LiteIpcNodeFree pid:%d, pool:%x buf:%x\n",
               processID, OS_PCB_FROM_PID(processID)->ipcInfo.pool.kvaddr, buf);
    return LOS_MemFree(OS_PCB_FROM_PID(processID)->ipcInfo.pool.kvaddr, buf);
}

LITE_OS_SEC_TEXT STATIC BOOL IsIpcNode(UINT32 processID, const VOID *buf)
{
    IpcUsedNode *node = NULL;
    UINT32 intSave;
    IPC_LOCK(intSave);
    LOS_DL_LIST_FOR_EACH_ENTRY(node, &g_ipcUsedNodelist[processID], IpcUsedNode, list) {
        if (node->ptr == buf) {
            LOS_ListDelete(&node->list);
            IPC_UNLOCK(intSave);
            free(node);
            return TRUE;
        }
    }
    IPC_UNLOCK(intSave);
    return FALSE;
}

LITE_OS_SEC_TEXT STATIC INTPTR GetIpcUserAddr(UINT32 processID, INTPTR kernelAddr)
{
    IpcPool pool = OS_PCB_FROM_PID(processID)->ipcInfo.pool;
    INTPTR offset = (INTPTR)(pool.uvaddr) - (INTPTR)(pool.kvaddr);
    return kernelAddr + offset;
}

LITE_OS_SEC_TEXT STATIC INTPTR GetIpcKernelAddr(UINT32 processID, INTPTR userAddr)
{
    IpcPool pool = OS_PCB_FROM_PID(processID)->ipcInfo.pool;
    INTPTR offset = (INTPTR)(pool.uvaddr) - (INTPTR)(pool.kvaddr);
    return userAddr - offset;
}

LITE_OS_SEC_TEXT STATIC UINT32 CheckUsedBuffer(const VOID *node, IpcListNode **outPtr)
{
    VOID *ptr = NULL;
    LosProcessCB *pcb = OsCurrProcessGet();
    IpcPool pool = pcb->ipcInfo.pool;
    if ((node == NULL) || ((INTPTR)node < (INTPTR)(pool.uvaddr)) ||
        ((INTPTR)node > (INTPTR)(pool.uvaddr) + pool.poolSize)) {
        return -EINVAL;
    }
    ptr = (VOID *)GetIpcKernelAddr(pcb->processID, (INTPTR)(node));
    if (IsIpcNode(pcb->processID, ptr) != TRUE) {
        return -EFAULT;
    }
    *outPtr = (IpcListNode *)ptr;
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 GetTid(UINT32 serviceHandle, UINT32 *taskID)
{
    if (serviceHandle >= MAX_SERVICE_NUM) {
        return -EINVAL;
    }
#if (USE_TASKID_AS_HANDLE == YES)
    *taskID = serviceHandle ? serviceHandle : g_cmsTask.taskID;
    return LOS_OK;
#else
    if (g_serviceHandleMap[serviceHandle].status == HANDLE_REGISTED) {
        *taskID = g_serviceHandleMap[serviceHandle].taskID;
        return LOS_OK;
    }
    return -EINVAL;
#endif
}

LITE_OS_SEC_TEXT STATIC UINT32 GenerateServiceHandle(UINT32 taskID, HandleStatus status, UINT32 *serviceHandle)
{
#if (USE_TASKID_AS_HANDLE == YES)
    *serviceHandle = taskID ? taskID : LOS_CurTaskIDGet(); /* if taskID is 0, return curTaskID */
    if (*serviceHandle == g_cmsTask.taskID) {
        return -EINVAL;
    }
    return LOS_OK;
#else
    UINT32 i;
    (VOID)LOS_MuxLock(&g_serviceHandleMapMux, LOS_WAIT_FOREVER);
    for (i = 1; i < MAX_SERVICE_NUM; i++) {
        if (g_serviceHandleMap[i].status == HANDLE_NOT_USED) {
            g_serviceHandleMap[i].taskID = taskID;
            g_serviceHandleMap[i].status = status;
            *serviceHandle = i;
            (VOID)LOS_MuxUnLock(&g_serviceHandleMapMux);
            return LOS_OK;
        }
    }
    (VOID)LOS_MuxUnlock(&g_serviceHandleMapMux);
    return -EINVAL;
#endif
}

LITE_OS_SEC_TEXT STATIC VOID RefreshServiceHandle(UINT32 serviceHandle, UINT32 result)
{
#if (USE_TASKID_AS_HANDLE == NO)
    (VOID)LOS_MuxLock(&g_serviceHandleMapMux, LOS_WAIT_FOREVER);
    if ((result == LOS_OK) && (g_serviceHandleMap[serviceHandle].status == HANDLE_REGISTING)) {
        g_serviceHandleMap[serviceHandle].status = HANDLE_REGISTED;
    } else {
        g_serviceHandleMap[serviceHandle].status = HANDLE_NOT_USED;
    }
    (VOID)LOS_MuxUnlock(&g_serviceHandleMapMux);
#endif
}

LITE_OS_SEC_TEXT STATIC UINT32 AddServiceAccess(UINT32 taskID, UINT32 serviceHandle)
{
    UINT32 serviceTid = 0;
    UINT32 ret = GetTid(serviceHandle, &serviceTid);
    if (ret != LOS_OK) {
        PRINT_ERR("AddServiceAccess GetTid failed\n");
        return ret;
    }
    UINT32 processID = OS_TCB_FROM_TID(taskID)->processID;
    OS_TCB_FROM_TID(serviceTid)->accessMap[processID] = TRUE;
    OS_PCB_FROM_PID(processID)->ipcInfo.access[serviceTid] = TRUE;
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC BOOL HasServiceAccess(UINT32 serviceHandle)
{
    UINT32 serviceTid = 0;
    UINT32 curProcessID = LOS_GetCurrProcessID();
    UINT32 ret;
    if (serviceHandle >= MAX_SERVICE_NUM) {
        return FALSE;
    }
    if (serviceHandle == 0) {
        return TRUE;
    }
    ret = GetTid(serviceHandle, &serviceTid);
    if (ret != LOS_OK) {
        PRINT_ERR("HasServiceAccess GetTid failed\n");
        return FALSE;
    }
    if (OS_TCB_FROM_TID(serviceTid)->processID == curProcessID) {
        return TRUE;
    }
    return OS_TCB_FROM_TID(serviceTid)->accessMap[curProcessID];
}

LITE_OS_SEC_TEXT STATIC UINT32 SetIpcTask(VOID)
{
    if (OsCurrProcessGet()->ipcInfo.ipcTaskID == INVAILD_ID) {
        OsCurrProcessGet()->ipcInfo.ipcTaskID = LOS_CurTaskIDGet();
        return OsCurrProcessGet()->ipcInfo.ipcTaskID;
    }
    PRINT_ERR("curprocess %d IpcTask already set!\n", OsCurrProcessGet()->processID);
    return -EINVAL;
}

LITE_OS_SEC_TEXT BOOL IsIpcTaskSet(VOID)
{
    if (OsCurrProcessGet()->ipcInfo.ipcTaskID == INVAILD_ID) {
        return FALSE;
    }
    return TRUE;
}

LITE_OS_SEC_TEXT STATIC UINT32 GetIpcTaskID(UINT32 processID, UINT32 *ipcTaskID)
{
    if (OS_PCB_FROM_PID(processID)->ipcInfo.ipcTaskID == INVAILD_ID) {
        return LOS_NOK;
    }
    *ipcTaskID = OS_PCB_FROM_PID(processID)->ipcInfo.ipcTaskID;
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 SendDeathMsg(UINT32 processID, UINT32 serviceHandle)
{
    UINT32 ipcTaskID;
    UINT32 ret;
    IpcContent content;
    IpcMsg msg;

    OS_PCB_FROM_PID(processID)->ipcInfo.access[serviceHandle] = false;

    ret = GetIpcTaskID(processID, &ipcTaskID);
    if (ret != LOS_OK) {
        return -EINVAL;
    }
    content.flag = SEND;
    content.outMsg = &msg;
    memset_s(content.outMsg, sizeof(IpcMsg), 0, sizeof(IpcMsg));
    content.outMsg->type = MT_DEATH_NOTIFY;
    content.outMsg->target.handle = ipcTaskID;
    content.outMsg->target.token = serviceHandle;
    content.outMsg->code = 0;
    return LiteIpcWrite(&content);
}

LITE_OS_SEC_TEXT VOID LiteIpcRemoveServiceHandle(LosTaskCB *taskCB)
{
    UINT32 j;
#if (USE_TASKID_AS_HANDLE == YES)

    UINT32 intSave;
    LOS_DL_LIST *listHead = NULL;
    LOS_DL_LIST *listNode = NULL;
    IpcListNode *node = NULL;
    UINT32 processID = taskCB->processID;

    listHead = &(taskCB->msgListHead);
    do {
        SCHEDULER_LOCK(intSave);
        if (LOS_ListEmpty(listHead)) {
            SCHEDULER_UNLOCK(intSave);
            break;
        } else {
            listNode = LOS_DL_LIST_FIRST(listHead);
            LOS_ListDelete(listNode);
            node = LOS_DL_LIST_ENTRY(listNode, IpcListNode, listNode);
            SCHEDULER_UNLOCK(intSave);
            (VOID)HandleSpecialObjects(taskCB->taskID, node, TRUE);
            (VOID)LiteIpcNodeFree(processID, (VOID *)node);
        }
    } while (1);

    taskCB->accessMap[processID] = FALSE;
    for (j = 0; j < MAX_SERVICE_NUM; j++) {
        if (taskCB->accessMap[j] == TRUE) {
            taskCB->accessMap[j] = FALSE;
            (VOID)SendDeathMsg(j, taskCB->taskID);
        }
    }
#else
    (VOID)LOS_MuxLock(&g_serviceHandleMapMux, LOS_WAIT_FOREVER);
    for (UINT32 i = 1; i < MAX_SERVICE_NUM; i++) {
        if ((g_serviceHandleMap[i].status != HANDLE_NOT_USED) && (g_serviceHandleMap[i].taskID == taskCB->taskID)) {
            g_serviceHandleMap[i].status = HANDLE_NOT_USED;
            g_serviceHandleMap[i].taskID = INVAILD_ID;
            break;
        }
    }
    (VOID)LOS_MuxUnlock(&g_serviceHandleMapMux);
    /* run deathHandler */
    if (i < MAX_SERVICE_NUM) {
        for (j = 0; j < MAX_SERVICE_NUM; j++) {
            if (taskCB->accessMap[j] == TRUE) {
                (VOID)SendDeathMsg(j, i);
            }
        }
    }
#endif
}

LITE_OS_SEC_TEXT STATIC UINT32 SetCms(UINTPTR maxMsgSize)
{
    if (maxMsgSize < sizeof(IpcMsg)) {
        return -EINVAL;
    }
    (VOID)LOS_MuxLock(&g_serviceHandleMapMux, LOS_WAIT_FOREVER);
#if (USE_TASKID_AS_HANDLE == YES)
    if (g_cmsTask.status == HANDLE_NOT_USED) {
        g_cmsTask.status = HANDLE_REGISTED;
        g_cmsTask.taskID = LOS_CurTaskIDGet();
        g_cmsTask.maxMsgSize = maxMsgSize;
        (VOID)LOS_MuxUnlock(&g_serviceHandleMapMux);
        return LOS_OK;
    }
#else
    if (g_serviceHandleMap[0].status == HANDLE_NOT_USED) {
        g_serviceHandleMap[0].status = HANDLE_REGISTED;
        g_serviceHandleMap[0].taskID = LOS_CurTaskIDGet();
        (VOID)LOS_MuxUnlock(&g_serviceHandleMapMux);
        return LOS_OK;
    }
#endif
    (VOID)LOS_MuxUnlock(&g_serviceHandleMapMux);
    return -EEXIST;
}

LITE_OS_SEC_TEXT STATIC BOOL IsCmsSet(VOID)
{
#if (USE_TASKID_AS_HANDLE == YES)
    return g_cmsTask.status == HANDLE_REGISTED;
#else
    return g_serviceHandleMap[0].status == HANDLE_REGISTED;
#endif
}

LITE_OS_SEC_TEXT STATIC BOOL IsCmsTask(UINT32 taskID)
{
#if (USE_TASKID_AS_HANDLE == YES)
    return IsCmsSet() ? (OS_TCB_FROM_TID(taskID)->processID == OS_TCB_FROM_TID(g_cmsTask.taskID)->processID) : FALSE;
#else
    return IsCmsSet() ? (OS_TCB_FROM_TID(taskID)->processID ==
        OS_TCB_FROM_TID(g_serviceHandleMap[0].taskID)->processID) : FALSE;
#endif
}

LITE_OS_SEC_TEXT STATIC BOOL IsTaskAlive(UINT32 taskID)
{
    LosTaskCB *tcb = NULL;
    if (OS_TID_CHECK_INVALID(taskID)) {
        return FALSE;
    }
    tcb = OS_TCB_FROM_TID(taskID);
    if (!OsProcessIsUserMode(OS_PCB_FROM_PID(tcb->processID))) {
        return FALSE;
    }
    if (OsTaskIsInactive(tcb)) {
        return FALSE;
    }
    return TRUE;
}

LITE_OS_SEC_TEXT STATIC UINT32 HandleFd(SpecialObj *obj, BOOL isRollback)
{
    /* now fd is not Isolated between processes, do nothing */
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 HandlePtr(UINT32 processID, SpecialObj *obj, BOOL isRollback)
{
    VOID *buf = NULL;
    UINT32 ret;
    if ((obj->content.ptr.buff == NULL) || (obj->content.ptr.buffSz == 0)) {
        return -EINVAL;
    }
    if (isRollback == FALSE) {
        if (LOS_IsUserAddress((vaddr_t)(UINTPTR)(obj->content.ptr.buff)) == FALSE) {
            PRINT_ERR("Bad ptr address\n");
            return -EINVAL;
        }
        buf = LiteIpcNodeAlloc(processID, obj->content.ptr.buffSz);
        if (buf == NULL) {
            PRINT_ERR("DealPtr alloc mem failed\n");
            return -EINVAL;
        }
        ret = copy_from_user(buf, obj->content.ptr.buff, obj->content.ptr.buffSz);
        if (ret != LOS_OK) {
            LiteIpcNodeFree(processID, buf);
            return ret;
        }
        obj->content.ptr.buff = (VOID *)GetIpcUserAddr(processID, (INTPTR)buf);
        EnableIpcNodeFreeByUser(processID, (VOID *)buf);
    } else {
        (VOID)LiteIpcNodeFree(processID, (VOID *)GetIpcKernelAddr(processID, (INTPTR)obj->content.ptr.buff));
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 HandleSvc(UINT32 dstTid, const SpecialObj *obj, BOOL isRollback)
{
    UINT32 taskID = 0;
    if (isRollback == FALSE) {
        if (IsTaskAlive(obj->content.svc.handle) == FALSE) {
            PRINT_ERR("HandleSvc wrong svctid\n");
            return -EINVAL;
        }
        if (HasServiceAccess(obj->content.svc.handle) == FALSE) {
            PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
            return -EACCES;
        }
        if (GetTid(obj->content.svc.handle, &taskID) == 0) {
            if (taskID == OS_PCB_FROM_PID(OS_TCB_FROM_TID(taskID)->processID)->ipcInfo.ipcTaskID) {
                AddServiceAccess(dstTid, obj->content.svc.handle);
            }
        }
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 HandleObj(UINT32 dstTid, SpecialObj *obj, BOOL isRollback)
{
    UINT32 ret;
    UINT32 processID = OS_TCB_FROM_TID(dstTid)->processID;
    switch (obj->type) {
        case OBJ_FD:
            ret = HandleFd(obj, isRollback);
            break;
        case OBJ_PTR:
            ret = HandlePtr(processID, obj, isRollback);
            break;
        case OBJ_SVC:
            ret = HandleSvc(dstTid, (const SpecialObj *)obj, isRollback);
            break;
        default:
            ret = -EINVAL;
            break;
    }
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 HandleSpecialObjects(UINT32 dstTid, IpcListNode *node, BOOL isRollback)
{
    UINT32 ret = LOS_OK;
    IpcMsg *msg = &(node->msg);
    INT32 i;
    SpecialObj *obj = NULL;
    UINT32 *offset = (UINT32 *)(UINTPTR)(msg->offsets);
    if (isRollback) {
        i = msg->spObjNum;
        goto EXIT;
    }
    for (i = 0; i < msg->spObjNum; i++) {
        if (offset[i] > msg->dataSz - sizeof(SpecialObj)) {
            ret = -EINVAL;
            goto EXIT;
        }
        if ((i > 0) && (offset[i] < offset[i - 1] + sizeof(SpecialObj))) {
            ret = -EINVAL;
            goto EXIT;
        }
        obj = (SpecialObj *)((UINTPTR)msg->data + offset[i]);
        if (obj == NULL) {
            ret = -EINVAL;
            goto EXIT;
        }
        ret = HandleObj(dstTid, obj, FALSE);
        if (ret != LOS_OK) {
            goto EXIT;
        }
    }
    return LOS_OK;
EXIT:
    for (i--; i >= 0; i--) {
        obj = (SpecialObj *)((UINTPTR)msg->data + offset[i]);
        (VOID)HandleObj(dstTid, obj, TRUE);
    }
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 CheckMsgSize(IpcMsg *msg)
{
    UINT64 totalSize;
    UINT32 i;
    UINT32 *offset = (UINT32 *)(UINTPTR)(msg->offsets);
    SpecialObj *obj = NULL;
    if (msg->target.handle != 0) {
        return LOS_OK;
    }
    /* msg send to cms, check the msg size */
    totalSize = (UINT64)sizeof(IpcMsg) + msg->dataSz + msg->spObjNum * sizeof(UINT32);
    for (i = 0; i < msg->spObjNum; i++) {
        if (offset[i] > msg->dataSz - sizeof(SpecialObj)) {
            return -EINVAL;
        }
        if ((i > 0) && (offset[i] < offset[i - 1] + sizeof(SpecialObj))) {
            return -EINVAL;
        }
        obj = (SpecialObj *)((UINTPTR)msg->data + offset[i]);
        if (obj == NULL) {
            return -EINVAL;
        }
        if (obj->type == OBJ_PTR) {
            totalSize += obj->content.ptr.buffSz;
        }
    }
    if (totalSize > g_cmsTask.maxMsgSize) {
        return -EINVAL;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 CopyDataFromUser(IpcListNode *node, UINT32 bufSz, const IpcMsg *msg)
{
    UINT32 ret;
    ret = (UINT32)memcpy_s((VOID *)(&node->msg), bufSz - sizeof(LOS_DL_LIST), (const VOID *)msg, sizeof(IpcMsg));
    if (ret != LOS_OK) {
        PRINT_DEBUG("%s, %d, %u\n", __FUNCTION__, __LINE__, ret);
        return ret;
    }

    if (msg->dataSz) {
        node->msg.data = (VOID *)((UINTPTR)node + sizeof(IpcListNode));
        ret = copy_from_user((VOID *)(node->msg.data), msg->data, msg->dataSz);
        if (ret != LOS_OK) {
            PRINT_DEBUG("%s, %d\n", __FUNCTION__, __LINE__);
            return ret;
        }
    } else {
        node->msg.data = NULL;
    }

    if (msg->spObjNum) {
        node->msg.offsets = (VOID *)((UINTPTR)node + sizeof(IpcListNode) + msg->dataSz);
        ret = copy_from_user((VOID *)(node->msg.offsets), msg->offsets, msg->spObjNum * sizeof(UINT32));
        if (ret != LOS_OK) {
            PRINT_DEBUG("%s, %d, %x, %x, %d\n", __FUNCTION__, __LINE__, node->msg.offsets, msg->offsets, msg->spObjNum);
            return ret;
        }
    } else {
        node->msg.offsets = NULL;
    }
    ret = CheckMsgSize(&node->msg);
    if (ret != LOS_OK) {
        PRINT_DEBUG("%s, %d\n", __FUNCTION__, __LINE__);
        return ret;
    }
    node->msg.taskID = LOS_CurTaskIDGet();
    node->msg.processID = OsCurrProcessGet()->processID;
#ifdef LOSCFG_SECURITY_CAPABILITY
    node->msg.userID = OsCurrProcessGet()->user->userID;
    node->msg.gid = OsCurrProcessGet()->user->gid;
#endif
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC BOOL IsLeagalReply(const IpcContent *content)
{
    UINT32 curProcessID = LOS_GetCurrProcessID();
    IpcListNode *node = (IpcListNode *)GetIpcKernelAddr(curProcessID, (INTPTR)(content->buffToFree));
    IpcMsg *requestMsg = &node->msg;
    IpcMsg *replyMsg = content->outMsg;
    UINT32 reqDstTid = 0;
    /* Check whether the reply matches the request */
    if ((requestMsg->type != MT_REQUEST)  ||
        (requestMsg->flag == LITEIPC_FLAG_ONEWAY) ||
        (replyMsg->timestamp != requestMsg->timestamp) ||
        (replyMsg->target.handle != requestMsg->taskID) ||
        (GetTid(requestMsg->target.handle, &reqDstTid) != 0) ||
        (OS_TCB_FROM_TID(reqDstTid)->processID != curProcessID)) {
        return FALSE;
    }
    return TRUE;
}

LITE_OS_SEC_TEXT STATIC UINT32 CheckPara(IpcContent *content, UINT32 *dstTid)
{
    UINT32 ret;
    IpcMsg *msg = content->outMsg;
    UINT32 flag = content->flag;
#if (USE_TIMESTAMP == YES)
    UINT64 now = LOS_CurrNanosec();
#endif
    if (((msg->dataSz > 0) && (msg->data == NULL)) ||
        ((msg->spObjNum > 0) && (msg->offsets == NULL)) ||
        (msg->dataSz > IPC_MSG_DATA_SZ_MAX) ||
        (msg->spObjNum > IPC_MSG_OBJECT_NUM_MAX) ||
        (msg->dataSz < msg->spObjNum * sizeof(SpecialObj))) {
        return -EINVAL;
    }
    switch (msg->type) {
        case MT_REQUEST:
            if (HasServiceAccess(msg->target.handle)) {
                ret = GetTid(msg->target.handle, dstTid);
                if (ret != LOS_OK) {
                    return -EINVAL;
                }
            } else {
                PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
                return -EACCES;
            }
#if (USE_TIMESTAMP == YES)
            msg->timestamp = now;
#endif
            break;
        case MT_REPLY:
        case MT_FAILED_REPLY:
            if ((flag & BUFF_FREE) != BUFF_FREE) {
                return -EINVAL;
            }
            if (!IsLeagalReply(content)) {
                return -EINVAL;
            }
#if (USE_TIMESTAMP == YES)
            if (now > msg->timestamp + LITEIPC_TIMEOUT_NS) {
#if (LOSCFG_KERNEL_TRACE == YES)
                IpcTrace(msg, WRITE_DROP, 0, msg->type);
                IpcBacktrace();
#endif
                PRINT_ERR("A timeout reply, request timestamp:%lld, now:%lld\n", msg->timestamp, now);
                return -ETIME;
            }
#endif
            *dstTid = msg->target.handle;
            break;
        case MT_DEATH_NOTIFY:
            *dstTid = msg->target.handle;
#if (USE_TIMESTAMP == YES)
            msg->timestamp = now;
#endif
            break;
        default:
            PRINT_DEBUG("Unknow msg type:%d\n", msg->type);
            return -EINVAL;
    }

    if (IsTaskAlive(*dstTid) == FALSE) {
        return -EINVAL;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 LiteIpcWrite(IpcContent *content)
{
    UINT32 ret, intSave;
    UINT32 dstTid;

    IpcMsg *msg = content->outMsg;

    ret = CheckPara(content, &dstTid);
    if (ret != LOS_OK) {
        return ret;
    }

    UINT32 bufSz = sizeof(IpcListNode) + msg->dataSz + msg->spObjNum * sizeof(UINT32);
    IpcListNode *buf = (IpcListNode *)LiteIpcNodeAlloc(OS_TCB_FROM_TID(dstTid)->processID, bufSz);
    if (buf == NULL) {
        PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }
    ret = CopyDataFromUser(buf, bufSz, (const IpcMsg *)msg);
    if (ret != LOS_OK) {
        PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
        goto ERROR_COPY;
    }
    ret = HandleSpecialObjects(dstTid, buf, FALSE);
    if (ret != LOS_OK) {
        PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
        goto ERROR_COPY;
    }
    /* add data to list and wake up dest task */
    SCHEDULER_LOCK(intSave);
    LosTaskCB *tcb = OS_TCB_FROM_TID(dstTid);
    LOS_ListTailInsert(&(tcb->msgListHead), &(buf->listNode));
#if (LOSCFG_KERNEL_TRACE == YES)
    IpcTrace(&buf->msg, WRITE, tcb->ipcStatus, buf->msg.type);
#endif
    if (tcb->ipcStatus & IPC_THREAD_STATUS_PEND) {
        tcb->ipcStatus &= ~IPC_THREAD_STATUS_PEND;
        OsTaskWake(tcb);
        SCHEDULER_UNLOCK(intSave);
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    } else {
        SCHEDULER_UNLOCK(intSave);
    }
    return LOS_OK;
ERROR_COPY:
    LiteIpcNodeFree(OS_TCB_FROM_TID(dstTid)->processID, buf);
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 CheckRecievedMsg(IpcListNode *node, IpcContent *content, LosTaskCB *tcb)
{
    UINT32 ret = LOS_OK;
    if (node == NULL) {
        return -EINVAL;
    }
    switch (node->msg.type) {
        case MT_REQUEST:
            if ((content->flag & SEND) == SEND) {
                PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
                ret = -EINVAL;
            }
            break;
        case MT_FAILED_REPLY:
            ret = -ENOENT;
            /* fall-through */
        case MT_REPLY:
            if ((content->flag & SEND) != SEND) {
                PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
                ret = -EINVAL;
            }
#if (USE_TIMESTAMP == YES)
            if (node->msg.timestamp != content->outMsg->timestamp) {
                PRINT_ERR("Recieve a unmatch reply, drop it\n");
                ret = -EINVAL;
            }
#else
            if ((node->msg.code != content->outMsg->code) ||
                (node->msg.target.token != content->outMsg->target.token)) {
                PRINT_ERR("Recieve a unmatch reply, drop it\n");
                ret = -EINVAL;
            }
#endif
            break;
        case MT_DEATH_NOTIFY:
            break;
        default:
            PRINT_ERR("Unknow msg type:%d\n", node->msg.type);
            ret =  -EINVAL;
    }
    if (ret != LOS_OK) {
#if (LOSCFG_KERNEL_TRACE == YES)
        IpcTrace(&node->msg, READ_DROP, tcb->ipcStatus, node->msg.type);
#endif
        (VOID)HandleSpecialObjects(LOS_CurTaskIDGet(), node, TRUE);
        (VOID)LiteIpcNodeFree(LOS_GetCurrProcessID(), (VOID *)node);
    } else {
#if (LOSCFG_KERNEL_TRACE == YES)
        IpcTrace(&node->msg, READ, tcb->ipcStatus, node->msg.type);
#endif
    }
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 LiteIpcRead(IpcContent *content)
{
    UINT32 intSave, ret;
    UINT32 selfTid = LOS_CurTaskIDGet();
    LOS_DL_LIST *listHead = NULL;
    LOS_DL_LIST *listNode = NULL;
    IpcListNode *node = NULL;
    UINT32 syncFlag = (content->flag & SEND) && (content->flag & RECV);
    UINT32 timeout = syncFlag ? LOS_MS2Tick(LITEIPC_TIMEOUT_MS) : LOS_WAIT_FOREVER;

    LosTaskCB *tcb = OS_TCB_FROM_TID(selfTid);
    listHead = &(tcb->msgListHead);
    do {
        SCHEDULER_LOCK(intSave);
        if (LOS_ListEmpty(listHead)) {
#if (LOSCFG_KERNEL_TRACE == YES)
            IpcTrace(NULL, TRY_READ, tcb->ipcStatus, syncFlag ? MT_REPLY : MT_REQUEST);
#endif
            tcb->ipcStatus |= IPC_THREAD_STATUS_PEND;
            ret = OsTaskWait(&g_ipcPendlist, timeout, TRUE);
            if (ret == LOS_ERRNO_TSK_TIMEOUT) {
#if (LOSCFG_KERNEL_TRACE == YES)
                IpcTrace(NULL, READ_TIMEOUT, tcb->ipcStatus, syncFlag ? MT_REPLY : MT_REQUEST);
#endif
                SCHEDULER_UNLOCK(intSave);
                return -ETIME;
            }

            SCHEDULER_UNLOCK(intSave);
        } else {
            listNode = LOS_DL_LIST_FIRST(listHead);
            LOS_ListDelete(listNode);
            node = LOS_DL_LIST_ENTRY(listNode, IpcListNode, listNode);
            SCHEDULER_UNLOCK(intSave);
            ret = CheckRecievedMsg(node, content, tcb);
            if (ret == LOS_OK) {
                break;
            }
            if (ret == -ENOENT) { /* It means that we've recieved a failed reply */
                return ret;
            }
        }
    } while (1);
    node->msg.data = (VOID *)GetIpcUserAddr(LOS_GetCurrProcessID(), (INTPTR)(node->msg.data));
    node->msg.offsets = (VOID *)GetIpcUserAddr(LOS_GetCurrProcessID(), (INTPTR)(node->msg.offsets));
    content->inMsg = (VOID *)GetIpcUserAddr(LOS_GetCurrProcessID(), (INTPTR)(&(node->msg)));
    EnableIpcNodeFreeByUser(LOS_GetCurrProcessID(), (VOID *)node);
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 LiteIpcMsgHandle(IpcContent *con)
{
    UINT32 ret = LOS_OK;
    IpcContent localContent;
    IpcContent *content = &localContent;
    IpcMsg localMsg;
    IpcMsg *msg = &localMsg;
    IpcListNode *nodeNeedFree = NULL;

    if (copy_from_user((void *)content, (const void *)con, sizeof(IpcContent)) != LOS_OK) {
        PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
        return -EINVAL;
    }

    if ((content->flag & BUFF_FREE) == BUFF_FREE) {
        ret = CheckUsedBuffer(content->buffToFree, &nodeNeedFree);
        if (ret != LOS_OK) {
            PRINT_ERR("CheckUsedBuffer failed:%d\n", ret);
            return ret;
        }
    }

    if ((content->flag & SEND) == SEND) {
        if (content->outMsg == NULL) {
            PRINT_ERR("content->outmsg is null\n");
            ret = -EINVAL;
            goto BUFFER_FREE;
        }
        if (copy_from_user((void *)msg, (const void *)content->outMsg, sizeof(IpcMsg)) != LOS_OK) {
            PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
            ret = -EINVAL;
            goto BUFFER_FREE;
        }
        content->outMsg = msg;
        if ((content->outMsg->type < 0) || (content->outMsg->type >= MT_DEATH_NOTIFY)) {
            PRINT_ERR("LiteIpc unknow msg type:%d\n", content->outMsg->type);
            ret = -EINVAL;
            goto BUFFER_FREE;
        }
        ret = LiteIpcWrite(content);
        if (ret != LOS_OK) {
            PRINT_ERR("LiteIpcWrite failed\n");
            goto BUFFER_FREE;
        }
    }
BUFFER_FREE:
    if (nodeNeedFree != NULL) {
        UINT32 freeRet = LiteIpcNodeFree(LOS_GetCurrProcessID(), nodeNeedFree);
        ret = (freeRet == LOS_OK) ? ret : freeRet;
    }
    if (ret != LOS_OK) {
        return ret;
    }

    if ((content->flag & RECV) == RECV) {
        ret = LiteIpcRead(content);
        if (ret != LOS_OK) {
            PRINT_ERR("LiteIpcRead failed\n");
            return ret;
        }
        UINT32 offset = LOS_OFF_SET_OF(IpcContent, inMsg);
        ret = copy_to_user((char*)con + offset, (char*)content + offset, sizeof(IpcMsg *));
        if (ret != LOS_OK) {
            PRINT_ERR("%s, %d, %d\n", __FUNCTION__, __LINE__, ret);
            return -EINVAL;
        }
    }
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 HandleCmsCmd(CmsCmdContent *content)
{
    UINT32 ret = LOS_OK;
    CmsCmdContent localContent;
    if (content == NULL) {
        return -EINVAL;
    }
    if (IsCmsTask(LOS_CurTaskIDGet()) == FALSE) {
        return -EACCES;
    }
    if (copy_from_user((void *)(&localContent), (const void *)content, sizeof(CmsCmdContent)) != LOS_OK) {
        PRINT_ERR("%s, %d\n", __FUNCTION__, __LINE__);
        return -EINVAL;
    }
    switch (localContent.cmd) {
        case CMS_GEN_HANDLE:
            if ((localContent.taskID != 0) && (IsTaskAlive(localContent.taskID) == FALSE)) {
                return -EINVAL;
            }
            ret = GenerateServiceHandle(localContent.taskID, HANDLE_REGISTED, &(localContent.serviceHandle));
            if (ret == LOS_OK) {
                ret = copy_to_user((void *)content, (const void *)(&localContent), sizeof(CmsCmdContent));
            }
            AddServiceAccess(g_cmsTask.taskID, localContent.serviceHandle);
            break;
        case CMS_REMOVE_HANDLE:
            if (localContent.serviceHandle >= MAX_SERVICE_NUM) {
                return -EINVAL;
            }
            RefreshServiceHandle(localContent.serviceHandle, -1);
            break;
        case CMS_ADD_ACCESS:
            if (IsTaskAlive(localContent.taskID) == FALSE) {
                return -EINVAL;
            }
            return AddServiceAccess(localContent.taskID, localContent.serviceHandle);
        default:
            PRINT_DEBUG("Unknow cmd cmd:%d\n", localContent.cmd);
            return -EINVAL;
    }
    return ret;
}

LITE_OS_SEC_TEXT int LiteIpcIoctl(FAR struct file *filep, int cmd, unsigned long arg)
{
    UINT32 ret = LOS_OK;
    if (IsPoolMapped() == FALSE) {
        PRINT_ERR("Ipc pool not init, need to mmap first!\n");
        return -ENOMEM;
    }
    switch (cmd) {
        case IPC_SET_CMS:
            return SetCms(arg);
        case IPC_CMS_CMD:
            return HandleCmsCmd((CmsCmdContent *)(UINTPTR)arg);
        case IPC_SET_IPC_THREAD:
            if (IsCmsSet() == FALSE) {
                PRINT_ERR("ServiceManager not set!\n");
                return -EINVAL;
            }
            return SetIpcTask();
        case IPC_SEND_RECV_MSG:
            if (arg == 0) {
                return -EINVAL;
            }
            if (IsCmsSet() == FALSE) {
                PRINT_ERR("ServiceManager not set!\n");
                return -EINVAL;
            }
            ret = LiteIpcMsgHandle((IpcContent *)(UINTPTR)arg);
            if (ret != LOS_OK) {
                return ret;
            }
            break;
        default:
            PRINT_ERR("Unknow liteipc ioctl cmd:%d\n", cmd);
            return -EINVAL;
    }
    return ret;
}
