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

#ifndef OHOS_ACELITE_CLOCK_HAND_COMPONENT_H
#define OHOS_ACELITE_CLOCK_HAND_COMPONENT_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_ANALOG_CLOCK

#include "component.h"
#include "non_copyable.h"
#include "stylemgr/app_style.h"

namespace OHOS {
namespace ACELite {
class ClockHandComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ClockHandComponent);
    ClockHandComponent() = delete;
    ClockHandComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~ClockHandComponent() {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ApplyPrivateStyle(const AppStyleItem* style) override;
    void PostRender() override;

    /**
    * @enum    LayoutType
    *
    * @brief   Values that represent different clock-hand layout types
    */
    enum class LayoutType {
        // UIImageView layout
        IMAGE,
        // Rectangle layout
        RECT
    };

private:
    char* GetStringAttrByName(const char * const name);
    void SetNamedProperty(jerry_value_t obj, const char * const name, jerry_value_t value);
    LayoutType GetLayoutType();

    jerry_value_t options_;
    const AppStyle* combinedStyle_;
    LayoutType layoutType_;
    UIView* clockHandView_;
    int16_t pivotX_;
    int16_t pivotY_;
    int32_t fillColor_;
    uint16_t opacity_;
    char* handType_;
};
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_ANALOG_CLOCK
#endif // OHOS_ACELITE_CLOCK_HAND_COMPONENT_H
