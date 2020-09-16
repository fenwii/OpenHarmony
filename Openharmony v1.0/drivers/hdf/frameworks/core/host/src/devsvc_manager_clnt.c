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

#include "devsvc_manager_clnt.h"
#include "devsvc_manager.h"
#include "hdf_base.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"

#define HDF_LOG_TAG devsvc_manager_clnt

int DevSvcManagerClntAddService(const char *svcName, struct HdfDeviceObject *service)
{
    struct DevSvcManagerClnt *devSvcMgrClnt = DevSvcManagerClntGetInstance();
    if (devSvcMgrClnt == NULL) {
        HDF_LOGE("Get device manager client is null");
        return HDF_FAILURE;
    }

    struct IDevSvcManager *serviceManager = devSvcMgrClnt->devSvcMgrIf;
    if (serviceManager->AddService == NULL) {
        HDF_LOGE("AddService function is not assigned");
        return HDF_FAILURE;
    }
    return serviceManager->AddService(serviceManager, svcName, service);
}

const struct HdfObject *DevSvcManagerClntGetService(const char *svcName)
{
    struct DevSvcManagerClnt *devSvcMgrClnt = DevSvcManagerClntGetInstance();
    if (devSvcMgrClnt == NULL) {
        HDF_LOGE("Get device manager client is null");
        return NULL;
    }

    struct IDevSvcManager *serviceManager = devSvcMgrClnt->devSvcMgrIf;
    if (serviceManager->GetService == NULL) {
        HDF_LOGE("GetService function is not assigned");
        return NULL;
    }
    return serviceManager->GetService(serviceManager, svcName);
}

struct HdfDeviceObject *DevSvcManagerClntGetDeviceObject(const char *svcName)
{
    struct DevSvcManagerClnt *devSvcMgrClnt = DevSvcManagerClntGetInstance();
    if (devSvcMgrClnt == NULL) {
        HDF_LOGE("Get device manager client is null");
        return NULL;
    }

    struct IDevSvcManager *serviceManager = devSvcMgrClnt->devSvcMgrIf;
    if (serviceManager->GetObject == NULL) {
        HDF_LOGE("GetObject function is not assigned");
        return NULL;
    }
    return serviceManager->GetObject(serviceManager, svcName);
}

int DevSvcManagerClntSubscribeService(const char *svcName, struct SubscriberCallback callback)
{
    struct DevSvcManagerClnt *devSvcMgrClnt = DevSvcManagerClntGetInstance();
    if (devSvcMgrClnt == NULL) {
        HDF_LOGE("Get device manager client is null");
        return HDF_FAILURE;
    }

    struct IDevSvcManager *serviceManager = devSvcMgrClnt->devSvcMgrIf;
    if (serviceManager->SubscribeService == NULL) {
        HDF_LOGE("SubscribeService function is not assigned");
        return HDF_FAILURE;
    }
    return serviceManager->SubscribeService(serviceManager, svcName, callback);
}

int DevSvcManagerClntUnsubscribeService(const char *svcName)
{
    struct DevSvcManagerClnt *devSvcMgrClnt = DevSvcManagerClntGetInstance();
    if (devSvcMgrClnt == NULL) {
        HDF_LOGE("Get device manager client is null");
        return HDF_FAILURE;
    }

    struct IDevSvcManager *serviceManager = devSvcMgrClnt->devSvcMgrIf;
    if (serviceManager->UnsubscribeService == NULL) {
        HDF_LOGE("UnsubService function is not assigned");
        return HDF_FAILURE;
    }
    return serviceManager->UnsubscribeService(serviceManager, svcName);
}

void DevSvcManagerClntRemoveService(const char *svcName)
{
    struct DevSvcManagerClnt *devSvcMgrClnt = DevSvcManagerClntGetInstance();
    if (devSvcMgrClnt == NULL) {
        HDF_LOGE("Get device manager client is null");
        return;
    }

    struct IDevSvcManager *serviceManager = devSvcMgrClnt->devSvcMgrIf;
    if (serviceManager->RemoveService == NULL) {
        HDF_LOGE("Remove service function is not assigned");
        return;
    }
    serviceManager->RemoveService(serviceManager, svcName);
}

static void DevSvcManagerClntConstruct(struct DevSvcManagerClnt *inst)
{
    inst->devSvcMgrIf = (struct IDevSvcManager *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DEVSVC_MANAGER);
}

struct DevSvcManagerClnt *DevSvcManagerClntGetInstance()
{
    static struct DevSvcManagerClnt *instance = NULL;
    if (instance == NULL) {
        static struct DevSvcManagerClnt singletonInstance;
        DevSvcManagerClntConstruct(&singletonInstance);
        instance = &singletonInstance;
    }
    return instance;
}

void DevSvcManagerClntFreeInstance(struct DevSvcManagerClnt *instance)
{
    if (instance != NULL) {
        if (instance->devSvcMgrIf != NULL) {
            HdfObjectManagerFreeObject((struct HdfObject *)instance->devSvcMgrIf);
        }
    }
}

