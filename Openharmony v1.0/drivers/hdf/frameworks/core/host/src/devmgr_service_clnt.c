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

#include "devmgr_service_clnt.h"
#include "hdf_base.h"
#include "hdf_device.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"

#define HDF_LOG_TAG devmgr_service_clnt

int DevmgrServiceClntAttachDeviceHost(uint16_t hostId, struct IDevHostService *hostService)
{
    struct IDevmgrService *devMgrSvcIf = NULL;
    struct DevmgrServiceClnt *inst = DevmgrServiceClntGetInstance();
    if ((inst == NULL) || (inst->devMgrSvcIf == NULL)) {
        HDF_LOGE("Attach device host failed, get device manager service client is null");
        return HDF_FAILURE;
    }

    devMgrSvcIf = inst->devMgrSvcIf;
    if (devMgrSvcIf->AttachDeviceHost == NULL) {
        HDF_LOGE("Attach device host failed, attach device host function is null");
        return HDF_FAILURE;
    }
    return devMgrSvcIf->AttachDeviceHost(devMgrSvcIf, hostId, hostService);
}

int DevmgrServiceClntAttachDevice(const struct HdfDeviceInfo *deviceInfo, struct IHdfDeviceToken *deviceToken)
{
    struct IDevmgrService *devMgrSvcIf = NULL;
    struct DevmgrServiceClnt *inst = DevmgrServiceClntGetInstance();
    if ((inst == NULL) || (inst->devMgrSvcIf == NULL)) {
        HDF_LOGE("Device manager service client attach device failed, inst is null");
        return HDF_FAILURE;
    }

    devMgrSvcIf = inst->devMgrSvcIf;
    if (devMgrSvcIf->AttachDevice == NULL) {
        HDF_LOGE("Device manager service client attach device failed, dmsOps->AttachDevice is nul");
        return HDF_FAILURE;
    }
    return devMgrSvcIf->AttachDevice(devMgrSvcIf, deviceInfo, deviceToken);
}

struct DevmgrServiceClnt *DevmgrServiceClntGetInstance()
{
    static struct DevmgrServiceClnt instance = {0};
    if (instance.devMgrSvcIf == NULL) {
        instance.devMgrSvcIf = (struct IDevmgrService *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DEVMGR_SERVICE);
    }
    return &instance;
}

void DevmgrServiceClntFreeInstance(struct DevmgrServiceClnt *inst)
{
    if ((inst != NULL) && (inst->devMgrSvcIf != NULL)) {
        HdfObjectManagerFreeObject((struct HdfObject *)inst->devMgrSvcIf);
        inst->devMgrSvcIf = NULL;
    }
}

