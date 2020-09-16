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

#ifndef FRAMEWORKS_APP_ADAPTER_H
#define FRAMEWORKS_APP_ADAPTER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifndef APP_PLATFORM_WATCHGT
// memory operator define
#include <stdlib.h>

#include "ohos_errno.h"
#include "ohos_types.h"

#define AdapterMalloc(a) malloc(a)
#define AdapterFree(a) \
    do { \
        if (a != nullptr) { \
            (void) free((void *)a); \
            a = nullptr; \
        } \
    } while (0)

// mutex operation define
#define MutexDelete(a) pthread_mutex_destroy(a)
#define MutexAcquire(a, b) pthread_mutex_lock(a)
#define MutexRelease(a) pthread_mutex_unlock(a)

#else // APP_PLATFORM_WATCHGT
#include "ability_package_adaptor.h"
#include "ability_package_manager.h"
// memory operator define
#define AdapterMalloc(a) UI_Malloc(a)
#define AdapterFree(a) \
    do { \
        if (a != nullptr) { \
            (void) UI_Free(a); \
            a = nullptr; \
        } \
    } while (0)

#define SvrMalloc(a) MC_SVR_MEM_ALLOC(a)
#define SvrFree(a) \
    do { \
        if (a != nullptr) { \
            (void) MC_SVR_MEM_FREE(a); \
            a = nullptr; \
        } \
    } while (0)
#define AdapterSend(a, b, c) MC_MsgSnd(a, b, c)
// mutex operation define
#define MutexDelete(a) osMutexDelete(a)
#define MutexAcquire(a, b) osMutexAcquire(a, b)
#define MutexRelease(a) osMutexRelease(a)

// hash log define
#ifndef HILOG_DEBUG
#define HILOG_DEBUG(mod, format, ...)
#endif
#ifndef HILOG_ERROR
#define HILOG_ERROR(mod, format, ...)
#endif
#ifndef HILOG_INFO
#define HILOG_INFO(mod, format, ...)
#endif
#ifndef HILOG_WARN
#define HILOG_WARN(mod, format, ...)
#endif
#ifndef HILOG_RACE
#define HILOG_RACE(mod, format, ...)
#endif

extern "C" {
void LogValZeroHashPrintfAAFWKFatal(unsigned int hash, ...);
void LogValZeroHashPrintfAAFWKError(unsigned int hash, ...);
void LogValZeroHashPrintfAAFWKWarn(unsigned int hash, ...);
void LogValZeroHashPrintfAAFWKInfo(unsigned int hash, ...);
void LogValZeroHashPrintfAAFWKDebug(unsigned int hash, ...);

void LogHashPrintfAAFWKFatal(unsigned int hash, unsigned int paraNum, ...);
void LogHashPrintfAAFWKError(unsigned int hash, unsigned int paraNum, ...);
void LogHashPrintfAAFWKWarn(unsigned int hash, unsigned int paraNum, ...);
void LogHashPrintfAAFWKInfo(unsigned int hash, unsigned int paraNum, ...);
void LogHashPrintfAAFWKDebug(unsigned int hash, unsigned int paraNum, ...);
}

#endif // APP_PLATFORM_WATCHGT
#endif // FRAMEWORKS_APP_ADAPTER_H