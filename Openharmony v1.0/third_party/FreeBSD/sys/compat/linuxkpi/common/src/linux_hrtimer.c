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

#include "linux/hrtimer.h"
#include "los_task_pri.h"
#include "los_hwi.h"
#include "asm/hal_platform_ints.h"
#include "los_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define US_PER_SECOND 1000000

/* spinlock for hrtimer module only available on SMP mode */
LITE_OS_SEC_BSS SPIN_LOCK_INIT(g_hrtimerSpin);

LITE_OS_SEC_BSS struct hrtimer_list_node *g_hrtimerList;

STATIC VOID HandlerNodeAdd(struct hrtimer_list_node *htrimer, struct handler_list_node *handlerNode)
{
    struct handler_list_node *tmpNode = NULL;

    if (htrimer == NULL) {
        return;
    }

    tmpNode = htrimer->HandlerHead;
    if (tmpNode == NULL) {
        htrimer->HandlerHead = handlerNode;
    } else {
        while (tmpNode->pstNext != NULL) {
            tmpNode = tmpNode->pstNext;
        }
        tmpNode->pstNext = handlerNode;
    } /* FIFO */
}

STATIC VOID HrtimerNodeAdd(struct hrtimer_list_node *htrimer, struct handler_list_node *handlerNode)
{
    struct hrtimer_list_node *prevNode = NULL;
    struct hrtimer_list_node *curNode = NULL;
    struct hrtimer_list_node *tmpNode = NULL;
    UINT32 temp;

    if (g_hrtimerList == NULL) {
        g_hrtimerList = htrimer;
        HrtimerClockStart(htrimer->set_time_reload);
    } else {
        temp = HrtimerClockValueGet();
        g_hrtimerList->set_time_reload = temp;
        curNode = g_hrtimerList;
        while (curNode != NULL) {
            if (curNode->set_time_reload > htrimer->set_time_reload) {
                break;
            }
            if (curNode->set_time_reload == htrimer->set_time_reload) {
                HandlerNodeAdd(curNode, handlerNode);
                (VOID)LOS_MemFree(m_aucSysMem0, htrimer);
                return;
            }
            htrimer->set_time_reload -= curNode->set_time_reload;
            prevNode = curNode;
            curNode = curNode->pstNext;
        }
        if (curNode == g_hrtimerList) {
            tmpNode = g_hrtimerList;
            HrtimerClockStop();
            HrtimerClockStart(htrimer->set_time_reload);

            tmpNode->set_time_reload -= htrimer->set_time_reload;
            htrimer->pstNext = curNode;
            g_hrtimerList = htrimer;
        } else if (curNode == NULL) {
            prevNode->pstNext = htrimer;
        } else {
            htrimer->pstNext = curNode;
            prevNode->pstNext = htrimer;
            curNode->set_time_reload -= htrimer->set_time_reload;
        }
    }
    if (handlerNode != NULL) {
        HandlerNodeAdd(htrimer, handlerNode);
    }
}

STATIC VOID HrtimerHandlerRunAddNode(struct hrtimer_list_node *hrtimer, struct handler_list_node *handlerHead)
{
    if (handlerHead == NULL) {
        (VOID)LOS_MemFree(m_aucSysMem0, hrtimer);
    } else {
        hrtimer->set_time_reload = (UINT32)((hrtimer->_softexpires.tv.sec * US_PER_SECOND +
                                    hrtimer->_softexpires.tv.usec) * HRTIMER_PERUS);
        LOS_SpinLock(&g_hrtimerSpin);
        HrtimerNodeAdd(hrtimer, handlerHead);
        LOS_SpinUnlock(&g_hrtimerSpin);
    }
}

STATIC VOID HrtimerHandlerRun(VOID)
{
    struct hrtimer_list_node *hrtimer = NULL;
    struct handler_list_node *curNode = NULL;
    struct handler_list_node *handler = NULL;
    struct handler_list_node *handlerTail = NULL;
    struct handler_list_node *handlerHead = NULL;
    struct hrtimer timer;
    enum hrtimer_restart restart;

    LOS_SpinLock(&g_hrtimerSpin);
    if (g_hrtimerList == NULL) {
        LOS_SpinUnlock(&g_hrtimerSpin);
        return;
    }
    hrtimer = g_hrtimerList;
    g_hrtimerList = hrtimer->pstNext;
    if (g_hrtimerList != NULL) {
        HrtimerClockStop();
        HrtimerClockStart(g_hrtimerList->set_time_reload);
    }
    LOS_SpinUnlock(&g_hrtimerSpin);

    timer._softexpires.tv.usec = hrtimer->_softexpires.tv.usec;
    timer._softexpires.tv.sec = hrtimer->_softexpires.tv.sec;
    handler = hrtimer->HandlerHead;
    hrtimer->pstNext = NULL;
    hrtimer->HandlerHead = NULL;

    while ((handler != NULL) && (handler->pfnHandler != NULL)) {
        timer.function = handler->pfnHandler;
        restart = handler->pfnHandler(&timer);
        curNode = handler;
        handler = handler->pstNext;
        curNode->pstNext = NULL;

        if (restart == HRTIMER_NORESTART) {
            (VOID)LOS_MemFree(m_aucSysMem0, curNode);
        } else if (restart == HRTIMER_RESTART) {
            if (handlerHead != NULL) {
                handlerTail->pstNext = curNode;
                handlerTail = curNode;
            } else {
                handlerHead = curNode;
                handlerTail = curNode;
            }
        } else {
            PRINT_ERR("The return value of hrtimer function is not defined!\n");
        }
    }

    HrtimerHandlerRunAddNode(hrtimer, handlerHead);
}

STATIC VOID HrtimerListScan(VOID)
{
    HrtimerClockIrqClear();
    HrtimerHandlerRun();
}

STATIC VOID GetHandlerNodePosition(const struct hrtimer *timer, struct hrtimer_list_node *hrtimerNode,
                                   struct handler_list_node **prevNode, struct handler_list_node **curNode)
{
    struct handler_list_node *curHandler = NULL;
    struct handler_list_node *prevHandler = NULL;

    curHandler = hrtimerNode->HandlerHead;
    while (curHandler != NULL) {
        if ((curHandler->pfnHandler == timer->function) &&
            (curHandler->_softexpires.tv.sec == timer->_softexpires.tv.sec) &&
            (curHandler->_softexpires.tv.usec == timer->_softexpires.tv.usec)) {
            *prevNode = prevHandler;
            *curNode = curHandler;
            return;
        }
        prevHandler = curHandler;
        curHandler = curHandler->pstNext;
    }
}

STATIC VOID GetHrtimerNodePosition(const struct hrtimer *timer, struct hrtimer_list_node **prevNode,
                                   struct hrtimer_list_node **curNode)
{
    struct handler_list_node *curHandler = NULL;

    *curNode = g_hrtimerList;
    while (*curNode != NULL) {
        curHandler = (*curNode)->HandlerHead;
        while (curHandler != NULL) {
            if ((curHandler->pfnHandler == timer->function) &&
                (curHandler->_softexpires.tv.sec == timer->_softexpires.tv.sec) &&
                (curHandler->_softexpires.tv.usec == timer->_softexpires.tv.usec)) {
                return;
            }
            curHandler = curHandler->pstNext;
        }
        *prevNode = *curNode;
        *curNode = (*curNode)->pstNext;
    }
}

STATIC struct hrtimer_list_node *HrtimerListNodeInit(union ktime time)
{
    struct hrtimer_list_node *hrtimer = (struct hrtimer_list_node *)LOS_MemAlloc(m_aucSysMem0,
                                                                                 sizeof(struct hrtimer_list_node));
    if (hrtimer == NULL) {
        return NULL;
    }
    hrtimer->_softexpires = time;
    hrtimer->set_time_reload = (UINT32)((time.tv.sec * US_PER_SECOND + time.tv.usec) * HRTIMER_PERUS);
    hrtimer->HandlerHead = NULL;
    hrtimer->pstNext = NULL;
    return hrtimer;
}

STATIC UINT32 ChangeNodePosition(struct hrtimer_list_node *prevNode, struct hrtimer_list_node *curNode,
                                 struct handler_list_node *prevHandler, struct handler_list_node *curHandler,
                                 union ktime time)
{
    struct hrtimer_list_node *htrimer = NULL;

    if ((prevHandler != NULL) || (curHandler->pstNext != NULL)) {
        if (prevHandler == NULL) {
            curNode->HandlerHead = curHandler->pstNext;
        } else {
            prevHandler->pstNext = curHandler->pstNext;
        }

        curHandler->pstNext = NULL;
        curHandler->_softexpires = time;

        htrimer = HrtimerListNodeInit(time);
        if (htrimer == NULL) {
            return LOS_NOK;
        }

        HrtimerNodeAdd(htrimer, curHandler);
    } else {
        if (curNode->pstNext != NULL) {
            if (curNode == g_hrtimerList) {
                g_hrtimerList = curNode->pstNext;
                g_hrtimerList->set_time_reload += HrtimerClockValueGet();
                HrtimerClockStop();
                HrtimerClockStart(g_hrtimerList->set_time_reload);
            } else {
                prevNode->pstNext = curNode->pstNext;
                curNode->pstNext->set_time_reload += curNode->set_time_reload;
            }
        } else {
            if (curNode == g_hrtimerList) {
                g_hrtimerList = NULL;
                HrtimerClockStop();
            } else {
                prevNode->pstNext = NULL;
            }
        }
        curNode->pstNext = NULL;
        curNode->_softexpires = time;
        curNode->set_time_reload = (UINT32)((time.tv.sec * US_PER_SECOND + time.tv.usec) * HRTIMER_PERUS);
        curNode->HandlerHead->_softexpires = time;
        HrtimerNodeAdd(curNode, NULL);
    }

    return LOS_OK;
}

STATIC VOID CancelHandlerNode(const struct hrtimer *timer, struct hrtimer_list_node *curNode)
{
    struct handler_list_node *curHandler = curNode->HandlerHead;
    struct handler_list_node *prevHandler = curHandler;

    while (curHandler != NULL) {
        if ((curHandler->pfnHandler == timer->function) &&
            (curHandler->_softexpires.tv.sec == timer->_softexpires.tv.sec) &&
            (curHandler->_softexpires.tv.usec == timer->_softexpires.tv.usec)) {
            if (curHandler == curNode->HandlerHead) {
                curNode->HandlerHead = curHandler->pstNext;
            } else {
                prevHandler->pstNext = curHandler->pstNext;
            }
            curHandler->pstNext = NULL;
            (VOID)LOS_MemFree(m_aucSysMem0, curHandler);
            break;
        }
        prevHandler = curHandler;
        curHandler = curHandler->pstNext;
    }
}

STATIC UINT32 CheckTime(union ktime *time)
{
    if ((time->tv.sec == 0) && (time->tv.usec == 0)) {
        return LOS_NOK;
    }

    if (time->tv.usec >= US_PER_SECOND) {
        time->tv.sec += time->tv.usec / US_PER_SECOND;
        time->tv.usec = time->tv.usec % US_PER_SECOND;
    }

    return LOS_OK;
}

void linux_hrtimer_init(struct hrtimer *timer, clockid_t clockID, enum hrtimer_mode mode)
{
    (VOID)clockID;
    if ((timer == NULL) || (mode != HRTIMER_MODE_REL)) {
        PRINT_ERR("The timer is NULL OR The mode is not HRTIMER_MODE_REL!\n");
    }
    return;
}

int linux_hrtimer_create(struct hrtimer *timer, union ktime time, Handler handler)
{
    UINT32 ret;

    if ((timer == NULL) || (handler == NULL)) {
        return -1;
    }

    ret = CheckTime(&time);
    if (ret != LOS_OK) {
        return -1;
    }

    timer->_softexpires.tv.sec = time.tv.sec;
    timer->_softexpires.tv.usec = time.tv.usec;
    timer->function = handler;

    return 0;
}

STATIC struct handler_list_node *HandleNodeInit(union ktime time, struct hrtimer *timer)
{
    struct handler_list_node *handler = NULL;
    handler = (struct handler_list_node *)LOS_MemAlloc(m_aucSysMem0, sizeof(struct handler_list_node));
    if (handler == NULL) {
        return NULL;
    }
    handler->_softexpires = time;
    handler->pfnHandler = timer->function;
    handler->pstNext = NULL;
    return handler;
}

int linux_hrtimer_start(struct hrtimer *timer, union ktime time, const enum hrtimer_mode mode)
{
    struct hrtimer_list_node *hrtimer = NULL;
    struct hrtimer_list_node *prevNode = NULL;
    struct hrtimer_list_node *curNode = NULL;
    struct handler_list_node *handler = NULL;
    struct handler_list_node *prevHandler = NULL;
    struct handler_list_node *curHandler = NULL;
    UINT32 intSave;

    if ((timer == NULL) || (mode != HRTIMER_MODE_REL)) {
        return -1;
    }

    if (CheckTime(&time) != LOS_OK) {
        return -1;
    }

    LOS_SpinLockSave(&g_hrtimerSpin, &intSave);
    GetHrtimerNodePosition(timer, &prevNode, &curNode);
    if (curNode == NULL) {
        LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
        if (timer->function == NULL) {
            return -1;
        }
        hrtimer = HrtimerListNodeInit(time);
        if (hrtimer == NULL) {
            return -1;
        }
        handler = HandleNodeInit(time, timer);
        if (handler == NULL) {
            (VOID)LOS_MemFree(m_aucSysMem0, hrtimer);
            return -1;
        }

        LOS_SpinLockSave(&g_hrtimerSpin, &intSave);
        HrtimerNodeAdd(hrtimer, handler);
        LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
        return 0;
    } else {
        GetHandlerNodePosition(timer, curNode, &prevHandler, &curHandler);
        if (ChangeNodePosition(prevNode, curNode, prevHandler, curHandler, time) == LOS_OK) {
            LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
            return 1;
        }
    }

    LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
    return -1;
}

int linux_hrtimer_cancel(struct hrtimer *timer)
{
    struct hrtimer_list_node *prevNode = NULL;
    struct hrtimer_list_node *curNode = NULL;
    UINT32 intSave;

    if (timer == NULL) {
        return -1;
    }

    LOS_SpinLockSave(&g_hrtimerSpin, &intSave);
    curNode = g_hrtimerList;
    if (curNode == NULL) {
        LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
        return 0;
    }

    GetHrtimerNodePosition(timer, &prevNode, &curNode);

    if (curNode == NULL) {
        LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
        return 0;
    } else if (curNode == g_hrtimerList) {
        CancelHandlerNode(timer, curNode);

        if (curNode->HandlerHead == NULL) {
            g_hrtimerList = curNode->pstNext;
            if (g_hrtimerList != NULL) {
                g_hrtimerList->set_time_reload += HrtimerClockValueGet();
                HrtimerClockStop();
                HrtimerClockStart(g_hrtimerList->set_time_reload);
            } else {
                HrtimerClockStop();
            }
            curNode->pstNext = NULL;
            (VOID)LOS_MemFree(m_aucSysMem0, curNode);
        }
    } else {
        CancelHandlerNode(timer, curNode);

        if (curNode->HandlerHead == NULL) {
            if (curNode->pstNext == NULL) {
                prevNode->pstNext = NULL;
            } else {
                prevNode->pstNext = curNode->pstNext;
                prevNode->pstNext->set_time_reload += curNode->set_time_reload;
            }
            curNode->pstNext = NULL;
            (VOID)LOS_MemFree(m_aucSysMem0, curNode);
        }
    }
    LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
    return 1;
}

u64 linux_hrtimer_forward(struct hrtimer *timer, union ktime interval)
{
    struct hrtimer_list_node *prevNode = NULL;
    struct hrtimer_list_node *curNode = NULL;
    struct handler_list_node *prevHandler = NULL;
    struct handler_list_node *curHandler = NULL;
    UINT32 intSave;
    UINT32 ret;

    if (timer == NULL) {
        return 0;
    }

    ret = CheckTime(&interval);
    if (ret != LOS_OK) {
        return 0;
    }

    LOS_SpinLockSave(&g_hrtimerSpin, &intSave);
    GetHrtimerNodePosition(timer, &prevNode, &curNode);
    if (curNode == NULL) {
        LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
        return 0;
    }
    GetHandlerNodePosition(timer, curNode, &prevHandler, &curHandler);
    timer->_softexpires = interval;
    ret = ChangeNodePosition(prevNode, curNode, prevHandler, curHandler, interval);
    LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);
    if (ret != LOS_OK) {
        return 0;
    } else {
        return (u64)((interval.tv.sec * US_PER_SECOND + interval.tv.usec) * HRTIMER_PERUS);
    }
}

int linux_hrtimer_is_queued(struct hrtimer *timer)
{
    struct hrtimer_list_node *curNode = NULL;
    struct handler_list_node *handler = NULL;
    INT32 ret = LOS_NOK;
    UINT32 intSave;

    if (timer == NULL) {
        return -1;
    }

    LOS_SpinLockSave(&g_hrtimerSpin, &intSave);
    curNode = g_hrtimerList;
    while (curNode != NULL) {
        handler = curNode->HandlerHead;
        while (handler != NULL) {
            if (handler->pfnHandler == timer->function) {
                break;
            }
            handler = handler->pstNext;
        }

        if ((handler != NULL) && (handler->pfnHandler == timer->function) &&
            (handler->_softexpires.tv.sec == timer->_softexpires.tv.sec) &&
            (handler->_softexpires.tv.usec == timer->_softexpires.tv.usec)) {
            ret = LOS_OK;
            break;
        }
        curNode = curNode->pstNext;
    }
    LOS_SpinUnlockRestore(&g_hrtimerSpin, intSave);

    return ret;
}

UINT32 HrtimersInit(VOID)
{
    UINT32 ret;

    g_hrtimerList = NULL;
    /* Initialize the timer */
    HrtimerClockInit();
    /* Create interrupt of the timer */
    ret = LOS_HwiCreate(NUM_HAL_INTERRUPT_HRTIMER, 0, 0, HrtimerListScan, 0);
    if (ret != LOS_OK) {
        return LOS_NOK;
    }
    HalIrqUnmask(NUM_HAL_INTERRUPT_HRTIMER);

    return LOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
