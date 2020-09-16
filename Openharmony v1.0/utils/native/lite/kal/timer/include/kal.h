/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef KAL_H_
#define KAL_H_
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*KalTimerProc)(union sigval);
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

KalTimerId KalTimerCreate(KalTimerProc func, KalTimerType type, void *arg, unsigned int millisec);
KalErrCode KalTimerStart(KalTimerId timerId);
KalErrCode KalTimerChange(KalTimerId timerId, unsigned int millisec);
KalErrCode KalTimerStop(KalTimerId timerId);
KalErrCode KalTimerDelete(KalTimerId timerId);
unsigned int KalTimerIsRunning(KalTimerId timerId);

#ifdef __cplusplus
}
#endif

#endif // KAL_H_
