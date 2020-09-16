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

#include "draw/draw_rect.h"
#include "draw/draw_arc.h"
#include "draw/draw_utils.h"
#include "graphic_log.h"
#include "graphic_math.h"
#include "style.h"

namespace OHOS {
void DrawRect::Draw(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    if (rect.GetWidth() <= 0 || rect.GetHeight() <= 0) {
        GRAPHIC_LOGD("DrawRect::Draw width or height is zero\n");
        return;
    }

    /**
     * no border
     *      radius = 0 (1/4)
     *      radius > 0 (2/4)
     *          rect width > rect height
     *              radius >= rect height / 2
     *              radius < rect height / 2
     *          rect width <= rect height
     *              radius >= rect width / 2
     *              radius < rect width / 2
     * have border
     *      radius = 0 (3/4)
     *      radius > 0 (4/4)
     *          radius < border width (4.1/4)
     *          radius = border width (4.2/4)
     *          radius > border width (4.3/4)
     *             rect width <= rect height
     *                  radius >= border width + rect height / 2
     *                  radius < border width + rect height / 2
     *             rect width > rect height
     *                  radius >= border width + rect height / 2
     *                  radius < border width + rect height / 2
     */
    if (style.borderWidth_ == 0) {
        if (style.borderRadius_ == 0) {
            /* no border no radius (1/4) */
            DrawUtils::GetInstance()->DrawColorArea(rect, dirtyRect, style.bgColor_, style.bgOpa_);
            return;
        } else {
            /* [2/4] no border with radius (2/4) */
            DrawRectRadiusWithoutBorder(rect, dirtyRect, style);
        }
    } else {
        if (style.borderRadius_ == 0) {
            /* [3/4] border without radius (3/4) */
            DrawRectBorderWithoutRadius(rect, dirtyRect, style);
        } else if (style.borderRadius_ < style.borderWidth_) {
            /* [4.1/4] radius < border width */
            DrawRectRadiusSmallThanBorder(rect, dirtyRect, style);
        } else if (style.borderRadius_ == style.borderWidth_) {
            /* [4.2/4] radius = border width */
            DrawRectRadiusEqualBorder(rect, dirtyRect, style);
        } else {
            /* [4.3/4] radius >= border width + rect height_or_width / 2 */
            DrawRectRadiusBiggerThanBorder(rect, dirtyRect, style);
        }
    }
}

void DrawRect::DrawRectRadiusWithoutBorder(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    if (rect.GetWidth() > rect.GetHeight() && style.borderRadius_ >= rect.GetHeight() / 2) {
        DrawRectRadiusWithoutBorderCon1(rect, dirtyRect, style);
    } else if (rect.GetWidth() < rect.GetHeight() && style.borderRadius_ >= rect.GetWidth() / 2) {
        DrawRectRadiusWithoutBorderCon2(rect, dirtyRect, style);
    } else if (rect.GetWidth() == rect.GetHeight() && style.borderRadius_ >= rect.GetWidth() / 2) {
        DrawRectRadiusWithoutBorderCon3(rect, dirtyRect, style);
    } else {
        DrawRectRadiusWithoutBorderCon4(rect, dirtyRect, style);
    }
}

void DrawRect::DrawRectRadiusWithoutBorderCon1(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = rect.GetHeight() / 2;
    int16_t col2X = rect.GetLeft() + radius;
    int16_t col3X = rect.GetRight() - radius;

    int16_t row1Y = rect.GetTop();
    int16_t row2Y = rect.GetTop() + radius;
    int16_t row3Y = rect.GetBottom();

    Style arcStyle = style;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;
    // draw left sector
    ArcInfo arcInfo;
    arcInfo.center = {col2X, row2Y};
    arcInfo.radius = radius;
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 360;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw right sector
    arcInfo.center = {col3X, row2Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw top rectangle
    Rect topRect(col2X, row1Y, col3X - 1, row2Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(topRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // draw bottom rectangle
    Rect bottomRect(col2X + 1, row2Y, col3X - 1, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomRect, dirtyRect, style.bgColor_, style.bgOpa_);
}

void DrawRect::DrawRectRadiusWithoutBorderCon2(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = rect.GetWidth() / 2;
    int16_t col1X = rect.GetLeft();
    int16_t col2X = rect.GetLeft() + radius;
    int16_t col3X = rect.GetRight();

    int16_t row2Y = rect.GetTop() + radius;
    int16_t row3Y = rect.GetBottom() - radius;

    Style arcStyle = style;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;
    // draw top sector
    ArcInfo arcInfo;
    arcInfo.center = {col2X, row2Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 90;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw bottom sector
    arcInfo.center = {col2X, row3Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw middle rectangle
    Rect middleRect(col1X, row2Y + 1, col3X, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(middleRect, dirtyRect, style.bgColor_, style.bgOpa_);
}

void DrawRect::DrawRectRadiusWithoutBorderCon3(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = rect.GetWidth() / 2;
    int16_t col1X = rect.GetLeft() + radius;
    int16_t row1Y = rect.GetTop() + radius;

    Style arcStyle = style;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;
    // draw circle
    ArcInfo arcInfo;
    arcInfo.center = {col1X, row1Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
}

void DrawRect::DrawRectRadiusWithoutBorderCon4(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = style.borderRadius_;
    int16_t col1X = rect.GetLeft();
    int16_t col2X = rect.GetLeft() + radius;
    int16_t col3X = rect.GetRight() - radius;
    int16_t col4X = rect.GetRight();

    int16_t row1Y = rect.GetTop();
    int16_t row2Y = rect.GetTop() + radius;
    int16_t row3Y = rect.GetBottom() - radius;
    int16_t row4Y = rect.GetBottom();

    // draw top rectangle
    Rect topRect(col2X, row1Y, col3X - 1, row2Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(topRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // draw middle rectangle
    Rect middleRect(col1X + 1, row2Y, col4X - 1, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(middleRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // draw bottom rectangle
    Rect bottomRect(col2X + 1, row3Y + 1, col3X - 1, row4Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomRect, dirtyRect, style.bgColor_, style.bgOpa_);

    Style arcStyle = style;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;
    // top left sector
    ArcInfo arcInfo;
    arcInfo.center.x = col2X;
    arcInfo.center.y = row2Y - 1;
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // top right sector
    arcInfo.center.x = col3X;
    arcInfo.center.y = row2Y - 1;
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 90;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // bottom left sector
    arcInfo.center.x = col2X;
    arcInfo.center.y = row3Y + 1;
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // bottom right sector
    arcInfo.center.x = col3X;
    arcInfo.center.y = row3Y + 1;
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
}

void DrawRect::DrawRectBorderWithoutRadius(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t col1X = rect.GetLeft();
    int16_t col2X = rect.GetLeft() + style.borderWidth_;
    int16_t col3X = rect.GetRight() - style.borderWidth_;
    int16_t col4X = rect.GetRight();

    int16_t row1Y = rect.GetTop();
    int16_t row2Y = rect.GetTop() + style.borderWidth_;
    int16_t row3Y = rect.GetBottom() - style.borderWidth_;
    int16_t row4Y = rect.GetBottom();

    // draw top border
    Rect topRect(col1X, row1Y, col4X, row2Y);
    DrawUtils::GetInstance()->DrawColorArea(topRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw left border
    Rect leftRect(col1X, row2Y + 1, col2X, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(leftRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw middle rectangle
    Rect middleRect(col2X + 1, row2Y + 1, col3X, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(middleRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // draw right border
    Rect rightRect(col3X + 1, row2Y + 1, col4X, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(rightRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw bottom border
    Rect bottomRect(col1X, row3Y + 1, col4X, row4Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomRect, dirtyRect, style.borderColor_, style.borderOpa_);
}

void DrawRect::DrawRectRadiusEqualBorder(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t col1X = rect.GetLeft();
    int16_t col2X = rect.GetLeft() + style.borderRadius_;
    int16_t col3X = rect.GetRight() - style.borderRadius_;
    int16_t col4X = rect.GetRight();

    int16_t row1Y = rect.GetTop();
    int16_t row2Y = rect.GetTop() + style.borderRadius_;
    int16_t row3Y = rect.GetBottom() - style.borderRadius_;
    int16_t row4Y = rect.GetBottom();

    Style arcStyle = style;
    arcStyle.lineWidth_ = style.borderWidth_;
    arcStyle.lineColor_ = style.borderColor_;
    arcStyle.lineOpa_ = style.borderOpa_;
    // draw top left sector in border
    ArcInfo arcInfo;
    arcInfo.center = {col2X, row2Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 360;
    arcInfo.radius = style.borderRadius_;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw top right sector in border
    arcInfo.center = {col3X, row2Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 90;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw bottom left sector in border
    arcInfo.center = {col2X, row3Y};
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw bottom right sector in border
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw top rectangle in border
    Rect topRect(col2X, row1Y, col3X - 1, row2Y);
    DrawUtils::GetInstance()->DrawColorArea(topRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw left rectangle in border
    Rect leftRect(col1X, row2Y + 1, col2X - 1, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(leftRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw middle rectangle
    Rect middleRect(col2X, row2Y + 1, col3X - 1, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(middleRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // draw right rectangle in border
    Rect rightRect(col3X, row2Y + 1, col4X, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(rightRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw bottom rectangle in border
    Rect bottomRect(col2X + 1, row3Y, col3X - 1, row4Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomRect, dirtyRect, style.borderColor_, style.borderOpa_);
}

void DrawRect::DrawRectRadiusSmallThanBorder(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radiusCol1X = rect.GetLeft();
    int16_t radiusCol2X = rect.GetLeft() + style.borderRadius_;
    int16_t radiusCol3X = rect.GetRight() - style.borderRadius_;
    int16_t radiusCol4X = rect.GetRight();

    int16_t radiusRow1Y = rect.GetTop();
    int16_t radiusRow2Y = rect.GetTop() + style.borderRadius_;
    int16_t radiusRow3Y = rect.GetBottom() - style.borderRadius_;
    int16_t radiusRow4Y = rect.GetBottom();

    int16_t rectCol1X = radiusCol1X;
    int16_t rectCol2X = rect.GetLeft() + style.borderWidth_;
    int16_t rectCol3X = rect.GetRight() - style.borderWidth_;
    int16_t rectCol4X = radiusCol4X;

    int16_t rectRow1Y = radiusRow2Y;
    int16_t rectRow2Y = rect.GetTop() + style.borderWidth_;
    int16_t rectRow3Y = rect.GetBottom() - style.borderWidth_;

    Style arcStyle = style;
    arcStyle.lineWidth_ = style.borderWidth_;
    arcStyle.lineColor_ = style.borderColor_;
    arcStyle.lineOpa_ = style.borderOpa_;
    // draw top left sector in border
    ArcInfo arcInfo;
    arcInfo.center = {radiusCol2X, radiusRow2Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 360;
    arcInfo.radius = style.borderRadius_;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw top right sector in border
    arcInfo.center = {radiusCol3X, radiusRow2Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 90;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw bottom left sector in border
    arcInfo.center = {radiusCol2X, radiusRow3Y};
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw bottom right sector in border
    arcInfo.center = {radiusCol3X, radiusRow3Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // draw top rectangle in border
    Rect topRect(radiusCol2X, radiusRow1Y, radiusCol3X - 1, radiusRow2Y);
    DrawUtils::GetInstance()->DrawColorArea(topRect, dirtyRect, style.borderColor_, style.borderOpa_);
    Rect topRect2(rectCol1X, rectRow1Y + 1, rectCol4X, rectRow2Y);
    DrawUtils::GetInstance()->DrawColorArea(topRect2, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw left rectangle in border
    Rect leftRect(rectCol1X, rectRow2Y + 1, rectCol2X, rectRow3Y);
    DrawUtils::GetInstance()->DrawColorArea(leftRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw middle rectangle
    Rect middleRect(rectCol2X + 1, rectRow2Y + 1, rectCol3X - 1, rectRow3Y);
    DrawUtils::GetInstance()->DrawColorArea(middleRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // draw right rectangle in border
    Rect rightRect(rectCol3X, rectRow2Y + 1, rectCol4X, rectRow3Y);
    DrawUtils::GetInstance()->DrawColorArea(rightRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // draw bottom rectangle in border
    Rect bottomRect(radiusCol2X + 1, radiusRow3Y, radiusCol3X - 1, radiusRow4Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomRect, dirtyRect, style.borderColor_, style.borderOpa_);
    Rect bottomRect2(rectCol1X, rectRow3Y + 1, rectCol4X, radiusRow3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(bottomRect2, dirtyRect, style.borderColor_, style.borderOpa_);
}

void DrawRect::DrawRectRadiusBiggerThanBorder(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    if (rect.GetWidth() > rect.GetHeight() && style.borderRadius_ >= rect.GetHeight() / 2) {
        DrawRectRadiusBiggerThanBorderCon1(rect, dirtyRect, style);
    } else if (rect.GetWidth() < rect.GetHeight() && style.borderRadius_ >= rect.GetWidth() / 2) {
        DrawRectRadiusBiggerThanBorderCon2(rect, dirtyRect, style);
    } else if (rect.GetWidth() == rect.GetHeight() && style.borderRadius_ >= rect.GetWidth() / 2) {
        DrawRectRadiusBiggerThanBorderCon3(rect, dirtyRect, style);
    } else {
        DrawRectRadiusBiggerThanBorderCon4(rect, dirtyRect, style);
    }
}

void DrawRect::DrawRectRadiusBiggerThanBorderCon1(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = rect.GetHeight() / 2;
    int16_t borderWidth = style.borderWidth_;
    int16_t col2X = rect.GetLeft() + radius;
    int16_t col3X = rect.GetRight() - radius;

    int16_t row1Y = rect.GetTop();
    int16_t row2Y = rect.GetTop() + borderWidth;
    int16_t row3Y = rect.GetTop() + radius;
    int16_t row4Y = rect.GetBottom() - borderWidth;
    int16_t row5Y = rect.GetBottom();

    Style arcStyle = style;
    arcStyle.lineWidth_ = borderWidth;
    arcStyle.lineColor_ = style.borderColor_;
    arcStyle.lineOpa_ = style.borderOpa_;
    // draw left arc in border
    ArcInfo arcInfo;
    arcInfo.center = {col2X, row3Y};
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw right arc in border
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    radius = radius - borderWidth;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;

    // draw left sector in rectangle
    arcInfo.center = {col2X, row3Y};
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw right sector in rectangle
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // top rectangle in border
    Rect topBorderRect(col2X, row1Y, col3X - 1, row2Y);
    DrawUtils::GetInstance()->DrawColorArea(topBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);
    // middle rectangle inner
    Rect middleInnerRect(col2X, row2Y + 1, col3X - 1, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(middleInnerRect, dirtyRect, style.bgColor_, style.bgOpa_);
    Rect middleInnerRect2(col2X + 1, row3Y + 1, col3X - 1, row4Y);
    DrawUtils::GetInstance()->DrawColorArea(middleInnerRect2, dirtyRect, style.bgColor_, style.bgOpa_);

    // bottom rectangle in border
    Rect bottomBorderRect(col2X + 1, row4Y + 1, col3X - 1, row5Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);
}

void DrawRect::DrawRectRadiusBiggerThanBorderCon2(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = rect.GetWidth() / 2;
    int16_t borderWidth = style.borderWidth_;
    int16_t col1X = rect.GetLeft();
    int16_t col2X = rect.GetLeft() + borderWidth;
    int16_t col3X = rect.GetLeft() + radius;
    int16_t col4X = rect.GetRight() - borderWidth;
    int16_t col5X = rect.GetRight();

    int16_t row2Y = rect.GetTop() + radius;
    int16_t row3Y = rect.GetBottom() - radius;

    Style arcStyle = style;
    arcStyle.lineWidth_ = borderWidth;
    arcStyle.lineColor_ = style.borderColor_;
    arcStyle.lineOpa_ = style.borderOpa_;
    // draw top arc in border
    ArcInfo arcInfo;
    arcInfo.center = {col3X, row2Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 90;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw bottom arc in border
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    radius = radius - borderWidth;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;

    // draw top sector in rectangle
    arcInfo.center = {col3X, row2Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 90;
    arcInfo.radius = radius;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw bottom sector in rectangle
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // left rectangle in border
    Rect topBorderRect(col1X, row2Y + 1, col2X, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(topBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);
    // middle rectangle inner
    Rect middleInnerRect(col2X + 1, row2Y + 1, col4X, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(middleInnerRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // right rectangle in border
    Rect bottomBorderRect(col4X + 1, row2Y + 1, col5X, row3Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(bottomBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);
}

void DrawRect::DrawRectRadiusBiggerThanBorderCon3(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = rect.GetWidth() / 2;
    int16_t borderWidth = style.borderWidth_;
    int16_t col2X = rect.GetLeft() + radius;
    int16_t row2Y = rect.GetTop() + radius;

    Style arcStyle = style;
    arcStyle.lineWidth_ = borderWidth;
    arcStyle.lineColor_ = style.borderColor_;
    arcStyle.lineOpa_ = style.borderOpa_;
    // draw circle in border
    ArcInfo arcInfo;
    arcInfo.center = {col2X, row2Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    radius = radius - borderWidth;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;

    // draw circle in rectangle
    arcInfo.center = {col2X, row2Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
}

void DrawRect::DrawRectRadiusBiggerThanBorderCon4(const Rect& rect, const Rect& dirtyRect, const Style& style)
{
    int16_t radius = style.borderRadius_;
    int16_t borderWidth = style.borderWidth_;
    int16_t col1X = rect.GetLeft();
    int16_t col2X = rect.GetLeft() + borderWidth;
    int16_t col3X = rect.GetLeft() + radius;
    int16_t col4X = rect.GetRight() - radius;
    int16_t col5X = rect.GetRight() - borderWidth;
    int16_t col6X = rect.GetRight();

    int16_t row1Y = rect.GetTop();
    int16_t row2Y = rect.GetTop() + borderWidth;
    int16_t row3Y = rect.GetTop() + radius;
    int16_t row4Y = rect.GetBottom() - radius;
    int16_t row5Y = rect.GetBottom() - borderWidth;
    int16_t row6Y = rect.GetBottom();

    Style arcStyle = style;
    arcStyle.lineWidth_ = borderWidth;
    arcStyle.lineColor_ = style.borderColor_;
    arcStyle.lineOpa_ = style.borderOpa_;

    // draw top left arc in border
    ArcInfo arcInfo;
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    arcInfo.imgPos = {0, 0};
    arcInfo.imgSrc = nullptr;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw top right arc in border
    arcInfo.center = {col4X, row3Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 90;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw bottom left arc in border
    arcInfo.center = {col3X, row4Y};
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw bottom right arc in border
    arcInfo.center = {col4X, row4Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    radius = radius - borderWidth;
    arcStyle.lineWidth_ = radius;
    arcStyle.lineColor_ = style.bgColor_;
    arcStyle.lineOpa_ = style.bgOpa_;

    // draw top left sector in rectangle
    arcInfo.center = {col3X, row3Y};
    arcInfo.startAngle = 270;
    arcInfo.endAngle = 360;
    arcInfo.radius = radius;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw top right sector in rectangle
    arcInfo.center = {col4X, row3Y};
    arcInfo.startAngle = 0;
    arcInfo.endAngle = 90;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw bottom left sector in rectangle
    arcInfo.center = {col3X, row4Y};
    arcInfo.startAngle = 180;
    arcInfo.endAngle = 270;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);
    // draw bottom right sector in rectangle
    arcInfo.center = {col4X, row4Y};
    arcInfo.startAngle = 90;
    arcInfo.endAngle = 180;
    DrawArc::GetInstance()->Draw(arcInfo, dirtyRect, arcStyle, OPA_OPAQUE, CapType::CAP_NONE);

    // top rectangle in border
    Rect topBorderRect(col3X, row1Y, col4X - 1, row2Y);
    DrawUtils::GetInstance()->DrawColorArea(topBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // left rectangle in border
    Rect leftBorderRect(col1X, row3Y + 1, col2X, row4Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(leftBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // right rectangle in border
    Rect rightBorderRect(col5X, row3Y + 1, col6X, row4Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(rightBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // bottom rectangle in border
    Rect bottomBorderRect(col3X + 1, row5Y + 1, col4X - 1, row6Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(bottomBorderRect, dirtyRect, style.borderColor_, style.borderOpa_);

    // top rectangle inner
    Rect topInnerRect(col3X, row2Y + 1, col4X - 1, row3Y);
    DrawUtils::GetInstance()->DrawColorArea(topInnerRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // middle rectangle inner
    Rect middleInnerRect(col2X + 1, row3Y + 1, col5X - 1, row4Y - 1);
    DrawUtils::GetInstance()->DrawColorArea(middleInnerRect, dirtyRect, style.bgColor_, style.bgOpa_);

    // bottom rectangle inner
    Rect bottomInnerRect(col3X + 1, row4Y, col4X - 1, row5Y);
    DrawUtils::GetInstance()->DrawColorArea(bottomInnerRect, dirtyRect, style.bgColor_, style.bgOpa_);
}
} // namespace OHOS