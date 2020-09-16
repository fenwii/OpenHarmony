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

#ifndef GRAPHIC_LITE_HI_FBDEV_H
#define GRAPHIC_LITE_HI_FBDEV_H

#include "common/lite_wm_type.h"

namespace OHOS {
enum LayerRotateType {
    LAYER_ROTATE_NONE = 0,        /**< No rotation */
    LAYER_ROTATE_90,              /**< Rotation by 90 degrees */
    LAYER_ROTATE_180,             /**< Rotation by 180 degrees */
    LAYER_ROTATE_270,             /**< Rotation by 270 degrees */
    LAYER_ROTATE_BUTT             /**< Invalid operation */
};

/**
 * @brief Get dev surface data.
 */
LiteSurfaceData* GetDevSurfaceData();

/**
 * @brief Get layer rotate type.
 */
LayerRotateType GetLayerRotateType();

/**
 * @brief Initialize fbdev.
 */
void HiFbdevInit(void);

/**
 * @brief Close fbdev.
 */
void HiFbdevClose();

/**
 * @brief flush
 */
void LcdFlush();
} // namespace OHOS
#endif // GRAPHIC_LITE_HI_FBDEV_H
