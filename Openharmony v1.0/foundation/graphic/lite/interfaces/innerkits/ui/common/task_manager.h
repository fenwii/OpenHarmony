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

#ifndef GRAPHIC_LITE_TASK_MANAGER_H
#define GRAPHIC_LITE_TASK_MANAGER_H

#include <cstdint>

#include "list.h"
#include "common/task.h"

namespace OHOS {
class TaskManager : public HeapBase {
public:
    /**
     * @brief return TaskManager's singleton
     * @return TaskManager*
     */
    static TaskManager* GetInstance()
    {
        static TaskManager taskManager;
        return &taskManager;
    }

    /**
     * @brief add task to task manager
     * @param [in] task task pointer
     */
    void Add(Task* task);

    /**
     * @brief del task from task manager
     * @param [in] task task pointer
     */
    void Remove(Task* task);

    /**
     * @brief set task run
     * @param [in] enable task run
     */
    void SetTaskRun(bool enable)
    {
        canTaskRun_ = enable;
    }

    /**
     * @brief get task run
     * @return enable task run
     */
    bool GetTaskRun() const
    {
        return canTaskRun_;
    }

    /**
     * @brief run all task
     */
    void TaskHandler();

    /**
     * @brief reset the mutex of task handler, must be used carefully
     */
    void ResetTaskHandlerMutex();

protected:
    List<Task*> list_; /* the task list */
    bool canTaskRun_;
    bool isHandlerRunning_;
    uint8_t idleLast_;

private:
    TaskManager() : canTaskRun_(false), isHandlerRunning_(false), idleLast_(0) {}
    ~TaskManager() {}

    static const uint16_t IDLE_MEAS_PERIOD = 500;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TASK_MANAGER_H
