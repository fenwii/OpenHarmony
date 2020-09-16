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

#include "linux/completion.h"
#include "limits.h"
#include "los_task_pri.h"
#include "los_mp.h"
#include "los_exc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

void linux_init_completion(struct completion *x)
{
    UINT32 intSave;

    if (x == NULL) {
        PRINT_ERR("%s failed, input param is invalid\n", __FUNCTION__);
        return;
    }

    SCHEDULER_LOCK(intSave);
    LOS_ListInit(&x->comList);
    x->comCount = 0;
    x->state = COMPLETION_ONE;
    SCHEDULER_UNLOCK(intSave);
    return;
}

STATIC VOID CompletionSchedule(VOID)
{
    LOS_MpSchedule(OS_MP_CPU_ALL);
    LOS_Schedule();
}

void linux_complete(struct completion *x)
{
    UINT32 intSave;
    LosTaskCB *resumedTask = NULL;

    if (x == NULL) {
        PRINT_ERR("%s failed, input param is invalid\n", __FUNCTION__);
        return;
    }

    SCHEDULER_LOCK(intSave);
    if (!LOS_ListEmpty(&x->comList)) {
        resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(x->comList)));
        OsTaskWake(resumedTask);
        SCHEDULER_UNLOCK(intSave);
        CompletionSchedule();
        return;
    } else if (x->comCount != UINT_MAX) {
        x->comCount++;
    }
    SCHEDULER_UNLOCK(intSave);
    return;
}

STATIC BOOL NoNeedWait(struct completion *x)
{
    if (x->state == COMPLETION_ALL) {
        return TRUE;
    }
    if (x->comCount > 0) {
        x->comCount--;
        return TRUE;
    }
    return FALSE;
}

void linux_wait_for_completion(struct completion *x)
{
    UINT32 intSave;

    if (x == NULL) {
        PRINT_ERR("%s failed, input param is invalid\n", __FUNCTION__);
        return;
    }

    if (OS_INT_ACTIVE) {
        PRINT_ERR("Calling %s in interrupt callback is not allowed.\n", __FUNCTION__);
        OsBackTrace();
        return;
    }

    /* DO NOT Call blocking API in system tasks */
    if (OsCurrTaskGet()->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        PRINTK("Warning: DO NOT call %s in system tasks.\n", __FUNCTION__);
        OsBackTrace();
        return;
    }

    SCHEDULER_LOCK(intSave);
    if (NoNeedWait(x) == TRUE) {
        SCHEDULER_UNLOCK(intSave);
        return;
    }

    (void)OsTaskWait(&x->comList, LOS_WAIT_FOREVER, TRUE);
    SCHEDULER_UNLOCK(intSave);
    return;
}

unsigned long linux_wait_for_completion_timeout(struct completion *x, unsigned long timeout)
{
    UINT32 ret;
    UINT32 intSave;
    UINT64 lastTick;
    LosTaskCB *runTask = NULL;

    if (x == NULL) {
        PRINT_ERR("%s failed, input param is invalid\n", __FUNCTION__);
        return timeout;
    }

    if (OS_INT_ACTIVE) {
        PRINT_ERR("Calling %s in interrupt callback is not allowed.\n", __FUNCTION__);
        OsBackTrace();
        return timeout;
    }

    runTask = OsCurrTaskGet();
    /* DO NOT Call blocking API in systems task */
    if (runTask->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        PRINTK("Warning: DO NOT call %s in system tasks.\n", __FUNCTION__);
        OsBackTrace();
        return timeout;
    }

    SCHEDULER_LOCK(intSave);
    lastTick = LOS_TickCountGet();

    if (NoNeedWait(x) == TRUE) {
        SCHEDULER_UNLOCK(intSave);
        return timeout ? timeout : 1;
    }

    if (timeout == 0) {
        SCHEDULER_UNLOCK(intSave);
        return timeout;
    }

    ret = OsTaskWait(&x->comList, timeout, TRUE);
    if (ret == LOS_ERRNO_TSK_TIMEOUT) {
        SCHEDULER_UNLOCK(intSave);
        return 0;
    }

    lastTick = LOS_TickCountGet() - lastTick;
    SCHEDULER_UNLOCK(intSave);

    return (unsigned long)((timeout > lastTick) ? (timeout - lastTick) : 1);
}

void linux_complete_all(struct completion *x)
{
    UINT32 intSave;
    LosTaskCB *resumedTask = NULL;

    if (x == NULL) {
        PRINT_ERR("%s failed, input param is invalid\n", __FUNCTION__);
        return;
    }

    SCHEDULER_LOCK(intSave);

    x->state = COMPLETION_ALL;
    if (LOS_ListEmpty(&x->comList)) {
        SCHEDULER_UNLOCK(intSave);
        return;
    }

    while (!LOS_ListEmpty(&x->comList)) {
        resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(x->comList)));
        OsTaskWake(resumedTask);
    }
    SCHEDULER_UNLOCK(intSave);
    CompletionSchedule();

    return;
}

int linux_completion_done(struct completion *x)
{
    UINT32 intSave;
    int isdone;

    SCHEDULER_LOCK(intSave);
    isdone = (x->comCount != 0);
    SCHEDULER_UNLOCK(intSave);
    return (isdone);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
