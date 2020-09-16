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

#ifndef OHOS_CONVERT_UTILS_H
#define OHOS_CONVERT_UTILS_H

#include "bundle_info.h"
#include "cJSON.h"

namespace OHOS {
struct ConvertUtils {
    static char *ConvertAbilityInfoToString(const AbilityInfo *abilityInfo);
    static char *ConvertBundleInfoToString(const BundleInfo *bundleInfo);
    static char *ConvertBundleInfosToString(BundleInfo **bundleInfo, uint32_t numOfBundleInfo);
    static AbilityInfo *ConvertStringToAbilityInfo(const char *str, size_t buffSize);
    static BundleInfo *ConvertStringToBundleInfo(const char *str, size_t buffSize);
    static bool ConvertStringToBundleInfos(const char *strs, BundleInfo **bundleInfo, uint32_t numOfBundleInfo,
        size_t buffSize);
    static cJSON *GetJsonBundleInfo(const BundleInfo *bundleInfo);
    static cJSON *GetJsonBundleInfos(BundleInfo **bundleInfo, uint32_t numOfBundleInfo);
    static cJSON *GetJsonModuleInfos(const ModuleInfo *moduleInfos, uint32_t numOfModule);
    static cJSON *GetJsonModuleInfoMetaData(const ModuleInfo *moduleInfos, uint32_t index);
    static cJSON *GetJsonModuleInfoDeviceType(const ModuleInfo *moduleInfos, uint32_t index);
    static cJSON *GetJsonAbilityInfos(const AbilityInfo *abilityInfos, uint32_t numOfAbility);
    static cJSON *GetJsonAbilityInfo(const AbilityInfo *abilityInfo);
    static bool ConvertJsonToBundleInfo(const cJSON *root, BundleInfo *bundleInfo);
    static bool ConvertJsonToMetaData(const cJSON *metaDataArray, MetaData **metaData);
    static bool ConvertJsonToDeviceType(const cJSON *deviceTypeArray, char **deviceType);
    static bool ConvertJsonToModuleInfos(const cJSON *moduleArray, ModuleInfo **moduleInfos, uint32_t numOfModule);
    static bool ConvertJsonToAbilityInfo(const cJSON *root, AbilityInfo *abilityInfo);
    static bool ConvertJsonToAbilityInfos(const cJSON *abilityArray, AbilityInfo **abilityInfos, uint32_t numOfAbility);
private:
    ConvertUtils() = default;
    ~ConvertUtils() = default;
    static bool ConvertBundleInfoPartToJson(const BundleInfo *bundleInfo, cJSON *root);
    static bool ConvertModuleInfosToJson(const BundleInfo *bundleInfo, cJSON *root);
    static bool ConvertAbilityInfosToJson(const BundleInfo *bundleInfo, cJSON *root);
    static bool ConvertModuleInfoMetaDataToJson(const ModuleInfo *moduleInfos, uint32_t index, cJSON *item);
    static bool ConvertModuleInfoDeviceTypeToJson(const ModuleInfo *moduleInfos, uint32_t index, cJSON *item);
}; // ConvertUtils
} // OHOS
#endif // OHOS_CONVERT_UTILS_H