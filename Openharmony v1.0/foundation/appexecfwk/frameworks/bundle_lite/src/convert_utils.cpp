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

#include "convert_utils.h"

#include "ability_info_utils.h"
#include "bundle_info_utils.h"
#include "log.h"
#include "module_info_utils.h"
#include "securec.h"
#include "utils.h"

namespace OHOS {
// bundleInfo json key
const char BUNDLEINFO_JSON_KEY_SYSTEMAPP[] = "isSystemApp";
const char BUNDLEINFO_JSON_KEY_NATIVEAPP[] = "isNativeApp";
const char BUNDLEINFO_JSON_KEY_KEEPALIVE[] = "isKeepAlive";
const char BUNDLEINFO_JSON_KEY_VERSIONCODE[] = "versionCode";
const char BUNDLEINFO_JSON_KEY_UID[] = "uid";
const char BUNDLEINFO_JSON_KEY_GID[] = "gid";
const char BUNDLEINFO_JSON_KEY_VERSIONNAME[] = "versionName";
const char BUNDLEINFO_JSON_KEY_BUNDLENAME[] = "bundleName";
const char BUNDLEINFO_JSON_KEY_LABLE[] = "label";
const char BUNDLEINFO_JSON_KEY_ICONPATH[] = "iconPath";
const char BUNDLEINFO_JSON_KEY_CODEPATH[] = "codePath";
const char BUNDLEINFO_JSON_KEY_DATAPATH[] = "dataPath";
const char BUNDLEINFO_JSON_KEY_COMPATIBLEAPI[] = "compatibleApi";
const char BUNDLEINFO_JSON_KEY_TARGETAPI[] = "targetApi";
const char BUNDLEINFO_JSON_KEY_VENDOR[] = "vendor";
const char BUNDLEINFO_JSON_KEY_APPID[] = "appId";
const char BUNDLEINFO_JSON_KEY_NUMOFMODULE[] = "numOfModule";
const char BUNDLEINFO_JSON_KEY_MODULEINFOS[] = "moduleInfos";
const char BUNDLEINFO_JSON_KEY_NUMOFABILITY[] = "numOfAbility";
const char BUNDLEINFO_JSON_KEY_ABILITYINFOS[] = "abilityInfos";
// abilityInfo json key
const char ABILITYINFO_JSON_KEY_BUNDLENAME[] = "bundleName";
const char ABILITYINFO_JSON_KEY_NAME[] = "name";
const char ABILITYINFO_JSON_KEY_ABILITYTYPE[] = "abilityType";
const char ABILITYINFO_JSON_KEY_LAUNCHMODE[] = "launchMode";
const char ABILITYINFO_JSON_KEY_VISIBLE[] = "isVisible";
const char ABILITYINFO_JSON_KEY_MODULENAME[] = "moduleName";
const char ABILITYINFO_JSON_KEY_DESCRIPTION[] = "description";
const char ABILITYINFO_JSON_KEY_ICONPATH[] = "iconPath";
const char ABILITYINFO_JSON_KEY_DEVICEID[] = "deviceId";
const char ABILITYINFO_JSON_KEY_LABEL[] = "label";
// moduleInfo json key
const char MODULEINFO_JSON_KEY_NAME[] = "name";
const char MODULEINFO_JSON_KEY_DESCRIPTION[] = "description";
const char MODULEINFO_JSON_KEY_MODULENAME[] = "moduleName";
const char MODULEINFO_JSON_KEY_MODULETYPE[] = "moduleType";
const char MODULEINFO_JSON_KEY_DELIVERYINSTALL[] = "isDeliveryInstall";
const char MODULEINFO_JSON_KEY_DEVICETYPE[] = "deviceType";
const char MODULEINFO_JSON_KEY_METADATA[] = "metaData";
const char MODULEINFO_JSON_KEY_METADATA_NAME[] = "name";
const char MODULEINFO_JSON_KEY_METADATA_VALUE[] = "value";
const char MODULEINFO_JSON_KEY_METADATA_EXTRA[] = "extra";

char *ConvertUtils::ConvertAbilityInfoToString(const AbilityInfo *abilityInfo)
{
    if (abilityInfo == nullptr) {
        return nullptr;
    }
    cJSON *root = GetJsonAbilityInfo(abilityInfo);
    if (root == nullptr) {
        return nullptr;
    }
    char *str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return str;
}

char *ConvertUtils::ConvertBundleInfoToString(const BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return nullptr;
    }
    cJSON *root = GetJsonBundleInfo(bundleInfo);
    if (root == nullptr) {
        return nullptr;
    }
    char *str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return str;
}

char *ConvertUtils::ConvertBundleInfosToString(BundleInfo **bundleInfo, uint32_t numOfBundleInfo)
{
    if (bundleInfo == nullptr || numOfBundleInfo == 0) {
        return nullptr;
    }
    cJSON *roots = GetJsonBundleInfos(bundleInfo, numOfBundleInfo);
    if (roots == nullptr) {
        return nullptr;
    }
    char *strs = cJSON_PrintUnformatted(roots);
    cJSON_Delete(roots);
    return strs;
}

AbilityInfo *ConvertUtils::ConvertStringToAbilityInfo(const char *str, size_t buffSize)
{
    if (str == nullptr) {
        return nullptr;
    }
    AbilityInfo *abilityInfo = reinterpret_cast<AbilityInfo *>(AdapterMalloc(sizeof(AbilityInfo)));
    if (abilityInfo == nullptr) {
        return nullptr;
    }
    if (memset_s(abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo)) != EOK) {
        AdapterFree(abilityInfo);
        return nullptr;
    }
    cJSON *root = cJSON_ParseWithLength(str, buffSize);
    if (root == nullptr) {
        AdapterFree(abilityInfo);
        return nullptr;
    }
    if (!ConvertJsonToAbilityInfo(root, abilityInfo)) {
        ClearAbilityInfo(abilityInfo);
        AdapterFree(abilityInfo);
        cJSON_Delete(root);
        return nullptr;
    }
    cJSON_Delete(root);
    return abilityInfo;
}

BundleInfo *ConvertUtils::ConvertStringToBundleInfo(const char *str, size_t buffSize)
{
    if (str == nullptr) {
        return nullptr;
    }
    BundleInfo *bundleInfo = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo)));
    if (bundleInfo == nullptr) {
        return nullptr;
    }
    if (memset_s(bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo)) != EOK) {
        AdapterFree(bundleInfo);
        return nullptr;
    }
    cJSON *root = cJSON_ParseWithLength(str, buffSize);
    if (root == nullptr) {
        AdapterFree(bundleInfo);
        return nullptr;
    }

    if (!ConvertJsonToBundleInfo(root, bundleInfo)) {
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        cJSON_Delete(root);
        return nullptr;
    }
    cJSON_Delete(root);
    return bundleInfo;
}

bool ConvertUtils::ConvertStringToBundleInfos(const char *strs, BundleInfo **bundleInfo, uint32_t numOfBundleInfo,
    size_t buffSize)
{
    if (strs == nullptr || bundleInfo == nullptr || numOfBundleInfo == 0) {
        return false;
    }
    cJSON *roots = cJSON_ParseWithLength(strs, buffSize);
    if (roots == nullptr) {
        return false;
    }

    if (!cJSON_IsArray(roots) || static_cast<uint32_t>(cJSON_GetArraySize(roots)) != numOfBundleInfo) {
        cJSON_Delete(roots);
        return false;
    }

    *bundleInfo = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo) * numOfBundleInfo));
    if (*bundleInfo == nullptr) {
        cJSON_Delete(roots);
        return false;
    }
    int32_t ret =
        memset_s(*bundleInfo, sizeof(BundleInfo) * numOfBundleInfo, 0, sizeof(BundleInfo) * numOfBundleInfo);
    if (ret != EOK) {
        AdapterFree(*bundleInfo);
        cJSON_Delete(roots);
        return false;
    }

    cJSON *item = nullptr;
    uint32_t i = 0;
    cJSON_ArrayForEach(item, roots) {
        if (!ConvertJsonToBundleInfo(item, *bundleInfo + i)) {
            BundleInfoUtils::FreeBundleInfos(*bundleInfo, numOfBundleInfo);
            cJSON_Delete(roots);
            return false;
        }
        i++;
    }
    cJSON_Delete(roots);
    return true;
}

cJSON *ConvertUtils::GetJsonBundleInfo(const BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return nullptr;
    }
    cJSON *root = cJSON_CreateObject();
    if (root == nullptr) {
        return nullptr;
    }
    if (!ConvertBundleInfoPartToJson(bundleInfo, root)) {
        cJSON_Delete(root);
        return nullptr;
    }
    // set moduleInfos in json
    if (!ConvertModuleInfosToJson(bundleInfo, root)) {
        cJSON_Delete(root);
        return nullptr;
    }
    // set abilityInfos in json when is exists
    if (!ConvertAbilityInfosToJson(bundleInfo, root)) {
        cJSON_Delete(root);
        return nullptr;
    }
    return root;
}

bool ConvertUtils::ConvertBundleInfoPartToJson(const BundleInfo *bundleInfo, cJSON *root)
{
    if (bundleInfo == nullptr || root == nullptr) {
        return false;
    }
    // set mandatory fileds in json
    if (cJSON_AddBoolToObject(root, BUNDLEINFO_JSON_KEY_SYSTEMAPP, bundleInfo->isSystemApp) == nullptr ||
        cJSON_AddBoolToObject(root, BUNDLEINFO_JSON_KEY_NATIVEAPP, bundleInfo->isNativeApp) == nullptr ||
        cJSON_AddBoolToObject(root, BUNDLEINFO_JSON_KEY_KEEPALIVE, bundleInfo->isKeepAlive) == nullptr ||
        cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_VERSIONCODE, bundleInfo->versionCode) == nullptr ||
        cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_UID, bundleInfo->uid) == nullptr ||
        cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_GID, bundleInfo->gid) == nullptr ||
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_VERSIONNAME, bundleInfo->versionName) == nullptr ||
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_BUNDLENAME, bundleInfo->bundleName) == nullptr ||
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_CODEPATH, bundleInfo->codePath) == nullptr ||
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_DATAPATH, bundleInfo->dataPath) == nullptr ||
        cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_COMPATIBLEAPI, bundleInfo->compatibleApi) == nullptr ||
        cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_TARGETAPI, bundleInfo->targetApi) == nullptr ||
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_APPID, bundleInfo->appId) == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "set mandatory fileds fail in bundleInfo json!");
        return false;
    }
    // set optional field which is not nullptr in json
    if ((bundleInfo->label != nullptr &&
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_LABLE, bundleInfo->label) == nullptr) ||
        (bundleInfo->bigIconPath != nullptr &&
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_ICONPATH, bundleInfo->bigIconPath) == nullptr) ||
        (bundleInfo->vendor != nullptr &&
        cJSON_AddStringToObject(root, BUNDLEINFO_JSON_KEY_VENDOR, bundleInfo->vendor) == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_APP, "set optional filed fail which not nullptr in bundleInfo json!");
        return false;
    }
    return true;
}

bool ConvertUtils::ConvertModuleInfosToJson(const BundleInfo *bundleInfo, cJSON *root)
{
    if (bundleInfo == nullptr || root == nullptr || bundleInfo->numOfModule <= 0) {
        return false;
    }

    cJSON *moduleInfosJson = GetJsonModuleInfos(bundleInfo->moduleInfos, bundleInfo->numOfModule);
    if (moduleInfosJson == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "get modulseInfos fail when convert moduleInfo to json!");
        return false;
    }

    if (cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_NUMOFMODULE, bundleInfo->numOfModule) == nullptr) {
        cJSON_Delete(moduleInfosJson);
        HILOG_ERROR(HILOG_MODULE_APP, "cJSON_AddNumberToObject fail when convert moduleInfo to json!");
        return false;
    }

    if (!cJSON_AddItemToObject(root, BUNDLEINFO_JSON_KEY_MODULEINFOS, moduleInfosJson)) {
        cJSON_Delete(moduleInfosJson);
        HILOG_ERROR(HILOG_MODULE_APP, "cJSON_AddItemToObject fail when convert moduleInfo to json!");
        return false;
    }
    return true;
}

bool ConvertUtils::ConvertAbilityInfosToJson(const BundleInfo *bundleInfo, cJSON *root)
{
    if (bundleInfo == nullptr || root == nullptr || bundleInfo->numOfAbility < 0) {
        return false;
    }

    if (bundleInfo->numOfAbility == 0) {
        return true;
    }

    cJSON *abilitysJson = GetJsonAbilityInfos(bundleInfo->abilityInfos, bundleInfo->numOfAbility);
    if (abilitysJson == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "get abilityInfos fail when convert abilityInfo to json!");
        return false;
    }
    if (cJSON_AddNumberToObject(root, BUNDLEINFO_JSON_KEY_NUMOFABILITY, bundleInfo->numOfAbility) == nullptr) {
        cJSON_Delete(abilitysJson);
        HILOG_ERROR(HILOG_MODULE_APP, "cJSON_AddNumberToObject fail when convert abilityInfo to json!");
        return false;
    }
    if (!cJSON_AddItemToObject(root, BUNDLEINFO_JSON_KEY_ABILITYINFOS, abilitysJson)) {
        cJSON_Delete(abilitysJson);
        HILOG_ERROR(HILOG_MODULE_APP, "cJSON_AddItemToObject fail when convert abilityInfo to json!");
        return false;
    }
    return true;
}

cJSON *ConvertUtils::GetJsonBundleInfos(BundleInfo **bundleInfo, uint32_t numOfBundleInfo)
{
    if (bundleInfo == nullptr) {
        return nullptr;
    }
    cJSON *roots = cJSON_CreateArray();
    if (roots == nullptr) {
        return nullptr;
    }

    for (uint32_t i = 0; i < numOfBundleInfo; i++) {
        cJSON *item = GetJsonBundleInfo(*bundleInfo + i);
        if (item == nullptr) {
            cJSON_Delete(roots);
            return nullptr;
        }
        if (!cJSON_AddItemToArray(roots, item)) {
            cJSON_Delete(item);
            cJSON_Delete(roots);
            return nullptr;
        }
    }
    return roots;
}

cJSON *ConvertUtils::GetJsonModuleInfos(const ModuleInfo *moduleInfos, uint32_t numOfModule)
{
    if (moduleInfos == nullptr) {
        return nullptr;
    }
    cJSON *jsonModuleInfos = cJSON_CreateArray();
    if (jsonModuleInfos == nullptr) {
        return nullptr;
    }
    for (uint32_t index = 0; index < numOfModule; ++index) {
        cJSON *moduleInfosItem = cJSON_CreateObject();
        if (moduleInfosItem == nullptr) {
            cJSON_Delete(jsonModuleInfos);
            return nullptr;
        }
        // set mandatory fileds in json
        if (cJSON_AddStringToObject(moduleInfosItem, MODULEINFO_JSON_KEY_MODULENAME,
            moduleInfos[index].moduleName) == nullptr ||
            cJSON_AddStringToObject(moduleInfosItem, MODULEINFO_JSON_KEY_MODULETYPE,
            moduleInfos[index].moduleType) == nullptr ||
            cJSON_AddBoolToObject(moduleInfosItem, MODULEINFO_JSON_KEY_DELIVERYINSTALL,
            moduleInfos[index].isDeliveryInstall) == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "set mandatory fileds fail in moduleInfo json!");
            cJSON_Delete(moduleInfosItem);
            cJSON_Delete(jsonModuleInfos);
            return nullptr;
        }
        // set optional field which is not nullptr in json
        if ((moduleInfos[index].name != nullptr && cJSON_AddStringToObject(moduleInfosItem,
            MODULEINFO_JSON_KEY_NAME, moduleInfos[index].name) == nullptr) ||
            (moduleInfos[index].description != nullptr && cJSON_AddStringToObject(moduleInfosItem,
            ABILITYINFO_JSON_KEY_DESCRIPTION, moduleInfos[index].description) == nullptr)) {
            HILOG_ERROR(HILOG_MODULE_APP, "set optional fileds fail in moduleInfo json!");
            cJSON_Delete(moduleInfosItem);
            cJSON_Delete(jsonModuleInfos);
            return nullptr;
        }
        if (!ConvertModuleInfoMetaDataToJson(moduleInfos, index, moduleInfosItem)) {
            cJSON_Delete(moduleInfosItem);
            cJSON_Delete(jsonModuleInfos);
            return nullptr;
        }
        if (!ConvertModuleInfoDeviceTypeToJson(moduleInfos, index, moduleInfosItem)) {
            cJSON_Delete(moduleInfosItem);
            cJSON_Delete(jsonModuleInfos);
            return nullptr;
        }
        if (!cJSON_AddItemToArray(jsonModuleInfos, moduleInfosItem)) {
            HILOG_ERROR(HILOG_MODULE_APP, "add moduleInfosItem in jsonModuleInfos fail!");
            cJSON_Delete(moduleInfosItem);
            cJSON_Delete(jsonModuleInfos);
            return nullptr;
        }
    }
    return jsonModuleInfos;
}

bool ConvertUtils::ConvertModuleInfoMetaDataToJson(const ModuleInfo *moduleInfos, uint32_t index, cJSON *item)
{
    if (moduleInfos == nullptr || item == nullptr) {
        return false;
    }

    if (moduleInfos[index].metaData[0] == nullptr) {
        return true;
    }

    cJSON *metaDataJson = GetJsonModuleInfoMetaData(moduleInfos, index);
    if (metaDataJson == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "get metaDataJson fail in moduleInfo json when metaData is not null!");
        return false;
    }

    if (!cJSON_AddItemToObject(item, MODULEINFO_JSON_KEY_METADATA, metaDataJson)) {
        HILOG_ERROR(HILOG_MODULE_APP, "set metaDataJson fail in moduleInfo json when metaData is not null!");
        cJSON_Delete(metaDataJson);
        return false;
    }
    return true;
}

bool ConvertUtils::ConvertModuleInfoDeviceTypeToJson(const ModuleInfo *moduleInfos, uint32_t index, cJSON *item)
{
    if (moduleInfos == nullptr || item == nullptr) {
        return false;
    }

    if (moduleInfos[index].deviceType[0] == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "deviceType is null!");
        return false;
    }

    cJSON *deviceTypeJson = GetJsonModuleInfoDeviceType(moduleInfos, index);
    if (deviceTypeJson == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "get deviceType fail in moduleInfo json when deviceType is not null!");
        return false;
    }

    if (!cJSON_AddItemToObject(item, MODULEINFO_JSON_KEY_DEVICETYPE, deviceTypeJson)) {
        cJSON_Delete(deviceTypeJson);
        HILOG_ERROR(HILOG_MODULE_APP, "set deviceType fail in moduleInfo json when deviceType is not null!");
        return false;
    }
    return true;
}

cJSON *ConvertUtils::GetJsonModuleInfoMetaData(const ModuleInfo *moduleInfos, uint32_t index)
{
    if (moduleInfos == nullptr) {
        return nullptr;
    }
    cJSON *jsonMetaData = cJSON_CreateArray();
    if (jsonMetaData == nullptr) {
        return nullptr;
    }
    for (uint32_t metaDataIndex = 0; metaDataIndex < METADATA_SIZE; ++metaDataIndex) {
        if (moduleInfos[index].metaData[metaDataIndex] == nullptr) {
            break;
        }
        cJSON *metaDataItem = cJSON_CreateObject();
        if (metaDataItem == nullptr) {
            cJSON_Delete(jsonMetaData);
            return nullptr;
        }
        if ((moduleInfos[index].metaData[metaDataIndex]->name != nullptr && cJSON_AddStringToObject(metaDataItem,
            MODULEINFO_JSON_KEY_METADATA_NAME, moduleInfos[index].metaData[metaDataIndex]->name) == nullptr) ||
            (moduleInfos[index].metaData[metaDataIndex]->value != nullptr && cJSON_AddStringToObject(metaDataItem,
            MODULEINFO_JSON_KEY_METADATA_VALUE, moduleInfos[index].metaData[metaDataIndex]->value) == nullptr) ||
            (moduleInfos[index].metaData[metaDataIndex]->extra != nullptr && cJSON_AddStringToObject(metaDataItem,
            MODULEINFO_JSON_KEY_METADATA_EXTRA, moduleInfos[index].metaData[metaDataIndex]->extra) == nullptr) ||
            !cJSON_AddItemToArray(jsonMetaData, metaDataItem)) {
            cJSON_Delete(metaDataItem);
            cJSON_Delete(jsonMetaData);
            return nullptr;
        }
    }
    return jsonMetaData;
}

cJSON *ConvertUtils::GetJsonModuleInfoDeviceType(const ModuleInfo *moduleInfos, uint32_t index)
{
    if (moduleInfos == nullptr) {
        return nullptr;
    }
    cJSON *jsonDeviceType = cJSON_CreateArray();
    if (jsonDeviceType == nullptr) {
        return nullptr;
    }
    for (int32_t deviceTypeIndex = 0; deviceTypeIndex < DEVICE_TYPE_SIZE; ++deviceTypeIndex) {
        if (moduleInfos[index].deviceType[deviceTypeIndex] == nullptr) {
            break;
        }
        cJSON *object = cJSON_CreateString(moduleInfos[index].deviceType[deviceTypeIndex]);
        if (object == nullptr) {
            cJSON_Delete(jsonDeviceType);
            return nullptr;
        }
        if (!cJSON_AddItemToArray(jsonDeviceType, object)) {
            cJSON_Delete(object);
            cJSON_Delete(jsonDeviceType);
            return nullptr;
        }
    }
    return jsonDeviceType;
}

cJSON *ConvertUtils::GetJsonAbilityInfos(const AbilityInfo *abilityInfos, uint32_t numOfAbility)
{
    cJSON *jsonAbilityInfos = cJSON_CreateArray();
    if (jsonAbilityInfos == nullptr) {
        return nullptr;
    }
    for (uint32_t index = 0; index < numOfAbility; ++index) {
        cJSON *item = GetJsonAbilityInfo(abilityInfos + index);
        if (item == nullptr) {
            cJSON_Delete(jsonAbilityInfos);
            return nullptr;
        }
        if (!cJSON_AddItemToArray(jsonAbilityInfos, item)) {
            cJSON_Delete(item);
            cJSON_Delete(jsonAbilityInfos);
            return nullptr;
        }
    }
    return jsonAbilityInfos;
}

cJSON *ConvertUtils::GetJsonAbilityInfo(const AbilityInfo *abilityInfo)
{
    cJSON *root = cJSON_CreateObject();
    if (root == nullptr) {
        return nullptr;
    }
    // set mandatory fileds in json
    if (cJSON_AddBoolToObject(root, ABILITYINFO_JSON_KEY_VISIBLE, abilityInfo->isVisible) == nullptr ||
        cJSON_AddNumberToObject(root, ABILITYINFO_JSON_KEY_ABILITYTYPE, abilityInfo->abilityType) == nullptr ||
        cJSON_AddNumberToObject(root, ABILITYINFO_JSON_KEY_LAUNCHMODE, abilityInfo->launchMode) == nullptr ||
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_BUNDLENAME, abilityInfo->bundleName) == nullptr ||
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_MODULENAME, abilityInfo->moduleName) == nullptr ||
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_NAME, abilityInfo->name) == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "set mandatory fileds fail in abilityInfo json!");
        cJSON_Delete(root);
        return nullptr;
    }
    // set optional fields in json
    if ((abilityInfo->description != nullptr &&
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_DESCRIPTION, abilityInfo->description) == nullptr) ||
        (abilityInfo->iconPath != nullptr &&
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_ICONPATH, abilityInfo->iconPath) == nullptr) ||
        (abilityInfo->label != nullptr &&
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_LABEL, abilityInfo->label) == nullptr) ||
        (abilityInfo->deviceId != nullptr &&
        cJSON_AddStringToObject(root, ABILITYINFO_JSON_KEY_DEVICEID, abilityInfo->deviceId) == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_APP, "set optional fileds fail in abilityInfo json!");
        cJSON_Delete(root);
        return nullptr;
    }
    return root;
}

bool ConvertUtils::ConvertJsonToBundleInfo(const cJSON *root, BundleInfo *bundleInfo)
{
    if (root == nullptr || bundleInfo == nullptr) {
        return false;
    }
    cJSON *item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_SYSTEMAPP);
    if (cJSON_IsBool(item)) {
        bundleInfo->isSystemApp = cJSON_IsTrue(item);
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_NATIVEAPP);
    if (cJSON_IsBool(item)) {
        bundleInfo->isNativeApp = cJSON_IsTrue(item);
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_KEEPALIVE);
    if (cJSON_IsBool(item)) {
        bundleInfo->isKeepAlive = cJSON_IsTrue(item);
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_VERSIONCODE);
    if (cJSON_IsNumber(item)) {
        bundleInfo->versionCode = item->valueint;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_UID);
    if (cJSON_IsNumber(item)) {
        bundleInfo->uid = item->valueint;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_GID);
    if (cJSON_IsNumber(item)) {
        bundleInfo->gid = item->valueint;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_COMPATIBLEAPI);
    if (cJSON_IsNumber(item)) {
        bundleInfo->compatibleApi = item->valueint;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_TARGETAPI);
    if (cJSON_IsNumber(item)) {
        bundleInfo->targetApi = item->valueint;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_VERSIONNAME);
    if (!cJSON_IsString(item) || !BundleInfoUtils::SetBundleInfoVersionName(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_BUNDLENAME);
    if (!cJSON_IsString(item) || !BundleInfoUtils::SetBundleInfoBundleName(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_LABLE);
    if (cJSON_IsString(item) && !BundleInfoUtils::SetBundleInfoLabel(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_ICONPATH);
    if (cJSON_IsString(item) && !BundleInfoUtils::SetBundleInfoBigIconPath(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_CODEPATH);
    if (!cJSON_IsString(item) || !BundleInfoUtils::SetBundleInfoCodePath(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_DATAPATH);
    if (!cJSON_IsString(item) || !BundleInfoUtils::SetBundleInfoDataPath(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_VENDOR);
    if (cJSON_IsString(item) && !BundleInfoUtils::SetBundleInfoVendor(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_APPID);
    if (!cJSON_IsString(item) || !BundleInfoUtils::SetBundleInfoAppId(bundleInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_NUMOFMODULE);
    if (cJSON_IsNumber(item) && item->valueint > 0) {
        bundleInfo->numOfModule = item->valueint;
        if (!ConvertJsonToModuleInfos(cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_MODULEINFOS),
            &(bundleInfo->moduleInfos), bundleInfo->numOfModule)) {
            return false;
        }
    }
    item = cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_NUMOFABILITY);
    if (cJSON_IsNumber(item) && item->valueint > 0) {
        bundleInfo->numOfAbility = item->valueint;
        if (!ConvertJsonToAbilityInfos(cJSON_GetObjectItem(root, BUNDLEINFO_JSON_KEY_ABILITYINFOS),
            &(bundleInfo->abilityInfos), bundleInfo->numOfAbility)) {
            return false;
        }
    }
    return true;
}

bool ConvertUtils::ConvertJsonToMetaData(const cJSON *metaDataArray, MetaData **metaData)
{
    if (metaData == nullptr || !cJSON_IsArray(metaDataArray) || cJSON_GetArraySize(metaDataArray) > METADATA_SIZE) {
        return false;
    }
    ModuleInfoUtils::ClearModuleInfoMetaData(metaData, METADATA_SIZE);
    cJSON *metaDataItem = nullptr;
    uint32_t index = 0;
    cJSON_ArrayForEach(metaDataItem, metaDataArray) {
        metaData[index] = reinterpret_cast<MetaData *>(AdapterMalloc(sizeof(MetaData)));
        if (metaData[index] == nullptr) {
            return false;
        }
        int32_t ret = memset_s(metaData[index], sizeof(MetaData), 0, sizeof(MetaData));
        if (ret != EOK) {
            AdapterFree(metaData[index]);
            return false;
        }
        cJSON *item = cJSON_GetObjectItem(metaDataItem, MODULEINFO_JSON_KEY_METADATA_NAME);
        if (cJSON_IsString(item) && (metaData[index]->name = Utils::Strdup(item->valuestring)) == nullptr) {
            return false;
        }
        item = cJSON_GetObjectItem(metaDataItem, MODULEINFO_JSON_KEY_METADATA_VALUE);
        if (cJSON_IsString(item) && (metaData[index]->value = Utils::Strdup(item->valuestring)) == nullptr) {
            return false;
        }
        item = cJSON_GetObjectItem(metaDataItem, MODULEINFO_JSON_KEY_METADATA_EXTRA);
        if (cJSON_IsString(item) && (metaData[index]->extra = Utils::Strdup(item->valuestring)) == nullptr) {
            return false;
        }
        ++index;
    }
    return true;
}

bool ConvertUtils::ConvertJsonToDeviceType(const cJSON *deviceTypeArray, char **deviceType)
{
    if (deviceType == nullptr || !cJSON_IsArray(deviceTypeArray) ||
        cJSON_GetArraySize(deviceTypeArray) > DEVICE_TYPE_SIZE) {
        return false;
    }
    ModuleInfoUtils::ClearModuleInfoDeviceType(deviceType, DEVICE_TYPE_SIZE);
    cJSON *deviceTypeItem = nullptr;
    uint32_t index = 0;
    cJSON_ArrayForEach(deviceTypeItem, deviceTypeArray) {
        if (!cJSON_IsString(deviceTypeItem)) {
            return false;
        }
        deviceType[index] = Utils::Strdup(deviceTypeItem->valuestring);
        if (deviceType[index] == nullptr) {
            return false;
        }
        ++index;
    }
    return true;
}

bool ConvertUtils::ConvertJsonToModuleInfos(const cJSON *moduleArray, ModuleInfo **moduleInfos, uint32_t numOfModule)
{
    if (moduleInfos == nullptr || !cJSON_IsArray(moduleArray) || numOfModule == 0 ||
        static_cast<uint32_t>(cJSON_GetArraySize(moduleArray)) != numOfModule) {
        return false;
    }

    *moduleInfos = reinterpret_cast<ModuleInfo*>(AdapterMalloc(sizeof(ModuleInfo) * numOfModule));
    if (*moduleInfos == nullptr) {
        return false;
    }

    int32_t ret = memset_s(*moduleInfos, sizeof(ModuleInfo) * numOfModule, 0, sizeof(ModuleInfo) * numOfModule);
    if (ret != EOK) {
        AdapterFree(*moduleInfos);
        return false;
    }
    cJSON *moduleItem = nullptr;
    uint32_t index = 0;
    cJSON_ArrayForEach(moduleItem, moduleArray) {
        cJSON *item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_NAME);
        if (cJSON_IsString(item) && !ModuleInfoUtils::SetModuleInfoName(*moduleInfos + index, item->valuestring)) {
            return false;
        }
        item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_DESCRIPTION);
        if (cJSON_IsString(item) &&
            !ModuleInfoUtils::SetModuleInfoDescription(*moduleInfos + index, item->valuestring)) {
            return false;
        }
        item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_MODULENAME);
        if (!cJSON_IsString(item) ||
            !ModuleInfoUtils::SetModuleInfoModuleName(*moduleInfos + index, item->valuestring)) {
            return false;
        }
        item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_MODULETYPE);
        if (!cJSON_IsString(item) ||
            !ModuleInfoUtils::SetModuleInfoModuleType(*moduleInfos + index, item->valuestring)) {
            return false;
        }
        item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_DELIVERYINSTALL);
        if (cJSON_IsBool(item)) {
            (*moduleInfos + index)->isDeliveryInstall = cJSON_IsTrue(item);
        }
        item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_METADATA);
        if (cJSON_IsArray(item) && !ConvertJsonToMetaData(item, (*moduleInfos + index)->metaData)) {
            return false;
        }
        item = cJSON_GetObjectItem(moduleItem, MODULEINFO_JSON_KEY_DEVICETYPE);
        if (!cJSON_IsArray(item) || !ConvertJsonToDeviceType(item, (*moduleInfos + index)->deviceType)) {
            return false;
        }
    }
    return true;
}

bool ConvertUtils::ConvertJsonToAbilityInfo(const cJSON *root, AbilityInfo *abilityInfo)
{
    if (root == nullptr || abilityInfo == nullptr) {
        return false;
    }

    cJSON *item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_BUNDLENAME);
    if (!cJSON_IsString(item) || !AbilityInfoUtils::SetAbilityInfoBundleName(abilityInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_NAME);
    if (!cJSON_IsString(item) || !AbilityInfoUtils::SetAbilityInfoName(abilityInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_ABILITYTYPE);
    if (cJSON_IsNumber(item)) {
        abilityInfo->abilityType = AbilityType(item->valueint);
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_LAUNCHMODE);
    if (cJSON_IsNumber(item)) {
        abilityInfo->launchMode = LaunchMode(item->valueint);
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_VISIBLE);
    abilityInfo->isVisible = cJSON_IsTrue(item);
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_MODULENAME);
    if (!cJSON_IsString(item) || !AbilityInfoUtils::SetAbilityInfoModuleName(abilityInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_DESCRIPTION);
    if (cJSON_IsString(item) && !AbilityInfoUtils::SetAbilityInfoDescription(abilityInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_ICONPATH);
    if (cJSON_IsString(item) && !AbilityInfoUtils::SetAbilityInfoIconPath(abilityInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_DEVICEID);
    if (cJSON_IsString(item) && !AbilityInfoUtils::SetAbilityInfoDeviceId(abilityInfo, item->valuestring)) {
        return false;
    }
    item = cJSON_GetObjectItem(root, ABILITYINFO_JSON_KEY_LABEL);
    if (cJSON_IsString(item) && !AbilityInfoUtils::SetAbilityInfoLabel(abilityInfo, item->valuestring)) {
        return false;
    }
    return true;
}

bool ConvertUtils::ConvertJsonToAbilityInfos(const cJSON *abilityArray, AbilityInfo **abilityInfos,
    uint32_t numOfAbility)
{
    if (abilityInfos == nullptr || !cJSON_IsArray(abilityArray) || numOfAbility == 0 ||
        static_cast<uint32_t>(cJSON_GetArraySize(abilityArray)) != numOfAbility) {
        return false;
    }

    *abilityInfos = reinterpret_cast<AbilityInfo*>(AdapterMalloc(sizeof(AbilityInfo) * numOfAbility));
    if (*abilityInfos == nullptr) {
        return false;
    }

    int32_t ret = memset_s(*abilityInfos, sizeof(AbilityInfo) * numOfAbility, 0,
        sizeof(AbilityInfo) * numOfAbility);
    if (ret != EOK) {
        AdapterFree(*abilityInfos);
        *abilityInfos = nullptr;
        return false;
    }

    cJSON *arrayItem = nullptr;
    uint32_t index = 0;
    cJSON_ArrayForEach(arrayItem, abilityArray) {
        if (!ConvertJsonToAbilityInfo(arrayItem, *abilityInfos + index)) {
            return false;
        }
        ++index;
    }
    return true;
}
} // OHOS