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
#ifndef OHOS_ACELITE_TIMER_MODULE_H
#define OHOS_ACELITE_TIMER_MODULE_H

#include "acelite_config.h"
#include "non_copyable.h"
#ifdef FEATURE_TIMER_MODULE
#include "ace_log.h"
#include "js_timer_list.h"
#include "presets/preset_module.h"

namespace OHOS {
namespace ACELite {
class TimerModule final : PresetModule {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TimerModule);
    static TimerModule *GetInstance()
    {
        static TimerModule instance;
        return &instance;
    }

    void Init() override;

    void Clear()
    {
        if (timerList_ != nullptr) {
            timerList_->ClearTimerList();
            delete (timerList_);
            timerList_ = nullptr;
        }
    }

private:
    /**
     * @fn TimerModule::TimerModule()
     * @brief Constructor
     */
    TimerModule() : PresetModule(nullptr),
        timerList_(nullptr)
    {
    }

    /**
     * @fn TimerModule::~TimerModule()
     *
     */
    ~TimerModule() = default;

    TimerList *GetTimerList()
    {
        if (timerList_ == nullptr) {
            timerList_ = new TimerList();
            if (timerList_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "malloc timer heap memory failed.");
            }
        }
        return timerList_;
    }

    /**
     * @brief set the scheduled tasks, execute only once.
     * @return the id of timer
     */
    static jerry_value_t SetTimeout(const jerry_value_t func,
                                    const jerry_value_t context,
                                    const jerry_value_t *args,
                                    const jerry_length_t argsNum)
    {
        return CreateTimer(func, context, args, argsNum, false);
    }

    /**
     * @brief start timer task
     */
    static jerry_value_t StartTask(TimerList::Arguments *argument, jerry_value_t time, bool repeated);

    /**
     * @brief set the repeated timer
     * @return the timer id
     */
    static jerry_value_t SetInterval(const jerry_value_t func,
                                     const jerry_value_t context,
                                     const jerry_value_t *args,
                                     const jerry_length_t argsNum)
    {
        return CreateTimer(func, context, args, argsNum, true);
    }

    /**
     * @brief set the repeated timer
     * @return the timer id
     */
    static jerry_value_t CreateTimer(const jerry_value_t func,
                                     const jerry_value_t context,
                                     const jerry_value_t *args,
                                     const jerry_length_t argsNum,
                                     bool repeated);

    /**
     * @brief set the timer task
     * @return the value of task executed
     */
    static void Task(void *arguments);

    /**
     * @brief cancel the timer which is not execute
     * @return the result of cancel timer
     */
    static jerry_value_t ClearTimer(const jerry_value_t func,
                                    const jerry_value_t context,
                                    const jerry_value_t *args,
                                    const jerry_length_t argsNum);

#if (!defined(_WIN32) && !defined(_WIN64))
    static void Execute(void *data);
#endif
    TimerList *timerList_;
};
} // namespace ACELite
} // namespace OHOS
#endif
namespace OHOS {
namespace ACELite {
class TimersModule final {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TimersModule);
    TimersModule() = default;
    ~TimersModule() = default;
    static void Load()
    {
#ifdef FEATURE_TIMER_MODULE
        TimerModule *timerModule = const_cast<TimerModule *>(TimerModule::GetInstance());
        timerModule->Init();
#endif
    }
    static void Clear()
    {
#ifdef FEATURE_TIMER_MODULE
        TimerModule *timerModule = const_cast<TimerModule *>(TimerModule::GetInstance());
        timerModule->Clear();
#endif
    }
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_TIMER_MODULE_H
