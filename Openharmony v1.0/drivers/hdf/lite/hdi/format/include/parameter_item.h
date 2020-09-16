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
 * @addtogroup format
 * @{
 *
 * @brief Defines format-related APIs.
 *
 * For example, you use this module to define custom data types and to initialize, create,
 * destroy the muxer and demuxer, and set their parameters. Also, you can read demuxer data frames,
 * select demuxer tracks, add muxer tracks, and write data frames into a container.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file parameter_item.h
 *
 * @brief Defines format-related structures and enumerations used to configure and obtain dynamic parameters.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef PARAMETER_ITEM_H
#define PARAMETER_ITEM_H

/**
 * @brief Enumerates key types used for setting and obtaining parameters.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    KEY_TYPE_MIME = 0x6d696d65,         /**< MIME type. The value type is <b>cstring</b>. */
    KEY_TYPE_HTTP_HEADERS = 0x68706864, /**< HTTP header. The value type is <b>cstring</b>. */
    KEY_TYPE_LANGUAGE     = 0x6c616e67, /**< Track language, which is usually the language of audio and subtitles.
                                         * The value type is <b>cstring</b>.
                                         */
    KEY_TYPE_PRE_CACHE    = 0x70726361  /**< Precapture cache size. The value type is <b>int</b> */
} KeyType;

/**
 * @brief Defines a structure for configuring and obtaining dynamic parameters.
 */
typedef struct {
    uint32_t key; /**< Key type. For details, see {@link KeyType} */
    int32_t size; /**< Data size, which indicates the size of the buffer memory pointed by <b>pValue</b> */
    /**
     * @brief Defines value types of the parameters.
     */
    union {
        int32_t s32Value;  /**< 32-bit integer */
        uint32_t u32Value; /**< 32-bit unsigned integer */
        int64_t s64Value;  /**< 64-bit integer */
        uint64_t u64Value; /**< 64-bit unsigned integer */
        float fValue;      /**< Single-precision floating point number */
        double dValue;      /**< Double-precision floating point number */
        const void *pValue; /**< Pointer */
    } value;
} ParameterItem;

#endif  // PARAMETER_ITEM_H
/** @} */