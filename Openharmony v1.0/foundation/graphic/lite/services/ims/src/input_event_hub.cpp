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

#include "input_event_hub.h"
#include "graphic_log.h"

namespace OHOS {
const uint32_t TOUCH_DEV_ID = 1;
const uint32_t MOUSE_DEV_ID = 2;
InputReportEventCb InputEventHub::callback_;
IInputInterface* InputEventHub::inputInterface_ = nullptr;
InputEventHub::InputDevStatusListener* InputEventHub::listener_ = nullptr;

void InputEventHub::SetUp()
{
    uint32_t ret = GetInputInterface(&inputInterface_);
    if (ret != INPUT_SUCCESS) {
        GRAPHIC_LOGE("get input driver interface failed!");
        return;
    }
    uint8_t num = ScanInputDevice();
    if (num == 0) {
        GRAPHIC_LOGE("There is no device!");
        return;
    }
    for (uint8_t i = 0; i < num; i++) {
        if (inputInterface_ == nullptr || inputInterface_->iInputManager == nullptr) {
            return;
        }
        ret = inputInterface_->iInputManager->OpenInputDevice(mountDevIndex_[i]);
        if (ret == INPUT_SUCCESS && inputInterface_->iInputReporter != nullptr && listener_ != nullptr) {
            callback_.ReportEventCallback = EventCallback;
            ret = inputInterface_->iInputReporter->RegisterReportCallback(mountDevIndex_[i], &callback_);
            if (ret != INPUT_SUCCESS) {
                GRAPHIC_LOGE("device dose not exist, can't register callback to it!");
                return;
            }
            listener_->OnDeviceMounted(mountDevIndex_[i]);
        }
    }
}

void InputEventHub::TearDown()
{
    uint32_t ret = 0;
    uint8_t num = ScanInputDevice();
    if (num != 0) {
        for (uint8_t i = 0; i < num; i++) {
            if (listener_ == nullptr || inputInterface_ == nullptr) {
                return;
            }
            if (!listener_->OnFindDeviceMounted(mountDevIndex_[i])) {
                continue;
            }
            if (inputInterface_->iInputReporter == nullptr || inputInterface_->iInputManager == nullptr) {
                return;
            }
            ret = inputInterface_->iInputReporter->UnregisterReportCallback(mountDevIndex_[i]);
            if (ret != INPUT_SUCCESS) {
                GRAPHIC_LOGE("Unregister callback failed!");
            }
            ret  = inputInterface_->iInputManager->CloseInputDevice(mountDevIndex_[i]);
            if (ret != INPUT_SUCCESS) {
                GRAPHIC_LOGE("Unmount device failed!");
            }
            listener_->OnDeviceUnmounted(mountDevIndex_[i]);
        }
    }
    if (inputInterface_ != nullptr) {
        if (inputInterface_->iInputManager != nullptr) {
            free(inputInterface_->iInputManager);
        }
        if (inputInterface_->iInputReporter != nullptr) {
            free(inputInterface_->iInputReporter);
        }
        if (inputInterface_->iInputController != nullptr) {
            free(inputInterface_->iInputController);
        }
        free(inputInterface_);
        inputInterface_ = nullptr;
    }
}

void InputEventHub::EventCallback(const InputEventData* eventData, uint32_t count, uint32_t devIndex)
{
    if (eventData == nullptr || listener_ == nullptr) {
        return;
    }
    RawEvent data;
    data.deviceId = devIndex;
    data.x = eventData->x;
    data.y = eventData->y;
    data.state = eventData->definedEvent;
    data.timestamp = eventData->timeStamp.tv_sec;
    listener_->OnSend(data);
}

uint8_t InputEventHub::ScanInputDevice()
{
    if (memset_s(mountDevIndex_, sizeof(mountDevIndex_), 0, sizeof(mountDevIndex_)) != EOK) {
        GRAPHIC_LOGE("Initialize mountDevIndex fail!");
        return 0;
    }
    /* later will be change get device mode */
    uint32_t deviceNum = 0;
    mountDevIndex_[0] = TOUCH_DEV_ID;
    mountDevIndex_[1] = MOUSE_DEV_ID;
    deviceNum = 2; // 2:Number of current devices
    return deviceNum;
}

InputDevType InputEventHub::GetDeviceType(uint32_t devIndex)
{
    switch (devIndex) {
        case TOUCH_DEV_ID: {
            return InputDevType::INDEV_TYPE_TOUCH;
        }
        case MOUSE_DEV_ID: {
            return InputDevType::INDEV_TYPE_MOUSE;
        }
        default: {
            return InputDevType::INDEV_TYPE_UNKNOWN;
        }
    }
}
} // namespace OHOS
