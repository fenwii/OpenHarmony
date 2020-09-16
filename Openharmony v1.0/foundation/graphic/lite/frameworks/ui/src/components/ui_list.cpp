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

#include "components/ui_list.h"

namespace OHOS {
UIList::Recycle::~Recycle()
{
    ListNode<UIView*>* node = scrapView_.Begin();
    while (node != scrapView_.End()) {
        if (node->data_) {
            UIView* deleteView = node->data_;
            if (deleteView != nullptr) {
                delete deleteView;
                deleteView = nullptr;
                node->data_ = nullptr;
            }
        }
        node = node->next_;
    }
    scrapView_.Clear();
}

void UIList::Recycle::InitRecycle()
{
    if (adapter_ == nullptr || listView_ == nullptr) {
        return;
    }
    FillActiveView();
    listView_->Invalidate();
}

UIView* UIList::Recycle::GetView(int16_t index)
{
    if (adapter_ == nullptr) {
        return nullptr;
    }
    UIView* inView = nullptr;
    UIView* retView = nullptr;

    if (scrapView_.Size() != 0) {
        inView = scrapView_.Back();
    }

    retView = adapter_->GetView(inView, index);
    if (retView != nullptr) {
        retView->SetViewIndex(index);
        scrapView_.PopBack();
    }
    return retView;
}

void UIList::Recycle::FillActiveView()
{
    if (adapter_ == nullptr || listView_ == nullptr) {
        return;
    }
    int16_t index = listView_->GetStartIndex();
    if (listView_->GetDirection() == UIList::VERTICAL) {
        int16_t childBottom = 0;
        while (index < adapter_->GetCount() && childBottom < listView_->GetHeight()) {
            UIView* view = GetView(index);
            if (view == nullptr) {
                break;
            }
            listView_->PushBack(view);
            if (listView_->childrenTail_) {
                childBottom =
                    listView_->childrenTail_->GetY() + listView_->childrenTail_->GetRelativeRect().GetHeight();
            } else {
                break;
            }
            index++;
        }
    } else {
        int16_t childRight = 0;
        while (index < adapter_->GetCount() && childRight < listView_->GetWidth()) {
            UIView* view = GetView(index);
            listView_->PushBack(view);
            if (listView_->childrenTail_) {
                childRight = listView_->childrenTail_->GetX() + listView_->childrenTail_->GetRelativeRect().GetWidth();
            } else {
                break;
            }
            index++;
        }
    }
}

UIList::UIList()
    : isLoopList_(false),
      isReCalculateDragEnd_(true),
      autoAlign_(false),
      startIndex_(0),
      topIndex_(0),
      bottomIndex_(0),
      selectPosition_(0),
      onSelectedIndex_(0),
      onSelectedView_(nullptr),
      recycle_(this),
      scrollListener_(nullptr)
{
    direction_ = VERTICAL;
    touchable_ = true;
    SetDraggable(true);
}

UIList::UIList(uint8_t direction)
    : isLoopList_(false),
      isReCalculateDragEnd_(true),
      autoAlign_(false),
      startIndex_(0),
      topIndex_(0),
      bottomIndex_(0),
      selectPosition_(0),
      onSelectedIndex_(0),
      onSelectedView_(nullptr),
      recycle_(this),
      scrollListener_(nullptr)
{
    direction_ = direction;
    touchable_ = true;
    SetDraggable(true);
}

UIList::~UIList()
{
    UIView* view = GetChildrenHead();
    while (view != nullptr) {
        UIView* tmp = view->GetNextSibling();
        delete view;
        view = tmp;
    }
}

bool UIList::OnDragEvent(const DragEvent& event)
{
    if (animator_.GetState() != Animator::STOP) {
        UIAbstractScroll::StopAnimator();
    }
    int16_t xDistance = event.GetDeltaX();
    int16_t yDistance = event.GetDeltaY();
    isReCalculateDragEnd_ = true;
    if (direction_ == VERTICAL) {
        RefreshDeltaY(yDistance);
        DragYInner(yDistance);
    } else {
        DragXInner(xDistance);
    }
    return UIView::OnDragEvent(event);
}

bool UIList::OnDragEndEvent(const DragEvent& event)
{
    Point last = event.GetPreLastPoint();
    Point current = event.GetLastPoint();
    if (last.x == current.x && last.y == current.y) {
        last = current;
        current = event.GetCurrentPos();
    }
    isReCalculateDragEnd_ = false;
    if (!DragThrowAnimator(current, last)) {
        if (scrollListener_ && scrollListener_->GetScrollState() == ListScrollListener::SCROLL_STATE_MOVE) {
            scrollListener_->SetScrollState(ListScrollListener::SCROLL_STATE_STOP);
            scrollListener_->OnScrollEnd(onSelectedIndex_, onSelectedView_);
        }
    }
    return UIView::OnDragEndEvent(event);
}

void UIList::OnPressEvent(const PressEvent& event)
{
    StopAnimator();
    UIView::OnPressEvent(event);
}

void UIList::ScrollBy(int16_t distance)
{
    if (direction_ == VERTICAL) {
        DragYInner(distance);
    } else {
        DragXInner(distance);
    }
    if (scrollListener_ && scrollListener_->GetScrollState() == ListScrollListener::SCROLL_STATE_MOVE) {
        scrollListener_->SetScrollState(ListScrollListener::SCROLL_STATE_STOP);
        scrollListener_->OnScrollEnd(onSelectedIndex_, onSelectedView_);
    }
}

bool UIList::DragXInner(int16_t distance)
{
    if (IsNeedReCalculateDragEnd()) {
        return false;
    }
    uint16_t listWidth = GetWidth();
    if (distance == 0) {
        return true;
    }
    bool ret = 0;
    do {
        ret = MoveChildStep(distance);
    } while (ret);

    if (isLoopList_) {
        return MoveOffset(distance);
    }
    if (distance > 0) {
        if (childrenHead_ && childrenHead_->GetX() + distance > scrollBlankSize_) {
            distance = scrollBlankSize_ - childrenHead_->GetX();
        }
    } else {
        if (childrenTail_) {
            if (childrenTail_->GetRelativeRect().GetRight() <= listWidth - scrollBlankSize_) {
                distance = 0;
            } else if (listWidth - (childrenTail_->GetX() + childrenTail_->GetRelativeRect().GetWidth() + distance) >
                       scrollBlankSize_) {
                distance =
                    listWidth - scrollBlankSize_ - childrenTail_->GetX() - childrenTail_->GetRelativeRect().GetWidth();
            }
        }
    }
    return MoveOffset(distance);
}

bool UIList::DragYInner(int16_t distance)
{
    if (IsNeedReCalculateDragEnd()) {
        return false;
    }
    uint16_t listHeigh = GetHeight();
    if (distance == 0) {
        return true;
    }
    bool ret = 0;
    do {
        ret = MoveChildStep(distance);
    } while (ret);

    if (isLoopList_) {
        return MoveOffset(distance);
    }
    if (distance > 0) {
        if (childrenHead_ && childrenHead_->GetY() + distance > scrollBlankSize_) {
            distance = scrollBlankSize_ - childrenHead_->GetY();
        }
    } else {
        if (childrenTail_) {
            if (childrenTail_->GetRelativeRect().GetBottom() <= listHeigh - scrollBlankSize_) {
                distance = 0;
            } else if (listHeigh - (childrenTail_->GetY() + childrenTail_->GetRelativeRect().GetHeight() + distance) >
                       scrollBlankSize_) {
                distance =
                    listHeigh - scrollBlankSize_ - childrenTail_->GetY() - childrenTail_->GetRelativeRect().GetHeight();
            }
        }
    }
    return MoveOffset(distance);
}

bool UIList::MoveOffset(int16_t offset)
{
    if (offset == 0) {
        return false;
    }
    if (direction_ == VERTICAL) {
        MoveChildByOffset(0, offset);
    } else {
        MoveChildByOffset(offset, 0);
    }
    Invalidate();
    if (scrollListener_ && scrollListener_->GetScrollState() == ListScrollListener::SCROLL_STATE_STOP) {
        scrollListener_->SetScrollState(ListScrollListener::SCROLL_STATE_MOVE);
        scrollListener_->OnScrollStart(onSelectedIndex_, onSelectedView_);
    }

    return true;
}

bool UIList::IsNeedReCalculateDragEnd()
{
    if (!autoAlign_ || isReCalculateDragEnd_ || onSelectedView_ == nullptr) {
        return false;
    }
    int16_t animationLess = 0;
    if (direction_ == VERTICAL) {
        animationLess = animatorCallback_.endValueY_ - animatorCallback_.previousValueY_;
    } else {
        animationLess = animatorCallback_.endValueX_ - animatorCallback_.previousValueX_;
    }
    if (!isDragging_ || MATH_ABS(animationLess) > RECALCULATE_DRAG_DISTANCE) {
        return false;
    }
    return true;
}
bool UIList::ReCalculateDragEnd()
{
    if (onSelectedView_ == nullptr || isReCalculateDragEnd_ || !autoAlign_) {
        return false;
    }

    int16_t offsetX = 0;
    int16_t offsetY = 0;
    if (direction_ == VERTICAL) {
        offsetY = selectPosition_ - (onSelectedView_->GetY() + (onSelectedView_->GetRelativeRect().GetHeight() >> 1));
    } else {
        offsetX = selectPosition_ - (onSelectedView_->GetX() + (onSelectedView_->GetRelativeRect().GetWidth() >> 1));
    }
    animatorCallback_.SetDragStartValue(0, 0);
    animatorCallback_.SetDragEndValue(offsetX, offsetY);
    animatorCallback_.SetDragTimes(RECALCULATE_DRAG_TIMES * DRAG_ACC_FACTOR / GetDragACCLevel());
    animator_.Start();
    isReCalculateDragEnd_ = true;
    return true;
}

bool UIList::MoveChildStepInner(int16_t distance,
                                int16_t (UIView::*pfnGetXOrY)() const,
                                int16_t (Rect::*pfnGetWidthOrHeight)() const)
{
    bool popRet = false;
    bool pushRet = false;
    if (distance > 0) {
        if ((childrenHead_ == nullptr) || ((childrenHead_->*pfnGetXOrY)() + distance > 0)) {
            UIView* newView = recycle_.GetView(GetIndexDec(topIndex_));
            if (newView != nullptr) {
                PushFront(newView);
                pushRet = true;
            } else {
                return false;
            }
        }
        if (childrenTail_ != nullptr &&
            ((childrenTail_->*pfnGetXOrY)() + distance > (this->GetRelativeRect().*pfnGetWidthOrHeight)())) {
            PopItem(childrenTail_);
            popRet = true;
        }
    } else {
        if ((childrenTail_ == nullptr) ||
            ((childrenTail_->*pfnGetXOrY)() + (childrenTail_->GetRelativeRect().*pfnGetWidthOrHeight)() + distance <
            (this->GetRelativeRect().*pfnGetWidthOrHeight)())) {
            UIView* newView = recycle_.GetView(GetIndexInc(bottomIndex_));
            if (newView != nullptr) {
                PushBack(newView);
                pushRet = true;
            } else {
                return false;
            }
        }
        if (childrenHead_ &&
            (childrenHead_->*pfnGetXOrY)() + distance + (childrenHead_->GetRelativeRect().*pfnGetWidthOrHeight)() < 0) {
            PopItem(childrenHead_);
            popRet = true;
        }
    }
    return (popRet || pushRet);
}

bool UIList::MoveChildStep(int16_t distance)
{
    if (direction_ == VERTICAL) {
        return MoveChildStepInner(distance, &UIView::GetY, &Rect::GetHeight);
    } else {
        return MoveChildStepInner(distance, &UIView::GetX, &Rect::GetWidth);
    }
}

void UIList::SetAdapter(AbstractAdapter* adapter)
{
    recycle_.SetAdapter(adapter);
    recycle_.InitRecycle();
}

UIView* UIList::GetSelectView()
{
    if (onSelectedView_ != nullptr) {
        return onSelectedView_;
    }
    if (childrenHead_ == nullptr || selectPosition_ == 0) {
        return nullptr;
    }
    UIView* child = childrenHead_;
    while (child != nullptr) {
        if (direction_ == VERTICAL) {
            if (child->GetY() <= selectPosition_ &&
                child->GetY() + child->GetRelativeRect().GetHeight() >= selectPosition_) {
                if (scrollListener_ != nullptr) {
                    scrollListener_->OnItemSelected(child->GetViewIndex(), child);
                }
                return child;
            }
        } else {
            if (child->GetX() <= selectPosition_ &&
                child->GetX() + child->GetRelativeRect().GetWidth() >= selectPosition_) {
                if (scrollListener_ != nullptr) {
                    scrollListener_->OnItemSelected(child->GetViewIndex(), child);
                }
                return child;
            }
        }
        child = child->GetNextSibling();
    }
    return nullptr;
}

void UIList::PushBack(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    if (childrenTail_ == nullptr) {
        SetHead(view);
    } else {
        if (direction_ == VERTICAL) {
            view->SetPosition(0, childrenTail_->GetY() + childrenTail_->GetRelativeRect().GetHeight());
        } else {
            view->SetPosition(childrenTail_->GetX() + childrenTail_->GetRelativeRect().GetWidth(), 0);
        }
        bottomIndex_ = GetIndexInc(bottomIndex_);
    }

    view->SetDragParentInstead(true);
    UIViewGroup::Add(view);
}

void UIList::PushFront(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    if (GetChildrenHead() == nullptr) {
        SetHead(view);
    } else {
        if (direction_ == VERTICAL) {
            view->SetPosition(0, GetChildrenHead()->GetY() - view->GetRelativeRect().GetHeight());
        } else {
            view->SetPosition(GetChildrenHead()->GetX() - view->GetRelativeRect().GetWidth(), 0);
        }
        topIndex_ = GetIndexDec(topIndex_);
    }
    view->SetDragParentInstead(true);
    UIViewGroup::Insert(nullptr, view);
}

void UIList::PopItem(UIView* view)
{
    if (view == nullptr) {
        return;
    }
    recycle_.AddScrapView(view);
    if (view == GetChildrenHead()) {
        topIndex_ = GetIndexInc(topIndex_);
    }

    if (view == childrenTail_) {
        bottomIndex_ = GetIndexDec(bottomIndex_);
    }
    UIViewGroup::Remove(view);
}

void UIList::SetHead(UIView* view)
{
    if (view != nullptr) {
        view->SetPosition(0, 0);
        topIndex_ = startIndex_;
        bottomIndex_ = startIndex_;
    }
}

void UIList::MoveChildByOffset(int16_t xOffset, int16_t yOffset)
{
    UIView* view = GetChildrenHead();
    if (view == nullptr) {
        return;
    }
    int16_t x;
    int16_t y;
    int16_t height;
    int16_t width;

    if (onSelectedIndex_ != NULL_SELECT_INDEX && selectPosition_ != 0) {
        if (direction_ == VERTICAL) {
            height = view->GetRelativeRect().GetHeight();
            if (GetChildrenHead()->GetY() + yOffset > selectPosition_ ||
                childrenTail_->GetY() + height + yOffset < selectPosition_) {
                onSelectedIndex_ = NULL_SELECT_INDEX;
                onSelectedView_ = nullptr;
                if (scrollListener_ != nullptr) {
                    scrollListener_->OnItemSelected(onSelectedIndex_, onSelectedView_);
                }
            }
        } else {
            width = view->GetRelativeRect().GetWidth();
            if (GetChildrenHead()->GetX() + xOffset > selectPosition_ ||
                childrenTail_->GetX() + width < selectPosition_) {
                onSelectedIndex_ = NULL_SELECT_INDEX;
                onSelectedView_ = nullptr;
                if (scrollListener_ != nullptr) {
                    scrollListener_->OnItemSelected(onSelectedIndex_, onSelectedView_);
                }
            }
        }
    }
    bool isSelectViewFind = false;
    while (view != nullptr) {
        x = view->GetX() + xOffset;
        y = view->GetY() + yOffset;
        view->SetPosition(x, y);

        if (selectPosition_ != 0 && !isSelectViewFind) {
            if (direction_ == VERTICAL) {
                height = view->GetRelativeRect().GetHeight();
                if (y <= selectPosition_ && y + height >= selectPosition_ && onSelectedView_ != view) {
                    onSelectedIndex_ = view->GetViewIndex();
                    onSelectedView_ = view;
                    if (scrollListener_ != nullptr) {
                        scrollListener_->OnItemSelected(onSelectedIndex_, onSelectedView_);
                    }
                    isSelectViewFind = true;
                }
            } else {
                width = view->GetRelativeRect().GetWidth();
                if (x <= selectPosition_ && x + width >= selectPosition_ && onSelectedView_ != view) {
                    onSelectedIndex_ = view->GetViewIndex();
                    onSelectedView_ = view;
                    if (scrollListener_ != nullptr) {
                        scrollListener_->OnItemSelected(onSelectedIndex_, onSelectedView_);
                    }
                    isSelectViewFind = true;
                }
            }
        }
        view = view->GetNextSibling();
    }
}

void UIList::StopAnimator()
{
    UIAbstractScroll::StopAnimator();
    if (!ReCalculateDragEnd()) {
        if ((scrollListener_ != nullptr) &&
            (scrollListener_->GetScrollState() == ListScrollListener::SCROLL_STATE_MOVE)) {
            scrollListener_->SetScrollState(ListScrollListener::SCROLL_STATE_STOP);
            scrollListener_->OnScrollEnd(onSelectedIndex_, onSelectedView_);
        }
    }
}

uint16_t UIList::GetIndexInc(uint16_t index)
{
    uint16_t ret = index + 1;
    if (isLoopList_ && recycle_.GetAdapterItemCount() != 0) {
        ret = ret % recycle_.GetAdapterItemCount();
    }
    return ret;
}

uint16_t UIList::GetIndexDec(uint16_t index)
{
    int16_t ret = index - 1;
    if (isLoopList_ && (ret < 0)) {
        ret = recycle_.GetAdapterItemCount() - 1;
    }
    return ret;
}

void UIList::ScrollTo(uint16_t index)
{
    UIView* child = GetChildrenHead();
    UIView* tmp = nullptr;
    while (child != nullptr) {
        tmp = child;
        child = child->GetNextSibling();
        PopItem(tmp);
    }
    onSelectedView_ = nullptr;
    SetStartIndex(index);
    recycle_.InitRecycle();
}

void UIList::RefreshList()
{
    int16_t topIndex = topIndex_;
    UIView* child = GetChildrenHead();
    UIView* tmp = nullptr;
    int16_t offset = 0;
    if (child != nullptr) {
        if (direction_ == VERTICAL) {
            offset = child->GetY();
        } else {
            offset = child->GetX();
        }
    }

    while (child != nullptr) {
        tmp = child;
        child = child->GetNextSibling();
        PopItem(tmp);
    }
    onSelectedView_ = nullptr;

    uint16_t tmpStartIndex = startIndex_;
    if (topIndex > recycle_.GetAdapterItemCount() - 1) {
        startIndex_ = 0;
        offset = 0;
    } else {
        startIndex_ = topIndex;
    }
    recycle_.InitRecycle();
    startIndex_ = tmpStartIndex;

    if (direction_ == VERTICAL) {
        DragYInner(offset);
    } else {
        DragXInner(offset);
    }
    Invalidate();
}

void UIList::RemoveAll()
{
    UIViewGroup::RemoveAll();
    recycle_.ClearScrapView();
}
} // namespace OHOS