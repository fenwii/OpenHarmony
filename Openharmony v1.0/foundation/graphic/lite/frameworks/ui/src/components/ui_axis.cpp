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

#include "components/ui_axis.h"
#include "common/screen.h"
#include "draw/draw_line.h"

namespace OHOS {
UIAxis::UIAxis()
    : maxRange_(0),
      minRange_(0),
      start_({0, 0}),
      end_({0, 0}),
      markInterval_(0),
      dataPerMark_(0),
      dataInterval_(0),
      markDataCount_(AXIS_DEFAULT_MARK_INTERVAL),
      enableReverse_(false)
{
    SetStyle(STYLE_LINE_WIDTH, 1);
    SetStyle(STYLE_LINE_COLOR, Color::White().full);
}

void UIAxis::SetLineColor(const ColorType& color)
{
    SetStyle(STYLE_LINE_COLOR, color.full);
}

void UIXAxis::SetMarkNum(uint16_t count)
{
    if ((count == 0) || (count > Screen::GetInstance().GetWidth())) {
        return;
    }
    markDataCount_ = count;
    UpdateAxis();
}

bool UIXAxis::SetDataRange(uint16_t min, uint16_t max)
{
    if (max <= min) {
        return false;
    }
    maxRange_ = max;
    minRange_ = min;
    return UpdateAxis();
}

void UIXAxis::UpdateAxisPoints()
{
    Rect current = GetContentRect();
    start_.x = current.GetLeft();
    end_.x = current.GetRight();
    start_.y = enableReverse_ ? current.GetTop() : current.GetBottom();
    end_.y = start_.y;
}

bool UIXAxis::UpdateAxis()
{
    UpdateAxisPoints();
    int16_t xAxisLength = end_.x - start_.x + 1;
    if (xAxisLength <= 0) {
        return false;
    }

    if (markDataCount_ != 0) {
        dataInterval_ = static_cast<float>((maxRange_ - minRange_) / markDataCount_);
        markInterval_ = static_cast<float>(xAxisLength) / markDataCount_;
        if (maxRange_ > minRange_) {
            dataPerMark_ = markInterval_ / dataInterval_;
        }
    }

    return true;
}

void UIXAxis::TranslateToPixel(int16_t& value)
{
    float minXStep = dataPerMark_ ? dataPerMark_ : markInterval_;
    value = start_.x + static_cast<int16_t>((value - minRange_) * minXStep);
}

void UIAxis::OnDraw(const Rect& invalidatedArea)
{
    DrawLine::Draw(start_, end_, invalidatedArea, style_->lineWidth_, style_->lineColor_, style_->lineOpa_);
    DrawAxisMark(invalidatedArea);
}

void UIXAxis::DrawAxisMark(const Rect& invalidatedArea)
{
    Point start;
    Point end;
    uint16_t index = 1;
    while (index <= markDataCount_) {
        start.y = start_.y;
        start.x = start_.x + static_cast<int16_t>(index * markInterval_);
        end.y = enableReverse_ ? (start.y + AXIS_DEFAULT_MARK_LENGTH) : (start.y - AXIS_DEFAULT_MARK_LENGTH);
        end.x = start.x;
        DrawLine::Draw(start, end, invalidatedArea, style_->lineWidth_, style_->lineColor_, style_->lineOpa_);
        index++;
    }
}

void UIYAxis::SetMarkNum(uint16_t count)
{
    if ((count == 0) || (count > Screen::GetInstance().GetHeight())) {
        return;
    }
    markDataCount_ = count;
    dataInterval_ = static_cast<float>((maxRange_ - minRange_) / markDataCount_);
}

bool UIYAxis::SetDataRange(uint16_t min, uint16_t max)
{
    if (max <= min) {
        return false;
    }

    maxRange_ = max;
    minRange_ = min;
    return UpdateAxis();
}

void UIYAxis::UpdateAxisPoints()
{
    Rect current = GetContentRect();
    int16_t top = current.GetTop();
    int16_t bottom = current.GetBottom();

    start_.x = current.GetLeft();
    end_.x = start_.x;
    if (enableReverse_) {
        start_.y = top;
        end_.y = bottom;
    } else {
        start_.y = bottom;
        end_.y = top;
    }
}

void UIYAxis::TranslateToPixel(int16_t& value)
{
    float minYStep = dataPerMark_ ? dataPerMark_ : markInterval_;
    if (enableReverse_) {
        value = start_.y + static_cast<int16_t>((maxRange_ - value + minRange_) * minYStep);
    } else {
        value = start_.y - static_cast<int16_t>((value - minRange_) * minYStep);
    }
}

bool UIYAxis::UpdateAxis()
{
    UpdateAxisPoints();
    int16_t yAxisLength = enableReverse_ ? (end_.y - start_.y + 1) : (start_.y - end_.y + 1);
    if (yAxisLength <= 0) {
        return false;
    }

    if (markDataCount_ != 0) {
        dataInterval_ = static_cast<float>((maxRange_ - minRange_) / markDataCount_);
        markInterval_ = static_cast<float>(yAxisLength) / markDataCount_;
        if (dataInterval_ != 0) {
            dataPerMark_ = markInterval_ / dataInterval_;
        }
    }
    return true;
}

void UIYAxis::DrawAxisMark(const Rect& invalidatedArea)
{
    uint16_t index = 1;
    while (index <= markDataCount_) {
        Point start;
        Point end;
        start.x = start_.x;
        start.y = enableReverse_ ? (start_.y + static_cast<int16_t>(index * markInterval_))
                                 : (start_.y - static_cast<int16_t>(index * markInterval_));
        end.x = start.x + AXIS_DEFAULT_MARK_LENGTH;
        end.y = start.y;
        DrawLine::Draw(start, end, invalidatedArea, style_->lineWidth_, style_->lineColor_, style_->lineOpa_);
        index++;
    }
}
} // namespace OHOS