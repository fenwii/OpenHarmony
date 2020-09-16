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

#include "linux/workqueue.h"
#include "los_swtmr_pri.h"
#include "los_event.h"
#include "unistd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define DELAY_TIME  10000

struct workqueue_struct *g_pstSystemWq = NULL;

/* spinlock for workqueue module only available on SMP mode */
LITE_OS_SEC_BSS SPIN_LOCK_INIT(g_workqueueSpin);

STATIC cpu_workqueue_struct *InitCpuWorkqueue(struct workqueue_struct *wq, INT32 cpu);
STATIC UINT32 CreateWorkqueueThread(cpu_workqueue_struct *cwq, INT32 cpu);
STATIC VOID WorkerThread(cpu_workqueue_struct *cwq);
STATIC VOID RunWorkqueue(cpu_workqueue_struct *cwq);
STATIC VOID DelayedWorkTimerFunc(unsigned long data);
typedef BOOL (*OsSortLinkCond)(SWTMR_CTRL_S *swtmr, struct delayed_work *dwork);

/*
 * @ingroup workqueue
 * Obtain the first work in a workqueue.
 */
#define worklist_entry(ptr, type, member)  ((type *)((char *)(ptr)-((UINTPTR)&(((type*)0)->member))))

/*
 * @ingroup workqueue
 * Traverse a workqueue.
 */
#define LIST_FOR_WORK(pos, listObject, type, field)                   \
    for ((pos) = LOS_DL_LIST_ENTRY((listObject)->next, type, field);  \
         &(pos)->field != (listObject);                               \
         (pos) = LOS_DL_LIST_ENTRY((pos)->field.next, type, field))

#define LIST_FOR_WORK_DEL(pos, nextNode, listObject, type, field)         \
    for ((pos) = LOS_DL_LIST_ENTRY((listObject)->next, type, field),      \
         (nextNode) = LOS_DL_LIST_ENTRY((pos)->field.next, type, field);  \
         &(pos)->field != (listObject);                                   \
         (pos) = (nextNode), (nextNode) = LOS_DL_LIST_ENTRY((pos)->field.next, type, field))


void linux_init_delayed_work(struct delayed_work *dwork, work_func_t func)
{
    if ((dwork == NULL) || (func == NULL)) {
        return;
    }
    INIT_WORK(&(dwork->work), func);
    init_timer(&dwork->timer);
    dwork->timer.function = DelayedWorkTimerFunc;
    dwork->timer.data = (unsigned long)(UINTPTR)(dwork);
    dwork->work.work_status = 0;
}

STATIC UINT32 WorkqueueIsEmpty(cpu_workqueue_struct *cwq)
{
    UINT32 ret;
    ret = list_empty(&cwq->worklist);
    return ret;
}

struct workqueue_struct *__create_workqueue_key(char *name,
                                                int singleThread,
                                                int freezeable,
                                                int rt,
                                                struct lock_class_key *key,
                                                const char *lockName)
{
    struct workqueue_struct *wq = NULL;
    cpu_workqueue_struct *cwq   = NULL;
    UINT32 ret;
    (VOID)key;
    (VOID)lockName;

    if (name == NULL) {
        return NULL;
    }

    wq = (struct workqueue_struct *)LOS_MemAlloc(m_aucSysMem0, sizeof(struct workqueue_struct));
    if (wq == NULL) {
        return NULL;
    }

    wq->cpu_wq = (cpu_workqueue_struct *)LOS_MemAlloc(m_aucSysMem0, sizeof(cpu_workqueue_struct));
    if (wq->cpu_wq == NULL) {
        (VOID)LOS_MemFree(m_aucSysMem0, wq);
        return NULL;
    }

    wq->name = name;
    wq->singlethread = singleThread;
    wq->freezeable = freezeable;
    wq->rt = rt;
    wq->delayed_work_count = 0;
    INIT_LIST_HEAD(&wq->list);
    (VOID)LOS_EventInit(&wq->wq_event);

    if (singleThread) {
        cwq = InitCpuWorkqueue(wq, singleThread);
        ret = CreateWorkqueueThread(cwq, singleThread);
    } else {
        LOS_MemFree(m_aucSysMem0, wq->cpu_wq);
        LOS_MemFree(m_aucSysMem0, wq);
        return NULL;
    }

    if (ret) {
        destroy_workqueue(wq);
        wq = NULL;
    }

    return wq;
}

struct workqueue_struct *linux_create_singlethread_workqueue(char *name)
{
    return __create_workqueue_key(name, 1, 0, 0, NULL, NULL);
}

STATIC cpu_workqueue_struct *InitCpuWorkqueue(struct workqueue_struct *wq, INT32 cpu)
{
    cpu_workqueue_struct *cwq = wq->cpu_wq;
    (VOID)cpu;

    cwq->wq = wq;
    INIT_LIST_HEAD(&cwq->worklist);

    return cwq;
}

STATIC UINT32 CreateWorkqueueThread(cpu_workqueue_struct *cwq, INT32 cpu)
{
    struct workqueue_struct *wq = cwq->wq;
    TSK_INIT_PARAM_S taskInitParam = {0};
    UINT32 ret;
    (VOID)cpu;

    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)WorkerThread;
    taskInitParam.uwStackSize  = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    taskInitParam.pcName       = wq->name;
    taskInitParam.usTaskPrio   = 1;
    taskInitParam.auwArgs[0]   = (UINTPTR)cwq;
    taskInitParam.uwResved     = LOS_TASK_STATUS_DETACHED;

    ret = LOS_TaskCreate(&cwq->wq->wq_id, &taskInitParam);
    if (ret != LOS_OK) {
        return LOS_NOK;
    }

    cwq->thread = (task_struct*)OS_TCB_FROM_TID(cwq->wq->wq_id);
    (VOID)LOS_TaskYield();

    return LOS_OK;
}

STATIC VOID WorkerThread(cpu_workqueue_struct *cwqParam)
{
    cpu_workqueue_struct *cwq = cwqParam;

    for (;;) {
        if (WorkqueueIsEmpty(cwq)) {
            (VOID)LOS_EventRead(&(cwq->wq->wq_event), 0x01, LOS_WAITMODE_OR | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
        }
        RunWorkqueue(cwq);
    }
}

STATIC VOID RunWorkqueue(cpu_workqueue_struct *cwq)
{
    struct work_struct *work = NULL;
    UINT32 intSave;
    work_func_t func = NULL;

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);

    if (!WorkqueueIsEmpty(cwq)) {
        work = worklist_entry(cwq->worklist.next, struct work_struct, entry);
        work->work_status |= WORK_STRUCT_RUNNING;
        list_del_init(cwq->worklist.next);
        func = work->func;

        cwq->current_work = work;
        LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
        func(work);
        LOS_SpinLockSave(&g_workqueueSpin, &intSave);
        cwq->current_work = NULL;

        if (work->work_status & WORK_STRUCT_RUNNING) {
            work->work_status &= ~(WORK_STRUCT_RUNNING | WORK_STRUCT_PENDING);
        }
    }

    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
}

STATIC VOID ListAdd(struct list_head *newNode, struct list_head *prev, struct list_head *next)
{
    next->prev = newNode;
    newNode->next = next;
    newNode->prev = prev;
    prev->next = newNode;
}

#ifdef WORKQUEUE_SUPPORT_PRIORITY
STATIC VOID WorkListAdd(struct list_head *newNode, struct list_head *head, UINT32 workPri)
{
    struct work_struct *work = NULL;
    struct list_head *list = head;
    do {
        list = list->next;
        if (list == head) {
            break;
        }
        work = worklist_entry(list, struct work_struct, entry);
    } while (work->work_pri <= workPri);

    ListAdd(newNode, list->prev, list);
}
#else
STATIC VOID WorkListAddTail(struct list_head *newNode, struct list_head *head)
{
    ListAdd(newNode, head->prev, head);
}
#endif

STATIC VOID InsertWork(cpu_workqueue_struct *cwq, struct work_struct *work, struct list_head *head, UINT32 *intSave)
{
#ifdef WORKQUEUE_SUPPORT_PRIORITY
    WorkListAdd(&work->entry, head, work->work_pri);
#else
    WorkListAddTail(&work->entry, head);
#endif
    LOS_SpinUnlockRestore(&g_workqueueSpin, *intSave);
    (VOID)LOS_EventWrite(&(cwq->wq->wq_event), 0x01);
    LOS_SpinLockSave(&g_workqueueSpin, intSave);
}

STATIC VOID QueueWork(cpu_workqueue_struct *cwq, struct work_struct *work, UINT32 *intSave)
{
    InsertWork(cwq, work, &cwq->worklist, intSave);
}

STATIC bool QueueWorkOn(struct workqueue_struct *wq, struct work_struct *work, UINT32 *intSave)
{
    bool ret = FALSE;
    struct work_struct *tmpWork = NULL;

    if (WorkqueueIsEmpty(wq->cpu_wq)) {
        ret = TRUE;
    } else {
        LIST_FOR_WORK(tmpWork, &wq->cpu_wq->worklist, struct work_struct, entry) {
            if (tmpWork == work) {
                return FALSE;
            }
        }
        ret = TRUE;
    }
    QueueWork(wq->cpu_wq, work, intSave);

    return ret;
}

bool linux_queue_work(struct workqueue_struct *wq, struct work_struct *work)
{
    bool ret = FALSE;
    UINT32 intSave;

    if ((wq == NULL) || (wq->name == NULL) || (work == NULL)) {
        return FALSE;
    }
    LOS_SpinLockSave(&g_workqueueSpin, &intSave);

    work->work_status = WORK_STRUCT_PENDING;
    ret = QueueWorkOn(wq, work, &intSave);

    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
    return ret;
}

bool linux_cancel_work_sync(struct work_struct *work)
{
    bool ret = FALSE;

    if (work == NULL) {
        return FALSE;
    }

    if (!work->work_status) {
        ret = FALSE;
    } else if (work->work_status & WORK_STRUCT_RUNNING) {
        ret = FALSE;
    } else {
        ret = TRUE;
    }
    while (work->work_status) {
        (VOID)usleep(DELAY_TIME);
    }
    return ret;
}

bool linux_flush_work(struct work_struct *work)
{
    if (work == NULL) {
        return FALSE;
    }

    if (work->work_status & WORK_STRUCT_PENDING) {
        while (work->work_status) {
            (VOID)usleep(DELAY_TIME);
        }
        return TRUE;
    }
    return FALSE;
}

STATIC VOID DelayedWorkTimerFunc(unsigned long data)
{
    struct delayed_work *dwork = (struct delayed_work *)data;
    UINT32 intSave;

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);
    /* It should have been called from irqsafe timer with irq already off. */
    dwork->wq->delayed_work_count--;
    (VOID)del_timer(&dwork->timer);
    (VOID)QueueWorkOn(dwork->wq, &dwork->work, &intSave);
    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
}

STATIC BOOL OsPerCpuSortLinkSearch(SortLinkAttribute *swtmrSortLink, OsSortLinkCond checkFunc, VOID *arg)
{
    UINT32 i;
    SWTMR_CTRL_S *curSwtmr = NULL;
    SortLinkList *listSorted = NULL;
    LOS_DL_LIST *listObject = NULL;

    for (i = 0; i < OS_TSK_SORTLINK_LEN; i++) {
        listObject = swtmrSortLink->sortLink + i;
        if (LOS_ListEmpty(listObject)) {
            continue;
        }
        listSorted = LOS_DL_LIST_ENTRY((listObject)->pstNext, SortLinkList, sortLinkNode);
        do {
            curSwtmr = LOS_DL_LIST_ENTRY(listSorted, SWTMR_CTRL_S, stSortList);
            if (checkFunc(curSwtmr, arg)) {
                return TRUE;
            }
            listSorted = LOS_DL_LIST_ENTRY(listSorted->sortLinkNode.pstNext, SortLinkList, sortLinkNode);
        } while (&listSorted->sortLinkNode != (listObject));
    }
    return FALSE;
}

BOOL OsSortLinkSearch(OsSortLinkCond checkFunc, VOID *arg)
{
    UINT32 i;
    SortLinkAttribute *swtmrSortLink = NULL;

    for (i = 0; i < LOSCFG_KERNEL_CORE_NUM; i++) {
        swtmrSortLink = &OsPercpuGetByID(i)->swtmrSortLink;
        if (OsPerCpuSortLinkSearch(swtmrSortLink, checkFunc, arg)) {
            return TRUE;
        }
    }
    return FALSE;
}

STATIC BOOL OsDelayWorkQueueCond(SWTMR_CTRL_S *swtmr, struct delayed_work *dwork)
{
    return (((struct delayed_work *)swtmr->uwArg) == dwork);
}

bool queue_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork, unsigned int delayTime)
{
    UINT32 intSave, intSave1;
    struct work_struct *work = NULL;

    if ((wq == NULL) || (wq->name == NULL) || (wq->cpu_wq == NULL) || (dwork == NULL)) {
        return FALSE;
    }

    dwork->wq = wq;
    if (delayTime == 0) {
        return queue_work(dwork->wq, &dwork->work);
    }

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);
    LOS_SpinLockSave(&g_swtmrSpin, &intSave1);
    if (OsSortLinkSearch(OsDelayWorkQueueCond, dwork)) {
        LOS_SpinUnlockRestore(&g_swtmrSpin, intSave1);
        LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
        return FALSE;
    }
    LOS_SpinUnlockRestore(&g_swtmrSpin, intSave1);
    if (!WorkqueueIsEmpty(wq->cpu_wq)) {
        LIST_FOR_WORK(work, &wq->cpu_wq->worklist, struct work_struct, entry) {
            if (work == &dwork->work) {
                LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
                return FALSE;
            }
        }
    }
    dwork->timer.expires = delayTime;
    add_timer(&dwork->timer);
    wq->delayed_work_count++;
    dwork->work.work_status = WORK_STRUCT_PENDING;
    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
    return TRUE;
}


STATIC BOOL OsDelayWorkCancelCond(SWTMR_CTRL_S *swtmr, struct delayed_work *dwork)
{
    if ((swtmr->usTimerID == dwork->timer.timerid) &&
        (swtmr->ucState == OS_SWTMR_STATUS_TICKING)) {
        return TRUE;
    }
    return FALSE;
}

bool linux_cancel_delayed_work(struct delayed_work *dwork)
{
    struct work_struct *work = NULL;
    struct work_struct *workNext = NULL;
    UINT32 intSave, intSave1;
    bool ret = FALSE;

    if ((dwork == NULL) || (dwork->wq == NULL)) {
        return FALSE;
    }

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);

    if (dwork->work.work_status & WORK_STRUCT_PENDING) {
        LOS_SpinLockSave(&g_swtmrSpin, &intSave1);
        if (OsSortLinkSearch(OsDelayWorkCancelCond, dwork)) {
            LOS_SpinUnlockRestore(&g_swtmrSpin, intSave1);
            (VOID)del_timer(&dwork->timer);
            dwork->work.work_status = 0;
            dwork->wq->delayed_work_count--;
            LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
            return TRUE;
        }

        LOS_SpinUnlockRestore(&g_swtmrSpin, intSave1);
        if (dwork->work.work_status & WORK_STRUCT_RUNNING) {
            ret = FALSE;
        } else if (dwork->work.work_status & WORK_STRUCT_PENDING) {
            LIST_FOR_WORK_DEL(work, workNext, &dwork->wq->cpu_wq->worklist, struct work_struct, entry) {
                if (work == &dwork->work) {
                    list_del_init(&work->entry);
                    dwork->work.work_status = 0;
                    ret = TRUE;
                    break;
                }
            }
        }
    }

    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
    return ret;
}

bool linux_cancel_delayed_work_sync(struct delayed_work *dwork)
{
    return cancel_delayed_work(dwork);
}

bool linux_flush_delayed_work(struct delayed_work *dwork)
{
    UINT32 intSave, intSave1;

    if ((dwork == NULL) || (dwork->wq == NULL)) {
        return FALSE;
    }

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);
    if (!(dwork->work.work_status & WORK_STRUCT_PENDING)) {
        LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
        return FALSE;
    }

    LOS_SpinLockSave(&g_swtmrSpin, &intSave1);
    if (OsSortLinkSearch(OsDelayWorkCancelCond, dwork)) {
        LOS_SpinUnlockRestore(&g_swtmrSpin, intSave1);
        (VOID)del_timer(&dwork->timer);
        dwork->wq->delayed_work_count--;
        LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
        (VOID)queue_work(dwork->wq, &dwork->work);
    } else {
        LOS_SpinUnlockRestore(&g_swtmrSpin, intSave1);
        LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
    }
    (VOID)flush_work(&dwork->work);
    return TRUE;
}

unsigned int linux_work_busy(struct work_struct *work)
{
    UINT32 ret = 0;

    if (work == NULL) {
        return FALSE;
    }

    if (work->work_status & WORK_STRUCT_PENDING) {
        ret |= WORK_BUSY_PENDING;
    }
    if (work->work_status & WORK_STRUCT_RUNNING) {
        ret |= WORK_BUSY_RUNNING;
    }
    return ret;
}

bool linux_schedule_work(struct work_struct *work)
{
    bool ret = FALSE;
    UINT32 intSave;

    if ((g_pstSystemWq == NULL) || (g_pstSystemWq->name == NULL) || (work == NULL)) {
        return FALSE;
    }

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);

    work->work_status = WORK_STRUCT_PENDING;
    ret = QueueWorkOn(g_pstSystemWq, work, &intSave);

    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
    return ret;
}

bool linux_schedule_delayed_work(struct delayed_work *dwork, unsigned int delayTime)
{
    bool ret = FALSE;

    if ((g_pstSystemWq == NULL) || (dwork == NULL)) {
        return FALSE;
    }

    ret = queue_delayed_work(g_pstSystemWq, dwork, delayTime);

    return ret;
}

static void drain_workqueue(struct workqueue_struct *wq)
{
    UINT32 intSave;
    while (1) {
        (VOID)usleep(DELAY_TIME);
        LOS_SpinLockSave(&g_workqueueSpin, &intSave);
        if (WorkqueueIsEmpty(wq->cpu_wq) && (wq->delayed_work_count == 0)) {
            break;
        }

        LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
    }
    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
}

void linux_destroy_workqueue(struct workqueue_struct *wq)
{
    UINT32 intSave;
    if (wq == NULL) {
        return;
    }

    /* Drain it before proceeding with destruction */
    drain_workqueue(wq);

    (VOID)LOS_TaskDelete(wq->wq_id);

    LOS_SpinLockSave(&g_workqueueSpin, &intSave);
    wq->name = NULL;
    list_del_init(&wq->list);
    (VOID)LOS_EventDestroy(&(wq->wq_event));

    (VOID)LOS_MemFree(m_aucSysMem0, wq->cpu_wq);
    (VOID)LOS_MemFree(m_aucSysMem0, wq);
    LOS_SpinUnlockRestore(&g_workqueueSpin, intSave);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif