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

#include "los_event_pri.h"
#include "los_priqueue_pri.h"
#include "los_task_pri.h"
#include "los_hw.h"
#include "los_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

LITE_OS_SEC_TEXT_INIT UINT32 LOS_EventInit(PEVENT_CB_S eventCB)
{
    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }
    eventCB->uwEventID = 0;
    LOS_ListInit(&eventCB->stEventList);
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_EventPoll(UINT32 *eventID, UINT32 eventMask, UINT32 mode)
{
    UINT32 ret = 0;
    UINTPTR intSave;

    intSave = LOS_IntLock();
    if (mode & LOS_WAITMODE_OR) {
        if ((*eventID & eventMask) != 0) {
            ret = *eventID & eventMask;
        }
    } else {
        if ((eventMask != 0) && (eventMask == (*eventID & eventMask))) {
            ret = *eventID & eventMask;
        }
    }
    if (ret && (mode & LOS_WAITMODE_CLR)) {
        *eventID = *eventID & ~(ret);
    }
    LOS_IntRestore(intSave);
    return ret;
}

LITE_OS_SEC_TEXT STATIC_INLINE UINT32 OsEventReadParamCheck(PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode)
{
    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }
    if ((eventCB->stEventList.pstNext == NULL) || (eventCB->stEventList.pstPrev == NULL)) {
        return LOS_ERRNO_EVENT_NOT_INITIALIZED;
    }
    if (eventMask == 0) {
        return LOS_ERRNO_EVENT_EVENTMASK_INVALID;
    }
    if (eventMask & LOS_ERRTYPE_ERROR) {
        return LOS_ERRNO_EVENT_SETBIT_INVALID;
    }
    if (((mode & LOS_WAITMODE_OR) && (mode & LOS_WAITMODE_AND)) ||
        (mode & ~(LOS_WAITMODE_OR | LOS_WAITMODE_AND | LOS_WAITMODE_CLR)) ||
        !(mode & (LOS_WAITMODE_OR | LOS_WAITMODE_AND))) {
        return LOS_ERRNO_EVENT_FLAGS_INVALID;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_EventRead(PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode, UINT32 timeOut)
{
    UINT32 ret;
    UINTPTR intSave;
    LosTaskCB *runTsk = NULL;

    ret = OsEventReadParamCheck(eventCB, eventMask, mode);
    if (ret != LOS_OK) {
        return ret;
    }

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_EVENT_READ_IN_INTERRUPT;
    }
    intSave = LOS_IntLock();
    ret = LOS_EventPoll(&(eventCB->uwEventID), eventMask, mode);
    if (ret == 0) {
        if (timeOut == 0) {
            LOS_IntRestore(intSave);
            return ret;
        }

        if (g_losTaskLock) {
            LOS_IntRestore(intSave);
            return LOS_ERRNO_EVENT_READ_IN_LOCK;
        }
        runTsk = g_losTask.runTask;
        runTsk->eventMask = eventMask;
        runTsk->eventMode = mode;
        OsTaskWait(&eventCB->stEventList, OS_TASK_STATUS_PEND, timeOut);
        LOS_IntRestore(intSave);
        LOS_Schedule();

        if (runTsk->taskStatus & OS_TASK_STATUS_TIMEOUT) {
            intSave = LOS_IntLock();
            runTsk->taskStatus &= (~OS_TASK_STATUS_TIMEOUT);
            LOS_IntRestore(intSave);
            return LOS_ERRNO_EVENT_READ_TIMEOUT;
        }
        intSave = LOS_IntLock();
        ret = LOS_EventPoll(&eventCB->uwEventID, eventMask, mode);
        LOS_IntRestore(intSave);
    } else {
        LOS_IntRestore(intSave);
    }
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_EventWrite(PEVENT_CB_S eventCB, UINT32 events)
{
    LosTaskCB *resumedTask = NULL;
    LosTaskCB *nextTask = (LosTaskCB *)NULL;
    UINTPTR intSave;
    UINT8 exitFlag = 0;
    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }
    if ((eventCB->stEventList.pstNext == NULL) || (eventCB->stEventList.pstPrev == NULL)) {
        return LOS_ERRNO_EVENT_NOT_INITIALIZED;
    }
    if (events & LOS_ERRTYPE_ERROR) {
        return LOS_ERRNO_EVENT_SETBIT_INVALID;
    }
    intSave = LOS_IntLock();
    eventCB->uwEventID |= events;
    if (!LOS_ListEmpty(&eventCB->stEventList)) {
        for (resumedTask = LOS_DL_LIST_ENTRY((&eventCB->stEventList)->pstNext, LosTaskCB, pendList);
             &resumedTask->pendList != (&eventCB->stEventList);) {
            nextTask = LOS_DL_LIST_ENTRY(resumedTask->pendList.pstNext, LosTaskCB, pendList);

            if (((resumedTask->eventMode & LOS_WAITMODE_OR) && (resumedTask->eventMask & events) != 0) ||
                ((resumedTask->eventMode & LOS_WAITMODE_AND) &&
                 ((resumedTask->eventMask & eventCB->uwEventID) == resumedTask->eventMask))) {
                exitFlag = 1;

                OsTaskWake(resumedTask, OS_TASK_STATUS_PEND);
            }
            resumedTask = nextTask;
        }

        if (exitFlag == 1) {
            LOS_IntRestore(intSave);
            LOS_Schedule();
            return LOS_OK;
        }
    }

    LOS_IntRestore(intSave);
    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_EventDestroy(PEVENT_CB_S eventCB)
{
    UINTPTR intSave;
    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }
    intSave = LOS_IntLock();

    if (!LOS_ListEmpty(&eventCB->stEventList)) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_EVENT_SHOULD_NOT_DESTORY;
    }
    eventCB->stEventList.pstNext = (LOS_DL_LIST *)NULL;
    eventCB->stEventList.pstPrev = (LOS_DL_LIST *)NULL;
    LOS_IntRestore(intSave);
    return LOS_OK;
}
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_EventClear(PEVENT_CB_S eventCB, UINT32 events)
{
    UINTPTR intSave;
    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }
    intSave = LOS_IntLock();
    eventCB->uwEventID &= events;
    LOS_IntRestore(intSave);
    return LOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

