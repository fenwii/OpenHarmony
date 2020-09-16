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

#include "module_info_utils.h"

#include "utils.h"

namespace OHOS {
void ModuleInfoUtils::CopyModuleInfo(ModuleInfo *des, ModuleInfo src)
{
    if (des == nullptr) {
        return;
    }
    SetModuleInfoModuleName(des, src.moduleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    SetModuleInfoName(des, src.name);
    SetModuleInfoDescription(des, src.description);
    SetModuleInfoModuleType(des, src.moduleType);
    SetModuleInfoDeviceType(des, src.deviceType, DEVICE_TYPE_SIZE);
    des->isDeliveryInstall = src.isDeliveryInstall;
#endif
    SetModuleInfoMetaData(des, src.metaData, METADATA_SIZE);
}

void ModuleInfoUtils::ClearModuleInfoMetaData(MetaData **metaData, uint32_t numOfMetaData)
{
    if (metaData == nullptr || numOfMetaData > METADATA_SIZE) {
        return;
    }
    for (uint32_t i = 0; i < numOfMetaData; i++) {
        if (metaData[i] != nullptr) {
            AdapterFree(metaData[i]->name);
            AdapterFree(metaData[i]->value);
            AdapterFree(metaData[i]->extra);
            AdapterFree(metaData[i]);
        }
    }
}

void ModuleInfoUtils::ClearModuleInfo(ModuleInfo *moduleInfo)
{
    if (moduleInfo == nullptr) {
        return;
    }
    AdapterFree(moduleInfo->moduleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    AdapterFree(moduleInfo->name);
    AdapterFree(moduleInfo->description);
    AdapterFree(moduleInfo->moduleType);
    ClearModuleInfoDeviceType(moduleInfo->deviceType, DEVICE_TYPE_SIZE);
#endif
    ClearModuleInfoMetaData(moduleInfo->metaData, METADATA_SIZE);
}

bool ModuleInfoUtils::SetModuleInfoModuleName(ModuleInfo *moduleInfo, const char *moduleName)
{
    if (moduleInfo == nullptr || moduleName == nullptr) {
        return false;
    }

    AdapterFree(moduleInfo->moduleName);
    moduleInfo->moduleName = Utils::Strdup(moduleName);
    return moduleInfo->moduleName != nullptr;
}

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
bool ModuleInfoUtils::SetModuleInfoName(ModuleInfo *moduleInfo, const char *name)
{
    if (moduleInfo == nullptr || name == nullptr) {
        return false;
    }

    AdapterFree(moduleInfo->name);
    moduleInfo->name = Utils::Strdup(name);
    return moduleInfo->name != nullptr;
}

bool ModuleInfoUtils::SetModuleInfoDescription(ModuleInfo *moduleInfo, const char *description)
{
    if (moduleInfo == nullptr || description == nullptr) {
        return false;
    }

    AdapterFree(moduleInfo->description);
    moduleInfo->description = Utils::Strdup(description);
    return moduleInfo->description != nullptr;
}

bool ModuleInfoUtils::SetModuleInfoModuleType(ModuleInfo *moduleInfo, const char *moduleType)
{
    if (moduleInfo == nullptr || moduleType == nullptr) {
        return false;
    }

    AdapterFree(moduleInfo->moduleType);
    moduleInfo->moduleType = Utils::Strdup(moduleType);
    return moduleInfo->moduleType != nullptr;
}

bool ModuleInfoUtils::SetModuleInfoDeviceType(ModuleInfo *moduleInfo, char **deviceType, uint32_t numOfDeviceType)
{
    if (moduleInfo == nullptr || deviceType == nullptr || numOfDeviceType > DEVICE_TYPE_SIZE) {
        return false;
    }

    ClearModuleInfoDeviceType(moduleInfo->deviceType, DEVICE_TYPE_SIZE);

    for (uint32_t i = 0; i < numOfDeviceType; i++) {
        if (deviceType[i] != nullptr) {
            moduleInfo->deviceType[i] = Utils::Strdup(deviceType[i]);
            if (moduleInfo->deviceType[i] == nullptr) {
                ClearModuleInfoDeviceType(moduleInfo->deviceType, DEVICE_TYPE_SIZE);
                return false;
            }
        }
    }
    return true;
}

void ModuleInfoUtils::ClearModuleInfoDeviceType(char **deviceType, uint32_t numOfdeviceType)
{
    if (deviceType == nullptr || numOfdeviceType == 0 || numOfdeviceType > DEVICE_TYPE_SIZE) {
        return;
    }
    for (uint32_t i = 0; i < numOfdeviceType; i++) {
        AdapterFree(deviceType[i]);
    }
}
#endif

bool ModuleInfoUtils::SetModuleInfoMetaData(ModuleInfo *moduleInfo, MetaData **metaData, uint32_t numOfMetaData)
{
    if (moduleInfo == nullptr || metaData == nullptr || numOfMetaData > METADATA_SIZE) {
        return false;
    }

    ClearModuleInfoMetaData(moduleInfo->metaData, METADATA_SIZE);

    for (uint32_t i = 0; i < numOfMetaData; i++) {
        if (metaData[i] != nullptr) {
            moduleInfo->metaData[i] = reinterpret_cast<MetaData *>(AdapterMalloc(sizeof(MetaData)));
            if (moduleInfo->metaData[i] == nullptr ||
                memset_s(moduleInfo->metaData[i], sizeof(MetaData), 0, sizeof(MetaData)) != EOK) {
                ClearModuleInfoMetaData(moduleInfo->metaData, i);
                return false;
            }
            if (metaData[i]->name != nullptr) {
                moduleInfo->metaData[i]->name = Utils::Strdup(metaData[i]->name);
            }
            if (metaData[i]->value != nullptr) {
                moduleInfo->metaData[i]->value = Utils::Strdup(metaData[i]->value);
            }
            if (metaData[i]->extra != nullptr) {
                moduleInfo->metaData[i]->extra = Utils::Strdup(metaData[i]->extra);
            }

            if ((metaData[i]->name != nullptr && moduleInfo->metaData[i]->name == nullptr) ||
                (metaData[i]->value != nullptr && moduleInfo->metaData[i]->value == nullptr) ||
                (metaData[i]->extra != nullptr && moduleInfo->metaData[i]->extra == nullptr)) {
                ClearModuleInfoMetaData(moduleInfo->metaData, i);
                return false;
            }
        }
    }
    return true;
}
} // OHOS