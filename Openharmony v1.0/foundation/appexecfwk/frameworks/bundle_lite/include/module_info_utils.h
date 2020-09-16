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

#ifndef OHOS_MODULEINFO_UTILS_H
#define OHOS_MODULEINFO_UTILS_H

#include "module_info.h"
#include "utils.h"

namespace OHOS {
struct ModuleInfoUtils {
    static void CopyModuleInfo(ModuleInfo *des, ModuleInfo src);
    static void ClearModuleInfoMetaData(MetaData **metaData, uint32_t numOfMetaData);
    static void ClearModuleInfo(ModuleInfo *moduleInfo);
    static bool SetModuleInfoModuleName(ModuleInfo *moduleInfo, const char *moduleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    static bool SetModuleInfoName(ModuleInfo *moduleInfo, const char *name);
    static bool SetModuleInfoDescription(ModuleInfo *moduleInfo, const char *description);
    static bool SetModuleInfoModuleType(ModuleInfo *moduleInfo, const char *moduleType);
    static bool SetModuleInfoDeviceType(ModuleInfo *moduleInfo, char **deviceType, uint32_t numOfDeviceType);
    static void ClearModuleInfoDeviceType(char **deviceType, uint32_t numOfdeviceType);
#endif
    static bool SetModuleInfoMetaData(ModuleInfo *moduleInfo, MetaData **metaData, uint32_t numOfMetaData);
private:
    ModuleInfoUtils() = default;
    ~ModuleInfoUtils() = default;
}; // ModuleInfoUtils
} // OHOS
#endif // OHOS_MODULEINFO_UTILS_H