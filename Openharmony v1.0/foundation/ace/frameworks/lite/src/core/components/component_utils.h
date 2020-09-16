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

#ifndef OHOS_ACELITE_COMPONENT_UTILS_H
#define OHOS_ACELITE_COMPONENT_UTILS_H

#include "js_fwk_common.h"
#include "non_copyable.h"
#include "ui_view.h"

namespace OHOS {
namespace ACELite {
class Component;

class ComponentUtils final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ComponentUtils);
    ~ComponentUtils() {}
    /**
     * @brief Easy method to get the root UIView from the component binded to the given JS object.
     */
    static UIView* GetViewFromBindingObject(jerry_value_t value);
    /**
     * @brief Easy method to get the the component binded to the given JS object.
     */
    static Component* GetComponentFromBindingObject(jerry_value_t value);
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_COMPONENT_UTILS_H
