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
 * @file transform.h
 *
 * @brief Provides functions to transform components, points, and line segments, including rotation and scaling.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_TRANSFORM_H
#define GRAPHIC_LITE_TRANSFORM_H

#include "geometry2d.h"
#include "graphic_math.h"
namespace OHOS {
/**
 * @brief Transforms a rectangle, including rotation and scaling.
 * @since 1.0
 * @version 1.0
 */
class TransformMap : public HeapBase {
public:
    /**
     * @brief The default constructor used to create a <b>TransformMap</b> instance.
     * @since 1.0
     * @version 1.0
     */
    TransformMap();

    /**
     * @brief A constructor used to create a <b>TransformMap</b> instance.
     *
     * @param rect Indicates the rectangle to transform.
     * @since 1.0
     * @version 1.0
     */
    explicit TransformMap(const Rect& rect);

    /**
     * @brief A destructor used to delete the <b>TransformMap</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~TransformMap() {}

    /**
     * @brief Checks whether the vertex coordinates of a polygon are clockwise.
     *
     * @return Returns <b>true</b> if the vertex coordinates are clockwise; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool GetClockWise() const;

    /**
     * @brief Sets a polygon after rectangle transformation.
     * @param polygon Indicates the polygon to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPolygon(const Polygon& polygon)
    {
        polygon_ = polygon;
    }

    /**
     * @brief Obtains the polygon after rectangle transformation.
     * @return Returns the polygon.
     * @since 1.0
     * @version 1.0
     */
    Polygon GetPolygon() const
    {
        return polygon_;
    }

    /**
     * @brief Obtains the pivot for the rotation or scaling operation.
     * @return Returns the pivot.
     * @since 1.0
     * @version 1.0
     */
    Point GetPivot() const
    {
        return pivot_;
    }

    /**
     * @brief Checks whether the <b>TransformMap</b> instance is invalid. When the vertices are all 0, the
     *        <b>TransformMap</b> is invalid.
     * @return Returns <b>true</b> if <b>TransformMap</b> is invalid; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsInvalid() const
    {
        for (uint8_t i = 0; i < polygon_.GetVertexNum(); i++) {
            if (polygon_[i].x_ != 0 || polygon_[i].y_ != 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Obtains the minimum rectangle that can contain a polygon. All vertices of the polygon are inside this
     *        rectangle.
     * @return Returns the minimum rectangle that can contain the polygon.
     * @since 1.0
     * @version 1.0
     */
    Rect GetBoxRect() const
    {
        return polygon_.MakeAABB();
    }

    /**
     * @brief Rotates the rectangle.
     * @param angle Indicates the angle to rotate.
     * @param pivot Indicates the rotation pivot.
     * @since 1.0
     * @version 1.0
     */
    void Rotate(int16_t angle, const Vector2<int16_t>& pivot);

    /**
     * @brief Scales the rectangle.
     *
     * @param scale Indicates the scaling factors of the x-axis and y-axis.
     * @param pivot Indicates the pivot for scaling.
     * @since 1.0
     * @version 1.0
     */
    void Scale(const Vector2<float> scale, const Vector2<int16_t>& pivot);

    const Rect& GetTransMapRect() const
    {
        return rect_;
    }

public:
    Matrix3<int64_t> rotate_;
    Matrix3<int64_t> translate_;
    Matrix3<int64_t> scale_;

protected:
    Rect rect_;       /* orig rect */
    Polygon polygon_; /* transformed from rect and 'rotate_' 'translate_' 'scale_' */

private:
    Point pivot_;
};

/**
 * @brief Rotates a point around the pivot by a certain angle.
 * @param point Indicates the point to rotate.
 * @param angle Indicates the angle to rotate.
 * @param pivot Indicates the rotation pivot.
 * @param out Indicates the point generated after rotation.
 * @since 1.0
 * @version 1.0
 */
void Rotate(const Vector2<int16_t>& point, int16_t angle, const Vector2<int16_t>& pivot, Vector2<int16_t>& out);

/**
 * @brief Rotates a line around the pivot by a certain angle.
 * @param origLine Indicates the line segment to rotate.
 * @param angle Indicates the angle to rotate.
 * @param pivot Indicates the rotation pivot.
 * @param out Indicates the line generated after rotation.
 * @since 1.0
 * @version 1.0
 */
void Rotate(const Line& origLine, int16_t angle, const Vector2<int16_t>& pivot, Line& out);

/**
 * @brief Rotates a rectangle around the pivot by a certain angle.
 * @param origRect Indicates the rectangle to rotate.
 * @param angle Indicates the angle to rotate.
 * @param pivot Indicates the rotation pivot.
 * @param out Indicates the polygon generated after the rectangle is rotated.
 * @since 1.0
 * @version 1.0
 */
void Rotate(const Rect& origRect, int16_t angle, const Vector2<int16_t>& pivot, Polygon& out);
} // namespace OHOS
#endif // GRAPHIC_LITE_TRANSFORM_H
