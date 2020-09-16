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
#ifndef NSTACKX_DEVICE_H
#define NSTACKX_DEVICE_H

#include "nstackx.h"
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include "lwip/sockets.h"
#else
#include <arpa/inet.h>
#endif
enum NetChannelState {
    NET_CHANNEL_STATE_START,
    NET_CHANNEL_STATE_DISABLED,
    NET_CHANNEL_STATE_DISCONNECT,
    NET_CHANNEL_STATE_CONNETING,
    NET_CHANNEL_STATE_CONNETED,
    NET_CHANNEL_STATE_END,
};

typedef struct {
    char name[NSTACKX_MAX_INTERFACE_NAME_LEN];
    struct in_addr ip;
} NetworkInterfaceInfo;

typedef struct {
    struct in_addr ip;
    uint8_t state;
    /* AP information? */
} WifiApChannelInfo;

typedef struct {
    WifiApChannelInfo wifiApInfo;
} NetChannelInfo;

typedef struct DeviceInfo {
    char deviceName[NSTACKX_MAX_DEVICE_NAME_LEN];
    char deviceId[NSTACKX_MAX_DEVICE_ID_LEN];
    int deviceType;
    uint16_t portNumber;
    NetChannelInfo netChannelInfo;
    /* Capability data */
    uint32_t capabilityBitmapNum;
    uint32_t capabilityBitmap[NSTACKX_MAX_CAPABILITY_NUM];
    char version[NSTACKX_MAX_HICOM_VERSION];
    uint8_t mode;
    char deviceHash[DEVICE_HASH_LEN];
    char serviceData[NSTACKX_MAX_SERVICE_DATA_LEN];
} DeviceInfo;
void SetDeviceHash(uint64_t deviceHash);
void ClearLocalData(void);
int ConfigureLocalDeviceInfo(const NSTACKX_LocalDeviceInfo *localDeviceInfo);
int UpdateLocalNetworkInterface(const NetworkInterfaceInfo *interfaceInfo);
const DeviceInfo *GetLocalDeviceInfo(void);
uint8_t IsWifiApConnected(void);
int GetLocalIpString(char *ipString, size_t length);
int GetLocalInterfaceName(char *ifName, size_t ifNameLength);
int RegisterCapability(uint32_t capabilityBitmapNum, const uint32_t capabilityBitmap[]);
int RegisterServiceData(const char* serviceData, int length);
#endif /* #ifndef NSTACKX_DEVICE_H */
