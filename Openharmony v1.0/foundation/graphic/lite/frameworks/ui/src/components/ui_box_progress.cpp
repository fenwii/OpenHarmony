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

#include "components/ui_box_progress.h"
#include "draw/draw_arc.h"
#include "draw/draw_rect.h"
#include "graphic_log.h"

namespace OHOS {
UIBoxProgress::UIBoxProgress() : progressWidth_(0), progressHeight_(0)
{
    SetDirection(Direction::DIR_LEFT_TO_RIGHT);
}

void UIBoxProgress::DrawValidRect(const Image* image, const Rect& rect, const Rect& invalidatedArea,
    const Style& style, uint16_t radius)
{
    Rect cordsTmp;
    if ((image != nullptr) && (image->GetSrcType() != IMG_SRC_UNKNOWN)) {
        ImageHeader header = {0};
        image->GetHeader(header);

        Rect area(rect);
        switch (direction_) {
            case Direction::DIR_LEFT_TO_RIGHT:
                cordsTmp.SetPosition(area.GetLeft() - radius, area.GetTop());
                break;
            case Direction::DIR_TOP_TO_BOTTOM:
                cordsTmp.SetPosition(area.GetLeft(), area.GetTop() - radius);
                break;
            case Direction::DIR_RIGHT_TO_LEFT:
                cordsTmp.SetPosition(area.GetRight() + radius - header.width, area.GetTop());
                break;
            case Direction::DIR_BOTTOM_TO_TOP:
                cordsTmp.SetPosition(area.GetLeft(), area.GetBottom() + radius - header.height);
                break;
            default:
                GRAPHIC_LOGE("UIBoxProgress: DrawValidRect direction %d Err!\n", direction_);
                break;
        }
        cordsTmp.SetHeight(header.height);
        cordsTmp.SetWidth(header.width);
        if (area.Intersect(area, invalidatedArea)) {
            image->DrawImage(cordsTmp, area, style, opaScale_);
        }
    } else {
        DrawRect::Draw(rect, invalidatedArea, style);
    }

    if (style.lineCap_ == CapType::CAP_ROUND) {
        DrawRoundCap(image, {cordsTmp.GetX(), cordsTmp.GetY()}, rect, invalidatedArea, radius, style);
    }
}

void UIBoxProgress::DrawRoundCap(const Image* image, const Point& imgPos, const Rect& rect,
    const Rect& invalidatedArea, uint16_t radius, const Style& style)
{
    Point leftTop;
    Point leftBottom;
    Point rightTop;
    Point rightBottom;

    switch (direction_) {
        case Direction::DIR_LEFT_TO_RIGHT:
        case Direction::DIR_RIGHT_TO_LEFT: {
            leftTop.x = rect.GetLeft() - 1;
            leftTop.y = rect.GetTop() + radius - 1;
            leftBottom.x = leftTop.x;
            leftBottom.y = rect.GetBottom() - radius + 1;
            rightTop.x = rect.GetRight() + 1;
            rightTop.y = leftTop.y;
            rightBottom.x = rightTop.x;
            rightBottom.y = leftBottom.y;
            break;
        }

        case Direction::DIR_TOP_TO_BOTTOM:
        case Direction::DIR_BOTTOM_TO_TOP: {
            leftTop.x = rect.GetLeft() + radius - 1;
            leftTop.y = rect.GetTop() - 1;
            rightTop.x = rect.GetRight() - radius + 1;
            rightTop.y = leftTop.y;
            leftBottom.x = leftTop.x;
            leftBottom.y = rect.GetBottom() + 1;
            rightBottom.x = rightTop.x;
            rightBottom.y = leftBottom.y;
            break;
        }
        default:
            GRAPHIC_LOGE("UIBoxProgress: DrawRoundCap direction %d Err!\n", direction_);
            break;
    }

    Style capStyle = style;
    capStyle.lineWidth_ = radius;
    capStyle.lineColor_ = style.bgColor_;
    capStyle.lineOpa_ = style.bgOpa_;
    ArcInfo arcInfo = {{0}};
    arcInfo.radius = radius;
    arcInfo.imgPos = imgPos;
    arcInfo.imgSrc = image;

    arcInfo.center = leftTop;
    arcInfo.startAngle = THREE_QUARTER_IN_DEGREE;
    arcInfo.endAngle = 0;
    DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, capStyle, opaScale_, CapType::CAP_NONE);

    arcInfo.center = leftBottom;
    arcInfo.startAngle = SEMICIRCLE_IN_DEGREE;
    arcInfo.endAngle = THREE_QUARTER_IN_DEGREE;
    DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, capStyle, opaScale_, CapType::CAP_NONE);

    arcInfo.center = rightTop;
    arcInfo.startAngle = 0;
    arcInfo.endAngle = THREE_QUARTER_IN_DEGREE;
    DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, capStyle, opaScale_, CapType::CAP_NONE);

    arcInfo.center = rightBottom;
    arcInfo.startAngle = THREE_QUARTER_IN_DEGREE;
    arcInfo.endAngle = SEMICIRCLE_IN_DEGREE;
    DrawArc::GetInstance()->Draw(arcInfo, invalidatedArea, capStyle, opaScale_, CapType::CAP_NONE);
}

void UIBoxProgress::GetBackgroundParam(Point& startPoint, int16_t& width, int16_t& height, uint16_t& radius,
    const Style& style)
{
    Rect rect = GetContentRect();
    startPoint.x = rect.GetLeft() + ((GetWidth() - progressWidth_) >> 1);
    startPoint.y = rect.GetTop() + ((GetHeight() - progressHeight_) >> 1);

    radius = 0;
    width = progressWidth_;
    height = progressHeight_;
    if (style.lineCap_ == CapType::CAP_ROUND) {
        switch (direction_) {
            case Direction::DIR_LEFT_TO_RIGHT:
            case Direction::DIR_RIGHT_TO_LEFT:
                radius = (progressHeight_ + 1) >> 1;
                width -= radius << 1;
                startPoint.x += radius;
                break;
            case Direction::DIR_TOP_TO_BOTTOM:
            case Direction::DIR_BOTTOM_TO_TOP:
                radius = (progressWidth_ + 1) >> 1;
                height -= radius << 1;
                startPoint.y += radius;
                break;
            default:
                GRAPHIC_LOGE("UIBoxProgress: GetBackgroundParam direction %d Err!\n", direction_);
                return;
        }
    }
}

void UIBoxProgress::DrawBackground(const Rect& invalidatedArea)
{
    Point startPoint;
    int16_t progressWidth;
    int16_t progressHeight;
    uint16_t radius;
    GetBackgroundParam(startPoint, progressWidth, progressHeight, radius, *backgroundStyle_);

    Rect coords(startPoint.x, startPoint.y, startPoint.x + progressWidth - 1, startPoint.y + progressHeight - 1);

    DrawValidRect(backgroundImage_, coords, invalidatedArea, *backgroundStyle_, radius);
}

void UIBoxProgress::DrawForeground(const Rect& invalidatedArea, Rect& coords)
{
    Point startPoint;
    int16_t progressWidth;
    int16_t progressHeight;
    uint16_t radius;
    GetBackgroundParam(startPoint, progressWidth, progressHeight, radius, *foregroundStyle_);
    int16_t length;

    switch (direction_) {
        case Direction::DIR_LEFT_TO_RIGHT: {
            length = GetCurrentPos(progressWidth - 1);
            coords.SetRect(startPoint.x, startPoint.y, startPoint.x + length, startPoint.y + progressHeight - 1);
            break;
        }
        case Direction::DIR_RIGHT_TO_LEFT: {
            length = GetCurrentPos(progressWidth - 1);
            coords.SetRect(startPoint.x + progressWidth - 1 - length,
                startPoint.y, startPoint.x + progressWidth - 1, startPoint.y + progressHeight - 1);
            break;
        }
        case Direction::DIR_TOP_TO_BOTTOM: {
            length = GetCurrentPos(progressHeight - 1);
            coords.SetRect(startPoint.x, startPoint.y, startPoint.x + progressWidth - 1, startPoint.y + length);
            break;
        }
        case Direction::DIR_BOTTOM_TO_TOP: {
            length = GetCurrentPos(progressHeight - 1);
            coords.SetRect(startPoint.x, startPoint.y + progressHeight - 1 - length,
                startPoint.x + progressWidth - 1, startPoint.y + progressHeight - 1);
            break;
        }
        default: {
            GRAPHIC_LOGE("UIBoxProgress: DrawForeground direction %d Err!\n", direction_);
            return;
        }
    }

    DrawValidRect(foregroundImage_, coords, invalidatedArea, *foregroundStyle_, radius);
}

void UIBoxProgress::OnDraw(const Rect& invalidatedArea)
{
    DrawRect::Draw(GetRect(), invalidatedArea, *style_);
    Rect trunc(invalidatedArea);
    if (trunc.Intersect(trunc, GetContentRect())) {
        if (enableBackground_) {
            DrawBackground(trunc);
        }

        if (lastValue_ - rangeMin_ != 0 || foregroundStyle_->lineCap_ == CapType::CAP_ROUND) {
            Rect coords;
            DrawForeground(trunc, coords);
        }
    }
}
} // namespace OHOS