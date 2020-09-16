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


#ifndef OHOS_ACELITE_JS_TIMER_LIST_H
#define OHOS_ACELITE_JS_TIMER_LIST_H

#include "acelite_config.h"

#ifdef FEATURE_TIMER_MODULE
#include <jerryscript.h>
#include <cstdint>
#include "memory_heap.h"
#include "nativeapi_timer_task.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class TimerList final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TimerList);
    /**
     * @fn TimerList::TimerList()
     * @brief Constructor
     */
    TimerList() : timerListHead_(nullptr), index_(0) {}

    /**
     * @fn TimerList::~TimerList()
     *
     */
    ~TimerList() = default;

    void ClearTimerList();

    // the struct of timer task arguments
    struct Arguments : public MemoryHeap {
        uint8_t index;
        bool repeated;
        jerry_length_t argsNum = 0;
        jerry_value_t func;
        jerry_value_t context;
        jerry_value_t *args = nullptr;
    };

    // the struct of timer
    struct TimerNode : public MemoryHeap {
        uint8_t index;
        timerHandle_t timerId;
        Arguments *arguments;
        struct TimerNode *next;
    };

    jerry_value_t AddTimer(timerHandle_t timerId, Arguments *&arguments);

    TimerNode* GetTimer(uint8_t id);

    void DeleteTimer(uint8_t timer);

    void ReleaseArguments(Arguments *&argument);

    uint8_t GetIndex()
    {
        return ++index_;
    }

private:
    void ReleaseTimer(TimerNode *&current);

    TimerNode *timerListHead_;
    uint8_t index_;
};
} // namespace ACELite
} //  namespace OHOS
#endif // FEATURE_TIMER_MODULE
#endif // OHOS_ACELITE_JS_TIMER_LIST_H
