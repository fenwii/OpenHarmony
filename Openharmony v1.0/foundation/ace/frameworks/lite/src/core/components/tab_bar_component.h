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

#ifndef OHOS_ACELITE_TAB_BAR_COMPONENT_H
#define OHOS_ACELITE_TAB_BAR_COMPONENT_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_TABS

#include "component.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class TabBarComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TabBarComponent);
    TabBarComponent() = delete;
    TabBarComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~TabBarComponent(){};
    int16_t GetWidth() const
    {
        return width_;
    }
    int16_t GetHeight() const
    {
        return height_;
    }
    char* GetMode() const
    {
        return mode_;
    }
    uint8_t GetChildrenLength();
    const char* GetTextByIndex(uint8_t index);

protected:
    void PreRender() override;
    inline bool CreateNativeViews() override
    {
        return true;
    }
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override
    {
        return nullptr;
    }

private:
    jerry_value_t GetAttrValHandler(jerry_value_t attrKeyHandler);
    void SetWidth();
    void SetHeight();
    void SetMode();
    jerry_value_t options_;
    jerry_value_t children_;
    uint16_t width_;
    uint16_t height_;
    char* mode_;
    const AppStyle* combinedStyle_;
};
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_TABS

#endif // OHOS_ACELITE_TAB_BAR_COMPONENT_H
