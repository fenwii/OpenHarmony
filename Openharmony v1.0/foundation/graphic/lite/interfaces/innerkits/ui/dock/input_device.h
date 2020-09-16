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

#ifndef GRAPHIC_LITE_INPUT_DEVICE_H
#define GRAPHIC_LITE_INPUT_DEVICE_H

#include "input_event_info.h"
#include "heap_base.h"

namespace OHOS {
/**
 * @brief Input device base class.
 */
class InputDevice : public HeapBase {
public:
    InputDevice() : rawDataState_(STATE_RELEASE) {}
    virtual ~InputDevice() {}

    /**
     * @brief Process event from input device driver.
     */
    void ProcessEvent();

    /**
     * @brief Read data from hardware.User should override this to set data
     *
     * @param [out] input device data.
     *
     * @returns no more data to read if true.
     */
    virtual bool Read(DeviceData& data) = 0;

    constexpr static uint8_t STATE_RELEASE = 0;
    constexpr static uint8_t STATE_PRESS = 1;

protected:
    uint16_t rawDataState_;

    /**
     * @brief Dispatch event to ui component.
     * @param [in] data data received from hardware
     */
    virtual void DispatchEvent(const DeviceData& data) = 0;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_INPUT_DEVICE_H
