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
 * @file key_event.h
 *
 * @brief Declares a key event, which indicates that a physical button is pressed or released.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_KEY_EVENT_H
#define GRAPHIC_LITE_KEY_EVENT_H

#include "event.h"

namespace OHOS {
constexpr uint16_t INVALID_KEY_STATE = UINT16_MAX;

/**
 * @brief Defines a key event, which indicates that a physical button is pressed or released.
 *
 * @since 1.0
 * @version 1.0
 */
class KeyEvent : public Event {
public:
    KeyEvent() = delete;

    /**
     * @brief A constructor used to create a <b>KeyEvent</b> instance.
     * @param keyId Indicates the key ID.
     * @param state Indicates the key state.
     * @since 1.0
     * @version 1.0
     */
    KeyEvent(uint16_t keyId, uint16_t state) : keyId_(keyId), state_(state) {}

    /**
     * @brief A destructor used to delete the <b>KeyEvent</b> instance.
     * @since 1.0
     * @version 1.0
     */
    ~KeyEvent() {}

    /**
     * @brief Obtains the key ID.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetKeyId() const
    {
        return keyId_;
    }

    /**
     * @brief Obtains the key state.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetState() const
    {
        return state_;
    }

private:
    uint16_t keyId_;
    uint16_t state_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_KEY_EVENT_H
