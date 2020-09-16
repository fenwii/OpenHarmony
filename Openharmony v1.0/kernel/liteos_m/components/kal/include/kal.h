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

 /**
 * @addtogroup KAL
 * @{
 * 
 * @brief Defines the kernel adaptation layer (KAL), which provides compatible interfaces across L0 and L1 systems.
 * 
 *
 * @since 1.0
 * @version 1.0
 */
 
#ifndef KAL_H_
#define KAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Indicates the maximum length of a thread name.
*
* @since 1.0
* @version 1.0
*/
#define KAL_TASK_NAME_LEN 32

typedef void (*KalTimerProc)(void *arg);
typedef void *KalTimerId;

typedef enum {
    KAL_TIMER_ONCE = 0,    // /< One-shot timer.
    KAL_TIMER_PERIODIC = 1 // /< Repeating timer.
} KalTimerType;

typedef enum {
    KAL_OK = 0,
    KAL_ERR_PARA = 1,
    KAL_ERR_INNER = 2,
    KAL_ERR_TIMER_STATE = 0x100,
} KalErrCode;

/**
* @brief Describes a thread.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
/** Thread name */
char name[KAL_TASK_NAME_LEN];
/** Thread ID */
unsigned int id;
/** Thread status */
unsigned short status;
/** Thread priority */
unsigned short priority;
/** Thread semaphore */
void *taskSem;
/** Thread mutex */
void *taskMutex;
/** Thread event */
unsigned int eventStru[3];
/** Thread event mask */
unsigned int eventMask;
/** Thread stack size */
unsigned int stackSize;
/** Thread stack top */
unsigned int topOfStack;
/** Thread stack bottom */
unsigned int bottomOfStack;
/** Thread current mstatus */
unsigned int mstatus;
/** Thread current mepc */
unsigned int mepc;
/** Thread current tp */
unsigned int tp;
/** Thread current ra */
unsigned int ra;
/** Thread stack pointer */
unsigned int sp;
/** Current stack space usage */
unsigned int currUsed;
/** Peak stack space usage */
unsigned int peakUsed;
/** Thread stack overflow flag */
unsigned int overflowFlag;
} ThreadInfo;

typedef struct {
    /**< Total space of the memory pool. */
    unsigned int total;
    /**< Used space of the memory pool. */
    unsigned int used;
    /**< Free space of the memory pool. */
    unsigned int free;
    /**< Number of free nodes in the memory pool. */
    unsigned int freeNodeNum;
    /**< Number of used nodes in the memory pool. */
    unsigned int usedNodeNum;
    /**< Maximum size of the node in the free space of the memory pool. */
    unsigned int maxFreeNodeSize;
    /**< Number of memory application failures. */
    unsigned int mallocFailCount;
    /**< Peak memory usage of the memory pool. */
    unsigned int peekSize;
    /**< Total space of the little memory pool. */
    unsigned int totalLmp;
    /**< Used space of the little memory pool. */
    unsigned int usedLmp;
    /**< Free space of the little memory pool. */
    unsigned int freeLmp;
} MemInfo;

/**
* @brief Obtains thread information.
*
* @param threadId Indicates the thread ID.
* @param info Indicates the pointer to the buffer for storing the obtained thread information.
* @return Returns <b>0</b> if the thread information is obtained; returns a negative value otherwise.
* @since 1.0
* @version 1.0
*/
unsigned int KalThreadGetInfo(unsigned int threadId, ThreadInfo *info);

/**
* @brief Delays a thread.
*
* The delay unit is microsecond. The actual delay precision can reach only the tick level.
*
* @param us Indicates the number of microseconds to delay. The actual delay precision is one tick.
* @since 1.0
* @version 1.0
*/
void KalDelayUs(unsigned int us);
KalTimerId KalTimerCreate(KalTimerProc func, KalTimerType type, void *arg, unsigned int ticks);
KalErrCode KalTimerStart(KalTimerId timerId);
KalErrCode KalTimerChange(KalTimerId timerId, unsigned int ticks);
KalErrCode KalTimerStop(KalTimerId timerId);
KalErrCode KalTimerDelete(KalTimerId timerId);
unsigned int KalTimerIsRunning(KalTimerId timerId);
unsigned int KalTickToMs(unsigned int ticks);
unsigned int KalMsToTick(unsigned int millisec);
KalErrCode KalGetMemInfo(MemInfo *pmemInfo);

#ifdef __cplusplus
}
#endif

#endif // KAL_H_

/* * @} */