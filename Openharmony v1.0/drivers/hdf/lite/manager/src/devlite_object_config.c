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

#include "hdf_object_manager.h"
#include "devhost_service.h"
#include "devmgr_service.h"
#include "devsvc_manager.h"
#include "hdf_device.h"
#include "hdf_device_node_ext.h"
#include "hdf_device_token.h"
#include "hdf_driver_installer.h"
#include "hdf_driver_loader.h"

static const struct HdfObjectCreator g_liteObjectCreators[] = {
    [HDF_OBJECT_ID_DEVMGR_SERVICE] =
        {
            .Create = DevmgrServiceCreate,
            .Release = DevmgrServiceRelease,
        },
    [HDF_OBJECT_ID_DEVSVC_MANAGER] =
        {
            .Create = DevSvcManagerCreate,
            .Release = DevSvcManagerRelease,
        },
    [HDF_OBJECT_ID_DEVHOST_SERVICE] =
        {
            .Create = DevHostServiceCreate,
            .Release = DevHostServiceRelease,
        },
    [HDF_OBJECT_ID_DRIVER_INSTALLER] =
        {
            .Create = DriverInstallerCreate,
            .Release = NULL,
        },
    [HDF_OBJECT_ID_DRIVER_LOADER] =
        {
            .Create = HdfDriverLoaderCreate,
            .Release = NULL,
        },
    [HDF_OBJECT_ID_DEVICE] =
        {
            .Create = HdfDeviceCreate,
            .Release = HdfDeviceRelease,
        },
    [HDF_OBJECT_ID_DEVICE_TOKEN] =
        {
            .Create = HdfDeviceTokenCreate,
            .Release = HdfDeviceTokenRelease,
        },
    [HDF_OBJECT_ID_DEVICE_SERVICE] =
        {
            .Create = DeviceNodeExtCreate,
            .Release = DeviceNodeExtRelease,
        }
};

const struct HdfObjectCreator *HdfObjectManagerGetCreators(int objectId)
{
    int numConfigs = sizeof(g_liteObjectCreators) / sizeof(g_liteObjectCreators[0]);
    if ((objectId >= 0) && (objectId < numConfigs)) {
        return &g_liteObjectCreators[objectId];
    }
    return NULL;
}