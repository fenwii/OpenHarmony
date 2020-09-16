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

#include "draw/draw_triangle.h"
#include "draw/draw_utils.h"

namespace OHOS {
void DrawTriangle::Draw(const Point* points, uint8_t count, const Rect& mask, const ColorType& color, OpacityType opa)
{
    if (points == nullptr || count != VERTEX_NUM) {
        return;
    }
    // sort vertex according to y axis
    Point p1 = points[0];  // 0: point index
    Point p2 = points[1];  // 1: point index
    Point p3 = points[2];  // 2: point index
    // return if vertexs are invalid.
    if (p1.x == p2.x && (p1.y == p2.y || p1.x == p3.x)) {
        return;
    }
    if (p2.x == p3.x && p2.y == p3.y) {
        return;
    }
    if ((p1.x == p3.x || p1.y == p2.y) && p1.y == p3.y) {
        return;
    }
    SortVertexs(p1, p2, p3);
    Edge edge1 = InitEdge(p1, p2);
    Edge edge2 = InitEdge(p1, p3);
    Rect area;
    int16_t lastY = p1.y;

    while (edge1.curPoint.y <= p3.y) {
        // change edge1 from p1-p2 to p2-p3
        if (edge1.curPoint.y == p2.y) {
            edge1 = InitEdge(p2, p3);
            if (edge1.dPoint.y == 0) {
                return;
            }
        }

        area.SetLeft(MATH_MIN(edge1.curPoint.x, edge2.curPoint.x));
        area.SetRight(MATH_MAX(edge1.curPoint.x, edge2.curPoint.x));
        area.SetTop(MATH_MIN(edge1.curPoint.y, edge2.curPoint.y));
        area.SetBottom(MATH_MAX(edge1.curPoint.y, edge2.curPoint.y));
        DrawUtils::GetInstance()->DrawColorArea(area, mask, color, opa);

        while (edge1.curPoint.y == lastY) {
            // use Bresenham algorithm to get next point on edge1
            StepToNextPointOnEdge(edge1);
        }
        while (edge2.curPoint.y == lastY) {
            // use Bresenham algorithm to get next point on edge2
            StepToNextPointOnEdge(edge2);
        }
        lastY = edge1.curPoint.y;
    }
}

void DrawTriangle::SortVertexs(Point& p1, Point& p2, Point& p3)
{
    SortPoint(p1, p2);
    SortPoint(p2, p3);
    SortPoint(p1, p2);
}

void DrawTriangle::SortPoint(Point& p1, Point& p2)
{
    Point temp;
    if (p1.y > p2.y) {
        temp = p1;
        p1 = p2;
        p2 = temp;
    }
}

void DrawTriangle::StepToNextPointOnEdge(Edge& edge)
{
    if (edge.dPoint.x > edge.dPoint.y) {
        edge.curPoint.x += edge.uPoint.x;
        edge.eps += edge.dPoint.y;
        if ((edge.eps << 1) >= edge.dPoint.x) {
            edge.curPoint.y += edge.uPoint.y;
            edge.eps -= edge.dPoint.x;
        }
    } else {
        edge.curPoint.y += edge.uPoint.y;
        edge.eps += edge.dPoint.x;
        if ((edge.eps << 1) >= edge.dPoint.y) {
            edge.curPoint.x += edge.uPoint.x;
            edge.eps -= edge.dPoint.y;
        }
    }
}

DrawTriangle::Edge DrawTriangle::InitEdge(const Point& startP, const Point& endP)
{
    Edge edge = { {0, 0}, {0, 0}, {0, 0}, 0 };
    edge.curPoint = startP;
    edge.dPoint.x = startP.x - endP.x;
    edge.dPoint.y = startP.y - endP.y;
    edge.uPoint.x = (edge.dPoint.x < 0) ? 1 : -1;
    edge.uPoint.y = (edge.dPoint.y < 0) ? 1 : -1;
    edge.eps = 0;
    edge.dPoint.x = MATH_ABS(edge.dPoint.x);
    edge.dPoint.y = MATH_ABS(edge.dPoint.y);
    return edge;
}
} // namespace OHOS