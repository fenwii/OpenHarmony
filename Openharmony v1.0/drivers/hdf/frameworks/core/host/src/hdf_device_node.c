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

#include "hdf_device_node.h"
#include "devhost_service.h"
#include "devmgr_service_clnt.h"
#include "devsvc_manager_clnt.h"
#include "hdf_base.h"
#include "hdf_device_object.h"
#include "hdf_device_token.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"
#include "hdf_observer_record.h"
#include "osal_mem.h"
#include "power_state_token.h"

#define HDF_LOG_TAG device_node

static int HdfDeviceNodePublishLocalService(
    struct HdfDeviceNode *devNode, const struct HdfDeviceInfo *deviceInfo)
{
    uint32_t matchId;
    if ((devNode == NULL) || (deviceInfo == NULL)) {
        HDF_LOGE("Publish local service failed, device is null");
        return HDF_FAILURE;
    }
    struct DevHostService *hostService = devNode->hostService;
    if (hostService == NULL) {
        HDF_LOGE("Publish local service failed, host service is null");
        return HDF_FAILURE;
    }
    matchId = HdfMakeHardwareId(deviceInfo->hostId, deviceInfo->deviceId);
    return HdfServiceObserverPublishService(&hostService->observer, deviceInfo->svcName,
        matchId, deviceInfo->policy, (struct HdfObject *)devNode->deviceObject.service);
}

static int HdfDeviceNodePublishService(
    struct HdfDeviceNode *devNode, const struct HdfDeviceInfo *deviceInfo, struct IHdfDevice *device)
{
    int status = HDF_SUCCESS;
    if (deviceInfo->policy == SERVICE_POLICY_NONE) {
        HDF_LOGI("policy is %d", SERVICE_POLICY_NONE);
        return status;
    }

    struct IDeviceNode *nodeIf = &devNode->super;
    if ((deviceInfo->policy == SERVICE_POLICY_PUBLIC) ||
        (deviceInfo->policy == SERVICE_POLICY_CAPACITY)) {
        if (nodeIf->PublishService != NULL) {
            status = nodeIf->PublishService(devNode, deviceInfo->svcName);
        }
    }
    if (status == HDF_SUCCESS) {
        status = HdfDeviceNodePublishLocalService(devNode, deviceInfo);
    }
    return status;
}

int HdfDeviceLaunchNode(struct HdfDeviceNode *devNode, struct IHdfDevice *devInst)
{
    struct HdfDevice *device = (struct HdfDevice *)devInst;
    if (device == NULL || devNode == NULL) {
        HDF_LOGE("Launch service failed, device or service is null");
        return HDF_ERR_INVALID_PARAM;
    }

    struct HdfDriverEntry *driverEntry = devNode->driverEntry;
    const struct HdfDeviceInfo *deviceInfo = devNode->deviceInfo;
    struct IHdfDeviceToken *deviceToken = NULL;

    if (deviceInfo == NULL) {
        HDF_LOGE("Launch service failed, deviceInfo is null");
        return HDF_ERR_INVALID_PARAM;
    }

    if ((driverEntry == NULL) || (driverEntry->Init == NULL)) {
        HDF_LOGE("deviceEntry or deviceEntry->Init is null");
        return HDF_ERR_INVALID_PARAM;
    }
    int ret = driverEntry->Init(&devNode->deviceObject);
    if (ret != HDF_SUCCESS) {
        if (driverEntry->Release != NULL) {
            driverEntry->Release(&devNode->deviceObject);
        }
        return HDF_DEV_ERR_DEV_INIT_FAIL;
    }
    ret = HdfDeviceNodePublishService(devNode, deviceInfo, devInst);
    if (ret != HDF_SUCCESS) {
        if (driverEntry->Release != NULL) {
            driverEntry->Release(&devNode->deviceObject);
        }
        return HDF_DEV_ERR_PUBLISH_FAIL;
    }
    deviceToken = devNode->token;
    ret = DevmgrServiceClntAttachDevice(deviceInfo, deviceToken);
    if (ret != HDF_SUCCESS) {
        if (driverEntry->Release != NULL) {
            driverEntry->Release(&devNode->deviceObject);
        }
        return HDF_DEV_ERR_ATTACHDEV_FAIL;
    }
    return ret;
}

int HdfDeviceNodeAddPowerStateListener(
    struct HdfDeviceNode *devNode, struct IPowerEventListener *listener)
{
    if (devNode->powerToken != NULL) {
        return HDF_FAILURE;
    }
    if (devNode->powerToken == NULL) {
        devNode->powerToken = PowerStateTokenNewInstance(&devNode->deviceObject, listener);
    }
    return (devNode->powerToken == NULL) ? HDF_SUCCESS : HDF_FAILURE;
}

int HdfDeviceNodePublishPublicService(struct HdfDeviceNode *devNode, const char *svcName)
{
    if ((devNode == NULL) || (devNode->deviceObject.service == NULL)) {
        HDF_LOGE("device method is null");
        return HDF_FAILURE;
    }
    return DevSvcManagerClntAddService(svcName, &devNode->deviceObject);
}

void HdfDeviceNodeReclaimService(const char *svcName)
{
    DevSvcManagerClntRemoveService(svcName);
}

void HdfDeviceNodeConstruct(struct HdfDeviceNode *devNode)
{
    if (devNode != NULL) {
        struct IDeviceNode *nodeIf = &devNode->super;
        HdfDeviceObjectConstruct(&devNode->deviceObject);
        devNode->token = HdfDeviceTokenNewInstance();
        nodeIf->LaunchNode = HdfDeviceLaunchNode;
        nodeIf->PublishService = HdfDeviceNodePublishPublicService;
    }
}

void HdfDeviceNodeDestruct(struct HdfDeviceNode *devNode)
{
    if (devNode == NULL) {
        return;
    }
    HdfDeviceTokenFreeInstance(devNode->token);
    devNode->token = NULL;
    PowerStateTokenFreeInstance(devNode->powerToken);
    devNode->powerToken = NULL;
}

struct HdfDeviceNode *HdfDeviceNodeNewInstance()
{
    return (struct HdfDeviceNode *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DEVICE_SERVICE);
}

void HdfDeviceNodeFreeInstance(struct HdfDeviceNode *devNode)
{
    HdfObjectManagerFreeObject((struct HdfObject *) devNode);
}

void HdfDeviceNodeDelete(struct HdfSListNode *deviceEntry)
{
    if (deviceEntry == NULL) {
        return;
    }
    struct HdfDeviceNode *devNode =
        HDF_SLIST_CONTAINER_OF(struct HdfSListNode, deviceEntry, struct HdfDeviceNode, entry);
    HdfDeviceNodeFreeInstance(devNode);
}

