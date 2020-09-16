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
#include "nstackx_device.h"

#include <securec.h>

#include "nstackx_error.h"
#include "os_adapter.h"

#define NSTACKX_DEFAULT_DEVICE_NAME "nStack Device"
#define NSTACKX_RESERVED_INFO_WIFI_IP "wifiIpAddr"
#define NSTACKX_WLAN_INDEX 0
#define NSTACKX_ETH_INDEX 1
#define NSTACKX_MAX_INTERFACE_NUM 4
#define NETWORKTYPE_LENGTH 20

static DeviceInfo g_localDeviceInfo;
static NetworkInterfaceInfo g_interfaceList[NSTACKX_MAX_INTERFACE_NUM];
static char g_networkType[NETWORKTYPE_LENGTH] = {0};
static void GetLocalIp(struct in_addr *ip);

void ClearLocalData(void)
{
    memset_s(&g_localDeviceInfo, sizeof(g_localDeviceInfo), 0, sizeof(g_localDeviceInfo));
    memset_s(&g_interfaceList, sizeof(g_interfaceList), 0, sizeof(g_interfaceList));
    memset_s(g_networkType, sizeof(g_networkType), 0, sizeof(g_networkType));
}
static const NetworkInterfaceInfo *GetLocalInterface(void)
{
    /* Ethernet have higher priority */
    if (g_interfaceList[NSTACKX_ETH_INDEX].ip.s_addr) {
        return &g_interfaceList[NSTACKX_ETH_INDEX];
    }

    if (g_interfaceList[NSTACKX_WLAN_INDEX].ip.s_addr) {
        return &g_interfaceList[NSTACKX_WLAN_INDEX];
    }

    return NULL;
}

static void GetLocalIp(struct in_addr *ip)
{
    const NetworkInterfaceInfo *ifInfo = GetLocalInterface();
    if (ifInfo != NULL) {
        (void)memcpy_s(ip, sizeof(struct in_addr),
                       &ifInfo->ip, sizeof(struct in_addr));
    } else {
        (void)memset_s(ip, sizeof(struct in_addr), 0, sizeof(struct in_addr));
    }
}

/* Return NSTACKX_TRUE if ifName prefix is the same, else return false */
static uint8_t NetworkInterfaceNamePrefixCmp(const char *ifName, const char *prefix)
{
    if (strlen(ifName) < strlen(prefix)) {
        return NSTACKX_FALSE;
    }

    if (memcmp(ifName, prefix, strlen(prefix)) == 0) {
        return NSTACKX_TRUE;
    } else {
        return NSTACKX_FALSE;
    }
}

int UpdateLocalNetworkInterface(const NetworkInterfaceInfo *interfaceInfo)
{
    int ret;
    uint32_t i;
    struct in_addr preIp, newIp;

    if (interfaceInfo == NULL) {
        return NSTACKX_EINVAL;
    }

    GetLocalIp(&preIp);
    for (i = 0; i < NSTACKX_MAX_INTERFACE_NUM; i++) {
        if (NetworkInterfaceNamePrefixCmp(interfaceInfo->name, g_interfaceList[i].name)
            && (i == NSTACKX_ETH_INDEX || i == NSTACKX_WLAN_INDEX)) {
            ret = memcpy_s(&g_interfaceList[i].ip, sizeof(struct in_addr), &interfaceInfo->ip, sizeof(struct in_addr));
            if (ret != EOK) {
                return NSTACKX_EINVAL;
            }
            break;
        }
    }

    if (i == NSTACKX_MAX_INTERFACE_NUM) {
        return NSTACKX_EINVAL;
    }

    GetLocalIp(&newIp);
    if (newIp.s_addr == preIp.s_addr) {
        return NSTACKX_EOK;
    }

    if (interfaceInfo->ip.s_addr == 0) {
        if (strcmp(g_networkType, interfaceInfo->name) != 0 && strcmp(g_networkType, "") != 0) {
            return NSTACKX_EOK;
        }
    } else {
        ret = strncpy_s(g_networkType, sizeof(g_networkType), interfaceInfo->name, strlen(interfaceInfo->name));
        if (ret != EOK) {
            return NSTACKX_EFAILED;
        }
    }

    return NSTACKX_EOK;
}

void SetDeviceHash(uint64_t deviceHash)
{
    (void)memset_s(g_localDeviceInfo.deviceHash, sizeof(g_localDeviceInfo.deviceHash),
        0, sizeof(g_localDeviceInfo.deviceHash));
    if (sprintf_s(g_localDeviceInfo.deviceHash, DEVICE_HASH_LEN,
        "%lu", deviceHash) == -1) {
        SOFTBUS_PRINT("[DISCOVERY] Set Device Hash fail\n");
    }
}

int ConfigureLocalDeviceInfo(const NSTACKX_LocalDeviceInfo *localDeviceInfo)
{
    char deviceId[NSTACKX_MAX_DEVICE_ID_LEN];
    struct in_addr ipAddr;
    NetworkInterfaceInfo interfaceInfo;

    (void)memset_s(&interfaceInfo, sizeof(interfaceInfo), 0, sizeof(interfaceInfo));
    (void)memcpy_s(deviceId, sizeof(deviceId), g_localDeviceInfo.deviceId, sizeof(deviceId));
    if (strcpy_s(g_localDeviceInfo.deviceId, sizeof(g_localDeviceInfo.deviceId), localDeviceInfo->deviceId) != EOK) {
        if (memcpy_s(g_localDeviceInfo.deviceId, sizeof(g_localDeviceInfo.deviceId),
            deviceId, sizeof(deviceId)) != EOK) {
        }
        return NSTACKX_EINVAL;
    }

    if ((inet_pton(AF_INET, localDeviceInfo->networkIpAddr, &ipAddr) == 1) &&
        (strcpy_s(interfaceInfo.name, sizeof(interfaceInfo.name), localDeviceInfo->networkName) == EOK)) {
        interfaceInfo.ip = ipAddr;
        UpdateLocalNetworkInterface(&interfaceInfo);
    }

    if (strlen(localDeviceInfo->name) == 0 || (strncpy_s(g_localDeviceInfo.deviceName,
        sizeof(g_localDeviceInfo.deviceName), localDeviceInfo->name, NSTACKX_MAX_DEVICE_NAME_LEN - 1) != EOK)) {
        (void)strcpy_s(g_localDeviceInfo.deviceName, sizeof(g_localDeviceInfo.deviceName), NSTACKX_DEFAULT_DEVICE_NAME);
    }

    if (strcpy_s(g_localDeviceInfo.version, sizeof(g_localDeviceInfo.version), localDeviceInfo->version) != EOK) {
        return NSTACKX_EINVAL;
    }

    g_localDeviceInfo.deviceType = localDeviceInfo->deviceType;

    return NSTACKX_EOK;
}

const DeviceInfo *GetLocalDeviceInfo(void)
{
    return &g_localDeviceInfo;
}

uint8_t IsWifiApConnected(void)
{
    struct in_addr ip;
    GetLocalIp(&ip);

    if (ip.s_addr != 0) {
        return NSTACKX_TRUE;
    } else {
        return NSTACKX_FALSE;
    }
}

int GetLocalIpString(char *ipString, size_t length)
{
    struct in_addr ip;
    GetLocalIp(&ip);
    if (ip.s_addr == 0) {
        return NSTACKX_EFAILED;
    }

    if (inet_ntop(AF_INET, &ip, ipString, length) == NULL) {
        return NSTACKX_EFAILED;
    }
    return NSTACKX_EOK;
}

int RegisterCapability(uint32_t capabilityBitmapNum, const uint32_t capabilityBitmap[])
{
    (void)memset_s(g_localDeviceInfo.capabilityBitmap, sizeof(g_localDeviceInfo.capabilityBitmap),
        0, sizeof(g_localDeviceInfo.capabilityBitmap));
    if (capabilityBitmapNum) {
        if (memcpy_s(g_localDeviceInfo.capabilityBitmap, sizeof(g_localDeviceInfo.capabilityBitmap),
            capabilityBitmap, sizeof(uint32_t) * capabilityBitmapNum) != EOK) {
            return NSTACKX_EFAILED;
        }
    }
    g_localDeviceInfo.capabilityBitmapNum = capabilityBitmapNum;
    return NSTACKX_EOK;
}

int RegisterServiceData(const char* serviceData, int length)
{
    if (serviceData == NULL) {
        return NSTACKX_EINVAL;
    }

    (void)memset_s(g_localDeviceInfo.serviceData, sizeof(g_localDeviceInfo.serviceData),
        0, sizeof(g_localDeviceInfo.serviceData));
    if (strcpy_s(g_localDeviceInfo.serviceData, NSTACKX_MAX_SERVICE_DATA_LEN, serviceData) != EOK)  {
        return NSTACKX_EFAILED;
    }

    (void)length;
    return NSTACKX_EOK;
}
