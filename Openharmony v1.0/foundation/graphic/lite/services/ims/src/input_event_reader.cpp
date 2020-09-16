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

#include "input_event_reader.h"
#include "graphic_log.h"

namespace OHOS {
InputEventReader::InputEventReader()
{
    hub_ = InputEventHub::GetInstance();
    hub_->AddInputDevStatusListener(this);
    readCallback_ = nullptr;
}

InputEventReader::~InputEventReader()
{
    hub_->TearDown();
    hub_->RemoveInputDevStatusListener();
}

void InputEventReader::RegisterInputEventListener(InputEventListener* listener)
{
    if (listener == nullptr) {
        return;
    }
    std::map<uint32_t, InputEventListener*>::iterator iter;
    for (iter = deviceListenerMap_.begin(); iter != deviceListenerMap_.end(); iter++) {
        if (hub_->GetDeviceType(iter->first) == listener->GetDevType()) {
            uint32_t devIndex = iter->first;
            if (deviceListenerMap_[devIndex] == nullptr) {
                deviceListenerMap_[devIndex] = listener;
                return;
            }
        }
    }
}

void InputEventReader::OnDeviceMounted(uint32_t devIndex)
{
    InputEventListener* listener = nullptr;
    deviceListenerMap_.insert(std::make_pair(devIndex, listener));
}

void InputEventReader::OnDeviceUnmounted(uint32_t devIndex)
{
    deviceListenerMap_.erase(devIndex);
}

void InputEventReader::OnSend(RawEvent event)
{
    if (deviceListenerMap_[event.deviceId] == nullptr) {
        return;
    }
    RawEvent data = deviceListenerMap_[event.deviceId]->DisposeData(event);
    readCallback_(&data);
}

bool InputEventReader::OnFindDeviceMounted(uint32_t devIndex)
{
    if (deviceListenerMap_.count(devIndex) == 0) {
        return false;
    }
    return true;
}
} // namespace OHOS
