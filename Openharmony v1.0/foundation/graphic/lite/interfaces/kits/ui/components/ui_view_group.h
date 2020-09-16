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
 * @file ui_view_group.h
 *
 * @brief Declares a view group.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_VIEW_GROUP_H
#define GRAPHIC_LITE_UI_VIEW_GROUP_H

#include "components/ui_view.h"

namespace OHOS {
/**
 * @brief Represents a view group that consists of its child views.
 *
 * The child views can be added to, inserted in, and removed from the view group.
 * Child views that are added later are displayed at the upper layer of this view group.
 * All child views are stored in a linked list.
 *
 * @since 1.0
 * @version 1.0
 */
class UIViewGroup : public UIView {
public:
    /**
     * @brief A default constructor used to create a <b>UIViewGroup</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIViewGroup();

    /**
     * @brief A destructor used to delete the <b>UIViewGroup</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIViewGroup();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_VIEW_GROUP</b>, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_VIEW_GROUP;
    }

    /**
     * @brief Adds a child view.
     *
     * @param view Indicates the pointer to the child view to add.
     * @since 1.0
     * @version 1.0
     */
    virtual void Add(UIView* view);

    /**
     * @brief Inserts a new child view behind the current one.
     *
     * @param prevView Indicates the pointer to the current child view, previous to the new child view to insert.
     * @param view Indicates the pointer to the new child view to insert.
     * @since 1.0
     * @version 1.0
     */
    virtual void Insert(UIView* prevView, UIView* insertView);

    /**
     * @brief Removes a child view.
     *
     * @param view Indicates the pointer to the child view to remove.
     * @since 1.0
     * @version 1.0
     */
    virtual void Remove(UIView* view);

    /**
     * @brief Removes all child views.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void RemoveAll();

    /**
     * @brief Obtains the target child view that is visible and can respond to touch events based on given coordinates.
     *
     * @param point Indicates the given coordinates.
     * @param last Indicates the double pointer to the target view. <b>nullptr</b> indicates that the target
     *             view is not available.
     * @since 1.0
     * @version 1.0
     */
    virtual void GetTargetView(const Point& point, UIView** last) override;

    /**
     * @brief Moves all child views.
     *
     * @param x Indicates the offset distance by which this view group is moved on the x-axis.
     * @param y Indicates the offset distance by which this view group is moved on the y-axis.
     * @since 1.0
     * @version 1.0
     */
    virtual void MoveChildByOffset(int16_t x, int16_t y);

    /**
     * @brief Obtains the first child view in this view group.
     *
     * @return Returns the first child view.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetChildrenHead() const
    {
        return childrenHead_;
    }

    /**
     * @brief Obtains the last child view in this view group.
     *
     * @return Returns the last child view.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetChildrenTail() const
    {
        return childrenTail_;
    }

    /**
     * @brief Sets whether this view group is intercepted upon touch events.
     *
     * @param flag Specifies whether this view group is intercepted upon touch events. <b>true</b> indicates that
     *             this view group is intercepted upon touch events, and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetDisallowIntercept(bool flag)
    {
        disallowIntercept_ = flag;
    }

    /**
     * @brief Obtains the target child view with a specified ID.
     *
     * @param id Indicates the pointer to the ID of the target child view.
     * @return Returns the target child view if available; returns <b>nullptr</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetChildById(const char* id) const override;

    /**
     * @brief Sets whether the size of this view group is adaptive to that of all child views.
     *
     * @param state Specifies whether the size of this view group is adaptive to that of all child views.
     *              <b>true</b> indicates automatic adaption is enabled, and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetAutoSize(bool state)
    {
        isAutoSize_ = state;
    }

protected:
    /**
     * @brief Obtains the rectangle area of a new view group after being adaptive to the size of all child views.
     *
     * @return Returns the rectangle area of the new view group.
     * @since 1.0
     * @version 1.0
     */
    Rect GetAllChildRelativeRect() const;

    /**
     * @brief Performs operations needed after a child view is added or removed.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void OnChildChanged() {};

    /**
     * @brief Indicates the pointer to the first child view of this view group.
     */
    UIView* childrenHead_;

    /**
     * @brief Indicates the pointer to the last child view of this view group.
     */
    UIView* childrenTail_;

    /**
     * @brief Represents the number of child views.
     */
    uint16_t childrenNum_;

    /**
     * @brief Specifies the sliding state of this view group.
     */
    bool isDragging_;

    /**
     * @brief Specifies whether this view group is intercepted upon touch events.
     */
    bool disallowIntercept_;

    /**
     * @brief Specifies whether the size of this view group is adaptive to that of all child views.
     */
    bool isAutoSize_;

private:
    void AutoResize();
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_VIEW_GROUP_H
