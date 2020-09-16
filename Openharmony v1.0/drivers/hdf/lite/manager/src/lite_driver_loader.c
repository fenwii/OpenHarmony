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

#include "hdf_driver_loader.h"
#include <string.h>
#include "hdf_log.h"

struct HdfDriverEntry *HdfDriverLoaderGetDriverEntry(const struct HdfDeviceInfo *deviceInfo)
{
    int count = (int) (((uint8_t *)(HDF_DRIVER_END()) - (uint8_t *)(HDF_DRIVER_BEGIN())) / sizeof(size_t));
    size_t *addrBegin = (size_t*)(HDF_DRIVER_BEGIN());
    if ((deviceInfo == NULL) || (deviceInfo->moduleName == NULL) || (deviceInfo->svcName == NULL)) {
        HDF_LOGE("Hdf get device entry failed, input deviceInfo is NULL!");
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        struct HdfDriverEntry *driverEntry = (struct HdfDriverEntry *)(*addrBegin);
        if (strcmp(deviceInfo->moduleName, driverEntry->moduleName) == 0) {
            return driverEntry;
        }
        addrBegin++;
    }
    HDF_LOGE("Hdf get %s device entry failed!", deviceInfo->svcName);
    return NULL;
}

