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

#include "common/input_device_manager.h"
#include "common/task_manager.h"
#include "graphic_log.h"

namespace OHOS {
void InputDeviceManager::Init()
{
    if (INDEV_READ_PERIOD > 0) {
        SetPeriod(INDEV_READ_PERIOD);
        TaskManager::GetInstance()->Add(this);
    }
}

void InputDeviceManager::Add(InputDevice* device)
{
    if (device == nullptr) {
        GRAPHIC_LOGE("InputDeviceManager::Add invalid param\n");
        return;
    }
    deviceList_.PushBack(device);
}

void InputDeviceManager::Remove(InputDevice* device)
{
    if (device == nullptr) {
        return;
    }
    ListNode<InputDevice*>* node = deviceList_.Begin();
    while (node != deviceList_.End()) {
        if (node->data_ == device) {
            deviceList_.Remove(node);
            return;
        }
        node = node->next_;
    }
}

void InputDeviceManager::Callback()
{
    ListNode<InputDevice*>* node = deviceList_.Begin();
    while (node != deviceList_.End()) {
        node->data_->ProcessEvent();
        node = node->next_;
    }
}

void InputDeviceManager::Clear()
{
    deviceList_.Clear();
}
}  // namespace OHOS