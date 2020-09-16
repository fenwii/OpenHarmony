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

#ifndef FSM_COMMON_H
#define FSM_COMMON_H

#include <cstdarg>
#include <pthread.h>
#include <stdint.h>
#include "media_log.h"
#include "player_define.h"

const char * const MOD_NAME_FSM = "FSM";

#define FSM_RETURN_IF_NULL(condition)                                                              \
    do {                                                                                        \
        if ((condition) == nullptr) {                                                              \
            MEDIA_ERR_LOG("" #condition " is NULL error");                   \
            return HI_FAILURE;                                                                  \
        }                                                                                       \
    } while (0)

#define FSM_RETURN_IF_HANDLE_NOT_EXIST(checkFunc, handle)                  \
    do {                                                           \
        if (!checkFunc((handle))) {                                  \
            MEDIA_ERR_LOG("invalid FSM handle not exist \n"); \
            return HI_FAILURE;                                     \
        }                                                          \
    } while (0)

#define FSM_LOCK(mutex)                   \
    do {                                  \
        (void)pthread_mutex_lock(&(mutex)); \
    } while (0)

#define FSM_UNLOCK(mutex)                   \
    do {                                    \
        (void)pthread_mutex_unlock(&(mutex)); \
    } while (0)

#define FSM_COND_WAIT(cond, mutex)              \
    do {                                        \
        (void)pthread_cond_wait(&(cond), &(mutex)); \
    } while (0)

#define FSM_COND_SIGNAL(cond)             \
    do {                                  \
        (void)pthread_cond_signal(&(cond)); \
    } while (0)

uint64_t FsmGetCurTimeUs();

void FsmCondInitRelative(pthread_cond_t &cond);

int32_t FsmCondTimewait(pthread_cond_t &cond, pthread_mutex_t &mutex, uint32_t delayUs);

#endif /* FSM_COMMON_H */
