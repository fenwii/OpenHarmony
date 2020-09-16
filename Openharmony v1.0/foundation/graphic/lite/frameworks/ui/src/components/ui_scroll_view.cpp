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

#include "components/ui_scroll_view.h"
#include "draw/draw_rect.h"

namespace OHOS {
UIScrollView::UIScrollView()
    : xSliderPos_({ 0, 0 }), ySliderPos_({ 0, 0 }), scrollBarWidth_(DEFAULT_BAR_WIDTH),
      xScrollMovable_(false), yScrollMovable_(false), xScrollable_(true), yScrollable_(true),
      minScrollBarLen_(DEFAULT_MIN_BAR_LEN), scrollListener_(nullptr)
{
    direction_ = HORIZONTAL_AND_VERTICAL;
    xSlider_.SetVisible(false);
    ySlider_.SetVisible(false);
    xSlider_.SetStyle(StyleDefault::GetBrightStyle());
    ySlider_.SetStyle(StyleDefault::GetBrightStyle());
}

void UIScrollView::OnPostDraw(const Rect& invalidatedArea)
{
    if (!xSlider_.IsVisible() && !ySlider_.IsVisible()) {
        return;
    }
    Rect scrollRect = GetRect();
    if (xSlider_.IsVisible()) {
        xSlider_.SetPosition(scrollRect.GetX() + xSliderPos_.x, scrollRect.GetY() + xSliderPos_.y);
        xSlider_.OnDraw(invalidatedArea);
    }
    if (ySlider_.IsVisible()) {
        ySlider_.SetPosition(scrollRect.GetX() + ySliderPos_.x, scrollRect.GetY() + ySliderPos_.y);
        ySlider_.OnDraw(invalidatedArea);
    }
}

bool UIScrollView::OnDragEvent(const DragEvent& event)
{
    if (animator_.GetState() != Animator::STOP) {
        UIAbstractScroll::StopAnimator();
    }
    Drag(event);
    return UIView::OnDragEvent(event);
}

bool UIScrollView::OnDragEndEvent(const DragEvent& event)
{
    Point last = event.GetPreLastPoint();
    Point current = event.GetLastPoint();
    if (last.x == current.x && last.y == current.y) {
        last = current;
        current = event.GetCurrentPos();
    }

    if (!DragReboundAnimator()) {
        if (!DragThrowAnimator(current, last)) {
            if (scrollListener_ && scrollListener_->GetScrollState() == OnScrollListener::SCROLL_STATE_MOVE) {
                scrollListener_->OnScrollEnd();
                scrollListener_->SetScrollState(OnScrollListener::SCROLL_STATE_STOP);
            }
        }
    }
    return UIView::OnDragEndEvent(event);
}

void UIScrollView::Drag(const DragEvent& event)
{
    int16_t xDistance = event.GetDeltaX();
    int16_t yDistance = event.GetDeltaY();

    if (xScrollMovable_ && xDistance != 0) {
        DragXInner(xDistance);
    }
    if (yScrollMovable_ && yDistance != 0) {
        DragYInner(yDistance);
    }
}

void UIScrollView::OnPressEvent(const PressEvent& event)
{
    StopAnimator();
    UIView::OnPressEvent(event);
}

void UIScrollView::ScrollBy(int16_t xDistance, int16_t yDistance)
{
    if (xScrollMovable_ && xDistance != 0) {
        DragXInner(xDistance);
    }
    if (yScrollMovable_ && yDistance != 0) {
        DragYInner(yDistance);
    }
    if ((scrollListener_ != nullptr) && (scrollListener_->GetScrollState() == OnScrollListener::SCROLL_STATE_MOVE)) {
        scrollListener_->OnScrollEnd();
        scrollListener_->SetScrollState(OnScrollListener::SCROLL_STATE_STOP);
    }
}

bool UIScrollView::DragXInner(int16_t distance)
{
    if (!xScrollMovable_) {
        return false;
    }
    Rect childRect = GetAllChildRelativeRect();
    int16_t reboundSize = reboundSize_;
    if (animator_.GetState() != Animator::STOP) {
        reboundSize = 0;
    }

    if (distance > 0) {
        if (childRect.GetLeft() > scrollBlankSize_ + reboundSize) {
            distance = 0;
        } else if ((childRect.GetLeft() + distance) > scrollBlankSize_ + reboundSize) {
            distance = scrollBlankSize_ - childRect.GetLeft() + reboundSize;
        }
    } else {
        int16_t childRight = childRect.GetRight();
        int16_t scrollWidth = GetWidth();
        if (yScrollable_ && ySlider_.IsVisible()) {
            if (childRight < scrollWidth - ySlider_.GetWidth() - (scrollBlankSize_ + reboundSize)) {
                distance = 0;
            } else if (childRight + distance < scrollWidth - ySlider_.GetWidth() -
                (scrollBlankSize_ + reboundSize)) {
                distance = scrollWidth - ySlider_.GetWidth() - (scrollBlankSize_ + reboundSize) - childRight;
            }
        } else {
            if (childRight < scrollWidth - (scrollBlankSize_ + reboundSize)) {
                distance = 0;
            } else if (childRight + distance < scrollWidth - (scrollBlankSize_ + reboundSize)) {
                distance = scrollWidth - (scrollBlankSize_ + reboundSize) - childRight - 1;
            }
        }
    }

    return MoveOffset(distance, 0);
}

bool UIScrollView::DragYInner(int16_t distance)
{
    if (!yScrollMovable_) {
        return false;
    }
    Rect childRect = GetAllChildRelativeRect();
    int16_t reboundSize = reboundSize_;
    if (animator_.GetState() != Animator::STOP) {
        reboundSize = 0;
    }

    if (distance > 0) {
        if (childRect.GetTop() > scrollBlankSize_ + reboundSize) {
            distance = 0;
        } else if ((childRect.GetTop() + distance) > scrollBlankSize_ + reboundSize) {
            distance = scrollBlankSize_ - childRect.GetTop() + reboundSize;
        }
    } else {
        int16_t childBottom = childRect.GetBottom();
        int16_t scrollHeight = GetHeight();
        if (xScrollable_ && xSlider_.IsVisible()) {
            if (childBottom < scrollHeight - xSlider_.GetHeight() - (scrollBlankSize_ + reboundSize)) {
                distance = 0;
            } else if (childBottom + distance < scrollHeight - xSlider_.GetHeight() -
                (scrollBlankSize_ + reboundSize)) {
                distance = scrollHeight - xSlider_.GetHeight() - (scrollBlankSize_ + reboundSize) - childBottom;
            }
        } else {
            if (childBottom < scrollHeight - (scrollBlankSize_ + reboundSize)) {
                distance = 0;
            } else if (childBottom + distance < scrollHeight - (scrollBlankSize_ + reboundSize)) {
                distance = scrollHeight - (scrollBlankSize_ + reboundSize) - childBottom - 1;
            }
        }
    }

    return MoveOffset(0, distance);
}

bool UIScrollView::MoveOffset(int16_t offsetX, int16_t offsetY)
{
    if (offsetX != 0 || offsetY != 0) {
        if ((scrollListener_ != nullptr) &&
            (scrollListener_->GetScrollState() == OnScrollListener::SCROLL_STATE_STOP)) {
            scrollListener_->OnScrollStart();
            scrollListener_->SetScrollState(OnScrollListener::SCROLL_STATE_MOVE);
        }
        UIAbstractScroll::MoveChildByOffset(offsetX, offsetY);
        Invalidate();
        RefreshScrollBarPosition();
        return true;
    }
    return false;
}

void UIScrollView::RefreshScrollBar()
{
    Rect childRect = GetAllChildRelativeRect();
    if (xScrollable_ && (childRect.GetWidth() <= GetWidth())) {
        xSliderPos_.y = GetHeight() - scrollBarWidth_;
        xSlider_.SetHeight(scrollBarWidth_);
        // y scroll bar is on, x scroll bar width should be group width - scroll bar width
        if (yScrollable_) {
            xSlider_.SetWidth(GetWidth() - scrollBarWidth_);
        } else {
            xSlider_.SetWidth(GetWidth());
        }
    }

    if (yScrollable_ && (childRect.GetHeight() <= GetHeight())) {
        ySliderPos_.x = GetWidth() - scrollBarWidth_;
        ySliderPos_.y = 0;
        ySlider_.SetWidth(scrollBarWidth_);
        // x scroll bar is on, y scroll bar height should be group height - scroll bar width
        if (xScrollable_) {
            ySlider_.SetHeight(GetHeight() - scrollBarWidth_);
        } else {
            ySlider_.SetHeight(GetHeight());
        }
    }
    xScrollMovable_ = false;
    yScrollMovable_ = false;
    float multiple;

    // child width is larger than group width, resize the x scroll bar width
    if (xScrollable_ && (childRect.GetWidth() > GetWidth()) && (childRect.GetWidth() != 0)) {
        int16_t groupWidth = GetWidth();
        int16_t xWidth;
        if (yScrollable_) {
            multiple = static_cast<float>(groupWidth - scrollBarWidth_) / childRect.GetWidth();
            xWidth = static_cast<int16_t>((groupWidth - scrollBarWidth_) * multiple);
        } else {
            multiple = static_cast<float>(groupWidth) / childRect.GetWidth();
            xWidth = static_cast<int16_t>(groupWidth * multiple);
        }
        if (xWidth < minScrollBarLen_) {
            xWidth = minScrollBarLen_;
        }

        xSliderPos_.x = GetXScrollOffset(childRect);
        xSliderPos_.y = GetHeight() - scrollBarWidth_;
        xSlider_.SetWidth(xWidth);
        xSlider_.SetHeight(scrollBarWidth_);
        xScrollMovable_ = true;
    }

    // child height is larger than group height, resize the y scroll height
    if (yScrollable_ && (childRect.GetHeight() > GetHeight()) && (childRect.GetHeight() != 0)) {
        int16_t groupHeight = GetHeight();
        int16_t yHeight;
        if (xScrollable_) {
            multiple = static_cast<float>(groupHeight - scrollBarWidth_) / childRect.GetHeight();
            yHeight = static_cast<int16_t>((groupHeight - scrollBarWidth_) * multiple);
        } else {
            multiple = static_cast<float>(groupHeight) / childRect.GetHeight();
            yHeight = static_cast<int16_t>(groupHeight * multiple);
        }

        // scroll bar may be too small, keep it min size
        if (yHeight < minScrollBarLen_) {
            yHeight = minScrollBarLen_;
        }

        ySliderPos_.x = GetWidth() - scrollBarWidth_;
        ySliderPos_.y = GetYScrollOffset(childRect);
        ySlider_.SetHeight(yHeight);
        ySlider_.SetWidth(scrollBarWidth_);
        yScrollMovable_ = true;
    }
}

void UIScrollView::RefreshScrollBarPosition()
{
    if (!xSlider_.IsVisible() && !ySlider_.IsVisible()) {
        return;
    }
    Rect childRect = GetAllChildRelativeRect();
    if (childRect.GetWidth() == 0 || childRect.GetHeight() == 0) {
        return;
    }
    if (xScrollMovable_ && xScrollable_) {
        int16_t xOffset = GetXScrollOffset(childRect);
        xSliderPos_.x = xOffset;
        Invalidate();
    }
    if (yScrollMovable_ && yScrollable_) {
        int16_t yOffset = GetYScrollOffset(childRect);
        ySliderPos_.y = yOffset;
        Invalidate();
    }
}

int16_t UIScrollView::GetXScrollOffset(const Rect& childRect)
{
    Rect scrollRect = GetRelativeRect();
    int16_t xOffset;
    int16_t scrollBarOffset = 0;
    float multiple;

    // set x scroll bar position, if y scroll bar is on,
    // x scroll bar should move between group left and y scroll bar left.
    // if y scroll bar off, move between group left and right
    if (yScrollable_) {
        scrollBarOffset = scrollBarWidth_;
    }

    int16_t childRectLeft = childRect.GetLeft();
    int16_t childRectWidth = childRect.GetWidth();
    int16_t scrollRectWidth = scrollRect.GetWidth();
    int16_t xSliderWidth = xSlider_.GetWidth();
    if ((childRectLeft >= 0) || (childRectWidth - scrollRectWidth + scrollBarOffset == 0)) {
        xOffset = 0;
    } else {
        multiple = static_cast<float>(scrollRectWidth - scrollBarOffset - xSliderWidth) /
            (childRectWidth - scrollRectWidth + scrollBarOffset);
        xOffset = static_cast<int16_t>(-childRectLeft * multiple);
    }
    return xOffset;
}

int16_t UIScrollView::GetYScrollOffset(const Rect& childRect)
{
    Rect scrollRect = GetRelativeRect();
    int16_t yOffset;
    int16_t scrollBarOffset = 0;
    float multiple;

    // set x scroll bar position, if y scroll bar is on,
    // x scroll bar should move between group left and y scroll bar left.
    // if y scroll bar off, move between group left and right
    if (xScrollable_) {
        scrollBarOffset = scrollBarWidth_;
    }

    int16_t childRectTop = childRect.GetTop();
    int16_t childRectHeight = childRect.GetHeight();
    int16_t scrollRectHeight = scrollRect.GetHeight();
    int16_t ySliderHeight = ySlider_.GetHeight();
    if ((childRectTop >= 0) || (childRectHeight - scrollRectHeight + scrollBarOffset == 0)) {
        yOffset = 0;
    } else {
        multiple = static_cast<float>(scrollRectHeight - scrollBarOffset - ySliderHeight) /
            (childRectHeight - scrollRectHeight + scrollBarOffset);
        yOffset = static_cast<int16_t>(-childRectTop * multiple);
    }
    return yOffset;
}

void UIScrollView::OnChildChanged()
{
    RefreshScrollBar();
}

bool UIScrollView::DragReboundAnimator()
{
    if (reboundSize_ == 0) {
        return false;
    }
    Rect rect = GetAllChildRelativeRect();
    int16_t top = rect.GetTop();
    int16_t bottom = rect.GetBottom();
    int16_t scrollHeight = GetHeight();
    int16_t dragDistanceY = 0;
    int16_t dragDistanceX = 0;

    if (yScrollMovable_) {
        if (scrollBlankSize_ < top) {
            dragDistanceY = scrollBlankSize_ - top;
        } else if (bottom < scrollHeight - 1) {
            dragDistanceY = scrollHeight - scrollBlankSize_ - bottom - 1;
        }
    }

    int16_t left = rect.GetLeft();
    int16_t right = rect.GetRight();
    int16_t scrollWidth = GetWidth();
    if (xScrollMovable_) {
        if (scrollBlankSize_ < left) {
            dragDistanceX = scrollBlankSize_ - left;
        } else if (right < scrollWidth - 1) {
            dragDistanceX = scrollWidth - scrollBlankSize_ - right - 1;
        }
    }

    if (dragDistanceY || dragDistanceX) {
        int16_t dragTimes = MATH_MAX(MATH_ABS(dragDistanceX), MATH_ABS(dragDistanceY)) / DRAG_TIMES_COEFFICIENT;
        if (dragTimes < MIN_DRAG_TIMES) {
            dragTimes = MIN_DRAG_TIMES;
        }
        animatorCallback_.SetDragStartValue(0, 0);
        animatorCallback_.SetDragEndValue(dragDistanceX, dragDistanceY);
        animatorCallback_.SetDragTimes(dragTimes * DRAG_ACC_FACTOR / GetDragACCLevel());
        animator_.Start();
        return true;
    }
    return false;
}

void UIScrollView::StopAnimator()
{
    if (scrollListener_ != nullptr && scrollListener_->GetScrollState() == OnScrollListener::SCROLL_STATE_MOVE) {
        scrollListener_->OnScrollEnd();
        scrollListener_->SetScrollState(OnScrollListener::SCROLL_STATE_STOP);
    }
    UIAbstractScroll::StopAnimator();
}
} // namespace OHOS