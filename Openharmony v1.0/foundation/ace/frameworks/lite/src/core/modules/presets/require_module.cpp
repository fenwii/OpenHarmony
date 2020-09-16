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
#include "presets/require_module.h"
#include "ace_mem_base.h"
#include "module_manager.h"

namespace OHOS {
namespace ACELite {
void RequireModule::Init()
{
    const char * const funcNameRequire = "requireNative";
    CreateNamedFunction(funcNameRequire, ImportModule);
}

jerry_value_t RequireModule::ImportModule(const jerry_value_t func,
                                          const jerry_value_t obj,
                                          const jerry_value_t* args,
                                          const jerry_length_t argsNum)
{
    const uint8_t requireArgc = 1;
    if (argsNum != requireArgc) {
        return UNDEFINED;
    }
    char* name = MallocStringOf(args[0]);
    if (name == nullptr) {
        return UNDEFINED;
    }

    ModuleManager* moduleManager = ModuleManager::GetInstance();
    jerry_value_t moduleObj = (jerry_value_t)(uintptr_t)(moduleManager->RequireModule(name));
    ace_free(name);
    name = nullptr;
    return moduleObj;
}
} // namespace ACELite
} // namespace OHOS
