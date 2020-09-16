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
 * @file drag_event.h
 *
 * @brief Declares a drag event, which indicates a certain movement (more than 10 pixels) after a view is pressed.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_DRAG_EVENT_H
#define GRAPHIC_LITE_DRAG_EVENT_H

#include "event.h"

namespace OHOS {
/**
 * @brief Defines a drag event, which indicates a certain movement (more than 10 pixels) after a view is pressed.
 *
 * @since 1.0
 * @version 1.0
 */
class DragEvent : public Event {
public:
    /**
     * @brief A constructor used to create a <b>DragEvent</b> instance.
     * @param newPos Indicates the new position in the drag event.
     * @param lastPos Indicates the last position in the drag event.
     * @param totalLen Indicates the distance that the view has been dragged, including the movement on the x-axis
     *                 and y-axis.
     * @since 1.0
     * @version 1.0
     */
    DragEvent(const Point& newPos, const Point& lastPos, const Point& totalLen) : Event(newPos)
    {
        lastPos_ = lastPos;
        startPos_.x = newPos.x - totalLen.x;
        startPos_.y = newPos.y - totalLen.y;
        preLastPos_ = lastPos;
        deltaX_ = newPos.x - lastPos.x;
        deltaY_ = newPos.y - lastPos.y;
    }

    /**
     * @brief A destructor used to delete the <b>DragEvent</b> instance.
     * @since 1.0
     * @version 1.0
     */
    virtual ~DragEvent() {}

    /**
     * @brief Obtains the coordinates of the last position in the drag event.
     * @return Returns the coordinates of the last position.
     * @since 1.0
     * @version 1.0
     */
    const Point& GetLastPoint() const
    {
        return lastPos_;
    }

    /**
     * @brief Obtains the start coordinates in the drag event.
     * @return Returns the start coordinates.
     * @since 1.0
     * @version 1.0
     */
    const Point& GetStartPoint() const
    {
        return startPos_;
    }

    /**
     * @brief Sets the coordinates of the stay position before the last position in the drag event.
     * @param preLastPos Indicates the coordinates of the stay position to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPreLastPoint(const Point& preLastPos)
    {
        preLastPos_ = preLastPos;
    }

    /**
     * @brief Obtains the coordinates of the stay position before the last position in the drag event.
     * @return Returns the coordinates of the stay position.
     * @since 1.0
     * @version 1.0
     */
    const Point& GetPreLastPoint() const
    {
        return preLastPos_;
    }

    /**
     * @brief Obtains the direction in the drag event.
     * @return Returns the direction. Available values are as follows:
     *         <b>0</b> indicates dragging from left to right.
     *         <b>1</b> indicates dragging from right to left.
     *         <b>2</b> indicates dragging from top to bottom.
     *         <b>3</b> indicates dragging from bottom to top.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetDragDirection() const
    {
        if (MATH_ABS(curPos_.x - startPos_.x) >= MATH_ABS(curPos_.y - startPos_.y)) {
            return (curPos_.x > startPos_.x) ? DIRECTION_LEFT_TO_RIGHT : DIRECTION_RIGHT_TO_LEFT;
        } else {
            return (curPos_.y > startPos_.y) ? DIRECTION_TOP_TO_BOTTOM : DIRECTION_BOTTOM_TO_TOP;
        }
    }

    /**
     * @brief Obtains the difference between the current position and the last position of the view in the x-axis.
     * @return Returns the different in the x-aix.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetDeltaX() const
    {
        return deltaX_;
    }

    /**
     * @brief Obtains the difference between the current position and the last position of the view in the y-axis.
     * @return Returns the different in the y-aix.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetDeltaY() const
    {
        return deltaY_;
    }

    static constexpr uint8_t DIRECTION_LEFT_TO_RIGHT = 0;
    static constexpr uint8_t DIRECTION_RIGHT_TO_LEFT = 1;
    static constexpr uint8_t DIRECTION_TOP_TO_BOTTOM = 2;
    static constexpr uint8_t DIRECTION_BOTTOM_TO_TOP = 3;

private:
    Point lastPos_;
    Point startPos_;
    Point preLastPos_;
    int16_t deltaX_;
    int16_t deltaY_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAG_EVENT_H

