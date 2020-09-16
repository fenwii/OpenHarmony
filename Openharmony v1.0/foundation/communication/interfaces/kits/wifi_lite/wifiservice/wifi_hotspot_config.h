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
 * @file wifi_hotspot_config.h
 *
 * @brief Defines the Wi-Fi hotspot configuration.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef _WIFI_HOTSPOT_CONFIG_H
#define _WIFI_HOTSPOT_CONFIG_H
#include "wifi_device_config.h"
#include "wifi_error_code.h"

/**
 * @brief Defines the maximum number of stations connected to a hotspot.
 */
#define WIFI_MAX_STA_NUM 6

/**
 * @brief Enumerates received signal strength indicator (RSSI) levels.
 *
 * Four RSSI levels are available: 1 to 4. The higher the RSSI level, the stronger the Wi-Fi signal.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** Level 1. The RSSI value for a 2.4 GHz hotspot ranges from <b>-88</b> (included) to <b>-82</b> (excluded),
     * and that for a 5 GHz hotspot ranges from <b>-85</b> (included) to <b>-79</b> (excluded). */
    RSSI_LEVEL_1 = 1,
    /** Level 2. The RSSI value for a 2.4 GHz hotspot ranges from <b>-82</b> (included) to <b>-75</b> (excluded),
     * and that for a 5 GHz hotspot ranges from <b>-79</b> (included) to <b>-72</b> (excluded). */
    RSSI_LEVEL_2 = 2,
    /** Level 3. The RSSI value for a 2.4 GHz hotspot ranges from <b>-75</b> (included) to <b>-65</b> (excluded),
     * and that for a 5 GHz hotspot ranges from <b>-72</b> (included) to <b>-65</b> (excluded). */
    RSSI_LEVEL_3 = 3,
    /** Level 4. The RSSI value for a 2.4 GHz or 5 GHz hotspot is greater than or equal to <b>-65</b>. */
    RSSI_LEVEL_4 = 4,
} RssiLevel;

/**
 * @brief Enumerates frequency bands supported by the Wi-Fi hotspot mode.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** 2.4 GHz */
    HOTSPOT_BAND_TYPE_2G = 1,
    /** 5 GHz */
    HOTSPOT_BAND_TYPE_5G = 2,
} HotspotBandType;

/**
 * @brief Represents the hotspot configuration.
 *
 * A hotspot configuration must contain the SSID (or BSSID), security type, and key (if the security type is open). \n
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /** Service set ID (SSID). For its length, see {@link WIFI_MAX_SSID_LEN}. */
    char ssid[WIFI_MAX_SSID_LEN];
    /** Security type */
    int securityType;
    /** Frequency band */
    int band;
    /** Channel number */
    int channelNum;
    /** Key. For its length, see {@link WIFI_MAX_SSID_LEN}. */
    char preSharedKey[WIFI_MAX_KEY_LEN];
} HotspotConfig;

/**
 * @brief Sets the frequency band for this hotspot.
 *
 * @param band Indicates the frequency band to set.
 * @return Returns {@link WIFI_SUCCESS} if the frequency band is set; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode SetBand(int band);

/**
 * @brief Obtains the frequency band of this hotspot.
 *
 * @param result Indicates the obtained frequency band.
 * @return Returns {@link WIFI_SUCCESS} if the frequency band is obtained; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetBand(int* result);

#endif // _WIFI_HOTSPOT_CONFIG_H
/** @} */
