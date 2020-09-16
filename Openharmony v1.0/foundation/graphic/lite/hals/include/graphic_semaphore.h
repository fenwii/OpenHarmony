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

#ifndef GRAPHIC_LITE_SEMAPHORE_H
#define GRAPHIC_LITE_SEMAPHORE_H

#ifdef _WIN32
#include <windows.h>
#elif defined __linux__ || defined __LITEOS__
#include <semaphore.h>
#else
#include "los_sem.h"
#endif // WIN32

namespace OHOS {
/** @brief Semaphore adapter for different platform. */
class Semaphore : public HeapBase {
public:
    /** Default constructor */
    Semaphore()
    {
#ifdef _WIN32
        sem = CreateSemaphore(NULL, 1, 1, NULL);
#elif defined __linux__ || defined __LITEOS__
        sem_init(&sem, 0, 0);
#else
        LOS_SemCreate(1, &sem);
#endif // WIN32
    }

    /** Default destructor */
    ~Semaphore()
    {
#ifdef _WIN32
        CloseHandle(sem);
#elif defined __linux__ || defined __LITEOS__
        sem_destroy(&sem);
#else
        LOS_SemDelete(sem);
#endif // WIN32
    }

    /** Increases the count of the specified semaphore object by a specified amount. */
    inline void notify()
    {
#ifdef _WIN32
        ReleaseSemaphore(sem, 1, NULL);
#elif defined __linux__ || defined __LITEOS__
        sem_post(&sem);
#else
        LOS_SemPost(sem);
#endif // WIN32
    }

    /** Waits until the specified object is in the signaled state. */
    inline void wait()
    {
#ifdef _WIN32
        WaitForSingleObject(sem, INFINITE);
#elif defined __linux__ || defined __LITEOS__
        sem_wait(&sem);
#else
        LOS_SemPend(sem, LOS_WAIT_FOREVER);
#endif // WIN32
    }

private:
#ifdef _WIN32
    HANDLE sem;
#elif defined __linux__ || defined __LITEOS__
    sem_t sem;
#else
    uint32_t sem;
#endif // WIN32
};
} // namespace OHOS
#endif // GRAPHIC_LITE_SEMAPHORE_H