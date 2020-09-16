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

#include "element_name_utils.h"

#include <cstring>

#include "utils.h"

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
namespace {
    constexpr int VALUE_NULL = 0;
    constexpr int VALUE_OBJECT = 1;
    constexpr int MAX_BUNDLE_NAME = 127;
    constexpr int MAX_ABILITY_NAME = 127;
    constexpr int MAX_DEVICE_ID = 1024;
}
#endif

void ClearElement(ElementName *element)
{
    if (element == nullptr) {
        return;
    }

    AdapterFree(element->deviceId);
    AdapterFree(element->bundleName);
    AdapterFree(element->abilityName);
}

bool SetElementDeviceID(ElementName *element, const char *deviceId)
{
    if (element == nullptr) {
        return false;
    }

    AdapterFree(element->deviceId);
    element->deviceId = OHOS::Utils::Strdup(deviceId);
    return element->deviceId != nullptr;
}

bool SetElementBundleName(ElementName *element, const char *bundleName)
{
    if (element == nullptr) {
        return false;
    }

    AdapterFree(element->bundleName);
    element->bundleName = OHOS::Utils::Strdup(bundleName);
    return element->bundleName != nullptr;
}

bool SetElementAbilityName(ElementName *element, const char *abilityName)
{
    if (element == nullptr) {
        return false;
    }

    AdapterFree(element->abilityName);
    element->abilityName = OHOS::Utils::Strdup(abilityName);
    return element->abilityName != nullptr;
}

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
bool SerializeElement(IpcIo *io, const ElementName *element)
{
    if ((io == nullptr) || (element == nullptr)) {
        return false;
    }

    if (element->deviceId == nullptr || strlen(element->deviceId) == 0) {
        IpcIoPushInt32(io, VALUE_NULL);
    } else if (strlen(element->deviceId) > MAX_DEVICE_ID) {
        return false;
    } else {
        IpcIoPushInt32(io, VALUE_OBJECT);
        IpcIoPushString(io, element->deviceId);
    }
    if (element->bundleName == nullptr || strlen(element->bundleName) == 0) {
        IpcIoPushInt32(io, VALUE_NULL);
    } else if (strlen(element->bundleName) > MAX_BUNDLE_NAME) {
        return false;
    } else {
        IpcIoPushInt32(io, VALUE_OBJECT);
        IpcIoPushString(io, element->bundleName);
    }
    if (element->abilityName == nullptr || strlen(element->abilityName) == 0) {
        IpcIoPushInt32(io, VALUE_NULL);
    } else if (strlen(element->abilityName) > MAX_ABILITY_NAME) {
        return false;
    } else {
        IpcIoPushInt32(io, VALUE_OBJECT);
        IpcIoPushString(io, element->abilityName);
    }
    return true;
}

bool DeserializeElement(ElementName *element, IpcIo *io)
{
    if ((io == nullptr) || (element == nullptr)) {
        return false;
    }

    if (IpcIoPopInt32(io) == VALUE_OBJECT &&
        !SetElementDeviceID(element, reinterpret_cast<char *>(IpcIoPopString(io, nullptr)))) {
        return false;
    }
    if (IpcIoPopInt32(io) == VALUE_OBJECT &&
        !SetElementBundleName(element, reinterpret_cast<char *>(IpcIoPopString(io, nullptr)))) {
        ClearElement(element);
        return false;
    }
    if (IpcIoPopInt32(io) == VALUE_OBJECT &&
        !SetElementAbilityName(element, reinterpret_cast<char *>(IpcIoPopString(io, nullptr)))) {
        ClearElement(element);
        return false;
    }
    return true;
}
#endif