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
#ifndef OHOS_ACELITE_PROFILER_MODULE_H
#define OHOS_ACELITE_PROFILER_MODULE_H

#include "js_profiler.h"
#include "non_copyable.h"
#if ENABLED(JS_PROFILER)
#include "presets/preset_module.h"
namespace OHOS {
namespace ACELite {
static constexpr char profiler[] = "profiler";
class ProfilerModule final : public PresetModule {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ProfilerModule);
    /**
     * @fn ProfilerModule::ProfilerModule()
     *
     * @brief Constructor.
     */
    ProfilerModule() : PresetModule(profiler) {}

    /**
     * @fn ProfilerModule::~ProfilerModule()
     *
     * @brief Constructor.
     */
    ~ProfilerModule() = default;

    void Init() override;

private:
    /**
     * @fn ProfilerModule::StartTracing()
     *
     * @brief request to start the tracing.
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param argsNum the num of arguments list
     */
    static jerry_value_t StartTracing(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t *args,
                                      const jerry_length_t argsNum);

    /**
     * @fn ProfilerModule::StopTracing()
     *
     * @brief request to start the tracing.
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param argsNum the num of arguments list
     */
    static jerry_value_t StopTracing(const jerry_value_t func,
                                     const jerry_value_t context,
                                     const jerry_value_t *args,
                                     const jerry_length_t argsNum);
};
} // namespace ACELite
} // namespace OHOS
#endif
namespace OHOS {
namespace ACELite {
class PerformaceProfilerModule final {
public:
    ACE_DISALLOW_COPY_AND_MOVE(PerformaceProfilerModule);
    PerformaceProfilerModule() = default;
    ~PerformaceProfilerModule() = default;
    static void Load()
    {
#if ENABLED(JS_PROFILER)
        ProfilerModule profilerModule;
        profilerModule.Init();
#endif
    }
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_PROFILER_MODULE_H
