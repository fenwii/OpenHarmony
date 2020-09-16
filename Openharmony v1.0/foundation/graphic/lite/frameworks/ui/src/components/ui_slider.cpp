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

#include "common/image.h"
#include "components/ui_slider.h"
#include "draw/draw_image.h"
#include "draw/draw_rect.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"
#include "themes/theme_manager.h"

namespace OHOS {
UISlider::UISlider()
    : knobWidth_(0), knobWidthSetFlag_(false), knobStyleAllocFlag_(false), knobImage_(nullptr), listener_(nullptr)
{
    SetTouchable(true);
    SetDraggable(true);
    Theme* theme = ThemeManager::GetInstance().GetCurrent();
    if (theme != nullptr) {
        knobStyle_ = &(theme->GetSliderKnobStyle());
    } else {
        knobStyle_ = &(StyleDefault::GetSliderKnobStyle());
    }
}

UISlider::~UISlider()
{
    if (knobImage_ != nullptr) {
        delete knobImage_;
        knobImage_ = nullptr;
    }

    if (knobStyleAllocFlag_) {
        delete knobStyle_;
        knobStyle_ = nullptr;
        knobStyleAllocFlag_ = false;
    }
}

void UISlider::SetKnobStyle(const Style& style)
{
    if (!knobStyleAllocFlag_) {
        knobStyle_ = new Style;
        knobStyleAllocFlag_ = true;
    }
    *knobStyle_ = style;
}

void UISlider::SetKnobStyle(uint8_t key, int64_t value)
{
    if (!knobStyleAllocFlag_) {
        knobStyle_ = new Style(*knobStyle_);
        knobStyleAllocFlag_ = true;
    }
    knobStyle_->SetStyle(key, value);
}

const Style& UISlider::GetKnobStyle() const
{
    return *knobStyle_;
}

int64_t UISlider::GetKnobStyle(uint8_t key) const
{
    return knobStyle_->GetStyle(key);
}

int16_t UISlider::CalculateCurrentValue(int16_t length, int16_t totalLength)
{
    if (totalLength != 0) {
        return static_cast<int16_t>(rangeMin_ + (static_cast<int64_t>(rangeMax_) - rangeMin_) * length / totalLength);
    }
    return 0;
}

int16_t UISlider::UpdateCurrentValue(const Point& knobPosition)
{
    Point startPoint;
    Rect rect = GetContentRect();
    startPoint.x = rect.GetLeft() + ((GetWidth() - progressWidth_) >> 1);
    startPoint.y = rect.GetTop() + ((GetHeight() - progressHeight_) >> 1);

    int16_t value = curValue_;
    switch (direction_) {
        case Direction::DIR_LEFT_TO_RIGHT:
            if (knobPosition.x <= startPoint.x) {
                value = rangeMin_;
            } else if (knobPosition.x >= startPoint.x + progressWidth_) {
                value = rangeMax_;
            } else {
                value = CalculateCurrentValue(knobPosition.x - startPoint.x, progressWidth_);
            }
            break;
        case Direction::DIR_RIGHT_TO_LEFT:
            if (knobPosition.x <= startPoint.x) {
                value = rangeMax_;
            } else if (knobPosition.x >= startPoint.x + progressWidth_) {
                value = rangeMin_;
            } else {
                value = CalculateCurrentValue(startPoint.x + progressWidth_ - knobPosition.x, progressWidth_);
            }
            break;
        case Direction::DIR_BOTTOM_TO_TOP:
            if (knobPosition.y <= startPoint.y) {
                value = rangeMax_;
            } else if (knobPosition.y >= startPoint.y + progressHeight_) {
                value = rangeMin_;
            } else {
                value = CalculateCurrentValue(startPoint.y + progressHeight_ - knobPosition.y, progressHeight_);
            }
            break;
        case Direction::DIR_TOP_TO_BOTTOM:
            if (knobPosition.y <= startPoint.y) {
                value = rangeMin_;
            } else if (knobPosition.y >= startPoint.y + progressHeight_) {
                value = rangeMax_;
            } else {
                value = CalculateCurrentValue(knobPosition.y - startPoint.y, progressHeight_);
            }
            break;
        default:
            GRAPHIC_LOGW("UISlider::UpdateProgressValue Direction error!\n");
    }
    SetValue(value);
    return value;
}

void UISlider::OnClickEvent(const ClickEvent& event)
{
    Point knobPosition = event.GetCurrentPos();
    int16_t value = UpdateCurrentValue(knobPosition);
    if (listener_ != nullptr) {
        listener_->OnChange(value);
    }
    UIView::OnClickEvent(event);
    Invalidate();
}

bool UISlider::OnDragEvent(const DragEvent& event)
{
    Point knobPosition = event.GetCurrentPos();
    int16_t value = UpdateCurrentValue(knobPosition);
    if (listener_ != nullptr) {
        listener_->OnChange(value);
    }
    Invalidate();
    return UIView::OnDragEvent(event);
}

bool UISlider::OnDragEndEvent(const DragEvent& event)
{
    Point knobPosition = event.GetCurrentPos();
    int16_t value = UpdateCurrentValue(knobPosition);
    if (listener_ != nullptr) {
        listener_->OnChange(value);
        listener_->OnRelease(value);
    }
    Invalidate();
    return UIView::OnDragEndEvent(event);
}

int16_t UISlider::GetKnobWidth()
{
    if (!knobWidthSetFlag_) {
        if (direction_ == Direction::DIR_LEFT_TO_RIGHT || direction_ == Direction::DIR_RIGHT_TO_LEFT) {
            knobWidth_ = progressHeight_;
        } else {
            knobWidth_ = progressWidth_;
        }
    }
    return knobWidth_;
}

void UISlider::SetImage(const ImageInfo* backgroundImage, const ImageInfo* foregroundImage, const ImageInfo* knobImage)
{
    if (backgroundImage_ == nullptr) {
        backgroundImage_ = new Image();
    }
    backgroundImage_->SetSrc(backgroundImage);

    if (foregroundImage_ == nullptr) {
        foregroundImage_ = new Image();
    }
    foregroundImage_->SetSrc(foregroundImage);

    if (knobImage_ == nullptr) {
        knobImage_ = new Image();
    }
    knobImage_->SetSrc(knobImage);
}

void UISlider::SetImage(const char* backgroundImage, const char* foregroundImage, const char* knobImage)
{
    if (backgroundImage_ == nullptr) {
        backgroundImage_ = new Image();
    }
    backgroundImage_->SetSrc(backgroundImage);

    if (foregroundImage_ == nullptr) {
        foregroundImage_ = new Image();
    }
    foregroundImage_->SetSrc(foregroundImage);

    if (knobImage_ == nullptr) {
        knobImage_ = new Image();
    }
    knobImage_->SetSrc(knobImage);
}

void UISlider::DrawKnob(const Rect& invalidatedArea, const Rect& foregroundRect)
{
    int16_t halfKnobWidth = GetKnobWidth() >> 1;
    int16_t offset;
    Rect knobBar;
    switch (direction_) {
        case Direction::DIR_LEFT_TO_RIGHT: {
            offset = (knobWidth_ - progressHeight_) >> 1;
            knobBar.SetRect(foregroundRect.GetRight() - halfKnobWidth, foregroundRect.GetTop() - offset,
                            foregroundRect.GetRight() + halfKnobWidth, foregroundRect.GetBottom() + offset);
            break;
        }
        case Direction::DIR_RIGHT_TO_LEFT: {
            offset = (knobWidth_ - progressHeight_) >> 1;
            knobBar.SetRect(foregroundRect.GetLeft() - halfKnobWidth, foregroundRect.GetTop() - offset,
                            foregroundRect.GetLeft() + halfKnobWidth, foregroundRect.GetBottom() + offset);
            break;
        }
        case Direction::DIR_BOTTOM_TO_TOP: {
            offset = (knobWidth_ - progressWidth_) >> 1;
            knobBar.SetRect(foregroundRect.GetLeft() - offset, foregroundRect.GetTop() - halfKnobWidth,
                            foregroundRect.GetRight() + offset, foregroundRect.GetTop() + halfKnobWidth);
            break;
        }
        case Direction::DIR_TOP_TO_BOTTOM: {
            offset = (knobWidth_ - progressWidth_) >> 1;
            knobBar.SetRect(foregroundRect.GetLeft() - offset, foregroundRect.GetBottom() - halfKnobWidth,
                            foregroundRect.GetRight() + offset, foregroundRect.GetBottom() + halfKnobWidth);
            break;
        }
        default: {
            GRAPHIC_LOGW("UISlider::DrawKnob Direction error!\n");
        }
    }
    DrawValidRect(knobImage_, knobBar, invalidatedArea, *knobStyle_, 0);
}

void UISlider::OnDraw(const Rect& invalidatedArea)
{
    DrawRect::Draw(GetRect(), invalidatedArea, *style_);

    Rect trunc(invalidatedArea);
    if (trunc.Intersect(trunc, GetContentRect())) {
        DrawBackground(trunc);
        Rect foregroundRect;
        DrawForeground(trunc, foregroundRect);
        DrawKnob(trunc, foregroundRect);
    }
}
} // namespace OHOS