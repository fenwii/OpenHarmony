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

#include "devmgr_service_start.h"
#include "devmgr_service.h"
#include "devsvc_manager_stub.h"
#include "hdf_base.h"
#include "hdf_io_service.h"
#include "hdf_log.h"
#include "hdf_sbuf.h"

#define DEV_MGR_NODE_PERM 0660

int DeviceManagerDispatch(struct HdfObject *stub, int code, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    (void)reply;
    int ret = HDF_FAILURE;
    struct DevmgrService *devMgrSvc = (struct DevmgrService *)stub;
    if (data == NULL || devMgrSvc == NULL) {
        HDF_LOGE("%s: input param is invalid", __func__);
        return ret;
    }

    const char *svcName = HdfSbufReadString(data);
    if (svcName == NULL) {
        return ret;
    }
    OsalMutexLock(&devMgrSvc->devMgrMutex);
    if (code == 0) {
        struct SubscriberCallback callback = {
            .deviceObject = NULL,
            .OnServiceConnected = NULL,
        };
        ret = DevSvcManagerClntSubscribeService(svcName, callback);
    } else {
        ret = DevSvcManagerClntUnsubscribeService(svcName);
    }
    OsalMutexUnlock(&devMgrSvc->devMgrMutex);
    return ret;
}

int DeviceManagerStart()
{
    struct IDevmgrService *instance = DevmgrServiceGetInstance();

    if (instance == NULL || instance->StartService == NULL) {
        HDF_LOGE("Device manager start failed, service instance is null!");
        return HDF_FAILURE;
    }
    struct HdfIoService *ioService = HdfIoServiceBind(DEV_MGR_NODE, DEV_MGR_NODE_PERM);
    if (ioService != NULL) {
        static struct HdfIoDispatcher dispatcher = {
            .Dispatch = DeviceManagerDispatch,
        };
        ioService->dispatcher = &dispatcher;
        ioService->target = (struct HdfObject *)&instance->object;
    }
    return instance->StartService(instance);
}

