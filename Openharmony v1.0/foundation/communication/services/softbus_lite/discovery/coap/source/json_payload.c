/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "json_payload.h"

#include <securec.h>

#include "cJSON.h"
#include "nstackx_device.h"
#include "nstackx_error.h"
#include "os_adapter.h"

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#else
#include <arpa/inet.h>
#endif

#define TAG "nStackXCoAP"

#define JSON_COAP_URI "coapUri"
#define JSON_CAPABILITY_BITMAP "capabilityBitmap"

#define JSON_DEVICE_ID "deviceId"
#define JSON_DEVICE_NAME "devicename"
#define JSON_DEVICE_WLAN_IP "wlanIp"
#define JSON_DEVICE_TYPE "type"
#define JSON_HICOM_VERSION "hicomversion"
#define JSON_REQUEST_MODE "mode"
#define JSON_DEVICE_HASH "deviceHash"
#define JSON_SERVICE_DATA "serviceData"
#define NSTACKX_MAX_URI_BUFFER_LENGTH 64

static int AddDeviceJsonData(cJSON *data, const DeviceInfo *deviceInfo)
{
    cJSON *item = cJSON_CreateString(deviceInfo->deviceId);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_DEVICE_ID, item)) {
        goto ERROR;
    }

    item = cJSON_CreateString(deviceInfo->deviceName);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_DEVICE_NAME, item)) {
        goto ERROR;
    }

    item = cJSON_CreateNumber(deviceInfo->deviceType);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_DEVICE_TYPE, item)) {
        goto ERROR;
    }

    item = cJSON_CreateString(deviceInfo->version);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_HICOM_VERSION, item)) {
        goto ERROR;
    }

    item = cJSON_CreateNumber(deviceInfo->mode);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_REQUEST_MODE, item)) {
        goto ERROR;
    }

    item = cJSON_CreateString(deviceInfo->deviceHash);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_DEVICE_HASH, item)) {
        goto ERROR;
    }

    item = cJSON_CreateString(deviceInfo->serviceData);
    if (item == NULL || !cJSON_AddItemToObject(data, JSON_SERVICE_DATA, item)) {
        goto ERROR;
    }
    return NSTACKX_EOK;
ERROR:
    if (item != NULL) {
        cJSON_Delete(item);
    }
    return NSTACKX_EFAILED;
}

static int AddWifiApJsonData(cJSON *data)
{
    cJSON *item = NULL;
    char ipString[INET_ADDRSTRLEN] = {0};

    if (GetLocalIpString(ipString, sizeof(ipString)) != NSTACKX_EOK) {
        return NSTACKX_EFAILED;
    }

    item = cJSON_CreateString(ipString);
    if (item == NULL) {
        return NSTACKX_EFAILED;
    }

    if (!cJSON_AddItemToObject(data, JSON_DEVICE_WLAN_IP, item)) {
        cJSON_Delete(item);
        return NSTACKX_EFAILED;
    }

    return NSTACKX_EOK;
}

static int AddCapabilityBitmap(cJSON *data, const DeviceInfo *deviceInfo)
{
    cJSON *capabilityArray = NULL;
    cJSON *capability = NULL;
    uint32_t i;

    if (deviceInfo->capabilityBitmapNum == 0) {
        return NSTACKX_EOK;
    }

    capabilityArray = cJSON_CreateArray();
    if (capabilityArray == NULL) {
        goto L_END_JSON;
    }

    for (i = 0; i < deviceInfo->capabilityBitmapNum; i++) {
        capability = cJSON_CreateNumber(deviceInfo->capabilityBitmap[i]);
        if (capability == NULL) {
            goto L_END_JSON;
        }
        cJSON_AddItemToArray(capabilityArray, capability);
    }
    cJSON_AddItemToObject(data, JSON_CAPABILITY_BITMAP, capabilityArray);

    return NSTACKX_EOK;

L_END_JSON:
    if (capabilityArray != NULL) {
        cJSON_Delete(capabilityArray);
        capabilityArray = NULL;
    }
    return NSTACKX_EFAILED;
}

static int ParseDeviceJsonData(const cJSON *data, DeviceInfo *dev)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(data, JSON_DEVICE_ID);
    if (!cJSON_IsString(item) || !strlen(item->valuestring)) {
        return NSTACKX_EINVAL;
    }
    if (strcpy_s(dev->deviceId, sizeof(dev->deviceId), item->valuestring)) {
        return NSTACKX_EFAILED;
    }

    item = cJSON_GetObjectItemCaseSensitive(data, JSON_DEVICE_NAME);
    if (!cJSON_IsString(item) || !strlen(item->valuestring)) {
        return NSTACKX_EINVAL;
    }
    if (strcpy_s(dev->deviceName, sizeof(dev->deviceName), item->valuestring)) {
        return NSTACKX_EFAILED;
    }

    item = cJSON_GetObjectItemCaseSensitive(data, JSON_DEVICE_TYPE);
    if (!cJSON_IsNumber(item) || (item->valuedouble < 0) || (item->valuedouble > 0xFF)) {
        return NSTACKX_EINVAL;
    }
    dev->deviceType = (uint8_t)item->valuedouble;

    item = cJSON_GetObjectItemCaseSensitive(data, JSON_HICOM_VERSION);
    if (!cJSON_IsString(item) || !strlen(item->valuestring)) {
        return NSTACKX_EOK;
    }
    if (strcpy_s(dev->version, sizeof(dev->version), item->valuestring)) {
        return NSTACKX_EFAILED;
    }

    return NSTACKX_EOK;
}

static void ParseWifiApJsonData(const cJSON *data, DeviceInfo *dev)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(data, JSON_DEVICE_WLAN_IP);
    if (cJSON_IsString(item)) {
        if (inet_pton(AF_INET, item->valuestring, &(dev->netChannelInfo.wifiApInfo.ip)) != 1) {
        } else {
            dev->netChannelInfo.wifiApInfo.state = NET_CHANNEL_STATE_CONNETED;
        }
    }
}

static void ParseModeJsonData(const cJSON *data, DeviceInfo *dev)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(data, JSON_REQUEST_MODE);
    if (item == NULL) {
        return;
    }
    if (!cJSON_IsNumber(item) || (item->valuedouble < 0)) {
    } else {
        if (dev == NULL) {
            return;
        }
        dev->mode = (uint8_t)item->valuedouble;
    }
}

static void ParseDeviceHashData(const cJSON *data, DeviceInfo *dev)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(data, JSON_DEVICE_HASH);
    if (item == NULL) {
        return;
    }
    if (!cJSON_IsString(item) || !strlen(item->valuestring)) {
        return;
    }
    if (strcpy_s(dev->deviceHash, sizeof(dev->deviceHash), item->valuestring)) {
        return;
    }
}

static void ParseServiceDataJsonData(const cJSON *data, DeviceInfo *dev)
{
    cJSON *item = NULL;
    item = cJSON_GetObjectItemCaseSensitive(data, JSON_SERVICE_DATA);
    if (item == NULL) {
        return;
    }
    if (!cJSON_IsString(item)) {
        return;
    }
    if (strcpy_s(dev->serviceData, sizeof(dev->serviceData), item->valuestring)) {
        return;
    }
}

static void ParseCapabilityBitmap(const cJSON *data, DeviceInfo *deviceInfo)
{
    cJSON *capability = NULL;
    cJSON *item = NULL;
    uint32_t capabilityBitmapNum = 0;

    item = cJSON_GetObjectItemCaseSensitive(data, JSON_CAPABILITY_BITMAP);
    if (cJSON_IsArray(item)) {
        cJSON_ArrayForEach(capability, item) {
            if (capabilityBitmapNum >= NSTACKX_MAX_CAPABILITY_NUM) {
                break;
            }

            if (!cJSON_IsNumber(capability) || capability->valuedouble < 0 || capability->valuedouble > 0xFFFFFFFF) {
                /* skip invalid capability */
                continue;
            }
            deviceInfo->capabilityBitmap[capabilityBitmapNum++] = (uint32_t)capability->valuedouble;
        }
    }
    deviceInfo->capabilityBitmapNum = capabilityBitmapNum;
}

char *PrepareServiceDiscover(void)
{
    char *formatString = NULL;
    const DeviceInfo *deviceInfo = GetLocalDeviceInfo();
    cJSON *data = NULL;

    data = cJSON_CreateObject();
    if (data == NULL) {
        goto L_END_JSON;
    }

    if ((AddDeviceJsonData(data, deviceInfo) != NSTACKX_EOK) || (AddWifiApJsonData(data) != NSTACKX_EOK) ||
        (AddCapabilityBitmap(data, deviceInfo) != NSTACKX_EOK)) {
        goto L_END_JSON;
    }

    formatString = cJSON_PrintUnformatted(data);
    if (formatString == NULL) {
        SOFTBUS_PRINT("[DISCOVERY] PrepareServiceDiscover format fail\n");
    }

L_END_JSON:
    if (data != NULL) {
        cJSON_Delete(data);
        data = NULL;
    }
    return formatString;
}

int ParseServiceDiscover(const uint8_t *buf, DeviceInfo *deviceInfo, char **remoteUrlPtr)
{
    char *remoteUrl = NULL;
    cJSON *data = NULL;
    cJSON *item = NULL;

    if (buf == NULL || deviceInfo == NULL || remoteUrlPtr == NULL) {
        return NSTACKX_EINVAL;
    }

    data = cJSON_Parse((char *)buf);
    if (data == NULL) {
        return NSTACKX_EINVAL;
    }

    if (ParseDeviceJsonData(data, deviceInfo) != NSTACKX_EOK) {
        cJSON_Delete(data);
        return NSTACKX_EINVAL;
    }

    ParseWifiApJsonData(data, deviceInfo);
    ParseCapabilityBitmap(data, deviceInfo);
    ParseModeJsonData(data, deviceInfo);
    ParseDeviceHashData(data, deviceInfo);
    ParseServiceDataJsonData(data, deviceInfo);

    item = cJSON_GetObjectItemCaseSensitive(data, JSON_COAP_URI);
    if (item != NULL) {
        if (cJSON_IsString(item)) {
            remoteUrl = strdup(item->valuestring);
        }
    }

    cJSON_Delete(data);
    data = NULL;

    if (remoteUrl == NULL) {
        return NSTACKX_EINVAL;
    }

    *remoteUrlPtr = remoteUrl;
    return NSTACKX_EOK;
}
