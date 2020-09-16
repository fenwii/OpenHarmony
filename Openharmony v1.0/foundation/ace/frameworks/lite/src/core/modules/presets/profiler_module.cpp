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
#include "profiler_module.h"
#if ENABLED(JS_PROFILER)
namespace OHOS {
namespace ACELite {
/**
 * Useage:
 *     profiler.startTracing(5);
 *     xxxx
 *     profiler.stopTracing();
 *  the parameter of profiler.startTracing must be one of PerformanceTag in js_profile.h
 */
void ProfilerModule::Init()
{
    const char * const startTracingFunc = "startTracing";
    const char * const stopTracingFunc = "stopTracing";
    CreateNamedFunction(startTracingFunc, StartTracing);
    CreateNamedFunction(stopTracingFunc, StopTracing);
}

jerry_value_t ProfilerModule::StartTracing(const jerry_value_t func,
                                           const jerry_value_t context,
                                           const jerry_value_t* args,
                                           const jerry_length_t argsNum)
{
#if ENABLED(JS_PROFILER)
    if ((args == nullptr) || (argsNum < 1)) {
        return UNDEFINED;
    }

    uint8_t tag = (uint8_t)jerry_get_number_value(args[0]);
    uint8_t component = 0;
    uint16_t description = 0;
    const uint8_t leastArgsNum = 2;
    if (argsNum >= leastArgsNum) {
        component = (uint8_t)jerry_get_number_value(args[1]);
    }
    const uint8_t jsArgsNum = 3;
    if (argsNum == jsArgsNum) {
        const uint8_t descriptionIndex = 2;
        description = (uint16_t)jerry_get_number_value(args[descriptionIndex]);
    }

    START_TRACING_WITH_EXTRA_INFO((PerformanceTag)tag, component, description);
#endif // ENABLED(JS_PROFILER)
    return UNDEFINED;
}

jerry_value_t ProfilerModule::StopTracing(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t* args,
                                          const jerry_length_t argsNum)
{
#if ENABLED(JS_PROFILER)
    STOP_TRACING();
#endif
    return UNDEFINED;
}
} // namespace ACELite
} // namespace OHOS
#endif