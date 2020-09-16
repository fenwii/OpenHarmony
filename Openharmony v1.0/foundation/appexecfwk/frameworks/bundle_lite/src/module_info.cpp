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

#include "module_info.h"

#include "module_info_utils.h"
#include "utils.h"

void ClearModuleInfo(ModuleInfo *moduleInfo)
{
    if (moduleInfo == nullptr) {
        return;
    }
    AdapterFree(moduleInfo->moduleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    AdapterFree(moduleInfo->name);
    AdapterFree(moduleInfo->description);
    AdapterFree(moduleInfo->moduleType);
    OHOS::ModuleInfoUtils::ClearModuleInfoDeviceType(moduleInfo->deviceType, DEVICE_TYPE_SIZE);
#endif
    OHOS::ModuleInfoUtils::ClearModuleInfoMetaData(moduleInfo->metaData, METADATA_SIZE);
}