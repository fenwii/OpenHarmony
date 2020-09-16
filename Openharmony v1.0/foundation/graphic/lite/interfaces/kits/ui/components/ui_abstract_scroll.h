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
 * @file ui_abstract_scroll.h
 *
 * @brief Declares the base class used to define the attributes of a scroll. The <b>UIList</b>, <b>UIScrollView</b>, and
 *        <b>UISwipeView</b> inherit from this class.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_ABSTRACT_SCROLL_H
#define GRAPHIC_LITE_UI_ABSTRACT_SCROLL_H

#include "animator/animator.h"
#include "animator/easing_equation.h"
#include "components/ui_view_group.h"

namespace OHOS {
/**
 * @brief Defines the attributes of a scroll, including the scroll direction, blank size of a scroll view, velocity and
 *        effects of a scroll animation.
 *
 * @since 1.0
 * @version 1.0
 */
class UIAbstractScroll : public UIViewGroup {
public:
    /**
     * @brief A constructor used to create a <b>UIAbstractScroll</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIAbstractScroll();

    /**
     * @brief A destructor used to delete the <b>UIAbstractScroll</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIAbstractScroll();

    /**
     * @brief Obtains the view type.
     * @return Returns the view type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_ABSTRACT_SCROLL;
    }

    /**
     * @brief Obtains the scroll direction.
     * @return Returns the scroll direction, either {@link HORIZONTAL} or {@link VERTICAL}.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetDirection() const
    {
        return direction_;
    }
    /**
     * @brief Sets the blank size for this scroll view.
     *
     *
     * @param value Indicates the blank size to set. The default value is <b>0</b>. Taking a vertical scroll as an
     *              example, the value <b>0</b> indicates that the head node can only scroll downwards the top of the
     *              view and the tail node scroll upwards the bottom; the value <b>10</b> indicates that the head node
     *              can continue scrolling down by 10 pixels after it reaches the top of the view.
     * @since 1.0
     * @version 1.0
     */
    void SetScrollBlankSize(uint16_t size)
    {
        scrollBlankSize_ = size;
    }

    /**
     * @brief Sets the maximum scroll distance after a finger lifts the screen.
     *
     * @param distance Indicates the maximum scroll distance to set. The default value is <b>0</b>, indicating that the
     *                 scroll distance is not limited.
     * @since 1.0
     * @version 1.0
     */
    void SetMaxScrollDistance(uint16_t distance)
    {
        maxScrollDistance_ = distance;
    }

    /**
     * @brief Sets the rebound size, which is the distance a knob moves after being released when it reaches the end of
     *        a scrollbar.
     *
     * @param size Indicates the rebound size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetReboundSize(uint16_t size)
    {
        reboundSize_ = size;
    }

    /**
     * @brief Obtains the maximum scroll distance after a finger lifts the screen.
     *
     * @return Returns the maximum scroll distance. The default value is <b>0</b>, indicating that the scroll distance
     * is not limited.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetMaxScrollDistance() const
    {
        return maxScrollDistance_;
    }

    /**
     * @brief Sets the easing function that specifies a scroll animation after a finger lifts the screen.
     *
     * @param func Indicates the easing function to set. The default function is {@link EasingEquation::CubicEaseOut}.
     *             For details, see {@link EasingEquation}.
     * @since 1.0
     * @version 1.0
     */
    void SetDragFunc(EasingFunc func)
    {
        easingFunc_ = func;
    }

    /**
     * @brief Sets whether to continue scrolling after a finger lifts the screen.
     *
     * @param throwDrag Specifies whether to continue scrolling after a finger lifts the screen. <b>true</b> indicates
     *                  the scroll continues, and <b>false</b> indicates the scroll stops immediately after a finger
     *                  lifts.
     * @since 1.0
     * @version 1.0
     */
    void SetThrowDrag(bool throwDrag)
    {
        throwDrag_ = throwDrag;
    }

    /**
     * @brief Moves the position of all child views.
     *
     * @param offsetX Indicates the offset distance by which a child view is moved on the x-axis.
     * @param offsetY Indicates the offset distance by which a child view is moved on the y-axis.
     * @since 1.0
     * @version 1.0
     */
    void MoveChildByOffset(int16_t offsetX, int16_t offsetY) override;

    /**
     * @brief Sets the drag acceleration.
     *
     * @param value Indicates the drag acceleration to set. The default value is <b>10</b>. A larger drag acceleration
     *              indicates a higher inertial scroll velocity.
     * @since 1.0
     * @version 1.0
     */
    void SetDragACCLevel(uint16_t value)
    {
        if (value != 0) {
            dragAccCoefficient_ = value;
        }
    }

    /**
     * @brief Obtains the drag acceleration.
     *
     * @return Returns the drag acceleration.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetDragACCLevel() const
    {
        return dragAccCoefficient_;
    }

    /**
     * @brief Sets the compensation distance after a finger lifts the screen.
     *
     * @param value Indicates the compensation distance to set. The default value is <b>0</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetSwipeACCLevel(uint16_t value)
    {
        swipeAccCoefficient_ = value;
    }

    /**
     * @brief Obtains the compensation distance after a finger lifts the screen.
     *
     * @return Returns the compensation distance.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetSwipeACCLevel() const
    {
        return swipeAccCoefficient_;
    }

    static constexpr uint8_t HORIZONTAL = 0;
    static constexpr uint8_t VERTICAL = 1;

protected:
    static constexpr uint8_t HORIZONTAL_AND_VERTICAL = 2;
    /* calculate drag throw distance, last drag distance in one tick * DRAG_DISTANCE_COEFFICIENT */
    static constexpr uint8_t DRAG_DISTANCE_COEFFICIENT = 5;
    /* calculate drag throw times, drag distance / DRAG_TIMES_COEFFICIENT */
    static constexpr uint8_t DRAG_TIMES_COEFFICIENT = 18;
    /* the minimum duration of the swipe animator */
    static constexpr uint8_t MIN_DRAG_TIMES = 5;
    /* acceleration calculation coefficient */
    static constexpr uint8_t DRAG_ACC_FACTOR = 10;
    /* the maximum number of historical drag data */
    static constexpr uint8_t MAX_DELTA_Y_SIZE = 3;

    class ListAnimatorCallback : public AnimatorCallback {
    public:
        ListAnimatorCallback()
            : curtTime_(0),
              dragTimes_(0),
              startValueX_(0),
              endValueX_(0),
              previousValueX_(0),
              startValueY_(0),
              endValueY_(0),
              previousValueY_(0)
        {
        }

        virtual ~ListAnimatorCallback() {}

        void SetDragTimes(uint16_t times)
        {
            dragTimes_ = times;
        }

        void SetDragStartValue(int16_t startValueX, int16_t startValueY)
        {
            startValueX_ = startValueX;
            previousValueX_ = startValueX;
            startValueY_ = startValueY;
            previousValueY_ = startValueY;
        }

        void SetDragEndValue(int16_t endValueX, int16_t endValueY)
        {
            endValueX_ = endValueX;
            endValueY_ = endValueY;
        }

        void RsetCallback()
        {
            curtTime_ = 0;
            dragTimes_ = 0;
            startValueX_ = 0;
            endValueX_ = 0;
            startValueY_ = 0;
            endValueY_ = 0;
        }

        virtual void Callback(UIView* view) override;

        uint16_t curtTime_;
        uint16_t dragTimes_;
        int16_t startValueX_;
        int16_t endValueX_;
        int16_t previousValueX_;
        int16_t startValueY_;
        int16_t endValueY_;
        int16_t previousValueY_;
    };

    bool DragThrowAnimator(Point currentPos, Point lastPos);
    virtual void StopAnimator();
    virtual bool DragXInner(int16_t distance) = 0;
    virtual bool DragYInner(int16_t distance) = 0;
    void RefreshDeltaY(int16_t distance)
    {
        lastDeltaY_[deltaYIndex_ % MAX_DELTA_Y_SIZE] = distance;
        deltaYIndex_++;
    }
    int16_t GetMaxDeltaY() const;

    uint16_t scrollBlankSize_;
    uint16_t reboundSize_;
    uint16_t maxScrollDistance_;
    int16_t lastDeltaY_[MAX_DELTA_Y_SIZE];
    uint8_t dragAccCoefficient_;
    uint8_t swipeAccCoefficient_;
    uint8_t direction_ : 2;
    uint8_t deltaYIndex_ : 2;
    uint8_t reserve_ : 4;
    bool throwDrag_;
    EasingFunc easingFunc_;
    ListAnimatorCallback animatorCallback_;
    Animator animator_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_ABSTRACT_LIST_VIEW_H
