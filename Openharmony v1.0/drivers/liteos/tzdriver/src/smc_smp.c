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

#include "smc.h"
#include <securec.h>
#include <linux/sched.h>
#include "agent.h"
#include "cmdmonitor.h"
#include "tc_ns_client.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"
#include "teek_ns_client.h"
#include "tzdriver_compat.h"
#ifdef SECURITY_AUTH_ENHANCE
#include "security_auth_enhance.h"

struct SessionCryptoInfo *g_sessionRootKey = NULL;
struct SessionCryptoInfo *GetSessionRootKeyInstance(void)
{
    return g_sessionRootKey;
}
#endif

#define SECS_SUSPEND_STATUS      0xA5A5
#define PREEMPT_COUNT            10000
#define HZ_COUNT                 10
#define IDLED_COUNT              100

#define MAX_EMPTY_RUNS           100
#define TZ_CPU_ZERO    0
#define TZ_CPU_ONE     1
#define TZ_CPU_FOUR    4
#define TZ_CPU_FIVE    5
#define TZ_CPU_SIX     6
#define TZ_CPU_SEVEN   7
#define LOW_BYTE    0xF

/* Current state of the system */
static uint8_t g_sysCrash;

enum SPI_CLK_MODE {
    SPI_CLK_OFF = 0,
    SPI_CLK_ON,
};

typedef struct {
    int *nIdled;
    uint64_t *ret;
    uint64_t *exitReason;
    uint64_t *ta;
    uint64_t *target;
} WoPmParams;

struct ShadowWork {
    struct work_struct work;
    uint64_t target;
};

unsigned long g_shadowThreadId = 0;
static LosTaskCB *g_siqThread = NULL;
static LosTaskCB *g_smcSvcThread = NULL;
struct workqueue_struct *g_ipiHelperWq = NULL;

#ifdef SECURITY_AUTH_ENHANCE
#define MAX_SMC_CMD 18
#else
#define MAX_SMC_CMD 23
#endif

typedef uint32_t SmcBufLockT;

typedef struct __attribute__((__packed__)) TcNsSmcQueue {
    /* set when CA send cmdIn, clear after cmdOut return */
    DECLARE_BITMAP(inBitmap, MAX_SMC_CMD);
    /* set when gtask get cmdIn, clear after cmdOut return */
    DECLARE_BITMAP(doingBitmap, MAX_SMC_CMD);
    /* set when gtask get cmdOut, clear after cmdOut return */
    DECLARE_BITMAP(outBitmap, MAX_SMC_CMD);
    SmcBufLockT smcLock;
    uint32_t lastIn;
    TcNsSmcCmd in[MAX_SMC_CMD];
    uint32_t lastOut;
    TcNsSmcCmd out[MAX_SMC_CMD];
} TcNsSmcQueue;

TcNsSmcQueue *g_cmdData = NULL;
paddr_t g_cmdPhys;

static struct list_head g_pendingHead;
static spinlock_t g_pendLock;

static inline void AcquireSmcBufLock(SmcBufLockT *lock)
{
    int ret;
    PreemptDisable();
    do {
        ret = CmpXchg(lock, 0, 1);
    } while (ret);
}

static inline void ReleaseSmcBufLock(SmcBufLockT *lock)
{
    (void)CmpXchg(lock, 1, 0);
    PreemptEnable();
}

static int OccupyFreeSmcInEntry(const TcNsSmcCmd *cmd)
{
    int idx = -1;
    int i;

    if (cmd == NULL) {
        tloge("Bad parameters! cmd is NULL.\n");
        return -1;
    }
    /* Note:
     * AcquireSmcBufLock will disable preempt and kernel will forbid
     * call mutex_lock in preempt disabled scenes.
     * To avoid such case(UpdateTimestamp and UpdateChksum will call
     * mutex_lock), only cmd copy is done when preempt is disable,
     * then do UpdateTimestamp and UpdateChksum.
     * As soon as this idx of inBitmap is set, gtask will see this
     * cmdIn, but the cmdIn is not ready that lack of update_xxx,
     * so we make a tricky here, set doingBitmap and inBitmap both
     * at first, after update_xxx is done, clear doingBitmap.
     */
    AcquireSmcBufLock(&g_cmdData->smcLock);
    for (i = 0; i < MAX_SMC_CMD; i++) {
        if (HmTestBit(i, g_cmdData->inBitmap)) {
            continue;
        }
        if (memcpy_s(&g_cmdData->in[i], sizeof(g_cmdData->in[i]), cmd, sizeof(*cmd)) != EOK) {
            tloge("memcpy_s failed,%s line:%d", __func__, __LINE__);
            break;
        }
        g_cmdData->in[i].eventNr = i;
        ISB;
        DSB;
        HmSetBit(i, g_cmdData->inBitmap);
        HmSetBit(i, g_cmdData->doingBitmap);
        idx = i;
        break;
    }
    ReleaseSmcBufLock(&g_cmdData->smcLock);
    if (idx == -1) {
        tloge("can't get any free smc entry\n");
        return -1;
    }
#ifdef SECURITY_AUTH_ENHANCE
    if (UpdateTimestamp(&g_cmdData->in[idx])) {
        tloge("UpdateTimestamp failed !\n");
        goto clean;
    }
    if (UpdateChksum(&g_cmdData->in[idx])) {
        tloge("UpdateChksum failed.\n");
        goto clean;
    }
#endif

    AcquireSmcBufLock(&g_cmdData->smcLock);
    ISB;
    DSB;
    HmClearBit(idx, g_cmdData->doingBitmap);
    ReleaseSmcBufLock(&g_cmdData->smcLock);
    return idx;
clean:
    AcquireSmcBufLock(&g_cmdData->smcLock);
    HmClearBit(i, g_cmdData->inBitmap);
    HmClearBit(i, g_cmdData->doingBitmap);
    ReleaseSmcBufLock(&g_cmdData->smcLock);
    return -1;
}

static int ReuseSmcInEntry(uint32_t idx)
{
    int rc = 0;

    AcquireSmcBufLock(&g_cmdData->smcLock);
    if (!(HmTestBit(idx, g_cmdData->inBitmap) &&
        HmTestBit(idx, g_cmdData->doingBitmap))) {
        tloge("invalid cmd to reuse\n");
        rc = -1;
        goto out;
    }
    if (memcpy_s(&g_cmdData->in[idx], sizeof(g_cmdData->in[idx]),
        &g_cmdData->out[idx], sizeof(g_cmdData->out[idx])) != EOK) {
        tloge("memcpy_s failed,%s line:%d", __func__, __LINE__);
        rc = -1;
        goto out;
    }
    ReleaseSmcBufLock(&g_cmdData->smcLock);
#ifdef SECURITY_AUTH_ENHANCE
    if (UpdateTimestamp(&g_cmdData->in[idx])) {
        tloge("UpdateTimestamp failed !\n");
        return -1;
    }
    if (UpdateChksum(&g_cmdData->in[idx])) {
        tloge("UpdateChksum failed.\n");
        return -1;
    }
#endif

    AcquireSmcBufLock(&g_cmdData->smcLock);
    ISB;
    DSB;
    HmClearBit(idx, g_cmdData->doingBitmap);
out:
    ReleaseSmcBufLock(&g_cmdData->smcLock);
    return rc;
}

enum CmdReuse {
    CLEAR,      /* clear this cmd index */
    RESEND,     /* use this cmd index resend */
};

static int CopySmcOutEntry(uint32_t idx, TcNsSmcCmd *copy,
    enum CmdReuse *usage)
{
    bool paramCheck = false;

    paramCheck = (copy == NULL || usage == NULL);
    if (paramCheck == true) {
        tloge("Bad parameters!\n");
        return -1;
    }
    AcquireSmcBufLock(&g_cmdData->smcLock);
    if (!HmTestBit(idx, g_cmdData->outBitmap)) {
        tloge("cmd out %u is not ready\n", idx);
        ShowCmdBitmap();
        ReleaseSmcBufLock(&g_cmdData->smcLock);
        return -1;
    }

    if (memcpy_s(copy, sizeof(*copy), &g_cmdData->out[idx],
        sizeof(g_cmdData->out[idx]))) {
        tloge("copy smc out failed\n");
        ReleaseSmcBufLock(&g_cmdData->smcLock);
        return -1;
    }

    ISB;
    DSB;
    if (g_cmdData->out[idx].retVal == TEEC_PENDING2 ||
        g_cmdData->out[idx].retVal == TEEC_PENDING) {
        *usage = RESEND;
    } else {
        HmClearBit(idx, g_cmdData->inBitmap);
        HmClearBit(idx, g_cmdData->doingBitmap);
        *usage = CLEAR;
    }
    HmClearBit(idx, g_cmdData->outBitmap);
    ReleaseSmcBufLock(&g_cmdData->smcLock);
    return 0;
}

static inline void ReleaseSmcEntry(uint32_t idx)
{
    AcquireSmcBufLock(&g_cmdData->smcLock);
    HmClearBit(idx, g_cmdData->inBitmap);
    HmClearBit(idx, g_cmdData->doingBitmap);
    HmClearBit(idx, g_cmdData->outBitmap);
    ReleaseSmcBufLock(&g_cmdData->smcLock);
}

static inline int IsCmdWorkingDone(uint32_t idx)
{
    bool ret = false;
    AcquireSmcBufLock(&g_cmdData->smcLock);

    if (HmTestBit(idx, g_cmdData->outBitmap)) {
        ret = true;
    }
    ReleaseSmcBufLock(&g_cmdData->smcLock);
    return ret;
}

static void ShowInBitmap(int *cmdIn, uint32_t len)
{
    uint32_t idx;
    uint32_t in = 0;
    char bitmap[MAX_SMC_CMD + 1];
    bool checkValue = (len != MAX_SMC_CMD ||
        g_cmdData == NULL);

    if (checkValue == true) {
        return;
    }
    for (idx = 0; idx < MAX_SMC_CMD; idx++) {
        if (HmTestBit(idx, g_cmdData->inBitmap)) {
            bitmap[idx] = '1';
            cmdIn[in++] = idx;
        } else {
            bitmap[idx] = '0';
        }
    }
    bitmap[MAX_SMC_CMD] = '\0';
    tloge("inBitmap: %s\n", bitmap);
}

static void ShowOutBitmap(int *cmdOut, uint32_t len)
{
    uint32_t idx;
    uint32_t out = 0;
    char bitmap[MAX_SMC_CMD + 1];
    bool checkValue = (len != MAX_SMC_CMD ||
        g_cmdData == NULL);

    if (checkValue == true) {
        return;
    }
    for (idx = 0; idx < MAX_SMC_CMD; idx++) {
        if (HmTestBit(idx, g_cmdData->outBitmap)) {
            bitmap[idx] = '1';
            cmdOut[out++] = idx;
        } else {
            bitmap[idx] = '0';
        }
    }
    bitmap[MAX_SMC_CMD] = '\0';
    tloge("outBitmap: %s\n", bitmap);
}

static void ShowDoingBitmap(void)
{
    uint32_t idx;
    char bitmap[MAX_SMC_CMD + 1];

    if (g_cmdData == NULL) {
        return;
    }
    for (idx = 0; idx < MAX_SMC_CMD; idx++) {
        if (HmTestBit(idx, g_cmdData->doingBitmap)) {
            bitmap[idx] = '1';
        } else {
            bitmap[idx] = '0';
        }
    }
    bitmap[MAX_SMC_CMD] = '\0';
    tloge("doingBitmap: %s\n", bitmap);
}

void ShowCmdBitmapWithLock(void)
{
    if (g_cmdData == NULL) {
        return;
    }
    AcquireSmcBufLock(&g_cmdData->smcLock);
    ShowCmdBitmap();
    ReleaseSmcBufLock(&g_cmdData->smcLock);
}

void ShowCmdBitmap(void)
{
    uint32_t idx;
    int cmdIn[MAX_SMC_CMD];
    int cmdOut[MAX_SMC_CMD];
    bool checkValue = false;

    if (g_cmdData == NULL) {
        return;
    }

    checkValue = memset_s(cmdIn, sizeof(cmdIn), -1, sizeof(cmdIn)) ||
        memset_s(cmdOut, sizeof(cmdOut), -1, sizeof(cmdOut));
    if (checkValue) {
        tloge("memset failed\n");
        return;
    }
    ShowInBitmap(cmdIn, MAX_SMC_CMD);
    ShowDoingBitmap();
    ShowOutBitmap(cmdOut, MAX_SMC_CMD);

    tloge("cmdIn value:\n");
    for (idx = 0; idx < MAX_SMC_CMD; idx++) {
        if (cmdIn[idx] == -1) {
            break;
        }
        tloge("cmd[%d]: cmdId=%u, caPid=%u, devId = 0x%x, eventNr=%u, retVal=0x%x\n",
            cmdIn[idx],
            g_cmdData->in[cmdIn[idx]].cmdId,
            g_cmdData->in[cmdIn[idx]].caPid,
            g_cmdData->in[cmdIn[idx]].devFileId,
            g_cmdData->in[cmdIn[idx]].eventNr,
            g_cmdData->in[cmdIn[idx]].retVal);
    }

    tloge("cmdOut value:\n");
    for (idx = 0; idx < MAX_SMC_CMD; idx++) {
        if (cmdOut[idx] == -1) {
            break;
        }
        tloge("cmd[%d]: cmdId=%u, caPid=%u, devId = 0x%x, eventNr=%u, retVal=0x%x\n",
            cmdOut[idx],
            g_cmdData->out[cmdOut[idx]].cmdId,
            g_cmdData->out[cmdOut[idx]].caPid,
            g_cmdData->out[cmdOut[idx]].devFileId,
            g_cmdData->out[cmdOut[idx]].eventNr,
            g_cmdData->out[cmdOut[idx]].retVal);
    }
}

static struct PendingEntry *InitPendingEntry(pid_t pid)
{
    struct PendingEntry *pe = NULL;

    pe = malloc(sizeof(*pe));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)pe)) {
        tloge("alloc pe failed\n");
        return NULL;
    }
    if (memset_s(pe, sizeof(*pe), 0, sizeof(*pe)) != EOK) {
        tloge("memset pe failed!.\n");
        free(pe);
        return NULL;
    }
    atomic_set(&pe->users, 1); // init pe->users to 1
    pe->pid = pid;
    init_waitqueue_head(&pe->wq);
    atomic_set(&pe->run, 0);
    INIT_LIST_HEAD(&pe->list);
    spin_lock(&g_pendLock);
    list_add_tail(&pe->list, &g_pendingHead);
    spin_unlock(&g_pendLock);
    return pe;
}

struct PendingEntry *FindPendingEntry(pid_t pid)
{
    struct PendingEntry *pe = NULL;

    spin_lock(&g_pendLock);
    list_for_each_entry(pe, &g_pendingHead, list) {
        if (pe->pid == pid) {
            atomic_inc(&pe->users);
            spin_unlock(&g_pendLock);
            return pe;
        }
    }
    spin_unlock(&g_pendLock);
    return NULL;
}

void ForeachPendingEntry(void (*func)(struct PendingEntry *))
{
    struct PendingEntry *pe = NULL;

    if (func == NULL) {
        return;
    }
    spin_lock(&g_pendLock);
    list_for_each_entry(pe, &g_pendingHead, list) {
        func(pe);
    }
    spin_unlock(&g_pendLock);
}

void PutPendingEntry(struct PendingEntry *pe)
{
    if (pe != NULL) {
        if (atomic_dec_and_test(&pe->users)) {
            free(pe);
        }
    }
}

static void ReleasePendingEntry(struct PendingEntry *pe)
{
    spin_lock(&g_pendLock);
    list_del(&pe->list);
    spin_unlock(&g_pendLock);
    PutPendingEntry(pe);
}

static DECLARE_WAIT_QUEUE_HEAD(siqThWait);
static DECLARE_WAIT_QUEUE_HEAD(ipi_th_wait);
static atomic_t g_siqThRun;

enum {
    TYPE_CRASH_TA   = 1,
    TYPE_CRASH_TEE = 2,
};

enum SmcOpsExit {
    SMC_OPS_NORMAL   = 0x0,
    SMC_OPS_SCHEDTO  = 0x1,
    SMC_OPS_START_SHADOW    = 0x2,
    SMC_OPS_START_FIQSHD    = 0x3,
    SMC_OPS_PROBE_ALIVE     = 0x4,
    SMC_OPS_TERMINATE       = 0x5,
    SMC_EXIT_NORMAL         = 0x0,
    SMC_EXIT_PREEMPTED      = 0x1,
    SMC_EXIT_SHADOW         = 0x2,
    SMC_EXIT_MAX            = 0x3,
};

#define SHADOW_EXIT_RUN             0x1234dead

typedef struct SmcCmdRet {
    uint64_t exit;
    uint64_t ta;
    uint64_t target;
} SmcCmdRetT;

static inline void SecretFill(SmcCmdRetT *ret, uint64_t exit, uint64_t ta, uint64_t target)
{
    if (ret != NULL) {
        ret->exit = exit;
        ret->ta = ta;
        ret->target = target;
    }
}

int SigkillPending(LosTaskCB *tsk)
{
    if (tsk == NULL) {
        tloge("tsk is null!\n");
        return 0;
    }

    return OsSigIsMember(&tsk->sig.sigwaitmask, SIGKILL) ||
        OsSigIsMember(&tsk->sig.sigwaitmask, SIGUSR1);
}

enum CmdState {
    START,
    KILLING,
    KILLED,
};

#define CPU0_ONLY_MASK 0x0001

#if CONFIG_CPU_AFF_NR
static void SetCpuStrategy(UINT16 *oldMask)
{
    LosTaskCB *taskCB = OsCurrTaskGet();
    UINT16 newMask = CPU0_ONLY_MASK;

    *oldMask = taskCB->cpuAffiMask;
    KthreadBindMask(taskCB, newMask);
}
#endif

#if CONFIG_CPU_AFF_NR
static void RestoreCpu(UINT16 *oldMask)
{
    LosTaskCB *taskCB = OsCurrTaskGet();
    KthreadBindMask(taskCB, *oldMask);
}
#endif

struct SmcParam {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    SmcCmdRetT *secret;
    uint32_t cmd;
    uint64_t ca;
    uint32_t ta;
    uint32_t exitReason;
    uint32_t target;
    enum CmdState state;
    uint64_t ops;
};

static int DoSmpSmcSend(struct SmcParam *param)
{
    int ret;
    if (param->secret != NULL && param->secret->exit == SMC_EXIT_PREEMPTED) {
        param->r0 = param->cmd;
        if (param->state == KILLING) {
            param->state = KILLED;
            param->r1 = SMC_OPS_TERMINATE;
            param->r2 = param->ca;
        } else {
            param->r1 = SMC_OPS_SCHEDTO;
            param->r2 = param->ca;
            param->r3 = param->secret->ta;
            param->r4 = param->secret->target;
        }
    }
    int checkValue = param->ops == SMC_OPS_SCHEDTO || param->ops == SMC_OPS_START_FIQSHD;
    if (param->secret != NULL && checkValue) {
        param->r4 = param->secret->target;
    }
    ISB;
    DSB;

    do {
        __asm__ volatile(
                "mov r0, %[fid]\n"
                "mov r1, %[a1]\n"
                "mov r2, %[a2]\n"
                "mov r3, %[a3]\n"
                ".arch_extension sec\n"
                "smc    #0\n"
                "str r0, [%[re0]]\n"
                "str r1, [%[re1]]\n"
                "str r2, [%[re2]]\n"
                "str r3, [%[re3]]\n"
            : [fid] "+r" (param->r0), [a1] "+r" (param->r1), [a2] "+r" (param->r2),
              [a3] "+r" (param->r3)
            : [re0] "r" (&ret), [re1] "r" (&param->exitReason),
              [re2] "r" (&param->ta), [re3] "r" (&param->target)
            : "r0", "r1", "r2", "r3");
    } while (0);
    ISB;
    DSB;
    return ret;
}
static noinline int SmpSmcSend(uint32_t cmd, uint64_t ops, uint64_t ca,
    SmcCmdRetT *secret, bool needKill)
{
    uint32_t ret = 0;
    bool checkValue = false;
#if CONFIG_CPU_AFF_NR
    UINT16 oldMask;
#endif
    struct SmcParam param;
    param.r0 = cmd;
    param.r1 = ops;
    param.r2 = ca;
    param.r3 = 0;
    param.r4 = 0;
    param.exitReason = 0;
    param.ta = 0;
    param.target = 0;
    param.state = START;
    param.cmd = cmd;
    param.ca = ca;
    param.secret = secret;
    param.ops = ops;

RETRY:
#if CONFIG_CPU_AFF_NR
    SetCpuStrategy(&oldMask);
#endif

    ret = DoSmpSmcSend(&param);

    if (secret == NULL) {
        return ret;
    }
    SecretFill(secret, param.exitReason, param.ta, param.target);
    if (param.exitReason == SMC_EXIT_PREEMPTED) {
        /* There's 2 ways to send a terminate cmd to kill a running TA,
         * in current context or another. If send terminate in another
         * context, may encounter concurrency problem, as terminate cmd
         * is send but not process, the original cmd has finished.
         * So we send the terminate cmd in current context.
         */
        checkValue = needKill && SigkillPending(OsCurrTaskGet()) && param.state == START &&
            IsThreadReported(OsCurrTaskGet()->taskID);
        if (checkValue == true) {
            param.state = KILLING;
            tloge("receive kill signal\n");
        }
#ifndef CONFIG_PREEMPT
        /* yield cpu to avoid soft lockup */
        cond_resched();
#endif
        goto RETRY;
    }
#if CONFIG_CPU_AFF_NR
    RestoreCpu(&oldMask);
#endif
    return ret;
}

static uint32_t SendSmcCmd(uint32_t cmd, paddr_t cmdAddr,
    uint32_t cmdType, uint8_t wait)
{
    register uint32_t r0 asm("r0") = cmd;
    register uint32_t r1 asm("r1") = cmdAddr;
    register uint32_t r2 asm("r2") = cmdType;
    register uint32_t r3 asm("r3") = 0;
    (void)r0;
    (void)r1;
    (void)r2;
    (void)r3;
    do {
        __asm__ volatile(
            ".ifnc %0, r0;.err;.endif;\n"
            ".ifnc %1, r0;.err;.endif;\n"
            ".ifnc %2, r1;.err;.endif;\n"
            ".ifnc %3, r2;.err;.endif;\n"
            ".ifnc %4, r3;.err;.endif;\n"
            ".arch_extension sec\n"
            "smc #0\n"
            : "+r"(r0)
            : "r"(r0), "r"(r1), "r"(r2), "r"(r3));
    } while (r0 == TSP_REQUEST && wait);
    return r0;
}

int RawSmcSend(uint32_t cmd, paddr_t cmdAddr,
    uint32_t cmdType, uint8_t wait)
{
    uint32_t r0;

#if (CONFIG_CPU_AFF_NR != 0)
    UINT16 oldMask;

    SetCpuStrategy(&oldMask);
#endif
    r0 = SendSmcCmd(cmd, cmdAddr, cmdType, wait);
#if (CONFIG_CPU_AFF_NR != 0)
    RestoreCpu(&oldMask);
#endif
    return r0;
}

void SiqDump(paddr_t mode)
{
    RawSmcSend(TSP_REE_SIQ, mode, 0, false);
    DoCmdNeedArchivelog();
}

static int SiqThreadFn(UINTPTR arg, int len)
{
    int ret;

    while (1) {
        ret = wait_event_interruptible(siqThWait,
            atomic_read(&g_siqThRun));
        if (ret) {
            tloge("wait_event_interruptible failed!\n");
            return -EINTR;
        }
        atomic_set(&g_siqThRun, 0);
        SiqDump((paddr_t)(1)); // set this addr to 1
    }
}

static void CmdResultCheck(TcNsSmcCmd *cmd)
{
    bool checkValue = false;
#ifdef SECURITY_AUTH_ENHANCE
    checkValue = (cmd->retVal == TEEC_SUCCESS) &&
        (VerifyChksum(cmd) != TEEC_SUCCESS);
    if (checkValue == true) {
        cmd->retVal = TEEC_ERROR_GENERIC;
        tloge("VerifyChksum failed.\n");
    }
#endif
    checkValue = cmd->retVal == TEEC_PENDING ||
        cmd->retVal == TEEC_PENDING2;

    if (checkValue == true) {
        tlogd("wakeup command %u\n", cmd->eventNr);
    }
    if (cmd->retVal == TEE_ERROR_TAGET_DEAD) {
        tloge("error smc call: ret = %x and cmd.errOrigin=%x\n",
              cmd->retVal, cmd->errOrigin);
#ifdef CONFIG_TEELOG
        CmdMonitorTaCrash(TYPE_CRASH_TA);
#endif
    } else if (cmd->retVal == TEE_ERROR_AUDIT_FAIL) {
        tloge("error smc call: ret = %x and cmd.errOrigin=%x\n",
            cmd->retVal, cmd->errOrigin);
#ifdef SECURITY_AUTH_ENHANCE
        tloge("error smc call: status = %x and cmd.errOrigin=%x\n",
            cmd->eventindex, cmd->errOrigin);
#endif
    }
}

static int ShadowWoPm(const void *arg, const WoPmParams *params)
{
    uint32_t r0 = TSP_REQUEST;
    uint32_t r1 = SMC_OPS_START_SHADOW;
    uint32_t r2 = OsCurrTaskGet()->taskID;
    uint32_t r3 = 0;
    uint32_t r4 = *(uint32_t *)arg;

    if (*(params->exitReason) == SMC_EXIT_PREEMPTED) {
        r0 = TSP_REQUEST;
        r1 = SMC_OPS_SCHEDTO;
        r2 = OsCurrTaskGet()->taskID;
        r3 = *(params->ta);
        r4 = *(params->target);
    } else if (*(params->exitReason) == SMC_EXIT_NORMAL) {
        r0 = TSP_REQUEST;
        r1 = SMC_OPS_SCHEDTO;
        r2 = OsCurrTaskGet()->taskID;
        r3 = 0;
        r4 = 0;
        if (*(params->nIdled) > IDLED_COUNT) {
            *(params->nIdled) = 0;
            r1 = SMC_OPS_PROBE_ALIVE;
        }
    }
    ISB;
    DSB;
    tlogd("%s: [cpu %d] r0=%x r1=%x r2=%x r3=%x r4=%x\n", __func__,
        RawSmpProcessorId(), r0, r1, r2, r3, r4);
    do {
        __asm__ volatile(
            "mov r0, %[fid]\n"
            "mov r1, %[a1]\n"
            "mov r2, %[a2]\n"
            "mov r3, %[a3]\n"
            "mov r4, %[a4]\n"
            ".arch_extension sec\n"
            "smc #0\n"
            "str r0, [%[re0]]\n"
            "str r1, [%[re1]]\n"
            "str r2, [%[re2]]\n"
            "str r3, [%[re3]]\n"
            :[fid] "+r"(r0), [a1] "+r"(r1), [a2] "+r"(r2),
            [a3] "+r"(r3), [a4] "+r"(r4)
            :[re0] "r"(params->ret), [re1] "r"(params->exitReason),
            [re2] "r"(params->ta), [re3] "r"(params->target)
            : "r0", "r1", "r2", "r3");
    } while (0);

    ISB;
    DSB;

    return 0;
}

static int CheckShadowParam(UINTPTR arg, int len, struct PendingEntry **pe)
{
    if (arg == 0) {
        return -ENOMEM;
    }
    if (len != sizeof(uint64_t)) {
        free((void *)arg);
        return -ENOMEM;
    }

    *pe = InitPendingEntry(GetCurrentPid());
    if (*pe == NULL) {
        tloge("init pending entry failed\n");
        free((void *)arg);
        return -ENOMEM;
    }

    ISB;
    DSB;
    return 0;
}

static int ShadowThreadFn(UINTPTR arg, int len)
{
    uint64_t ret = 0;
    uint64_t exitReason = SMC_EXIT_MAX;
    uint64_t ta = 0;
    uint64_t target = 0;
    int nPreempted = 0;
    int nIdled = 0;
    int retVal;
    struct PendingEntry *pe = NULL;
    int rc;
    WoPmParams params = {&nIdled, &ret, &exitReason, &ta, &target};

    ret = CheckShadowParam(arg, len, &pe);
    if (ret) {
        return ret;
    }

RETRY_WO_PM:
    retVal = ShadowWoPm((void *)arg, &params);
    if (retVal == -1) {
        goto CLEAN_WO_PM;
    }
    tlogd("shadow thread return %lld\n", exitReason);
    if (exitReason == SMC_EXIT_PREEMPTED) {
        nIdled = 0;
        if (++nPreempted > PREEMPT_COUNT) {
            tlogi("%s: retry 10K times on CPU%d\n", __func__, RawSmpProcessorId());
            nPreempted = 0;
        }
        goto RETRY_WO_PM;
    } else if (exitReason == SMC_EXIT_NORMAL) {
        nPreempted = 0;
        long long timeout = HZ * (long)(HZ_COUNT + ((uint8_t)GetCurrentPid() & LOW_BYTE));
        rc = wait_event_interruptible_timeout(pe->wq, atomic_read(&pe->run), (long)timeout);
        if (!rc) {
            nIdled++;
        }
        if (atomic_read(&pe->run) == SHADOW_EXIT_RUN) {
            tlogd("shadow thread work quit, be killed\n");
            goto CLEAN_WO_PM;
        } else {
            atomic_set(&pe->run, 0);
            goto RETRY_WO_PM;
        }
    } else if (exitReason == SMC_EXIT_SHADOW) {
        tlogd("shadow thread exit, it self\n");
    } else {
        tlogd("shadow thread exit with unknown code %ld\n", (long)exitReason);
    }

CLEAN_WO_PM:
    free((void *)arg);
    ReleasePendingEntry(pe);
    return retVal;
}

static void ShadowWorkFunc(struct work_struct *work)
{
    LosTaskCB *shadowThread = NULL;
    if (work == NULL) {
        return;
    }
    struct ShadowWork *sWork =
        container_of(work, struct ShadowWork, work);
    uint64_t *targetArg = malloc(sizeof(uint64_t));

    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)targetArg)) {
        tloge("%s: malloc(8 bytes) failed\n", __func__);
        return;
    }
    if (memset_s(targetArg, sizeof(uint64_t),
        0, sizeof(uint64_t)) != EOK) {
        tloge("memset targetArg failed!.\n");
        free(targetArg);
        return;
    }
    *targetArg = sWork->target;

    char shadowName[OS_TCB_NAME_LEN] = {0};
    sprintf_s(shadowName, OS_TCB_NAME_LEN, "shadow_th/%lu", g_shadowThreadId++);
    shadowThread = KthreadRun(ShadowThreadFn, targetArg, sizeof(uint64_t), shadowName);
    if (IS_ERR_OR_NULL(shadowThread)) {
        free(targetArg);
        tloge("couldn't create shadowThread %ld\n",
            PTR_ERR(shadowThread));
        return;
    }
    tlogd("%s: create shadow thread %lu for target %llx\n",
        __func__, g_shadowThreadId, *targetArg);
    WakeUpProcess(shadowThread);
}

static int ProcSmcWakeupCa(pid_t ca, int which)
{
    if (ca == 0) {
        tlogw("wakeup for ca = 0\n");
    } else {
        struct PendingEntry *pe = FindPendingEntry(ca);

        if (pe == NULL) {
            tloge("invalid ca pid=%d for pending entry\n", (int)ca);
            return -1;
        }
        atomic_set(&pe->run, which);
        wake_up(&pe->wq);
        tlogd("wakeup pending thread %ld\n", (long)ca);
        PutPendingEntry(pe);
    }
    return 0;
}

void WakeupPe(struct PendingEntry *pe)
{
    if (pe != NULL) {
        atomic_set(&pe->run, 1);
        wake_up(&pe->wq);
    }
}

int SmcWakeupBroadcast(void)
{
    ForeachPendingEntry(WakeupPe);
    return 0;
}

int SmcWakeupCa(pid_t ca)
{
    return ProcSmcWakeupCa(ca, 1); // set pe->run to 1
}

int SmcShadowExit(pid_t ca)
{
    return ProcSmcWakeupCa(ca, SHADOW_EXIT_RUN);
}

void FiqShadowWorkFunc(uint64_t target)
{
    SmcCmdRetT secret = { SMC_EXIT_MAX, 0, target };

    SmpSmcSend(TSP_REQUEST, SMC_OPS_START_FIQSHD, GetCurrentPid(),
        &secret, false);
    return;
}

int SmcQueueShadowWorker(uint64_t target)
{
    struct ShadowWork shadowWork;
    INIT_WORK_ONSTACK(&shadowWork.work, ShadowWorkFunc);
    shadowWork.target = target;

    /* Run work on CPU 0 */
    queue_work(g_ipiHelperWq, &shadowWork.work);
    flush_work(&shadowWork.work);
    return 0;
}

static int SmcOpsNormal(enum CmdReuse *cmdUsage, int *cmdIndex,
    int *lastIndex, struct PendingEntry *pe, const TcNsSmcCmd *cmd)
{
    if (*cmdUsage == RESEND) {
        if (ReuseSmcInEntry(*cmdIndex)) {
            tloge("reuse smc entry failed\n");
            ReleaseSmcEntry(*cmdIndex);
            ReleasePendingEntry(pe);
            return -1;
        }
    } else {
        *cmdIndex = OccupyFreeSmcInEntry(cmd);
        if (*cmdIndex == -1) {
            tloge("there's no more smc entry\n");
            ReleasePendingEntry(pe);
            return -1;
        }
    }
    if (*cmdUsage != CLEAR) {
        *cmdIndex = *lastIndex;
        *cmdUsage = CLEAR;
    } else {
        *lastIndex = *cmdIndex;
    }
    tlogd("submit new cmd: cmd.ca=%u cmd-id=%x ev-nr=%u cmd-index=%u last-index=%d\n",
        cmd->caPid, cmd->cmdId,
        g_cmdData->in[*cmdIndex].eventNr, *cmdIndex,
        *lastIndex);
    return 0;
}

static int SmpSmcSendCmdDone(int cmdIndex, TcNsSmcCmd *cmd,
    TcNsSmcCmd *in)
{
    CmdResultCheck(cmd);
    switch (cmd->retVal) {
        case TEEC_PENDING2: {
            unsigned int agentId = cmd->agentId;
            /* If the agent does not exist post
             * the answer right back to the TEE
             */
            if (AgentProcessWork(cmd, agentId) != TEEC_SUCCESS) {
                tloge("agent process work failed\n");
            }
            return -1;
        }
        case TEE_ERROR_TAGET_DEAD:
        case TEEC_PENDING:
        /* just copy out, and let out to proceed */
        default:
            if (memcpy_s(in, sizeof(*in),
                cmd, sizeof(*cmd)) != EOK) {
                tloge("memcpy_s failed,%s line:%d", __func__, __LINE__);
                cmd->retVal = -1;
            }
            break;
    }

    return 0;
}

#define SYM_NAME_LEN_MAX 16
#define SYM_NAME_LEN_1 7
#define SYM_NAME_LEN_2 4
#define CRASH_REG_NUM  3
#define LOW_FOUR_BITE  4

typedef union {
    uint64_t crashReg[CRASH_REG_NUM];
    struct {
        uint8_t haltReason : LOW_FOUR_BITE;
        uint8_t app : LOW_FOUR_BITE;
        char symName[SYM_NAME_LEN_1];
        uint16_t off;
        uint16_t size;
        uint32_t far;
        uint32_t fault;
        union {
            char symNameAppend[SYM_NAME_LEN_2];
            uint32_t elr;
        };
    } CrashMsg;
} CrashInf;

static void PrintCrashMsg(CrashInf *crashInfo)
{
    static const char *teeCriticalApp[] = {
        "gtask",
        "teesmcmgr",
        "hmsysmgr",
        "hmfilemgr",
        "platdrv",
        "kernel"
    };
    int appNum = sizeof(teeCriticalApp) / sizeof(teeCriticalApp[0]);
    const char *crashAppName = "NULL";
    uint16_t off = crashInfo->CrashMsg.off;
    int appIndex = crashInfo->CrashMsg.app & LOW_BYTE;
    int haltReason = crashInfo->CrashMsg.haltReason;
    int sret;

    crashInfo->CrashMsg.off = 0; // for end of symName

    if (appIndex >= 0 && appIndex < appNum) {
        crashAppName = teeCriticalApp[appIndex];
    } else {
        tloge("index error: %x\n", crashInfo->CrashMsg.app);
    }

    // kernel
    if (appIndex == (appNum - 1)) {
        tloge("====crash app:%s user_sym:%s kernel crash off/size: <0x%x/0x%x>\n",
              crashAppName, crashInfo->CrashMsg.symName,
              off, crashInfo->CrashMsg.size);
        tloge("====crash haltReason: 0x%x far:0x%x fault:0x%x elr:0x%x (ret_ip: 0x%llx)\n",
              haltReason, crashInfo->CrashMsg.far,
              crashInfo->CrashMsg.fault, crashInfo->CrashMsg.elr,
              crashInfo->crashReg[CRASH_RET_IP]);
    } else { // user app
        char syms[SYM_NAME_LEN_MAX] = {0};

        sret = memcpy_s(syms, SYM_NAME_LEN_MAX,
            crashInfo->CrashMsg.symName, SYM_NAME_LEN_1);
        if (sret != EOK) {
            tloge("memcpy symName failed!\n");
        }
        sret = memcpy_s(syms + SYM_NAME_LEN_1,
            SYM_NAME_LEN_MAX - SYM_NAME_LEN_1,
            crashInfo->CrashMsg.symNameAppend, SYM_NAME_LEN_2);
        if (sret != EOK) {
            tloge("memcpy symNameAppend failed!\n");
        }
        tloge("====crash app:%s user_sym:%s + <0x%x/0x%x>\n",
              crashAppName, syms, off, crashInfo->CrashMsg.size);
        tloge("====crash far:0x%x fault:%x\n",
              crashInfo->CrashMsg.far, crashInfo->CrashMsg.fault);
    }
}

static int SmpSmcSendProcess(TcNsSmcCmd *cmd, uint64_t ops,
    SmcCmdRetT *cmdRet, int cmdIndex)
{
    int ret;

    ret = SmpSmcSend(TSP_REQUEST, ops, GetCurrentPid(), cmdRet, true);
    tlogd("SmpSmcSend ret = %x, cmdRet.exit=%ld, cmdIndex=%d\n",
        ret, (long)cmdRet->exit, cmdIndex);
    ISB;
    DSB;
    if (ret == (int)TSP_CRASH) {
        CrashInf crashInfo;
        crashInfo.crashReg[CRASH_RET_EXIT] = cmdRet->exit;
        crashInfo.crashReg[CRASH_RET_TA] = cmdRet->ta;
        crashInfo.crashReg[CRASH_RET_IP] = cmdRet->target;

        tloge("TEEOS has crashed!\n");
        PrintCrashMsg(&crashInfo);

        g_sysCrash = 1;
#ifdef CONFIG_TEELOG
        CmdMonitorTaCrash(TYPE_CRASH_TEE);
#endif
        cmd->retVal = -1;
        return -1;
    }

    return 0;
}

static int InitForSmcSend(TcNsSmcCmd *in, struct PendingEntry **pe,
    TcNsSmcCmd *cmd, bool reuse)
{
    if (in == NULL) {
        tloge("Bad params\n");
        return -1;
    }

    *pe = InitPendingEntry(GetCurrentPid());
    if (*pe == NULL) {
        tloge("init pending entry failed\n");
        return -ENOMEM;
    }
    in->caPid = GetCurrentPid();
    if (!reuse) {
        if (memcpy_s(cmd, sizeof(*cmd), in, sizeof(*in))) {
            tloge("memcpy_s failed,%s line:%d", __func__, __LINE__);
            ReleasePendingEntry(*pe);
            return -1;
        }
    }
    return 0;
}

#define GOTO_RESLEEP 1
#define GOTO_RETRY_WITH_CMD 2
#define GOTO_RETRY 3
#define GOTO_CLEAN 4

static int CheckIsCaKilled(int cmdIndex, uint64_t *ops)
{
    /* if CA has not been killed */
    if (SigkillPending(OsCurrTaskGet()) == 0) {
        if (!IsCmdWorkingDone(cmdIndex)) {
            return GOTO_RESLEEP;
        } else {
            tloge("cmd done, may miss a spi!\n");
            ShowCmdBitmapWithLock();
        }
    } else {
        /* if CA killed, send terminate cmd */
        *ops = SMC_OPS_TERMINATE;
        tloge("CA is killed, send terminate!\n");
        return GOTO_RETRY_WITH_CMD;
    }
    return 0;
}

struct CmdPram {
    TcNsSmcCmd *cmd;
    int cmdIndex;
    enum CmdReuse *cmdUsage;
};

static int CmdDoneProcess(TcNsSmcCmd *in, struct CmdPram *cmdParam, uint64_t *ops)
{
    if ((in == NULL) || (cmdParam == NULL) || (ops == NULL)) {
        return 0;
    }

    if (CopySmcOutEntry(cmdParam->cmdIndex, cmdParam->cmd, cmdParam->cmdUsage)) {
        cmdParam->cmd->retVal = -1;
        return GOTO_CLEAN;
    }

    if (SmpSmcSendCmdDone(cmdParam->cmdIndex, cmdParam->cmd, in) == -1) {
        *ops = SMC_OPS_NORMAL;
        /* cmd will be reused */
        return GOTO_RETRY;
    }

    return 0;
}

static int RetryWithFillCmdProcess(TcNsSmcCmd *in, struct CmdPram *cmdParam, struct PendingEntry *pe,  uint64_t *ops)
{
    SmcCmdRetT cmdRet = {0};

    if ((in == NULL) || (cmdParam == NULL) || (pe == NULL) || (ops == NULL)) {
        return 0;
    }

    while (1) {
        tlogd("SmpSmcSend start cmdId = %u, ca = %u\n", cmdParam->cmd->cmdId, cmdParam->cmd->caPid);
        if (SmpSmcSendProcess(cmdParam->cmd, *ops, &cmdRet, cmdParam->cmdIndex) == -1) {
            return GOTO_CLEAN;
        }
        if (IsCmdWorkingDone(cmdParam->cmdIndex)) {
            return CmdDoneProcess(in, cmdParam, ops);
        }

        if (cmdRet.exit != SMC_EXIT_NORMAL) {
            tloge("invalid cmd work state\n");
            cmdParam->cmd->retVal = -1;
            return GOTO_CLEAN;
        }
        /* task pending exit */
        tlogd("goto sleep, exitReason=%lld\n", cmdRet.exit);
RESLEEP:
        if (wait_event_interruptible_timeout(pe->wq, atomic_read(&pe->run),
            (long)(RESLEEP_TIMEOUT * HZ)) == 0) {
            tlogd("CA wait event for %d s\n", RESLEEP_TIMEOUT);
            int ret = CheckIsCaKilled(cmdParam->cmdIndex, ops);
            if (ret == GOTO_RESLEEP) {
                goto RESLEEP;
            } else if (ret == GOTO_RETRY_WITH_CMD) {
                continue;
            }
        }
        atomic_set(&pe->run, 0);

        if (IsCmdWorkingDone(cmdParam->cmdIndex)) {
            tlogd("cmd is done\n");
            return CmdDoneProcess(in, cmdParam, ops);
        }
        *ops = SMC_OPS_SCHEDTO;
    }

    return 0;
}

static int SmpSmcSendFunc(TcNsSmcCmd *in, uint32_t cmdType,
    bool reuse)
{
    int cmdIndex = 0;
    int lastIndex = 0;
    TcNsSmcCmd cmd = { {0}, 0 };
    struct PendingEntry *pe = NULL;
    uint64_t ops;
    enum CmdReuse cmdUsage = CLEAR;
    int ret;
    bool check = false;

    if (InitForSmcSend(in, &pe, &cmd, reuse) != 0) {
        tloge(KERN_INFO "InitForSmcSend fail\n");
        return -1;
    }
    if (reuse) {
        lastIndex = cmdIndex = in->eventNr;
        cmdUsage = RESEND;
    }
    ops = SMC_OPS_NORMAL;

RETRY:
    if ((ops == SMC_OPS_NORMAL) &&
        SmcOpsNormal(&cmdUsage, &cmdIndex, &lastIndex, pe, &cmd) == -1) {
        tloge(KERN_INFO "SmcOpsNormal fail\n");
        return -1;
    }

    struct CmdPram cmdParam;
    cmdParam.cmd = &cmd;
    cmdParam.cmdIndex = cmdIndex;
    cmdParam.cmdUsage = &cmdUsage;

    ret = RetryWithFillCmdProcess(in, &cmdParam, pe, &ops);
    if (ret == GOTO_CLEAN) {
        goto CLEAN;
    } else if (ret == GOTO_RETRY) {
        goto RETRY;
    }

CLEAN:
    check = (cmdUsage != CLEAR && cmd.retVal != TEEC_PENDING);
    if (check == true) {
        ReleaseSmcEntry(cmdIndex);
    }
    ReleasePendingEntry(pe);
    return cmd.retVal;
}

static int SmcSvcThreadFn(UINTPTR arg, int len)
{
    while (!KthreadShouldStop()) {
        TcNsSmcCmd smcCmd = { {0}, 0 };
        int ret;

        smcCmd.globalCmd = true;
        smcCmd.cmdId = GLOBAL_CMD_ID_SET_SERVE_CMD;
        ret = SmpSmcSendFunc(&smcCmd,
            TC_NS_CMD_TYPE_NS_TO_SECURE, false);
        tlogd("smc svc return 0x%x\n", ret);
    }
    tloge("smc_svc_thread stop ...\n");
    return 0;
}

void WakeupTcSiq(void)
{
    atomic_set(&g_siqThRun, 1); // init g_siqThRun to 1
    wake_up_interruptible(&siqThWait);
}
/*
 * This function first power on crypto cell, then send smc cmd to trustedcore.
 * After finished, power off crypto cell.
 */
static int ProcTcNsSmc(TcNsSmcCmd *cmd, bool reuse)
{
    int ret;

    if (g_sysCrash) {
        tloge("ERROR: sys crash happened!!!\n");
        return TEEC_ERROR_GENERIC;
    }
    if (cmd == NULL) {
        tloge("invalid cmd\n");
        return TEEC_ERROR_GENERIC;
    }
    tlogd(KERN_INFO "***TC_NS_SMC call start on cpu %d ***\n",
        RawSmpProcessorId());
    CmdMonitorLog(cmd);
    ret = SmpSmcSendFunc(cmd, TC_NS_CMD_TYPE_NS_TO_SECURE, reuse);
    CmdMonitorLogend();
    return ret;
}

int TcNsSmc(TcNsSmcCmd *cmd)
{
    return ProcTcNsSmc(cmd, false);
}

int TcNsSmcWithNoNr(TcNsSmcCmd *cmd)
{
    return ProcTcNsSmc(cmd, true);
}

static void SmcWorkNoWait(uint32_t type)
{
    RawSmcSend(TSP_REQUEST, g_cmdPhys, type, true);
}

static void SmcWorkSetCmdBuffer(struct work_struct *work)
{
    (void)work;
    SmcWorkNoWait(TC_NS_CMD_TYPE_SECURE_CONFIG);
}

static void SmcWorkInitSecondaryCpus(struct work_struct *work)
{
    (void)work;
    SmcWorkNoWait(TC_NS_CMD_TYPE_NS_TO_SECURE);
}

static int SmcSetCmdBuffer(void)
{
    struct work_struct work;

    INIT_WORK_ONSTACK(&work, SmcWorkSetCmdBuffer);
    /* Run work on CPU 0 */
    ScheduleWorkOn(0, &work);
    flush_work(&work);
    tlogd("smc set cmd buffer done\n");
    return 0;
}

static int SmcInitSecondaryCpus(void)
{
    unsigned int i;
    struct work_struct work;

    INIT_WORK_ONSTACK(&work, SmcWorkInitSecondaryCpus);
    /* Run work on all secondary cpus */
    for (i = 1; i < LOSCFG_KERNEL_CORE_NUM; i++) {
#if CONFIG_CPU_AFF_NR
        if (i >= CONFIG_CPU_AFF_NR) {
            break;
        }
#endif
        ScheduleWorkOn((int)i, &work);
        flush_work(&work);
        tlogd("init secondary cpu %u done\n", i);
    }
    return 0;
}

#ifdef SECURITY_AUTH_ENHANCE
#define ALIGN_BIT  0x3

static void FreeRootKey(void)
{
    if (memset_s((void *)g_sessionRootKey, sizeof(*g_sessionRootKey),
        0, sizeof(*g_sessionRootKey)) != EOK) {
        tloge("memset mem failed\n");
    }
    free(g_sessionRootKey);
    g_sessionRootKey = NULL;
}

static int GetSessionRootKey(void)
{
    int ret;
    uint32_t *buffer = (uint32_t *)(g_cmdData->in);
#ifdef CONFIG_ARM64
    if (buffer == NULL || ((uint64_t)(uintptr_t)buffer & ALIGN_BIT)) {
#else
    if (buffer == NULL || ((uint32_t)(uintptr_t)buffer & ALIGN_BIT)) {
#endif
        tloge("Session root key must be 4bytes aligned\n");
        return -EFAULT;
    }
    g_sessionRootKey = calloc(1, sizeof(*g_sessionRootKey));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)g_sessionRootKey)) {
        tloge("No memory to store session root key\n");
        return -ENOMEM;
    }
    if (memcpy_s(g_sessionRootKey, sizeof(*g_sessionRootKey),
        (void *)(buffer + 1), sizeof(*g_sessionRootKey))) {
        tloge("Copy session root key from TEE failed\n");
        ret = -EFAULT;
        goto FREE_MEM;
    }
    if (memset_s((void *)(g_cmdData->in), sizeof(g_cmdData->in),
        0, sizeof(g_cmdData->in))) {
        tloge("Clean the command buffer failed\n");
        ret = -EFAULT;
        goto FREE_MEM;
    }
    return 0;
FREE_MEM:
    FreeRootKey();
    return ret;
}
#endif

static int SmcInitDataCmdData(void)
{
    g_cmdData = (TcNsSmcQueue *)GetPhyPage();
    if (g_cmdData == NULL) {
        return -ENOMEM;
    }
    if (memset_s(g_cmdData, sizeof(TcNsSmcQueue), 0, sizeof(TcNsSmcQueue))) {
        FreePhyPage(g_cmdData);
        g_cmdData = NULL;
        return -ENOMEM;
    }
    g_cmdPhys = LOS_PaddrQuery(g_cmdData);
    return 0;
}

int SmcInitData(void)
{
    int ret = SmcInitDataCmdData();
    if (ret) {
        return ret;
    }
    /* Send the allocated buffer to TrustedCore for init */
    if (SmcSetCmdBuffer()) {
        ret = -EINVAL;
        goto FREE_MEM;
    }
    if (SmcInitSecondaryCpus()) {
        ret = -EINVAL;
        goto FREE_MEM;
    }
#ifdef SECURITY_AUTH_ENHANCE
    if (GetSessionRootKey()) {
        ret = -EFAULT;
        goto FREE_MEM;
    }
#endif

    g_siqThread = KthreadRun(SiqThreadFn, NULL, 0, "siqthread/0");
    if (unlikely(IS_ERR_OR_NULL(g_siqThread))) {
        pr_err("couldn't create siqthread %ld\n",
            PTR_ERR(g_siqThread));
        ret = (int)PTR_ERR(g_siqThread);
        goto FREE_MEM;
    }

    g_ipiHelperWq = create_workqueue("ipihelper");
    if (g_ipiHelperWq == NULL) {
        tloge("couldn't create workqueue.\n");
        ret = -ENOMEM;
        goto FREE_SIQ_WORKER;
    }

    WakeUpProcess(g_siqThread);
    InitCmdMonitor();
    INIT_LIST_HEAD(&g_pendingHead);
    spin_lock_init(&g_pendLock);
    return 0;

FREE_SIQ_WORKER:
    KthreadStop(g_siqThread);
    g_siqThread = NULL;
FREE_MEM:
    FreePhyPage(g_cmdData);
    g_cmdData = NULL;
#ifdef SECURITY_AUTH_ENHANCE
    if (!IS_ERR_OR_NULL(g_sessionRootKey)) {
        FreeRootKey();
    }
#endif
    return ret;
}

int InitSmcSvcThread(void)
{
    g_smcSvcThread = KthreadRun(SmcSvcThreadFn, NULL, 0, "smc_svc_thread");
    if (unlikely(IS_ERR_OR_NULL(g_smcSvcThread))) {
        tloge("couldn't create smc_svc_thread %ld\n", PTR_ERR(g_smcSvcThread));
        return PTR_ERR(g_smcSvcThread);
    }
    WakeUpProcess(g_smcSvcThread);
    return 0;
}

void SmcFreeData(void)
{
    FreePhyPage(g_cmdData);
    g_cmdData = NULL;
    if (!IS_ERR_OR_NULL(g_smcSvcThread)) {
        KthreadStop(g_smcSvcThread);
        g_smcSvcThread = NULL;
    }
#ifdef SECURITY_AUTH_ENHANCE
    if (!IS_ERR_OR_NULL(g_sessionRootKey)) {
        FreeRootKey();
    }
#endif
}

