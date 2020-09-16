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
 * @file mem_api.h
 *
 * @brief Defines the functions for memory application and release. You can implement the <b>malloc</b> and <b>free</b>
 *        functions to manage the memory.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_MEM_API_H
#define GRAPHIC_LITE_MEM_API_H

#include "graphic_config.h"
#include "image_info.h"

#ifndef IMG_CACHE_MEMORY_CUSTOM
#include <cstdlib>
#endif

namespace OHOS {
/**
 * @brief Applies for the image cache memory. You can customize the memory area when loading image resources.
 *
 * @param info Indicates the image information. For details, see {@link ImageInfo}.
 * @since 1.0
 * @version 1.0
 */
void* ImageCacheMalloc(ImageInfo& info);

/**
 * @brief Releases the image cache memory.
 *
 * @param info Indicates the image information. For details, see {@link ImageInfo}.
 * @since 1.0
 * @version 1.0
 */
void ImageCacheFree(ImageInfo& info);

/**
 * @brief Applies for memory for the graphics module. You can implement this function to override the <b>malloc</b> and
 *        <b>new</b> functions.
 *
 * @param size Indicates the size of the memory to apply for.
 * @since 1.0
 * @version 1.0
 */
void* UIMalloc(uint32_t size);

/**
 * @brief Releases memory for the graphics module. You can implement this function to override the <b>free</b> and
 *        <b>delete</b> functions.
 *
 * @param buffer Indicates the pointer to the memory to be released.
 * @since 1.0
 * @version 1.0
 */
void UIFree(void* buffer);
} // namespace OHOS
#endif
