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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file geometry2d.h
 *
 * @brief Defines attributes of 2D geometries (including points, lines, rectangles, and polygons) of the lightweight
 *        graphics system and provides functions for performing operations on the geometries.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_GEOMETRY2D_H
#define GRAPHIC_LITE_GEOMETRY2D_H

#include "graphic_assert.h"
#include "graphic_math.h"
#include "graphic_types.h"
#include "rect.h"
#include "heap_base.h"
#include <string.h>

namespace OHOS {
/**
 * @brief Defines a line, which consists of the start and end points.
 * @since 1.0
 * @version 1.0
 */
class Line : public HeapBase {
public:
    /**
     * @brief The default constructor used to create a <b>Line</b> instance.
     * @since 1.0
     * @version 1.0
     */
    Line() {}

    /**
     * @brief A constructor used to create a <b>Line</b> instance.
     * @param a Indicates the start point of the line.
     * @param b Indicates the end point of the line.
     * @since 1.0
     * @version 1.0
     */
    Line(const Vector2<int16_t>& a, const Vector2<int16_t>& b)
    {
        vertex_[0] = a;
        vertex_[1] = b;
    }

    /**
     * @brief A constructor used to create a <b>Line</b> instance.
     * @param x1 Indicates the X coordinate of the line's start point.
     * @param y1 Indicates the Y coordinate of the line's start point.
     * @param x2 Indicates the X coordinate of the line's end point.
     * @param y2 Indicates the Y coordinate of the line's end point.
     * @since 1.0
     * @version 1.0
     */
    Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
    {
        vertex_[0].x_ = x1;
        vertex_[0].y_ = y1;
        vertex_[1].x_ = x2;
        vertex_[1].y_ = y2;
    }

    /**
     * @brief A destructor used to delete the <b>Line</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~Line() {}

    /**
     * @brief Obtains the start or end point of the line based on the value of <b>index</b>.
     * @param index Indicates the start or end point to obtain. The value <b>0</b> indicates that the start point is to
     *              be obtained, and <b>1</b> indicates that the end point is to be obtained.
     * @return Returns the start or end point of the line.
     * @since 1.0
     * @version 1.0
     */
    Vector2<int16_t>& operator[](uint8_t index)
    {
        return vertex_[index];
    }

    /**
     * @brief Obtains the start or end point of the line based on the value of <b>index</b>.
     * @param index Indicates the start or end point to obtain. The value <b>0</b> indicates that the start point is to
     *              be obtained, and <b>1</b> indicates that the end point is to be obtained.
     * @return Returns the start or end point of the line.
     * @since 1.0
     * @version 1.0
     */
    const Vector2<int16_t> operator[](uint8_t index) const
    {
        return vertex_[index];
    }

protected:
    Vector2<int16_t> vertex_[2]; /* 2: two vertexes of the line */
};

/**
 * @brief Defines a polygon, including vertex coordinates and the maximum number of vertices
 *        (defined by {@link MAX_VERTEX_NUM}).
 *
 * @since 1.0
 * @version 1.0
 */
class Polygon : public HeapBase {
public:
    /**
     * @brief The default constructor used to create a <b>Polygon</b> instance.
     * @since 1.0
     * @version 1.0
     */
    Polygon() : vertexNum_(0) {}

    /**
     * @brief A constructor used to construct a <b>Polygon</b> instance based on a rectangle.
     *
     * @param rect Indicates the rectangle used to construct the polygon.
     * @since 1.0
     * @version 1.0
     */
    explicit Polygon(const Rect& rect)
    {
        vertexNum_ = 4; // 4: number of vertex
        vertexes_[0].x_ = rect.GetLeft();
        vertexes_[0].y_ = rect.GetTop();

        vertexes_[1].x_ = rect.GetRight();
        vertexes_[1].y_ = rect.GetTop();

        vertexes_[2].x_ = rect.GetRight();
        vertexes_[2].y_ = rect.GetBottom();

        vertexes_[3].x_ = rect.GetLeft();
        vertexes_[3].y_ = rect.GetBottom();
    }

    /**
     * @brief A constructor used to create a <b>Polygon</b> instance based on the vertex coordinates and the number of
     *        coordinates.
     *
     * The number of vertex coordinates cannot exceed the value of {@link MAX_VERTEX_NUM}.
     *
     * @param vertexes Indicates the pointer to the vertex coordinates.
     * @param vertexNum Indicates the number of vertices.
     * @since 1.0
     * @version 1.0
     */
    Polygon(const Vector2<int16_t>* vertexes, const uint8_t vertexNum);

    /**
     * @brief A destructor used to delete the <b>Polygon</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~Polygon() {}

    /**
     * @brief Obtains the minimum rectangle that can contain the polygon. All vertices of the polygon are inside this
     *        rectangle.
     *
     * @return Returns the minimum rectangle that contains the polygon.
     * @since 1.0
     * @version 1.0
     */
    Rect MakeAABB() const;

    /**
     * @brief Obtains the number of vertices of the polygon.
     *
     * @return Returns the number of vertices.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetVertexNum() const
    {
        return vertexNum_;
    }

    /**
     * @brief Sets the number of vertices of a polygon.
     * @param vertexNum Indicates the number of vertices.
     * @since 1.0
     * @version 1.0
     */
    void SetVertexNum(uint8_t vertexNum)
    {
        vertexNum_ = vertexNum;
    }

    const Vector2<int16_t> operator[](uint8_t index) const
    {
        return vertexes_[index];
    }

    Vector2<int16_t>& operator[](uint8_t index)
    {
        ASSERT(index < MAX_VERTEX_NUM);
        return vertexes_[index];
    }

    Polygon& operator=(const Rect& rect)
    {
        /* clockwise */
        vertexNum_ = 4; // 4: number of vertex
        vertexes_[0].x_ = rect.GetLeft();
        vertexes_[0].y_ = rect.GetTop();

        vertexes_[1].x_ = rect.GetRight();
        vertexes_[1].y_ = rect.GetTop();

        vertexes_[2].x_ = rect.GetRight();
        vertexes_[2].y_ = rect.GetBottom();

        vertexes_[3].x_ = rect.GetLeft();
        vertexes_[3].y_ = rect.GetBottom();

        return *this;
    }

    /** Maximum number of vertices in a polygon */
    static const uint8_t MAX_VERTEX_NUM = 8;

protected:
    Vector2<int16_t> vertexes_[MAX_VERTEX_NUM]; /* the vertexes of polygon */
    uint8_t vertexNum_;                         /* the vertex num of polygon */
};

/**
 * @brief Checks whether line segment a and line segment b intersect, and returns the intersection point (if available).
 * @param a Indicates line segment a.
 * @param b Indicates line segment b.
 * @param out Indicates the intersection point.
 * @return Returns <b>true</b> if the two line segments intersect; returns <b>false</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
bool Intersect(const Line& a, const Line& b, Vector2<int16_t>& out);

/**
 * @brief Chekcs whether line segment a and line segment b intersect.
 * @param a Indicates line segment a.
 * @param b Indicates line segment b.
 * @return Returns <b>true</b> if the two line segments intersect; returns <b>false</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
bool IsIntersect(const Line& a, const Line& b);

/**
 * @brief Clips a polygon by using a line segment.
 * @param poly Indicates the polygon to clip.
 * @param line Indicates the line segment used for clipping.
 * @since 1.0
 * @version 1.0
 */
void Clip(Polygon& poly, const Line& line);

/**
 * @brief Implements Sutherland-Hodgman, an algorithm used for clipping polygons.
 * @param clipRect Indicates the rectangle used for clipping the polygon.
 * @param polygon Indicates the polygon to clip.
 * @return Returns the polygon after clipping.
 * @since 1.0
 * @version 1.0
 */
Polygon SuthHodgClip(const Rect& clipRect, const Polygon& polygon);

/**
 * @brief Clips a polygon by using a line segment and obtains the intersections.
 * @param line Indicates the line segment used for clipping.
 * @param poly Indicates the polygon to clip.
 * @param pOut Indicates the pointer to the intersections.
 * @param pNum Indicates the pointer to the number of the intersections.
 * @since 1.0
 * @version 1.0
 */
void Clip(const Line& line, const Polygon& poly, Vector2<int16_t>* pOut, uint8_t* pNum);
} // namespace OHOS
#endif // GRAPHIC_LITE_GEOMETRY2D_H
