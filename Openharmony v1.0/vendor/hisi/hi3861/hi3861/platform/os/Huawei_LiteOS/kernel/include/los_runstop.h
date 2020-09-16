/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description : LiteOS interrupt module implemention.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
 * ---------------------------------------------------------------------------- */

#ifndef _LOS_RUNSTOP_H
#define _LOS_RUNSTOP_H

#include "los_config.h"

#define WAKEUP_BIT_GPIO 0x0001
#define WAKEUP_BIT_RTC  0x0002
#define WAKEUP_BIT_SDIO 0x0004
#define WAKEUP_BIT_STA0 0x0010
#define WAKEUP_BIT_STA1 0x0020
#define WAKEUP_BIT_AP0  0x0040
#define WAKEUP_BIT_ALL  0x0077

typedef VOID (*RunstopFn)(VOID);
extern RunstopFn g_runStopHook;
typedef UINT32 (*GetSuspendState)(VOID);
typedef UINT32 (*RunStopDisableWDG)(VOID);
typedef UINT32 (*RunStopResumeWDG)(VOID);
typedef UINT32 (*RunStopSavePeripheral)(VOID);
typedef UINT32 (*RunStopResumePeripheral)(VOID);
typedef UINT32 (*RunStopHwSaveHandler)(VOID);
typedef UINT32 (*RunStopHwResumeHandler)(VOID);
typedef UINT32 (*RunStopSwSaveHandler)(VOID);
typedef UINT32 (*RunStopSwResumeHandler)(VOID);

typedef VOID (*RunStopSleep)(VOID);

typedef struct RunStopHandler {
    GetSuspendState getState;   // get if func can sleep
    struct RunStopHandler *next;
} RunStopHandler;

/* if debug information is used, debug macros need to be defined here */
#ifdef DEBUG_RUNSTOP_PHASE
typedef struct ThresholdDebugInfo {
    UINT32 timerTick;
    UINT32 taskTick;
    UINT32 taskID;
} ThresholdInfo;
#endif

typedef struct RunStopInfo {
    UINT32 tickThreshold;
    UINT32 thresholdFailCnt;
    UINT32 voteFailCnt;
    UINT32 sleepCnt;
    UINT32 timerTick;
    UINT32 timerPfnHandler;
    UINT32 timerArg;
    UINT32 taskTick;
    UINT32 taskID;
    UINT32 sleepTicks;
    UINT32 refuseVoteHandle;
    UINT8 voteState;
#ifdef DEBUG_RUNSTOP_PHASE
    UINT64 wakeupTick;
    UINT64 exitIdleTick;
#endif
} RunStopInfo;

VOID LOS_RunStopRegisterDisWDG(RunStopDisableWDG disableWDG);
VOID LOS_RunStopRegisterResWDG(RunStopDisableWDG resumeWDG);
VOID LOS_RunStopRegisterSavePeripheral(RunStopSavePeripheral savePeripheral);
VOID LOS_RunStopRegisterResumePeripheral(RunStopResumePeripheral resumePeripheral);
RunStopHandler* LOS_RunStopRegisterVote (GetSuspendState getState);
UINT32 LOS_RunStopUnregisterHandler(RunStopHandler *handler);
VOID LOS_RunStopRegisterDeepSleepFunc(RunStopSleep deepSleepFunc);
VOID LOS_RunStopRegisterLightSleepFunc(RunStopSleep deepSleepFunc);
VOID LOS_RunStopSleep(VOID);
VOID LOS_RunStopRegisterHwHandler(RunStopHwSaveHandler saveHandler,
    RunStopHwResumeHandler resumeHandler);
VOID LOS_RunStopRegisterSwHandler(RunStopSwSaveHandler saveHandler,
    RunStopSwResumeHandler resumeHandler);
VOID LOS_RunStopSetDeepSleepMaxTime(UINT32 timeMs);
RunStopInfo *LOS_RunStopInfo(VOID);
UINT8 *getRunStopSleepMode(VOID);
VOID setRunStopSleepMode(UINT8 sleepMode);

/**
 * @ingroup los_runstop
 * @brief Register the runstop callback.
 *
 * @par Description:
 * This API is used to register the runstop callback.
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 *
 * @param None
 * @retval #los_runstop_fn       The runstop callback.
 * @par Dependency:
 * <ul><li>los_runstop.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern VOID LOS_RunStopCallBackRegister(RunstopFn cb);

#endif
