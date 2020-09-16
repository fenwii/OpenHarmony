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

#ifndef GRAPHIC_LITE_POINTER_INPUT_DEVICE_H
#define GRAPHIC_LITE_POINTER_INPUT_DEVICE_H

#include "hal_tick.h"
#include "dock/input_device.h"
#include "components/ui_view_group.h"

namespace OHOS {
/** @brief A pointer input device. */
class PointerInputDevice : public InputDevice {
public:
    PointerInputDevice()
        : touchableView_(nullptr), draggableView_(nullptr), lastPos_({ 0, 0 }), dragLastPos_({ 0, 0 }),
          curPos_({ 0, 0 }), dragStep_({ 0, 0 }), dragLen_({ 0, 0 }), pressState_(false), pressSent_(false),
          longPressSent_(false), cancelSent_(false), isDragging_(false), needClick_(true), pressTimeStamp_(0)
    {}
    virtual ~PointerInputDevice() {}

protected:
    void DispatchEvent(const DeviceData& data) override;

private:
    UIView* touchableView_;
    UIView* draggableView_;
    Point lastPos_;
    Point dragLastPos_;
    Point curPos_;
    Point dragStep_;
    Point dragLen_;
    bool pressState_;
    bool pressSent_;
    bool longPressSent_;
    bool cancelSent_;
    bool isDragging_;
    bool needClick_;
    uint32_t pressTimeStamp_;

    void DispatchPressEvent(UIViewGroup* rootView);
    void DispatchReleaseEvent(UIViewGroup* rootView);
    void DispatchDragStartEvent();
    void DispatchDragEndEvent();
    void DispatchDragEvent();
    void DispatchLongPressEvent(uint32_t elapse);
    void DispatchCancelEvent();
    UIView* GetDraggableView(UIView* targetView) const
    {
        UIView* tempView = targetView;
        while (tempView != nullptr && tempView->IsDragParentInstead()) {
            tempView = tempView->GetParent();
        }
        if (tempView == nullptr || !tempView->IsDraggable()) {
            return nullptr;
        }
        return tempView;
    }
};
}; // namespace OHOS
#endif // GRAPHIC_LITE_POINTER_INPUT_DEVICE_H
