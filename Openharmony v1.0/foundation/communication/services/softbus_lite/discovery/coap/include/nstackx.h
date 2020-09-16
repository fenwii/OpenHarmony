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
#ifndef NSTACKX_H
#define NSTACKX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#define NSTACKX_MAX_DEVICE_NAME_LEN 64
#define NSTACKX_MAX_MODULE_NAME_LEN 64
#define NSTACKX_MAX_DEVICE_ID_LEN 96
#define NSTACKX_MAX_SENDMSG_DATA_LEN 512
#define NSTACKX_MAX_MAC_STRING_LEN 18
#define NSTACKX_MAX_IP_STRING_LEN 16
#define NSTACKX_MAX_CAPABILITY_NUM 2
#define NSTACKX_MAX_DEVICE_NUM 10
#define NSTACKX_MAX_INTERFACE_NAME_LEN 16
#define NSTACKX_MAX_HICOM_VERSION 16
#define NSTACKX_MAX_SERVICE_DATA_LEN 64

#define NSTACKX_MAX_RESERVED_INFO_LEN 107
#define DEVICE_HASH_LEN 21
#define PUBLISH_DEVICE_NUM 1

#define INNER_DISCOVERY 1
#define PUBLISH_NUM 1
#define COUNT_INIT 0

/* Remote device information */
typedef struct NSTACKX_DeviceInfo {
    char deviceId[NSTACKX_MAX_DEVICE_ID_LEN];
    char deviceName[NSTACKX_MAX_DEVICE_NAME_LEN];
    uint32_t capabilityBitmapNum;
    uint32_t capabilityBitmap[NSTACKX_MAX_CAPABILITY_NUM];
    uint8_t deviceType;
    char version[NSTACKX_MAX_HICOM_VERSION];
    char reservedInfo[NSTACKX_MAX_RESERVED_INFO_LEN];
} NSTACKX_DeviceInfo;

/* Local device information */
typedef struct {
    char name[NSTACKX_MAX_DEVICE_NAME_LEN];
    char deviceId[NSTACKX_MAX_DEVICE_ID_LEN];
    char btMacAddr[NSTACKX_MAX_MAC_STRING_LEN];
    char wifiMacAddr[NSTACKX_MAX_MAC_STRING_LEN];
    char networkIpAddr[NSTACKX_MAX_IP_STRING_LEN];
    char networkName[NSTACKX_MAX_INTERFACE_NAME_LEN];
    uint8_t is5GHzBandSupported;
    int deviceType;
    char version[NSTACKX_MAX_HICOM_VERSION];
} NSTACKX_LocalDeviceInfo;

/* Register local device information with deviceHash */
int NSTACKX_RegisterDeviceAn(const NSTACKX_LocalDeviceInfo *localDeviceInfo, uint64_t deviceHash);

/*
 * NSTACKX Initialization
 * return 0 on success, negative value on failure
 */
int NSTACKX_Init(void);

/* NSTACKX Destruction */
int NSTACKX_Deinit(void);

/*
 * Register the capability of local device.
 * return 0 on success, negative value on failure
 */
int NSTACKX_RegisterCapability(uint32_t capabilityBitmapNum, const uint32_t capabilityBitmap[]);

/*
 * Register the serviceData of local device.
 * return 0 on success, negative value on failure
 */
int NSTACKX_RegisterServiceData(const char* serviceData);

#ifdef __cplusplus
};
#endif

#endif /* #ifndef NSTACKX_H */
