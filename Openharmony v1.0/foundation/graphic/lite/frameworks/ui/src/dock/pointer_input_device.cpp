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

#include "dock/pointer_input_device.h"

#include "components/root_view.h"
#include "core/render_manager.h"
#if ENABLE_AOD
#include "events/aod_callback.h"
#endif
#include "graphic_log.h"
#include "graphic_math.h"
#if ENABLE_WINDOW
#include "window/window.h"
#endif

namespace OHOS {
void PointerInputDevice::DispatchEvent(const DeviceData& data)
{
    curPos_ = data.point;
#if ENABLE_WINDOW
    Window* window = RenderManager::GetInstance().GetWindowById(data.winId);
    if (window == nullptr) {
        return;
    }
    curPos_.x = curPos_.x - window->GetRect().GetLeft();
    curPos_.y = curPos_.y - window->GetRect().GetTop();
    UIViewGroup* rootView = window->GetRootView();
#else
    UIViewGroup* rootView = RootView::GetInstance();
#endif
    // invalid touchable and draggable view will be reset to nullptr
    if (touchableView_ != nullptr && !RootView::FindSubView(*rootView, touchableView_)) {
        touchableView_ = nullptr;
        lastPos_ = curPos_;
    }
    if (draggableView_ != nullptr && !RootView::FindSubView(*rootView, draggableView_)) {
        draggableView_ = nullptr;
        lastPos_ = curPos_;
        dragLastPos_ = curPos_;
        dragLen_ = { 0, 0 };
        dragStep_ = { 0, 0 };
        isDragging_ = false;
    }

    if (data.state == STATE_PRESS) {
        DispatchPressEvent(rootView);
    } else {
        DispatchReleaseEvent(rootView);
    }
    dragLastPos_ = lastPos_;
    lastPos_ = curPos_;
}

void PointerInputDevice::DispatchPressEvent(UIViewGroup* rootView)
{
    if (rootView == nullptr) {
        return;
    }
    // first time to press
    if (!pressState_) {
        rootView->GetTargetView(curPos_, &touchableView_);
        if (touchableView_ == nullptr) {
            GRAPHIC_LOGE("PointerInputDevice::DispatchPressEvent cannot find target view!\n");
            return;
        }
        draggableView_ = GetDraggableView(touchableView_);
        pressState_ = true;
        pressTimeStamp_ = HALTick::GetInstance().GetTime();
        lastPos_ = curPos_;
        dragLastPos_ = lastPos_;
    } else {
        uint32_t elapse = HALTick::GetInstance().GetElapseTime(pressTimeStamp_);
        DispatchDragStartEvent();
        DispatchDragEvent();
        if (!isDragging_ && touchableView_ != nullptr && !cancelSent_) {
            UIView* tempView = nullptr;
            rootView->GetTargetView(curPos_, &tempView);
            if (tempView != touchableView_) {
                DispatchCancelEvent();
            } else {
                if (!pressSent_ && elapse > INDEV_PRESS_TIME_IN_DRAG) {
                    touchableView_->OnPressEvent(curPos_);
                    pressSent_ = true;
                }
                DispatchLongPressEvent(elapse);
            }
        }
    }
}

void PointerInputDevice::DispatchReleaseEvent(UIViewGroup* rootView)
{
    if (!pressState_ || rootView == nullptr) {
        return;
    }

    DispatchDragStartEvent();
    DispatchDragEndEvent();
    if (!isDragging_ && touchableView_ != nullptr && !cancelSent_) {
        UIView* tempView = nullptr;
        rootView->GetTargetView(curPos_, &tempView);
        if (tempView != touchableView_) {
            DispatchCancelEvent();
        } else {
            // reissue press event.
            if (!pressSent_) {
                touchableView_->OnPressEvent(curPos_);
                pressSent_ = true;
                return;
            } else {
                touchableView_->OnReleaseEvent(curPos_);
                if (pressSent_ && needClick_) {
                    touchableView_->OnClickEvent(curPos_);
#if ENABLE_AOD
                    OnClickEventHappen(*touchableView_);
#endif
                }
            }
        }
    }
    isDragging_ = false;
    pressState_ = false;
    pressSent_ = false;
    cancelSent_ = false;
    longPressSent_ = false;
    needClick_ = true;
    touchableView_ = nullptr;
}

void PointerInputDevice::DispatchDragStartEvent()
{
    if (draggableView_ == nullptr) {
        return;
    }
    dragStep_.x = curPos_.x - lastPos_.x;
    dragStep_.y = curPos_.y - lastPos_.y;
    dragLen_.x += dragStep_.x;
    dragLen_.y += dragStep_.y;
    if (!isDragging_) {
        if (MATH_ABS(dragLen_.x) >= INDEV_DRAG_LIMIT || MATH_ABS(dragLen_.y) >= INDEV_DRAG_LIMIT) {
            if (touchableView_ != nullptr && !cancelSent_) {
                DispatchCancelEvent();
            }
            // Send Drag Begin Event.
            DragEvent evt(curPos_, lastPos_, dragLen_);
            if (!draggableView_->OnDragStartEvent(evt)) {
                UIView* parent = draggableView_->GetParent();
                while (parent != nullptr) {
                    if (parent->OnDragStartEvent(evt)) {
                        break;
                    }
                    parent = parent->GetParent();
                }
            }
            dragLastPos_ = lastPos_;
            isDragging_ = true;
        }
    }
}

void PointerInputDevice::DispatchDragEvent()
{
    if (draggableView_ == nullptr || !isDragging_) {
        return;
    }
    if (dragStep_.x != 0 || dragStep_.y != 0) {
        DragEvent evt(curPos_, lastPos_, dragLen_);
        if (!draggableView_->OnDragEvent(evt)) {
            UIView* parent = draggableView_->GetParent();
            while (parent != nullptr) {
                if (parent->OnDragEvent(evt)) {
                    break;
                }
                parent = parent->GetParent();
            }
        }
    }
}

void PointerInputDevice::DispatchDragEndEvent()
{
    if (draggableView_ == nullptr) {
        return;
    }

    if (isDragging_) {
        DragEvent evt(curPos_, lastPos_, dragLen_);
        evt.SetPreLastPoint(dragLastPos_);
        if (!draggableView_->OnDragEndEvent(evt)) {
            UIView* parent = draggableView_->GetParent();
            while (parent != nullptr) {
                if (parent->OnDragEndEvent(evt)) {
                    break;
                }
                parent = parent->GetParent();
            }
        }
#if ENABLE_AOD
        OnDragEndEventHappen(*draggableView_);
#endif
    }
    dragLen_ = { 0, 0 };
    dragStep_ = { 0, 0 };
    draggableView_ = nullptr;
}

void PointerInputDevice::DispatchLongPressEvent(uint32_t elapse)
{
    if (!longPressSent_ && elapse > INDEV_LONG_PRESS_TIME) {
        longPressSent_ = true;
        LongPressEvent evt(curPos_, pressTimeStamp_);
        needClick_ = touchableView_->OnLongPressEvent(evt);
#if ENABLE_AOD
        OnLongPressEventHappen(*touchableView_);
#endif
    }
}

void PointerInputDevice::DispatchCancelEvent()
{
    touchableView_->OnCancelEvent(lastPos_);
    cancelSent_ = true;
}
}  // namespace OHOS
