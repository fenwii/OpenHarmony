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
 * @addtogroup kv_store
 * @{
 *
 * @brief Provides functions for obtaining, setting, and deleting a key-value pair.
 *
 *
 * Key-value pairs can be permanently stored in the file system. \n
 * If {@link FEATURE_KV_CACHE} is enabled, key-value pairs can be stored in the cache. \n
 * For details about cache specifications, see {@link MAX_CACHE_SIZE}. \n
 * For details about the number of key-value pairs that can be stored in an application, see {@link MAX_KV_SUM}. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file kv_store.h
 *
 * @brief Provides functions for obtaining, setting, and deleting a key-value pair.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef KV_STORE_API_H
#define KV_STORE_API_H

#include "utils_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Obtains the value matching a specified key from the file system or cache.
 *
 * @param key Indicates the key to be indexed. It allows only lowercase letters, digits, underscores (_), and dots (.).
 * Its length cannot exceed 32 bytes (including the end-of-text character in the string).
 * @param value Indicates the buffer for storing the value that matches the key. This is an output parameter.
 * @param len Indicates the size of the value space in the buffer.
 * @return Returns the length of the value if the operation is successful;
 * returns <b>-9</b> if a parameter is incorrect; returns <b>-1</b> in other scenarios;
 * returns <b>0</b> if the value is obtained from the cache.
 * @since 1.0.
 * @version 1.0.
 */
int UtilsGetValue(const char* key, char* value, unsigned int len);

/**
 * @brief Adds or updates the value matching a specified key in the file system or cache.
 *
 * @param key Indicates the key whose value is to be added or updated.
 * It allows only lowercase letters, digits, underscores (_), and dots (.).
 * Its length cannot exceed 32 bytes (including the end-of-text character in the string).
 * @param value Indicates the value to be added or updated.
 * Its length cannot exceed 128 bytes (including the end-of-text character in the string).
 * @return Returns <b>0</b> if the operation is successful; returns <b>-9</b> if a parameter is incorrect;
 * returns <b>-1</b> in other scenarios.
 * @since 1.0.
 * @version 1.0.
 */
int UtilsSetValue(const char* key, const char* value);

/**
 * @brief Deletes the value matching a specified key from the file system or cache.
 *
 * @param key Indicates the key whose value is to be deleted.
 * It allows only lowercase letters, digits, underscores (_), and dots (.).
 * Its length cannot exceed 32 bytes (including the end-of-text character in the string).
 * @return Returns <b>0</b> if the operation is successful; returns <b>-9</b> if a parameter is incorrect;
 * returns <b>-1</b> in other scenarios.
 * @since 1.0.
 * @version 1.0.
 */
int UtilsDeleteValue(const char* key);

#ifdef FEATURE_KV_CACHE

/**
 * @brief Clears all key-value pairs from the cache.
 *
 * @attention This function is available only if {@link FEATURE_KV_CACHE} is enabled.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0.
 * @version 1.0.
 */
int ClearKVCache(void);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // KV_STORE_API_H
/** @} */