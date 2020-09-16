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
 * @file rect.h
 *
 * @brief Defines a rectangle, including the position data of the four boundaries of the rectangle, and provides
 *        functions for rectangle inclusion, intersection, and aggregation.
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_RECT_H
#define GRAPHIC_LITE_RECT_H

#include "heap_base.h"
#include "graphic_types.h"
#include "graphic_math.h"

namespace OHOS {
/**
 * @brief Defines a rectangle, including the position data of the four boundaries of the rectangle, and provides
 *        functions for rectangle inclusion, intersection, and aggregation.
 * @since 1.0
 * @version 1.0
 */
class Rect : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Rect</b> instance.
     * @since 1.0
     * @version 1.0
     */
    Rect() : left_(0), top_(0), right_(0), bottom_(0) {}

    /**
     * @brief A destructor used to delete the <b>Rect</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~Rect() {}

    /**
     * @brief A constructor used to create a <b>Rect</b> instance based on the coordinates of the four boundaries.
     * @param left Indicates the coordinate of the left boundary.
     * @param top Indicates the coordinate of the top boundary.
     * @param right Indicates the coordinate of the right boundary.
     * @param bottom Indicates the coordinate of the bottom boundary.
     * @since 1.0
     * @version 1.0
     */
    Rect(int16_t left, int16_t top, int16_t right, int16_t bottom);

    /**
     * @brief A constructor used to create a <b>Rect</b> instance by copying another rectangle.
     *
     * @param other Indicates the rectangle to copy.
     * @since 1.0
     * @version 1.0
     */
    Rect(const Rect& other);

    /**
     * @brief A constructor used to create a <b>Rect</b> instance by copying another rectangle.
     *
     * @param other Indicates the rectangle to copy.
     * @since 1.0
     * @version 1.0
     */
    Rect(const Rect&& other);

    /**
     * @brief Sets the coordinates of the four boundaries of a rectangle.
     *
     * @param left Indicates the coordinate of the left boundary.
     * @param top Indicates the coordinate of the top boundary.
     * @param right Indicates the coordinate of the right boundary.
     * @param bottom Indicates the coordinate of the bottom boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetRect(int16_t left, int16_t top, int16_t right, int16_t bottom);

    /**
     * @brief Obtains the rectangle width.
     * @return Returns the rectangle width.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetWidth() const
    {
        return right_ - left_ + 1;
    }

    /**
     * @brief Obtains the rectangle height.
     * @return Returns the rectangle height.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetHeight() const
    {
        return bottom_ - top_ + 1;
    }

    /**
     * @brief Obtains the left boundary coordinate of the rectangle.
     * @return Returns the left boundary coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetX() const
    {
        return left_;
    }

    /**
     * @brief Obtains the top boundary coordinate of the rectangle.
     * @return Returns the top boundary coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetY() const
    {
        return top_;
    }

    /**
     * @brief Obtains the left boundary coordinate of the rectangle.
     * @return Returns the left boundary coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetLeft() const
    {
        return left_;
    }

    /**
     * @brief Obtains the top boundary coordinate of the rectangle.
     * @return Returns the top boundary coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetTop() const
    {
        return top_;
    }

    /**
     * @brief Obtains the right boundary coordinate of the rectangle.
     * @return Returns the right boundary coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetRight() const
    {
        return right_;
    }

    /**
     * @brief Obtains the bottom boundary coordinate of the rectangle.
     * @return Returns the bottom boundary coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetBottom() const
    {
        return bottom_;
    }

    /**
     * @brief Changes the left boundary coordinate of the rectangle without changing the rectangle width.
     * @param x Indicates the coordinate of the left boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetX(int16_t x)
    {
        right_ += x - left_;
        left_ = x;
    }

    /**
     * @brief Changes the top boundary coordinate of the rectangle without changing the rectangle height.
     * @param y Indicates the coordinate of the top boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetY(int16_t y)
    {
        bottom_ += y - top_;
        top_ = y;
    }

    /**
     * @brief Changes the coordinates of the left and top boundaries of the rectangle without changing the rectangle
     *        width and height.
     * @param x Indicates the coordinate of the left boundary.
     * @param y Indicates the coordinate of the top boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetPosition(int16_t x, int16_t y)
    {
        right_ += x - left_;
        bottom_ += y - top_;
        left_ = x;
        top_ = y;
    }

    /**
     * @brief Changes the width of the rectangle without changing the coordinate of the left boundary.
     * @param width Indicates the width of the rectangle.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width)
    {
        right_ = left_ + width - 1;
    }

    /**
     * @brief Changes the height of the rectangle without changing the coordinate of the top boundary.
     * @param height Indicates the height of the rectangle.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height)
    {
        bottom_ = top_ + height - 1;
    }

    /**
     * @brief Sets the coordinate of the left boundary of a rectangle.
     * @param left Indicates the coordinate of the left boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetLeft(int16_t left)
    {
        left_ = left;
    }

    /**
     * @brief Sets the coordinate of the top boundary of a rectangle.
     * @param top Indicates the coordinate of the top boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetTop(int16_t top)
    {
        top_ = top;
    }

    /**
     * @brief Sets the coordinate of the right boundary of a rectangle.
     * @param right Indicates the coordinate of the right boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetRight(int16_t right)
    {
        right_ = right;
    }

    /**
     * @brief Sets the coordinate of the bottom boundary of a rectangle.
     * @param bottom Indicates the coordinate of the bottom boundary.
     * @since 1.0
     * @version 1.0
     */
    void SetBottom(int16_t bottom)
    {
        bottom_ = bottom;
    }

    /**
     * @brief Sets the width and height of a rectangle.
     * @param width Indicates the width of the rectangle.
     * @param height Indicates the height of the rectangle.
     * @since 1.0
     * @version 1.0
     */
    void Resize(int16_t width, int16_t height)
    {
        right_ = left_ + width - 1;
        bottom_ = top_ + height - 1;
    }

    /**
     * @brief Obtains the area of a rectangle.
     * @return Returns the area of the rectangle.
     * @since 1.0
     * @version 1.0
     */
    uint32_t GetSize() const;

    /**
     * @brief Checks whether two rectangles intersect.
     * @param rect1 Indicates the first rectangle to check.
     * @param rect2 Indicates the second rectangle to check.
     * @return Returns <b>true</b> if the two rectangles intersect; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool Intersect(const Rect& rect1, const Rect& rect2);

    /**
     * @brief Obtains the minimum rectangle that contains another two rectangles.
     * @param rect1 Indicates the first rectangle to contain.
     * @param rect2 Indicates the second rectangle to contain.
     * @since 1.0
     * @version 1.0
     */
    void Join(const Rect& rect1, const Rect& rect2);

    /**
     * @brief Checks whether the rectangle contains a coordinate point.
     * @param point Indicates the coordinate point.
     * @return Returns <b>true</b> if the input coordinate point is contained; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsContains(const Vector2<int16_t>& point) const;

    /**
     * @brief Checks whether the rectangle contains a coordinate point.
     * @param point Indicates the coordinate point.
     * @return Returns <b>true</b> if the input coordinate point is contained; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsContains(const Point& point) const;

    /**
     * @brief Checks whether the rectangle is adjacent to another rectangle horizontally or vertically.
     * @param other Indicates the rectangle to be used for check.
     * @return Returns <b>true</b> if the rectangle is adjacent to the input rectangle; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsExtends(const Rect& other) const;

    /**
     * @brief Checks whether the rectangle intersects with another rectangle.
     * @param other Indicates the rectangle to be used for check.
     * @return Returns <b>true</b> if the two rectangles intersect; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsIntersect(const Rect& other) const;

    /**
     * @brief Checks whether the rectangle contains another rectangle.
     *
     * @param other Indicates the rectangle to be used for check.
     * @return Returns <b>true</b> if the input rectangle is contained; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsContains(const Rect& other) const;

    void Inflate(int16_t delta);
    void operator=(const Rect& other);
    void operator=(const Rect&& other);

protected:
    int16_t left_;
    int16_t top_;
    int16_t right_;
    int16_t bottom_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_RECT_H