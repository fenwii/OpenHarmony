/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _HKS_FILE_API_H
#define _HKS_FILE_API_H

#include <stdint.h>
#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct hks_file_callbacks {
    /*
     * Read data from file or flash
     *
     * filename: The path name of the file
     * offset: param reserved for future use
     * buf: The buffer used to store the content readed from the file
     * len: The size count in buffer trying to read from the file
     * return < 0 read error, return > 0 real read length,
     * return == 0 secret key information does not exist in storage media
     */
    int32_t (*read)(const char *file_name, uint32_t offset,
        uint8_t *buf, uint32_t len);

    /*
     * Write data into file or flash
     *
     * filename: The path name of the file
     * offset: param reserved for future use
     * buf: The content which you want write into the file
     * len: The size of the content
     * return == 0 write ok, return < 0 other error
     */
    int32_t (*write)(const char *file_name, uint32_t offset,
        const uint8_t *buf, uint32_t len);

    /*
     * Get file size
     *
     * filename: The path name of the file
     * return  < 0 error, >= 0 The size of the file
     * flash can return a fixed value of 4096
     */
    int32_t (*file_size)(const char *file_name);
};

/*
 * Register file operation callbacks
 *
 * callbacks: The callback functions for file operation
 * return 0 ok, other error
 */
#ifndef HKS_API_PUBLIC
#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
#ifdef HKS_DLL_EXPORT
__declspec(dllexport) int32_t hks_register_file_callbacks(
    struct hks_file_callbacks *callbacks);
#else
__declspec(dllimport) int32_t hks_register_file_callbacks(
    struct hks_file_callbacks *callbacks);
#endif
#else
__attribute__ ((visibility("default"))) int32_t hks_register_file_callbacks(
    struct hks_file_callbacks *callbacks);
#endif
#else
__attribute__ ((visibility("default"))) int32_t hks_register_file_callbacks(
    struct hks_file_callbacks *callbacks);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _HKS_FILE_API_H */
