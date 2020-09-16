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
 * @file display_gralloc.h
 *
 * @brief Declares the driver functions for memory.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef DISPLAY_GRALLOC_H
#define DISPLAY_GRALLOC_H
#include "display_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines pointers to the memory driver functions.
 */
typedef struct {
    /**
     * @brief Allocates memory based on the parameters passed by the GUI.
     *
     * @param hdl Indicates the pointer to the handle of memory.
     * @param type Indicates the type of memory to allocate. The value {@code 0} indicates memory without cache,
     * {@code 1} indicates memory with cache, and {@code 2} indicates shared memory.
     * @param size Indicates the size of memory to allocate, in bytes.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*AllocMem)(GrallocBuffer *buffer);

    /**
     * @brief Releases memory.
     *
     * @param hdl Indicates the pointer to the handle of memory that has been applied for.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*FreeMem)(GrallocBuffer *buffer);

    /**
     * @brief Maps memory with a specified physical address and size to memory without cache in the process's address
     * space.
     *
     * @param phyAddr Indicates the physical address of memory to map.
     * @param size Indicates the size of memory to map.
     *
     * @return Returns the pointer to a valid address if the operation is successful; returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    void *(*Mmap)(GrallocBuffer *buffer);

    /**
     * @brief Maps memory with a specified physical address and size to memory with cache in the process's address
     * space.
     *
     * @param phyAddr Indicates the physical address of memory to map.
     * @param size Indicates the size of memory to map.
     *
     * @return Returns the pointer to a valid address if the operation is successful; returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0 */
    void *(*MmapCache)(GrallocBuffer *buffer);

    /**
     * @brief Unmaps memory, that is, removes any mappings in the process's address space.
     *
     * @param virAddr Indicates the pointer to the virtual address of memory to unmap.
     * @param size Indicates the size of memory to unmap.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*Unmap)(GrallocBuffer *buffer);

    /**
     * @brief Flushes data from the cache to memory and invalidates the data in the cache.
     *
     * @param hdl Indicates the pointer to the handle of the cache.
     * @param size Indicates the size of the cache from which data is to flush.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*FlushCache)(GrallocBuffer *buffer);

    /**
     * @brief Flushes data from the cache mapping to {@link Mmap} to memory and invalidates the data in the cache.
     *
     * @param hdl Indicates the pointer to the handle of the cache.
     * @param size Indicates the size of the cache from which data is to flush.
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*FlushMCache)(GrallocBuffer *buffer);
} GrallocFuncs;

/**
 * @brief Initializes the memory module to obtain the pointer to functions for memory operations.
 *
 * @param funcs Indicates the double pointer to functions for memory operations. Memory is allocated automatically when
 * you initiate the memory module initialization, so you can simply use the pointer to gain access to the functions.
 *
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
 * otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t GrallocInitialize(GrallocFuncs **funcs);

/**
 * @brief Deinitializes the memory module to release the memory allocated to the pointer to functions for memory
 * operations.
 *
 * @param funcs Indicates the pointer to functions for memory operations.
 *
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link DispErrCode}
 * otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t GrallocUninitialize(GrallocFuncs *funcs);

#ifdef __cplusplus
}
#endif
#endif
/** @} */
