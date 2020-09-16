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

#include "components/ui_swipe_view.h"

namespace OHOS {
UISwipeView::UISwipeView(uint8_t direction)
    : swipeListener_(nullptr),
      curIndex_(0),
      blankSize_(DEFAULT_BLANK_SIZE),
      curView_(nullptr),
      direction_(direction),
      loop_(false)
{
    AnimatorManager::GetInstance()->Add(&animator_);
    tickTime_ = ANIMATOR_TIME;
    swipeAccCoefficient_ = DRAG_ACC_FACTOR;
}

UISwipeView::~UISwipeView()
{
    AnimatorManager::GetInstance()->Remove(&animator_);
}

void UISwipeView::Add(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    view->SetDragParentInstead(true);
    UIViewGroup::Add(view);
    SortChild();
    Invalidate();
}

void UISwipeView::Insert(UIView* prevView, UIView* insertView)
{
    if (insertView == nullptr) {
        return;
    }
    insertView->SetDragParentInstead(true);
    UIViewGroup::Insert(prevView, insertView);
    SortChild();
    Invalidate();
}

void UISwipeView::Remove(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    UIViewGroup::Remove(view);
    SortChild();
    Invalidate();
}

void UISwipeView::SetCurrentPage(uint16_t index, bool needAnimator)
{
    SwitchToPage(index, needAnimator);
    Invalidate();
}

bool UISwipeView::DragXInner(int16_t distance)
{
    if (distance == 0) {
        return true;
    }
    if (!loop_) {
        if ((distance > 0) && (childrenHead_ != nullptr)) {
            if (childrenHead_->GetX() >= blankSize_) {
                distance = 0;
            } else if (childrenHead_ && childrenHead_->GetX() + distance > blankSize_) {
                distance = blankSize_ - childrenHead_->GetX();
            }
        } else if (childrenTail_ != nullptr) {
            uint16_t width = GetWidth();
            if (childrenTail_->GetRelativeRect().GetRight() <= width - blankSize_) {
                distance = 0;
            } else if (width - (childrenTail_->GetX() + childrenTail_->GetWidth() + distance) > blankSize_) {
                distance = width - blankSize_ - childrenTail_->GetX() - childrenTail_->GetWidth();
            }
        }
    }
    CalculateInvalidate();
    MoveChildByOffset(distance, 0);
    CalculateInvalidate();
    return true;
}

bool UISwipeView::DragYInner(int16_t distance)
{
    if (distance == 0) {
        return true;
    }
    if (!loop_) {
        if ((distance > 0) && (childrenHead_ != nullptr)) {
            if (childrenHead_->GetY() >= blankSize_) {
                distance = 0;
            } else if ((childrenHead_ != nullptr) && (childrenHead_->GetY() + distance > blankSize_)) {
                distance = blankSize_ - childrenHead_->GetY();
            }
        } else if (childrenTail_ != nullptr) {
            uint16_t height = GetHeight();
            if (childrenTail_->GetRelativeRect().GetBottom() <= height - blankSize_) {
                distance = 0;
            } else if (height - (childrenTail_->GetY() + childrenTail_->GetHeight() + distance) > blankSize_) {
                distance = height - blankSize_ - childrenTail_->GetY() - childrenTail_->GetHeight();
            }
        }
    }
    CalculateInvalidate();
    MoveChildByOffset(0, distance);
    CalculateInvalidate();
    return true;
}

bool UISwipeView::OnDragEvent(const DragEvent& event)
{
    UIView* curView = GetViewByIndex(curIndex_);
    if (curView == nullptr) {
        return UIView::OnDragEvent(event);
    }
    if (animator_.GetState() != Animator::STOP) {
        UIAbstractScroll::StopAnimator();
    }

    if (direction_ == HORIZONTAL) {
        DragXInner(event.GetDeltaX());
        RefreshDeltaY(event.GetDeltaX());
    } else {
        DragYInner(event.GetDeltaY());
        RefreshDeltaY(event.GetDeltaY());
    }
    return UIView::OnDragEvent(event);
}

bool UISwipeView::OnDragEndEvent(const DragEvent& event)
{
    int16_t distance = 0;
    if (direction_ == HORIZONTAL) {
        distance = event.GetCurrentPos().x - event.GetPreLastPoint().x;
    } else {
        distance = event.GetCurrentPos().y - event.GetPreLastPoint().y;
    }
    RefreshCurrentView(distance);

    if (curView_ == nullptr) {
        return UIView::OnDragEndEvent(event);
    }

    SwitchToPage(curIndex_);

    Invalidate();
    return UIView::OnDragEndEvent(event);
}

UIView* UISwipeView::GetViewByIndex(uint16_t index) const
{
    UIView* child = childrenHead_;
    while (child != nullptr) {
        if (child->GetViewIndex() == index) {
            return child;
        }
        child = child->GetNextSibling();
    }
    return nullptr;
}

void UISwipeView::SetAnimatorTime(uint16_t time)
{
    tickTime_ = time / DEFAULT_TASK_PERIOD;
    if (tickTime_ == 0) {
        tickTime_ = 1;
    }
    animatorCallback_.SetDragTimes(tickTime_);
}

void UISwipeView::SwitchToPage(int16_t dst, bool needAnimator)
{
    if (isNeedLoop()) {
        dst = (dst + childrenNum_) % childrenNum_;
    } else if (dst < 0) {
        dst = 0;
    } else if (dst >= childrenNum_) {
        dst = childrenNum_ - 1;
    }

    UIView* dstView = GetViewByIndex(dst);
    if (dstView == nullptr) {
        return;
    }
    curIndex_ = dst;
    int16_t xOffset = 0;
    int16_t yOffset = 0;

    if (direction_ == HORIZONTAL) {
        xOffset = (GetWidth() >> 1) - (dstView->GetX() + (dstView->GetWidth() >> 1));
    } else {
        yOffset = (GetHeight() >> 1) - (dstView->GetY() + (dstView->GetHeight() >> 1));
    }

    if (xOffset != 0 || yOffset != 0) {
        if (animator_.GetState() != Animator::STOP) {
            animator_.Stop();
        }
        if (needAnimator) {
            animatorCallback_.SetDragTimes(tickTime_);
            animatorCallback_.SetDragStartValue(0, 0);
            animatorCallback_.SetDragEndValue(xOffset, yOffset);
            animator_.Start();
        } else {
            MoveChildByOffset(xOffset, yOffset);
        }
    }
}

void UISwipeView::StopAnimator()
{
    UIAbstractScroll::StopAnimator();
    if (swipeListener_ != nullptr) {
        swipeListener_->OnSwipe(*this);
    }
}

void UISwipeView::SortChild()
{
    if (childrenHead_ == nullptr) {
        return;
    }
    int16_t index = 0;
    UIView* pre = childrenHead_;
    UIView* next = childrenHead_->GetNextSibling();
    if (direction_ == HORIZONTAL) {
        pre->SetX(0);
    } else {
        pre->SetY(0);
    }
    pre->SetViewIndex(index);
    index++;

    while (next != nullptr) {
        if (direction_ == HORIZONTAL) {
            next->SetX(pre->GetX() + pre->GetWidth());
        } else {
            next->SetY(pre->GetY() + pre->GetHeight());
        }
        pre = next;
        next->SetViewIndex(index);
        next = next->GetNextSibling();
        index++;
    }
    bool tmpLoop = loop_;
    loop_ = false;
    SwitchToPage(curIndex_, false);
    loop_ = tmpLoop;
}

void UISwipeView::RefreshCurrentViewInner(int16_t distance, int16_t (UIView::*pfnGetXOrY)() const,
    int16_t(UIView::*pfnGetWidthOrHeight)())
{
    if (childrenHead_ == nullptr) {
        curIndex_ = 0;
        curView_ = nullptr;
        return;
    }

    curIndex_ = 0;
    curView_ = nullptr;

    uint16_t swipeMid = (this->*pfnGetWidthOrHeight)() >> 1;
    UIView* view = childrenHead_;

    if ((childrenHead_->*pfnGetXOrY)() > swipeMid) {
        curIndex_ = childrenHead_->GetViewIndex();
        curView_ = childrenHead_;
    } else if ((childrenTail_->*pfnGetXOrY)() + (childrenHead_->*pfnGetWidthOrHeight)() < swipeMid) {
        curIndex_ = childrenTail_->GetViewIndex();
        curView_ = childrenTail_;
    } else {
        while (view != nullptr) {
            if (swipeMid >= (view->*pfnGetXOrY)() &&
                swipeMid <= (view->*pfnGetXOrY)() + (view->*pfnGetWidthOrHeight)()) {
                curIndex_ = view->GetViewIndex();
                curView_ = view;
                break;
            }
            view = view->GetNextSibling();
        }
    }
    if (curView_ == nullptr) {
        return;
    }

    int16_t accelerationOffset = GetMaxDeltaY() * GetSwipeACCLevel() / DRAG_ACC_FACTOR;
    if (distance < 0) {
        /*
         * 7, 10 : Check whether the current view is dragged by more than 1/5,
         * that is, the x or y coordinate plus 7/10 width or height.
         */
        if (((curView_->*pfnGetXOrY)() + ((curView_->*pfnGetWidthOrHeight)() >> 1) < swipeMid) &&
            ((curView_->*pfnGetXOrY)() + ((curView_->*pfnGetWidthOrHeight)() * 7 / 10) -
            accelerationOffset < swipeMid)) {
            curIndex_++;
        }
    } else if (distance > 0) {
        /*
         * 3, 10 : Check whether the current view is dragged by more than 1/5,
         * that is, the x or y coordinate plus 3/10 width or height.
         */
        if (((curView_->*pfnGetXOrY)() + ((curView_->*pfnGetWidthOrHeight)() >> 1) > swipeMid) &&
            ((curView_->*pfnGetXOrY)() + ((curView_->*pfnGetWidthOrHeight)() * 3 / 10) +
            accelerationOffset > swipeMid)) {
            curIndex_--;
        }
    }
}

void UISwipeView::RefreshCurrentView(int16_t distance)
{
    if (direction_ == HORIZONTAL) {
        RefreshCurrentViewInner(distance, &UIView::GetX, &UIView::GetWidth);
    } else {
        RefreshCurrentViewInner(distance, &UIView::GetY, &UIView::GetHeight);
    }
}

void UISwipeView::MoveChildByOffset(int16_t xOffset, int16_t yOffset)
{
    UIViewGroup::MoveChildByOffset(xOffset, yOffset);
    if (direction_ == HORIZONTAL) {
        while (isNeedLoop() && childrenHead_->GetX() > 0) {
            MoveLastChildToFirst();
        }
        while (isNeedLoop() && (childrenTail_->GetX() + childrenTail_->GetWidth()) < GetWidth()) {
            MoveFirstChildToLast();
        }
    } else {
        while (isNeedLoop() && childrenHead_->GetY() > 0) {
            MoveLastChildToFirst();
        }
        while (isNeedLoop() && (childrenTail_->GetY() + childrenTail_->GetHeight()) < GetHeight()) {
            MoveFirstChildToLast();
        }
    }
}

bool UISwipeView::isNeedLoop()
{
    if (!loop_ || childrenHead_ == nullptr || childrenTail_ == nullptr) {
        return false;
    }
    Rect childRect = GetAllChildRelativeRect();
    if (direction_ == HORIZONTAL) {
        if (childRect.GetWidth() - childrenHead_->GetWidth() >= GetWidth() &&
            childRect.GetWidth() - childrenTail_->GetWidth() >= GetWidth()) {
            return true;
        }
    } else {
        if (childRect.GetHeight() - childrenHead_->GetHeight() >= GetHeight() &&
            childRect.GetHeight() - childrenTail_->GetHeight() >= GetHeight()) {
            return true;
        }
    }
    return false;
}

void UISwipeView::MoveFirstChildToLast()
{
    if (childrenTail_ == nullptr || childrenHead_ == nullptr) {
        return;
    }
    if (direction_ == HORIZONTAL) {
        childrenHead_->SetX(childrenTail_->GetX() + childrenTail_->GetWidth());
    } else {
        childrenHead_->SetY(childrenTail_->GetY() + childrenTail_->GetHeight());
    }
    UIView* head = childrenHead_;
    UIViewGroup::Remove(childrenHead_);
    UIViewGroup::Add(head);
}

void UISwipeView::MoveLastChildToFirst()
{
    if (childrenTail_ == nullptr || childrenHead_ == nullptr) {
        return;
    }
    if (direction_ == HORIZONTAL) {
        childrenTail_->SetX(childrenHead_->GetX() - childrenTail_->GetWidth());
    } else {
        childrenTail_->SetY(childrenHead_->GetY() - childrenTail_->GetHeight());
    }
    UIView* last = childrenTail_;
    UIViewGroup::Remove(childrenTail_);
    UIViewGroup::Insert(nullptr, last);
}

void UISwipeView::CalculateInvalidate()
{
    Rect swipeRect(0, 0, GetRelativeRect().GetWidth() - 1, GetRelativeRect().GetHeight() - 1);
    UIView* view = childrenHead_;
    bool isFound = false;
    while (view != nullptr) {
        Rect rect = view->GetRelativeRect();
        if (rect.IsIntersect(swipeRect)) {
            if (view->IsVisible() && view->GetOpaScale() != OPA_TRANSPARENT) {
                view->Invalidate();
            }
            isFound = true;
        } else if (isFound) {
            return;
        }

        view = view->GetNextSibling();
    }
}
} // namespace OHOS
