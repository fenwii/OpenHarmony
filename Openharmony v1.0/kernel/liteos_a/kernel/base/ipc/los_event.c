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
#include "los_task_pri.h"
#include "los_spinlock.h"
#include "los_mp.h"
#include "los_percpu_pri.h"

#if (LOSCFG_BASE_CORE_SWTMR == YES)
#include "los_exc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

LITE_OS_SEC_TEXT_INIT UINT32 LOS_EventInit(PEVENT_CB_S eventCB)
{
    UINT32 intSave;

    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }

    intSave = LOS_IntLock();
    eventCB->uwEventID = 0;
    LOS_ListInit(&eventCB->stEventList);
    LOS_IntRestore(intSave);
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 OsEventParamCheck(const VOID *ptr, UINT32 eventMask, UINT32 mode)
{
    if (ptr == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
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

LITE_OS_SEC_TEXT UINT32 OsEventPoll(UINT32 *eventID, UINT32 eventMask, UINT32 mode)
{
    UINT32 ret = 0;

    LOS_ASSERT(OsIntLocked());
    LOS_ASSERT(LOS_SpinHeld(&g_taskSpin));

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
        *eventID = *eventID & ~ret;
    }

    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 OsEventReadCheck(const PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode)
{
    UINT32 ret;
    LosTaskCB *runTask = NULL;

    ret = OsEventParamCheck(eventCB, eventMask, mode);
    if (ret != LOS_OK) {
        return ret;
    }

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_EVENT_READ_IN_INTERRUPT;
    }

    runTask = OsCurrTaskGet();
    if (runTask->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        OsBackTrace();
        return LOS_ERRNO_EVENT_READ_IN_SYSTEM_TASK;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT STATIC UINT32 OsEventReadImp(PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode,
                                              UINT32 timeout, BOOL once)
{
    UINT32 ret = 0;
    LosTaskCB *runTask = OsCurrTaskGet();

    if (once == FALSE) {
        ret = OsEventPoll(&eventCB->uwEventID, eventMask, mode);
    }

    if (ret == 0) {
        if (timeout == 0) {
            return ret;
        }

        if (!OsPreemptableInSched()) {
            return LOS_ERRNO_EVENT_READ_IN_LOCK;
        }

        runTask->eventMask = eventMask;
        runTask->eventMode = mode;
        runTask->taskEvent = eventCB;
        ret = OsTaskWait(&eventCB->stEventList, timeout, TRUE);
        if (ret == LOS_ERRNO_TSK_TIMEOUT) {
            runTask->taskEvent = NULL;
            return LOS_ERRNO_EVENT_READ_TIMEOUT;
        }

        ret = OsEventPoll(&eventCB->uwEventID, eventMask, mode);
    }
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT32 OsEventRead(PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode, UINT32 timeout,
                                           BOOL once)
{
    UINT32 ret;
    UINT32 intSave;

    ret = OsEventReadCheck(eventCB, eventMask, mode);
    if (ret != LOS_OK) {
        return ret;
    }

    SCHEDULER_LOCK(intSave);
    ret = OsEventReadImp(eventCB, eventMask, mode, timeout, once);
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT STATIC UINT8 OsEventResume(LosTaskCB *resumedTask, const PEVENT_CB_S eventCB, UINT32 events)
{
    UINT8 exitFlag = 0;

    if (((resumedTask->eventMode & LOS_WAITMODE_OR) && ((resumedTask->eventMask & events) != 0)) ||
        ((resumedTask->eventMode & LOS_WAITMODE_AND) &&
        ((resumedTask->eventMask & eventCB->uwEventID) == resumedTask->eventMask))) {
        exitFlag = 1;

        resumedTask->taskEvent = NULL;
        OsTaskWake(resumedTask);
    }

    return exitFlag;
}

LITE_OS_SEC_TEXT VOID OsEventWriteUnsafe(PEVENT_CB_S eventCB, UINT32 events, BOOL once, UINT8 *exitFlag)
{
    LosTaskCB *resumedTask = NULL;
    LosTaskCB *nextTask = NULL;
    BOOL schedFlag = FALSE;

    eventCB->uwEventID |= events;
    if (!LOS_ListEmpty(&eventCB->stEventList)) {
        for (resumedTask = LOS_DL_LIST_ENTRY((&eventCB->stEventList)->pstNext, LosTaskCB, pendList);
             &resumedTask->pendList != &eventCB->stEventList;) {
            nextTask = LOS_DL_LIST_ENTRY(resumedTask->pendList.pstNext, LosTaskCB, pendList);
            if (OsEventResume(resumedTask, eventCB, events)) {
                schedFlag = TRUE;
            }
            if (once == TRUE) {
                break;
            }
            resumedTask = nextTask;
        }
    }

    if ((exitFlag != NULL) && (schedFlag == TRUE)) {
        *exitFlag = 1;
    }
}

LITE_OS_SEC_TEXT STATIC UINT32 OsEventWrite(PEVENT_CB_S eventCB, UINT32 events, BOOL once)
{
    UINT32 intSave;
    UINT8 exitFlag = 0;

    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }

    if (events & LOS_ERRTYPE_ERROR) {
        return LOS_ERRNO_EVENT_SETBIT_INVALID;
    }

    SCHEDULER_LOCK(intSave);
    OsEventWriteUnsafe(eventCB, events, once, &exitFlag);
    SCHEDULER_UNLOCK(intSave);

    if (exitFlag == 1) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_EventPoll(UINT32 *eventID, UINT32 eventMask, UINT32 mode)
{
    UINT32 ret;
    UINT32 intSave;

    ret = OsEventParamCheck((VOID *)eventID, eventMask, mode);
    if (ret != LOS_OK) {
        return ret;
    }

    SCHEDULER_LOCK(intSave);
    ret = OsEventPoll(eventID, eventMask, mode);
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_EventRead(PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode, UINT32 timeout)
{
    return OsEventRead(eventCB, eventMask, mode, timeout, FALSE);
}

LITE_OS_SEC_TEXT UINT32 LOS_EventWrite(PEVENT_CB_S eventCB, UINT32 events)
{
    return OsEventWrite(eventCB, events, FALSE);
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsEventReadOnce(PEVENT_CB_S eventCB, UINT32 eventMask, UINT32 mode,
                                              UINT32 timeout)
{
    return OsEventRead(eventCB, eventMask, mode, timeout, TRUE);
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsEventWriteOnce(PEVENT_CB_S eventCB, UINT32 events)
{
    return OsEventWrite(eventCB, events, TRUE);
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_EventDestroy(PEVENT_CB_S eventCB)
{
    UINT32 intSave;

    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }

    SCHEDULER_LOCK(intSave);
    if (!LOS_ListEmpty(&eventCB->stEventList)) {
        SCHEDULER_UNLOCK(intSave);
        return LOS_ERRNO_EVENT_SHOULD_NOT_DESTORY;
    }

    eventCB->uwEventID = 0;
    LOS_ListDelInit(&eventCB->stEventList);
    SCHEDULER_UNLOCK(intSave);

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_EventClear(PEVENT_CB_S eventCB, UINT32 events)
{
    UINT32 intSave;

    if (eventCB == NULL) {
        return LOS_ERRNO_EVENT_PTR_NULL;
    }
    SCHEDULER_LOCK(intSave);
    eventCB->uwEventID &= events;
    SCHEDULER_UNLOCK(intSave);

    return LOS_OK;
}

#ifdef LOSCFG_COMPAT_POSIX
LITE_OS_SEC_TEXT UINT32 OsEventReadWithCond(const EventCond *cond, PEVENT_CB_S eventCB,
                                            UINT32 eventMask, UINT32 mode, UINT32 timeout)
{
    UINT32 ret;
    UINT32 intSave;

    ret = OsEventReadCheck(eventCB, eventMask, mode);
    if (ret != LOS_OK) {
        return ret;
    }

    SCHEDULER_LOCK(intSave);

    if (*cond->realValue != cond->value) {
        eventCB->uwEventID &= cond->clearEvent;
        goto OUT;
    }

    ret = OsEventReadImp(eventCB, eventMask, mode, timeout, FALSE);
OUT:
    SCHEDULER_UNLOCK(intSave);
    return ret;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
