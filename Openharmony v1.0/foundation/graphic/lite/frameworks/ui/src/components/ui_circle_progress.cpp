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

#include "components/ui_circle_progress.h"
#include "draw/draw_arc.h"
#include "draw/draw_line.h"
#include "draw/draw_rect.h"

namespace OHOS {
UICircleProgress::UICircleProgress()
    : center_({0, 0}),
      backgroundImagePos_({0, 0}),
      progressImagePos_({0, 0}),
      radius_(0),
      startAngle_(MIN_ANGLE_VALUE),
      endAngle_(MAX_ANGLE_VALUE)
{
}

void UICircleProgress::SetCenterPosition(int16_t x, int16_t y)
{
    center_.x = x;
    center_.y = y;
}

void UICircleProgress::SetStartAngle(int16_t startAngle)
{
    startAngle_ = startAngle;
}

void UICircleProgress::SetEndAngle(int16_t endAngle)
{
    endAngle_ = endAngle;
}

void UICircleProgress::GetStartEndAngle(int16_t& start, int16_t& end) const
{
    if (startAngle_ > endAngle_) {
        start = endAngle_;
        end = startAngle_;
    } else {
        start = startAngle_;
        end = endAngle_;
    }
}

void UICircleProgress::GetAngleRange(int16_t& start, int16_t& end) const
{
    GetStartEndAngle(start, end);
    DrawArc::GetInstance()->GetDrawRange(start, end);
}

void UICircleProgress::GetRedrawAngle(int16_t& start, int16_t& end) const
{
    GetStartEndAngle(start, end);

    if (startAngle_ == endAngle_) {
        return;
    }

    int16_t angleRange = end - start;
    angleRange = (angleRange > CIRCLE_IN_DEGREE) ? CIRCLE_IN_DEGREE : angleRange;

    int16_t angle = GetCurrentPos(angleRange);
    if (startAngle_ > endAngle_) {
        start = end - angle;
    } else {
        end = angle + start;
    }
    DrawArc::GetInstance()->GetDrawRange(start, end);
}

void UICircleProgress::DrawCommonCircle(const Rect& invalidatedArea)
{
    ArcInfo arcinfo = {{0}};
    arcinfo.radius = radius_;
    int16_t endAngle;
    int16_t startAngle;
    GetRedrawAngle(startAngle, endAngle);

    int16_t start;
    int16_t end;
    GetAngleRange(start, end);
    Rect rect = GetRect();
    arcinfo.center.x = center_.x + rect.GetLeft() + style_->paddingLeft_ + style_->borderWidth_;
    arcinfo.center.y = center_.y + rect.GetTop() + style_->paddingTop_ + style_->borderWidth_;

    if (enableBackground_ && (start != end || backgroundStyle_->lineCap_ == CapType::CAP_ROUND)) {
        arcinfo.imgPos.x = backgroundImagePos_.x + rect.GetLeft();
        arcinfo.imgPos.y = backgroundImagePos_.y + rect.GetTop();
        arcinfo.startAngle = start;
        arcinfo.endAngle = end;
        arcinfo.imgSrc = backgroundImage_;
        DrawArc::GetInstance()->Draw(arcinfo, invalidatedArea, *backgroundStyle_, opaScale_,
                                     backgroundStyle_->lineCap_);
    }

    if (startAngle != endAngle || foregroundStyle_->lineCap_ == CapType::CAP_ROUND) {
        arcinfo.imgPos.x = progressImagePos_.x + rect.GetLeft();
        arcinfo.imgPos.y = progressImagePos_.y + rect.GetTop();
        arcinfo.startAngle = startAngle;
        arcinfo.endAngle = endAngle;
        arcinfo.imgSrc = foregroundImage_;
        DrawArc::GetInstance()->Draw(arcinfo, invalidatedArea, *foregroundStyle_, opaScale_,
                                     foregroundStyle_->lineCap_);
    }
}

void UICircleProgress::OnDraw(const Rect& invalidatedArea)
{
    if (GetRangeSize() == 0) {
        return;
    }

    DrawRect::Draw(GetRect(), invalidatedArea, *style_);

    Rect trunc(invalidatedArea);
    if (trunc.Intersect(trunc, GetContentRect())) {
        DrawCommonCircle(trunc);
    }
}
} // namespace OHOS