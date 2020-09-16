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
 * @file screen.h
 *
 * @brief Declares the screen information.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_SCREEN_H
#define GRAPHIC_LITE_SCREEN_H

#include "heap_base.h"

namespace OHOS {
/**
 * @brief Represents the screen info of the device.
 *
 * @since 1.0
 * @version 1.0
 */
class Screen : HeapBase {
public:
    /**
     * @brief Obtains a singleton <b>Screen</b> instance.
     * @return Returns the <b>Screen</b> instance.
     */
    static Screen& GetInstance()
    {
        static Screen instance;
        return instance;
    }

    /**
     * @brief Obtains the width of this screen.
     *
     * @return Returns the screen width.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetWidth();

    /**
     * @brief Obtains the height of this screen.
     *
     * @return Returns the screen height.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetHeight();

private:
    Screen() {}
    virtual ~Screen() {}
};
} // namespace OHOS
#endif // GRAPHIC_LITE_SCREEN_H