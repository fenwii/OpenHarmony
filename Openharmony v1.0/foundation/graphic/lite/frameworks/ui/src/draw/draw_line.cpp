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

#include "draw/draw_line.h"
#include "draw/draw_utils.h"
#include "graphic_math.h"

namespace OHOS {
constexpr int16_t MAX_WIDTH = 100;

void DrawLine::Draw(const Point& start,
                    const Point& end,
                    const Rect& mask,
                    int16_t width,
                    const ColorType& color,
                    OpacityType opacity)
{
    if (width == 0 || opacity == OPA_TRANSPARENT) {
        return;
    }

    int16_t yTop;
    int16_t yBottom;

    if (start.y < end.y) {
        yTop = start.y - width / 2;  // 2: half
        yBottom = end.y + width / 2; // 2: half
    } else {
        yTop = end.y - width / 2;      // 2: half
        yBottom = start.y + width / 2; // 2: half
    }

    if (yBottom < mask.GetTop() || yTop > mask.GetBottom()) {
        return;
    }

    if (start.y == end.y) {
        DrawHorizontalLine(start, end, mask, width, color, opacity);
    } else if (start.x == end.x) {
        DrawVerticalLine(start, end, mask, width, color, opacity);
    } else {
        DrawObliqueLine(start, end, mask, width, color, opacity);
    }
}

void DrawLine::DrawVerticalLine(const Point& start,
                                const Point& end,
                                const Rect& mask,
                                int16_t width,
                                const ColorType& color,
                                OpacityType opacity)
{
    Rect rect;

    if (start.y < end.y) {
        rect.SetX(start.x - width / 2); // 2: half
        rect.SetY(start.y);
        rect.SetWidth(width);
        rect.SetHeight(end.y - start.y + 1);
    } else {
        rect.SetX(end.x - width / 2); // 2: half
        rect.SetY(end.y);
        rect.SetWidth(width);
        rect.SetHeight(start.y - end.y + 1);
    }

    DrawUtils::GetInstance()->DrawColorArea(rect, mask, color, opacity);
}

void DrawLine::DrawHorizontalLine(const Point& start,
                                  const Point& end,
                                  const Rect& mask,
                                  int16_t width,
                                  const ColorType& color,
                                  OpacityType opacity)
{
    Rect rect;

    if (start.x < end.x) {
        rect.SetX(start.x);
        rect.SetY(start.y - width / 2); // 2: half
        rect.SetWidth(end.x - start.x + 1);
        rect.SetHeight(width);
    } else {
        rect.SetX(end.x);
        rect.SetY(end.y - width / 2); // 2: half
        rect.SetWidth(start.x - end.x + 1);
        rect.SetHeight(width);
    }

    DrawUtils::GetInstance()->DrawColorArea(rect, mask, color, opacity);
}

void DrawLine::DrawObliqueLine(const Point& start,
                               const Point& end,
                               const Rect& mask,
                               int16_t width,
                               const ColorType& color,
                               OpacityType opacity)
{
    LineInfo mainLine;
    LineInit(mainLine, start, end);

    int16_t lineWidth = (width > MAX_WIDTH) ? MAX_WIDTH : width;
    Point normalVector[MAX_WIDTH];
    GenerateNormalVector(mainLine, lineWidth, normalVector, MAX_WIDTH);
    if (lineWidth <= 0) {
        return;
    }

    int16_t xCenter = normalVector[lineWidth - 1].x / 2; // 2: half
    int16_t yCenter = normalVector[lineWidth - 1].y / 2; // 2: half
    bool fillGaps = false;
    for (int16_t i = 0; i < lineWidth; i++) {
        if (i != 0) {
            fillGaps = true;
        }

        normalVector[i].x -= xCenter;
        normalVector[i].y -= yCenter;
        DrawBresenhamLine(mainLine, normalVector[i], fillGaps, mask, color, opacity);
    }
}

void DrawLine::DrawBresenhamLine(LineInfo& line,
                                 const Point& translate,
                                 bool fillGaps,
                                 const Rect& mask,
                                 const ColorType& color,
                                 OpacityType opacity)
{
    int16_t x = line.start.x + translate.x;
    int16_t y = line.start.y + translate.y;
    DrawUtils* utils = DrawUtils::GetInstance();
    if (line.hor) {
        int16_t p = line.twoDy - line.dx;
        for (int16_t i = 0; i <= line.dx; i++) {
            utils->DrawPixel(x, y, mask, color, opacity);
            x += line.sx;
            if (p >= 0) {
                if (fillGaps) {
                    utils->DrawPixel(x, y, mask, color, opacity);
                }
                y += line.sy;
                p = p - line.twoDx;
            }
            p = p + line.twoDy;
        }
    } else {
        int16_t p = line.twoDx - line.dy;
        for (int16_t i = 0; i <= line.dy; i++) {
            utils->DrawPixel(x, y, mask, color, opacity);
            y += line.sy;
            if (p >= 0) {
                if (fillGaps) {
                    utils->DrawPixel(x, y, mask, color, opacity);
                }
                x += line.sx;
                p = p - line.twoDy;
            }
            p = p + line.twoDx;
        }
    }
}

void DrawLine::GenerateNormalVector(LineInfo& mainLine, int16_t& lineWidth, Point* normalVector, int16_t maxLen)
{
    Point vectMain;
    Point vectNorm;
    vectMain.x = mainLine.end.x - mainLine.start.x;
    vectMain.y = mainLine.end.y - mainLine.start.y;

    /* If vectMain is in 1 and 3 quadrant or not */
    bool quadrant_1_3 = (vectMain.x > 0 && vectMain.y > 0) || (vectMain.x < 0 && vectMain.y < 0);

    if ((mainLine.hor && quadrant_1_3) || (!mainLine.hor && !quadrant_1_3)) {
        vectNorm.x = -vectMain.y;
        vectNorm.y = vectMain.x;
    } else {
        vectNorm.x = vectMain.y;
        vectNorm.y = -vectMain.x;
    }

    LineInfo normalVectorLine;
    Point p0 = {0, 0};
    LineInit(normalVectorLine, p0, vectNorm);

    uint32_t widthSqr = lineWidth * lineWidth;
    uint32_t sqr = 0;
    lineWidth = 0;
    while (sqr < widthSqr && lineWidth < maxLen) {
        normalVector[lineWidth++] = normalVectorLine.act;
        GetNextPoint(normalVectorLine);
        sqr = normalVectorLine.act.x * normalVectorLine.act.x + normalVectorLine.act.y * normalVectorLine.act.y;
    }
}

void DrawLine::LineInit(LineInfo& line, const Point& start, const Point& end)
{
    line.start.x = start.x;
    line.start.y = start.y;
    line.end.x = end.x;
    line.end.y = end.y;
    line.act.x = line.start.x;
    line.act.y = line.start.y;

    line.dx = MATH_ABS(line.end.x - line.start.x);
    line.twoDx = 2 * line.dx; /* 2: twice as much as dx */
    line.sx = (line.start.x < line.end.x) ? 1 : -1;
    line.dy = MATH_ABS(line.end.y - line.start.y);
    line.twoDy = 2 * line.dy; /* 2: twice as much as dy */
    line.sy = (line.start.y < line.end.y) ? 1 : -1;
    line.hor = (line.dx > line.dy) ? true : false;
    line.p = line.hor ? (line.twoDy - line.dx) : (line.twoDx - line.dy);
}

void DrawLine::GetNextPoint(LineInfo& line)
{
    if (line.hor) {
        line.act.x += line.sx;
        if (line.p >= 0) {
            line.act.y += line.sy;
            line.p = line.p - line.twoDx;
        }
        line.p = line.p + line.twoDy;
    } else {
        line.act.y += line.sy;
        if (line.p >= 0) {
            line.act.x += line.sx;
            line.p = line.p - line.twoDy;
        }
        line.p = line.p + line.twoDx;
    }
}
} // namespace OHOS