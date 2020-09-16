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

#include "ability_event_handler.h"

namespace OHOS {
namespace {
    thread_local AbilityEventHandler* g_currentHandler;
}

AbilityEventHandler::AbilityEventHandler()
{
    g_currentHandler = this;
    (void) pthread_mutex_init(&queueMutex_, nullptr);
    (void) pthread_cond_init(&pthreadCond_, nullptr);
}

AbilityEventHandler::~AbilityEventHandler()
{
    (void) pthread_mutex_destroy(&queueMutex_);
    (void) pthread_cond_destroy(&pthreadCond_);

    g_currentHandler = nullptr;
}

void AbilityEventHandler::Run()
{
    while (!quit_) {
        (void) pthread_mutex_lock(&queueMutex_);
        if (taskQueue_.empty()) {
            (void) pthread_cond_wait(&pthreadCond_, &queueMutex_);
        }
        Task task = std::move(taskQueue_.front());
        taskQueue_.pop();
        (void) pthread_mutex_unlock(&queueMutex_);
        task();
    }
}

void AbilityEventHandler::PostTask(const Task& task)
{
    (void) pthread_mutex_lock(&queueMutex_);
    taskQueue_.push(task);
    (void) pthread_mutex_unlock(&queueMutex_);

    (void) pthread_cond_signal(&pthreadCond_);
}

void AbilityEventHandler::PostQuit()
{
    Task task = [this]() {
        quit_ = true;
    };
    PostTask(task);
}

AbilityEventHandler* AbilityEventHandler::GetCurrentHandler()
{
    return g_currentHandler;
}
}  // namespace OHOS