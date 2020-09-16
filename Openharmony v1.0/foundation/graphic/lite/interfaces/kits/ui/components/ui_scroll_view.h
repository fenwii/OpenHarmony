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
 * @file ui_scroll_view.h
 *
 * @brief Declares a view group that allows its child views to be displayed as scroll events occur.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_SCROLL_VIEW_H
#define GRAPHIC_LITE_UI_SCROLL_VIEW_H

#include "animator/animator.h"
#include "components/ui_abstract_scroll.h"

namespace OHOS {
/**
 * @brief Supports horizontal or vertical scroll of child views. This class is inherited from {@link UIAbstractScroll}.
 *
 * Horizontal or vertical scroll occurs only when the width or height of the child view is greater than that of the
 * <b>UIScrollView</b>.
 *
 * @since 1.0
 * @version 1.0
 */
class UIScrollView : public UIAbstractScroll {
public:
    /**
     * @brief Represents a listener that contains a callback to be invoked upon scroll state changes. The state can
     *        either be {@link SCROLL_STATE_STOP} or {@link SCROLL_STATE_MOVE}.
     * @since 1.0
     * @version 1.0
     */
    class OnScrollListener : public HeapBase {
    public:
        /**
         * @brief A constructor used to create an <b>OnScrollListener</b> instance with the default scroll state
         *        {@link SCROLL_STATE_STOP}.
         * @since 1.0
         * @version 1.0
         */
        OnScrollListener() : state_(SCROLL_STATE_STOP) {}

        /**
         * @brief A destructor used to delete the <b>OnScrollListener</b> instance.
         * @since 1.0
         * @version 1.0
         */
        virtual ~OnScrollListener() {}

        /**
         * @brief Called when a scroll starts.
         *
         * @since 1.0
         * @version 1.0
         */
        virtual void OnScrollStart() {}

        /**
         * @brief Called when a scroll ends.
         *
         * @since 1.0
         * @version 1.0
         */
        virtual void OnScrollEnd() {}

        /**
         * @brief Obtains the scroll state of this view.
         *
         * @return Returns the scroll state, either {@link SCROLL_STATE_STOP} or {@link SCROLL_STATE_MOVE}.
         * @since 1.0
         * @version 1.0
         */
        uint8_t GetScrollState() const
        {
            return state_;
        }

        void SetScrollState(uint8_t state)
        {
            state_ = state;
        }

        static constexpr uint8_t SCROLL_STATE_STOP = 0;
        static constexpr uint8_t SCROLL_STATE_MOVE = 1;

    private:
        uint8_t state_;
    };

    /**
     * @brief A constructor used to create a <b>UIScrollView</b> instance, with both horizontal and vertical scrolls
     *        supported.
     *
     * @since 1.0
     * @version 1.0
     */
    UIScrollView();

    /**
     * @brief A destructor used to delete the <b>UIScrollView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIScrollView() {}

    /**
     * @brief Obtains the view type.
     * @return Returns the view type, as defined in {@link UIViewType}.
     *
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_SCROLL_VIEW;
    }

    void OnPostDraw(const Rect& invalidatedArea) override;

    bool OnDragEvent(const DragEvent& event) override;

    bool OnDragEndEvent(const DragEvent& event) override;

    void OnPressEvent(const PressEvent& event) override;

    /**
     * @brief Scrolls the content of this view.
     *
     * @param xDistance Indicates the offset distance by which the content is scrolled on the x-axis.
     * @param yDistance Indicates the offset distance by which the content is scrolled on the y-axis.
     * @since 1.0
     * @version 1.0
     */
    void ScrollBy(int16_t xDistance, int16_t yDistance);

    /**
     * @brief Sets the width for this scroll bar.
     *
     * @param width Indicates the width to set. The default value is {@link DEFAULT_BAR_WIDTH}.
     * @since 1.0
     * @version 1.0
     */
    void SetScrollbarWidth(uint8_t width)
    {
        scrollBarWidth_ = width;
        minScrollBarLen_ = scrollBarWidth_ * MIN_BAR_MULTIPLE;
    }

    /**
     * @brief Sets whether a horizontal scroll is enabled.
     *
     * @param state Specifies whether a horizontal scroll is enabled. <b>true</b> indicates a horizontal scroll is
     *              enabled, and <b>false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetHorizontalScrollState(bool state)
    {
        xScrollable_ = state;
    }

    /**
     * @brief Checks whether a horizontal scroll is enabled.
     *
     * @return Returns <b>true</b> if a horizontal scroll is enabled; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool GetHorizontalScrollState() const
    {
        return xScrollable_;
    }

    /**
     * @brief Sets whether a vertical scroll is enabled.
     *
     * @param state Specifies whether a vertical scroll is enabled. <b>true</b> indicates a vertical scroll is enabled,
     *              and <b>false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetVerticalScrollState(bool state)
    {
        yScrollable_ = state;
    }

    /**
     * @brief Checks whether a vertical scroll is enabled.
     *
     * @return Returns <b>true</b> if a vertical scroll is enabled, returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool GetVerticalScrollState() const
    {
        return yScrollable_;
    }

    /**
     * @brief Sets whether the horizontal scroll bar is visible.
     *
     * @param state Specifies whether the horizontal scroll bar is visible. <b>true</b> indicates the horizontal scroll
     *              bar is visible, and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetXScrollBarVisible(bool state)
    {
        xSlider_.SetVisible(state);
    }

    /**
     * @brief Sets whether the vertical scroll bar is visible.
     *
     * @param state Specifies whether this vertical scroll bar is visible. <b>true</b> indicates the horizontal scroll
     *              bar is visible, and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetYScrollBarVisible(bool state)
    {
        ySlider_.SetVisible(state);
    }

    /**
     * @brief Registers a listener that contains a callback to be invoked upon scroll state changes.
     *
     * @param scrollListener Indicates the listener to register. For details, see {@link OnScrollListener}.
     * @since 1.0
     * @version 1.0
     */
    void RegisterScrollListener(OnScrollListener* scrollListener)
    {
        scrollListener_ = scrollListener;
    }

    void RefreshScrollBar();

protected:
    void StopAnimator() override;
    bool DragXInner(int16_t distance) override;
    bool DragYInner(int16_t distance) override;

private:
    void Drag(const DragEvent& event);
    void RefreshScrollBarPosition();
    bool MoveOffset(int16_t offsetX, int16_t offsetY);
    int16_t GetXScrollOffset(const Rect& childRect);
    int16_t GetYScrollOffset(const Rect& childRect);
    void OnChildChanged() override;
    bool DragReboundAnimator();

    static constexpr uint8_t DEFAULT_BAR_WIDTH = 5;
    static constexpr uint8_t MIN_BAR_MULTIPLE = 2;
    static constexpr uint8_t DEFAULT_MIN_BAR_LEN = DEFAULT_BAR_WIDTH * MIN_BAR_MULTIPLE;
    UIView xSlider_;
    UIView ySlider_;
    Point xSliderPos_;
    Point ySliderPos_;
    int16_t scrollBarWidth_;
    bool xScrollMovable_;
    bool yScrollMovable_;
    bool xScrollable_;
    bool yScrollable_;
    int16_t minScrollBarLen_;
    OnScrollListener* scrollListener_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_SCROLL_VIEW_H
