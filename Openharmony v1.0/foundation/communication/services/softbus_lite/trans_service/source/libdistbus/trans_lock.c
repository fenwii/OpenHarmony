/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "trans_lock.h"

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include <cmsis_os.h>
#else
#include <pthread.h>
#endif
#include "data_bus_error.h"

#define BUS_WAIT_FOREVER 0xFFFFFFFF

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
static osMutexId_t g_sessionManagerLock;
#else
static pthread_mutex_t g_sessionManagerLock;
#endif
int InitTcpMgrLock(void)
{
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    if (g_sessionManagerLock != NULL) {
        return DBE_SUCCESS;
    }
    g_sessionManagerLock = osMutexNew(NULL);
#else
    pthread_mutex_init(&g_sessionManagerLock, NULL);
#endif
    return DBE_SUCCESS;
}

int GetTcpMgrLock(void)
{
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    if (g_sessionManagerLock == NULL) {
        return -DBE_INNER_ERROR;
    }
    osStatus_t ret = osMutexAcquire(g_sessionManagerLock, BUS_WAIT_FOREVER);
    if (ret != osOK) {
        return -DBE_INNER_ERROR;
    }
#else
    pthread_mutex_lock(&g_sessionManagerLock);
#endif
    return DBE_SUCCESS;
}

int ReleaseTcpMgrLock(void)
{
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    if (g_sessionManagerLock == NULL) {
        return -DBE_INNER_ERROR;
    }
    osStatus_t ret = osMutexRelease(g_sessionManagerLock);
    if (ret != osOK) {
        return -DBE_INNER_ERROR;
    }
#else
    pthread_mutex_unlock(&g_sessionManagerLock);
#endif
    return DBE_SUCCESS;
}
