/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hdf_device_node_ext.h"
#include "devsvc_manager_clnt.h"
#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "hdf_log.h"
#include "hdf_sbuf.h"
#include "osal_mem.h"

#define HDF_LOG_TAG device_node_ext

static int DeviceNodeExtDispatch(struct HdfObject *stub, int code, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    struct IDeviceIoService *deviceMethod = NULL;
    const struct HdfDeviceInfo *deviceInfo = NULL;
    struct HdfDeviceNode *devNode = NULL;

    if (stub == NULL) {
        HDF_LOGE("input ioService null");
        return HDF_FAILURE;
    }
    uint64_t ioClientPtr = 0;
    if (!HdfSbufReadUint64(reply, &ioClientPtr) || ioClientPtr == 0) {
        HDF_LOGE("input ioClient null");
        return HDF_FAILURE;
    }
    HdfSbufFlush(reply);
    devNode = CONTAINER_OF(stub, struct HdfDeviceNode, deviceObject);
    deviceMethod = devNode->deviceObject.service;
    if (deviceMethod == NULL) {
        HDF_LOGE("Device service interface is null");
        return HDF_FAILURE;
    }
    deviceInfo = devNode->deviceInfo;
    if (deviceInfo == NULL) {
        HDF_LOGE("Device deviceInfo is null");
        return HDF_FAILURE;
    }
    if (deviceInfo->policy == SERVICE_POLICY_CAPACITY) {
        if (deviceMethod->Dispatch == NULL) {
            HDF_LOGE("Remote service dispatch is null");
            return HDF_FAILURE;
        }
        return deviceMethod->Dispatch((struct HdfDeviceIoClient *)((uintptr_t)ioClientPtr), code, data, reply);
    }
    return HDF_FAILURE;
}

static int DeviceNodeExtPublishService(struct HdfDeviceNode *inst, const char *serviceName)
{
    const struct HdfDeviceInfo *deviceInfo = NULL;
    struct HdfDeviceObject *deviceObject = NULL;
    struct DeviceNodeExt *devNodeExt = (struct DeviceNodeExt *)inst;
    if (devNodeExt == NULL) {
        return HDF_FAILURE;
    }
    int ret = HdfDeviceNodePublishPublicService(inst, serviceName);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("Device publish service failed, ret is: %d", ret);
        return HDF_FAILURE;
    }

    deviceInfo = inst->deviceInfo;
    deviceObject = &devNodeExt->super.deviceObject;
    if ((deviceObject->service == NULL) || (deviceInfo == NULL)) {
        HDF_LOGE("Device service interface or deviceInfo is null");
        return HDF_FAILURE;
    }
    if (deviceInfo->policy == SERVICE_POLICY_CAPACITY) {
        devNodeExt->ioService = HdfIoServiceBind(serviceName, deviceInfo->permission);
        if (devNodeExt->ioService != NULL) {
            devNodeExt->ioService->target = (struct HdfObject*)(&inst->deviceObject);
            static struct HdfIoDispatcher dispatcher = {
                .Dispatch = DeviceNodeExtDispatch
            };
            devNodeExt->ioService->dispatcher = &dispatcher;
        } else {
            HDF_LOGE("Device remote service bind failed");
            HdfDeviceNodeReclaimService(serviceName);
            return HDF_FAILURE;
        }
    }
    return HDF_SUCCESS;
}

static void DeviceNodeExtConstruct(struct DeviceNodeExt *inst)
{
    struct IDeviceNode *nodeIf = (struct IDeviceNode *)inst;
    if (nodeIf != NULL) {
        HdfDeviceNodeConstruct(&inst->super);
        nodeIf->PublishService = DeviceNodeExtPublishService;
    }
}

struct HdfObject *DeviceNodeExtCreate()
{
    struct DeviceNodeExt *instance =
        (struct DeviceNodeExt *)OsalMemCalloc(sizeof(struct DeviceNodeExt));
    if (instance != NULL) {
        DeviceNodeExtConstruct(instance);
        instance->ioService = NULL;
    }
    return (struct HdfObject *)instance;
}

void DeviceNodeExtRelease(struct HdfObject *object)
{
    struct DeviceNodeExt *instance = (struct DeviceNodeExt *)object;
    if (instance != NULL) {
        if (instance->ioService != NULL) {
            HdfIoServiceRecycle(instance->ioService);
        }
        HdfDeviceNodeDestruct(&instance->super);
        OsalMemFree(instance);
    }
}

