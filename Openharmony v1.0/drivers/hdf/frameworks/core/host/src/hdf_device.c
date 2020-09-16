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

#include "hdf_device.h"
#include "hdf_base.h"
#include "hdf_cstring.h"
#include "hdf_device_node.h"
#include "hdf_device_token.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"
#include "hdf_service_observer.h"
#include "osal_mem.h"

#define HDF_LOG_TAG hdf_device

static int HdfDeviceAttach(struct IHdfDevice *devInst, struct HdfDeviceNode *devNode)
{
    struct HdfDevice *device = (struct HdfDevice *)devInst;
    struct IDeviceNode *nodeIf = (struct IDeviceNode *)devNode;
    if (device == NULL || nodeIf == NULL || nodeIf->LaunchNode == NULL) {
        HDF_LOGE("Device attach failed, input params is wrong");
        return HDF_ERR_INVALID_PARAM;
    }
    HdfSListAdd(&device->services, &devNode->entry);
    return nodeIf->LaunchNode(devNode, devInst);
}

static void HdfDeviceConstruct(struct HdfDevice *device)
{
    device->super.Attach = HdfDeviceAttach;
    HdfSListInit(&device->services);
}

static void HdfDeviceDestruct(struct HdfDevice *device)
{
    HdfSListFlush(&device->services, HdfDeviceNodeDelete);
}

struct HdfObject *HdfDeviceCreate()
{
    struct HdfDevice *device =
        (struct HdfDevice *)OsalMemCalloc(sizeof(struct HdfDevice));
    if (device != NULL) {
        HdfDeviceConstruct(device);
    }
    return (struct HdfObject *)device;
}

void HdfDeviceRelease(struct HdfObject *object)
{
    struct HdfDevice *device = (struct HdfDevice *)object;
    if (device != NULL) {
        HdfDeviceDestruct(device);
        OsalMemFree(device);
    }
}

struct HdfDevice *HdfDeviceNewInstance()
{
    return (struct HdfDevice *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DEVICE);
}

void HdfDeviceFreeInstance(struct HdfDevice *device)
{
    if (device != NULL) {
        HdfObjectManagerFreeObject((struct HdfObject *)device);
    }
}

void HdfDeviceDelete(struct HdfSListNode *listEntry)
{
    if (listEntry != NULL) {
        struct HdfDevice *device = (struct HdfDevice *)HDF_SLIST_CONTAINER_OF(
            struct HdfSListNode, listEntry, struct HdfDevice, node);
        HdfDeviceFreeInstance(device);
    }
}

