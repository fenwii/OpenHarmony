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

#ifndef OHOS_ACELITE_ANALOG_CLOCK_COMPONENT_H
#define OHOS_ACELITE_ANALOG_CLOCK_COMPONENT_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_ANALOG_CLOCK

#include "component.h"
#include "non_copyable.h"
#include "stylemgr/app_style.h"
#include "ui_analog_clock.h"

namespace OHOS {
namespace ACELite {
class AnalogClockComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(AnalogClockComponent);
    AnalogClockComponent() = delete;
    AnalogClockComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~AnalogClockComponent() {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ProcessChildren() override;

private:
    int32_t GetIntegerProperty(jerry_value_t obj, const char * const name);
    bool GetBoolProperty(jerry_value_t obj, const char * const name);
    void SetImageHand(uint16_t handType, jerry_value_t child, UIView* childView);
    void SetRectHand(uint16_t handType, jerry_value_t child, UIView* childView);
    void UpdateClock();

    uint8_t hour_;
    uint8_t min_;
    uint8_t sec_;
    jerry_value_t children_;
    UIAnalogClock* clockView_;
    const char * const clockHandPivotX = "pivot-x";
    const char * const clockHandPivotY = "pivot-y";
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_ANALOG_CLOCK_COMPONENT_H

#endif // FEATURE_COMPONENT_ANALOG_CLOCK
