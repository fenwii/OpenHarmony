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

#ifndef GRAPHIC_LITE_KEY_INPUT_DEVICE_H
#define GRAPHIC_LITE_KEY_INPUT_DEVICE_H

#include "dock/input_device.h"

namespace OHOS {
/** @brief A key input device. */
class KeyInputDevice : public InputDevice {
public:
    /**
     * @brief Constructor
     *
     * @param [in] read If non-null, the read.
     * @param [in] userData If non-null, information describing the user.
     */
    KeyInputDevice() {}
    /** @brief Destructor */
    virtual ~KeyInputDevice() {}

private:
    void DispatchEvent(const DeviceData& data) override;
};
} // namespace OHOS
#endif // UI_INCLUDE_CORE_PHYKEY_INPUT_DEVICE_H
