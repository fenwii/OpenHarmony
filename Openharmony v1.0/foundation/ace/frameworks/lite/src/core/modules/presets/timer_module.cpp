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

#include "timer_module.h"
#ifdef FEATURE_TIMER_MODULE
#if (!defined(_WIN32) && !defined(_WIN64))
#include "js_async_work.h"
#endif
#include "ace_log.h"
#include "ace_mem_base.h"
#include "js_fwk_common.h"
#include <cstdint>
#include <string.h>
#include "nativeapi_timer_task.h"

namespace OHOS {
namespace ACELite {
void TimerModule::Init()
{
    const char * const setTimeout = "setTimeout";
    const char * const clearTimeout = "clearTimeout";
    const char * const setInterval = "setInterval";
    const char * const clearInterval = "clearInterval";
    CreateNamedFunction(setTimeout, SetTimeout);
    CreateNamedFunction(clearTimeout, ClearTimer);
    CreateNamedFunction(setInterval, SetInterval);
    CreateNamedFunction(clearInterval, ClearTimer);
    InitTimerTask();
}

jerry_value_t TimerModule::CreateTimer(const jerry_value_t func,
                                       const jerry_value_t context,
                                       const jerry_value_t *args,
                                       const jerry_length_t argsNum,
                                       bool repeated)
{
    const uint8_t leastArguments = 2;
    if ((argsNum < leastArguments) || (GetInstance()->GetTimerList() == nullptr)) {
        return UNDEFINED;
    } else {
        TimerList::Arguments *arguments = new TimerList::Arguments();
        if (arguments == nullptr) {
            return jerry_create_error(JERRY_ERROR_EVAL, reinterpret_cast<const jerry_char_t *>("memory error"));
        }
        arguments->context = context;
        jerry_value_t function = args[0];
        arguments->func = jerry_acquire_value(function);
        arguments->repeated = repeated;
        TimerList* timerList = GetInstance()->GetTimerList();
        if (argsNum > leastArguments) {
            uint8_t funcNumber = argsNum - leastArguments;
            jerry_value_t *funcArg =
                static_cast<jerry_value_t *>(ace_malloc(sizeof(jerry_value_t) * (funcNumber)));
            if (funcArg == nullptr) {
                timerList->ReleaseArguments(arguments);
                return jerry_create_error(JERRY_ERROR_EVAL, reinterpret_cast<const jerry_char_t *>("memory error"));
            }
            for (uint8_t i = 0; i < funcNumber; i++) {
                funcArg[i] = jerry_acquire_value(args[i + leastArguments]);
            }
            arguments->args = funcArg;
            arguments->argsNum = funcNumber;
        }
        jerry_value_t retVal = StartTask(arguments, args[1], repeated);
        if (jerry_value_is_undefined(retVal)) {
            timerList->ReleaseArguments(arguments);
        }
        return retVal;
    }
}

jerry_value_t TimerModule::StartTask(TimerList::Arguments *arguments, jerry_value_t time, bool repeated)
{
    timerHandle_t timerId = nullptr;
    TimerList *timerList = GetInstance()->GetTimerList();
    jerry_value_t retVal = UNDEFINED;
    if (timerList == nullptr) {
        return retVal;
    }
    if (!jerry_value_is_number(time)) {
        retVal = timerList->AddTimer(timerId, arguments);
        if (jerry_value_is_undefined(retVal)) {
            return retVal;
        }
        Task(arguments);
    } else {
        jerry_value_t numProp = jerry_value_to_number(time);
        int64_t num = jerry_get_number_value(numProp);
        jerry_release_value(numProp);
        if (num <= 0 || num >= UINT32_MAX) {
            retVal = timerList->AddTimer(timerId, arguments);
            if (jerry_value_is_undefined(retVal)) {
                return retVal;
            }
            Task(arguments);
        } else {
            int result = StartTimerTask(repeated, (uint32_t)num, reinterpret_cast<void *>(Task), arguments, &timerId);
            if (result < 0) {
                return UNDEFINED;
            }
            retVal = timerList->AddTimer(timerId, arguments);
        }
    }
    return retVal;
}

jerry_value_t TimerModule::ClearTimer(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t *args,
                                      const jerry_length_t argsNum)
{
    if (argsNum == 0) {
        return UNDEFINED;
    }
    TimerList* timerList = GetInstance()->GetTimerList();
    if ((timerList != nullptr) && (jerry_value_is_number(args[0]))) {
        int16_t timerKey = IntegerOf(args[0]);
        if (timerKey < 0) {
            return UNDEFINED;
        }
        uint8_t index = (uint8_t)(timerKey);
        TimerList::TimerNode* timer = timerList->GetTimer(index);
        if (timer != nullptr) {
            int result = StopTimerTask(timer->timerId);
            if (result >= 0) {
                timerList->DeleteTimer(index);
            }
        }
    }
    return UNDEFINED;
}

void TimerModule::Task(void *arguments)
{
    TimerList::Arguments *arg = static_cast<TimerList::Arguments *>(arguments);
    if (arg == nullptr) {
        return;
    }
    TimerList *timerList = GetInstance()->GetTimerList();
    if (timerList == nullptr) {
        return;
    }
#if (!defined _WIN32) && (!defined _WIN64)
    uint8_t* index = static_cast<uint8_t*>(ace_malloc(sizeof(uint8_t)));
    bool check = true;
    if (index == nullptr) {
        check = false;
        HILOG_ERROR(HILOG_MODULE_ACE, "copy timer id failed\n");
    } else {
        *index = arg->index;
        if (!JsAsyncWork::DispatchAsyncWork(TimerModule::Execute, index)) {
            ACE_FREE(index);
            check = false;
        }
    }
    if (!check && (!arg->repeated)) {
#if defined(__LITEOS__)
        TimerList::TimerNode* timer = timerList->GetTimer(arg->index);
        if (timer != nullptr) {
            StopTimerTask(timer->timerId);
        }
#endif
        timerList->DeleteTimer(arg->index);
    }
#else
    if (jerry_value_is_function(arg->func)) {
        CallJSFunctionAutoRelease(arg->func, arg->context, arg->args, arg->argsNum);
    }
    if (!arg->repeated) {
        timerList->DeleteTimer(arg->index);
    }
#endif
}

#if (!defined(_WIN32) && !defined(_WIN64))
void TimerModule::Execute(void *data)
{
    uint8_t* timerId = static_cast<uint8_t*>(data);
    if (timerId == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "timer index is invalid");
        return;
    }
    TimerList* timerList = GetInstance()->GetTimerList();
    if (timerList != nullptr) {
        TimerList::TimerNode* timer = timerList->GetTimer(*timerId);
        if (timer != nullptr) {
            TimerList::Arguments* funcArgs = timer->arguments;
            if (jerry_value_is_function(funcArgs->func)) {
                CallJSFunctionAutoRelease(funcArgs->func, funcArgs->context, funcArgs->args, funcArgs->argsNum);
            }
            // if timer is once, release the arguments
            if (!funcArgs->repeated) {
#if defined(__LITEOS__)
                StopTimerTask(timer->timerId);
#endif
                timerList->DeleteTimer(funcArgs->index);
            }
        }
    }
    ACE_FREE(timerId);
}
#endif
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_TIMER_MODULE
