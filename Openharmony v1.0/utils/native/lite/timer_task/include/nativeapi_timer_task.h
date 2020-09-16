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

#ifndef JS_NATIVEAPI_TIMER_TASK_H
#define JS_NATIVEAPI_TIMER_TASK_H

#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef void *timerHandle_t;

int InitTimerTask();
int StartTimerTask(bool isPeriodic, const unsigned int delay, void* userCallback,
                   void* userContext, timerHandle_t *timerHandle);
int StopTimerTask(const timerHandle_t timerHandle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif /* JS_NATIVEAPI_TIMER_TASK_H */
