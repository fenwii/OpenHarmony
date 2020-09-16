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

#include "hdf_driver_loader.h"
#include "devsvc_manager_clnt.h"
#include "hcs_tree_if.h"
#include "hdf_device_desc.h"
#include "hdf_device_node.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"

#define HDF_LOG_TAG driver_loader

static struct HdfDeviceNode *HdfDriverLoaderLoadNode(
    struct IDriverLoader *loader, const struct HdfDeviceInfo *deviceInfo)
{
    struct HdfDriverEntry *driverEntry = NULL;
    struct HdfDeviceNode *devNode = NULL;
    if ((loader == NULL) || (loader->GetDriverEntry == NULL)) {
        HDF_LOGE("loader or loader->GetDriverEntry is null");
        return NULL;
    }

    driverEntry = loader->GetDriverEntry(deviceInfo);
    if (driverEntry == NULL) {
        HDF_LOGE("Load service failed, deviceEntry is null");
        return NULL;
    }

    devNode = HdfDeviceNodeNewInstance();
    if (devNode == NULL) {
        HDF_LOGE("Load service failed, device node is null");
        return NULL;
    }

    devNode->driverEntry = driverEntry;
    devNode->deviceInfo = deviceInfo;
    devNode->deviceObject.property = HcsGetNodeByMatchAttr(HcsGetRootNode(), deviceInfo->deviceMatchAttr);
    if (devNode->deviceObject.property == NULL) {
        HDF_LOGW("Get property is null, match attr is: %s", deviceInfo->deviceMatchAttr);
    }

    if ((deviceInfo->policy == SERVICE_POLICY_PUBLIC) || (deviceInfo->policy == SERVICE_POLICY_CAPACITY)) {
        if (driverEntry->Bind == NULL) {
            HDF_LOGE("driver bind method is null");
            HdfDeviceNodeFreeInstance(devNode);
            return NULL;
        }
        if (driverEntry->Bind(&devNode->deviceObject) != 0) {
            HDF_LOGE("bind driver failed");
            HdfDeviceNodeFreeInstance(devNode);
            return NULL;
        }
    }
    return devNode;
}

static void HdfDriverLoaderUnLoadNode(struct IDriverLoader *loader, const struct HdfDeviceInfo *deviceInfo)
{
    struct HdfDriverEntry *driverEntry = NULL;
    struct HdfDeviceObject *deviceObject = NULL;
    if ((loader == NULL) || (loader->GetDriverEntry == NULL)) {
        HDF_LOGE("loader or loader->GetDriverEntry is null");
        return;
    }

    driverEntry = loader->GetDriverEntry(deviceInfo);
    if (driverEntry == NULL) {
        HDF_LOGE("Load service failed, driverEntry is null");
        return;
    }
    if (driverEntry->Release == NULL) {
        HDF_LOGI("Device Release func is null");
        return;
    }
    deviceObject = DevSvcManagerClntGetDeviceObject(deviceInfo->svcName);
    driverEntry->Release(deviceObject);
}

static void HdfDriverLoaderConstruct(struct HdfDriverLoader *inst)
{
    struct IDriverLoader *driverLoaderIf = (struct IDriverLoader *)inst;
    driverLoaderIf->LoadNode = HdfDriverLoaderLoadNode;
    driverLoaderIf->UnLoadNode = HdfDriverLoaderUnLoadNode;
    driverLoaderIf->GetDriverEntry = HdfDriverLoaderGetDriverEntry;
}

struct HdfObject *HdfDriverLoaderCreate()
{
    static bool isDriverLoaderInit = false;
    static struct HdfDriverLoader driverLoader;
    if (!isDriverLoaderInit) {
        HdfDriverLoaderConstruct(&driverLoader);
        isDriverLoaderInit = true;
    }
    return (struct HdfObject *)&driverLoader;
}

struct IDriverLoader *HdfDriverLoaderGetInstance()
{
    static struct IDriverLoader *instance = NULL;
    if (instance == NULL) {
        instance = (struct IDriverLoader *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DRIVER_LOADER);
    }
    return instance;
}

