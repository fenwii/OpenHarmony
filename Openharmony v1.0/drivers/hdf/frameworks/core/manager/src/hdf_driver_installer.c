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

#include "hdf_driver_installer.h"
#include "devhost_service.h"
#include "hdf_base.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"

#define HDF_LOG_TAG driver_installer

static int DriverInstallerStartDeviceHost(uint32_t devHostId, const char *devHostName)
{
    struct IDevHostService *hostServiceIf = DevHostServiceNewInstance(devHostId, devHostName);
    if ((hostServiceIf == NULL) || (hostServiceIf->StartService == NULL)) {
        HDF_LOGE("hostServiceIf or hostServiceIf->StartService is null");
        return HDF_FAILURE;
    }
    int ret = hostServiceIf->StartService(hostServiceIf);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("Start host service failed, ret is: %d", ret);
        DevHostServiceFreeInstance(hostServiceIf);
    }
    return ret;
}

static void DriverInstallerConstruct(struct DriverInstaller *inst)
{
    struct IDriverInstaller *driverInstallIf = (struct IDriverInstaller *)inst;
    driverInstallIf->StartDeviceHost = DriverInstallerStartDeviceHost;
}

struct HdfObject *DriverInstallerCreate(void)
{
    static bool isDriverInstInit = false;
    static struct DriverInstaller driverInstaller;
    if (!isDriverInstInit) {
        DriverInstallerConstruct(&driverInstaller);
        isDriverInstInit = true;
    }
    return (struct HdfObject *)&driverInstaller;
}

struct IDriverInstaller *DriverInstallerGetInstance()
{
    static struct IDriverInstaller *installer = NULL;
    if (installer == NULL) {
        installer = (struct IDriverInstaller *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DRIVER_INSTALLER);
    }
    return installer;
}

