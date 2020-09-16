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

#include "presets/preset_module.h"
#include <string.h>
#include "ace_log.h"

namespace OHOS {
namespace ACELite {
PresetModule::PresetModule(const char * const name)
{
    jerry_value_t globalObject = jerry_get_global_object();
    moduleName_ = const_cast<char *>(name);
    if (moduleName_ != nullptr) {
        module_ = jerry_create_object();
        JerrySetNamedProperty(globalObject, moduleName_, module_);
        jerry_release_value(globalObject);
    } else {
        module_ = globalObject;
    }
}

PresetModule::~PresetModule()
{
    jerry_release_value(module_);
}

void PresetModule::CreateNamedFunction(const char * const funcName, jerry_external_handler_t handler)
{
    if (funcName == nullptr) {
        return;
    }
    JerrySetFuncProperty(module_, funcName, handler);
}
} // namespace ACELite
} // namespace OHOS
