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

#ifndef __LOS_SR_H__
#define __LOS_SR_H__

#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define SENSORHUB_COLDBOOT  0x1
#define SENSORHUB_SLEEP     0x2


#define OS_WAKEUP_INFO_COUNT 32
typedef struct tagWakeupInfo
{
    UINT64 uwSleepTimeTotal;
    UINT8 ucIdx;
    UINT8 ucIsFull;
    UINT8  auwPID[OS_WAKEUP_INFO_COUNT];
}OS_WAKEUP_INFO;


extern unsigned int  g_uwSrStateFlag;
extern unsigned int  g_uwOneshotLoadValue;

extern unsigned int  osDelayTskSuspend();
extern void  osDelayTskResume(unsigned int sleep_time);

extern unsigned int osSwTmrGetNextTimeout(void);
extern void osSwTmrAdjust(unsigned int sleep_time);

extern void osTickLock(void);
extern void osTickUnlock(void);
extern int osSRSuspend(void);
extern void osSRResume(void);

extern unsigned int getSleepTime();
extern void DisableWakeUpTimer(void);
extern void enterSleepMode(unsigned int SleepTime);
extern void enterStopMode(unsigned int SleepTime);
extern void StopMode_Measure(unsigned int sleepTime, unsigned int WakeUpClock);

extern void LOS_SrIdleTaskProcess(void);

extern void LOS_SystemWakeup(UINT32 uwHwiIndex);
extern void  osSRSaveRegister();
extern void osSRRestoreRegister();

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif
