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
 * @addtogroup Surface
 * @{
 *
 * @brief Provides shared memory for multimedia and graphics.
 *
 * This module is used to apply for and release shared memory and is used by the multimedia and graphics
 * modules across processes.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file surface_buffer.h
 *
 * @brief Provides functions such as setting the virtual address, size, and additional attributes of shared memory.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_SURFACE_BUFFER_H
#define GRAPHIC_LITE_SURFACE_BUFFER_H

#include <map>

namespace OHOS {
/**
 *
 * @brief Provides functions such as setting the virtual address, size, and additional attributes of shared memory.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class SurfaceBuffer {
public:
    /**
     * @brief Obtains the virtual address of shared memory for producers and consumers.
     *
     * @return Returns the virtual address of shared memory.
     * @since 1.0
     * @version 1.0
     */
    virtual void* GetVirAddr() const = 0;

    /**
     * @brief Obtains the physical address of shared memory.
     *
     * @return Returns the physical address of shared memory.
     * @since 1.0
     * @version 1.0
     */
    virtual uint64_t GetPhyAddr() const = 0;

    /**
     * @brief Obtains the size of shared memory.
     *
     * @return Returns the size of shared memory.
     * @since 1.0
     * @version 1.0
     */
    virtual uint32_t GetSize() const = 0;

    /**
     * @brief Sets the size of shared memory.
     *
     * @param size Indicates the size of shared memory to set.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetSize(uint32_t size) = 0;

    /**
     * @brief Sets an extra attribute value of the int32 type.
     *
     * Sets an extra attribute value of the int32 type, The extra attribute is stored in the format of <key, value>.
     * Each key corresponds to a value. If the same keys are used in two calls, \n
     * the value in the second call overwrites that in the first call. \n
     *
     * @param key Indicates the key of a key-value pair to set.
     * @param value Indicates the value of the key-value pair to set.
     * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual int32_t SetInt32(uint32_t key, int32_t value) = 0;

    /**
     * @brief Obtains an extra attribute value of the int32 type.
     *
     * Obtains an extra attribute value of the int32 type, The extra attribute is stored in the format of <key, value>.
     * Each key corresponds to a value. If the key does not exist or the value is not int32, <b>-1</b> is returned.
     *
     * @param key Indicates the key of a key-value pair for which the value is to be obtained.
     * @param value Indicates the value of the key-value pair obtained.
     * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual int32_t GetInt32(uint32_t key, int32_t& value) = 0;

    /**
     * @brief Sets an extra attribute value of the int64 type.
     *
     * Sets an extra attribute value of the int64 type. The storage mode of the extra attribute is <key, value>.
     * the value in the second call overwrites that in the first call.
     *
     * @param key Indicates the key of a key-value pair to set.
     * @param value Indicates the value of the key-value pair to set.
     * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual int32_t SetInt64(uint32_t key, int64_t value) = 0;

    /**
     * @brief Obtains an extra attribute value of the int64 type.
     *
     * Obtains an extra attribute value of the int64 type, The extra attribute is stored in the format of <key, value>.
     * Each key corresponds to a value. If the key does not exist or the value is not int64, <b>-1</b> is returned.
     *
     * @param key Indicates the key of a key-value pair for which the value is to be obtained.
     * @param value Indicates the value of the key-value pair obtained.
     * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual int32_t GetInt64(uint32_t key, int64_t& value) = 0;
protected:
    SurfaceBuffer(){}
    virtual ~SurfaceBuffer(){}
};
} // end namespace
#endif
