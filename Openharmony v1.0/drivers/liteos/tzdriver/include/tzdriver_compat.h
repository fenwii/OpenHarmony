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

#ifndef __TZDRIVER_COMPAT_H
#define __TZDRIVER_COMPAT_H

#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include "arm.h"
#include "fs/fs.h"
#include "fs_poll_pri.h"
#include "hisoc/random.h"
#include "los_process_pri.h"
#include "los_task.h"
#include "los_vm_lock.h"
#include "los_vm_map.h"
#include "los_vm_phys.h"
#include "mbedtls/sha256.h"

/* TEE config */
#define DEF_ENG 1
#define CONFIG_TEE_SMP 1
#define CONFIG_TEELOG 1
#define CONFIG_CPU_AFF_NR 0
#define CONFIG_TEE_SMP 1
/* TEE config end */

#define VERIFY_READ 0
#define VERIFY_WRITE 1
#define MAX_DEV_NAME_SIZE  32
#define SHA256_DIGEST_LENGTH 32
#define ALIGN_TZ(x, boundary) (((x) + ((boundary) - 1)) & ~((boundary) - 1))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

typedef pthread_mutex_t     mutex_t;

#ifndef IS_ERR_OR_NULL
#ifndef IS_ERR_VALUE
#define IS_ERR_VALUE(x) unlikely((unsigned long)(void *)(x) >= (unsigned long) - 4095)
#endif
#define IS_ERR_OR_NULL(x) ((!x) || IS_ERR_VALUE((UINTPTR)x))
#endif

#define TEE_DEV_PRI 0660

#define TASK_COMM_LEN OS_TCB_NAME_LEN

#define WQ_HIGHPRI (1 << 4)
#define IRQF_NO_SUSPEND        0x00004000
#define __GFP_ZERO 0x8000u

#define SZ_4K 0x1000UL
#define SZ_1M (1024 * 1024)
#define SZ_4M (4 * SZ_1M)
#define SZ_8M (8 * SZ_1M)

#define MAX_POW_TWO(n) \
( \
((n) >> 31) ? 31 : ((n) >> 30) ? 30 : \
((n) >> 29) ? 29 : ((n) >> 28) ? 28 : \
((n) >> 27) ? 27 : ((n) >> 26) ? 26 : \
((n) >> 25) ? 25 : ((n) >> 25) ? 25 : \
((n) >> 23) ? 23 : ((n) >> 22) ? 22 : \
((n) >> 21) ? 21 : ((n) >> 20) ? 20 : \
((n) >> 19) ? 19 : ((n) >> 18) ? 18 : \
((n) >> 17) ? 17 : ((n) >> 16) ? 16 : \
((n) >> 15) ? 15 : ((n) >> 14) ? 14 : \
((n) >> 13) ? 13 : ((n) >> 12) ? 12 : \
((n) >> 11) ? 11 : ((n) >> 10) ? 10 : \
((n) >> 9) ? 9: ((n) >> 8) ? 8 : \
((n) >> 7) ? 7: ((n) >> 6) ? 6 : \
((n) >> 5) ? 5: ((n) >> 4) ? 4 : \
((n) >> 3) ? 3: ((n) >> 2) ? 2 : 1)

#define GET_ORDER(n) \
( \
    n <= PAGE_SIZE ? 0 : (MAX_POW_TWO(n - 1) - PAGE_SHIFT + 1) \
)

#ifndef MSEC_PER_SEC
#define MSEC_PER_SEC 1000
#endif

#ifndef NSEC_PER_MSEC
#define NSEC_PER_MSEC 1000000L
#endif

#ifndef USEC_PER_SEC
#define USEC_PER_SEC 1000000L
#endif

#ifndef NSEC_PER_USEC
#define NSEC_PER_USEC 1000
#endif

#define CRASH_RET_EXIT 0
#define CRASH_RET_TA 1
#define CRASH_RET_IP 2

#undef DIV_ROUND_UP
#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))
#undef BITS_PER_BYTE
#define BITS_PER_BYTE 8
#undef BITS_PER_LONG
#define BITS_PER_LONG 64
#undef BITS_TO_LONGS
#define BITS_TO_LONGS(nr) DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(uint64_t))
#undef BIT_MASK
#define BIT_MASK(nr) (1UL << ((nr) % BITS_PER_LONG))
#undef BIT_WORD
#define BIT_WORD(nr) ((nr) / BITS_PER_LONG)
#undef DECLARE_BITMAP
#define DECLARE_BITMAP(name, bits) uint64_t name[BITS_TO_LONGS(bits)]

#define INIT_WORK_ONSTACK(_work, _func) \
do { \
    INIT_WORK(_work, _func); \
} while (0)

bool ScheduleWorkOn(int cpu, struct work_struct *work);

#define __WORK_INIT(n, f) { \
    .data = 0, \
    .entry = { &(n).entry, &(n).entry }, \
    .func = f \
}
#define DECLARE_WORK(work, func) \
    struct work_struct work = __WORK_INIT(work, func);

#define noinline __attribute__((noinline))

LosTaskCB *KthreadRun(int (*threadfn)(UINTPTR data, int dataLen), void *data, int len, char *name);
void KthreadStop(const LosTaskCB *k);
int KthreadShouldStop(void);
INT32 DoVmallocRemap(LosVmMapRegion *vma, void *kvaddr);
int RemapVmallocRange(LosVmMapRegion *vma, void *addr, unsigned long pgoff);
int CreateTcClientDevice(const char *devName, const struct file_operations_vfs *op);
ssize_t SimpleReadFromBuffer(void *to, size_t count, const void *from, size_t available);
LosVmPage *MailboxPoolAllocPages(unsigned int order);
void MailboxPoolFreePages(LosVmPage *pageArray, size_t order);

struct AesParam {
    unsigned char *iv;
    const unsigned char *key;
    int size;
    unsigned int encryptoType;
};

int CryptoAescbcKey256(unsigned char *output, const unsigned char *input, struct AesParam *param);

#define INT_SIZE 4

static inline struct workqueue_struct *AllocOrderedWorkqueue(const char *fmt, unsigned int flags)
{
    return create_workqueue((char *)fmt);
}

static inline int AccessOk(int type, unsigned long ptr, unsigned int size)
{
    if (ptr + size < ptr) {
        return false;
    }
    return LOS_IsUserAddress(ptr + size);
}

static inline int GetTaskUid(LosTaskCB *task)
{
#ifdef LOSCFG_SECURITY_CAPABILITY
    int intSave = LOS_IntLock();
    int uid = -1;

    LosProcessCB *process = OS_PCB_FROM_PID(task->processID);
    if (process->user) {
        uid = process->user->userID;
    }
    LOS_IntRestore(intSave);
    return uid;
#else
    return 0;
#endif
}

static inline int DevmRequestIrq(unsigned int irq, irq_handler_t handler,
    unsigned long irqflags, const char *devname, void *devId)
{
    return request_irq(irq, handler, irqflags, devname, NULL);
}

static inline void *GetPhyPage(void)
{
    LosVmPage *page = LOS_PhysPageAlloc();
    if (page == NULL) {
        return NULL;
    }
    return OsVmPageToVaddr(page);
}

static inline void FreePhyPage(void *ptr)
{
    if (ptr == NULL) {
        return;
    }
    LosVmPage *page = OsVmVaddrToPage(ptr);
    if (page != NULL) {
        LOS_PhysPageFree(page);
    }
}

static inline void KthreadBindMask(LosTaskCB *p, UINT16 mask)
{
    if (p == NULL) {
        return;
    }
    LOS_TaskCpuAffiSet(p->taskID, mask);
}

static inline void HmSetBit(int nr, volatile uint64_t *addr)
{
    if (addr == NULL) {
        return;
    }
    uint64_t mask = BIT_MASK(nr);
    uint64_t *p   = ((uint64_t *)addr) + BIT_WORD(nr);
    *p |= mask;
}

static inline void HmClearBit(int nr, volatile uint64_t *addr)
{
    if (addr == NULL) {
        return;
    }

    uint64_t mask = BIT_MASK(nr);
    uint64_t *p   = ((uint64_t *)addr) + BIT_WORD(nr);
    *p &= ~mask;
}

static inline int HmTestBit(int nr, const volatile uint64_t *addr)
{
    if (addr == NULL) {
        return 0;
    }

    return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG - 1)));
}

static inline void PreemptDisable(void)
{
    UINT32 intSave = LOS_IntLock();
    OsPercpuGet()->taskLockCnt++;
    LOS_IntRestore(intSave);
}

static inline void PreemptEnable(void)
{
    UINT32 intSave = LOS_IntLock();
    OsPercpuGet()->taskLockCnt--;
    LOS_IntRestore(intSave);
}

static inline int CmpXchg(unsigned int *lock, int old, int new)
{
    return LOS_AtomicCmpXchg32bits((Atomic *)lock, new, old);
}

static inline int RawSmpProcessorId(void)
{
    return ArchCurrCpuid();
}

static inline int WakeUpProcess(LosTaskCB *p)
{
    LOS_TaskYield();
    return 0;
}

static inline void GetRandomBytesArch(void *data, uint32_t size)
{
    HiRandomHwGetNumber((char *)data, size);
}

static inline void GetUser(unsigned int *value, const unsigned int *userPtr)
{
    copy_from_user(value, userPtr, sizeof(unsigned int));
}

static inline int GetCurrentPid(void)
{
    return OsCurrTaskGet()->processID;
}

/* unsupport restart syscall */
static inline int RestartSyscall(void)
{
    return 0;
}

static inline LosTaskCB *GetProcessGroupLeader(LosTaskCB *task)
{
    if (task == NULL) {
        return NULL;
    }
    return OS_TCB_FROM_TID(OS_PCB_FROM_PID(task->processID)->threadGroupID);
}

static inline unsigned long MsecsToJiffies(const unsigned int m)
{
    if ((int)m < 0) {
        return 0;
    }

    return (m + (MSEC_PER_SEC / HZ) - 1) / (MSEC_PER_SEC / HZ);
}

static inline struct timespec CurrentKernelTime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts;
}

static inline void InitDeferrableWork(struct delayed_work *w, void(* wq)(struct work_struct *))
{
    INIT_DELAYED_WORK(w, wq);
}

static inline int IsKernelThread(LosTaskCB *task)
{
    if (task == NULL) {
        return true;
    }
    return (OS_PCB_FROM_PID(task->processID)->processMode == OS_KERNEL_MODE);
}

static inline int IsTeecdProcess(LosTaskCB *teecd, LosTaskCB *task)
{
    if (teecd == NULL || task == NULL) {
        return 0;
    }
    return teecd->processID == task->processID;
}

typedef mbedtls_sha256_context TeeSha256Context;

static inline void TeeSha256Init(TeeSha256Context *ctx)
{
    mbedtls_sha256_init(ctx);
    (void)mbedtls_sha256_starts_ret(ctx, 0);
}

static inline void TeeSha256Update(TeeSha256Context *ctx, const unsigned char *input, size_t ilen)
{
    (void)mbedtls_sha256_update_ret(ctx, input, ilen);
}

static inline void TeeSha256Final(TeeSha256Context *ctx, unsigned char output[32])
{
    (void)mbedtls_sha256_finish_ret(ctx, output);
}

#endif
