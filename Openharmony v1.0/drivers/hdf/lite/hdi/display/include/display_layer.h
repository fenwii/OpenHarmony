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
 * @file display_layer.h
 *
 * @brief Declares the driver functions for implementing layer operations.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef DISPLAY_LAYTER_H
#define DISPLAY_LAYTER_H
#include "display_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines pointers to the layer driver functions.
 */
typedef struct {
    /**
     * @brief Initializes a display device.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see DeinitDisplay
     * @since 1.0
     * @version 1.0
     */
    int32_t (*InitDisplay)(uint32_t devId);

    /**
     * @brief Deinitializes a display device.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see InitDisplay
     * @since 1.0
     * @version 1.0
     */
    int32_t (*DeinitDisplay)(uint32_t devId);

    /**
     * @brief Obtains information about a display device.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param dispInfo Indicates the pointer to the display device information obtained.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetDisplayInfo)(uint32_t devId, DisplayInfo *dispInfo);

    /**
     * @brief Opens a layer on a specified display device.
     *
     * Before using a layer on the GUI, you must open the layer based on the layer information. After the layer is
     * opened, you can obtain the layer ID and then use other functions based on the layer ID.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerInfo Indicates the pointer to the layer information passed to open a layer, including the layer
     * type, layer size, and pixel format.
     * @param layerId Indicates the pointer to the layer ID, which identifies a unique layer. The layer ID is returned
     * to the GUI after the layer is successfully opened.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see CloseLayer
     * @since 1.0
     * @version 1.0
     */
    int32_t (*OpenLayer)(uint32_t devId, const LayerInfo *layerInfo, uint32_t *layerId);

    /**
     * @brief Closes a layer that is no longer required on a specified display device.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see OpenLayer
     * @since 1.0
     * @version 1.0
     */
    int32_t (*CloseLayer)(uint32_t devId, uint32_t layerId);

    /**
     * @brief Sets whether a layer is visible.
     *
     * A visible layer is displayed on the screen, whereas an invisible layer is not displayed on the screen.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param visible Indicates the visibility to set for the layer. The value <b>true</b> means to set the layer to be
     * visible, and <b>false</b> means the opposite.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerVisibleState
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerVisible)(uint32_t devId, uint32_t layerId, bool visible);

    /**
     * @brief Checks whether a layer is visible.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param visible Indicates the pointer to the obtained layer visibility. The value <b>true</b> indicates that the
     * layer is visible, and <b>false</b> indicates that the layer is invisible.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerVisible
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerVisibleState)(uint32_t devId, uint32_t layerId, bool *visible);

    /**
     * @brief Sets the size of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param rect Indicates the pointer to the layer size to set, in pixels.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerSize
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerSize)(uint32_t devId, uint32_t layerId, IRect *rect);

    /**
     * @brief Obtains the size of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param rect Indicates the pointer to the obtained layer size.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerSize
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerSize)(uint32_t devId, uint32_t layerId, IRect *rect);

    /**
     * @brief Sets the rectangular area to crop for a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param rect Indicates the pointer to the rectangular area to crop.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerCrop)(uint32_t devId, uint32_t layerId, IRect *rect);

    /**
     * @brief Sets the z-order for a layer.
     *
     * A larger z-order value indicates a higher layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param zorder Indicates the z-order to set. The value is an integer ranging from 0 to 255.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerZorder
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerZorder)(uint32_t devId, uint32_t layerId, uint32_t zorder);

    /**
     * @brief Obtains the z-order of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param zorder Indicates the pointer to the obtained z-order. The value is an integer ranging from 0 to 255.
     * A larger z-order value indicates a higher layer.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerZorder
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerZorder)(uint32_t devId, uint32_t layerId, uint32_t *zorder);

    /**
     * @brief Sets layer premultiplication.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param preMul Specifies whether to enable layer premultiplication. The value <b>1</b> means to enable layer
     * premultiplication, and <b>0</b> means the opposite.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerPreMulti
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerPreMulti)(uint32_t devId, uint32_t layerId, bool preMul);

    /**
     * @brief Obtains the premultiplication flag of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param preMul Indicates the pointer to the obtained layer premultiplication flag.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerPreMulti
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerPreMulti)(uint32_t devId, uint32_t layerId, bool *preMul);

    /**
     * @brief Sets the alpha value for a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param alpha Indicates the pointer to the alpha value to set.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerAlpha
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerAlpha)(uint32_t devId, uint32_t layerid, LayerAlpha *alpha);

    /**
     * @brief Obtains the alpha value of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param alpha Indicates the pointer to the obtained alpha value.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerAlpha
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerAlpha)(uint32_t devId, uint32_t layerId, LayerAlpha *alpha);

    /**
     * @brief Sets the color key for a layer.
     *
     * The color key is used during layer overlay.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param enable Specify whether to enable the color key.
     * @param key Indicates the color key.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerColorKey
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerColorKey)(uint32_t devId, uint32_t layerId, bool enable, uint32_t key);

    /**
     * @brief Obtains the color key of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param enable Indicates the pointer to the color key enable bit.
     * @param key Indicates the pointer to the color key.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerColorKey
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerColorKey)(uint32_t devId, uint32_t layerId, bool *enable, uint32_t *key);

    /**
     * @brief Sets the palette for a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param palette Indicates the pointer to the palette to set.
     * @param len Indicates the length of the palette.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerPalette
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerPalette)(uint32_t devId, uint32_t layerId, uint32_t *palette, uint32_t len);

    /**
     * @brief Obtains the palette of a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param palette Indicates the pointer to the obtained palette.
     * @param len Indicates the length of the palette.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerPalette
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerPalette)(uint32_t devId, uint32_t layerId, uint32_t *palette, uint32_t len);

    /**
     * @brief Sets the transform mode for a layer.
     *
     * Using this function, you can rotate, scale, and move the layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param type Indicates the transformation mode to set.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetTransformMode)(uint32_t devId, uint32_t layerId, TransformType type);

    /**
     * @brief Sets the compression feature for a layer.
     *
     * In specific scenarios, images need to be compressed. You can set whether to enable layer compression.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param compType Specifies whether to enable the compression feature. The value <b>true>/b> means to enable
     * compression, and <b>false> means the opposite.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see GetLayerCompression
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerCompression)(uint32_t devId, uint32_t layerId, int32_t compType);

    /**
     * @brief Checks whether the compression feature is enabled for a layer.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param compType Indicates the pointer to the variable specifying whether the compression feature is enabled.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see SetLayerCompression
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerCompression)(uint32_t devId, uint32_t layerId, int32_t *compType);

    /**
     * @brief Sets the flushing area for a layer.
     *
     * After the GUI draws an image, you must set the layer flushing area before calling the {@link Flush} function to
     * flush the screen.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param region Indicates the pointer to the flushing area to set.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetLayerDirtyRegion)(uint32_t devId, uint32_t layerId, IRect *region);

    /**
     * @brief Obtains the buffer of a layer.
     *
     * After drawing a picture in the buffer, the application calls the {@link Flush} function to display the picture
     * on the screen.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param buffer Indicates the pointer to the obtained buffer.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @see Flush
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetLayerBuffer)(uint32_t devId, uint32_t layerId, LayerBuffer *buffer);

    /**
     * @brief Flushes a layer.
     *
     * Display data in the buffer is flushed to a specified layer so that the image data is displayed on the screen.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param buffer Indicates the pointer to the buffer in which the display data is to flush.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*Flush)(uint32_t devId, uint32_t layerId, LayerBuffer *buffer);

    /**
     * @brief Waits for the arrival of vertical blanking.
     *
     * This function blocks the process until vertical blanking arrives, implementing the synchronization between
     * software and hardware.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param layerId Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer
     * with the specified layer ID.
     * @param timeOut Indicates the maximum duration that the process waits for the arrival of vertical blanking.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*WaitForVBlank)(uint32_t devId, uint32_t layerId);

    /**
     * @brief Implements the snapshot feature.
     *
     * This function saves the screenshot of image data on the display device to the buffer for debugging or as
     * requested by applications.
     *
     * @param devId Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first
     * display device and 4 indicates the last display device.
     * @param buffer Indicates the pointer to the buffer for saving screenshots.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SnapShot)(uint32_t devId, LayerBuffer *buffer);
} LayerFuncs;

/**
 * @brief Initializes the layer to apply for resources used by the layer and obtain the pointer to functions for
 * layer operations.
 *
 * @param funcs Indicates the double pointer to functions for layer operations. Memory is allocated automatically when
 * you initiate the layer module, so you can simply use the pointer to gain access to the functions.
 *
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
 * otherwise.
 * @see LayerUninitialize
 * @since 1.0
 * @version 1.0
 */
int32_t LayerInitialize(LayerFuncs **funcs);

/**
 * @brief Deinitializes the layer module to release the memory allocated to the pointer to functions for
 * layer operations.
 *
 * @param funcs Indicates the pointer to functions for layer operations.
 *
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
 * otherwise.
 * @see LayerInitialize
 * @since 1.0
 * @version 1.0
 */
int32_t LayerUninitialize(LayerFuncs *funcs);

#ifdef __cplusplus
}
#endif
#endif
/** @} */
