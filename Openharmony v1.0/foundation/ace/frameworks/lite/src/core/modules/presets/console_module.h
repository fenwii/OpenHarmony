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
#ifndef OHOS_ACELITE_CONSOLE_MODULE_H
#define OHOS_ACELITE_CONSOLE_MODULE_H

#include "non_copyable.h"
#include "presets/preset_module.h"

namespace OHOS {
namespace ACELite {
static constexpr char console[] = "console";
class ConsoleModule final : public PresetModule {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ConsoleModule);
    /**
     * @fn ConsoleModule::ConsoleModule()
     *
     * @brief Constructor.
     */
    ConsoleModule() : PresetModule(console) {}

    /**
     * @fn ConsoleModule::~ConsoleModule()
     *
     * @brief Constructor.
     */
    ~ConsoleModule() = default;

    void Init() override;

    static void Load()
    {
        ConsoleModule consoleModule;
        consoleModule.Init();
    }

private:
    /**
     * @fn ConsoleModule::LogDebug()
     *
     * @brief Outputs a message to the console with the log level "debug".
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param length the length of arguments list
     */
    static jerry_value_t LogDebug(const jerry_value_t func,
                                  const jerry_value_t context,
                                  const jerry_value_t* args,
                                  const jerry_length_t length);

    /**
     * @fn ConsoleModule::LogInfo()
     *
     * @brief Outputs a message to the console with the log level "info".
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param length the length of arguments list
     */
    static jerry_value_t LogInfo(const jerry_value_t func,
                                 const jerry_value_t context,
                                 const jerry_value_t* args,
                                 const jerry_length_t length);

    /**
     * @fn ConsoleModule::LogWarn()
     *
     * @brief Outputs a message to the console with the log level "warn".
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param length the length of arguments list
     */
    static jerry_value_t LogWarn(const jerry_value_t func,
                                 const jerry_value_t context,
                                 const jerry_value_t* args,
                                 const jerry_length_t length);

    /**
     * @fn ConsoleModule::Log()
     *
     * @brief Outputs a message to the console with the log level "log".
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param length the length of arguments list
     */
    static jerry_value_t Log(const jerry_value_t func,
                             const jerry_value_t context,
                             const jerry_value_t* args,
                             const jerry_length_t length);

    /**
     * @fn ConsoleModule::LogError()
     *
     * @brief Outputs a message to the console with the log level "error".
     * @param func function object
     * @param context the context of function execution
     * @param args the list of arguments
     * @param length the length of arguments list
     */
    static jerry_value_t LogError(const jerry_value_t func,
                                  const jerry_value_t context,
                                  const jerry_value_t* args,
                                  const jerry_length_t length);
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_CONSOLE_MODULE_H
