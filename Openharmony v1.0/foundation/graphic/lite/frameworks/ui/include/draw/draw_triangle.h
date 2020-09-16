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

#ifndef GRAPHIC_LITE_DRAW_TRIANGLE_H
#define GRAPHIC_LITE_DRAW_TRIANGLE_H

#include "color.h"
#include "geometry2d.h"

namespace OHOS {
class DrawTriangle : public HeapBase {
public:
    static void Draw(const Point* points, uint8_t count, const Rect& mask, const ColorType& color, OpacityType opa);

    struct Edge {
        Point curPoint;
        Point dPoint;
        Point uPoint;
        int16_t eps;
    };

    static void SortVertexs(Point& p1, Point& p2, Point& p3);

    static void SortPoint(Point& p1, Point& p2);

    static void StepToNextPointOnEdge(Edge& edge);

    static Edge InitEdge(const Point& startP, const Point& endP);
private:
    static constexpr uint8_t VERTEX_NUM = 3;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_TRIANGLE_H
