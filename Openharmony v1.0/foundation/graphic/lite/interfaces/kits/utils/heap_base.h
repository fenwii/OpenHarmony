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
 * @file heap_base.h
 *
 * @brief Declares the functions for overriding the <b>new</b> and <b>delete</b> functions.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_HEAP_BASE_H
#define GRAPHIC_LITE_HEAP_BASE_H

#include "graphic_config.h"
#include "mem_api.h"
#include <stddef.h>
namespace OHOS {
/**
 * @brief Defines the base class, overriding the <b>new</b> and <b>delete</b> functions.
 *
 * @since 1.0
 * @version 1.0
 */
class HeapBase {
public:
#if ENABLE_MEMORY_HOOKS
    /**
     * @brief Overrides the <b>new</b> function.
     * @param size Indicates the size of the memory to be allocated.
     *
     * @since 1.0
     * @version 1.0
     */
    void* operator new(size_t size)
    {
        return UIMalloc(static_cast(uint32_t>(size));
    }

    /**
     * @brief Overrides the <b>delete</b> function.
     * @param p Indicates the pointer to the memory to be released.
     *
     * @since 1.0
     * @version 1.0
     */
    void operator delete(void* p)
    {
        UIFree(p);
    }
#endif
};
} // namespace OHOS
#endif //
