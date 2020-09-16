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

#include "los_event.h"
#include "linux/semaphore.h"
#include "linux/wait.h"
#include "sys/types.h"
#include "poll.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

int _sema_init(losMutexDef_t *sem, unsigned int value)
{
    UINT32 semHandle;
    UINT32 ret;

    if ((sem == NULL) || (value > OS_SEM_COUNT_MAX)) {
        return -1;
    }

    ret = LOS_SemCreate((UINT16)value, &semHandle);
    if (ret != LOS_OK) {
        return -1;
    }

    sem->sem = GET_SEM(semHandle);

    return 0;
}

int _sema_lock(losMutexDef_t *sem)
{
    UINT32 ret;

    if ((sem == NULL) || (sem->sem == NULL)) {
        return -1;
    }

    if ((UINTPTR)sem->sem == UNINIT_VALUE) {
        if (_sema_init(sem, sem->count) != 0) {
            return -1;
        }
    }

    ret = LOS_SemPend(sem->sem->semID, LOS_WAIT_FOREVER);
    if (ret == LOS_OK) {
        return 0;
    }

    return -1;
}

int _sema_trylock(losMutexDef_t *sem)
{
    UINT32 ret;

    if ((sem == NULL) || (sem->sem == NULL)) {
        return -1;
    }

    ret = LOS_SemPend(sem->sem->semID, LOS_NO_WAIT);
    if (ret == LOS_OK) {
        return 0;
    }

    return -1;
}

int _sema_unlock(losMutexDef_t *sem)
{
    UINT32 ret;

    if ((sem == NULL) || (sem->sem == NULL)) {
        return -1;
    }

    ret = LOS_SemPost(sem->sem->semID);
    if (ret != LOS_OK) {
        return -1;
    }

    return 0;
}

int _sema_destory(losMutexDef_t *sem)
{
    UINT32 ret;

    if ((sem == NULL) || (sem->sem == NULL)) {
        return -1;
    }
    if ((UINTPTR)sem->sem == UNINIT_VALUE) {
        return -1;
    }
    ret = LOS_SemDelete(sem->sem->semID);
    if (ret != LOS_OK) {
        return -1;
    }

    return 0;
}

void __init_waitqueue_head(wait_queue_head_t *wait)
{
    if (wait == NULL) {
        return;
    }
    (VOID)LOS_EventInit(&wait->stEvent);
    spin_lock_init(&wait->lock);
    LOS_ListInit(&wait->poll_queue);
}

void __wake_up_interruptible(wait_queue_head_t *wait)
{
    if (wait == NULL) {
        return;
    }
    (VOID)LOS_EventWrite(&wait->stEvent, 0x1);
    notify_poll(wait);
}

void __wake_up_interruptible_poll(wait_queue_head_t *wait, pollevent_t key)
{
    if (wait == NULL) {
        return;
    }
    (VOID)LOS_EventWrite(&wait->stEvent, 0x1);
    notify_poll_with_key(wait, key);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
