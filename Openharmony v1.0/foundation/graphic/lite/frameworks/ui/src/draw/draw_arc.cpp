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

#include "draw/draw_arc.h"
#include "common/image.h"
#include "graphic_math.h"

namespace OHOS {
#define IS_IN_DEGREERANE(d, s, e) ((s) <= (e)) ? (((d) >= (s)) && ((d) <= (e))) : (((d) >= (s)) || ((d) <= (e)))

void DrawArc::DrawImg(const Point& imgPos,
                      Rect& area,
                      const Rect& invalidatedArea,
                      const Style& style,
                      uint8_t opaScale,
                      const Image* image)
{
    if (image == nullptr) {
        return;
    }
    ImageHeader header = {0};
    image->GetHeader(header);

    Rect cordsTmp;
    cordsTmp.SetPosition(imgPos.x, imgPos.y);
    cordsTmp.SetHeight(header.height);
    cordsTmp.SetWidth(header.width);
    if (area.Intersect(area, invalidatedArea)) {
        image->DrawImage(cordsTmp, area, style, opaScale);
    }
}

void DrawArc::DrawVerLine(const Point& begin,
                          const Point& imgPos,
                          const Rect& mask,
                          int16_t len,
                          const Style& style,
                          uint8_t opaScale,
                          const Image* image)
{
    Rect rect(begin.x, begin.y, begin.x, begin.y + len);
    if (image != nullptr && image->GetSrcType() != IMG_SRC_UNKNOWN) {
        DrawImg(imgPos, rect, mask, style, opaScale, image);
    } else {
        DrawUtils::GetInstance()->DrawColorArea(rect, mask, style.lineColor_, opaScale);
    }
}

void DrawArc::DrawHorLine(const Point& begin,
                          const Point& imgPos,
                          const Rect& mask,
                          int16_t len,
                          const Style& style,
                          uint8_t opaScale,
                          const Image* image)
{
    if (image != nullptr && image->GetSrcType() != IMG_SRC_UNKNOWN) {
        Rect rect(begin.x, begin.y, begin.x + len, begin.y);
        DrawImg(imgPos, rect, mask, style, opaScale, image);
    } else {
        if (len == 0) {
            DrawUtils::GetInstance()->DrawPixel(begin.x, begin.y, mask, style.lineColor_, opaScale);
        } else {
            Rect rect(begin.x, begin.y, begin.x + len, begin.y);
            DrawUtils::GetInstance()->DrawColorArea(rect, mask, style.lineColor_, opaScale);
        }
    }
}

int16_t DrawArc::GetDrawAngle(int16_t angle)
{
    if (angle < 0) {
        angle = (angle % CIRCLE_IN_DEGREE) + CIRCLE_IN_DEGREE;
    } else if (angle > CIRCLE_IN_DEGREE) {
        angle = angle % CIRCLE_IN_DEGREE;
    }
    return angle;
}

void DrawArc::GetDrawRange(int16_t& start, int16_t& end)
{
    int16_t tempAngle = GetDrawAngle(start);
    if (start == end) {
        start = tempAngle;
        end = tempAngle;
    } else if (end - start >= CIRCLE_IN_DEGREE) {
        // draw circle
        start = 0;
        end = CIRCLE_IN_DEGREE;
    } else {
        start = tempAngle;
        end = GetDrawAngle(end);
    }
}

uint16_t DrawArc::CalculateTanDegree(uint16_t x, uint16_t y)
{
    uint16_t degree = FastAtan2(x, y);
    if (degree == QUARTER_IN_DEGREE && y != 0) {
        degree--;
    }
    if (degree == 0 && x != 0) {
        degree++;
    }
    return degree;
}

void DrawArc::DrawCircleNoEndpoint(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opa, bool anti)
{
    DrawAxisLine(arcInfo, mask, style, opa);

    int16_t yStart = mask.GetTop() - arcInfo.center.y;
    int16_t yEnd = mask.GetBottom() - arcInfo.center.y;
    if (yStart >= 0 && yEnd >= 0) {
        int16_t tmp = yStart;
        yStart = -yEnd;
        yEnd = -tmp;
    } else if (yStart < 0 && yEnd > 0) {
        yStart = MATH_MIN(yStart, -yEnd);
        yEnd = -1;
    }
    yStart = MATH_MAX(yStart, -outRadius_);
    yEnd = MATH_MIN(yEnd, -1);

    int16_t xi;
    int16_t xLineStart = -outRadius_;
    int16_t xLineStart2 = xLineStart - 1;
    int16_t xLineStart3 = COORD_MIN;

    for (y_ = yEnd; y_ >= yStart; y_--) {
        ySqr_ = static_cast<int32_t>(y_) * y_;
        bool isSetStartPot = false;
        for (xi = xLineStart2; xi < 0; xi++) {
            uint32_t currentSqr = static_cast<int32_t>(xi) * xi + ySqr_;
            if (currentSqr > outRadiusSqr_) {
                continue;
            }
            if (!isSetStartPot) {
                xLineStart2 = xi;
                lineStart_ = xi;
                if (xLineStart3 != COORD_MIN) {
                    xi = xLineStart3;
                }
                isSetStartPot = true;
            }
            if (y_ <= -inRadius_) {
                lineEnd_ = -1;
                xi = -1;
                break;
            }
            if (currentSqr < inRadiusSqr_) {
                xLineStart3 = xi - 1;
                lineEnd_ = xi - 1;
                break;
            }
        }
        if (!isSetStartPot) {
            continue;
        }
#if ENABLE_ANTIALIAS
        if (anti) {
            DrawLineAnti(arcInfo, mask, style, opa);
        }
#endif
        DrawLineWithDegree(arcInfo, -lineEnd_, -lineStart_, y_, mask, style, opa, ARC_QUADRANT_ONE);

        DrawLineWithDegree(arcInfo, -lineEnd_, -lineStart_, -y_, mask, style, opa, ARC_QUADRANT_TWO);

        DrawLineWithDegree(arcInfo, lineStart_, lineEnd_, -y_, mask, style, opa, ARC_QUADRANT_THREE);

        DrawLineWithDegree(arcInfo, lineStart_, lineEnd_, y_, mask, style, opa, ARC_QUADRANT_FOUR);
    }
}

void DrawArc::DrawAxisLine(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opa)
{
    int16_t lineWidth = 0;
    int16_t outRadius = outRadius_ - 1;
    int16_t inRadius = inRadius_;
    if (inRadius <= 0) {
        inRadius = 1;
        DrawHorLine(arcInfo.center, arcInfo.imgPos, mask, 0, style, opa, arcInfo.imgSrc);
    }
    lineWidth = outRadius - inRadius;

    if (isCircle_ || (IS_IN_DEGREERANE(THREE_QUARTER_IN_DEGREE, arcInfo.startAngle, arcInfo.endAngle))) {
        DrawHorLine(Point{static_cast<int16_t>(arcInfo.center.x - outRadius), arcInfo.center.y}, arcInfo.imgPos, mask,
                    lineWidth, style, opa, arcInfo.imgSrc);
    }

    if (isCircle_ || (IS_IN_DEGREERANE(QUARTER_IN_DEGREE, arcInfo.startAngle, arcInfo.endAngle))) {
        DrawHorLine(Point{static_cast<int16_t>(arcInfo.center.x + inRadius), arcInfo.center.y}, arcInfo.imgPos, mask,
                    lineWidth, style, opa, arcInfo.imgSrc);
    }

    if (isCircle_ || (IS_IN_DEGREERANE(0, arcInfo.startAngle, arcInfo.endAngle))) {
        DrawVerLine(Point{arcInfo.center.x, static_cast<int16_t>(arcInfo.center.y - outRadius)}, arcInfo.imgPos, mask,
                    lineWidth, style, opa, arcInfo.imgSrc);
    }

    if (isCircle_ || (IS_IN_DEGREERANE(SEMICIRCLE_IN_DEGREE, arcInfo.startAngle, arcInfo.endAngle))) {
        DrawVerLine(Point{arcInfo.center.x, static_cast<int16_t>(arcInfo.center.y + inRadius)}, arcInfo.imgPos, mask,
                    lineWidth, style, opa, arcInfo.imgSrc);
    }
}

void DrawArc::DrawLineWithDegree(ArcInfo& arcInfo,
                                 int16_t start,
                                 int16_t end,
                                 int16_t y,
                                 const Rect& mask,
                                 const Style& style,
                                 uint8_t opaScale,
                                 uint8_t quadrant)
{
    if (isCircle_) {
        DrawHorLine(Point{static_cast<int16_t>(arcInfo.center.x + start), static_cast<int16_t>(arcInfo.center.y + y)},
                    arcInfo.imgPos, mask, end - start, style, opaScale, arcInfo.imgSrc);
        return;
    }
    uint16_t degreeStart = GetDegreeInQuadrant(CalculateTanDegree(MATH_ABS(start), MATH_ABS(y)), quadrant);
    uint16_t degreeEnd = GetDegreeInQuadrant(CalculateTanDegree(MATH_ABS(end), MATH_ABS(y)), quadrant);
    if (degreeStart > degreeEnd) {
        uint16_t tmp = degreeStart;
        degreeStart = degreeEnd;
        degreeEnd = tmp;
    }

    int16_t lineDegreeRet = GetDegreeRangeIntersectState(degreeStart, degreeEnd, arcInfo.startAngle, arcInfo.endAngle);
    int16_t drawEnd = 0;
    switch (lineDegreeRet) {
        case OUT_DEGREE_RANG:
            return;
        case IN_DEGREE_RANG:
            DrawHorLine(
                Point{static_cast<int16_t>(arcInfo.center.x + start), static_cast<int16_t>(arcInfo.center.y + y)},
                arcInfo.imgPos, mask, end - start, style, opaScale, arcInfo.imgSrc);
            return;
        case INTERSECT:
            DrawLineWithDegreeInner(arcInfo, start, end, y, mask, style, opaScale, quadrant);
            return;
        case DOUBLE_INTERSECT:
            drawEnd = DrawLineWithDegreeInner(arcInfo, start, end, y, mask, style, opaScale, quadrant);
            DrawLineWithDegreeInner(arcInfo, drawEnd + 1, end, y, mask, style, opaScale, quadrant);
        default:
            return;
    }
}

int16_t DrawArc::DrawLineWithDegreeInner(ArcInfo& arcInfo,
                                         int16_t start,
                                         int16_t end,
                                         int16_t y,
                                         const Rect& mask,
                                         const Style& style,
                                         uint8_t opaScale,
                                         uint8_t quadrant)
{
    int16_t drawStart = COORD_MIN;
    int16_t drawEnd = COORD_MIN;
    for (int16_t xi = start; xi <= end; xi++) {
        uint16_t degreeBase = CalculateTanDegree(MATH_ABS(xi), MATH_ABS(y));
        uint16_t degree = GetDegreeInQuadrant(degreeBase, quadrant);
        if (IS_IN_DEGREERANE(degree, arcInfo.startAngle, arcInfo.endAngle)) {
            if (drawStart == COORD_MIN) {
                drawStart = xi;
            }
        } else {
            if (drawStart != COORD_MIN && drawEnd == COORD_MIN) {
                drawEnd = xi - 1;
                break;
            }
        }
    }
    if (drawEnd == COORD_MIN) {
        drawEnd = end;
    }
    if (drawStart != COORD_MIN && drawEnd != COORD_MIN) {
        DrawHorLine(
            Point{static_cast<int16_t>(arcInfo.center.x + drawStart), static_cast<int16_t>(arcInfo.center.y + y)},
            arcInfo.imgPos, mask, drawEnd - drawStart, style, opaScale, arcInfo.imgSrc);
    }
    return drawEnd;
}

#if ENABLE_ANTIALIAS
void DrawArc::DrawLineAnti(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opa)
{
    outAntiStart_ = lineStart_;
    outAntiEnd_ = lineStart_;
    inAntiStart_ = lineEnd_ + 1;
    inAntiEnd_ = COORD_MIN;

    for (int16_t xAnti = lineStart_; xAnti <= lineEnd_; xAnti++) {
        uint32_t currentSqr = static_cast<int32_t>(xAnti) * xAnti + ySqr_;
        if (currentSqr <= antiOutRadiusSqr_ || xAnti == lineEnd_) {
            lineStart_ = xAnti;
            outAntiEnd_ = xAnti - 1;
            break;
        }
    }

    for (int16_t xAnti = lineEnd_ + 1; xAnti <= -1; xAnti++) {
        uint32_t currentSqr = static_cast<int32_t>(xAnti) * xAnti + ySqr_;
        if (currentSqr <= antiInRadiusSqr_ || xAnti == -1) {
            inAntiEnd_ = xAnti;
            break;
        }
    }

    for (int16_t xAnti = outAntiStart_; xAnti <= outAntiEnd_; xAnti++) {
        uint32_t currentSqr = static_cast<int32_t>(xAnti) * xAnti + ySqr_;
        uint8_t antiOpa =
            (((static_cast<uint64_t>(outRadius_) << 1) - 1 - (currentSqr - antiOutRadiusSqr_)) * OPA_OPAQUE) /
            ((outRadius_ << 1) - 1);
        antiOpa = (opa == OPA_OPAQUE) ? antiOpa : (static_cast<uint16_t>(antiOpa) * opa) >> SHIFT_8;
        DrawPointAnti(arcInfo, xAnti, mask, style, antiOpa);
    }

    for (int16_t xAnti = inAntiStart_; xAnti <= inAntiEnd_; xAnti++) {
        uint32_t currentSqr = static_cast<int32_t>(xAnti) * xAnti + ySqr_;
        if (currentSqr <= antiInRadiusSqr_) {
            break;
        }
        uint8_t antiOpa = (static_cast<uint64_t>(currentSqr - antiInRadiusSqr_) * OPA_OPAQUE) / ((inRadius_ << 1) - 1);
        antiOpa = (opa == OPA_OPAQUE) ? antiOpa : (static_cast<uint16_t>(antiOpa) * opa) >> SHIFT_8;
        DrawPointAnti(arcInfo, xAnti, mask, style, antiOpa);
    }
}

void DrawArc::DrawPointAnti(ArcInfo& arcInfo, int16_t x, const Rect& mask, const Style& style, uint8_t antiOpa)
{
    int16_t startX;
    int16_t starty;
    int16_t degreeBase = CalculateTanDegree(MATH_ABS(x), MATH_ABS(y_));
    if (isCircle_ || (IS_IN_DEGREERANE(CIRCLE_IN_DEGREE - degreeBase, arcInfo.startAngle, arcInfo.endAngle))) {
        startX = arcInfo.center.x + x;
        starty = arcInfo.center.y + y_;
        DrawHorLine(Point{startX, starty}, arcInfo.imgPos, mask, 0, style, antiOpa, arcInfo.imgSrc);
    }
    if (isCircle_ || (IS_IN_DEGREERANE(SEMICIRCLE_IN_DEGREE + degreeBase, arcInfo.startAngle, arcInfo.endAngle))) {
        startX = arcInfo.center.x + x;
        starty = arcInfo.center.y - y_;
        DrawHorLine(Point{startX, starty}, arcInfo.imgPos, mask, 0, style, antiOpa, arcInfo.imgSrc);
    }
    if (isCircle_ || (IS_IN_DEGREERANE(degreeBase, arcInfo.startAngle, arcInfo.endAngle))) {
        startX = arcInfo.center.x - x;
        starty = arcInfo.center.y + y_;
        DrawHorLine(Point{startX, starty}, arcInfo.imgPos, mask, 0, style, antiOpa, arcInfo.imgSrc);
    }
    if (isCircle_ || (IS_IN_DEGREERANE(SEMICIRCLE_IN_DEGREE - degreeBase, arcInfo.startAngle, arcInfo.endAngle))) {
        startX = arcInfo.center.x - x;
        starty = arcInfo.center.y - y_;
        DrawHorLine(Point{startX, starty}, arcInfo.imgPos, mask, 0, style, antiOpa, arcInfo.imgSrc);
    }
}
#endif

uint16_t DrawArc::GetDegreeInQuadrant(uint16_t degree, uint8_t quadrant)
{
    switch (quadrant) {
        case ARC_QUADRANT_ONE:
            return degree;
        case ARC_QUADRANT_TWO:
            return SEMICIRCLE_IN_DEGREE - degree;
        case ARC_QUADRANT_THREE:
            return SEMICIRCLE_IN_DEGREE + degree;
        case ARC_QUADRANT_FOUR:
            return CIRCLE_IN_DEGREE - degree;
        default:
            return degree;
    }
}

void DrawArc::Draw(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opaScale, uint8_t cap)
{
    OpacityType opa = (opaScale == OPA_OPAQUE) ? style.lineOpa_
                                              : ((static_cast<uint16_t>(style.lineOpa_) * opaScale) >> SHIFT_8);
    if (opa == OPA_TRANSPARENT || style.lineWidth_ < 1) {
        return;
    }

    SetArcInfo(arcInfo, style);

    if (arcInfo.imgSrc != nullptr && arcInfo.imgSrc->GetSrcType() != IMG_SRC_UNKNOWN) {
        DrawCircleNoEndpoint(arcInfo, mask, style, opa, false);
    } else {
        DrawCircleNoEndpoint(arcInfo, mask, style, opa, true);
    }

    if (!isCircle_ && cap == CapType::CAP_ROUND) {
        int16_t lineWidth = style.lineWidth_;
        if (lineWidth > arcInfo.radius) {
            lineWidth = arcInfo.radius;
        }

        ArcInfo endArcInfo = arcInfo;
        endArcInfo.startAngle = 0;
        endArcInfo.endAngle = CIRCLE_IN_DEGREE;

        int16_t outRadius = arcInfo.radius - 1;
        lineWidth--;
        /* the arc radius of the round cap should be half the line width */
        endArcInfo.radius = (static_cast<uint16_t>(lineWidth + 1) >> 1) + 1;

        /* 0.5: round up */
        float temp = (outRadius - endArcInfo.radius + 1) * Sin(arcInfo.startAngle);
        int16_t startCapX = static_cast<int16_t>((temp > 0) ? (temp + 0.5f) : (temp - 0.5f));

        temp = (outRadius - endArcInfo.radius + 1) * Sin(QUARTER_IN_DEGREE - arcInfo.startAngle);
        int16_t startCapY = static_cast<int16_t>((temp > 0) ? (temp + 0.5f) : (temp - 0.5f));

        endArcInfo.center.x += startCapX;
        endArcInfo.center.y -= startCapY;
        SetArcInfo(endArcInfo, style);
        DrawCircleNoEndpoint(endArcInfo, mask, style, opa, true);

        temp = (outRadius - endArcInfo.radius + 1) * Sin(arcInfo.endAngle);
        int16_t endCapX = static_cast<int16_t>((temp > 0) ? (temp + 0.5f) : (temp - 0.5f));

        temp = (outRadius - endArcInfo.radius + 1) * Sin(QUARTER_IN_DEGREE - arcInfo.endAngle);
        int16_t endCapY = static_cast<int16_t>((temp > 0) ? (temp + 0.5f) : (temp - 0.5f));

        endArcInfo.center = arcInfo.center;
        endArcInfo.center.x += endCapX;
        endArcInfo.center.y -= endCapY;
        SetArcInfo(endArcInfo, style);
        DrawCircleNoEndpoint(endArcInfo, mask, style, opa, true);
    }
}

int16_t DrawArc::GetDegreeRangeIntersectState(uint16_t degreeStart, uint16_t degreeEnd, uint16_t start, uint16_t end)
{
    if (start <= end) {
        if (degreeStart >= start && degreeStart <= end && degreeEnd >= start && degreeEnd <= end) {
            return IN_DEGREE_RANG;
        } else if (degreeEnd < start || degreeStart > end) {
            return OUT_DEGREE_RANG;
        } else {
            return INTERSECT;
        }
    } else {
        if ((degreeStart >= start && degreeEnd >= start) || (degreeStart <= end && degreeEnd <= end)) {
            return IN_DEGREE_RANG;
        } else if (degreeStart > end && degreeEnd < start) {
            return OUT_DEGREE_RANG;
        } else if (degreeStart <= end && degreeEnd >= start) {
            return DOUBLE_INTERSECT;
        } else {
            return INTERSECT;
        }
    }
}
void DrawArc::SetArcInfo(ArcInfo& arcInfo, const Style& style)
{
    outRadius_ = arcInfo.radius;
    inRadius_ = outRadius_ - style.lineWidth_;
    if (inRadius_ < 0) {
        inRadius_ = 0;
    }
    outRadiusSqr_ = outRadius_ * outRadius_;
    inRadiusSqr_ = inRadius_ * inRadius_;

    if (arcInfo.startAngle == 0 && arcInfo.endAngle == CIRCLE_IN_DEGREE) {
        isCircle_ = true;
    } else {
        isCircle_ = false;
    }
#if ENABLE_ANTIALIAS
    antiOutRadiusSqr_ = (outRadius_ - 1) * (outRadius_ - 1);
    if (inRadius_ == 0) {
        antiInRadiusSqr_ = 0;
    } else {
        antiInRadiusSqr_ = (inRadius_ - 1) * (inRadius_ - 1);
    }
#endif
}
} // namespace OHOS