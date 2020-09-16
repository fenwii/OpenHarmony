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

#include "common/task_manager.h"
#include <cassert>
#include "hal_tick.h"

namespace OHOS {
void TaskManager::Add(Task* task)
{
    if (task == nullptr) {
        return;
    }

    list_.PushBack(task);
}

void TaskManager::Remove(Task* task)
{
    if (task == nullptr) {
        return;
    }
    ListNode<Task*>* pos = list_.Begin();
    while (pos != list_.End()) {
        if (pos->data_ == task) {
            list_.Remove(pos);
            return;
        }
        pos = pos->next_;
    }
}

void TaskManager::TaskHandler()
{
    if (canTaskRun_ == false) {
        return;
    }

    if (isHandlerRunning_) {
        return;
    }
    isHandlerRunning_ = true;

    ListNode<Task*>* node = list_.Begin();

    while (node != list_.End()) {
        Task* currentTask = node->data_;
        currentTask->TaskExecute();

        node = node->next_;
    }

    isHandlerRunning_ = false;
}
}
