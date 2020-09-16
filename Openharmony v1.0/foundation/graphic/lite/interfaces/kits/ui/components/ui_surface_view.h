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

#ifndef GRAPHIC_LITE_UI_SURFACE_VIEW_H
#define GRAPHIC_LITE_UI_SURFACE_VIEW_H

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
 * @file ui_surface_view.h
 *
 * @brief Declares the surface view that interacts with the multimedia to achieve camera preview and video playback.
 *
 * @since 1.0
 * @version 1.0
 */

#include "components/ui_view.h"
#include "surface.h"

#include <string>

namespace OHOS {
/**
 * @brief Represents a surface view that interacts with the multimedia to achieve camera preview and video playback.
 *
 * @since 1.0
 * @version 1.0
 */
class UISurfaceView : public UIView {
public:
    /**
     * @brief A constructor used to create a <b>UISurfaceView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UISurfaceView();

    /**
     * @brief A destructor used to delete the <b>UISurfaceView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    ~UISurfaceView();

    /**
     * @brief Obtains the surface, which should be used together with the camera and video modules.
     *
     * @return Returns the surface.
     * @since 1.0
     * @version 1.0
     */
    Surface* GetSurface() const;

    /**
     * @brief Sets the position for this view.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPosition(int16_t x, int16_t y) override;

    /**
     * @brief Sets the position and size for this view.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @param width Indicates the width to set.
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPosition(int16_t x, int16_t y, int16_t width, int16_t height) override;

    /**
     * @brief Adjusts the size of this view.
     *
     * @param width Indicates the new width.
     * @param height Indicates the new height.
     * @since 1.0
     * @version 1.0
     */
    void Resize(int16_t width, int16_t height) override;

    /**
     * @brief Sets the x-coordinate for this view.
     *
     * @param x Indicates the x-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetX(int16_t x) override;

    /**
     * @brief Sets the y-coordinate for this view.
     *
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetY(int16_t y) override;

    /**
     * @brief Sets the width for this view.
     *
     * @param width Indicates the width to set.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width) override;

    /**
     * @brief Sets the height for this view.
     *
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height) override;

    /**
     * @brief Sets whether this view is visible.
     *
     * @param visible Specifies whether this view is visible. <b>true</b> indicates this view is visible,
     *      and <b>false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void SetVisible(bool visible) override;

    /**
     * @brief Called before this view is drawn. This function is used to check whether the parent view of this view
     *        needs to be redrawn so that the drawing process is optimized.
     *
     * @param invalidatedArea Indicates the area to draw.
     * @return Returns <b>true</b> if the parent view needs to be redrawn; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool OnPreDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Called when this view is drawn.
     *
     * @param invalidatedArea Indicates the area to draw.
     * @since 1.0
     * @version 1.0
     */
    void OnDraw(const Rect& invalidatedArea) override;

private:
    void Draw(const Rect& invalidatedArea);

    Surface* surface_;
    const std::string REGION_POSITION_X = "region_position_x";
    const std::string REGION_POSITION_Y = "region_position_y";
    const std::string REGION_WIDTH = "region_width";
    const std::string REGION_HEIGHT = "region_height";
    const uint8_t DEFAULT_QUEUE_SIZE = 2;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_SURFACE_VIEW_H
