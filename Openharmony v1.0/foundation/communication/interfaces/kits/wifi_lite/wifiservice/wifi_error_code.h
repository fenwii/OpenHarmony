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
 * @addtogroup wifiservice
 * @{
 *
 * @brief Provides functions for the Wi-Fi station and hotspot modes.
 *
 * You can use this module to enable and disable the Wi-Fi station or hotspot mode, connect to and disconnect from a
 * station or hotspot, query the station or hotspot status, and listen for events. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file wifi_error_code.h
 *
 * @brief Defines error codes of the Wi-Fi service.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef _WIFI_ERROR_CODE_H
#define _WIFI_ERROR_CODE_H

/**
 * @brief Enumerates Wi-Fi error codes.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** No errors. */
    WIFI_SUCCESS = 0,
    /** Invalid parameters */
    ERROR_WIFI_INVALID_ARGS = -1,
    /** Invalid chip */
    ERROR_WIFI_CHIP_INVALID = -2,
    /** Invalid Wi-Fi interface */
    ERROR_WIFI_IFACE_INVALID = -3,
    /** Invalid RTT controller */
    ERROR_WIFI_RTT_CONTROLLER_INVALID = -4,
    /** Wi-Fi not supported by the current version or device */
    ERROR_WIFI_NOT_SUPPORTED = -5,
    /** Wi-Fi unavailable */
    ERROR_WIFI_NOT_AVAILABLE = -6,
    /** Wi-Fi not initialized or started */
    ERROR_WIFI_NOT_STARTED = -7,
    /** System busy */
    ERROR_WIFI_BUSY = -8,
    /** Unknown error */
    ERROR_WIFI_UNKNOWN = -9
} WifiErrorCode;

#endif // _WIFI_ERROR_CODE_H
/** @} */