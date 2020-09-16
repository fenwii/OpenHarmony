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

#ifndef GRAPHIC_LITE_IWINDOW_H
#define GRAPHIC_LITE_IWINDOW_H

#include "client/isurface.h"
#include "common/lite_wm_type.h"
#include "geometry2d.h"

namespace OHOS {
/**
 * @brief The IWindow class is an abstract definition of window. Each IWindow has a ISurface.
 */
class IWindow {
public:
    IWindow() {}

    virtual ~IWindow() {}

    /**
     * @brief Do some initialization after creating the window.
     * @return The result of initialize.
     */
    virtual int Init() = 0;

    /**
     * @brief Destroy the window.
     */
    virtual void Destroy() = 0;

    /**
     * @brief Show the window.
     */
    virtual void Show() = 0;

    /**
     * @brief Hide the window.
     */
    virtual void Hide() = 0;

    /**
     * @brief Resize the window.
     */
    virtual void Resize(int16_t width, int16_t height) = 0;

    /**
     * @brief Move the window to the specified coordinates.
     */
    virtual void MoveTo(int16_t x, int16_t y) = 0;

    /**
     * @brief Put the window on the top of the window stack.
     */
    virtual void RaiseToTop() = 0;

    /**
     * @brief Send a window to the bottom of the window stack.
     */
    virtual void LowerToBottom() = 0;

    /**
     * @brief Get surface of the window.
     * @return Pointer of surface
     */
    virtual ISurface* GetSurface() = 0;

    /**
     * @brief Get identification of the window.
     * @return Identification of the window
     */
    virtual int32_t GetWindowId() = 0;

    /**
     * @brief Update window.
     */
    virtual void Update() = 0;
};
}
#endif // GRAPHIC_LITE_IWINDOW_H

