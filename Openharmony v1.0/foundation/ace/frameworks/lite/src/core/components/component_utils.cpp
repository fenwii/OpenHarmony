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

#include "component_utils.h"
#include "ace_log.h"
#include "component.h"

namespace OHOS {
namespace ACELite {
UIView* ComponentUtils::GetViewFromBindingObject(jerry_value_t value)
{
    Component* component = GetComponentFromBindingObject(value);
    return component ? component->GetComponentRootView() : nullptr;
}

Component* ComponentUtils::GetComponentFromBindingObject(jerry_value_t value)
{
    if (IS_UNDEFINED(value)) {
        return nullptr;
    }

    Component* component = nullptr;
    bool isBinded = jerry_get_object_native_pointer(value, reinterpret_cast<void**>(&component), nullptr);
    if (!isBinded || (component == nullptr)) {
        return nullptr;
    }
    return component;
}
} // namespace ACELite
} // namespace OHOS
