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

#ifdef FEATURE_COMPONENT_ANALOG_CLOCK

#include "ace_log.h"
#include "analog_clock_component.h"
#include "keys.h"
#include "ui_image_view.h"

namespace OHOS {
namespace ACELite {
AnalogClockComponent::AnalogClockComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager)
    : Component(options, children, styleManager), hour_(0), min_(0), sec_(0), children_(children), clockView_(nullptr),
{
    SetComponentName(K_ANALOG_CLOCK);
}

bool AnalogClockComponent::CreateNativeViews()
{
    clockView_ = new UIAnalogClock();
    if (clockView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: create native view failed!");
        return false;
    }
    return true;
}

void AnalogClockComponent::ReleaseNativeViews()
{
    if (clockView_) {
        delete clockView_;
        clockView_ = nullptr;
    }
}

inline UIView* AnalogClockComponent::GetComponentRootView() const
{
    return clockView_;
}

bool AnalogClockComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    if ((clockView_ == nullptr) || !KeyParser::IsKeyValid(attrKeyId) || IS_UNDEFINED(attrValue)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: set private attribute failed!");
        return false;
    }
    switch (attrKeyId) {
        case K_HOUR:
            hour_ = IntegerOf(attrValue);
            break;
        case K_MIN:
            min_ = IntegerOf(attrValue);
            break;
        case K_SEC:
            sec_ = IntegerOf(attrValue);
            break;
        default:
            return false;
    }
    UpdateClock();
    return true;
}

void AnalogClockComponent::UpdateClock()
{
    if (clockView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: update clock failed!");
        return;
    }
    clockView_->SetTime24Hour(hour_, min_, sec_);
}

bool AnalogClockComponent::ProcessChildren()
{
    if (jerry_value_is_undefined(children_) || (clockView_ == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: process children failed!");
        return false;
    }

    uint16_t length = jerry_get_array_length(children_);
    for (uint16_t index = 0; index < length; index++) {
        jerry_value_t child = jerry_get_property_by_index(children_, index);
        if (jerry_value_is_undefined(child)) {
            continue;
        }
        UIView* childView = ComponentUtils::GetViewFromBindingObject(child);
        if (childView == nullptr) {
            jerry_release_value(child);
            continue;
        }

        uint16_t handType = GetIntegerProperty(child, ATTR_TYPE);
        if (handType > 0) { // clock-hand
            bool isImage = GetBoolProperty(child, CLOCK_HAND_IS_IMAGE);
            if (isImage) {
                SetImageHand(handType, child, childView);
            } else {
                SetRectHand(handType, child, childView);
            }
        } else { // clock background
            clockView_->Add(childView);
        }
        jerry_release_value(child);
    }
    clockView_->SetInitTime24Hour(hour_, min_, sec_);
    clockView_->SetDragParentInstead(true);
    return true;
}

void AnalogClockComponent::SetImageHand(uint16_t handType, jerry_value_t child, UIView* childView)
{
    UIImageView* imageView = reinterpret_cast<UIImageView*>(childView);
    if (imageView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: childView reinterpret_cast failed!");
        return;
    }
    int16_t posX = imageView->GetX();
    int16_t posY = imageView->GetY();
    int16_t pivotX = GetIntegerProperty(child, clockHandPivotX);
    int16_t pivotY = GetIntegerProperty(child, clockHandPivotY);
    switch (handType) {
        case K_HOUR:
            clockView_->SetHandImage(UIAnalogClock::HandType::HOUR_HAND,
                *imageView, {posX, posY}, {pivotX, pivotY});
            break;
        case K_MIN:
            clockView_->SetHandImage(UIAnalogClock::HandType::MINUTE_HAND,
                *imageView, {posX, posY}, {pivotX, pivotY});
            break;
        case K_SEC:
            clockView_->SetHandImage(UIAnalogClock::HandType::SECOND_HAND,
                *imageView, {posX, posY}, {pivotX, pivotY});
            break;
        default:
            HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: UIImageView hand type error!");
            break;
    }
}

void AnalogClockComponent::SetRectHand(uint16_t handType, jerry_value_t child, UIView* childView)
{
    int16_t posX = childView->GetX();
    int16_t posY = childView->GetY();
    int16_t width = childView->GetWidth();
    int16_t height = childView->GetHeight();
    int16_t pivotX = GetIntegerProperty(child, clockHandPivotX);
    int16_t pivotY = GetIntegerProperty(child, clockHandPivotY);
    int32_t fillColor = GetIntegerProperty(child, COMMON_STYLE_COLOR);
    ColorType colorRGB = GetRGBColor(fillColor);
    uint16_t opacity = GetIntegerProperty(child, COMMON_STYLE_OPACITY);
    switch (handType) {
        case K_HOUR:
            clockView_->SetHandLine(UIAnalogClock::HandType::HOUR_HAND, {posX, posY},
                {pivotX, pivotY}, colorRGB, width, height, opacity);
            break;
        case K_MIN:
            clockView_->SetHandLine(UIAnalogClock::HandType::MINUTE_HAND, {posX, posY},
                {pivotX, pivotY}, colorRGB, width, height, opacity);
            break;
        case K_SEC:
            clockView_->SetHandLine(UIAnalogClock::HandType::SECOND_HAND, {posX, posY},
                {pivotX, pivotY}, colorRGB, width, height, opacity);
            break;
        default:
            HILOG_ERROR(HILOG_MODULE_ACE, "AnalogClockComponent: rectangle hand type error!");
            break;
    }
}

int32_t AnalogClockComponent::GetIntegerProperty(jerry_value_t obj, const char * const name)
{
    jerry_value_t propName = jerry_create_string((const jerry_char_t*)name);
    jerry_value_t propValue = jerry_get_property(obj, propName);

    jerry_value_t target = jerry_value_to_number(propValue);
    int32_t res = (int32_t)jerry_get_number_value(target);
    jerry_release_value(target);
    jerry_release_value(propValue);
    jerry_release_value(propName);
    return res;
}

bool AnalogClockComponent::GetBoolProperty(jerry_value_t obj, const char * const name)
{
    jerry_value_t propName = jerry_create_string((const jerry_char_t*)name);
    jerry_value_t propValue = jerry_get_property(obj, propName);

    bool res = jerry_value_to_boolean(propValue);
    jerry_release_value(propValue);
    jerry_release_value(propName);
    return res;
}
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_ANALOG_CLOCK
