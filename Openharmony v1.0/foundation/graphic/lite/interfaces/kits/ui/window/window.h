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
 * @addtogroup Window
 * @{
 *
 * @brief Provides window management capabilities, including creating, destroying, showing, hiding, moving,
 *        resizing a window, raising a window to the top, and lowering a window to the bottom.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file window.h
 *
 * @brief Declares the <b>Window</b> class that provides a drawing canvas for the <b>RootView</b>,
 *        which represents the root node of a view tree.
 *
 * Each window is bound to a <b>RootView</b>. For details, see {@link RootView}.
 * The <b>Window</b> class also provides window management capabilities, including creating, destroying, showing,
 * hiding, moving, resizing a window, raising a window to the top, and lowering a window to the bottom.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_WINDOW_H
#define GRAPHIC_LITE_WINDOW_H

#include "components/root_view.h"

namespace OHOS {
/**
 * @brief Enumerates the pixel formats of this window.
 *
 * @since 1.0
 * @version 1.0
 */
enum WindowPixelFormat {
    /** RGB565 format */
    WINDOW_PIXEL_FORMAT_RGB565 = 101,
    /** ARGB1555 format */
    WINDOW_PIXEL_FORMAT_ARGB1555,
    /** RGB888 format */
    WINDOW_PIXEL_FORMAT_RGB888,
    /** ARGB8888 format */
    WINDOW_PIXEL_FORMAT_ARGB8888,
};

/**
 * @brief Sets the attributes for this window.
 *
 * This structure stores the attributes such as the rectangle, opacity, and pixel format of this window.
 *
 * @since 1.0
 * @version 1.0
 */
struct WindowConfig {
    /** Rectangle */
    Rect rect;
    /** Opacity, within [0, 255] */
    uint8_t opacity;
    /** Pixel format */
    WindowPixelFormat pixelFormat;
    /** Other options */
    uint32_t option;
};

/**
 * @brief Provides a drawing canvas for the <b>RootView</b>, which represents the root node of a view tree.
 *
 * Each window is bound to a <b>RootView</b>. For details, see {@link RootView}.
 * This class also provides window management capabilities, including creating, destroying, showing, hiding,
 * moving, resizing a window, raising a window to the top, and lowering a window to the bottom.
 *
 * @since 1.0
 * @version 1.0
 */
class Window {
public:
    /**
     * @brief Creates a <b>Window</b> instance.
     *
     * @param config Indicates the window configuration. For details, see {@link WindowConfig}.
     * @return Returns the <b>Window</b> instance if the operation is successful; returns <b>nullptr</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    static Window* CreateWindow(const WindowConfig& config);

    /**
     * @brief Destroys a specified window.
     *
     * @param window Indicates the <b>Window</b> instance to destroy.
     * @since 1.0
     * @version 1.0
     */
    static void DestoryWindow(Window* window);

    /**
     * @brief Binds the <b>RootView</b> to this window.
     *
     * @param rootView Indicates the <b>RootView</b> to bind.
     * @since 1.0
     * @version 1.0
     */
    virtual void BindRootView(RootView* rootView) = 0;

    /**
     * @brief Unbinds the <b>RootView</b> from this window.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void UnbindRootView() = 0;

    /**
     * @brief Obtains the <b>RootView</b> bound to this window.
     *
     * @return Returns the <b>RootView</b> if available; returns <b>nullptr</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual RootView* GetRootView() = 0;

    /**
     * @brief Obtains the rectangle information (position, width, and height) of this window.
     *
     * @return Returns the rectangle information of this window.
     * @since 1.0
     * @version 1.0
     */
    virtual Rect GetRect() = 0;

    /**
     * @brief Shows this window.
     *
     * @since 1.0
     * @version 1.0 */
    virtual void Show() = 0;

    /**
     * @brief Hides this window.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void Hide() = 0;

    /**
     * @brief Moves this window to a specified position.
     *
     * @param x Indicates the x-coordinate of the target position.
     * @param y Indicates the y-coordinate of the target position.
     * @since 1.0
     * @version 1.0
     */
    virtual void MoveTo(int16_t x, int16_t y) = 0;

    /**
     * @brief Resizes this window.
     *
     * @param width Indicates the new window width.
     * @param height Indicates the new window height.
     * @since 1.0
     * @version 1.0
     */
    virtual void Resize(int16_t width, int16_t height) = 0;

    /**
     * @brief Raises this window to the top.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void RaiseToTop() = 0;

    /**
     * @brief Lowers this window to the bottom.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void LowerToBottom() = 0;

    /**
     * @brief Obtains the unique ID of this window.
     *
     * The window ID is within [0, 31]. An ID will be reused after the current window is destroyed.
     * A maximum of 32 windows can be displayed at the same time.
     *
     * @return Returns the unique ID of this window if the operation is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual int32_t GetWindowId() = 0;
};
}
#endif