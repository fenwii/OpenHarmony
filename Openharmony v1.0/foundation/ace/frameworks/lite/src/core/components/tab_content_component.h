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

#ifndef OHOS_ACELITE_TAB_CONTENT_COMPONENT_H
#define OHOS_ACELITE_TAB_CONTENT_COMPONENT_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_TABS

#include "component.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class TabContentComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TabContentComponent);
    TabContentComponent() = delete;
    TabContentComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~TabContentComponent() {}
    inline UIView *GetComponentRootView() const override
    {
        return nullptr;
    }
    uint8_t GetChildrenLength();
    Component* GetComponentByIndex(uint8_t index);

protected:
    inline bool CreateNativeViews() override
    {
        return true;
    }
    inline void ReleaseNativeViews() override {}

private:
    jerry_value_t children_;
};
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_TABS

#endif // OHOS_ACELITE_TAB_CONTENT_COMPONENT_H
