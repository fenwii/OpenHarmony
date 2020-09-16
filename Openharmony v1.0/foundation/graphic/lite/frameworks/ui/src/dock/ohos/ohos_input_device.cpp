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

#include "dock/ohos/ohos_input_device.h"
#include "input_event_info.h"
#include "client/iwindows_manager.h"

namespace OHOS {
bool OHOSInputDevice::Read(DeviceData& data)
{
    IWindowsManager::GetInstance()->GetEventData(&data);
    return false;
}
}
