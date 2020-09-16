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

#include "dfx/event_injector.h"
#include "dfx/point_event_injector.h"

#if ENABLE_DEBUG
#include "common/input_device_manager.h"
#include "graphic_log.h"

namespace OHOS {
EventInjector::~EventInjector()
{
    if (pointEventInjector_ != nullptr) {
        InputDeviceManager::GetInstance()->Remove(pointEventInjector_);
        delete pointEventInjector_;
        pointEventInjector_ = nullptr;
    }
}

bool EventInjector::RegisterEventInjector(EventDataType type)
{
    switch (type) {
        case EventDataType::POINT_TYPE:
            if (pointEventInjector_ == nullptr) {
                pointEventInjector_ = new PointEventInjector;
                if (pointEventInjector_ == nullptr) {
                    GRAPHIC_LOGE("EventInjector::RegisterEventInjector register pointEventInjector failed Err!\n");
                    return false;
                }
                InputDeviceManager::GetInstance()->Add(pointEventInjector_);
            }
            return true;
        default:
            break;
    }
    return false;
}

void EventInjector::UnregisterEventInjector(EventDataType type)
{
    switch (type) {
        case EventDataType::POINT_TYPE:
            if (pointEventInjector_ != nullptr) {
                InputDeviceManager::GetInstance()->Remove(pointEventInjector_);
                delete pointEventInjector_;
                pointEventInjector_ = nullptr;
            }
            break;
        default:
            break;
    }
}

bool EventInjector::IsEventInjectorRegistered(EventDataType type) const
{
    switch (type) {
        case EventDataType::POINT_TYPE:
            if (pointEventInjector_ != nullptr) {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool EventInjector::SetInjectEvent(const DeviceData* dataArray, uint16_t arrayLength, EventDataType type)
{
    if (dataArray == nullptr) {
        return false;
    }
    switch (type) {
        case EventDataType::POINT_TYPE:
            if (pointEventInjector_ == nullptr) {
                return false;
            }
            for (uint16_t i = 0; i < arrayLength; i++) {
                if (!pointEventInjector_->SetPointEvent(dataArray[i])) {
                    return false;
                }
            }
            break;
        default:
            return false;
    }
    return true;
}
}
#endif // ENABLE_DEBUG