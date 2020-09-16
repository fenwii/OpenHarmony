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

#include "tz_spi_notify.h"
#include <securec.h>
#include "gp_ops.h"
#include "mailbox_mempool.h"
#include "smc.h"
#include "tc_client_driver.h"
#include "tc_client_sub_driver.h"
#include "tc_ns_client.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"

#define MAX_CALLBACK_COUNT 100
#define UUID_SIZE 16
struct TeecTimerProperty;

#ifdef DEF_ENG
static int g_timerType;
#endif

enum TimerClassType {
    /* timer event using timer10 */
    TIMER_GENERIC,
    /* timer event using RTC */
    TIMER_RTC
};

struct TeecTimerProperty {
    unsigned int type;
    unsigned int timerId;
    unsigned int timerClass;
    unsigned int reserved2;
};

struct NotifyContextTimer {
    unsigned int devFileId;
    unsigned char uuid[UUID_SIZE];
    unsigned int sessionId;
    struct TeecTimerProperty property;
    uint32_t expireTime;
};

#ifdef CONFIG_TEE_SMP
struct NotifyContextWakeup {
    pid_t caThreadId;
};

struct NotifyContextShadow {
    uint64_t targetTcb;
};

struct NotifyContextStats {
    uint32_t sends;
    uint32_t recvs;
    uint32_t sendw;
    uint32_t recvw;
    uint32_t missed;
};
#endif

union NotifyContext {
    struct NotifyContextTimer timer;
#ifdef CONFIG_TEE_SMP
    struct NotifyContextWakeup wakeup;
    struct NotifyContextShadow shadow;
    struct NotifyContextStats  meta;
#endif
};

struct NotifyDataEntry {
    uint32_t entryType : 31;
    uint32_t filled     : 1;
    union NotifyContext context;
};

#define NOTIFY_DATA_ENTRY_COUNT \
    ((PAGE_SIZE / sizeof(struct NotifyDataEntry)) - 1)
struct NotifyDataStruct {
    struct NotifyDataEntry entry[NOTIFY_DATA_ENTRY_COUNT];
    struct NotifyDataEntry meta;
};

static struct NotifyDataStruct *g_notifyData = NULL;
static struct NotifyDataEntry *g_notifyDataEntryTimer = NULL;
static struct NotifyDataEntry *g_notifyDataEntryRtc = NULL;
#ifdef CONFIG_TEE_SMP
static struct NotifyDataEntry *g_notifyDataEntryShadow = NULL;
#endif

enum NotifyDataType {
    NOTIFY_DATA_ENTRY_UNUSED,
    NOTIFY_DATA_ENTRY_TIMER,
    NOTIFY_DATA_ENTRY_RTC,
#ifdef CONFIG_TEE_SMP
    NOTIFY_DATA_ENTRY_WAKEUP,
    NOTIFY_DATA_ENTRY_SHADOW,
    NOTIFY_DATA_ENTRY_FIQSHD,
    NOTIFY_DATA_ENTRY_SHADOW_EXIT,
#endif
    NOTIFY_DATA_ENTRY_MAX,
};

struct TcNsCallback {
    unsigned char uuid[UUID_SIZE];
    mutex_t callbackLock;
    void (*callbackFunc)(void *);
    struct list_head head;
};

struct TcNsCallbackList {
    unsigned int callbackCount;
    mutex_t callbackListLock;
    struct list_head callbackList;
};

static void TcNotifyFn(struct work_struct *dummy);
static struct TcNsCallbackList g_taCallbackFuncList;
static DECLARE_WORK(tc_notify_work, TcNotifyFn);
#ifdef CONFIG_TEE_SMP
static struct workqueue_struct *g_tzSpiWq = NULL;
#endif

static void WalkCallbackList(struct NotifyContextTimer *tcNotifyDataTimer)
{
    struct TcNsCallback *callbackFuncT = NULL;

    mutex_lock(&g_taCallbackFuncList.callbackListLock);
    list_for_each_entry(callbackFuncT,
        &g_taCallbackFuncList.callbackList, head) {
        if (memcmp(callbackFuncT->uuid, tcNotifyDataTimer->uuid,
            UUID_SIZE) == 0) {
            if (tcNotifyDataTimer->property.timerClass == TIMER_RTC) {
                tlogd("start to call callback func\n");
                callbackFuncT->callbackFunc(
                    (void *)(&(tcNotifyDataTimer->property)));
                tlogd("end to call callback func\n");
            } else if (tcNotifyDataTimer->property.timerClass == TIMER_GENERIC) {
                tlogd("timer60 no callback func\n");
            }
        }
    }
    mutex_unlock(&g_taCallbackFuncList.callbackListLock);
}

static void TcNotifyTimerFn(struct NotifyDataEntry *notifyDataEntry)
{
    TcNsDevFile *tempDevFile = NULL;
    TcNsService *tempSvc = NULL;
    TcNsSession *tempSes = NULL;
    int encFound = 0;
    struct NotifyContextTimer *tcNotifyDataTimer = NULL;

    tcNotifyDataTimer = &(notifyDataEntry->context.timer);
    notifyDataEntry->filled = 0;
    tlogd("notify_data timer type is 0x%x, timer ID is 0x%x\n",
          tcNotifyDataTimer->property.type,
          tcNotifyDataTimer->property.timerId);
    WalkCallbackList(tcNotifyDataTimer);
    mutex_lock(&GetTcNsDevList()->devLock);
    list_for_each_entry(tempDevFile, &GetTcNsDevList()->devFileList, head) {
        tlogd("dev file id1 = %u, id2 = %u\n", tempDevFile->devFileId, tcNotifyDataTimer->devFileId);
        if (tempDevFile->devFileId == tcNotifyDataTimer->devFileId) {
            mutex_lock(&tempDevFile->serviceLock);
            tempSvc = TcFindServiceInDev(tempDevFile, tcNotifyDataTimer->uuid, UUID_LEN);
            GetServiceStruct(tempSvc);
            mutex_unlock(&tempDevFile->serviceLock);
            if (tempSvc == NULL) {
                break;
            }
            mutex_lock(&tempSvc->SessionLock);
            tempSes = TcFindSessionWithOwner(&tempSvc->sessionList, tcNotifyDataTimer->sessionId, tempDevFile);
            GetSessionStruct(tempSes);
            mutex_unlock(&tempSvc->SessionLock);
            PutServiceStruct(tempSvc);
            tempSvc = NULL;
            if (tempSes != NULL) {
                tlogd("send cmd ses id %u\n", tempSes->sessionId);
                encFound = 1;
                break;
            }
            break;
        }
    }
    mutex_unlock(&GetTcNsDevList()->devLock);
    if (tcNotifyDataTimer->property.timerClass == TIMER_GENERIC) {
        tlogd("timer60 wake up event\n");
        if (encFound && tempSes != NULL) {
            tempSes->waitData.sendWaitFlag = 1;
            wake_up(&tempSes->waitData.sendCmdWq);
            PutSessionStruct(tempSes);
            tempSes = NULL;
        }
    } else {
        tlogd("RTC do not need to wakeup\n");
    }
}

#ifdef CONFIG_TEE_SMP
static noinline int GetNotifyDataEntry(struct NotifyDataEntry *copy)
{
    uint32_t i;
    int filled;
    int ret = -1;

    if (copy == NULL) {
        tloge("Bad parameters! ");
        return ret;
    }
    /* TIMER and RTC use fix entry, skip them. */
    for (i = NOTIFY_DATA_ENTRY_WAKEUP - 1; i < NOTIFY_DATA_ENTRY_COUNT; i++) {
        struct NotifyDataEntry *e = NULL;
        e = &g_notifyData->entry[i];
        filled = e->filled;
        DMB;
        if (!filled) {
            continue;
        }
        switch (e->entryType) {
            case NOTIFY_DATA_ENTRY_SHADOW: // fall through
            case NOTIFY_DATA_ENTRY_SHADOW_EXIT: // fall through
            case NOTIFY_DATA_ENTRY_FIQSHD: // fall through
                g_notifyData->meta.context.meta.recvs++;
                break;
            case NOTIFY_DATA_ENTRY_WAKEUP:
                g_notifyData->meta.context.meta.recvw++;
                break;
            default:
                tloge("invalid notify type=%u\n", e->entryType);
                goto exit;
        }
        if (memcpy_s(copy, sizeof(*copy), e, sizeof(*e)) != EOK) {
            tloge("memcpy entry failed\n");
            break;
        }
        DMB;
        e->filled = 0;
        ret = 0;
        break;
    }
exit:
    return ret;
}

static void TcNotifyWakeupFn(struct NotifyDataEntry *entry)
{
    struct NotifyContextWakeup *tcNotifyWakeup = NULL;

    tcNotifyWakeup = &(entry->context.wakeup);
    SmcWakeupCa(tcNotifyWakeup->caThreadId);
    tlogd("notify_data_entry_wakeup ca: %d\n", tcNotifyWakeup->caThreadId);
}

static void TcNotifyShadowFn(struct NotifyDataEntry *entry)
{
    struct NotifyContextShadow *tcNotifyShadow = NULL;

    tcNotifyShadow = &(entry->context.shadow);
    SmcQueueShadowWorker(tcNotifyShadow->targetTcb);
}

static void TcNotifyFiqshdFn(struct NotifyDataEntry *entry)
{
    struct NotifyContextShadow *tcNotifyShadow = NULL;

    if (entry == NULL) {
        /* for NOTIFY_DATA_ENTRY_FIQSHD missed */
        FiqShadowWorkFunc(0);
        return;
    }
    tcNotifyShadow = &(entry->context.shadow);
    FiqShadowWorkFunc(tcNotifyShadow->targetTcb);
}

static void TcNotifyShadowExitFn(struct NotifyDataEntry *entry)
{
    struct NotifyContextWakeup *tcNotifyWakeup = NULL;

    tcNotifyWakeup = &(entry->context.wakeup);
    if (SmcShadowExit(tcNotifyWakeup->caThreadId) != 0) {
        tloge("shadow ca exit failed: %d\n",
            (int)tcNotifyWakeup->caThreadId);
    }
}

static void SpiBroadcastNotifications(void)
{
    uint32_t missed;

    DMB;
    missed = LOS_AtomicXchg32bits((Atomic *)&g_notifyData->meta.context.meta.missed, 0);
    if (!missed) {
        return;
    }
    if (missed & (1U << NOTIFY_DATA_ENTRY_WAKEUP)) {
        SmcWakeupBroadcast();
        missed &= ~(1U << NOTIFY_DATA_ENTRY_WAKEUP);
    }
    if (missed & (1U << NOTIFY_DATA_ENTRY_FIQSHD)) {
        TcNotifyFiqshdFn(NULL);
        missed &= ~(1U << NOTIFY_DATA_ENTRY_FIQSHD);
    }
    if (missed) {
        tloge("missed spi notification mask %x\n", missed);
    }
}

static void TcNotifyOtherFun(void)
{
    struct NotifyDataEntry copy = {0};

    while (GetNotifyDataEntry(&copy) == 0) {
        switch (copy.entryType) {
            case NOTIFY_DATA_ENTRY_WAKEUP:
                TcNotifyWakeupFn(&copy);
                break;
            case NOTIFY_DATA_ENTRY_SHADOW:
                TcNotifyShadowFn(&copy);
                break;
            case NOTIFY_DATA_ENTRY_FIQSHD:
                TcNotifyFiqshdFn(&copy);
                break;
            case NOTIFY_DATA_ENTRY_SHADOW_EXIT:
                TcNotifyShadowExitFn(&copy);
                break;
            default:
                tloge("invalid entry type = %u\n", copy.entryType);
                break;
        }
        if (memset_s(&copy, sizeof(copy), 0, sizeof(copy))) {
            tloge("memset copy failed\n");
        }
    }
    SpiBroadcastNotifications();
}
#else
static void TcNotifyOtherFun(void) {}
#endif
int g_spiInited = 0;
static void TcNotifyFn(struct work_struct *dummy)
{
    if (!g_spiInited) {
        return;
    }
    if (g_notifyDataEntryTimer->filled) {
        TcNotifyTimerFn(g_notifyDataEntryTimer);
    }
    if (g_notifyDataEntryRtc->filled) {
        TcNotifyTimerFn(g_notifyDataEntryRtc);
    }
    TcNotifyOtherFun();
}

static irqreturn_t TcSecureNotify(int irq, void *devId)
{
#ifdef CONFIG_TEE_SMP
#define N_WORK  8
    int i;
    static struct work_struct tcNotifyWorks[N_WORK];
    static int init = 0;
    if (!init) {
        for (i = 0; i < N_WORK; i++) {
            INIT_WORK(&tcNotifyWorks[i], TcNotifyFn);
        }
        init = 1;
    }
    for (i = 0; i < N_WORK; i++) {
        if (queue_work(g_tzSpiWq, &tcNotifyWorks[i])) {
            break;
        }
    }
#undef N_WORK
#else
    schedule_work(&tc_notify_work);
    ISB;
    DSB;
    TcSmcWakeup();
#endif
    return IRQ_HANDLED;
}

int TcNsRegisterServiceCallBackFunc(const char *uuid, void *func)
{
    struct TcNsCallback *callbackFunc = NULL;
    struct TcNsCallback *newCallback = NULL;
    int ret = 0;
    errno_t sret;
    bool checkStat = (uuid == NULL || func == NULL);

    if (checkStat) {
        return -EINVAL;
    }

    mutex_lock(&g_taCallbackFuncList.callbackListLock);
    if (g_taCallbackFuncList.callbackCount > MAX_CALLBACK_COUNT) {
        mutex_unlock(&g_taCallbackFuncList.callbackListLock);
        tloge("callbackCount is out\n");
        return -ENOMEM;
    }
    list_for_each_entry(callbackFunc,
        &g_taCallbackFuncList.callbackList, head) {
        if (memcmp(callbackFunc->uuid, uuid, UUID_SIZE) == 0) {
            callbackFunc->callbackFunc = (void (*)(void *))func;
            tlogd("succeed to find uuid ta_callback_func_list\n");
            goto FIND_CALLBACK;
        }
    }
    /* create a new callback struct if we couldn't find it in list */
    newCallback = calloc(1, sizeof(*newCallback));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)newCallback)) {
        tloge("calloc failed\n");
        ret = -ENOMEM;
        goto FIND_CALLBACK;
    }
    sret = memcpy_s(newCallback->uuid, UUID_SIZE, uuid, UUID_SIZE);
    if (sret != EOK) {
        free(newCallback);
        newCallback = NULL;
        ret = -ENOMEM;
        goto FIND_CALLBACK;
    }
    g_taCallbackFuncList.callbackCount++;
    tlogd("ta_callback_func_list.callbackCount is %u\n",
          g_taCallbackFuncList.callbackCount);
    INIT_LIST_HEAD(&newCallback->head);
    newCallback->callbackFunc = (void (*)(void *))func;
    mutex_init(&newCallback->callbackLock);
    list_add_tail(&newCallback->head, &g_taCallbackFuncList.callbackList);
FIND_CALLBACK:
    mutex_unlock(&g_taCallbackFuncList.callbackListLock);
    return ret;
}

#ifdef DEF_ENG
static void TimerCallbackFunc(void *param)
{
    struct TeecTimerProperty *timerProperty =
        (struct TeecTimerProperty *)param;
    tlogd("timerProperty->type = %x, timerProperty->timerId = %x\n",
        timerProperty->type, timerProperty->timerId);
    g_timerType = (int)timerProperty->type;
}

static void TstGetTimerType(int *type)
{
    *type = g_timerType;
}

static void CallbackDemoMain(const char *uuid)
{
    int ret;

    tlogd("step into CallbackDemoMain\n");
    ret = TcNsRegisterServiceCallBackFunc(uuid,
        (void *)&TimerCallbackFunc);
    if (ret != 0) {
        tloge("failed to TcNsRegisterServiceCallBackFunc\n");
    }
}

#define PARAM1 1
#define DUMP_UUID_INDEX0 0
#define DUMP_UUID_INDEX1 1
#define DUMP_UUID_INDEX2 2
#define DUMP_UUID_INDEX3 3
static int HandleTstCmdId(int cmdId, TcNsClientContext *clientContext)
{
    int timerType;
    int ret;
    switch (cmdId) {
        case TST_CMD_01:
            CallbackDemoMain((char *)clientContext->uuid);
            break;
        case TST_CMD_02:
            TstGetTimerType(&timerType);
            if (TcUserParamValid(clientContext, (unsigned int)PARAM1)) {
                tloge("param 1 is invalid\n");
                ret = -EFAULT;
                return ret;
            }
            if (copy_to_user(
                (void *)(uintptr_t)clientContext->params[PARAM1].value.aAddr,
                &timerType, sizeof(timerType))) {
                tloge("copy to user failed:timerType\n");
                ret = -ENOMEM;
                return ret;
            }
            break;
        default:
            ret = -EINVAL;
            return ret;
    }
    return 0;
}

int TcNsTstCmd(TcNsDevFile *devId, void *argp)
{
    TcNsClientContext clientContext;
    int ret;
    int cmdId;

    TeecUuid secureTimerUuid = {
        0x19b39980, 0x2487, 0x7b84,
        {0xf4, 0x1a, 0xbc, 0x89, 0x22, 0x62, 0xbb, 0x3d}
    };
    if (argp == NULL) {
        tloge("argp is NULL input buffer\n");
        ret = -EINVAL;
        return ret;
    }
    if (copy_from_user(&clientContext, argp, sizeof(clientContext))) {
        tloge("copy from user failed\n");
        ret = -ENOMEM;
        return ret;
    }
    if (TcUserParamValid(&clientContext, (unsigned int)0)) {
        tloge("param 0 is invalid\n");
        ret = -EFAULT;
        return ret;
    }
    /* aAddr contain the command id */
    if (copy_from_user(&cmdId, (void *)(uintptr_t)clientContext.params[0].value.aAddr, sizeof(cmdId))) {
        tloge("copy from user failed:cmdId\n");
        ret = -ENOMEM;
        return ret;
    }
    if (memcmp((char *)clientContext.uuid, (char *)&secureTimerUuid, sizeof(TeecUuid))) {
        tloge("request not from secure_timer\n");
        tloge("request uuid: %x %x %x %x\n", clientContext.uuid[DUMP_UUID_INDEX0],
              clientContext.uuid[DUMP_UUID_INDEX1], clientContext.uuid[DUMP_UUID_INDEX2],
              clientContext.uuid[DUMP_UUID_INDEX3]); // just wanna print the first four characters of uuid
        ret = -EACCES;
        return ret;
    }
    ret = HandleTstCmdId(cmdId, &clientContext);
    if (ret) {
        return ret;
    }

    if (copy_to_user(argp, (void *)&clientContext, sizeof(clientContext))) {
        tloge("copy to user failed:client context\n");
        ret = -ENOMEM;
        return ret;
    }
    return ret;
}
#endif

static int TcNsRegisterNotifyDataMemory(void)
{
    TcNsSmcCmd smcCmd = { {0}, 0 };
    int ret;
    struct MbCmdPack *mbPack = NULL;

    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        return TEEC_ERROR_GENERIC;
    }
    mbPack->operation.paramTypes =
        TEE_PARAM_TYPE_VALUE_INPUT | TEE_PARAM_TYPE_VALUE_INPUT << TEE_PARAM_NUM;
    mbPack->operation.params[TEE_PARAM_ONE].value.a = LOS_PaddrQuery(g_notifyData);
    mbPack->operation.params[TEE_PARAM_ONE].value.b = 0;
    mbPack->operation.params[TEE_PARAM_TWO].value.a = SZ_4K;
    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    tlogd("cmd. context_phys:%x\n", smcCmd.contextId);
    ret = TcNsSmc(&smcCmd);
    MailboxFree(mbPack);
    mbPack = NULL;
    return ret;
}

static int TcNsUnregisterNotifyDataMemory(void)
{
    TcNsSmcCmd smcCmd = { {0}, 0 };
    int ret;
    struct MbCmdPack *mbPack = NULL;

    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        return TEEC_ERROR_GENERIC;
    }
    mbPack->operation.paramTypes =
        TEE_PARAM_TYPE_VALUE_INPUT | TEE_PARAM_TYPE_VALUE_INPUT << TEE_PARAM_NUM;
    mbPack->operation.params[TEE_PARAM_ONE].value.a = LOS_PaddrQuery(g_notifyData);
    mbPack->operation.params[TEE_PARAM_ONE].value.b = 0;
    mbPack->operation.params[TEE_PARAM_TWO].value.a = SZ_4K;
    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    tlogd("cmd. context_phys:%x\n", smcCmd.contextId);
    ret = TcNsSmc(&smcCmd);
    MailboxFree(mbPack);
    mbPack = NULL;
    return ret;
}

static int InitNotifyData(void)
{
    if (g_notifyData != NULL) {
        return 0;
    }

    g_notifyData = (struct NotifyDataStruct *)GetPhyPage();
    if (g_notifyData == NULL) {
        tloge("GetFreePage failed for notification data\n");
        return -ENOMEM;
    }
    int ret = memset_s(g_notifyData, PAGESIZE, 0, sizeof(struct NotifyDataStruct));
    if (ret != EOK) {
        return -EFAULT;
    }
    ret = TcNsRegisterNotifyDataMemory();
    if (ret != TEEC_SUCCESS) {
        tloge("Shared memory failed ret is 0x%x\n", ret);
        FreePhyPage(g_notifyData);
        g_notifyData = NULL;
        return -EFAULT;
    }
    g_notifyDataEntryTimer = &g_notifyData->entry[NOTIFY_DATA_ENTRY_TIMER - 1];
    g_notifyDataEntryRtc = &g_notifyData->entry[NOTIFY_DATA_ENTRY_RTC - 1];
#ifdef CONFIG_TEE_SMP
    g_notifyDataEntryShadow = &g_notifyData->entry[NOTIFY_DATA_ENTRY_SHADOW - 1];
    tlogi("test target is: %llx\n", g_notifyDataEntryShadow->context.shadow.targetTcb);
#endif
    return 0;
}

int TzSpiInit()
{
    unsigned int irq;
#ifdef CONFIG_TEE_SMP
    g_tzSpiWq = AllocOrderedWorkqueue("g_tzSpiWq", WQ_HIGHPRI);
    if (g_tzSpiWq == NULL) {
        tloge("it failed to create workqueue g_tzSpiWq\n");
        return -ENOMEM;
    }
#endif
    /* Map IRQ 0 from the OF interrupts list */
    irq = NUM_HAL_INTERRUPT_TEE_SPI_NOTIFY;
    int ret = DevmRequestIrq(irq, TcSecureNotify, IRQF_NO_SUSPEND, TC_NS_CLIENT_DEV, NULL);
    if (ret < 0) {
        tloge("device irq %u request failed %u", irq, ret);
        goto clean;
    }
    ret = memset_s(&g_taCallbackFuncList, sizeof(g_taCallbackFuncList), 0, sizeof(g_taCallbackFuncList));
    if (ret != EOK) {
        ret = -EFAULT;
        goto clean;
    }
    g_taCallbackFuncList.callbackCount = 0;
    INIT_LIST_HEAD(&g_taCallbackFuncList.callbackList);
    mutex_init(&g_taCallbackFuncList.callbackListLock);

    ret = InitNotifyData();
    if (ret < 0) {
        goto clean;
    }

    g_spiInited = 1;
    return 0;
clean:
    TzSpiExit();
    return ret;
}

void TzSpiExit(void)
{
    g_spiInited = 0;

    if (g_notifyData != NULL) {
        if (TcNsUnregisterNotifyDataMemory() != TEEC_SUCCESS) {
            tloge("unregister notify data mem failed\n");
        }
        FreePhyPage(g_notifyData);
        g_notifyData = NULL;
    }
#ifdef CONFIG_TEE_SMP
    if (g_tzSpiWq != NULL) {
        destroy_workqueue(g_tzSpiWq);
        g_tzSpiWq = NULL;
    }
#endif
}
