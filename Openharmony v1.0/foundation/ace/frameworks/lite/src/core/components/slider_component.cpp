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

#include "slider_component.h"
#include "ace_log.h"
#include "js_fwk_common.h"
#include "key_parser.h"
#include "keys.h"

namespace OHOS {
namespace ACELite {
SliderComponent::SliderComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      minValue_(0),
      maxValue_(DEFAULT_VALUE),
      value_(0),
      visibleWidth_(0),
      visibleHeight_(0),
      startPosition_({0, 0}),
      sliderView_(nullptr),
      eventListener_(nullptr),
      direction_(UISlider::Direction::DIR_LEFT_TO_RIGHT)
{
    SetComponentName(K_SLIDER);
}

bool SliderComponent::CreateNativeViews()
{
    sliderView_ = new UISlider();
    if (sliderView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create native slider view failed");
        return false;
    }
    eventListener_ = new SliderEventListener();
    if (eventListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create listener event failed");
        return false;
    }
    return true;
}

void SliderComponent::ReleaseNativeViews()
{
    if (sliderView_) {
        delete sliderView_;
        sliderView_ = nullptr;
    }

    if (eventListener_) {
        delete eventListener_;
        eventListener_ = nullptr;
    }
}

inline UIView *SliderComponent::GetComponentRootView() const
{
    return sliderView_;
}

bool SliderComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_MIN:
            minValue_ = IntegerOf(attrValue);
            break;
        case K_MAX:
            maxValue_ = IntegerOf(attrValue);
            break;
        case K_STEP:
            // depend on native implementation
            break;
        case K_VALUE:
            value_ = IntegerOf(attrValue);
            break;
        default:
            return false;
    }
    return true;
}

bool SliderComponent::RegisterEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    if ((sliderView_ == nullptr) || !KeyParser::IsKeyValid(eventTypeId) || IS_UNDEFINED(funcValue)) {
        return false;
    }

    // slider's event type has bigger priority than common ones, so try private handler first
    bool registerResult = RegisterPrivateEventListener(eventTypeId, funcValue);
    if (registerResult) {
        return true;
    }
    // try common ones if no private ones get hitted
    registerResult = RegisterCommonEventListener(*sliderView_, eventTypeId, funcValue);
    return registerResult;
}

bool SliderComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    switch (eventTypeId) {
        case K_CHANGE:
            sliderView_->SetSliderEventListener(eventListener_);
            eventListener_->SetBindChangeFuncName(funcValue);
            break;
        default:
            return false;
    }

    sliderView_->SetDraggable(true);
    sliderView_->SetTouchable(true);
    return true;
}

bool SliderComponent::ApplyPrivateStyle(const AppStyleItem *style)
{
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    uint16_t stylePropNameId = GetStylePropNameId(style);
    switch (stylePropNameId) {
        case K_COLOR: {
            // set slider background style color
            if (!GetStyleColorValue(style, color, alpha)) {
                return false;
            }
            sliderView_->SetBackgroundStyle(STYLE_BACKGROUND_COLOR, GetRGBColor(color).full);
            sliderView_->SetBackgroundStyle(STYLE_BACKGROUND_OPA, alpha);
            break;
        }
        case K_SELECTED_COLOR: {
            // set slider indicator style color
            if (!GetStyleColorValue(style, color, alpha)) {
                return false;
            }
            sliderView_->SetForegroundStyle(STYLE_BACKGROUND_COLOR, GetRGBColor(color).full);
            sliderView_->SetForegroundStyle(STYLE_BACKGROUND_OPA, alpha);
            break;
        }
        case K_BLOCK_COLOR: {
            // set slider knob style color
            if (!GetStyleColorValue(style, color, alpha)) {
                return false;
            }
            sliderView_->SetKnobStyle(STYLE_BACKGROUND_COLOR, GetRGBColor(color).full);
            sliderView_->SetKnobStyle(STYLE_BACKGROUND_OPA, alpha);
            break;
        }
        case K_LEFT: {
            startPosition_.x = GetStylePixelValue(style);
            break;
        }
        case K_TOP: {
            startPosition_.y = GetStylePixelValue(style);
            break;
        }
        case K_DIRECTION: {
            SetDirection(GetStyleStrValue(style));
            break;
        }
        case K_HEIGHT: {
            visibleHeight_ = GetStylePixelValue(style);
            break;
        }
        case K_WIDTH: {
            visibleWidth_ = GetStylePixelValue(style);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

void SliderComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if ((sliderView_ == nullptr) || !updateResult || !KeyParser::IsKeyValid(attrKeyId)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "slider component post update check args failed");
        return;
    }
    switch (attrKeyId) {
        case K_LEFT:
        case K_TOP:
            sliderView_->SetPosition(startPosition_.x, startPosition_.y);
            sliderView_->Invalidate();
            break;
        case K_HEIGHT:
        case K_WIDTH:
            sliderView_->SetHeight(visibleHeight_);
            sliderView_->SetWidth(visibleWidth_);
            if (direction_ == UISlider::Direction::DIR_BOTTOM_TO_TOP) {
                sliderView_->SetValidWidth(SLIDER_WIDTH);
                sliderView_->SetValidHeight(visibleHeight_ - KNOB_WIDTH);
            } else {
                sliderView_->SetValidHeight(SLIDER_WIDTH);
                sliderView_->SetValidWidth(visibleWidth_ - KNOB_WIDTH);
            }
            sliderView_->Invalidate();
            break;
        case K_MAX:
        case K_MIN:
        case K_VALUE:
            sliderView_->SetRange(maxValue_, minValue_);
            sliderView_->SetValue(value_);
            sliderView_->Invalidate();
            break;
        default:
            break;
    }
}

void SliderComponent::PostRender()
{
    if (sliderView_ == nullptr) {
        return;
    }

    if (value_ < minValue_) {
        value_ = minValue_;
    } else if (value_ > maxValue_) {
        value_ = maxValue_;
    }
    sliderView_->SetDirection(direction_);
    sliderView_->SetPosition(startPosition_.x, startPosition_.y);
    sliderView_->SetRange(maxValue_, minValue_);
    sliderView_->SetHeight(visibleHeight_);
    sliderView_->SetWidth(visibleWidth_);
    if (direction_ == UISlider::Direction::DIR_BOTTOM_TO_TOP) {
        sliderView_->SetValidWidth(SLIDER_WIDTH);
        sliderView_->SetValidHeight(visibleHeight_ - KNOB_WIDTH);
    } else {
        sliderView_->SetValidHeight(SLIDER_WIDTH);
        sliderView_->SetValidWidth(visibleWidth_ - KNOB_WIDTH);
    }
    sliderView_->SetKnobWidth(KNOB_WIDTH);
    sliderView_->SetSliderRadius(DEFAULT_BORDER_RADIUS, DEFAULT_BORDER_RADIUS, KNOB_RADIUS);
    sliderView_->SetBackgroundStyle(STYLE_LINE_CAP, CapType::CAP_ROUND);
    sliderView_->SetForegroundStyle(STYLE_LINE_CAP, CapType::CAP_ROUND);
    sliderView_->SetBackgroundStyle(STYLE_BORDER_WIDTH, 0);
    sliderView_->SetForegroundStyle(STYLE_BORDER_WIDTH, 0);
    sliderView_->SetKnobStyle(STYLE_BORDER_WIDTH, 0);
    sliderView_->SetValue(value_);
}

void SliderComponent::SetDirection(const char * const directionValue)
{
    if (directionValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get js slider direction is nullptr.");
        return;
    }
    const char * const sliderDirectionColumn = "column";
    direction_ = (!strcmp(directionValue, sliderDirectionColumn)) ? UISlider::Direction::DIR_BOTTOM_TO_TOP
                                                                  : UISlider::Direction::DIR_LEFT_TO_RIGHT;
}
} // namespace ACELite
} // namespace OHOS
