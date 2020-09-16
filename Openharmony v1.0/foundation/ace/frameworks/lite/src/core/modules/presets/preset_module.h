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
#ifndef OHOS_ACELITE_PRESET_MODULE_H
#define OHOS_ACELITE_PRESET_MODULE_H

#include "js_fwk_common.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class PresetModule : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(PresetModule);
    /**
     * @fn PresetModule::PresetModule()
     *
     * @brief Constructor.
     */
    PresetModule() = delete;

    /**
     * @fn PresetModule::PresetModule(const char* name)
     *
     * @brief Constructor.
     */
    PresetModule(const char * const name);

    /**
     * @fn PresetModule::~PresetModule()
     *
     * @brief Destructor.
     */
    ~PresetModule();

    /**
     * @fn PresetModule::Init
     *
     * @brief Initialize module
     */
    virtual void Init() = 0;

protected:
    /**
     * @fn PresetModule::CreateNamedFunction(char* funcName, jerry_external_handler_t handler)
     *
     * @brief create a new named function
     * @param funcName the name of new function
     * @param handler the handler of new function
     */
    void CreateNamedFunction(const char * const funcName, jerry_external_handler_t handler);

private:
    jerry_value_t module_;
    char* moduleName_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_PRESET_MODULE_H
