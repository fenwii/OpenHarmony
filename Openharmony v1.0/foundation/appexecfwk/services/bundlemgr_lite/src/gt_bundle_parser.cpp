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

#include "gt_bundle_parser.h"

#include "ability_info_utils.h"
#include "appexecfwk_errors.h"
#include "bundle_info_utils.h"
#include "bundle_util.h"
#include "global.h"
#include "gt_bundle_extractor.h"
#include "module_info_utils.h"
#include "securec.h"
#include "utils.h"

namespace OHOS {
const int32_t BASE_API_VERSION = 3;

int32_t GtBundleParser::ParseValue(const cJSON *object, const char *key, int32_t defaultValue)
{
    if (object == nullptr) {
        return defaultValue;
    }

    cJSON *son = nullptr;
    son = cJSON_GetObjectItem(object, key);
    if (!cJSON_IsNumber(son)) {
        return defaultValue;
    }
    return son->valueint;
}

char *GtBundleParser::ParseValue(const cJSON *object, const char *key)
{
    if (object == nullptr) {
        return nullptr;
    }

    cJSON *son = nullptr;
    son = cJSON_GetObjectItem(object, key);
    if (!cJSON_IsString(son)) {
        return nullptr;
    }
    return son->valuestring;
}

cJSON *GtBundleParser::ParseValue(const cJSON *object, const char *key, cJSON *defaultValue)
{
    if (object == nullptr) {
        return defaultValue;
    }

    cJSON *son = nullptr;
    son = cJSON_GetObjectItem(object, key);
    if (son == nullptr) {
        return defaultValue;
    }

    if (cJSON_IsArray(son) || cJSON_IsObject(son)) {
        return son;
    }
    return defaultValue;
}

bool GtBundleParser::ParseBundleAttr(const char *path, char **bundleName, int32_t &versionCode)
{
    if (!BundleUtil::CheckRealPath(path)) {
        return false;
    }

    uint32_t totalFileSize = BundleUtil::GetFileSize(path);
    int32_t fp = open(path, O_RDONLY, S_IREAD);
    if (fp < 0) {
        return false;
    }

    char *profileStr = GtBundleExtractor::ExtractHapProfile(fp, totalFileSize);
    if (profileStr == nullptr) {
        close(fp);
        return false;
    }
    close(fp);

    cJSON *root = cJSON_Parse(profileStr);
    if (root == nullptr) {
        AdapterFree(profileStr);
        return false;
    }
    AdapterFree(profileStr);

    cJSON *appObject = cJSON_GetObjectItem(root, PROFILE_KEY_APP);
    if (appObject == nullptr) {
        cJSON_Delete(root);
        return false;
    }

    *bundleName = Utils::Strdup(ParseValue(appObject, PROFILE_KEY_BUNDLENAME));
    if (*bundleName == nullptr) {
        cJSON_Delete(root);
        return false;
    }

    cJSON *object = ParseValue(appObject, PROFILE_KEY_VERSION, nullptr);
    if (object == nullptr) {
        cJSON_Delete(root);
        return false;
    }

    versionCode = ParseValue(object, PROFILE_KEY_VERSION_CODE, -1);
    if (versionCode == -1) {
        cJSON_Delete(root);
        return false;
    }
    cJSON_Delete(root);
    return true;
}

BundleInfo *GtBundleParser::ParseHapProfile(const char *path)
{
    if (!BundleUtil::CheckRealPath(path)) {
        return nullptr;
    }

    char *profilePathComp[] = {
        const_cast<char *>(path), const_cast<char *>(PATH_SEPARATOR), const_cast<char *>(PROFILE_NAME)
    };
    char *profilePath = BundleUtil::Strscat(profilePathComp, sizeof(profilePathComp) / sizeof(char *));
    if (profilePath == nullptr) {
        return nullptr;
    }

    cJSON *root = BundleUtil::GetJsonStream(profilePath);
    if (root == nullptr) {
        AdapterFree(profilePath);
        return nullptr;
    }
    AdapterFree(profilePath);

    cJSON *appObject = cJSON_GetObjectItem(root, PROFILE_KEY_APP);
    cJSON *configObject = cJSON_GetObjectItem(root, PROFILE_KEY_DEVICECONFIG);
    cJSON *moduleObject = cJSON_GetObjectItem(root, PROFILE_KEY_MODULE);
    if (appObject == nullptr || moduleObject == nullptr) {
        cJSON_Delete(root);
        return nullptr;
    }

    BundleProfile bundleProfile;
    if (memset_s(&bundleProfile, sizeof(BundleProfile), 0, sizeof(BundleProfile)) != EOK) {
        cJSON_Delete(root);
        return nullptr;
    }

    BundleRes bundleRes;
    if (memset_s(&bundleRes, sizeof(BundleRes), 0, sizeof(BundleRes)) != EOK) {
        cJSON_Delete(root);
        return nullptr;
    }

    if (ParseJsonInfo(appObject, configObject, moduleObject, bundleProfile, bundleRes) != ERR_OK) {
        cJSON_Delete(root);
        FREE_BUNDLE_PROFILE(bundleProfile);
        FREE_BUNDLE_RES(bundleRes);
        return nullptr;
    }

    BundleInfo *bundleInfo = CreateBundleInfo(path, bundleProfile, bundleRes);
    FREE_BUNDLE_PROFILE(bundleProfile);
    FREE_BUNDLE_RES(bundleRes);
    cJSON_Delete(root);
    return bundleInfo;
}

uint8_t GtBundleParser::ParseJsonInfo(const cJSON *appObject, const cJSON *configObject, const cJSON *moduleObject,
    BundleProfile &bundleProfile, BundleRes &bundleRes)
{
    // parse app config
    bundleProfile.bundleName = ParseValue(appObject, PROFILE_KEY_BUNDLENAME);
    CHECK_NULL(bundleProfile.bundleName, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_BUNDLENAME_ERROR);
    CHECK_LENGTH(strlen(PROFILE_KEY_BUNDLENAME), MAX_BUNDLE_NAME_LEN,
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME_LENGTH);

    if (cJSON_HasObjectItem(appObject, PROFILE_KEY_VENDOR)) {
        bundleProfile.vendor = ParseValue(appObject, PROFILE_KEY_VENDOR);
        CHECK_NULL(bundleProfile.vendor, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VENDOR_ERROR);
    }

    cJSON *object = ParseValue(appObject, PROFILE_KEY_VERSION, nullptr);
    bundleProfile.profileVersion.versionName = ParseValue(object, PROFILE_KEY_VERSION_NAME);
    CHECK_NULL(bundleProfile.profileVersion.versionName, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONNAME_ERROR);
    CHECK_LENGTH(strlen(bundleProfile.profileVersion.versionName), MAX_VERSION_NAME_LEN,
        ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VERSIONNAME_LENGTH_ERROR);

    bundleProfile.profileVersion.versionCode = ParseValue(object, PROFILE_KEY_VERSION_CODE, -1);
    if (bundleProfile.profileVersion.versionCode == -1) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONCODE_ERROR;
    }
    // check apiVersion
    if (cJSON_HasObjectItem(appObject, PROFILE_KEY_APIVERSION)) {
        object = ParseValue(appObject, PROFILE_KEY_APIVERSION, nullptr);
        CHECK_NULL(object, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR);
        bundleProfile.profileApiVersion.minApiVersion = ParseValue(object, PROFILE_KEY_APIVERSION_COMPATIBLE, -1);
        CHECK_IS_TRUE((bundleProfile.profileApiVersion.minApiVersion >= 0),
            ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR);
        if (cJSON_HasObjectItem(object, PROFILE_KEY_APIVERSION_TARGET)) {
            bundleProfile.profileApiVersion.maxApiVersion = ParseValue(object, PROFILE_KEY_APIVERSION_TARGET, -1);
            CHECK_IS_TRUE(
                (bundleProfile.profileApiVersion.maxApiVersion >= bundleProfile.profileApiVersion.minApiVersion),
                ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR);
        }
    } else {
        // parse deviceConfig
        bundleProfile.profileApiVersion.minApiVersion = BASE_API_VERSION;
        bundleProfile.profileApiVersion.maxApiVersion = BASE_API_VERSION;
    }

    uint8_t errorCode = ParseModuleInfo(moduleObject, bundleProfile, bundleRes);
    return errorCode;
}

uint8_t GtBundleParser::ParseModuleInfo(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes)
{
    // parse deviceType
    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_MODULE_DEVICETYPE, nullptr);
    if (!CheckDeviceTypeIsValid(object)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR;
    }
    // parse distro
    object = ParseValue(moduleObject, PROFILE_KEY_MODULE_DISTRO, nullptr);
    CHECK_NULL(object, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_ERROR);
    cJSON *deliveryObject = cJSON_GetObjectItem(object, PROFILE_KEY_MODULE_DISTRO_DELIVERY);
    CHECK_NULL(deliveryObject, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_DELIVERY_ERROR);
    if (!cJSON_IsBool(deliveryObject)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_DELIVERY_ERROR;
    }

    bundleProfile.moduleInfo.moduleName = ParseValue(object, PROFILE_KEY_MODULE_DISTRO_MODULENAME);
    CHECK_NULL(bundleProfile.moduleInfo.moduleName, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULENAME_ERROR);
    if (strstr(bundleProfile.moduleInfo.moduleName, "../") != nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_MODULENAME;
    }
    // parse metaData
    uint8_t errorCode = ParseModuleMetaData(moduleObject, bundleProfile);
    if (errorCode != ERR_OK) {
        return errorCode;
    }

    char *moduleType = ParseValue(object, PROFILE_KEY_MODULE_DISTRO_MODULETYPE);
    CHECK_NULL(moduleType, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR);
    bool result = ((strcmp(moduleType, MODULE_ENTRY) == 0) || (strcmp(moduleType, MODULE_FEATURE) == 0));
    if (!result) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR;
    }
    // parse ability
    cJSON *abilityObjects = ParseValue(moduleObject, PROFILE_KEY_MODULE_ABILITIES, nullptr);
    CHECK_NULL(abilityObjects, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR);
    if (abilityObjects->type != cJSON_Array || cJSON_GetArraySize(abilityObjects) == 0) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR;
    }
    return ParseAbilityInfo(abilityObjects, bundleProfile, bundleRes);
}

uint8_t GtBundleParser::ParseAbilityInfo(const cJSON *abilityInfoObjects, BundleProfile &bundleProfile,
    BundleRes &bundleRes)
{
    cJSON *firstAbilityJson = cJSON_GetArrayItem(abilityInfoObjects, 0);
    bundleProfile.label = ParseValue(firstAbilityJson, PROFILE_KEY_MODULE_ABILITY_LABEL);
    CHECK_NULL(bundleProfile.label, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR);

    bundleRes.abilityRes = reinterpret_cast<AbilityRes *>(AdapterMalloc(sizeof(AbilityRes)));
    bundleRes.totalNumOfAbilityRes = 1;
    CHECK_NULL(bundleRes.abilityRes, ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR);
    if (memset_s(bundleRes.abilityRes, sizeof(AbilityRes), 0, sizeof(AbilityRes)) != EOK) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (BundleUtil::StartWith(bundleProfile.label, DEFAULT_LABEL_SETTING)) {
        int32_t labelId = ParseValue(firstAbilityJson, LABEL_ID, -1);
        if (labelId < 0) {
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR;
        }
        bundleRes.abilityRes->labelId = labelId;
    }
    CHECK_LENGTH(strlen(bundleProfile.label), MAX_LABLE_LEN,
        ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_LABEL_LENGTH_ERROR);

    bundleProfile.iconPath = ParseValue(firstAbilityJson, PROFILE_KEY_MODULE_ABILITY_ICON);
    CHECK_NULL(bundleProfile.iconPath, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR);
    if (strcmp(bundleProfile.iconPath, DEFAULT_ICON_SETTING) != 0) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR;
    }
    int32_t iconId = ParseValue(firstAbilityJson, ICON_ID, -1);
    if (iconId < 0) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR;
    }
    bundleRes.abilityRes->iconId = iconId;
    return ERR_OK;
}

bool GtBundleParser::CheckDeviceTypeIsValid(const cJSON *deviceTypeObject)
{
    if (!cJSON_IsArray(deviceTypeObject)) {
        return false;
    }

    cJSON *object = nullptr;
    cJSON_ArrayForEach(object, deviceTypeObject) {
        if (object->type != cJSON_String) {
            return false;
        }
        if ((object->valuestring != nullptr) && strcmp(object->valuestring, DEFAULT_DEVICE_TYPE) == 0) {
            return true;
        }
    }
    return false;
}

uint8_t GtBundleParser::ParseModuleMetaData(const cJSON *moduleObject, BundleProfile &bundleProfile)
{
    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_MODULE_METADATA, nullptr);
    if (object == nullptr || object->type == cJSON_NULL) {
        return ERR_OK;
    }

    object = cJSON_GetObjectItem(object, PROFILE_KEY_MODULE_METADATA_CUSTOMIZEDATA);
    if (object == nullptr || object->type == cJSON_NULL) {
        return ERR_OK;
    }
    int32_t size = cJSON_GetArraySize(object);
    if (object->type != cJSON_Array || size > METADATA_SIZE) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR;
    }
    cJSON *objectItem = nullptr;
    int32_t i = 0;
    cJSON_ArrayForEach(objectItem, object) {
        bundleProfile.moduleInfo.metaData[i] = reinterpret_cast<MetaData *>
            (AdapterMalloc(sizeof(MetaData)));
        if (bundleProfile.moduleInfo.metaData[i] == nullptr ||
            memset_s(bundleProfile.moduleInfo.metaData[i], sizeof(MetaData), 0, sizeof(MetaData)) != EOK) {
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR;
        }
        if (cJSON_HasObjectItem(objectItem, PROFILE_KEY_MODULE_METADATA_NAME)) {
            bundleProfile.moduleInfo.metaData[i]->name = ParseValue(objectItem, PROFILE_KEY_MODULE_METADATA_NAME);
            CHECK_NULL(bundleProfile.moduleInfo.metaData[i]->name,
                ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR);
            CHECK_LENGTH(strlen(bundleProfile.moduleInfo.metaData[i]->name), MAX_METADATA_NAME,
                ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_NAME_LENGTH_ERROR);
        }

        if (cJSON_HasObjectItem(objectItem, PROFILE_KEY_MODULE_METADATA_VALUE)) {
            bundleProfile.moduleInfo.metaData[i]->value = ParseValue(objectItem, PROFILE_KEY_MODULE_METADATA_VALUE);
            CHECK_NULL(bundleProfile.moduleInfo.metaData[i]->value,
                ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR);
            CHECK_LENGTH(strlen(bundleProfile.moduleInfo.metaData[i]->value), MAX_METADATA_VALUE,
                ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_VALUE_LENGTH_ERROR);
        }

        if (cJSON_HasObjectItem(objectItem, PROFILE_KEY_MODULE_METADATA_EXTRA)) {
            bundleProfile.moduleInfo.metaData[i]->extra = ParseValue(objectItem, PROFILE_KEY_MODULE_METADATA_EXTRA);
            CHECK_NULL(bundleProfile.moduleInfo.metaData[i]->extra,
                ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR);
        }
        i++;
    }
    return ERR_OK;
}

BundleInfo *GtBundleParser::CreateBundleInfo(const char *path, const BundleProfile &bundleProfile,
    const BundleRes &bundleRes)
{
    BundleInfo *bundleInfo = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo)));
    if (bundleInfo == nullptr) {
        return nullptr;
    }

    if (memset_s(bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo)) != EOK) {
        AdapterFree(bundleInfo);
        return nullptr;
    }
    if (!SetBundleInfo(bundleProfile, bundleRes, bundleInfo)) {
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        return nullptr;
    }

    uint8_t errorCode = ConvertResInfoToBundleInfo(path, bundleRes.abilityRes->labelId, bundleRes.abilityRes->iconId,
        bundleInfo);
    if (errorCode != ERR_OK) {
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        return nullptr;
    }
    // get js path
    char *jsPathComp[] = {bundleInfo->codePath, const_cast<char *>(ASSET_JS_PATH)};
    char *jsPath = BundleUtil::Strscat(jsPathComp, sizeof(jsPathComp) / sizeof(char *));
    if (jsPath == nullptr) {
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        return nullptr;
    }

    if (!BundleUtil::IsDir(jsPath)) {
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        AdapterFree(jsPath);
        return nullptr;
    }
    // set abilityInfo
    AbilityInfo abilityInfo = {.bundleName = bundleInfo->bundleName, .srcPath = jsPath};
    if (!BundleInfoUtils::SetBundleInfoAbilityInfo(bundleInfo, abilityInfo)) {
        AdapterFree(abilityInfo.srcPath);
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        return nullptr;
    }
    AdapterFree(abilityInfo.srcPath);
    return bundleInfo;
}

uint8_t GtBundleParser::ConvertResInfoToBundleInfo(const char *path, uint32_t labelId, uint32_t iconId,
    BundleInfo *bundleInfo)
{
    if (path == nullptr || bundleInfo == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    char *resPathComp[] = {
        const_cast<char *>(path), const_cast<char *>(ASSETS), bundleInfo->moduleInfos[0].moduleName,
        const_cast<char *>(PATH_SEPARATOR), const_cast<char *>(RESOURCES_INDEX)
    };
    char *resPath = BundleUtil::Strscat(resPathComp, sizeof(resPathComp) / sizeof(char *));
    if (resPath == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    if (!BundleUtil::IsFile(resPath)) {
        AdapterFree(resPath);
        return ERR_APPEXECFWK_INSTALL_FAILED_RESOURCE_INDEX_NOT_EXISTS;
    }
    if (labelId != 0) {
        char *label = nullptr;
        if (GLOBAL_GetValueById(labelId, resPath, &label) != 0) {
            AdapterFree(label);
            AdapterFree(resPath);
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_LABEL_RES_ERROR;
        }
        bundleInfo->label = Utils::Strdup(label);
        AdapterFree(label);
        if (bundleInfo->label == nullptr) {
            AdapterFree(resPath);
            return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
        }
    }
    if (!ConvertIconResToBundleInfo(resPath, iconId, bundleInfo)) {
        AdapterFree(resPath);
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ICON_RES_ERROR;
    }
    AdapterFree(resPath);
    return ERR_OK;
}

bool GtBundleParser::ConvertIconResToBundleInfo(const char *resPath, uint32_t iconId, BundleInfo *bundleInfo)
{
    if (resPath == nullptr || bundleInfo == nullptr || iconId == 0) {
        return false;
    }

    char *relativeIconPath = nullptr;
    if (GLOBAL_GetValueById(iconId, const_cast<char *>(resPath), &relativeIconPath) != 0) {
        return false;
    }
    // set relativeIconDir
    if (relativeIconPath == nullptr) {
        return false;
    }
    char *pos = relativeIconPath + strlen(relativeIconPath);
    for (; *pos != '/'; pos--) {};
    *pos = '\0';
    char *bigIconPathComp[] = {
        bundleInfo->codePath, const_cast<char *>(ASSETS), relativeIconPath, const_cast<char *>(PATH_SEPARATOR),
        const_cast<char *>(ICON_NAME)
    };
    char *smallIconPathComp[] = {
        bundleInfo->codePath, const_cast<char *>(ASSETS), relativeIconPath, const_cast<char *>(PATH_SEPARATOR),
        const_cast<char *>(SMALL_ICON_NAME)
    };
    bundleInfo->bigIconPath = BundleUtil::Strscat(bigIconPathComp, sizeof(bigIconPathComp) / sizeof(char *));
    bundleInfo->smallIconPath = BundleUtil::Strscat(smallIconPathComp, sizeof(smallIconPathComp) / sizeof(char *));
    if (bundleInfo->bigIconPath == nullptr || bundleInfo->smallIconPath == nullptr) {
        AdapterFree(relativeIconPath);
        return false;
    }
    AdapterFree(relativeIconPath);
    if (!BundleUtil::IsFile(bundleInfo->bigIconPath) || !BundleUtil::IsFile(bundleInfo->smallIconPath)) {
        return false;
    }
    return true;
}

uint8_t GtBundleParser::ParseHapProfile(int32_t fp, uint32_t fileSize, Permissions &permissions, BundleRes &bundleRes,
    BundleInfo **bundleInfo)
{
    char *profileStr = GtBundleExtractor::ExtractHapProfile(fp, fileSize);
    if (profileStr == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR;
    }

    cJSON *root = cJSON_Parse(profileStr);
    if (root == nullptr) {
        AdapterFree(profileStr);
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR;
    }
    AdapterFree(profileStr);

    cJSON *appObject = cJSON_GetObjectItem(root, PROFILE_KEY_APP);
    cJSON *configObject = cJSON_GetObjectItem(root, PROFILE_KEY_DEVICECONFIG);
    cJSON *moduleObject = cJSON_GetObjectItem(root, PROFILE_KEY_MODULE);
    if (appObject == nullptr || moduleObject == nullptr) {
        cJSON_Delete(root);
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR;
    }

    BundleProfile bundleProfile;
    if (memset_s(&bundleProfile, sizeof(BundleProfile), 0, sizeof(BundleProfile)) != EOK) {
        cJSON_Delete(root);
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }

    uint8_t errorCode = ParseJsonInfo(appObject, configObject, moduleObject, bundleProfile, bundleRes);
    CHECK_PARSE_RESULT(errorCode, root, bundleProfile, bundleRes);

    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_REQPERMISSIONS, nullptr);
    errorCode = ParsePermissions(object, permissions);
    CHECK_PARSE_RESULT(errorCode, root, bundleProfile, bundleRes);

    errorCode = SaveBundleInfo(bundleProfile, bundleRes, bundleInfo);
    CHECK_PARSE_RESULT(errorCode, root, bundleProfile, bundleRes);

    FREE_BUNDLE_PROFILE(bundleProfile);
    cJSON_Delete(root);
    return ERR_OK;
}

uint8_t GtBundleParser::SaveBundleInfo(const BundleProfile &bundleProfile, const BundleRes &bundleRes,
    BundleInfo **bundleInfo)
{
    *bundleInfo = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo)));
    if (*bundleInfo == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (memset_s(*bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo)) != EOK) {
        AdapterFree(*bundleInfo);
        *bundleInfo = nullptr;
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (!SetBundleInfo(bundleProfile, bundleRes, *bundleInfo)) {
        BundleInfoUtils::FreeBundleInfo(*bundleInfo);
        *bundleInfo = nullptr;
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    char *jsPathComp[] = {(*bundleInfo)->codePath, const_cast<char *>(ASSET_JS_PATH)};
    char *jsPath = BundleUtil::Strscat(jsPathComp, sizeof(jsPathComp) / sizeof(char *));
    if (jsPath == nullptr) {
        BundleInfoUtils::FreeBundleInfo(*bundleInfo);
        *bundleInfo = nullptr;
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    AbilityInfo abilityInfo = {.bundleName = (*bundleInfo)->bundleName, .srcPath = jsPath};
    // set abilityInfo
    if (!BundleInfoUtils::SetBundleInfoAbilityInfo(*bundleInfo, abilityInfo)) {
        AdapterFree(jsPath);
        BundleInfoUtils::FreeBundleInfo(*bundleInfo);
        *bundleInfo = nullptr;
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    AdapterFree(jsPath);
    return ERR_OK;
}

bool GtBundleParser::SetBundleInfo(const BundleProfile &bundleProfile, const BundleRes &bundleRes,
    BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr || bundleRes.abilityRes == nullptr) {
        return false;
    }

    bundleInfo->versionCode = bundleProfile.profileVersion.versionCode;
    bundleInfo->compatibleApi = bundleProfile.profileApiVersion.minApiVersion;
    bundleInfo->targetApi = bundleProfile.profileApiVersion.maxApiVersion;

    char *codePathComp[] = {
        const_cast<char *>(INSTALL_PATH), const_cast<char *>(PATH_SEPARATOR), bundleProfile.bundleName
    };

    char *dataPathComp[] = {
        const_cast<char *>(DATA_PATH), const_cast<char *>(PATH_SEPARATOR), bundleProfile.bundleName
    };

    bundleInfo->codePath = BundleUtil::Strscat(codePathComp, sizeof(codePathComp) / sizeof(char *));
    bundleInfo->dataPath = BundleUtil::Strscat(dataPathComp, sizeof(dataPathComp) / sizeof(char *));
    if (bundleInfo->codePath == nullptr || bundleInfo->dataPath == nullptr) {
        return false;
    }

    if (bundleProfile.vendor != nullptr && !BundleInfoUtils::SetBundleInfoVendor(bundleInfo, bundleProfile.vendor)) {
        return false;
    }

    if (bundleRes.abilityRes->labelId == 0 && bundleProfile.label != nullptr &&
        !BundleInfoUtils::SetBundleInfoLabel(bundleInfo, bundleProfile.label)) {
        return false;
    }

    if (!BundleInfoUtils::SetBundleInfoBundleName(bundleInfo, bundleProfile.bundleName) ||
        !BundleInfoUtils::SetBundleInfoVersionName(bundleInfo, bundleProfile.profileVersion.versionName) ||
        !SetModuleInfos(bundleProfile, bundleInfo)) {
        return false;
    }
    return true;
}

bool GtBundleParser::SetModuleInfos(const BundleProfile &bundleProfile, BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return false;
    }
    bundleInfo->moduleInfos = reinterpret_cast<ModuleInfo *>(AdapterMalloc(sizeof(ModuleInfo)));
    if (bundleInfo->moduleInfos == nullptr) {
        return false;
    }

    if (memset_s(bundleInfo->moduleInfos, sizeof(ModuleInfo), 0, sizeof(ModuleInfo)) != EOK) {
        AdapterFree(bundleInfo->moduleInfos);
        return false;
    }

    bundleInfo->numOfModule = 1;
    if (!ModuleInfoUtils::SetModuleInfoMetaData(bundleInfo->moduleInfos,
        const_cast<MetaData **>(bundleProfile.moduleInfo.metaData), METADATA_SIZE)) {
        return false;
    }
    if (!ModuleInfoUtils::SetModuleInfoModuleName(bundleInfo->moduleInfos, bundleProfile.moduleInfo.moduleName)) {
        return false;
    }
    return true;
}

uint8_t GtBundleParser::ParsePermissions(const cJSON *object, Permissions &permissions)
{
    if (object == nullptr) {
        return ERR_OK;
    }

    if (object->type != cJSON_Array) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PERMISSIONS_ERROR;
    }
    permissions.permNum = cJSON_GetArraySize(object);
    if (permissions.permNum == 0) {
        return ERR_OK;
    }

    permissions.permissionTrans = reinterpret_cast<PermissionTrans *>(AdapterMalloc(sizeof(PermissionTrans) *
        permissions.permNum));

    if (permissions.permissionTrans == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PERMISSIONS_ERROR;
    }

    PermissionTrans *perms = permissions.permissionTrans;
    cJSON *reqPermission = nullptr;
    cJSON_ArrayForEach(reqPermission, object) {
        if (!SetReqPermission(reqPermission, perms)) {
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PERMISSIONS_ERROR;
        }
        perms++;
    }
    return ERR_OK;
}

bool GtBundleParser::SetReqPermission(const cJSON *object, PermissionTrans *permission)
{
    if (object == nullptr || permission == nullptr) {
        return false;
    }

    char *name = ParseValue(object, PROFILE_KEY_REQPERMISSIONS_NAME);
    char *desc = ParseValue(object, PROFILE_KEY_REQPERMISSIONS_REASON);
    if (name == nullptr || desc == nullptr) {
        return false;
    }

    if (IsPermissionValid(name) != 0) {
        return false;
    }
    if (strncpy_s(permission->name, sizeof(permission->name), name, strlen(name)) != EOK ||
        strncpy_s(permission->desc, sizeof(permission->desc), desc, strlen(desc)) != EOK) {
        return false;
    }

    cJSON *usedSceneObject = ParseValue(object, PROFILE_KEY_REQPERMISSIONS_USEDSCENE, nullptr);
    char *when = ParseValue(usedSceneObject, PROFILE_KEY_REQPERMISSIONS_WHEN);
    if (when == nullptr) {
        return false;
    }
    if (strcmp(when, GRANTTIME_INUSE) == 0) {
        permission->when = INUSE;
    } else if (strcmp(when, GRANTTIME_ALWAYS) == 0) {
        permission->when = ALWAYS;
    } else {
        return false;
    }
    return true;
}
} // namespace OHOS