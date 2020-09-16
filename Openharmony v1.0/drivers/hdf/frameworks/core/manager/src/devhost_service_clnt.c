/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "device_token_clnt.h"
#include "devhost_service_clnt.h"
#include "hdf_base.h"
#include "hdf_driver_installer.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG devhost_service_clnt

int DevHostServiceClntInstallDriver(struct DevHostServiceClnt *hostClnt)
{
    int ret;
    struct HdfSListIterator it;
    struct HdfDeviceInfo *deviceInfo = NULL;
    struct IDevHostService *devHostSvcIf = NULL;
    if (hostClnt == NULL) {
        HDF_LOGE("Install driver failed, hostClnt is null");
        return HDF_FAILURE;
    }

    devHostSvcIf = (struct IDevHostService *)hostClnt->hostService;
    if (devHostSvcIf == NULL || devHostSvcIf->AddDevice == NULL) {
        HDF_LOGE("devHostSvcIf or devHostSvcIf->AddDevice is null");
        return HDF_FAILURE;
    }
    HdfSListIteratorInit(&it, hostClnt->deviceInfos);
    while (HdfSListIteratorHasNext(&it)) {
        deviceInfo = (struct HdfDeviceInfo *)HdfSListIteratorNext(&it);
        if ((deviceInfo == NULL) || (deviceInfo->preload != DEVICE_PRELOAD_ENABLE)) {
            continue;
        }
        ret = devHostSvcIf->AddDevice(devHostSvcIf, deviceInfo);
        if (ret != HDF_SUCCESS) {
            deviceInfo->preload = DEVICE_PRELOAD_DISABLE;
            HDF_LOGE("Install %s driver failed, ret = %d", deviceInfo->svcName, ret);
        }
    }
    return HDF_SUCCESS;
}

static void DevHostServiceClntConstruct(struct DevHostServiceClnt *hostClnt)
{
    HdfSListInit(&hostClnt->devices);
}

struct DevHostServiceClnt *DevHostServiceClntNewInstance(uint16_t hostId, const char *hostName)
{
    struct DevHostServiceClnt *hostClnt =
        (struct DevHostServiceClnt *)OsalMemCalloc(sizeof(struct DevHostServiceClnt));
    if (hostClnt != NULL) {
        hostClnt->hostId = hostId;
        hostClnt->hostName = hostName;
        DevHostServiceClntConstruct(hostClnt);
    }
    return hostClnt;
}

void DevHostServiceClntFreeInstance(struct DevHostServiceClnt *hostClnt)
{
    if (hostClnt != NULL) {
        HdfSListFlush(&hostClnt->devices, DeviceTokenClntDelete);
        HdfSListFlush(hostClnt->deviceInfos, HdfDeviceInfoDelete);
        OsalMemFree(hostClnt);
    }
}

void DevHostServiceClntDelete(struct HdfSListNode *listEntry)
{
    struct DevHostServiceClnt *hostClnt = (struct DevHostServiceClnt *)listEntry;
    if (hostClnt != NULL) {
        DevHostServiceClntFreeInstance(hostClnt);
    }
}

