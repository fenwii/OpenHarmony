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

#include "progress_component.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "component.h"
#include "key_parser.h"
#include "keys.h"
#include "stylemgr/app_style.h"
#include "ui_box_progress.h"
#include "ui_circle_progress.h"

namespace OHOS {
namespace ACELite {
ProgressComponent::ProgressComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      options_(options),
      progressView_(nullptr),
      type_(HORIZONTAL),
      hStrokeWidth_(0),
      startAngle_(-1),
      totalAngle_(-1)
{
    SetComponentName(K_PROGRESS);
}

bool ProgressComponent::CreateNativeViews()
{
    // Step1. get progress type
    type_ = GetType();
    // Step2. create progress object
    if (type_ == ARC) {
        progressView_ = new UICircleProgress();

        if (progressView_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create circle progress error");
            return false;
        }

        // set default value
        UICircleProgress *circleProgress = reinterpret_cast<UICircleProgress *>(progressView_);
        circleProgress->SetRadius(circleProgress->GetRadius());
        circleProgress->SetStartAngle(circleProgress->GetStartAngle());
        circleProgress->SetEndAngle(circleProgress->GetEndAngle());

        circleProgress->SetBackgroundStyle(StyleDefault::GetBrightStyle());
        const int8_t defaultLineWidth = 32;
        circleProgress->SetBackgroundStyle(STYLE_LINE_WIDTH, defaultLineWidth); // Compatible with rich devices
        circleProgress->SetBackgroundStyle(STYLE_LINE_CAP, CapType::CAP_ROUND);

        circleProgress->SetForegroundStyle(StyleDefault::GetBrightColorStyle());
        circleProgress->SetForegroundStyle(STYLE_BACKGROUND_OPA, 0);
        circleProgress->SetForegroundStyle(STYLE_BORDER_OPA, 0);
        circleProgress->SetForegroundStyle(STYLE_LINE_WIDTH, defaultLineWidth);
        circleProgress->SetForegroundStyle(STYLE_LINE_CAP, CapType::CAP_ROUND);
    } else {
        progressView_ = new UIBoxProgress();

        if (progressView_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create horizon progress error");
            return false;
        }

        UIBoxProgress *horizonProgress = reinterpret_cast<UIBoxProgress *>(progressView_);
        // set default style for progress & background
        Style progressStyle = StyleDefault::GetBrightColorStyle();
        Style backStyle = StyleDefault::GetBrightStyle();
        horizonProgress->SetForegroundStyle(progressStyle);
        horizonProgress->SetBackgroundStyle(backStyle);

        // set default progress self border width
        horizonProgress->SetForegroundStyle(STYLE_BORDER_WIDTH, 0);
        horizonProgress->SetBackgroundStyle(STYLE_BORDER_WIDTH, 0);
        // set defaut progress stroke width & canvas width & canvas height & border width
        hStrokeWidth_ = DEFAULT_STROKE_WIDTH;
    }
    return true;
}

void ProgressComponent::ReleaseNativeViews()
{
    if (progressView_) {
        delete progressView_;
        progressView_ = nullptr;
    }
}

inline UIView *ProgressComponent::GetComponentRootView() const
{
    return progressView_;
}

bool ProgressComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_PERCENT: {
            // set the specific attribute of this progress view
            int16_t rangeMax = 100;
            int16_t rangeMin = 0;
            progressView_->SetRange(rangeMax, rangeMin);
            progressView_->SetValue(IntegerOf(attrValue));
            return true;
        }
        default: {
            return false;
        }
    }
}

bool ProgressComponent::ApplyPrivateStyle(const AppStyleItem *style)
{
    bool setResult = true;

    if (type_ == ARC) {
        setResult = SetArcProgressStyle(style);
    } else {
        setResult = SetHorizonProgressStyle(style);
    }
    return setResult;
}

ProgressType ProgressComponent::GetType() const
{
    ProgressType pType = HORIZONTAL;
    uint16_t len = 0;
    char *typeValue = GetStringAttrByName(ATTR_TYPE, &len);
    if (typeValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "type value is a nullptr");
        return pType;
    }
    uint16_t typeValueId = KeyParser::ParseKeyId(typeValue, len);
    if (typeValueId == K_ARC) {
        pType = ARC;
    }
    ace_free(typeValue);
    typeValue = nullptr;
    return pType;
}

char *ProgressComponent::GetStringAttrByName(const char * const name, uint16_t *len) const
{
    char *strValue = nullptr;
    jerry_value_t attrsPropValue = jerryx_get_property_str(options_, ATTR_ATTRS);
    if (!jerry_value_is_undefined(attrsPropValue)) {
        jerry_value_t attrPropValue = jerryx_get_property_str(attrsPropValue, name);
        if (jerry_value_is_string(attrPropValue)) {
            strValue = MallocStringOf(attrPropValue, len);
        } else {
            HILOG_ERROR(HILOG_MODULE_ACE, "progress_component: target attribute: %s, value format is error", name);
        }
        jerry_release_value(attrPropValue);
    } else {
        HILOG_INFO(HILOG_MODULE_ACE, "progress_component: target attribute: %s, not exist", name);
    }
    jerry_release_value(attrsPropValue);
    return strValue;
}

void ProgressComponent::HorizonProgressPostDeal() const
{
    // set width & height of progress
    UIBoxProgress *horizonProgress = reinterpret_cast<UIBoxProgress *>(progressView_);
    if (horizonProgress->GetWidth() < 0) {
        horizonProgress->SetValidWidth(0);
    } else {
        horizonProgress->SetValidWidth(horizonProgress->GetWidth());
    }
    horizonProgress->SetValidHeight(hStrokeWidth_);
}

void ProgressComponent::SetAngles() const
{
    UICircleProgress *circleProgress = reinterpret_cast<UICircleProgress *>(progressView_);
    uint8_t defaultStartAngle = 240;
    if (startAngle_ == -1) {
        circleProgress->SetStartAngle(defaultStartAngle);
    } else {
        circleProgress->SetStartAngle(startAngle_);
    }
    if (totalAngle_ == -1) {
        uint8_t defaultTotalAngle = 240;
        circleProgress->SetEndAngle(defaultStartAngle + defaultTotalAngle);
    } else {
        circleProgress->SetEndAngle(startAngle_ + totalAngle_);
    }
}

bool ProgressComponent::SetArcProgressStyle(const AppStyleItem *style)
{
    if (progressView_ == nullptr) {
        return false;
    }

    UICircleProgress *circleProgress = reinterpret_cast<UICircleProgress *>(progressView_);

    uint16_t stylePropNameId = GetStylePropNameId(style);

    switch (stylePropNameId) {
        case K_CENTER_X: {
            Point point = circleProgress->GetCenterPosition();
            point.x = GetStylePixelValue(style);
            circleProgress->SetCenterPosition(point.x, point.y);
            return true;
        }
        case K_CENTER_Y: {
            Point point = circleProgress->GetCenterPosition();
            point.y = GetStylePixelValue(style);
            circleProgress->SetCenterPosition(point.x, point.y);
            return true;
        }
        case K_RADIUS: {
            circleProgress->SetRadius(GetStylePixelValue(style));
            return true;
        }
        case K_START_ANGLE: {
            const int16_t minStartAngle = 0;
            const int16_t maxStartAngle = 360;
            startAngle_ = GetStyleDegValue(style); // Compatible with rich devices, value should between -180 and 0
            if (startAngle_ > maxStartAngle) {
                startAngle_ = maxStartAngle;
            } else if (startAngle_ < minStartAngle) {
                startAngle_ = minStartAngle;
            }
            return true;
        }
        case K_TOTAL_ANGLE: {
            const int16_t minStartAngle = -360;
            const int16_t maxStartAngle = 360;
            totalAngle_ = GetStyleDegValue(style); // Compatible with rich devices, value should between 0 and 180
            if (totalAngle_ < minStartAngle) {
                totalAngle_ = minStartAngle;
            } else if (totalAngle_ > maxStartAngle) {
                totalAngle_ = maxStartAngle;
            }
            return true;
        }
        case K_COLOR: {
            uint32_t color = 0;
            uint8_t alpha = OPA_OPAQUE;
            if (!GetStyleColorValue(style, color, alpha)) {
                return false;
            }
            circleProgress->SetForegroundStyle(STYLE_LINE_COLOR, GetRGBColor(color).full);
            circleProgress->SetForegroundStyle(STYLE_LINE_OPA, alpha);
            return true;
        }
        case K_STROKE_WIDTH: {
            circleProgress->SetBackgroundStyle(STYLE_LINE_WIDTH, GetStylePixelValue(style));
            circleProgress->SetForegroundStyle(STYLE_LINE_WIDTH, GetStylePixelValue(style));
            return true;
        }
        case K_BACKGROUND_COLOR: {
            uint32_t color = 0;
            uint8_t alpha = OPA_OPAQUE;
            if (!GetStyleColorValue(style, color, alpha)) {
                return false;
            }
            circleProgress->SetBackgroundStyle(STYLE_LINE_COLOR, GetRGBColor(color).full);
            circleProgress->SetBackgroundStyle(STYLE_LINE_OPA, alpha);
            return true;
        }
        default: {
            return false;
        }
    }
}

bool ProgressComponent::SetHorizonProgressStyle(const AppStyleItem *style)
{
    if (progressView_ == nullptr) {
        return false;
    }

    UIBoxProgress *horizonProgress = reinterpret_cast<UIBoxProgress *>(progressView_);
    uint16_t stylePropNameId = GetStylePropNameId(style);

    switch (stylePropNameId) {
        // Get stroke width.
        case K_STROKE_WIDTH: {
            hStrokeWidth_ = GetStylePixelValue(style);
            break;
        }
        // Set horizon progress style: color.
        case K_COLOR: {
            uint32_t color = 0;
            uint8_t alpha = OPA_OPAQUE;
            if (!GetStyleColorValue(style, color, alpha)) {
                return false;
            }
            horizonProgress->SetForegroundStyle(STYLE_BACKGROUND_COLOR, GetRGBColor(color).full);
            horizonProgress->SetForegroundStyle(STYLE_BACKGROUND_OPA, alpha);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

void ProgressComponent::PostRender()
{
    if (type_ == HORIZONTAL) {
        HorizonProgressPostDeal();
    } else if (type_ == ARC) {
        SetAngles();
    }
}

void ProgressComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if (type_ == HORIZONTAL) {
        HorizonProgressPostDeal();
    } else if (type_ == ARC) {
        if ((attrKeyId == K_DIRECTION) || (attrKeyId == K_START_ANGLE) || (attrKeyId == K_TOTAL_ANGLE)) {
            SetAngles();
        }
    } else {
        // Do nothing
    }
}
} // namespace ACELite
} // namespace OHOS
