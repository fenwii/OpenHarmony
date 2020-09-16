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

#include "bundle_parser.h"

#include "appexecfwk_errors.h"
#include "bundle_extractor.h"
#include "bundle_info_creator.h"
#include "bundle_util.h"
#include "log.h"
#include "securec.h"
#include "utils.h"

#include <algorithm>
#include <map>
#include <regex>
#include <vector>

namespace OHOS {
const std::map<std::string, AbilityType> ABILITY_TYPE_MAP = {{"page", PAGE}, {"service", SERVICE}};
const std::map<std::string, LaunchMode> LAUNCH_MODE_MAP = {{"singleton", SINGLETON}, {"standard", STANDARD}};

int32_t BundleParser::ParseValue(const cJSON *object, const char *key, int32_t defaultValue)
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

char *BundleParser::ParseValue(const cJSON *object, const char *key)
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

cJSON *BundleParser::ParseValue(const cJSON *object, const char *key, cJSON *defaultValue)
{
    if (object == nullptr) {
        return defaultValue;
    }

    cJSON *son = nullptr;
    son = cJSON_GetObjectItem(object, key);
    if (cJSON_IsArray(son) || cJSON_IsObject(son)) {
        return son;
    }
    return defaultValue;
}

bool BundleParser::CheckBundleNameIsValid(const char *bundleName)
{
    if (bundleName == nullptr) {
        return false;
    }
    std::string pattern { "([a-zA-Z0-9]+\\.)+[a-zA-Z0-9]+" };
    std::regex re(pattern);
    try {
        if (!std::regex_match(bundleName, re)) {
            return false;
        }
    } catch (std::regex_error &message) {
        HILOG_ERROR(HILOG_MODULE_APP, "regex fail! message is %s", message.what());
        return false;
    } catch (std::out_of_range &message) {
        HILOG_ERROR(HILOG_MODULE_APP, "regex out_of_range fail! message is %s", message.what());
        return false;
    } catch (std::runtime_error &message) {
        HILOG_ERROR(HILOG_MODULE_APP, "regex runtime_error fail! message is %s", message.what());
        return false;
    }
    return true;
}

uint8_t BundleParser::ParsePermissions(const cJSON *object, Permissions &permissions)
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
        HILOG_ERROR(HILOG_MODULE_APP, "malloc permissionTrans fail!");
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

bool BundleParser::SetReqPermission(const cJSON *object, PermissionTrans *permission)
{
    if ((object == nullptr) || (permission == nullptr)) {
        return false;
    }

    char *name = ParseValue(object, PROFILE_KEY_REQPERMISSIONS_NAME);
    char *desc = ParseValue(object, PROFILE_KEY_REQPERMISSIONS_REASON);
    if (name == nullptr || desc == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "the value of name or desc is invalid!");
        return false;
    }

    if (IsPermissionValid(name) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "reqpermission is invalid!");
        return false;
    }

    if (strncpy_s(permission->name, sizeof(permission->name), name, strlen(name)) != EOK ||
        strncpy_s(permission->desc, sizeof(permission->desc), desc, strlen(desc)) != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "SetReqPermission  strncpy name or desc fail!");
        return false;
    }

    cJSON *usedSceneObject = ParseValue(object, PROFILE_KEY_REQPERMISSIONS_USEDSCENE, nullptr);
    char *when = ParseValue(usedSceneObject, PROFILE_KEY_REQPERMISSIONS_WHEN);
    if (when == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "the value of when is invalid!");
        return false;
    }
    if (strcmp(when, GRANTTIME_INUSE) == 0) {
        permission->when = INUSE;
    } else if (strcmp(when, GRANTTIME_ALWAYS) == 0) {
        permission->when = ALWAYS;
    } else {
        HILOG_ERROR(HILOG_MODULE_APP, "the type of when is invalid!");
        return false;
    }
    return true;
}

int8_t BundleParser::ParseBundleParam(const char *path, char **bundleName, int32_t &versionCode)
{
    if (!BundleUtil::CheckRealPath(path)) {
        return PROFILE_INVALID;
    }
    std::ostringstream profileStream;
    if (BundleExtractor::ExtractHapProfile(path, profileStream) != ERR_OK) {
        return PROFILE_INVALID;
    }
    cJSON *root = cJSON_Parse(profileStream.str().c_str());
    if (root == nullptr) {
        return PROFILE_INVALID;
    }

    cJSON *appObject = cJSON_GetObjectItem(root, PROFILE_KEY_APP);
    if (appObject == nullptr) {
        cJSON_Delete(root);
        return PROFILE_INVALID;
    }

    *bundleName = Utils::Strdup(ParseValue(appObject, PROFILE_KEY_BUNDLENAME));
    if (*bundleName == nullptr) {
        cJSON_Delete(root);
        return BUNDLENAME_INVALID;
    }

    cJSON *object = ParseValue(appObject, PROFILE_KEY_VERSION, nullptr);
    if (object == nullptr) {
        cJSON_Delete(root);
        return VERSION_CODE_INVALID;
    }

    versionCode = ParseValue(object, PROFILE_KEY_VERSION_CODE, -1);
    if (versionCode == -1) {
        cJSON_Delete(root);
        return VERSION_CODE_INVALID;
    }
    cJSON_Delete(root);
    return 0;
}

BundleInfo *BundleParser::ParseHapProfile(const char *path)
{
    if (!BundleUtil::CheckRealPath(path)) {
        return nullptr;
    }

    std::string profilePath = path + std::string(PATH_SEPARATOR) + PROFILE_NAME;
    cJSON *root = BundleUtil::GetJsonStream(profilePath.c_str());
    if (root == nullptr) {
        return nullptr;
    }

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

    BundleRes bundleRes = {.moduleDescriptionId = 0, .abilityRes = nullptr, .totalNumOfAbilityRes = 0};
    if (ParseJsonInfo(appObject, configObject, moduleObject, bundleProfile, bundleRes) != ERR_OK) {
        FREE_BUNDLE_PROFILE(bundleProfile);
        AdapterFree(bundleRes.abilityRes);
        cJSON_Delete(root);
        return nullptr;
    }
    std::string installDirPath;
    std::string dataDirPath;
    if (BundleUtil::StartWith(path, INSTALL_PATH)) {
        installDirPath = INSTALL_PATH;
        dataDirPath = DATA_PATH;
    } else {
        installDirPath = EXTEANAL_INSTALL_PATH;
        dataDirPath = EXTEANAL_DATA_PATH;
    }
    BundleInfo *bundleInfo = BundleInfoCreator::CreateBundleInfo(bundleProfile, installDirPath, dataDirPath,
        bundleRes);
    FREE_BUNDLE_PROFILE(bundleProfile);
    AdapterFree(bundleRes.abilityRes);
    cJSON_Delete(root);
    return bundleInfo;
}

uint8_t BundleParser::ParseHapProfile(const std::string &path, Permissions &permissions, BundleRes &bundleRes,
    BundleInfo **bundleInfo)
{
    std::ostringstream profileStream;
    uint8_t errorCode = BundleExtractor::ExtractHapProfile(path, profileStream);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);

    cJSON *root = cJSON_Parse(profileStream.str().c_str());
    CHECK_IS_TRUE((root != nullptr), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR);

    cJSON *appObject = cJSON_GetObjectItem(root, PROFILE_KEY_APP);
    cJSON *configObject = cJSON_GetObjectItem(root, PROFILE_KEY_DEVICECONFIG);
    cJSON *moduleObject = cJSON_GetObjectItem(root, PROFILE_KEY_MODULE);
    if (appObject == nullptr || moduleObject == nullptr) {
        cJSON_Delete(root);
        HILOG_ERROR(HILOG_MODULE_APP, "json file format is invalid!");
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR;
    }

    BundleProfile bundleProfile;
    if (memset_s(&bundleProfile, sizeof(BundleProfile), 0, sizeof(BundleProfile)) != EOK) {
        cJSON_Delete(root);
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }

    errorCode = ParseJsonInfo(appObject, configObject, moduleObject, bundleProfile, bundleRes);
    CHECK_PARSE_RESULT(errorCode, root, bundleProfile);

    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_REQPERMISSIONS, nullptr);
    errorCode = ParsePermissions(object, permissions);
    CHECK_PARSE_RESULT(errorCode, root, bundleProfile);

    errorCode = BundleInfoCreator::SaveBundleInfo(bundleProfile, bundleInfo);
    CHECK_PARSE_RESULT(errorCode, root, bundleProfile);

    FREE_BUNDLE_PROFILE(bundleProfile);
    cJSON_Delete(root);
    return ERR_OK;
}

uint8_t BundleParser::ParseJsonInfo(const cJSON *appObject, const cJSON *configObject, const cJSON *moduleObject,
    BundleProfile &bundleProfile, BundleRes &bundleRes)
{
    // parse app config
    bundleProfile.bundleName = ParseValue(appObject, PROFILE_KEY_BUNDLENAME);
    CHECK_NULL(bundleProfile.bundleName, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_BUNDLENAME_ERROR);
    CHECK_IS_TRUE((strlen(bundleProfile.bundleName) >= MIN_BUNDLE_NAME_LEN) &&
        (strlen(bundleProfile.bundleName) <= MAX_BUNDLE_NAME_LEN),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME_LENGTH);
    // check bundleName
    CHECK_IS_TRUE(CheckBundleNameIsValid(bundleProfile.bundleName),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME);

    if (cJSON_HasObjectItem(appObject, PROFILE_KEY_VENDOR)) {
        bundleProfile.vendor = ParseValue(appObject, PROFILE_KEY_VENDOR);
        CHECK_NULL(bundleProfile.vendor, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VENDOR_ERROR);
        CHECK_LENGTH(strlen(bundleProfile.vendor), MAX_VENDOR_LEN,
            ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VENDOR_LENGTH_ERROR);
    }
    // check version and versionName
    cJSON *object = ParseValue(appObject, PROFILE_KEY_VERSION, nullptr);
    bundleProfile.profileVersion.versionName = ParseValue(object, PROFILE_KEY_VERSION_NAME);
    CHECK_NULL(bundleProfile.profileVersion.versionName, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONNAME_ERROR);
    CHECK_LENGTH(strlen(bundleProfile.profileVersion.versionName), MAX_VERSION_NAME_LEN,
        ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VERSIONNAME_LENGTH_ERROR);

    bundleProfile.profileVersion.versionCode = ParseValue(object, PROFILE_KEY_VERSION_CODE, -1);
    CHECK_IS_TRUE((bundleProfile.profileVersion.versionCode >= 0),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONCODE_ERROR);
    // check apiVersion
    object = ParseValue(appObject, PROFILE_KEY_APIVERSION, nullptr);
    CHECK_NULL(object, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR);
    bundleProfile.profileApiVersion.minApiVersion = ParseValue(object, PROFILE_KEY_APIVERSION_COMPATIBLE, -1);
    CHECK_IS_TRUE((bundleProfile.profileApiVersion.minApiVersion >= 0),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR);
    if (cJSON_HasObjectItem(object, PROFILE_KEY_APIVERSION_TARGET)) {
        bundleProfile.profileApiVersion.maxApiVersion = ParseValue(object, PROFILE_KEY_APIVERSION_TARGET, -1);
        CHECK_IS_TRUE((bundleProfile.profileApiVersion.maxApiVersion >= bundleProfile.profileApiVersion.minApiVersion),
            ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR);
    }
    // parse deviceConfig
    uint8_t errorCode = ParseDeviceConfig(configObject, bundleProfile);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);
    // parse moduleInfo
    return ParseModuleInfo(moduleObject, bundleProfile, bundleRes);
}

uint8_t BundleParser::ParseDeviceConfig(const cJSON *configObject, BundleProfile &bundleProfile)
{
    if (configObject == nullptr || configObject->type == cJSON_NULL) {
        bundleProfile.isKeepAlive = false;
        return ERR_OK;
    }
    CHECK_IS_TRUE(cJSON_IsObject(configObject), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICE_CONFIG_ERROR);

    cJSON *defaultObject = nullptr;
    cJSON *smartVisionObject = nullptr;
    if (cJSON_HasObjectItem(configObject, PROFILE_KEY_DEVICECONFIG_DEFAULT)) {
        defaultObject = ParseValue(configObject, PROFILE_KEY_DEVICECONFIG_DEFAULT, nullptr);
        CHECK_IS_TRUE(cJSON_IsObject(defaultObject), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICE_CONFIG_ERROR);
    }
    if (cJSON_HasObjectItem(configObject, DEFAULT_DEVICE_TYPE)) {
        smartVisionObject = ParseValue(configObject, DEFAULT_DEVICE_TYPE, nullptr);
        CHECK_IS_TRUE(cJSON_IsObject(smartVisionObject), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICE_CONFIG_ERROR);
    }

    cJSON *object = nullptr;
    if (cJSON_HasObjectItem(defaultObject, PROFILE_KEY_KEEPALIVE)) {
        object = cJSON_GetObjectItem(defaultObject, PROFILE_KEY_KEEPALIVE);
    }

    if (cJSON_HasObjectItem(smartVisionObject, PROFILE_KEY_KEEPALIVE)) {
        object = cJSON_GetObjectItem(smartVisionObject, PROFILE_KEY_KEEPALIVE);
    }

    if (object != nullptr && !cJSON_IsBool(object)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_KEEPALIVE_ERROR;
    }
    bundleProfile.isKeepAlive = (object == nullptr) ? false : cJSON_IsTrue(object);
    return ERR_OK;
}

uint8_t BundleParser::ParseModuleInfo(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes)
{
    // parse module name
    if (cJSON_HasObjectItem(moduleObject, PROFILE_KEY_MODULE_NAME)) {
        bundleProfile.moduleInfo.name = ParseValue(moduleObject, PROFILE_KEY_MODULE_NAME);
        CHECK_NULL(bundleProfile.moduleInfo.name, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULENAME_ERROR);
        CHECK_LENGTH(strlen(bundleProfile.moduleInfo.name), MAX_NAME_LEN,
            ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULENAME_ERROR);
    }
    // parse module description
    uint8_t errorCode = ParseModuleDesc(moduleObject, bundleProfile, bundleRes);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);
    // parse deviceType
    errorCode = ParseDeviceType(moduleObject, bundleProfile);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);
    // parse distro
    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_MODULE_DISTRO, nullptr);
    CHECK_NULL(object, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_ERROR);
    cJSON *deliveryObject = cJSON_GetObjectItem(object, PROFILE_KEY_MODULE_DISTRO_DELIVERY);
    CHECK_IS_TRUE(cJSON_IsBool(deliveryObject), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_DELIVERY_ERROR);
    bundleProfile.moduleInfo.isDeliveryInstall = cJSON_IsTrue(deliveryObject);

    bundleProfile.moduleInfo.moduleName = ParseValue(object, PROFILE_KEY_MODULE_DISTRO_MODULENAME);
    CHECK_NULL(bundleProfile.moduleInfo.moduleName, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULENAME_ERROR);
    CHECK_LENGTH(strlen(bundleProfile.moduleInfo.moduleName), MAX_MODULENAME_LEN,
        ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_MODULENAME_LENGTH_ERROR);
    CHECK_IS_TRUE((strstr(bundleProfile.moduleInfo.moduleName, "../") == nullptr),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_MODULENAME);

    bundleProfile.moduleInfo.moduleType = ParseValue(object, PROFILE_KEY_MODULE_DISTRO_MODULETYPE);
    CHECK_NULL(bundleProfile.moduleInfo.moduleType, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR);
    bool result = ((strcmp(bundleProfile.moduleInfo.moduleType, MODULE_ENTRY) == 0) ||
        (strcmp(bundleProfile.moduleInfo.moduleType, MODULE_FEATURE) == 0));
    CHECK_IS_TRUE(result, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR);
    // parse metaData
    errorCode = ParseModuleMetaData(moduleObject, bundleProfile);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);
    // parse js config, if object is null or [], it means nativeApp, otherwise is js app
    object = ParseValue(moduleObject, PROFILE_KEY_JS, nullptr);
    bundleProfile.isNativeApp = ((object == nullptr) || (cJSON_IsArray(object) && cJSON_GetArraySize(object) == 0));
    // parse abilityInfo
    return ParseAbilityInfos(moduleObject, bundleProfile, bundleRes);
}

uint8_t BundleParser::ParseModuleDesc(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes)
{
    if (!cJSON_HasObjectItem(moduleObject, PROFILE_KEY_MODULE_DESCRIPTION)) {
        return ERR_OK;
    }
    bundleProfile.moduleInfo.description = ParseValue(moduleObject, PROFILE_KEY_MODULE_DESCRIPTION);
    CHECK_NULL(bundleProfile.moduleInfo.description, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULE_DESCRIPTION_ERROR);
    if (BundleUtil::StartWith(bundleProfile.moduleInfo.description, DEFAULT_DESC_SETTING)) {
        int32_t descId = ParseValue(moduleObject, MODULE_DES_ID, -1);
        if (descId < 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "get module descriptionId fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULE_DESCRIPTION_ERROR;
        }
        bundleRes.moduleDescriptionId = static_cast<uint32_t>(descId);
    } else {
        CHECK_LENGTH(strlen(bundleProfile.moduleInfo.description), MAX_DECRIPTION_LEN,
            ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULE_DESCRIPTION_ERROR);
    }
    return ERR_OK;
}

uint8_t BundleParser::ParseDeviceType(const cJSON *moduleObject, BundleProfile &bundleProfile)
{
    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_MODULE_DEVICETYPE, nullptr);
    CHECK_IS_TRUE((cJSON_IsArray(object) && (cJSON_GetArraySize(object) <= DEVICE_TYPE_SIZE)),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR);

    bool isMatched = false;
    cJSON *item = nullptr;
    int32_t i = 0;
    cJSON_ArrayForEach(item, object) {
        CHECK_IS_TRUE((item->type == cJSON_String), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR);
        if (item->valuestring != nullptr && strcmp(item->valuestring, DEFAULT_DEVICE_TYPE) == 0) {
            isMatched = true;
        }
        bundleProfile.moduleInfo.deviceType[i++] = item->valuestring;
    }
    CHECK_IS_TRUE(isMatched, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR);
    return ERR_OK;
}

uint8_t BundleParser::ParseModuleMetaData(const cJSON *moduleObject, BundleProfile &bundleProfile)
{
    cJSON *object = ParseValue(moduleObject, PROFILE_KEY_MODULE_METADATA, nullptr);
    // if no metadata, return ERR_OK
    if (object == nullptr || object->type == cJSON_NULL) {
        return ERR_OK;
    }

    object = cJSON_GetObjectItem(object, PROFILE_KEY_MODULE_METADATA_CUSTOMIZEDATA);
    if (object == nullptr || object->type == cJSON_NULL) {
        return ERR_OK;
    }
    CHECK_IS_TRUE((cJSON_IsArray(object) && (cJSON_GetArraySize(object) <= METADATA_SIZE)),
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR);

    cJSON *objectItem = nullptr;
    int32_t i = 0;
    cJSON_ArrayForEach(objectItem, object) {
        bundleProfile.moduleInfo.metaData[i] = reinterpret_cast<MetaData *>
            (AdapterMalloc(sizeof(MetaData)));
        if (bundleProfile.moduleInfo.metaData[i] == nullptr ||
            memset_s(bundleProfile.moduleInfo.metaData[i], sizeof(MetaData), 0, sizeof(MetaData)) != EOK) {
            HILOG_ERROR(HILOG_MODULE_APP, "malloc metaData fail!");
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

uint8_t BundleParser::ParseAbilityInfos(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes)
{
    cJSON *abilityObjects = ParseValue(moduleObject, PROFILE_KEY_MODULE_ABILITIES, nullptr);
    CHECK_IS_TRUE(cJSON_IsArray(abilityObjects), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR);
    if (cJSON_GetArraySize(abilityObjects) == 0) {
        bundleProfile.numOfAbility = 0;
        return ERR_OK;
    }
    // label can be null
    cJSON *firstAbilityJson = cJSON_GetArrayItem(abilityObjects, 0);
    if (cJSON_HasObjectItem(firstAbilityJson, PROFILE_KEY_MODULE_ABILITY_LABEL)) {
        bundleProfile.label = ParseValue(firstAbilityJson, PROFILE_KEY_MODULE_ABILITY_LABEL);
        CHECK_NULL(bundleProfile.label, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR);
        CHECK_LENGTH(strlen(bundleProfile.label), MAX_LABLE_LEN,
            ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_LABEL_LENGTH_ERROR);
    }
    // iconPath can be null
    if (cJSON_HasObjectItem(firstAbilityJson, PROFILE_KEY_MODULE_ABILITY_ICON)) {
        bundleProfile.iconPath = ParseValue(firstAbilityJson, PROFILE_KEY_MODULE_ABILITY_ICON);
        CHECK_NULL(bundleProfile.iconPath, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR);
    }
    // parse every ability
    return ParseAllAbilityInfo(abilityObjects, bundleProfile, bundleRes);
}

uint8_t BundleParser::ParseAllAbilityInfo(const cJSON *abilityObjects, BundleProfile &bundleProfile,
    BundleRes &bundleRes)
{
    bundleProfile.numOfAbility = cJSON_GetArraySize(abilityObjects);
    bundleRes.totalNumOfAbilityRes = bundleProfile.numOfAbility;
    if (bundleProfile.numOfAbility == 0) {
        return ERR_OK;
    }

    bundleRes.abilityRes = reinterpret_cast<AbilityRes *>(AdapterMalloc(sizeof(AbilityRes) *
        bundleProfile.numOfAbility));
    if (bundleRes.abilityRes == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "abilityRes malloc fail!");
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR;
    }
    int32_t ret = memset_s(bundleRes.abilityRes, sizeof(AbilityRes) * bundleProfile.numOfAbility, 0,
        sizeof(AbilityRes) * bundleProfile.numOfAbility);
    if (ret != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "abilityRes memset fail!");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }

    bundleProfile.abilityInfos = reinterpret_cast<AbilityInfo *>(AdapterMalloc(sizeof(AbilityInfo) *
        bundleProfile.numOfAbility));
    if (bundleProfile.abilityInfos == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "abilityInfos malloc fail!");
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR;
    }

    ret = memset_s(bundleProfile.abilityInfos, sizeof(AbilityInfo) * bundleProfile.numOfAbility, 0,
        sizeof(AbilityInfo) * bundleProfile.numOfAbility);
    if (ret != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "abilityInfos memset fail!");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }

    cJSON *object = nullptr;
    int32_t i = 0;
    cJSON_ArrayForEach(object, abilityObjects) {
        bundleProfile.abilityInfos[i].moduleName = bundleProfile.moduleInfo.moduleName;
        bundleProfile.abilityInfos[i].bundleName = bundleProfile.bundleName;
        uint8_t errorCode = ParsePerAbilityInfo(object, bundleProfile, bundleRes.abilityRes[i], i);
        CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);
        i++;
    }
    return ERR_OK;
}

uint8_t BundleParser::ParsePerAbilityInfo(const cJSON *abilityObjectItem, BundleProfile &bundleProfile,
    AbilityRes &abilityRes, uint32_t index)
{
    bundleProfile.abilityInfos[index].name = ParseValue(abilityObjectItem, PROFILE_KEY_MODULE_ABILITY_NAME);
    CHECK_NULL(bundleProfile.abilityInfos[index].name, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_NAME_ERROR);
    CHECK_LENGTH(strlen(bundleProfile.abilityInfos[index].name), MAX_ABILITY_NAME_LEN,
        ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITYNAME_LENGTH_ERROR);

    uint8_t errorCode = ParseAbilityDesc(abilityObjectItem, bundleProfile, abilityRes, index);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);

    errorCode = ParseAbilityIcon(abilityObjectItem, bundleProfile, abilityRes, index);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);

    errorCode = ParseAbilityLabel(abilityObjectItem, bundleProfile, abilityRes, index);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);

    errorCode = ParseAbilityType(abilityObjectItem, bundleProfile.abilityInfos[index]);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);

    errorCode = ParseAbilityLauchMode(abilityObjectItem, bundleProfile.abilityInfos[index]);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);

    errorCode = ParseAbilityVisible(abilityObjectItem, bundleProfile.abilityInfos[index]);
    CHECK_IS_TRUE((errorCode == ERR_OK), errorCode);
    return ERR_OK;
}

uint8_t BundleParser::ParseAbilityDesc(const cJSON *abilityObject, BundleProfile &bundleProfile,
    AbilityRes &abilityRes, int32_t index)
{
    if (!cJSON_HasObjectItem(abilityObject, PROFILE_KEY_MODULE_ABLLITY_DESCRIPTION)) {
        return ERR_OK;
    }
    bundleProfile.abilityInfos[index].description = ParseValue(abilityObject,
        PROFILE_KEY_MODULE_ABLLITY_DESCRIPTION);
    CHECK_NULL(bundleProfile.abilityInfos[index].description,
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_DESCRIPTION_ERROR);
    if (BundleUtil::StartWith(bundleProfile.abilityInfos[index].description, DEFAULT_DESC_SETTING)) {
        int32_t descId = ParseValue(abilityObject, ABILITY_DES_ID, -1);
        if (descId < 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "get ability descriptionId fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_DESCRIPTION_ERROR;
        }
        abilityRes.index = index;
        abilityRes.descriptionId = static_cast<uint32_t>(descId);
    } else {
        CHECK_LENGTH(strlen(bundleProfile.abilityInfos[index].description), MAX_DECRIPTION_LEN,
            ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_DESCRIPTION_LENGTH_ERROR);
    }
    return ERR_OK;
}

uint8_t BundleParser::ParseAbilityIcon(const cJSON *abilityObject, BundleProfile &bundleProfile,
    AbilityRes &abilityRes, int32_t index)
{
    if (!cJSON_HasObjectItem(abilityObject, PROFILE_KEY_MODULE_ABILITY_ICON)) {
        return ERR_OK;
    }
    bundleProfile.abilityInfos[index].iconPath = ParseValue(abilityObject, PROFILE_KEY_MODULE_ABILITY_ICON);
    CHECK_NULL(bundleProfile.abilityInfos[index].iconPath,
        ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR);
    if (BundleUtil::StartWith(bundleProfile.abilityInfos[index].iconPath, DEFAULT_ICON_SETTING_BEGIN)) {
        int32_t iconId = ParseValue(abilityObject, ICON_ID, -1);
        if (iconId < 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "get ability iconId fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR;
        }
        abilityRes.index = index;
        abilityRes.iconId = static_cast<uint32_t>(iconId);
    }
    return ERR_OK;
}

uint8_t BundleParser::ParseAbilityLabel(const cJSON *abilityObject, BundleProfile &bundleProfile,
    AbilityRes &abilityRes, int32_t index)
{
    if (!cJSON_HasObjectItem(abilityObject, PROFILE_KEY_MODULE_ABILITY_LABEL)) {
        return ERR_OK;
    }
    bundleProfile.abilityInfos[index].label = ParseValue(abilityObject, PROFILE_KEY_MODULE_ABILITY_LABEL);
    CHECK_NULL(bundleProfile.abilityInfos[index].label, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR);
    if (BundleUtil::StartWith(bundleProfile.abilityInfos[index].label, DEFAULT_LABEL_SETTING)) {
        int32_t labelId = ParseValue(abilityObject, LABEL_ID, -1);
        if (labelId < 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "get ability labelId fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR;
        }
        abilityRes.index = index;
        abilityRes.labelId = static_cast<uint32_t>(labelId);
    } else {
        CHECK_LENGTH(strlen(bundleProfile.abilityInfos[index].label), MAX_LABLE_LEN,
            ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_LABEL_LENGTH_ERROR);
    }
    return ERR_OK;
}

uint8_t BundleParser::ParseAbilityType(const cJSON *abilityObjectItem, AbilityInfo &abilityInfo)
{
    char *abilityType = ParseValue(abilityObjectItem, PROFILE_KEY_MODULE_ABILITY_TYPE);
    CHECK_NULL(abilityType, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_TYPE_ERROR);
    auto iter = std::find_if(std::begin(ABILITY_TYPE_MAP), std::end(ABILITY_TYPE_MAP),
        [&abilityType] (const auto &item) {
            return item.first == std::string(abilityType);
    });
    if (iter != ABILITY_TYPE_MAP.end()) {
        abilityInfo.abilityType = iter->second;
        return ERR_OK;
    }
    abilityInfo.abilityType = UNKNOWN;
    return ERR_OK;
}

uint8_t BundleParser::ParseAbilityLauchMode(const cJSON *abilityObjectItem, AbilityInfo &abilityInfo)
{
    if (cJSON_HasObjectItem(abilityObjectItem, PROFILE_KEY_MODULE_ABILITY_LAUNCHTYPE)) {
        char *launchMode = ParseValue(abilityObjectItem, PROFILE_KEY_MODULE_ABILITY_LAUNCHTYPE);
        CHECK_NULL(launchMode, ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LAUNCHTYPE_ERROR);
        auto iter = std::find_if(std::begin(LAUNCH_MODE_MAP), std::end(LAUNCH_MODE_MAP),
            [&launchMode] (const auto &item) {
            return item.first == std::string(launchMode);
        });
        if (iter != LAUNCH_MODE_MAP.end()) {
            abilityInfo.launchMode = iter->second;
        }
        abilityInfo.launchMode = SINGLETON;
        return ERR_OK;
    }
    abilityInfo.launchMode = SINGLETON;
    return ERR_OK;
}

uint8_t BundleParser::ParseAbilityVisible(const cJSON *abilityObjectItem, AbilityInfo &abilityInfo)
{
    if (cJSON_HasObjectItem(abilityObjectItem, PROFILE_KEY_MODULE_ABILITY_VISIBLE)) {
        cJSON *visibleObject = cJSON_GetObjectItem(abilityObjectItem, PROFILE_KEY_MODULE_ABILITY_VISIBLE);
        CHECK_IS_TRUE(cJSON_IsBool(visibleObject), ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_VISIBLE_ERROR);
        abilityInfo.isVisible = cJSON_IsTrue(visibleObject);
    } else {
        abilityInfo.isVisible = false;
    }
    return ERR_OK;
}
} // namespace OHOS