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
#include "nstackx_common.h"

#include <securec.h>

#include "cJSON.h"
#include "coap_discover.h"
#include "nstackx.h"
#include "nstackx_device.h"
#include "nstackx_error.h"
#include "os_adapter.h"
enum {
    NSTACKX_INIT_STATE_START = 0,
    NSTACKX_INIT_STATE_ONGOING,
    NSTACKX_INIT_STATE_DONE,
};

static uint8_t g_nstackInitState = NSTACKX_INIT_STATE_START;
int NSTACKX_Init()
{
    int ret;
    if (g_nstackInitState != NSTACKX_INIT_STATE_START) {
        return NSTACKX_EOK;
    }

    g_nstackInitState = NSTACKX_INIT_STATE_ONGOING;
    cJSON_InitHooks(NULL);

    ret = CoapInitDiscovery();
    if (ret != NSTACKX_EOK) {
        goto L_ERR_INIT;
    }
    g_nstackInitState = NSTACKX_INIT_STATE_DONE;
    return NSTACKX_EOK;

L_ERR_INIT:
    ret = NSTACKX_Deinit();
    if (ret != NSTACKX_EOK) {
        SOFTBUS_PRINT("[DISCOVERY] deinit fail\n");
    }
    return NSTACKX_EFAILED;
}

int NSTACKX_Deinit(void)
{
    if (g_nstackInitState == NSTACKX_INIT_STATE_START) {
        return NSTACKX_EOK;
    }

    int ret = CoapDeinitDiscovery();
    if (ret != NSTACKX_EOK) {
        return ret;
    }

    ClearLocalData();
    g_nstackInitState = NSTACKX_INIT_STATE_START;
    return NSTACKX_EOK;
}

int NSTACKX_RegisterDeviceAn(const NSTACKX_LocalDeviceInfo *localDeviceInfo, uint64_t deviceHash)
{
    if (g_nstackInitState != NSTACKX_INIT_STATE_DONE) {
        return NSTACKX_EFAILED;
    }

    if (localDeviceInfo == NULL) {
        return NSTACKX_EINVAL;
    }

    if (ConfigureLocalDeviceInfo(localDeviceInfo) != NSTACKX_EOK) {
        return NSTACKX_EINVAL;
    }
    SetDeviceHash(deviceHash);

    return NSTACKX_EOK;
}

typedef struct {
    uint32_t capabilityBitmapNum;
    uint32_t capabilityBitmap[NSTACKX_MAX_CAPABILITY_NUM];
} CapabilityProcessData;

int NSTACKX_RegisterCapability(uint32_t capabilityBitmapNum, const uint32_t capabilityBitmap[])
{
    if (g_nstackInitState != NSTACKX_INIT_STATE_DONE) {
        return NSTACKX_EFAILED;
    }

    if (capabilityBitmapNum > NSTACKX_MAX_CAPABILITY_NUM) {
        return NSTACKX_EINVAL;
    }

    if (RegisterCapability(capabilityBitmapNum, capabilityBitmap) != NSTACKX_EOK) {
        return NSTACKX_EINVAL;
    }

    return NSTACKX_EOK;
}

int NSTACKX_RegisterServiceData(const char* serviceData)
{
    if (serviceData == NULL) {
        return NSTACKX_EINVAL;
    }

    if (g_nstackInitState != NSTACKX_INIT_STATE_DONE) {
        return NSTACKX_EFAILED;
    }
    unsigned int serviceLen = strlen(serviceData);
    if (serviceLen >= NSTACKX_MAX_SERVICE_DATA_LEN) {
        return NSTACKX_EINVAL;
    }

    if (RegisterServiceData(serviceData, serviceLen + 1) != NSTACKX_EOK) {
        return NSTACKX_EINVAL;
    }
    return NSTACKX_EOK;
}
