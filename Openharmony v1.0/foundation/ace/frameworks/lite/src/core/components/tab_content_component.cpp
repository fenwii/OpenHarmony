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

#ifdef FEATURE_COMPONENT_TABS

#include "js_fwk_common.h"
#include "keys.h"
#include "tab_content_component.h"
#include "ui_view_group.h"

namespace OHOS {
namespace ACELite {
TabContentComponent::TabContentComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager)
    : Component(options, children, styleManager),
      children_(children)
{
    SetComponentName(K_TAB_CONTENT);
}

uint8_t TabContentComponent::GetChildrenLength()
{
    return jerry_get_array_length(children_);
}

Component* TabContentComponent::GetComponentByIndex(uint8_t index)
{
    jerry_value_t childHandler = jerry_get_property_by_index(children_, index);
    if (jerry_value_is_undefined(childHandler)) {
        return nullptr;
    }
    Component* component = ComponentUtils::GetComponentFromBindingObject(childHandler);
    jerry_release_value(childHandler);
    return component;
}
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_TABS
