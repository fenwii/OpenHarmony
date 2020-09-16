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
 * @addtogroup Display
 * @{
 *
 * @brief Defines driver functions of the display module.
 *
 * The driver functions provided for the GUI include the layer, hardware acceleration, memory, and callback functions.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file display_gfx.h
 *
 * @brief Declares the driver functions for implementing hardware acceleration.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef DISPLAY_GFX_H
#define DISPLAY_GFX_H
#include "display_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines pointers to the hardware acceleration driver functions.
 */
typedef struct {
    /**
     * @brief Initializes hardware acceleration.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see DeinitGfx
     * @since 1.0
     * @version 1.0
     */
    int32_t (*InitGfx)(void);

    /**
     * @brief Deinitializes hardware acceleration.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see InitGfx
     * @since 1.0
     * @version 1.0
     */
    int32_t (*DeinitGfx)(void);

    /**
     * @brief Fills a rectangle with a given color on the canvas.
     *
     * @param surface Indicates the pointer to the canvas.
     * @param rect Indicates the pointer to the rectangle to fill.
     * @param color Indicates the color to fill.
     * @param opt Indicates the pointer to the hardware acceleration option.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*FillRect)(ISurface *surface, IRect *rect, uint32_t color, GfxOpt *opt);

    /**
     * @brief Draws a rectangle with a given color on the canvas.
     *
     * @param surface Indicates the pointer to the canvas.
     * @param rect Indicates the pointer to the rectangle to draw.
     * @param color Indicates the color to draw.
     * @param opt Indicates the pointer to the hardware acceleration option.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see FillRect
     * @since 1.0
     * @version 1.0
     */
    int32_t (*DrawRectangle)(ISurface *surface, Rectangle *rect, uint32_t color, GfxOpt *opt);

    /**
     * @brief Draws a straight line with a given color on the canvas.
     *
     * @param surface Indicates the pointer to the canvas.
     * @param line Indicates the pointer to the line to draw.
     * @param opt Indicates the pointer to the hardware acceleration option.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*DrawLine)(ISurface *surface, ILine *line, GfxOpt *opt);

    /**
     * @brief Draws a circle with a specified center and radius on the canvas using a given color.
     *
     * @param surface Indicates the pointer to the canvas.
     * @param circle Indicates the pointer to the circle to draw.
     * @param opt Indicates the pointer to the hardware acceleration option.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*DrawCircle)(ISurface *surface, ICircle *circle, GfxOpt *opt);

    /**
     * @brief Blits bitmaps.
     *
     * During bit blit, color space conversion (CSC), scaling, and rotation can be implemented.
     *
     * @param srcSurface Indicates the pointer to the source bitmap.
     * @param srcRect Indicates the pointer to the rectangle of the source bitmap.
     * @param dstSurface Indicates the pointer to the destination bitmap.
     * @param dstRect Indicates the pointer to the rectangle of the destination bitmap.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see Blit3
     * @since 1.0
     * @version 1.0
     */
    int32_t (*Blit)(ISurface *srcSurface, IRect *srcRect, ISurface *dstSurface, IRect *dstRect);

    /**
     * @brief Synchronizes hardware acceleration.
     *
     * Use this function for hardware acceleration synchronization when hardware acceleration is used to draw and blit
     * bitmaps. This function blocks the process until hardware acceleration is complete.
     *
     * @param timeOut Indicates the timeout duration for hardware acceleration synchronization. The value <b>0</b>
     * indicates no timeout, so the process waits until hardware acceleration is complete.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*Sync)(void);
} GfxFuncs;

/**
 * @brief Initializes the hardware acceleration module to obtain the pointer to functions for hardware acceleration
 * operations.
 *
 * @param funcs Indicates the double pointer to functions for hardware acceleration operations. Memory is allocated
 * automatically when you initiate the hardware acceleration module, so you can simply use the pointer to gain access
 * to the functions.
 *
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
 * otherwise.
 * @see GfxUninitialize
 * @since 1.0
 * @version 1.0
 */
int32_t GfxInitialize(GfxFuncs **funcs);

/**
 * @brief Deinitializes the hardware acceleration module to release the memory allocated to the pointer to functions
 * for hardware acceleration operations.
 *
 * @param funcs Indicates the pointer to functions for hardware acceleration operations.
 *
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
 * otherwise.
 * @see GfxInitialize
 * @since 1.0
 * @version 1.0
 */
int32_t GfxUninitialize(GfxFuncs *funcs);

#ifdef __cplusplus
}
#endif
#endif
/** @} */
