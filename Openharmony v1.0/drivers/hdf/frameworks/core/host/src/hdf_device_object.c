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

#include "hdf_device_object.h"
#include "hdf_base.h"
#include "hdf_device_node.h"
#include "hdf_log.h"
#include "hdf_observer_record.h"
#include "hdf_service_observer.h"
#include "power_state_token.h"

#define HDF_LOG_TAG device_object

int32_t HdfDeviceSubscribeService(
    struct HdfDeviceObject *deviceObject, const char *serviceName, struct SubscriberCallback callback)
{
    uint32_t matchId;
    struct DevHostService *hostService = NULL;
    const struct HdfDeviceInfo *deviceInfo = NULL;
    if (deviceObject == NULL || serviceName == NULL) {
        HDF_LOGE("%s input param is invalid", __func__);
        return HDF_FAILURE;
    }
    struct HdfDeviceNode *devNode = (struct HdfDeviceNode *)HDF_SLIST_CONTAINER_OF(
        struct HdfDeviceObject, deviceObject, struct HdfDeviceNode, deviceObject);
    hostService = devNode->hostService;
    if (hostService == NULL) {
        HDF_LOGE("Get host service is null");
        return HDF_FAILURE;
    }
    deviceInfo = devNode->deviceInfo;
    if (deviceInfo == NULL) {
        HDF_LOGE("Get device deviceInfo is null");
        return HDF_FAILURE;
    }
    matchId = HdfMakeHardwareId(deviceInfo->hostId, deviceInfo->deviceId);
    return HdfServiceObserverSubscribeService(&hostService->observer, serviceName, matchId, callback);
}

const char *HdfDeviceGetServiceName(const struct HdfDeviceObject *deviceObject)
{
    if (deviceObject == NULL) {
        HDF_LOGE("%s input param is invalid", __func__);
        return NULL;
    }
    struct HdfDeviceNode *devNode = (struct HdfDeviceNode *)HDF_SLIST_CONTAINER_OF(
        struct HdfDeviceObject, deviceObject, struct HdfDeviceNode, deviceObject);
    const struct HdfDeviceInfo *deviceInfo = devNode->deviceInfo;
    if (deviceInfo == NULL) {
        HDF_LOGE("Get device deviceInfo is null");
        return NULL;
    }
    return deviceInfo->svcName;
}

void HdfDeviceRegisterPowerListener(struct HdfDeviceObject *deviceObject, struct IPowerEventListener *listener)
{
    if (deviceObject == NULL) {
        HDF_LOGE("%s input param is invalid", __func__);
        return;
    }
    struct HdfDeviceNode *devNode = (struct HdfDeviceNode *)HDF_SLIST_CONTAINER_OF(
        struct HdfDeviceObject, deviceObject, struct HdfDeviceNode, deviceObject);
    HdfDeviceNodeAddPowerStateListener(devNode, listener);
}

void HdfDeviceAcquireWakeLock(struct HdfDeviceObject *deviceObject)
{
    if (deviceObject == NULL) {
        HDF_LOGE("%s input param is invalid", __func__);
        return;
    }
    struct HdfDeviceNode *devNode = (struct HdfDeviceNode *)HDF_SLIST_CONTAINER_OF(
        struct HdfDeviceObject, deviceObject, struct HdfDeviceNode, deviceObject);
    struct IPowerStateToken *tokenIf = (struct IPowerStateToken *)devNode->powerToken;
    if ((tokenIf != NULL) && (tokenIf->AcquireWakeLock != NULL)) {
        tokenIf->AcquireWakeLock(tokenIf);
    }
}

void HdfDeviceReleaseWakeLock(struct HdfDeviceObject *deviceObject)
{
    if (deviceObject == NULL) {
        HDF_LOGE("%s input param is invalid", __func__);
        return;
    }
    struct HdfDeviceNode *devNode = (struct HdfDeviceNode *)HDF_SLIST_CONTAINER_OF(
        struct HdfDeviceObject, deviceObject, struct HdfDeviceNode, deviceObject);
    struct IPowerStateToken *tokenIf = (struct IPowerStateToken *)devNode->powerToken;
    if ((tokenIf != NULL) && (tokenIf->ReleaseWakeLock != NULL)) {
        tokenIf->ReleaseWakeLock(tokenIf);
    }
}

void HdfDeviceObjectConstruct(struct HdfDeviceObject *deviceObject)
{
    if (deviceObject != NULL) {
        deviceObject->property = NULL;
        deviceObject->service = NULL;
    }
}
