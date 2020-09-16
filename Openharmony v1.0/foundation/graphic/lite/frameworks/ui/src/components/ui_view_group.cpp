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

#include "components/ui_view_group.h"
#include <cstring>

namespace OHOS {
UIViewGroup::UIViewGroup()
    : childrenHead_(nullptr), childrenTail_(nullptr), childrenNum_(0),
      isDragging_(false), disallowIntercept_(false), isAutoSize_(false)
{
    isViewGroup_ = true;
}

UIViewGroup::~UIViewGroup() {}

void UIViewGroup::Add(UIView* view)
{
    if ((view == this) || (view == nullptr)) {
        return;
    }
    if (childrenHead_ == nullptr) {
        childrenHead_ = view;
    } else {
        UIView* head = childrenHead_;
        while (head != nullptr) {
            if (view == head ||
                (view->GetViewId() != nullptr &&
                head->GetViewId() != nullptr &&
                !strcmp(view->GetViewId(), head->GetViewId()))) {
                return;
            }
            head = head->GetNextSibling();
        }
        childrenTail_->SetNextSibling(view);
    }
    view->SetParent(this);
    view->SetNextSibling(nullptr);
    childrenTail_ = view;
    childrenNum_++;
    if (isAutoSize_) {
        AutoResize();
    }
    OnChildChanged();
}

void UIViewGroup::Insert(UIView* prevView, UIView* insertView)
{
    if (insertView == nullptr) {
        return;
    }
    if (childrenHead_ == nullptr) {
        Add(insertView);
        return;
    }
    UIView* head = childrenHead_;
    while (head != nullptr) {
        if (insertView == head ||
            (insertView->GetViewId() != nullptr &&
            head->GetViewId() != nullptr &&
            !strcmp(insertView->GetViewId(), head->GetViewId()))) {
            return;
        }
        head = head->GetNextSibling();
    }
    if (prevView == nullptr) {
        insertView->SetNextSibling(childrenHead_);
        insertView->SetParent(this);
        childrenHead_ = insertView;
    } else {
        UIView* nextView = prevView->GetNextSibling();
        prevView->SetNextSibling(insertView);
        insertView->SetNextSibling(nextView);
        insertView->SetParent(this);
    }
    if (childrenTail_ == prevView) {
        childrenTail_ = insertView;
    }
    childrenNum_++;
    if (isAutoSize_) {
        AutoResize();
    }
    OnChildChanged();
}

void UIViewGroup::Remove(UIView* view)
{
    if (childrenHead_ == nullptr || view == nullptr) {
        return;
    }
    if (childrenHead_ == view) {
        childrenHead_ = childrenHead_->GetNextSibling();
        view->SetParent(nullptr);
        view->SetNextSibling(nullptr);
        if (childrenTail_ == view) {
            childrenTail_ = nullptr;
        }
        childrenNum_--;
        OnChildChanged();
        return;
    }
    UIView* node = childrenHead_;
    while (node->GetNextSibling() != nullptr) {
        if (node->GetNextSibling() == view) {
            node->SetNextSibling(view->GetNextSibling());
            view->SetParent(nullptr);
            view->SetNextSibling(nullptr);
            if (childrenTail_ == view) {
                childrenTail_ = node;
            }
            childrenNum_--;
            OnChildChanged();
            return;
        }
        node = node->GetNextSibling();
    }
}

void UIViewGroup::RemoveAll()
{
    UIView* node = childrenHead_;
    childrenHead_ = nullptr;
    childrenTail_ = nullptr;
    childrenNum_ = 0;
    UIView* tmp = nullptr;
    while (node != nullptr) {
        tmp = node;
        node = node->GetNextSibling();
        tmp->SetParent(nullptr);
        tmp->SetNextSibling(nullptr);
    }
    OnChildChanged();
}

void UIViewGroup::GetTargetView(const Point& point, UIView** last)
{
    if (last == nullptr) {
        return;
    }

    Rect rect = GetRect();
    if (disallowIntercept_) {
        *last = nullptr;
        return;
    }
    if (!rect.IsContains(point)) {
        return;
    }
    if (!visible_) {
        return;
    }
    if (touchable_) {
        *last = this;
    }
    if (isDragging_) {
        return;
    }
    UIView* view = childrenHead_;
    while (view != nullptr) {
        if (!view->IsViewGroup()) {
            Rect rect = view->GetRect();
            if (rect.IsContains(point)) {
                view->GetTargetView(point, last);
            }
        } else {
            UIViewGroup* viewGroup = static_cast<UIViewGroup*>(view);
            viewGroup->GetTargetView(point, last);
        }
        view = view->GetNextSibling();
    }
}

Rect UIViewGroup::GetAllChildRelativeRect() const
{
    Rect rect;
    UIView* view = childrenHead_;
    if (view != nullptr) {
        rect = view->GetRelativeRect();
        view = view->GetNextSibling();
    }
    while (view != nullptr) {
        Rect rectChild = view->GetRelativeRect();
        rect.Join(rect, rectChild);
        view = view->GetNextSibling();
    }
    return rect;
}

UIView* UIViewGroup::GetChildById(const char* id) const
{
    if (id == nullptr) {
        return nullptr;
    }
    UIView* child = childrenHead_;
    if (child == nullptr) {
        return nullptr;
    }
    while (child != nullptr) {
        if (child->GetViewId() != nullptr && !strcmp(child->GetViewId(), id)) {
            return child;
        }
        child = child->GetNextSibling();
    }
    return nullptr;
}

void UIViewGroup::MoveChildByOffset(int16_t xOffset, int16_t yOffset)
{
    UIView* view = childrenHead_;
    int16_t x;
    int16_t y;
    while (view != nullptr) {
        x = view->GetX() + xOffset;
        y = view->GetY() + yOffset;
        view->SetPosition(x, y);
        view = view->GetNextSibling();
    }
}

void UIViewGroup::AutoResize()
{
    Rect rect = GetAllChildRelativeRect();
    SetWidth(rect.GetWidth() + rect.GetLeft());
    SetHeight(rect.GetHeight() + rect.GetTop());
}
} // namespace OHOS
