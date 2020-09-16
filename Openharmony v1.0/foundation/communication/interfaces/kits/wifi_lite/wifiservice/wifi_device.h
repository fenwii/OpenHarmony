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
 * @file wifi_device.h
 *
 * @brief Provides capabilities to enable and disable the station mode, connect to and disconnect from a station,
 * query the station status, and listen for events.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef _WIFI_DEVICE_H
#define _WIFI_DEVICE_H
#include "wifi_event.h"
#include "station_info.h"
#include "wifi_scan_info.h"
#include "wifi_error_code.h"
#include "wifi_linked_info.h"
#include "wifi_device_config.h"

/**
 * @brief Enables the station mode.
 *
 * @return Returns {@link WIFI_SUCCESS} if the station mode is enabled; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode EnableWifi(void);

/**
 * @brief Disables the station mode.
 *
 * @return Returns {@link WIFI_SUCCESS} if the station mode is disabled; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode DisableWifi(void);

/**
 * @brief Checks whether the station mode is enabled.
 *
 * @return Returns {@link WIFI_STA_ACTIVE} if the station mode is enabled; returns {@link WIFI_STA_NOT_ACTIVE}
 * otherwise.
 * @since 1.0
 * @version 1.0
 */
int IsWifiActive(void);

/**
 * @brief Starts a Wi-Fi scan.
 *
 * @return Returns {@link WIFI_SUCCESS} if the Wi-Fi scan is started; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode Scan(void);

/**
 * @brief Obtains an array of hotspots detected in a Wi-Fi scan.
 *
 * The array of hotspots can be obtained only after the Wi-Fi scan is complete. \n
 *
 * @param result Indicates the array of hotspots detected in a Wi-Fi scan. The array is requested and released by the
 * caller. The value must be greater than or equal to {@link WIFI_SCAN_HOTSPOT_LIMIT}.
 * @param size Indicates the size of the array.
 * @return Returns {@link WIFI_SUCCESS} if the array of hotspots detected in the Wi-Fi scan is obtained; returns an
 * error code defined in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetScanInfoList(WifiScanInfo* result, unsigned int* size);

/**
 * @brief Adds a specified hotspot configuration for connecting to a hotspot.
 *
 * This function generates a <b>networkId</b>. \n
 *
 * @param config Indicates the hotspot configuration to add.
 * @param result Indicates the generated <b>networkId</b>. Each <b>networkId</b> matches a hotspot configuration.
 * @return Returns {@link WIFI_SUCCESS} if the specified hotspot configuration is added; returns an error code defined
 * in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode AddDeviceConfig(const WifiDeviceConfig* config, int* result);

/**
 * @brief Obtains all hotspot configurations.
 *
 * Hotspot configurations were added using {@link AddDeviceConfig}. \n
 *
 * @param result Indicates the array of all hotspot configurations. The array is requested and released by the caller.
 * The value must be greater than or equal to {@link WIFI_MAX_CONFIG_SIZE}.
 * @param size Indicates the size of the array.
 * @return Returns {@link WIFI_SUCCESS} if all hotspot configurations are obtained; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetDeviceConfigs(WifiDeviceConfig* result, unsigned int* size);

/**
 * @brief Removes a hotspot configuration matching a specified <b>networkId</b>.
 *
 * @param networkId Indicates the <b>networkId</b> matching the hotspot configuration to remove.
 * @return Returns {@link WIFI_SUCCESS} if the hotspot configuration is removed; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode RemoveDevice(int networkId);

/**
 * @brief Connects to a hotspot matching a specified <b>networkId</b>.
 *
 * Before calling this function, call {@link AddDeviceConfig} to add a hotspot configuration. \n
 *
 * @param networkId Indicates the <b>networkId</b> matching the target hotspot.
 * @return Returns {@link WIFI_SUCCESS} if the hotspot is connected; returns an error code defined in
 * {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode ConnectTo(int networkId);

/**
 * @brief Disconnects this Wi-Fi connection.
 *
 * @return Returns {@link WIFI_SUCCESS} if this Wi-Fi connection is disconnected; returns an error code defined
 * in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode Disconnect(void);

/**
 * @brief Obtains information about the connected hotspot.
 *
 * @param result Indicates the information about the connected hotspot.
 * @return Returns {@link WIFI_SUCCESS} if the information about the connected hotspot is obtained; returns an error
 * code defined in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetLinkedInfo(WifiLinkedInfo* result);

/**
 * @brief Registers a callback for a specified Wi-Fi event.
 *
 * The registered callback will be invoked when the Wi-Fi event defined in {@link WifiEvent} occurs. \n
 *
 * @param event Indicates the event for which the callback is to be registered.
 * @return Returns {@link WIFI_SUCCESS} if the callback is registered successfully; returns an error code defined
 * in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode RegisterWifiEvent(WifiEvent* event);

/**
 * @brief Unregisters a callback previously registered for a specified Wi-Fi event.
 *
 * @param event Indicates the event for which the callback is to be unregistered.
 * @return Returns {@link WIFI_SUCCESS} if the callback is unregistered successfully; returns an error code defined
 * in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode UnRegisterWifiEvent(const WifiEvent* event);

/**
 * @brief Obtains the MAC address of this device.
 *
 *
 *
 * @param result Indicates the MAC address of this device. It is a char array whose length is 6.
 * @return Returns {@link WIFI_SUCCESS} if the MAC address of this device is obtained; returns an error code defined
 * in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode GetDeviceMacAddress(unsigned char* result);

/**
 * @brief Starts a Wi-Fi scan based on a specified parameter.
 *
 * Only results matching the specified parameter will be returned for the Wi-Fi scan.\n
 *
 * @param params Indicates the pointer to the parameter for starting the Wi-Fi scan.
 * For details, see {@link WifiScanParams}.
 * @return Returns {@link WIFI_SUCCESS} if the Wi-Fi scan is started successfully;
 * returns an error code defined in {@link WifiErrorCode} otherwise.
 * @since 1.0
 * @version 1.0
 */
WifiErrorCode AdvanceScan(WifiScanParams *params);
#endif // _WIFI_DEVICE_H
/** @} */
