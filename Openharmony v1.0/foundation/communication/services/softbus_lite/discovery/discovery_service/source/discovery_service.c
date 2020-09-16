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
#include "discovery_service.h"
#include "bus_manager.h"
#include "coap_discover.h"
#include "coap_service.h"
#include "common_info_manager.h"
#include "discovery_error.h"
#include "os_adapter.h"
#include "securec.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char package[MAX_PACKAGE_NAME];
    int publishId;
    unsigned short medium;
    unsigned short capabilityBitmap;
    char *capabilityData;
    unsigned short dataLength;
    unsigned short used;
} PublishModule;

typedef struct {
    char deviceId[MAX_DEV_ID_LEN];
    char deviceName[MAX_DEV_NAME_LEN];
    int  deviceType;
} ConfigDeviceInfo;

#define MAX_MODULE_COUNT 3
static int g_isServiceInit = 0;
PublishModule *g_publishModule = NULL;
char *g_capabilityData = NULL;
#define INVALID_SEM_ID 0xffffffff
unsigned long g_serviceSemId = INVALID_SEM_ID;
#define SOFTBUS_PERMISSION  "ohos.permission.DISTRIBUTED_DATASYNC"
static int DoRegistService(int medium);
int GetDeviceType(const char *value)
{
    if (value == NULL) {
        return UNKOWN;
    }

    for (unsigned int i = 0; i < sizeof(g_devMap) / sizeof(DeviceMap); i++) {
        if (!strcmp(g_devMap[i].value, value)) {
            return g_devMap[i].devType;
        }
    }
    return UNKOWN;
}

void BackupCommonDeviceInfo(const DeviceInfo *devInfo, ConfigDeviceInfo *info)
{
    if (devInfo == NULL || info == NULL) {
        return;
    }

    int ret = strcpy_s(info->deviceId, MAX_DEV_ID_LEN, devInfo->deviceId);
    if (ret != 0) {
        return;
    }

    ret = strcpy_s(info->deviceName, MAX_DEV_NAME_LEN, devInfo->deviceName);
    if (ret != 0) {
        memset_s(info->deviceId, MAX_DEV_ID_LEN, 0, MAX_DEV_ID_LEN);
        return;
    }

    info->deviceType = devInfo->deviceType;
    return;
}

void RecoverCommonDeviceInfo(const ConfigDeviceInfo *devInfo, DeviceInfo *info)
{
    if (devInfo == NULL || info == NULL) {
        return;
    }

    int ret = strcpy_s(info->deviceId, MAX_DEV_ID_LEN, devInfo->deviceId);
    if (ret != 0) {
        return;
    }

    ret = strcpy_s(info->deviceName, MAX_DEV_NAME_LEN, devInfo->deviceName);
    if (ret != 0) {
        memset_s(info->deviceId, MAX_DEV_ID_LEN, 0, MAX_DEV_ID_LEN);
        return;
    }

    info->deviceType = devInfo->deviceType;
    return;
}

int SetCommonDeviceInfo(const struct CommonDeviceInfo *devInfo, unsigned int num)
{
    if (SoftBusCheckPermission(SOFTBUS_PERMISSION) != 0 || devInfo == NULL || num == 0 ||
        num > COMM_DEVICE_KEY_MAX) {
        SOFTBUS_PRINT("[DISCOVERY] SetCommonDeviceInfo invalid para\n");
        return ERROR_FAIL;
    }

    DeviceInfo *localDev = GetCommonDeviceInfo();
    if (localDev == NULL) {
        return ERROR_FAIL;
    }

    int ret;
    int devType;
    ConfigDeviceInfo info = {0};
    BackupCommonDeviceInfo(localDev, &info);
    for (unsigned int i = 0; i < num; i++) {
        switch (devInfo[i].key) {
            case COMM_DEVICE_KEY_DEVID:
                ret = strcpy_s(localDev->deviceId, MAX_DEV_ID_LEN, devInfo[i].value);
                break;
            case COMM_DEVICE_KEY_DEVTYPE:
                ret = ERROR_FAIL;
                devType = GetDeviceType(devInfo[i].value);
                if (devType != UNKOWN) {
                    localDev->deviceType = devType;
                    ret = ERROR_SUCCESS;
                }
                break;
            case COMM_DEVICE_KEY_DEVNAME:
                ret = strcpy_s(localDev->deviceName, MAX_DEV_NAME_LEN, devInfo[i].value);
                break;
            default:
                ret = ERROR_FAIL;
                break;
        }

        if (ret != ERROR_SUCCESS) {
            break;
        }
    }

    if (ret == ERROR_SUCCESS) {
        ret = UpdateCommonDeviceInfo();
    } else {
        (void)RecoverCommonDeviceInfo(&info, localDev);
    }
    SOFTBUS_PRINT("[DISCOVERY] SetCommonDeviceInfo result = %d\n", ret);
    return ret;
}

void WifiEventTrigger(unsigned int para)
{
    DeviceInfo *localDev = GetCommonDeviceInfo();
    if (localDev == NULL) {
        return;
    }

    int ret;
    if (para) {
        char wifiIp[MAX_DEV_IP_LEN] = {0};
        CoapGetIp(wifiIp, MAX_DEV_IP_LEN, 0);
        if (strcmp(wifiIp, "0.0.0.0") == 0) {
            SOFTBUS_PRINT("[DISCOVERY] WifiEventTrigger new event interupt.\n");
            return;
        }
        ret = memcpy_s(localDev->deviceIp, sizeof(localDev->deviceIp), wifiIp, sizeof(wifiIp));
    } else {
        ret = memset_s(localDev->deviceIp, sizeof(localDev->deviceIp), 0, sizeof(localDev->deviceIp));
    }

    if (ret != ERROR_SUCCESS) {
        return;
    }

    if (BusManager(para) != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] WifiEventTrigger StartBusManager(%d) fail\n", para);
        return;
    }

    if (CoapRegisterDeviceInfo() != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] WifiEventTrigger CoapRegisterDeviceInfo fail\n");
        return;
    }

    if (DoRegistService(COAP) != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] WifiEventTrigger DoRegistService fail\n");
        return;
    }
}

int DeinitService(void)
{
    int ret = BusManager(0);
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] DeinitService BusManager(0) fail\n");
    }

    if (g_publishModule) {
        free(g_publishModule);
        g_publishModule = NULL;
    }

    if (g_capabilityData) {
        free(g_capabilityData);
        g_capabilityData = NULL;
    }

    ret = CoapDeinit();
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] DeinitService CoapDeinit fail\n");
    }

    RegisterWifiCallback(NULL);
    DeinitCommonManager();
    g_isServiceInit = 0;
    return ERROR_SUCCESS;
}

int InitService(void)
{
    if (g_isServiceInit != 0) {
        return ERROR_SUCCESS;
    }

    if (InitCommonManager() != 0) {
        SOFTBUS_PRINT("[DISCOVERY] InitService InitCommonManager fail\n");
        DeinitService();
        return ERROR_FAIL;
    }

    g_publishModule = calloc(1, sizeof(PublishModule) * MAX_MODULE_COUNT);
    if (g_publishModule == NULL) {
        DeinitService();
        return ERROR_NOMEMORY;
    }

    g_capabilityData = calloc(1, MAX_SERVICE_DATA_LEN);
    if (g_capabilityData == NULL) {
        DeinitService();
        return ERROR_NOMEMORY;
    }

    RegisterWifiCallback(WifiEventTrigger);
    int ret = CoapInit();
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] InitService CoapInit fail\n");
        DeinitService();
        return ret;
    }
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    CoapWriteMsgQueue(UPDATE_IP_EVENT);
#endif
    ret = CoapRegisterDeviceInfo();
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] InitService CoapRegisterDeviceInfo fail\n");
        DeinitService();
        return ret;
    }
    g_isServiceInit = 1;
#if defined(__LITEOS_A__) || defined(__LINUX__)
    if (BusManager(1) != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] InitService BusManager(1) fail\n");
    }
#endif
    SOFTBUS_PRINT("[DISCOVERY] InitService ok\n");
    return ERROR_SUCCESS;
}

PublishModule *FindExistModule(const char *packageName, int publishId)
{
    if (packageName == NULL || g_publishModule == NULL) {
        return NULL;
    }

    for (int i = 0; i < MAX_MODULE_COUNT; i++) {
        if (g_publishModule[i].used == 0) {
            continue;
        }

        if (strcmp(g_publishModule[i].package, packageName) == 0 && g_publishModule[i].publishId == publishId) {
            return &g_publishModule[i];
        }
    }

    return NULL;
}

unsigned int IsAllModuleFree(void)
{
    if (g_publishModule == NULL) {
        return 1;
    }

    for (int i = 0; i < MAX_MODULE_COUNT; i++) {
        if (g_publishModule[i].used == 1) {
            return 0;
        }
    }

    return 1;
}

PublishModule *FindFreeModule(void)
{
    if (g_publishModule == NULL) {
        return NULL;
    }

    for (int i = 0; i < MAX_MODULE_COUNT; i++) {
        if (g_publishModule[i].used == 1) {
            continue;
        }
        return &g_publishModule[i];
    }

    return NULL;
}

int ParseCapability(const char* capability, unsigned short *capabilityBitmap)
{
    if (capability == NULL || capabilityBitmap == NULL) {
        return ERROR_FAIL;
    }

    for (unsigned int i = 0; i < sizeof(g_capabilityMap) / sizeof(CapabilityMap); i++) {
        if (!strcmp(g_capabilityMap[i].capability, capability)) {
            *capabilityBitmap = g_capabilityMap[i].bitmap;
            return ERROR_SUCCESS;
        }
    }
    return ERROR_FAIL;
}

PublishModule *AddPublishModule(const char *packageName, const PublishInfo *info)
{
    if (packageName == NULL || g_publishModule == NULL || info == NULL) {
        return NULL;
    }

    if (info->dataLen > MAX_SERVICE_DATA_LEN) {
        return NULL;
    }

    if (FindExistModule(packageName, info->publishId) != NULL) {
        return NULL;
    }

    if (FindFreeModule() == NULL) {
        return NULL;
    }
    int ret;
    for (int i = 0; i < MAX_MODULE_COUNT; i++) {
        if (g_publishModule[i].used == 1) {
            continue;
        }

        if (ParseCapability(info->capability, &g_publishModule[i].capabilityBitmap)) {
            return NULL;
        }

        g_publishModule[i].used = 1;
        g_publishModule[i].capabilityData = calloc(1, info->dataLen + 1);
        if (g_publishModule[i].capabilityData == NULL) {
            memset_s(&g_publishModule[i], sizeof(g_publishModule[i]), 0, sizeof(g_publishModule[i]));
            return NULL;
        }
        g_publishModule[i].dataLength = info->dataLen + 1;
        ret = memcpy_s(g_publishModule[i].capabilityData,
                       g_publishModule[i].dataLength,
                       info->capabilityData, info->dataLen);
        if (ret != 0) {
            free(g_publishModule[i].capabilityData);
            g_publishModule[i].capabilityData = NULL;
            memset_s(&g_publishModule[i], sizeof(g_publishModule[i]), 0, sizeof(g_publishModule[i]));
            return NULL;
        }
        g_publishModule[i].medium = info->medium;
        g_publishModule[i].publishId = info->publishId;
        ret = memcpy_s(g_publishModule[i].package, MAX_PACKAGE_NAME, packageName, strlen(packageName));
        if (ret != 0) {
            free(g_publishModule[i].capabilityData);
            g_publishModule[i].capabilityData = NULL;
            memset_s(&g_publishModule[i], sizeof(g_publishModule[i]), 0, sizeof(g_publishModule[i]));
            return NULL;
        }
        return &g_publishModule[i];
    }
    return NULL;
}

int GetCapablityAndData(unsigned int capabilityBitmap[], char* capabilityData, int dataLen)
{
    if (g_publishModule == NULL || capabilityBitmap == NULL || capabilityData == NULL) {
        return ERROR_INVALID;
    }

    int len = 0;
    DeviceInfo *local = GetCommonDeviceInfo();
    if (local == NULL) {
        return ERROR_FAIL;
    }
    int ret = sprintf_s(capabilityData, dataLen, "port:%d,", local->devicePort);
    if (ret == -1) {
        return ERROR_FAIL;
    }
    len += ret;
    int moduleUsed = 0;
    for (int i = 0; i < MAX_MODULE_COUNT; i++) {
        if (g_publishModule[i].used == 0) {
            continue;
        }
#ifdef COAP_DEBUG
        SOFTBUS_PRINT("[DISCOVERY] Module[%d].capabilityBitmap = %d, capabilityData = %s\n", i,
            g_publishModule[i].capabilityBitmap, g_publishModule[i].capabilityData);
#endif
        capabilityBitmap[0] |= (0x1 << g_publishModule[i].capabilityBitmap);
        moduleUsed++;
        if (g_publishModule[i].capabilityData == NULL) {
            continue;
        }
        if (moduleUsed == MAX_MODULE_COUNT) {
            ret = sprintf_s(capabilityData + len, dataLen - len, "%s",
                g_publishModule[i].capabilityData);
        } else {
            ret = sprintf_s(capabilityData + len, dataLen - len, "%s,",
                g_publishModule[i].capabilityData);
        }
        if (ret == -1) {
            return ERROR_FAIL;
        }
        len += ret;
    }

    return ERROR_SUCCESS;
}

void PublishCallback(int publishId, int result,
    PublishModule *findModule, const IPublishCallback *cb)
{
    SOFTBUS_PRINT("[DISCOVERY] PublishCallback publishId=%d, result=%d\n", publishId, result);

    if (result == ERROR_SUCCESS) {
        if (cb->onPublishSuccess != NULL) {
            cb->onPublishSuccess(publishId);
        }
    } else {
        if (findModule != NULL) {
            if (findModule->capabilityData != NULL) {
                free(findModule->capabilityData);
                findModule->capabilityData = NULL;
            }
            memset_s(findModule, sizeof(PublishModule), 0, sizeof(PublishModule));
        }

        if (cb->onPublishFail != NULL) {
            cb->onPublishFail(publishId, result);
        }
    }
}

int DoRegistService(int medium)
{
    if (g_capabilityData != NULL) {
        memset_s(g_capabilityData, MAX_SERVICE_DATA_LEN, 0, MAX_SERVICE_DATA_LEN);
    } else {
        return ERROR_NOMEMORY;
    }

    unsigned int capabilityBitmap[MAX_CAPABILITY_NUM] = {0};
    if (GetCapablityAndData(capabilityBitmap, g_capabilityData, MAX_SERVICE_DATA_LEN) != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] DoRegistService GetCapablityAndData fail\n");
        return ERROR_CAPABLITY_FAIL;
    }

    int ret;
    switch (medium) {
        case COAP:
            ret = CoapRegistService(capabilityBitmap, MAX_CAPABILITY_NUM, g_capabilityData);
            break;
        default:
            ret = ERROR_NOT_SUPPORT_MEDIUM;
            break;
    }

    return ret;
}

int PublishService(const char *moduleName, const struct PublishInfo *info, const struct IPublishCallback *cb)
{
    if (SoftBusCheckPermission(SOFTBUS_PERMISSION) != 0 || info == NULL || cb == NULL) {
        SOFTBUS_PRINT("[DISCOVERY] PublishService invalid para(info or cb)\n");
        return ERROR_INVALID;
    }

    if (moduleName == NULL || strlen(moduleName) >= MAX_PACKAGE_NAME || info->publishId <= 0 ||
        info->dataLen > MAX_CAPABILITY_DATA_LEN) {
        SOFTBUS_PRINT("[DISCOVERY] PublishService invliad para\n");
        PublishCallback(info->publishId, PUBLISH_FAIL_REASON_PARAMETER_INVALID, NULL, cb);
        return ERROR_INVALID;
    }

    if (info->medium != COAP) {
        PublishCallback(info->publishId, PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM, NULL, cb);
        return ERROR_INVALID;
    }
    if (g_serviceSemId == INVALID_SEM_ID) {
        if (SemCreate(0, &g_serviceSemId) != 0) {
            g_serviceSemId = INVALID_SEM_ID;
            PublishCallback(info->publishId, PUBLISH_FAIL_REASON_UNKNOWN, NULL, cb);
            return ERROR_FAIL;
        }
    }
    (void)SemWait(&g_serviceSemId);
    if (InitService() != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] PublishService InitService fail\n");
        PublishCallback(info->publishId, PUBLISH_FAIL_REASON_UNKNOWN, NULL, cb);
        (void)SemPost(&g_serviceSemId);
        return ERROR_FAIL;
    }
    PublishModule *findModule = AddPublishModule(moduleName, info);
    if (findModule == NULL) {
        SOFTBUS_PRINT("[DISCOVERY] PublishService AddPublishModule fail\n");
        PublishCallback(info->publishId, PUBLISH_FAIL_REASON_UNKNOWN, NULL, cb);
        (void)SemPost(&g_serviceSemId);
        return ERROR_FAIL;
    }
    int ret = ERROR_SUCCESS;
    if (info->capability == NULL || info->capabilityData == NULL) {
        (void)CoapRegisterDefualtService();
    } else {
        ret = DoRegistService(info->medium);
    }
    (void)SemPost(&g_serviceSemId);
    if (ret != ERROR_SUCCESS) {
        PublishCallback(info->publishId, PUBLISH_FAIL_REASON_UNKNOWN, findModule, cb);
        return ERROR_FAIL;
    } else {
        PublishCallback(info->publishId, ERROR_SUCCESS, findModule, cb);
        return ERROR_SUCCESS;
    }
}

int UnPublishService(const char* moduleName, int publishId)
{
    if (SoftBusCheckPermission(SOFTBUS_PERMISSION) != 0) {
        SOFTBUS_PRINT("[DISCOVERY] No permission\n");
        return ERROR_FAIL;
    }

    if (moduleName == NULL || publishId <= 0 || g_serviceSemId == INVALID_SEM_ID) {
        SOFTBUS_PRINT("[DISCOVERY] UnPublishService invliad para\n");
        return ERROR_INVALID;
    }

    (void)SemWait(&g_serviceSemId);
    PublishModule *findModule = FindExistModule(moduleName, publishId);
    if (findModule == NULL) {
        SOFTBUS_PRINT("[DISCOVERY] UnPublishService get module fail\n");
        (void)SemPost(&g_serviceSemId);
        return ERROR_NONEXIST;
    }

    if (findModule->capabilityData != NULL) {
        free(findModule->capabilityData);
    }

    unsigned short medium = findModule->medium;
    memset_s(findModule, sizeof(PublishModule), 0, sizeof(PublishModule));
    int ret = DoRegistService(medium);
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] UnPublishService DoRegistService fail, error =  %d\n", ret);
        (void)SemPost(&g_serviceSemId);
        return ret;
    }

    (void)SemPost(&g_serviceSemId);
    SOFTBUS_PRINT("[DISCOVERY] UnPublishService ok\n");
    return ret;
}
