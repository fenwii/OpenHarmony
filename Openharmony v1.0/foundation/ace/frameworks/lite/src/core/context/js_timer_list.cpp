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

#include "acelite_config.h"

#ifdef FEATURE_TIMER_MODULE
#include "js_timer_list.h"
#include "presets/timer_module.h"
#include "ace_mem_base.h"

namespace OHOS {
namespace ACELite {
jerry_value_t TimerList::AddTimer(timerHandle_t timerId, Arguments *&arg)
{
    TimerNode *timer = static_cast<TimerNode *>(ace_malloc(sizeof(TimerNode)));
    if (timer == nullptr) {
        return UNDEFINED;
    }
    uint8_t index = GetIndex();
    timer->index = index;
    timer->next = timerListHead_;
    timer->timerId = timerId;
    arg->index = index;
    timer->arguments = arg;
    timerListHead_ = timer;
    timer = nullptr;
    return jerry_create_number(index);
}

TimerList::TimerNode* TimerList::GetTimer(uint8_t id)
{
    TimerNode *current = timerListHead_;
    while (current != nullptr) {
        if (current->index == id) {
            break;
        }
        current = current->next;
    }
    return current;
}

void TimerList::DeleteTimer(uint8_t timer)
{
    if (timerListHead_ == nullptr) {
        return;
    }
    TimerNode *current = timerListHead_;
    TimerNode *preNode = nullptr;
    while ((timer != current->index) && (current->next != nullptr)) {
        preNode = current;
        current = current->next;
    }
    if (timer == current->index) {
        if (current == timerListHead_) {
            timerListHead_ = current->next;
        } else {
            preNode->next = current->next;
        }
        ReleaseTimer(current);
    }
}

void TimerList::ClearTimerList()
{
    while (timerListHead_ != nullptr) {
        TimerNode *current = timerListHead_;
        timerListHead_ = timerListHead_->next;
        StopTimerTask(current->timerId);
        ReleaseTimer(current);
    }
}

void TimerList::ReleaseTimer(TimerNode *&current)
{
    if (current == nullptr) {
        return;
    }
    ReleaseArguments(current->arguments);
    ace_free(current);
    current = nullptr;
}

void TimerList::ReleaseArguments(Arguments *&argument)
{
    if (argument) {
        jerry_release_value(argument->func);
        if ((argument->argsNum > 0) && (argument->args != nullptr)) {
            for (uint32_t i = 0; i < argument->argsNum; i++) {
                jerry_release_value((argument->args)[i]);
            }
        }
        ACE_FREE(argument->args);
        delete argument;
        argument = nullptr;
    }
}
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_TIMER_MODULE
