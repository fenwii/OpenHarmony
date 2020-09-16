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
 * @file ui_swipe_view.h
 *
 * @brief Defines the attributes and common functions of a swipe view.
 *
 * Each swipe view consists of multiple child views, which can be navigated through swiping. The child views can be
 * either horizontal or vertical.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_SWIPE_VIEW_H
#define GRAPHIC_LITE_UI_SWIPE_VIEW_H

#include "animator/animator.h"
#include "components/ui_abstract_scroll.h"

namespace OHOS {
/**
 * @brief Represents a swipe view.
 *
 * Each swipe view consists of multiple child views, which can be navigated through swiping. The child views can be
 * either horizontal or vertical.
 *
 * @see UIAbstractScroll
 * @since 1.0
 * @version 1.0
 */
class UISwipeView : public UIAbstractScroll {
public:
    /**
     * @brief Represents a listener for changes of the swipe view.
     *
     * This is an inner class of <b>UISwipeView</b>. It contains a callback function to be invoked when the swipe view
     * state changes.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnSwipeListener : public HeapBase {
    public:
        virtual void OnSwipe(UISwipeView& view) = 0;
        virtual ~OnSwipeListener() {}
    };

    /**
     * @brief A constructor used to create a <b>UISwipeView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UISwipeView(uint8_t direction = HORIZONTAL);

    /**
     * @brief A destructor used to delete the <b>UISwipeView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UISwipeView();

    /**
     * @brief Obtains the component type.
     *
     * @return Returns the component type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_SWIPE_VIEW;
    }

    /**
     * @brief Sets the dragging direction.
     *
     * @param direction Indicates the dragging direction, either {@link HORIZONTAL} or {@link VERTICAL}.
     * @since 1.0
     * @version 1.0
     */
    void SetDirection(uint8_t direction)
    {
        direction_ = direction;
    }

    /**
     * @brief Obtains the dragging direction.
     *
     * @return Returns the dragging direction.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetDirection() const
    {
        return direction_;
    }

    /**
     * @brief Adds a view.
     *
     * @param view Indicates the view to add.
     * @since 1.0
     * @version 1.0
     */
    void Add(UIView* view) override;

    /**
     * @brief Inserts a view.
     *
     * @param prevView Indicates the previous view.
     * @param insertView Indicates the view to insert.
     * @since 1.0
     * @version 1.0
     */
    void Insert(UIView* prevView, UIView* insertView) override;

    /**
     * @brief Deletes a view.
     *
     * @param view Indicates the view to delete.
     * @since 1.0
     * @version 1.0
     */
    virtual void Remove(UIView* view) override;

    /**
     * @brief Sets the index for the current tab.
     *
     * @param index Indicates the index of a view.
     * @param needAnimator Specifies whether a flip animation is needed. <b>false</b> (default value) indicates a flip
     * animation is not needed, and <b>true</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetCurrentPage(uint16_t index, bool needAnimator = false);

    /**
     * @brief Obtains the current tab index.
     *
     * @return Returns the current tab index.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetCurrentPage() const
    {
        return curIndex_;
    }

    /**
     * @brief Obtains the current view.
     *
     * @return Returns the current view.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetCurrentView() const
    {
        return curView_;
    }

    /**
     * @brief Sets a blank size, as defined in {@link DEFAULT_BLANK_SIZE}
     *
     * @param size Indicates the blank size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetBlankSize(uint16_t size)
    {
        blankSize_ = size;
    }

    /**
     * @fn void OnDragEvent(const DragEvent& event) override
     *
     * @brief revice drag event, Switch to specified view when drag
     *
     * @param event The drag event
     */
    bool OnDragEvent(const DragEvent& event) override;

    bool OnDragEndEvent(const DragEvent& event) override;

    /**
     * @brief Sets the time for the page being animated. The page will go beyond the blank during this time.
     *
     * @param time Indicates the time of the page being animated.
     * @since 1.0
     * @version 1.0
     */
    void SetAnimatorTime(uint16_t time);

    /**
     * @brief Sets whether the swipe view supports a cycle swipe.
     *
     * @param loop Indicates the cycle swipe flag. <b>true</b> indicates the cycle swipe is supported, and <b>false</b>
     * indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetLoopState(bool loop)
    {
        loop_ = loop;
    }

    /**
     * @brief Obtains a view based on its index.
     *
     * @param Indicates the index of a view.
     * @return Returns the view.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetViewByIndex(uint16_t index) const;

    /**
     * @brief Obtains the listener set for swipe events.
     *
     * @return Returns the swipe event listener.
     * @since 1.0
     * @version 1.0
     */
    OnSwipeListener*& GetOnSwipeListener()
    {
        return swipeListener_;
    }

    /**
     * @brief Sets the listener that contains a callback to be invoked upon a swipe event.
     *
     * @param onSwipeListener Indicates the listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnSwipeListener(OnSwipeListener* onSwipeListener)
    {
        swipeListener_ = onSwipeListener;
    }

    /**
     * @brief Indicates the horizontal direction.
     *
     * @since 1.0
     * @version 1.0
     */
    static constexpr uint8_t HORIZONTAL = 0;

    /**
     * @brief Indicates the vertical direction.
     *
     * @since 1.0
     * @version 1.0
     */
    static constexpr uint8_t VERTICAL = 1;

protected:
    bool DragXInner(int16_t distance) override;
    bool DragYInner(int16_t distance) override;
    void SortChild();
    void StopAnimator() override;
    virtual void SwitchToPage(int16_t dst, bool needAnimator = true);
    void MoveChildByOffset(int16_t xOffset, int16_t yOffset) override;

    /**
     * @brief Indicates that the animation duration is 12 ticks.
     *
     * @since 1.0
     * @version 1.0
     */
    constexpr static uint16_t ANIMATOR_TIME = 12;

    /**
     * @brief Indicates the maximum distance of an invalid dragging. Dragging is not triggered if the distance is less
     * than this value.
     *
     * @since 1.0
     * @version 1.0
     */
    constexpr static uint16_t STOP_DISTANCE = 5;

    /**
     * @brief Indicates the maximum distance between the first and the last tab when the current view is not in a cycle
     * swipe mode. The page can be rebound after the setting.
     *
     * @since 1.0
     * @version 1.0
     */
    constexpr static uint16_t DEFAULT_BLANK_SIZE = 30;
    uint16_t tickTime_;
    OnSwipeListener* swipeListener_;
    uint16_t curIndex_;
    uint16_t blankSize_;
    UIView* curView_;
    uint8_t direction_;
    bool loop_;

private:
    void RefreshCurrentView(int16_t distance);
    void RefreshCurrentViewInner(int16_t distance, int16_t (UIView::*pfnGetXOrY)() const,
        int16_t(UIView::*pfnGetWidthOrHeight)());
    bool isNeedLoop();
    void MoveFirstChildToLast();
    void MoveLastChildToFirst();
    void CalculateInvalidate();
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_SWIPE_VIEW_H

