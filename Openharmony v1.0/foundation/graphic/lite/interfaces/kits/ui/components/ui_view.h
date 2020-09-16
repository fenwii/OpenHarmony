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
 * @file ui_view.h
 *
 * @brief Declares the base class of a view, providing basic view attributes and operations. All views are derived
 *        from this class.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_VIEW_H
#define GRAPHIC_LITE_UI_VIEW_H

#include "color.h"
#include "events/cancel_event.h"
#include "events/click_event.h"
#include "events/drag_event.h"
#include "events/event.h"
#include "events/long_press_event.h"
#include "events/press_event.h"
#include "events/release_event.h"
#include "geometry2d.h"
#include "heap_base.h"
#include "style.h"
#include "transform.h"

namespace OHOS {
/* Enumerates view types. */
enum UIViewType : uint8_t {
    UI_ROOT_VIEW = 0,
    UI_VIEW_GROUP,
    UI_LABEL,
    UI_ARC_LABEL,
    UI_LABEL_BUTTON,
    UI_CHECK_BOX,
    UI_TOGGLE_BUTTON,
    UI_RADIO_BUTTON,
    UI_IMAGE_VIEW,
    UI_BOX_PROGRESS,
    UI_SLIDER,
    UI_CIRCLE_PROGRESS,
    UI_SCROLL_VIEW,
    UI_LIST,
    UI_DIGITAL_CLOCK,
    UI_ANALOG_CLOCK,
    UI_PICKER,
    UI_SWIPE_VIEW,
    UI_TIME_PICKER,
    UI_ABSTRACT_CLOCK,
    UI_ABSTRACT_PROGRESS,
    UI_ABSTRACT_SCROLL,
    UI_AXIS,
    UI_BUTTON,
    UI_CANVAS,
    UI_CHART,
    UI_IMAGE_ANIMATOR_VIEW,
    UI_REPEAT_BUTTON,
    UI_TEXTURE_MAPPER,
    UI_DIALOG,
    UI_NUMBER_MAX
};

#if ENABLE_DEBUG
const char* const VIEW_TYPE_STRING[UI_NUMBER_MAX] = {
    "RootView",
    "UIViewGroup",
    "UILabel",
    "UIArcLabel",
    "UILabelButton",
    "UICheckBox",
    "UIToggleButton",
    "UIRadioButton",
    "UIImageView",
    "UIBoxProgress",
    "UISlider",
    "UICircleProgress",
    "UIScrollView",
    "UIList",
    "UIDigitalClock",
    "UIAnalogClock",
    "UIPicker",
    "UISwipeView",
    "UITimePicker",
    "UIAbstractClock",
    "UIAbstractProgress",
    "UIAbstractScroll",
    "UIAxis",
    "UIButton",
    "UICanvas",
    "UIChart",
    "UIImageAnimatorView",
    "UIRepeatButton",
    "UITextureMapper",
    "UIDialog",
};
#endif // ENABLE_DEBUG

/**
 * @brief Defines the base class of a view, providing basic view attributes and operations. All views are derived
 *        from this class.
 *
 * @since 1.0
 * @version 1.0
 */
class UIView : public HeapBase {
public:
    /**
     * @brief Defines a click event listener. You need to register this listener with the view to listen to
     *        click events.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnClickListener : public HeapBase {
    public:
        /**
         * @brief Called when a view is clicked.
         * @param view Indicates the view clicked.
         * @param event Indicates the click event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnClick(UIView& view, const ClickEvent& event)
        {
            return true;
        }

        /**
         * @brief A destructor used to delete the <b>OnClickListener</b> instance.
         * @since 1.0
         * @version 1.0
         */
        virtual ~OnClickListener() {}
    };

    /**
     * @brief Defines a long-press event listener. You need to register this listener with the view to listen to
     *        long-press events.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnLongPressListener : public HeapBase {
    public:
        /**
         * @brief Called when a view is long pressed.
         * @param view Indicates the view long pressed.
         * @param event Indicates the long-press event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnLongPress(UIView& view, const LongPressEvent& event)
        {
            return true;
        }

        /**
         * @brief A destructor used to delete the <b>OnLongPressListener</b> instance.
         * @since 1.0
         * @version 1.0
         */
        virtual ~OnLongPressListener() {}
    };

    /**
     * @brief Defines a drag event listener. You need to register this listener with the view to listen to drag events.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnDragListener : public HeapBase {
    public:
        /**
         * @brief Called when a view starts to drag.
         * @param view Indicates the view dragged.
         * @param event Indicates the drag event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnDragStart(UIView& view, const DragEvent& event)
        {
            return true;
        }

        /**
         * @brief Called when a view is being dragged.
         * @param view Indicates the view dragged.
         * @param event Indicates the drag event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnDrag(UIView& view, const DragEvent& event)
        {
            return true;
        }

        /**
         * @brief Called when a view stops dragging.
         * @param view Indicates the view dragged.
         * @param event Indicates the drag event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnDragEnd(UIView& view, const DragEvent& event)
        {
            return true;
        }

        /**
         * @brief A destructor used to delete the <b>OnDragListener</b> instance.
         * @since 1.0
         * @version 1.0
         */
        virtual ~OnDragListener() {}
    };

    /**
     * @brief Defines a touch event listener. You need to register this listener with the view to listen to touch
     *        events.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnTouchListener : public HeapBase {
    public:
        /**
         * @brief Called when a view is pressed.
         * @param view Indicates the view pressed.
         * @param event Indicates the press event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnPress(UIView& view, const PressEvent& event)
        {
            return true;
        }

        /**
         * @brief Called when a view is released.
         * @param view Indicates the view released.
         * @param event Indicates the release event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnRelease(UIView& view, const ReleaseEvent& event)
        {
            return true;
        }

        /**
         * @brief Called when a click event on a view is canceled.
         * @param view Indicates the view on which a click event is canceled.
         * @param event Indicates the cancel event.
         * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
         *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
         *         it is transferred to the parent view after local processing is complete.)
         * @since 1.0
         * @version 1.0
         */
        virtual bool OnCancel(UIView& view, const CancelEvent& event)
        {
            return true;
        }

        /**
         * @brief A destructor used to delete the <b>OnTouchListener</b> instance.
         * @since 1.0
         * @version 1.0
         */
        virtual ~OnTouchListener() {}
    };

    /**
     * @brief A default constructor used to create an <b>UIView</b> instance.
     * @since 1.0
     * @version 1.0
     */
    UIView();

    /**
     * @brief A constructor used to create an <b>UIView</b> instance.
     * @param id Indicates the pointer to the view ID.
     * @since 1.0
     * @version 1.0
     */
    UIView(const char* id) : UIView()
    {
        id_ = id;
    }

    /**
     * @brief A destructor used to delete the <b>UIView</b> instance.
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIView();

    /**
     * @brief Called before a view is drawn. This function is used to check whether the parent view of this view
     *        needs to be redrawn so as to optimize the drawing process.
     * @param invalidatedArea Indicates the area to draw.
     * @return Returns <b>true</b> if the parent view needs to be redrawn; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual bool OnPreDraw(const Rect& invalidatedArea);

    /**
     * @brief Called when a view is drawn.
     * @param invalidatedArea Indicates the area to draw.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnDraw(const Rect& invalidatedArea);

    /**
     * @brief Called after a view is drawn.
     * @param invalidatedArea Indicates the area in which the view is drawn.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnPostDraw(const Rect& invalidatedArea) {}

    /**
     * @brief Remeasures the view size.
     * @since 1.0
     * @version 1.0
     */
    virtual void ReMeasure() {}

    /**
     * @brief Refreshes the invalidated area of the view.
     * @since 1.0
     * @version 1.0
     */
    void Invalidate();

    /**
     * @brief Refreshes a view in a specified invalidated area.
     * @param invalidatedArea Indicates the area to refresh.
     * @since 1.0
     * @version 1.0
     */
    void InvalidateRect(const Rect& invalidatedArea);

    /**
     * @brief Called when the view is long pressed.
     * @param event Indicates the long-press event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual bool OnLongPressEvent(const LongPressEvent& event)
    {
        if (onLongPressListener_ != nullptr) {
            onLongPressListener_->OnLongPress(*this, event);
            return false;
        }
        return true;
    }

    /**
     * @brief Called when the view starts to drag.
     * @param event Indicates the drag event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual bool OnDragStartEvent(const DragEvent& event)
    {
        if (onDragListener_ != nullptr) {
            onDragListener_->OnDragStart(*this, event);
        }
        return isIntercept_;
    }

    /**
     * @brief Called when the view is being dragged.
     * @param event Indicates the drag event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual bool OnDragEvent(const DragEvent& event)
    {
        if (onDragListener_ != nullptr) {
            onDragListener_->OnDrag(*this, event);
        }
        return isIntercept_;
    }

    /**
     * @brief Called when the view stops dragging.
     * @param event Indicates the drag event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual bool OnDragEndEvent(const DragEvent& event)
    {
        if (onDragListener_ != nullptr) {
            onDragListener_->OnDragEnd(*this, event);
        }
        return isIntercept_;
    }

    /**
    * @brief Called when the view is clicked.
    * @param event Indicates the click event.
    * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
    *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
    *         it is transferred to the parent view after local processing is complete.)
    * @since 1.0
    * @version 1.0
    */
    virtual void OnClickEvent(const ClickEvent& event)
    {
        if (onClickListener_ != nullptr) {
            onClickListener_->OnClick(*this, event);
        }
    }

    /**
     * @brief Called when the view is pressed.
     * @param event Indicates the press event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual void OnPressEvent(const PressEvent& event)
    {
        if (onTouchListener_ != nullptr) {
            onTouchListener_->OnPress(*this, event);
        }
    }

    /**
     * @brief Called when the view is released.
     * @param event Indicates the release event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual void OnReleaseEvent(const ReleaseEvent& event)
    {
        if (onTouchListener_ != nullptr) {
            onTouchListener_->OnRelease(*this, event);
        }
    }

    /**
     * @brief Called when a click event on the view is canceled.
     * @param event Indicates the cancel event.
     * @return Returns <b>true</b> if the event is consumed; returns <b>false</b> otherwise.
     *         (If an event is consumed, it is not transferred to the parent view. If an event is not consumed,
     *         it is transferred to the parent view after local processing is complete.)
     * @since 1.0
     * @version 1.0
     */
    virtual void OnCancelEvent(const CancelEvent& event)
    {
        if (onTouchListener_ != nullptr) {
            onTouchListener_->OnCancel(*this, event);
        }
    }

    /**
     * @brief Sets a drag event listener for the view.
     * @param onDragListener Indicates the pointer to the drag event listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnDragListener(OnDragListener* onDragListener)
    {
        onDragListener_ = onDragListener;
    }

    /**
     * @brief Obtains the drag event listener for the view.
     * @return Returns the drag event listener.
     * @since 1.0
     * @version 1.0
     */
    OnDragListener*& GetOnDragListener()
    {
        return onDragListener_;
    }

    /**
     * @brief Sets a click event listener for the view.
     * @param onClickListener Indicates the pointer to the click event listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnClickListener(OnClickListener* onClickListener)
    {
        onClickListener_ = onClickListener;
    }

    /**
     * @brief Obtains the click event listener for the view.
     * @return Returns the click event listener.
     * @since 1.0
     * @version 1.0
     */
    OnClickListener*& GetOnClickListener()
    {
        return onClickListener_;
    }

    /**
     * @brief Sets a long-press event listener for the view.
     * @param onLongPressListener Indicates the pointer to the long-press event listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnLongPressListener(OnLongPressListener* onLongPressListener)
    {
        onLongPressListener_ = onLongPressListener;
    }

    /**
     * @brief Obtains the long-press event listener for the view.
     * @return Returns the long-press event listener.
     * @since 1.0
     * @version 1.0
     */
    OnLongPressListener*& GetOnLongPressListener()
    {
        return onLongPressListener_;
    }

    /**
     * @brief Sets a touch event listener for the view.
     * @param onTouchListener Indicates the pointer to the touch event listener to set.
     * @since 1.0
     * @version 1.0
     */
    void SetOnTouchListener(OnTouchListener* onTouchListener)
    {
        onTouchListener_ = onTouchListener;
    }

    /**
     * @brief Obtains the touch event listener for the view.
     * @return Returns the touch event listener.
     * @since 1.0
     * @version 1.0
     */
    OnTouchListener*& GetTouchListener()
    {
        return onTouchListener_;
    }

    /**
     * @brief Obtains the top-level view based on specified coordinates.
     * @param point Indicates the coordinates to specify.
     * @param last Indicates the double pointer to the view that contains the specified coordinates.
     * @since 1.0
     * @version 1.0
     */
    virtual void GetTargetView(const Point& point, UIView** last);

    /**
     * @brief Sets the parent view for the view.
     * @param parent Indicates the pointer to the parent view to set.
     * @since 1.0
     * @version 1.0
     */
    void SetParent(UIView* parent)
    {
        parent_ = parent;
    }

    /**
     * @brief Obtains the parent view of the view.
     * @return Returns the pointer to the parent view.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetParent() const
    {
        return parent_;
    }

    /**
     * @brief Sets the next sibling view for the view.
     * @param sibling Indicates the pointer to the next sibling view to set.
     * @since 1.0
     * @version 1.0
     */
    void SetNextSibling(UIView* sibling)
    {
        nextSibling_ = sibling;
    }

    /**
     * @brief Obtains the next sibling view of the view.
     * @return Returns the pointer to the next sibling view.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetNextSibling() const
    {
        return nextSibling_;
    }

    /**
     * @brief Sets whether the view is visible.
     * @param visible Specifies whether to set the view visible. Value <b>true</b> means to set the view visible,
     *                and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetVisible(bool visible)
    {
        if (visible_ != visible) {
            visible_ = visible;
            needRedraw_ = true;
        }
    }

    /**
     * @brief Checks whether the view is visible.
     * @return Returns <b>true</b> if the view is visible; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsVisible() const
    {
        return visible_;
    }

    /**
     * @brief Sets whether the view is touchable.
     * @param touchable Specifies whether to set the view touchable. Value <b>true</b> means to set the view touchable,
     *                  and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    void SetTouchable(bool touch)
    {
        touchable_ = touch;
    }

    /**
     * @brief Checks whether the view is touchable.
     * @return Returns <b>true</b> if the view is touchable; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsTouchable() const
    {
        return touchable_;
    }

    /**
     * @brief Sets whether the view is draggable.
     * @param draggable Specifies whether to set the view draggable. Value <b>true</b> means to set the view draggable,
     *                  and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    void SetDraggable(bool draggable)
    {
        draggable_ = draggable;
        dragParentInstead_ = !draggable;
    }

    /**
     * @brief Checks whether the view is draggable.
     * @return Returns <b>true</b> if the view is draggable; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsDraggable() const
    {
        return draggable_;
    }

    /**
     * @brief Sets whether to transfer the drag event to the parent view for processing when the view is being dragged.
     * @param dragParentInstead Specifies whether to transfer the event to the parent view for processing.
     *                          Value <b>true</b> means to transfer the event to the parent view for processing,
     *                          and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    void SetDragParentInstead(bool dragParentInstead)
    {
        dragParentInstead_ = dragParentInstead;
    }

    /**
     * @brief Obtains whether the view transfers a drag event to the parent view for processing.
     * @return Returns <b>true</b> if the view transfers the event to the parent view for processing;
     *         returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsDragParentInstead() const
    {
        return dragParentInstead_;
    }

    /**
     * @brief Obtains the absolute rectangle area of the view. When the view has deformation such as rotation,
     *        the rectangle area is the intersection set of the absolute rectangle area and deformation matrix.
     * @return Returns the absolute rectangle area.
     * @since 1.0
     * @version 1.0
     */
    Rect GetRect() const;

    /**
     * @brief Obtains the visible absolute rectangle area of the view.
     * @return Returns the visible absolute rectangle area.
     * @since 1.0
     * @version 1.0
     */
    Rect GetVisibleRect() const;

    /**
     * @brief Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view
     *        can be displayed. Generally, the valid area is the same as the visible view area, but they may be
     *        different in the grid layout.
     * @return Returns the valid absolute rectangle area.
     * @since 1.0
     * @version 1.0
     */
    Rect GetMaskedRect() const;

    /**
     * @brief Obtains the absolute rectangle area of the view.
     * @return Returns the absolute rectangle area.
     * @since 1.0
     * @version 1.0
     */
    Rect GetOrigRect() const;

    /**
     * @brief Obtains the content of the absolute rectangle area of the view. This area excludes padding.
     * @return Returns the content of the absolute rectangle area.
     * @since 1.0
     * @version 1.0
     */
    virtual Rect GetContentRect();

    /**
     * @brief Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area
     *        relative to the coordinates of the parent view.
     * @return Returns the rectangle area relative to the parent view.
     * @since 1.0
     * @version 1.0
     */
    Rect GetRelativeRect() const
    {
        return rect_;
    }

    /**
     * @brief Adjusts the size of the visible area. This operation may affect the final display size.
     * @param x Indicates the new x-coordinate.
     * @param y Indicates the new y-coordinate.
     * @param width Indicates the new width.
     * @param height Indicates the new height.
     * @since 1.0
     * @version 1.0
     */
    void ResizeVisibleArea(int16_t x, int16_t y, int16_t width, int16_t height)
    {
        if (visibleRect_ == nullptr) {
            visibleRect_ = new Rect();
        }
        visibleRect_->SetWidth(width);
        visibleRect_->SetHeight(height);
        visibleRect_->SetPosition(x, y);
    }

    /**
     * @brief Sets the width for the view.
     * @param width Indicates the width to set.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetWidth(int16_t width)
    {
        if (GetWidth() != width) {
            int16_t newWidth = width + style_->paddingLeft_ + style_->paddingRight_ +
                              (style_->borderWidth_ * 2); /* 2: left and right border */
            rect_.SetWidth(newWidth);
        }
    }

    /**
     * @brief Obtains the width for the view.
     * @return Returns the view width.
     * @since 1.0
     * @version 1.0
     */
    virtual int16_t GetWidth()
    {
        return rect_.GetWidth() - (style_->paddingLeft_ + style_->paddingRight_) -
            (style_->borderWidth_ * 2); /* 2: left and right border */
    }

    /**
     * @brief Sets the height for the view.
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetHeight(int16_t height)
    {
        if (GetHeight() != height) {
            int16_t newHeight = height + style_->paddingTop_ + style_->paddingBottom_ +
                               (style_->borderWidth_ * 2); /* 2: top and bottom border */
            rect_.SetHeight(newHeight);
        }
    }

    /**
     * @brief Obtains the height for the view.
     * @return Returns the view height.
     * @since 1.0
     * @version 1.0
     */
    virtual int16_t GetHeight()
    {
        return rect_.GetHeight() - (style_->paddingTop_ + style_->paddingBottom_) -
            (style_->borderWidth_ * 2); /* 2: top and bottom border */
    }

    /**
     * @brief Adjusts the size of the view.
     * @param width Indicates the new width.
     * @param height Indicates the new height.
     * @since 1.0
     * @version 1.0
     */
    virtual void Resize(int16_t width, int16_t height)
    {
        SetWidth(width);
        SetHeight(height);
    }

    /**
    * @brief Sets the x-coordinate for the view.
    * @param x Indicates the x-coordinate to set.
    * @since 1.0
    * @version 1.0
    */
    virtual void SetX(int16_t x)
    {
        rect_.SetX(x);
    }

    /**
     * @brief Obtains the x-coordinate for the view.
     * @return Returns the x-coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetX() const
    {
        return rect_.GetX();
    }

    /**
     * @brief Sets the y-coordinate for the view.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetY(int16_t y)
    {
        rect_.SetY(y);
    }

    /**
     * @brief Obtains the y-coordinate for the view.
     * @return Returns the y-coordinate.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetY() const
    {
        return rect_.GetY();
    }

    /**
     * @brief Sets the position for the view.
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetPosition(int16_t x, int16_t y)
    {
        rect_.SetPosition(x, y);
    }

    /**
     * @brief Adjusts the position and size of the view.
     * @param x Indicates the new x-coordinate.
     * @param y Indicates the new y-coordinate.
     * @param width Indicates the new width.
     * @param height Indicates the new height.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetPosition(int16_t x, int16_t y, int16_t width, int16_t height)
    {
        SetPosition(x, y);
        SetWidth(width);
        SetHeight(height);
    }

    /**
     * @brief Checks whether the view is a container view.
     * @return Returns <b>true</b> if the view is a container view; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsViewGroup() const
    {
        return isViewGroup_;
    }

    /**
     * @brief Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to
     *        the parent view after local processing.
     * @param isIntercept Specifies whether to intercept the drag event. Value <b>true</b> means to intercept the drag
     *                    event, and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    void SetIntercept(bool isIntercept)
    {
        isIntercept_ = isIntercept;
    }

    /**
     * @brief Sets the affine transformation matrix.
     * @param transMap Indicates the transformation matrix.
     * @since 1.0
     * @version 1.0
     */
    void SetTransformMap(const TransformMap& transMap);

    /**
     * @brief Obtains an affine transformation matrix.
     * @return Returns the transform matrix.
     * @since 1.0
     * @version 1.0
     */
    TransformMap& GetTransformMap()
    {
        if (transMap_ == nullptr) {
            transMap_ = new TransformMap();
        }
        return *transMap_;
    }

    /**
     * @brief Obtains the child view of a specified ID.
     * @return Returns the pointer to the child view.
     * @since 1.0
     * @version 1.0
     */
    virtual UIView* GetChildById(const char* id) const
    {
        return nullptr;
    }

    /**
     * @brief Sets the view ID.
     * @param id Indicates the pointer to the view ID.
     * @since 1.0
     * @version 1.0
     */
    void SetViewId(const char* id)
    {
        id_ = id;
    }

    /**
     * @brief Obtains the view ID.
     * @return Returns the pointer to the view ID.
     * @since 1.0
     * @version 1.0
     */
    const char* GetViewId() const
    {
        return id_;
    }

    /**
     * @brief Sets the view index.
     * @param index Indicates the view index to set.
     * @since 1.0
     * @version 1.0
     */
    void SetViewIndex(int16_t index)
    {
        index_ = index;
    }

    /**
     * @brief Obtains the view index.
     * @return Returns the view index.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetViewIndex() const
    {
        return index_;
    }

    /**
     * @brief Obtains the view type.
     * @return Returns the view type.
     * @since 1.0
     * @version 1.0
     */
    virtual UIViewType GetViewType() const
    {
        return UI_NUMBER_MAX;
    }

    /**
     * @brief Lays out all child views according to the preset arrangement mode.
     * @param needInvalidate Specifies whether to refresh the invalidated area after the layout is complete.
     *                       Value <b>true</b> means to refresh the invalidated area after the layout is complete,
     *                       and <b>false</b> means the opposite.
     * @since 1.0
     * @version 1.0
     */
    virtual void LayoutChildren(bool neeInvalidate = false) {}

    /**
     * @brief Lays out the view in the center of the parent view.
     * @param xOffset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *                the offset to the right, and a negative number indicates the offset to the left.
     * @param yOffset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
     *                the offset to the bottom, and a negative number indicates the offset to the top.
     * @since 1.0
     * @version 1.0
     */
    void LayoutCenterOfParent(int16_t xOffSet = 0, int16_t yOffset = 0);

    /**
     * @brief Lays out the view on the left of the parent view.
     * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *               the offset to the right, and a negative number indicates the offset to the left.
     * @since 1.0
     * @version 1.0
     */
    void LayoutLeftOfParent(int16_t offset = 0);

    /**
    * @brief Lays out the view on the right of the parent view.
    * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
    *               the offset to the left, and a negative number indicates the offset to the right.
    * @since 1.0
    * @version 1.0
    */
    void LayoutRightOfParent(int16_t offset = 0);

    /**
    * @brief Lays out the view on the top of the parent view.
    * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
    *               the offset to the bottom, and a negative number indicates the offset to the top.
    * @since 1.0
    * @version 1.0
    */
    void LayoutTopOfParent(int16_t offset = 0);

    /**
     * @brief Lays out the view on the bottom of the parent view.
     * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
     *               the offset to the top, and a negative number indicates the offset to the bottom.
     * @since 1.0
     * @version 1.0
     */
    void LayoutBottomOfParent(int16_t offset = 0);

    /**
     * @brief Aligns the view with the left of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *               the offset to the right, and a negative number indicates the offset to the left.
     * @since 1.0
     * @version 1.0
     */
    void AlignLeftToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Aligns the view with the right of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *               the offset to the left, and a negative number indicates the offset to the right.
     * @since 1.0
     * @version 1.0
     */
    void AlignRightToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Aligns the view with the top of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
     *               the offset to the bottom, and a negative number indicates the offset to the top.
     * @since 1.0
     * @version 1.0
     */
    void AlignTopToSibling(const char* id, int16_t offset = 0);

    /**
    * @brief Aligns the view with the bottom of a sibling view.
    * @param id Indicates the pointer to the ID of the sibling view.
    * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
    *               the offset to the top, and a negative number indicates the offset to the bottom.
    * @since 1.0
    * @version 1.0
    */
    void AlignBottomToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Aligns the view with the center of a sibling view in the x-axis.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *               the offset to the right, and a negative number indicates the offset to the left.
     * @since 1.0
     * @version 1.0
     */
    void AlignHorCenterToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Aligns the view with the center of a sibling view in the y-axis.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
     *               the offset to the bottom, and a negative number indicates the offset to the top.
     * @since 1.0
     * @version 1.0
     */
    void AlignVerCenterToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Lays out the view on the left of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *               the offset to the left, and a negative number indicates the offset to the right.
     * @since 1.0
     * @version 1.0
     */
    void LayoutLeftToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Lays out the view on the right of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the x-axis after the view is placed. A positive number indicates
     *               the offset to the right, and a negative number indicates the offset to the left.
     * @since 1.0
     * @version 1.0
     */
    void LayoutRightToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Lays out the view on the above of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
     *               the offset to the top, and a negative number indicates the offset to the bottom.
     * @since 1.0
     * @version 1.0
     */
    void LayoutTopToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Lays out the view on the below of a sibling view.
     * @param id Indicates the pointer to the ID of the sibling view.
     * @param offset Indicates the offset added to the y-axis after the view is placed. A positive number indicates
     *               the offset to the bottom, and a negative number indicates the offset to the top.
     * @since 1.0
     * @version 1.0
     */
    void LayoutBottomToSibling(const char* id, int16_t offset = 0);

    /**
     * @brief Sets the view style.
     * @param style Indicates the view style.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetStyle(Style& style);

    /**
     * @brief Sets a style.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetStyle(uint8_t key, int64_t value);

    /**
     * @brief Obtains the value of a style.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    virtual int64_t GetStyle(uint8_t key) const
    {
        return style_->GetStyle(key);
    }

    /**
     * @brief Obtains the view style. This function applies to scenarios where the style does not need to be modified,
     *        which saves memory.
     * @return Returns the view style.
     * @since 1.0
     * @version 1.0
     */
    const Style& GetStyleConst() const
    {
        return *style_;
    }

    void SetOpaScale(uint8_t opaScale)
    {
        opaScale_ = opaScale;
    }

    uint8_t GetOpaScale() const
    {
        return opaScale_;
    }

protected:
    bool touchable_ : 1;
    bool visible_ : 1;
    bool draggable_ : 1;
    bool dragParentInstead_ : 1;
    bool isViewGroup_ : 1;
    bool needRedraw_ : 1;
    bool styleAllocFlag_ : 1;
    bool isIntercept_ : 1;
    uint8_t opaScale_;
    int16_t index_;
    const char* id_;
    UIView* parent_;
    UIView* nextSibling_;
    Style* style_;
    TransformMap* transMap_;
    OnClickListener* onClickListener_;
    OnLongPressListener* onLongPressListener_;
    OnDragListener* onDragListener_;
    OnTouchListener* onTouchListener_;
    void AddMeasureView();
    void DeleteMeasureView();

private:
    Rect rect_;
    Rect* visibleRect_;
    void SetupThemeStyles();
};
}
#endif // GRAPHIC_LITE_UI_VIEW_H

