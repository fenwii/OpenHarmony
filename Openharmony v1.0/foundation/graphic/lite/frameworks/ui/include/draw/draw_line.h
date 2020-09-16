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

#ifndef GRAPHIC_LITE_DRAW_LINE_H
#define GRAPHIC_LITE_DRAW_LINE_H

#include "color.h"
#include "geometry2d.h"

namespace OHOS {
struct LineInfo {
    Point start;
    Point end;
    Point act;
    int16_t dx;
    int16_t sx;
    int16_t dy;
    int16_t sy;
    int16_t twoDx;
    int16_t twoDy;
    int16_t p;
    bool hor;
};

class DrawLine : public HeapBase {
public:
    static void Draw(const Point& start, const Point& end, const Rect& mask,
        int16_t width, const ColorType& color, OpacityType opacity);

private:
    static void DrawVerticalLine(const Point& start, const Point& end, const Rect& mask,
        int16_t width, const ColorType& color, OpacityType opacity);
    static void DrawHorizontalLine(const Point& start, const Point& end, const Rect& mask,
        int16_t width, const ColorType& color, OpacityType opacity);
    static void DrawObliqueLine(const Point& start, const Point& end, const Rect& mask,
        int16_t width, const ColorType& color, OpacityType opacity);
    static void DrawBresenhamLine(LineInfo& line, const Point& translate, bool fillGaps,
        const Rect& mask, const ColorType& color, OpacityType opacity);
    static void GenerateNormalVector(LineInfo& mainLine, int16_t& lineWidth, Point* pattern, int16_t maxLen);
    static void LineInit(LineInfo& line, const Point& start, const Point& end);
    static void GetNextPoint(LineInfo& line);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_LINE_H
