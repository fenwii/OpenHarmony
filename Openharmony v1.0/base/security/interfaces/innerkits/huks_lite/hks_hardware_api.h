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

#ifndef HKS_HARDWARE_API_H
#define HKS_HARDWARE_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * get hardware UDID(Unique Device Identifier)
 *
 * udid: UDID(Unique Device Identifier)
 * udid_len: The length of UDID
 * return == 0 write ok, return < 0 other error
 */
typedef int32_t (*hks_get_hardware_udid_callback)(uint8_t *udid,
    uint32_t udid_len);

/*
 * Register callback for get hardware UDID(Unique Device Identifier)
 *
 * callbacks: The callback functions for get hardware UDID
 * return 0 ok, other error
 */
#ifndef HKS_API_PUBLIC
#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
#ifdef HKS_DLL_EXPORT
__declspec(dllexport) int32_t hks_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback);
#else
__declspec(dllimport) int32_t hks_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback);
#endif
#else
__attribute__ ((visibility("default"))) int32_t hks_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback);
#endif
#else
__attribute__ ((visibility("default"))) int32_t hks_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HKS_HARDWARE_API_H */
