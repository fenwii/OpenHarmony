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

#ifndef OHOS_MUTEX_LOCK_H
#define OHOS_MUTEX_LOCK_H

#include <pthread.h>

namespace OHOS {
template<typename T>
struct Lock {
public:
    explicit Lock(T &mutex) : mutex_(&mutex)
    {
        if (mutex_ != nullptr) {
            mutex_->Lock();
        }
    }

    ~Lock()
    {
        if (mutex_ != nullptr) {
            mutex_->UnLock();
        }
    }
private:
    T *mutex_;
};

struct Mutex {
public:
    Mutex()
    {
        pthread_mutex_init(&mutex_, nullptr);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&mutex_);
    }

    void Lock()
    {
        pthread_mutex_lock(&mutex_);
    }

    void UnLock()
    {
        pthread_mutex_unlock(&mutex_);
    }
private:
    pthread_mutex_t mutex_;
};
} // OHOS
#endif // OHOS_MUTEX_LOCK_H
