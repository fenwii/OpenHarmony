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
#include "coap_service.h"
#include "coap_discover.h"
#include "coap_socket.h"
#include "common_info_manager.h"
#include "discovery_error.h"
#include "nstackx.h"
#include "os_adapter.h"
#include "securec.h"
#define DEV_HASH_ID 0
#define WLAN_NAME "wlan0"
#define DEV_DEFAULT_TYPE 14
typedef struct {
    char packageName[MAX_PACKAGE_NAME];
    unsigned int capabilityBitmap[MAX_CAPABILITY_NUM];
    char custData[MAX_SERVICE_DATA_LEN];
} PackageModule;

static int CoapGetLocalDeviceInfo(NSTACKX_LocalDeviceInfo *nstackInfo)
{
    if (nstackInfo == NULL) {
        return -1;
    }

    DeviceInfo *info = GetCommonDeviceInfo();
    if (info == NULL) {
        return ERROR_FAIL;
    }

    unsigned int ret;
    ret = (unsigned int)strcpy_s(nstackInfo->networkName, sizeof(nstackInfo->networkName), WLAN_NAME);
    ret |= (unsigned int)strcpy_s(nstackInfo->networkIpAddr, sizeof(nstackInfo->networkIpAddr), info->deviceIp);
    ret |= (unsigned int)strcpy_s(nstackInfo->name, sizeof(nstackInfo->name), info->deviceName);
    if (ret != 0) {
        return ERROR_FAIL;
    }

    if (sprintf_s(nstackInfo->deviceId, sizeof(nstackInfo->deviceId), "{\"UDID\":\"%s\"}", info->deviceId) == -1) {
        SOFTBUS_PRINT("[DISCOVERY] CoapGetLocalDeviceInfo set deviceid fail\n");
        return ERROR_FAIL;
    }
    nstackInfo->deviceType = info->deviceType;

    return ERROR_SUCCESS;
}

int CoapRegisterDeviceInfo(void)
{
    NSTACKX_LocalDeviceInfo localDeviceInfo;
    int ret;

    (void)memset_s(&localDeviceInfo, sizeof(NSTACKX_LocalDeviceInfo), 0, sizeof(NSTACKX_LocalDeviceInfo));
    ret = CoapGetLocalDeviceInfo(&localDeviceInfo);
    if (ret != 0) {
        return ERROR_FAIL;
    }

    ret = NSTACKX_RegisterDeviceAn(&localDeviceInfo, DEV_HASH_ID);
    if (ret != 0) {
        SOFTBUS_PRINT("[DISCOVERY] CoapRegisterDeviceInfo RegisterDeviceAn fail\n");
        return ERROR_FAIL;
    }

    return ERROR_SUCCESS;
}

int CoapRegisterDefualtService(void)
{
    DeviceInfo *info = GetCommonDeviceInfo();
    if (info == NULL) {
        return ERROR_FAIL;
    }

    char serviceData[MAX_DEFAULT_SERVICE_DATA_LEN] = {0};
    if (sprintf_s(serviceData, sizeof(serviceData), "port:%d", info->devicePort) == -1) {
        return ERROR_FAIL;
    }

    return NSTACKX_RegisterServiceData(serviceData);
}

int CoapInit(void)
{
    int ret = NSTACKX_Init();
    if (ret != 0) {
        SOFTBUS_PRINT("[DISCOVERY] CoapInit NSTACKX_Init fail\n");
        return ERROR_FAIL;
    }
    return ERROR_SUCCESS;
}

int CoapDeinit(void)
{
    int ret = NSTACKX_Deinit();
    if (ret != 0) {
        return ret;
    }
    return ERROR_SUCCESS;
}

int CoapRegistService(const unsigned int capabilityBitmap[], int length, const char* capabilityData)
{
    if (capabilityData == NULL || capabilityBitmap == NULL) {
        return ERROR_INVALID;
    }

    if (NSTACKX_RegisterCapability(MAX_CAPABILITY_NUM, capabilityBitmap) != 0) {
        SOFTBUS_PRINT("[DISCOVERY] CoapRegistService RegisterCapability fail\n");
        return ERROR_CAPABLITY_FAIL;
    }

    if (NSTACKX_RegisterServiceData(capabilityData) != 0) {
        return ERROR_SERVICEDATA_FAIL;
    }
    (void)length;
    return ERROR_SUCCESS;
}
