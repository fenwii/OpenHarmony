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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file virtual_device_event.h
 *
 * @brief Declares a virtual device event, which is used to receive a customized input event and call back
 *        the listening function registered.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_VIRTUAL_DEVICE_EVENT_H
#define GRAPHIC_LITE_VIRTUAL_DEVICE_EVENT_H

#include "event.h"

namespace OHOS {
/**
 * @brief Defines a virtual device event, which is used to receive a customized input event and call back
 *        the listening function registered.
 *
 * @since 1.0
 * @version 1.0
 */
class VirtualDeviceEvent : public Event {
public:
    VirtualDeviceEvent() = delete;

    /**
     * @brief A constructor used to create a <b>VirtualDeviceEvent</b> instance.
     *
     * @param type Indicates the virtual device type. The options are <b>AOD</b> and <b>PRIVATE</b>.
     * @param value Indicates the virtual event value.
     * @since 1.0
     * @version 1.0
     */
    VirtualDeviceEvent(uint16_t type, uint16_t value) : type_(type), state_(value) {}

    /**
     * @brief A destructor used to delete the <b>VirtualDeviceEvent</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    ~VirtualDeviceEvent() {}

    /**
     * @brief Enumerates virtual device types.
     *
     */
    enum DeviceType {
        AOD, // Standby event
        PRIVATE, // Other customized events
    };

    /**
     * @brief Obtains the type of the virtual device.
     *
     * @return Returns the type.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetType() const
    {
        return type_;
    }

    /**
    * @brief Obtains the state of the virtual event.
    *
    * @return Returns the state.
    * @since 1.0
    * @version 1.0
    */
    uint16_t GetState() const
    {
        return state_;
    }

private:
    uint16_t type_;
    uint16_t state_;
    static constexpr uint16_t INVALID_VIRTUAL_INPUT_STATE = UINT16_MAX;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_VIRTUAL_DEVICE_EVENT_H

