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
 * @file image_info.h
 *
 * @brief Defines image information.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_IMAGE_INFO_H
#define GRAPHIC_LITE_IMAGE_INFO_H

#include <cstdint>

namespace OHOS {
/**
 * @brief Defines image head node information.
 */
struct ImageHeader {
    /** Color format, which is used to match image type. This variable is important. */
    uint32_t colorMode : 8;
    uint32_t reserved : 24;
    /** Image width */
    uint16_t width;
    /** Image height */
    uint16_t height;
};

/**
 * @brief Defines image information.
 */
struct ImageInfo {
    /** Image head node information. For details, see {@link ImageHeader}. */
    ImageHeader header;
    /** Size of the image data (in bytes) */
    uint32_t dataSize;
    /** Pixel color data of pixelmap images */
    const uint8_t* data;
    /** User-defined data */
    void* userData;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_IMAGE_INFO_H
