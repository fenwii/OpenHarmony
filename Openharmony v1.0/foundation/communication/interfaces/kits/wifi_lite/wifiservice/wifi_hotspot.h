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
 * @file wifi_hotspot.h
 *
 * @brief Provides capabilities to enable and disable the hotspot mode, connect to and disconnect from a hotspot, query
 * the hotspot status, and listen for events.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef _WIFI_HOTSPOT_H
#define _WIFI_HOTSPOT_H
#include "wifi_device.h"
#include "wifi_error_code.h"
#include "wifi_hotspot_config.h"
#include "wifi_event.h"

/**
 * @brief Defines the default channel of the hotspot mode.
 */
#define HOTSPOT_DEFAULT_CHANNEL 6

/**
 * @brief Enables the hotspot mode.
 *
 * Before using this function, you need to invoke {@link SetHotspotConfig} and set at least the SSID, security type,
 * and key. \n
 *
 * @return Returns {@link WIFI_SUCCESS} if the hotspot mode is enabled; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode EnableHotspot(void);

/**
 * @brief Disables the hotspot mode.
 *
 * @return Returns {@link WIFI_SUCCESS} if the hotspot mode is disabled; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode DisableHotspot(void);

/**
 * @brief Sets a specified hotspot configuration.
 *
 * The hotspot configuration includes the SSID, security type, and key. The configuration set overwrites the existing
 * configuration and takes effect after the hotspot mode is re-enabled. \n
 * Before enabling the hotspot mode for the first time, you must call this function. \n
 *
 * @param config Indicates the hotspot configuration to set.
 * @return Returns {@link WIFI_SUCCESS} if the hotspot configuration is set; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0 */
WifiErrorCode SetHotspotConfig(const HotspotConfig* config);

/**
 * @brief Obtains a specified hotspot configuration.
 *
 * The hotspot configuration includes the SSID, security type, and key. \n
 *
 * @param result Indicates the obtained hotspot configuration.
 * @return Returns {@link WIFI_SUCCESS} if the hotspot configuration is obtained; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetHotspotConfig(HotspotConfig* result);

/**
 * @brief Checks whether the hotspot mode is enabled.
 *
 * @return Returns {@link WIFI_HOTSPOT_ACTIVE} if the hotspot mode is enabled; returns {@link WIFI_HOTSPOT_NOT_ACTIVE}
 * otherwise.
 * @since 1.0
 * @version 1.0
 */
int IsHotspotActive(void);

/**
 * @brief Obtains an array of stations connected to this hotspot.
 *
 * The station information is defined in {@link StationInfo}. \n
 *
 * @param result Indicates the array of stations connected to this hotspot. The array is requested and released by the
 * caller. The value must be greater than or equal to {@link WIFI_MAX_STA_NUM}.
 * @param size Indicates the size of the array.
 * @return Returns {@link WIFI_SUCCESS} if the array of stations connected to this hotspot is obtained; returns an error
 *  code defined in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetStationList(StationInfo* result, unsigned int* size);

/**
 * @brief Obtains the signal level indicated by a specified received signal strength indicator (RSSI) and frequency
 * band.
 *
 *
 * Based on the signal level, you can display the signal strength represented by the number of signal bars. \n
 *
 * @param rssi Indicates the RSSI.
 * @param band Indicates the frequency band, either {@link HOTSPOT_BAND_TYPE_5G} or {@link HOTSPOT_BAND_TYPE_2G}.
 * @return Returns the signal level if it is obtained; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetSignalLevel(int rssi, int band);

#endif // _WIFI_HOTSPOT_H_
/** @} */
