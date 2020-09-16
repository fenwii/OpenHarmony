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

#include "agent.h"
#include <securec.h>
#include "cmdmonitor.h"
#include "mailbox_mempool.h"
#include "smc.h"
#include "tc_client_sub_driver.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"
#include "tzdriver_compat.h"

#define HASH_FILE_MAX_SIZE         (16 * 1024)
#define AGENT_BUFF_SIZE            (4 * 1024)
#define AGENT_MAX                  32
#define MAX_PATH_SIZE              512
#define PAGE_ORDER_RATIO           2

/* kernel agent, TeeAgentKernelOps list */
static struct list_head g_teeAgentList;

struct AgentControl {
    spinlock_t lock;
    struct list_head agentList; /* SmcEventData list */
};
static struct AgentControl g_agentControl;

typedef struct TagCaInfo {
    char path[MAX_PATH_SIZE];
    uint32_t uid;
    uint32_t agentId;
} CaInfo;

static CaInfo g_allowedExtAgentCa[] = {
    /* just for test in ENG version */
#ifdef DEF_ENG
    {
        "/vendor/bin/tee_test_agent",
        0,
        TEE_SECE_AGENT_ID,
    },

#endif
};

static int IsAllowedAgentCa(const CaInfo *ca, bool checkAgentIdFlag)
{
    uint32_t i;
    bool tmpCheckStatus = false;
    CaInfo *tmpCa = g_allowedExtAgentCa;

    if (!checkAgentIdFlag) {
        for (i = 0; i < ARRAY_SIZE(g_allowedExtAgentCa); i++) {
            if ((memcmp(ca->path, tmpCa->path, MAX_PATH_SIZE) == EOK) &&
                (ca->uid == tmpCa->uid)) {
                return AGENT_SUCCESS;
            }
            tmpCa++;
        }
    } else {
        for (i = 0; i < ARRAY_SIZE(g_allowedExtAgentCa); i++) {
            tmpCheckStatus = ((memcmp(ca->path, tmpCa->path, MAX_PATH_SIZE) == EOK) &&
                (ca->uid == tmpCa->uid) && (ca->agentId == tmpCa->agentId));
            if (tmpCheckStatus) {
                return AGENT_SUCCESS;
            }
            tmpCa++;
        }
    }
    tlogd("ca-uid is %u, ca_path is %s, agent id is %x\n", ca->uid, ca->path, ca->agentId);
    return AGENT_FALSE;
}

static int GetCaPathAndUid(LosTaskCB *caTask, CaInfo *ca)
{
    char *path = NULL;
    int messageSize;
    int ret = -1;
    char *tPath = NULL;

    tPath = malloc(MAX_PATH_SIZE);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)tPath)) {
        tloge("tPath malloc fail\n");
        return -EPERM;
    }

    path = GetProcessPath(caTask, tPath, MAX_PATH_SIZE);
    if (IS_ERR_OR_NULL(path)) {
        ret = -ENOMEM;
        tloge("get process path failed\n");
        goto END;
    }

    messageSize = snprintf_s(ca->path, MAX_PATH_SIZE - 1, MAX_PATH_SIZE - 1, "%s", path);
    ca->uid = GetTaskUid(caTask);
    if (ca->uid < 0) {
        free(tPath);
        tPath = NULL;
        return -EPERM;
    }
    tlogd("caTask->comm is %s, path is %s, ca uid is %u\n", caTask->taskName, path, ca->uid);

    if (messageSize > 0) {
        ret = 0;
    }

END:
    free(tPath);
    tPath = NULL;
    return ret;
}

int CheckExtAgentAccess(LosTaskCB *caTask)
{
    int ret;
    CaInfo agentCa = { {0}, 0 };

    if (caTask == NULL) {
        tloge("caTask is NULL.\n");
        return -EPERM;
    }

    ret = GetCaPathAndUid(caTask, &agentCa);
    if (ret) {
        tloge("get cp path or uid failed.\n");
        return ret;
    }

    ret = IsAllowedAgentCa(&agentCa, 0);
    return ret;
}

int CheckExtAgentAccessWithAgentId(LosTaskCB *caTask,
    uint32_t agentId)
{
    int ret;
    CaInfo agentCa = {"", 0, 0};

    if (caTask == NULL) {
        tloge("caTask is NULL\n");
        return -EPERM;
    }

    ret = GetCaPathAndUid(caTask, &agentCa);
    if (ret) {
        tloge("get cp path or uid failed\n");
        return ret;
    }
    agentCa.agentId = agentId;
    ret = IsAllowedAgentCa(&agentCa, 1);
    return ret;
}

static int CheckNativeHashParam(uint8_t *inBuf, uint32_t *bufLen)
{
    if (inBuf == NULL) {
        return AGENT_FALSE;
    }
    if (TcNsGetUid() != 0) {
        tloge("It is a fake tee agent\n");
        return -EACCES;
    }
    if (copy_from_user(bufLen, inBuf, sizeof(*bufLen))) {
        tloge("copy from user failed\n");
        return -EFAULT;
    }
    if (*bufLen > HASH_FILE_MAX_SIZE) {
        tloge("ERROR: file size[0x%x] too big\n", *bufLen);
        return AGENT_FALSE;
    }
    return 0;
}

int TcNsSetNativeHash(unsigned long arg, unsigned int cmdId)
{
    int ret;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    uint8_t *inBuf = (uint8_t *)(uintptr_t)arg;
    uint32_t bufLen = 0;
    uint8_t *bufToTee = NULL;
    struct MbCmdPack *mbPack = NULL;

    ret = CheckNativeHashParam(inBuf, &bufLen);
    if (ret) {
        return ret;
    }

    bufToTee = MailboxAlloc(bufLen, 0);
    if (bufToTee == NULL) {
        tloge("failed to alloc memory!\n");
        return AGENT_FALSE;
    }
    if (copy_from_user(bufToTee, inBuf, bufLen)) {
        tloge("copy from user failed\n");
        MailboxFree(bufToTee);
        return -EFAULT;
    }
    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc cmd pack failed\n");
        MailboxFree(bufToTee);
        return -ENOMEM;
    }
    mbPack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT |
        (TEE_PARAM_TYPE_VALUE_INPUT << TEE_PARAM_NUM);
    mbPack->operation.params[TEE_PARAM_ONE].value.a =
        (unsigned int)LOS_PaddrQuery(bufToTee);
    mbPack->operation.params[TEE_PARAM_ONE].value.b = 0;
    mbPack->operation.params[TEE_PARAM_TWO].value.a = bufLen;
    smcCmd.globalCmd = true;
    smcCmd.cmdId = cmdId;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    ret = TcNsSmc(&smcCmd);
    MailboxFree(bufToTee);
    MailboxFree(mbPack);
    bufToTee = NULL;
    mbPack = NULL;
    return ret;
}

int TcNsLateInit(unsigned long arg)
{
    int ret;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    uint32_t index = (uint32_t)arg; // index is uint32, no truncate risk
    struct MbCmdPack *mbPack = NULL;

    if (TcNsGetUid() != 0) {
        tloge("It is a fake tee agent\n");
        return -EACCES;
    }

    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc cmd pack failed\n");
        return -ENOMEM;
    }

    mbPack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT;
    mbPack->operation.params[TEE_PARAM_ONE].value.a = index;

    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_LATE_INIT;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;

    ret = TcNsSmc(&smcCmd);

    MailboxFree(mbPack);
    mbPack = NULL;

    return ret;
}

void SendEventResponseSingle(const TcNsDevFile *devFile)
{
    struct SmcEventData *eventData = NULL;
    struct SmcEventData *tmp = NULL;
    unsigned long flags;
    unsigned int agentId = 0;

    if (devFile == NULL) {
        return;
    }

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry_safe(eventData, tmp, &g_agentControl.agentList, head) {
        if (eventData->owner == devFile) {
            agentId = eventData->agentId;
            break;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);
    SendEventResponse(agentId);
    return;
}

struct SmcEventData *FindEventControl(unsigned int agentId)
{
    struct SmcEventData *eventData = NULL;
    struct SmcEventData *tmpData = NULL;
    unsigned long flags;

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry(eventData, &g_agentControl.agentList, head) {
        if (eventData->agentId == agentId) {
            tmpData = eventData;
            GetAgentEvent(eventData);
            break;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);

    return tmpData;
}

static void UnmapAgentBuffer(struct SmcEventData *eventData)
{
    if (eventData == NULL) {
        tloge("event data is NULL\n");
        return;
    }

    if (IS_ERR_OR_NULL(eventData->agentBuffUser)) {
        return;
    }

    if (LOS_UnMMap((VADDR_T)eventData->agentBuffUser, eventData->agentBuffSize) != 0) {
        tloge("unmap failed\n");
    }

    eventData->agentBuffUser = NULL;
}

static void FreeEventControl(unsigned int agentId)
{
    struct SmcEventData *eventData = NULL;
    struct SmcEventData *tmpEvent = NULL;
    unsigned long flags;
    bool find = false;

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry_safe(eventData, tmpEvent, &g_agentControl.agentList, head) {
        if (eventData->agentId == agentId) {
            list_del(&eventData->head);
            find = true;
            break;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);

    if (find) {
        UnmapAgentBuffer(eventData);

        MailboxFree(eventData->agentBuffKernel);
        eventData->agentBuffKernel = NULL;
        PutAgentEvent(eventData);
    }
}

static int InitAgentContext(unsigned int agentId,
    const TcNsSmcCmd *smcCmd,
    struct SmcEventData **eventData)
{
    if (eventData == NULL) {
        return TEEC_ERROR_GENERIC;
    }
    *eventData = FindEventControl(agentId);
    if (*eventData == NULL) {
        tloge("agent %u not exist\n", agentId);
        return TEEC_ERROR_GENERIC;
    }
    tlogd("AgentProcessWork(0x%x): returning client command", agentId);

#ifndef CONFIG_TEE_SMP
    /* Keep a copy of the SMC cmd to return to TEE when the work is done */
    if (memcpy_s(&((*eventData)->cmd), sizeof((*eventData)->cmd), smcCmd, sizeof(*smcCmd))) {
        tloge("failed to memcpy_s smcCmd\n");
        PutAgentEvent(*eventData);
        return TEEC_ERROR_GENERIC;
    }
    ISB;
    DSB;
#endif
    return TEEC_SUCCESS;
}

static int WaitAgentResponse(struct SmcEventData *eventData)
{
    int ret = TEEC_SUCCESS;
    bool answered = true;

    do {
        answered = true;
        int r = wait_event_interruptible_timeout(eventData->caPendingWq,
            atomic_read(&eventData->caRun), (long)(RESLEEP_TIMEOUT * HZ));
        if (r != 0) {
            continue;
        }
        /* if no kill signal, just resleep before agent wake */
        if (SigkillPending(OsCurrTaskGet()) == 0) {
            answered = false;
        } else {
            tloge("CA is killed, no need to wait agent response\n");
            eventData->retFlag = 0;
            ret = TEEC_ERROR_GENERIC;
        }
    } while (!answered);

    return ret;
}

int AgentProcessWork(const TcNsSmcCmd *smcCmd, unsigned int agentId)
{
    struct SmcEventData *eventData = NULL;
    int ret;

    if (smcCmd == NULL) {
        tloge("smcCmd is null\n");
        return TEEC_ERROR_GENERIC;
    }
    if (InitAgentContext(agentId, smcCmd, &eventData) != TEEC_SUCCESS) {
        return TEEC_ERROR_GENERIC;
    }

#ifdef CONFIG_TEE_SMP
    if (atomic_read(&eventData->agentReady) == AGENT_CRASHED) {
        tloge("agent 0x%x is killed and restarting\n", agentId);
        PutAgentEvent(eventData);
        return TEEC_ERROR_GENERIC;
    }
    eventData->retFlag = 1;
    /* Wake up the agent that will process the command */
    tlogd("AgentProcessWork: wakeup the agent");
    wake_up(&eventData->waitEventWq);
    tlogd("agent 0x%x request, goto sleep, pe->run=%d\n",
          agentId, atomic_read(&eventData->caRun));

    ret = WaitAgentResponse(eventData);
    atomic_set(&eventData->caRun, 0);
#endif

    PutAgentEvent(eventData);
    /*
     * when agent work is done, reset cmd monitor time
     * add agent call count, cause it's a new smc cmd.
     */
    CmdMonitorResetContext();
    return ret;
}

int IsAgentAlive(unsigned int agentId)
{
    struct SmcEventData *eventData = NULL;

    eventData = FindEventControl(agentId);
    if (eventData != NULL) {
        PutAgentEvent(eventData);
        return AGENT_ALIVE;
    } else {
        return AGENT_DEAD;
    }
}

int TcNsWaitEvent(unsigned int agentId)
{
    int ret = -EINVAL;
    struct SmcEventData *eventData = NULL;

    if ((TcNsGetUid() != 0) &&
        CheckExtAgentAccessWithAgentId(OsCurrTaskGet(), agentId)) {
        tloge("It is a fake tee agent\n");
        return -EACCES;
    }
    tlogd("agent %u waits for command\n", agentId);
    eventData = FindEventControl(agentId);
    if (eventData != NULL) {
        /* only when agent wait event, it's in ready state to work */
        atomic_set(&(eventData->agentReady), AGENT_READY);
        ret = wait_event_interruptible(eventData->waitEventWq, eventData->retFlag);
        PutAgentEvent(eventData);
    }

    return ret;
}

int TcNsSyncSysTime(const TcNsClientTime *tcNsTime)
{
    TcNsSmcCmd smcCmd = { {0}, 0 };
    int ret;
    TcNsClientTime tmpTcNsTime = {0};
    struct MbCmdPack *mbPack = NULL;

    if (tcNsTime == NULL) {
        tloge("tcNsTime is NULL input buffer\n");
        return -EINVAL;
    }
    if (TcNsGetUid() != 0) {
        tloge("It is a fake tee agent\n");
        return TEEC_ERROR_GENERIC;
    }
    if (copy_from_user(&tmpTcNsTime, tcNsTime,
        sizeof(tmpTcNsTime))) {
        tloge("copy from user failed\n");
        return -EFAULT;
    }

    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc mb pack failed\n");
        return -ENOMEM;
    }

    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_ADJUST_TIME;
    smcCmd.errOrigin = tmpTcNsTime.seconds;
    smcCmd.retVal = (int)tmpTcNsTime.millis;

    ret = TcNsSmc(&smcCmd);
    if (ret) {
        tloge("tee adjust time failed, return error %x\n", ret);
    }

    MailboxFree(mbPack);
    mbPack = NULL;

    return ret;
}

static struct SmcEventData *CheckForSendEventResponse(unsigned int agentId)
{
    struct SmcEventData *eventData = FindEventControl(agentId);
    bool tmpCheckStatus = false;

    if (eventData == NULL) {
        tloge("Can't get eventData\n");
        return NULL;
    }
    tmpCheckStatus = ((TcNsGetUid() != 0) &&
        CheckExtAgentAccessWithAgentId(OsCurrTaskGet(), agentId));
    if (tmpCheckStatus) {
        tloge("It is a fake tee agent\n");
        PutAgentEvent(eventData);
        return NULL;
    }
    return eventData;
}

static int ProcessSendEventResponse(struct SmcEventData *eventData)
{
    int ret = 0;
    if (eventData->retFlag) {
        eventData->retFlag = 0;
        /* Send the command back to the TA session waiting for it */
#ifdef CONFIG_TEE_SMP
        tlogd("agent wakeup ca\n");
        atomic_set(&eventData->caRun, 1);
        /* make sure reset working_ca before wakeup CA */
        wake_up(&eventData->caPendingWq);
        ret = 0;
#else
        ret = TcNsPostSmc(&eventData->cmd);
#endif
    }
    return ret;
}

int TcNsSendEventResponse(unsigned int agentId)
{
    struct SmcEventData *eventData = NULL;
    int ret;

    eventData = CheckForSendEventResponse(agentId);
    if (eventData == NULL) {
        tlogd("agent %u pre-check failed\n", agentId);
        return -1;
    }
    tlogd("agent %u sends answer back\n", agentId);
    ret = ProcessSendEventResponse(eventData);
    PutAgentEvent(eventData);
    return ret;
}

void SendEventResponse(unsigned int agentId)
{
    struct SmcEventData *eventData = FindEventControl(agentId);
    int ret;

    if (eventData == NULL) {
        tloge("Can't get eventData\n");
        return;
    }

    tloge("agent 0x%x sends answer back\n", agentId);
    atomic_set(&eventData->agentReady, AGENT_CRASHED);
    ret = ProcessSendEventResponse(eventData);
    PutAgentEvent(eventData);
    if (ret) {
        tloge("agent 0x%x sends answer back failed\n", agentId);
    }
    return;
}

static void InitEventDataForRestart(TcNsDevFile *devFile,
    struct SmcEventData *eventData)
{
    eventData->retFlag = 0;
    eventData->owner = devFile;
    atomic_set(&eventData->agentReady, AGENT_REGISTERED);
    init_waitqueue_head(&(eventData->waitEventWq));
    init_waitqueue_head(&(eventData->sendResponseWq));
#ifdef CONFIG_TEE_SMP
    init_waitqueue_head(&(eventData->caPendingWq));
    atomic_set(&(eventData->caRun), 0);
#endif
    return;
}

static int AllocAndInitEventData(TcNsDevFile *devFile,
    struct SmcEventData **eventData, unsigned int agentId,
    UINTPTR *agentBuff, uint32_t agentBuffSize)
{
    *agentBuff = (UINTPTR)MailboxAlloc(agentBuffSize, MB_FLAG_ZERO);
    if (*agentBuff == 0) {
        tloge("alloc agent buff failed\n");
        return -ENOMEM;
    }
    *eventData = calloc(1, sizeof(**eventData));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*eventData))) {
        MailboxFree((void *)*agentBuff);
        *agentBuff = 0;
        *eventData = NULL;
        tloge("alloc event data failed\n");
        return -ENOMEM;
    }
    (*eventData)->agentId = agentId;
    (*eventData)->retFlag = 0;
    (*eventData)->agentBuffKernel = (void *)*agentBuff;
    (*eventData)->agentBuffSize = agentBuffSize;
    (*eventData)->owner = devFile;
    atomic_set(&(*eventData)->agentReady, AGENT_REGISTERED);
    init_waitqueue_head(&(*eventData)->waitEventWq);
    init_waitqueue_head(&(*eventData)->sendResponseWq);
    INIT_LIST_HEAD(&(*eventData)->head);
#ifdef CONFIG_TEE_SMP
    init_waitqueue_head(&(*eventData)->caPendingWq);
    atomic_set(&(*eventData)->caRun, 0);
#endif
    return TEEC_SUCCESS;
}

static bool IsBuiltInAgent(unsigned int agentId)
{
    bool checkValue = false;

    checkValue = ((agentId == AGENT_FS_ID) ||
        (agentId == AGENT_MISC_ID) ||
        (agentId == AGENT_SOCKET_ID) ||
        (agentId == SECFILE_LOAD_AGENT_ID));
    return checkValue;
}

static unsigned long AgentBufferMap(unsigned long buffer, uint32_t size)
{
    int ret;

    if (!IS_PAGE_ALIGNED(buffer) || !IS_PAGE_ALIGNED(size)) {
        return -EFAULT;
    }

    vaddr_t userAddr = LOS_MMap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (IS_ERR_OR_NULL(userAddr)) {
        goto ERR_OUT;
    }

    for (int i = 0; i < (size >> PAGE_SHIFT); i++) {
        LosVmPage *page = LOS_VmPageGet(buffer + PAGE_SIZE * i);
        if (page == NULL) {
            goto ERR_OUT;
        }
        LOS_AtomicInc(&page->refCounts);
    }

    // agent buffer page is physically contiguous, so can entirety mmap
    ret = remap_pfn_range(userAddr, buffer >> PAGE_SHIFT, size,
        VM_MAP_REGION_FLAG_PERM_USER | VM_MAP_REGION_FLAG_PERM_READ | VM_MAP_REGION_FLAG_PERM_WRITE);
    if (ret) {
        tloge("remap agent buffer failed, err=%d", ret);
        goto ERR_OUT;
    }
    return userAddr;

ERR_OUT:
    if (LOS_UnMMap(userAddr, size) != 0) {
        tloge("munmap failed\n");
    }
    return -EFAULT;
}

static bool IsValidAgent(unsigned int agentId,
    unsigned int bufferSize, bool userAgent)
{
    if (TcNsGetUid() != 0 &&
        CheckExtAgentAccessWithAgentId(OsCurrTaskGet(), agentId)) {
        tloge("It is a fake tee agent\n");
        return false;
    }

    if (userAgent && (bufferSize > SZ_4K)) {
        tloge("size: %u of user agent's shared mem is invalid\n",
            bufferSize);
        return false;
    }
    return true;
}

static void IsAgentAlreadyExist(unsigned int agentId,
    struct SmcEventData **eventData, bool *findFlag)
{
    unsigned long flags;
    bool flag = false;
    struct SmcEventData *agentNode = NULL;

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry(agentNode, &g_agentControl.agentList, head) {
        if (agentNode->agentId == agentId) {
            flag = true;
            GetAgentEvent(agentNode);
            break;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);
    *findFlag = flag;
    if (flag == true) {
        *eventData = agentNode;
    }
    return;
}

static void AddEventNodeToList(struct SmcEventData *eventData)
{
    unsigned long flags;
    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_add_tail(&eventData->head, &g_agentControl.agentList);
    atomic_set(&eventData->usage, 1);
    spin_unlock_irqrestore(&g_agentControl.lock, flags);
    return;
}

static int RegisterAgentToTee(unsigned int agentId, UINTPTR agentBuff,
    uint32_t agentBuffSize)
{
    int ret;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    struct MbCmdPack *mbPack = NULL;

    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc mailbox failed\n");
        return AGENT_FALSE;
    }

    mbPack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT |
        (TEE_PARAM_TYPE_VALUE_INPUT << TEE_PARAM_NUM);
    mbPack->operation.params[TEE_PARAM_ONE].value.a =
        LOS_PaddrQuery((void *)agentBuff);
    mbPack->operation.params[TEE_PARAM_ONE].value.b = 0;
    mbPack->operation.params[TEE_PARAM_TWO].value.a = agentBuffSize;
    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_REGISTER_AGENT;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    smcCmd.agentId = agentId;

    ret = TcNsSmc(&smcCmd);
    /* mbPack should be released no matter what ret is */
    MailboxFree(mbPack);
    mbPack = NULL;

    return ret;
}

static void ReleaseAgentResource(bool findFlag, struct SmcEventData *eventData, UINTPTR agentBuff)
{
    if (findFlag) {
        PutAgentEvent(eventData); // match get action
    } else {
        free(eventData); // here eventData can never be NULL;
    }

    if (agentBuff != 0) {
        MailboxFree((void *)agentBuff);
    }
}

int TcNsRegisterAgent(TcNsDevFile *devFile, unsigned int agentId,
    unsigned int bufferSize, void **buffer, bool userAgent)
{
    struct SmcEventData *eventData = NULL;
    bool findFlag = false;
    UINTPTR agentBuff = 0;
    uint32_t sizeAlign;

    if (buffer == NULL || devFile == NULL) {
        return TEEC_ERROR_GENERIC;
    }

    if (IsValidAgent(agentId, bufferSize, userAgent) != true) {
        return TEEC_ERROR_GENERIC;
    }

    sizeAlign = ALIGN(bufferSize, SZ_4K);

    IsAgentAlreadyExist(agentId, &eventData, &findFlag);
    /*
     * We find the agent's eventData aready in agentList, it indicate agent
     * didn't unregister normally, so the eventData will be reused.
     */
    if (findFlag) {
        InitEventDataForRestart(devFile, eventData);
    } else {
        if (AllocAndInitEventData(devFile, &eventData,
            agentId, &agentBuff, sizeAlign) != TEEC_SUCCESS) {
            return TEEC_ERROR_GENERIC;
        }
    }

    /* if the agent is first time or restart register, both case need a remap */
    if (userAgent) {
        eventData->agentBuffUser = (void *)(uintptr_t)AgentBufferMap(
            LOS_PaddrQuery(eventData->agentBuffKernel),
            eventData->agentBuffSize);
        if (IS_ERR(eventData->agentBuffUser)) {
            tloge("vm map agent buffer failed\n");
            goto RELEASE_RSRC;
        }
        *buffer = eventData->agentBuffUser;
    } else {
        *buffer = eventData->agentBuffKernel;
    }

    /* findFlag is false means it's a new agent register */
    if (findFlag == false) {
        /* Obtain share memory which is released in TcNsUnregisterAgent */
        if (RegisterAgentToTee(agentId, agentBuff, sizeAlign) != TEEC_SUCCESS) {
            UnmapAgentBuffer(eventData);
            goto RELEASE_RSRC;
        }
        AddEventNodeToList(eventData);
    }
    if (findFlag) {
        PutAgentEvent(eventData); // match get action
    }
    return TEEC_SUCCESS;
RELEASE_RSRC:
    ReleaseAgentResource(findFlag, eventData, agentBuff);
    return TEEC_ERROR_GENERIC;
}

static int CheckForUnregisterAgent(unsigned int agentId)
{
    bool checkValue = false;

    checkValue = (TcNsGetUid() != 0);
    if (checkValue) {
        tloge("It is a fake tee agent\n");
        return TEEC_ERROR_GENERIC;
    }

    checkValue = (IsBuiltInAgent(agentId) ||
        agentId == TEE_RPMB_AGENT_ID);
    if (checkValue) {
        tloge("agent: 0x%x is not allowed to unregister\n", agentId);
        return TEEC_ERROR_GENERIC;
    }
    return TEEC_SUCCESS;
}

static bool IsThirdPartyAgent(unsigned int agentId)
{
    uint32_t i;
    CaInfo *tmpCa = g_allowedExtAgentCa;

    for (i = 0; i < ARRAY_SIZE(g_allowedExtAgentCa); i++) {
        if (tmpCa->agentId == agentId) {
            return true;
        }
        tmpCa++;
    }

    return false;
}

int TcNsUnregisterAgent(unsigned int agentId)
{
    struct SmcEventData *eventData = NULL;
    int ret;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    struct MbCmdPack *mbPack = NULL;

    if (CheckForUnregisterAgent(agentId) != TEEC_SUCCESS) {
        return TEEC_ERROR_GENERIC;
    }
    /* if third party itself trigger unregister agent
     * we allow them to unregister.
     */
    if (IsThirdPartyAgent(agentId) != true) {
        tloge("invalid agent id: 0x%x\n", agentId);
        return TEEC_ERROR_GENERIC;
    }

    eventData = FindEventControl(agentId);
    if (eventData == NULL || eventData->agentBuffKernel == NULL) {
        tloge("agent is not found or kernelAddr is not allocated\n");
        return TEEC_ERROR_GENERIC;
    }

    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc mailbox failed\n");
        PutAgentEvent(eventData);
        return TEEC_ERROR_GENERIC;
    }
    mbPack->operation.paramTypes = TEE_PARAM_TYPE_VALUE_INPUT |
        (TEE_PARAM_TYPE_VALUE_INPUT << TEE_PARAM_NUM);
    mbPack->operation.params[TEE_PARAM_ONE].value.a =
        LOS_PaddrQuery(eventData->agentBuffKernel);

    mbPack->operation.params[TEE_PARAM_ONE].value.b = 0;
    mbPack->operation.params[TEE_PARAM_TWO].value.a = SZ_4K;
    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_UNREGISTER_AGENT;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;

    smcCmd.agentId = agentId;
    tlogd("Unregistering agent 0x%x\n", agentId);
    ret = TcNsSmc(&smcCmd);
    if (ret == TEEC_SUCCESS) {
        FreeEventControl(agentId);
    }
    PutAgentEvent(eventData);
    MailboxFree(mbPack);
    return ret;
}

bool IsSystemAgent(const TcNsDevFile *devFile)
{
    struct SmcEventData *eventData = NULL;
    struct SmcEventData *tmp = NULL;
    bool systemAgent = false;
    unsigned long flags;

    if (devFile == NULL) {
        return systemAgent;
    }

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry_safe(eventData, tmp, &g_agentControl.agentList, head) {
        if (eventData->owner == devFile) {
            systemAgent = true;
            break;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);

    return systemAgent;
}

void SendCrashedEventResponseAll(const TcNsDevFile *devFile)
{
    struct SmcEventData *eventData = NULL;
    struct SmcEventData *tmp = NULL;
    unsigned int agentId[AGENT_MAX] = {0};
    unsigned int i = 0;
    unsigned long flags;

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry_safe(eventData, tmp, &g_agentControl.agentList,
        head) {
        if ((eventData->owner == devFile) && (i < AGENT_MAX)) {
            agentId[i++] = eventData->agentId;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);

    for (i = 0; i < AGENT_MAX; i++) {
        if (agentId[i]) {
            SendEventResponse(agentId[i]);
        }
    }

    return;
}

void TeeAgentClearDevOwner(const TcNsDevFile *devFile)
{
    struct SmcEventData *eventData = NULL;
    struct SmcEventData *tmp = NULL;
    unsigned long flags;

    spin_lock_irqsave(&g_agentControl.lock, flags);
    list_for_each_entry_safe(eventData, tmp, &g_agentControl.agentList, head) {
        if (eventData->owner == devFile) {
            eventData->owner = NULL;
            break;
        }
    }
    spin_unlock_irqrestore(&g_agentControl.lock, flags);
    return;
}

static int DefTeeAgentWork(UINTPTR instance, int len)
{
    int ret = 0;
    struct TeeAgentKernelOps *agentInstance = NULL;

    if (len != sizeof(struct TeeAgentKernelOps)) {
        return ret;
    }

    agentInstance = (struct TeeAgentKernelOps *)instance;
    while (!KthreadShouldStop()) {
        tlogd("%s agent loop++++\n", agentInstance->agentName);
        ret = TcNsWaitEvent(agentInstance->agentId);
        if (ret) {
            tloge("%s wait event fail\n",
                agentInstance->agentName);
            break;
        }
        if (agentInstance->teeAgentWork != NULL) {
            ret = agentInstance->teeAgentWork(agentInstance);
            if (ret) {
                tloge("%s agent work fail\n", agentInstance->agentName);
            }
        }
        ret = TcNsSendEventResponse(agentInstance->agentId);
        if (ret) {
            tloge("%s send event response fail\n",
                agentInstance->agentName);
            break;
        }
        tlogd("%s agent loop----\n", agentInstance->agentName);
    }

    return ret;
}

static int DefTeeAgentRun(struct TeeAgentKernelOps *agentInstance)
{
    TcNsDevFile dev = {0};
    int ret;
    char agentName[OS_TCB_NAME_LEN] = {0};

    /* 1. Register agent buffer to TEE */
    ret = TcNsRegisterAgent(&dev, agentInstance->agentId,
        agentInstance->agentBuffSize, &agentInstance->agentBuff, false);
    if (ret) {
        tloge("register agent buffer fail,ret =0x%x\n", ret);
        ret = -1;
        goto OUT;
    }

    /* 2. Creat thread to run agent */
    ret = sprintf_s(agentName, OS_TCB_NAME_LEN, "agent_%s", agentInstance->agentName);
    if (ret == -1) {
        goto OUT;
    }
    agentInstance->agentThread =
        KthreadRun(DefTeeAgentWork, (void *)agentInstance, sizeof(struct TeeAgentKernelOps), agentName);
    if (IS_ERR_OR_NULL(agentInstance->agentThread)) {
        tloge("kthread create fail\n");
        ret = PTR_ERR(agentInstance->agentThread);
        agentInstance->agentThread = NULL;
        goto OUT;
    }
    return AGENT_SUCCESS;

OUT:
    return ret;
}

static int DefTeeAgentStop(struct TeeAgentKernelOps *agentInstance)
{
    int ret;

    if (TcNsSendEventResponse(agentInstance->agentId)) {
        tloge("failed to send response for agent %u\n",
            agentInstance->agentId);
    }

    ret = TcNsUnregisterAgent(agentInstance->agentId);
    if (ret != 0) {
        tloge("failed to unregister agent %u\n",
            agentInstance->agentId);
    }
    if (!IS_ERR_OR_NULL(agentInstance->agentThread)) {
        KthreadStop(agentInstance->agentThread);
    }

    return AGENT_SUCCESS;
}

/* default kernel agent ops */
static struct TeeAgentKernelOps g_defTeeAgentOps = {
    .agentName = "default",
    .agentId = 0,
    .teeAgentInit = NULL,
    .teeAgentRun = DefTeeAgentRun,
    .teeAgentWork = NULL,
    .teeAgentExit = NULL,
    .teeAgentStop = DefTeeAgentStop,
    .teeAgentCrashWork = NULL,
    .agentBuffSize = PAGE_SIZE,
    .list = LINUX_LIST_HEAD_INIT(g_defTeeAgentOps.list)
};

static int TeeAgentKernelInit(void)
{
    struct TeeAgentKernelOps *agentOps = NULL;
    int ret = 0;
    bool tmpCheckStatus = false;

    list_for_each_entry(agentOps, &g_teeAgentList, list) {
        /* Check the agent validity */
        tmpCheckStatus = ((agentOps->agentId == 0) ||
            (agentOps->agentName == NULL) ||
            (agentOps->teeAgentWork == NULL));
        if (tmpCheckStatus) {
            tloge("agent is invalid\n");
            continue;
        }
        tlogd("ready to init %s agent, id=0x%x\n",
            agentOps->agentName, agentOps->agentId);

        /* Set agent buff size */
        if (agentOps->agentBuffSize == 0) {
            agentOps->agentBuffSize = g_defTeeAgentOps.agentBuffSize;
        }

        /* Initialize the agent */
        if (agentOps->teeAgentInit != NULL) {
            ret = agentOps->teeAgentInit(agentOps);
        } else if (g_defTeeAgentOps.teeAgentInit != NULL) {
            ret = g_defTeeAgentOps.teeAgentInit(agentOps);
        } else {
            tlogw("agent id %u has no init function\n",
                agentOps->agentId);
        }
        if (ret) {
            tloge("teeAgentInit %s failed\n",
                agentOps->agentName);
            continue;
        }

        /* Run the agent */
        if (agentOps->teeAgentRun != NULL) {
            ret = agentOps->teeAgentRun(agentOps);
        } else if (g_defTeeAgentOps.teeAgentRun != NULL) {
            ret = g_defTeeAgentOps.teeAgentRun(agentOps);
        } else {
            tlogw("agent id %u has no run function\n",
                agentOps->agentId);
        }
        if (ret) {
            tloge("teeAgentRun %s failed\n",
                agentOps->agentName);
            if (agentOps->teeAgentExit != NULL) {
                agentOps->teeAgentExit(agentOps);
            }
            continue;
        }
    }

    return AGENT_SUCCESS;
}

static void TeeAgentKernelExit(void)
{
    struct TeeAgentKernelOps *agentOps = NULL;

    list_for_each_entry(agentOps, &g_teeAgentList, list) {
        /* Stop the agent */
        if (agentOps->teeAgentStop != NULL) {
            agentOps->teeAgentStop(agentOps);
        } else if (g_defTeeAgentOps.teeAgentStop != NULL) {
            g_defTeeAgentOps.teeAgentStop(agentOps);
        } else {
            tlogw("agent id %u has no stop function\n",
                agentOps->agentId);
        }
        /* Uninitialize the agent */
        if (agentOps->teeAgentExit != NULL) {
            agentOps->teeAgentExit(agentOps);
        } else if (g_defTeeAgentOps.teeAgentExit != NULL) {
            g_defTeeAgentOps.teeAgentExit(agentOps);
        } else {
            tlogw("agent id %u has no exit function\n",
                agentOps->agentId);
        }
    }
}

int TeeAgentClearWork(TcNsClientContext *context,
    unsigned int devFileId)
{
    struct TeeAgentKernelOps *agentOps = NULL;

    list_for_each_entry(agentOps, &g_teeAgentList, list) {
        if (agentOps->teeAgentCrashWork != NULL) {
            agentOps->teeAgentCrashWork(agentOps,
                context, devFileId);
        }
    }
    return AGENT_SUCCESS;
}

/* register kernel agent, for TeeAgentKernelInit load */
int TeeAgentKernelRegister(struct TeeAgentKernelOps *newAgent)
{
    if (newAgent == NULL) {
        return AGENT_FALSE;
    }
    INIT_LIST_HEAD(&newAgent->list);
    list_add_tail(&newAgent->list, &g_teeAgentList);
    return AGENT_SUCCESS;
}

void AgentInit(void)
{
    spin_lock_init(&g_agentControl.lock);
    INIT_LIST_HEAD(&g_agentControl.agentList);
    INIT_LIST_HEAD(&g_teeAgentList);

    if (TeeAgentKernelInit() != AGENT_SUCCESS) {
        tloge("tee agent kernel init failed\n");
    }

    return;
}

int AgentExit(void)
{
    TeeAgentKernelExit();
    return AGENT_SUCCESS;
}
