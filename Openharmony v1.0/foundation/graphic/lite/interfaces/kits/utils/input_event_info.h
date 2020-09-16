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

#ifndef GRAPHIC_LITE_INPUT_EVENT_INFO_H
#define GRAPHIC_LITE_INPUT_EVENT_INFO_H

#include <cstdint>
#include "geometry2d.h"

namespace OHOS {
const static uint8_t MAX_EVENT_SIZE = 10;
const static uint8_t MAX_INPUT_DEVICE_NUM = 10;

/**
 * @brief Enumerates input device types.
 */
enum class InputDevType {
    INDEV_TYPE_TOUCH,       /** Touchscreen */
    INDEV_TYPE_KEY,         /** Physical key */
    INDEV_TYPE_KEYBOARD,    /** Keyboard */
    INDEV_TYPE_MOUSE,       /** Mouse */
    INDEV_TYPE_BUTTON,      /** Virtual button */
    INDEV_TYPE_CROWN,       /** Watch crown */
    INDEV_TYPE_ENCODER,     /** Customized type of a specific function or event */
    INDEV_TYPE_UNKNOWN,     /** Unknown input device type */
};

/** @brief struct of raw event */
struct RawEvent {
    int32_t deviceId;
    InputDevType type;
    union {
        struct {
            int16_t x;
            int16_t y;
            uint16_t state;
        };
        uint16_t keyId; /* key type device use this param for touched key id */
    };
    int32_t timestamp;
};

struct DeviceData {
    union {
        Point point; /* pointer type device use this param for touched point */
        uint16_t keyId; /* key type device use this param for touched key id */
        int16_t encoderDiff; /* encode type device used this param for number of steps since the previous read */
        uint16_t type; /* for virtual device the currently event type */
    };
    uint16_t state;
#if ENABLE_WINDOW
    int32_t winId;
#endif
};
} // namespace OHOS
#endif // GRAPHIC_LITE_INPUT_EVENT_INFO_H