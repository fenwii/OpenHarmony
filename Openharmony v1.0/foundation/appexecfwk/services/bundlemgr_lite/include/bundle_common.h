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

#ifndef OHOS_BUNDLE_COMMON_H
#define OHOS_BUNDLE_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
#include "pms.h"
#ifdef __cplusplus
}
#endif

#include "ability_info.h"
#include "module_info.h"
#include "stdint.h"

namespace OHOS {
const char PROFILE_NAME[] = "config.json";
const char JSON_SUFFIX[] = ".json";
const char PATH_SEPARATOR[] = "/";
const char FILE_DELIMITER[] = "_";
const char TMP_SUFFIX[] = "_tmp";
const char EMPTY_STRING[] = "";
const char MODULE_ENTRY[] = "entry";
const char MODULE_FEATURE[] = "feature";
const uint16_t PATH_LENGTH = 256;
const uint8_t ICON_NUM = 2;
const uint16_t MAX_METADATA_NAME = 255;
const uint16_t MAX_METADATA_VALUE = 255;
const uint16_t MAX_NAME_LEN = 255;
const uint16_t MAX_DECRIPTION_LEN = 255;
const uint16_t MAX_VENDOR_LEN = 255;
const uint8_t MAX_MODULENAME_LEN = 31;
const uint8_t MAX_ABILITY_NAME_LEN = 127;
const int8_t PROFILE_INVALID = -1;
const int8_t BUNDLENAME_INVALID = -2;
const int8_t VERSION_CODE_INVALID = -3;
const uint8_t NUMBER_TEN = 10;
const uint8_t ZERO_ASCII_NUM = 48;
const uint8_t NUMBER_TWO = 2;
// bundle type
const uint8_t SYSTEM_APP_FLAG = 0;
const uint8_t THIRD_SYSTEM_APP_FLAG = 1;
const uint8_t THIRD_APP_FLAG = 2;

const char LABEL_ID[] = "labelId";
const char ICON_ID[] = "iconId";
const char MODULE_DES_ID[] = "descriptionId";
const char ABILITY_DES_ID[] = "descriptionId";
const char RESOURCES_INDEX[] = "resources.index";
const char DEFAULT_LABEL_SETTING[] = "$string:";
const char DEFAULT_DESC_SETTING[] = "$string:";
const char DEFAULT_ICON_SETTING_BEGIN[] = "$media:";
// app config
const char PROFILE_KEY_APP[] = "app";
const char PROFILE_KEY_VENDOR[] = "vendor";
const char PROFILE_KEY_BUNDLENAME[] = "bundleName";
const char PROFILE_KEY_VERSION[] = "version";
const char PROFILE_KEY_VERSION_CODE[] = "code";
const char PROFILE_KEY_VERSION_NAME[] = "name";
const char PROFILE_KEY_APIVERSION[] = "apiVersion";
const char PROFILE_KEY_APIVERSION_COMPATIBLE[] = "compatible";
const char PROFILE_KEY_APIVERSION_TARGET[] = "target";
// deviceConfig
const char PROFILE_KEY_DEVICECONFIG[] = "deviceConfig";
const char PROFILE_KEY_DEVICECONFIG_DEFAULT[] = "default";
const char PROFILE_KEY_KEEPALIVE[] = "keepAlive";
// module config
const char PROFILE_KEY_MODULE[] = "module";
const char PROFILE_KEY_MODULE_NAME[] = "name";
const char PROFILE_KEY_MODULE_DESCRIPTION[] = "description";
const char PROFILE_KEY_MODULE_DEVICETYPE[] = "deviceType";
const char PROFILE_KEY_MODULE_DISTRO[] = "distro";
const char PROFILE_KEY_MODULE_DISTRO_DELIVERY[] = "deliveryWithInstall";
const char PROFILE_KEY_MODULE_DISTRO_MODULENAME[] = "moduleName";
const char PROFILE_KEY_MODULE_DISTRO_MODULETYPE[] = "moduleType";
const char PROFILE_KEY_MODULE_METADATA[] = "metaData";
const char PROFILE_KEY_MODULE_METADATA_CUSTOMIZEDATA[] = "customizeData";
const char PROFILE_KEY_MODULE_METADATA_NAME[] = "name";
const char PROFILE_KEY_MODULE_METADATA_VALUE[] = "value";
const char PROFILE_KEY_MODULE_METADATA_EXTRA[] = "extra";
const char PROFILE_KEY_MODULE_ABILITIES[] = "abilities";
const char PROFILE_KEY_MODULE_ABILITY_NAME[] = "name";
const char PROFILE_KEY_MODULE_ABLLITY_DESCRIPTION[] = "description";
const char PROFILE_KEY_MODULE_ABILITY_LABEL[] = "label";
const char PROFILE_KEY_MODULE_ABILITY_ICON[] = "icon";
const char PROFILE_KEY_MODULE_ABILITY_TYPE[] = "type";
const char PROFILE_KEY_MODULE_ABILITY_LAUNCHTYPE[] = "launchType";
const char PROFILE_KEY_MODULE_ABILITY_VISIBLE[] = "visible";
// js config
const char PROFILE_KEY_JS[] = "js";

const char PROFILE_KEY_REQPERMISSIONS[] = "reqPermissions";
const char PROFILE_KEY_REQPERMISSIONS_NAME[] = "name";
const char PROFILE_KEY_REQPERMISSIONS_REASON[] = "reason";
const char PROFILE_KEY_REQPERMISSIONS_USEDSCENE[] = "usedScene";
const char PROFILE_KEY_REQPERMISSIONS_WHEN[] = "when";

const char ASSETS[] = "/assets/";

const char USES_SDK_FLAG[] = "zsdk ";
const char SPACE[] = " ";
const char DOT[] = ".";
const char GRANTTIME_INUSE[] = "inuse";
const char GRANTTIME_ALWAYS[] = "always";
const uint8_t VERSION_POINT_NUM = 2;
const uint8_t USES_SDK_SEGMENT = 2;
// shared lib path
const char SHARED_LIB_PATH[] = "shared_libs";
const char SEPARATOR[] = ":";

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
const char DEFAULT_DEVICE_TYPE[] = "smartVision";
const char INSTALL_PATH[] = "/storage/app/run";
const char DATA_PATH[] = "/storage/app/data";
const char JSON_PATH[] = "/storage/app/etc/bundles";
const char EXTEANAL_INSTALL_PATH[] = "/sdcard/app/run";
const char EXTEANAL_DATA_PATH[] = "/sdcard/app/data";
const char SYSTEM_BUNDLE_PATH[] = "/system/internal";
const char THIRD_SYSTEM_BUNDLE_PATH[] = "/system/external";
const char UNINSTALL_THIRD_SYSTEM_BUNDLE_JSON[] = "/storage/app/etc/uninstalled_delbundle.json";
const char THIRD_SYSTEM_BUNDLE_JSON[] = "/storage/app/etc/third_system_bundle.json";
const char UID_GID_MAP[] = "uid_gid_map";
// store bundle permissions for IAM
const char INSTALL_FILE_SUFFIX[] = ".hap";
// uid and gid
const int8_t INVALID_UID = -1;
const int8_t INVALID_GID = -1;
const uint32_t BASE_SYS_UID = 100;
const uint32_t BASE_SYS_VEN_UID = 1000;
const uint32_t MAX_SYS_VEN_UID = 9999;
const uint32_t BASE_APP_UID = 10000;
const char PROFILE_KEY_UID_SIZE[] = "size";
const char PROFILE_KEY_UID_AND_GID[] = "uid_and_gid";

const uint8_t MIN_BUNDLE_NAME_LEN = 7;
const uint8_t MAX_BUNDLE_NAME_LEN = 127;
const uint8_t MAX_VERSION_NAME_LEN = 127;
const uint16_t MAX_LABLE_LEN = 255;
#else
const char DEFAULT_DEVICE_TYPE[] = "fitnessWatch";
const char INSTALL_PATH[] = "app/ace/run";
const char DATA_PATH[] = "app/ace/data";
const char SYSTEM_BUNDLE_PATH[] = "system/ace/sys";
const char THIRD_SYSTEM_BUNDLE_PATH[] = "system/ace/vendor";
const char UNINSTALL_THIRD_SYSTEM_BUNDLE_JSON[] = "app/ace/etc/uninstalled_delbundle.json";
const char THIRD_SYSTEM_BUNDLE_JSON[] = "app/ace/etc/third_system_bundle.json";
const char JSON_PATH[] = "app/ace/etc/bundles";
// store bundle permissions for IAM
const char PERMISSIONS_PATH[] = "app/ace/etc/permissions";
const char ASSET_JS_PATH[] = "/assets/js/default";
const char DEFAULT_BIG_ICON_DIR_PATH[] = "/resources/base/media/icon.bin";
const char DEFAULT_SMALL_ICON_DIR_PATH[] = "/resources/base/media/icon_small.bin";
const char ICON_NAME[] = "icon.bin";
const char SMALL_ICON_NAME[] = "icon_small.bin";
const char DEFAULT_ICON_SETTING[] = "$media:icon";
const char INSTALL_FILE_SUFFIX[] = ".bin";
const uint16_t READ_SIZE = 1024 * 4;
const uint8_t MAGIC_NUMBER_LEN = 1;
const uint8_t INT_LENGTH = 4;
const uint8_t LONG_LENGTH = 8;
const uint16_t MAX_INT = 256;
const uint8_t MAX_BUNDLE_NAME_LEN = 30;
const uint8_t MAX_VERSION_NAME_LEN = 20;
const uint8_t MAX_LABLE_LEN = 30;

struct SignatureInfo {
    char *bundleName;
    char *appId;
    char **restricPermission;
    uint32_t restricNum;
};
#endif
// InstallRecord key
const char JSON_MAIN_KEY[] = "packages";
const char JSON_SUB_KEY_PACKAGE[] = "bundleName";
const char JSON_SUB_KEY_CODEPATH[] = "codePath";
const char JSON_SUB_KEY_APPID[] = "appID";
const char JSON_SUB_KEY_VERSIONCODE[] = "versionCode";
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
const char JSON_SUB_KEY_UID[] = "uid";
const char JSON_SUB_KEY_GID[] = "gid";
#endif

struct ProfileVersion {
    uint32_t versionCode;
    char *versionName;
};

struct ProfileApiVersion {
    int32_t minApiVersion;
    int32_t maxApiVersion;
};

struct AbilityRes {
    uint32_t iconId;
    uint32_t labelId;
    uint32_t descriptionId;
    uint32_t index;
};

struct BundleRes {
    uint32_t moduleDescriptionId;
    AbilityRes *abilityRes;
    uint32_t totalNumOfAbilityRes;
};

struct BundleProfile {
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    bool isKeepAlive;
    bool isNativeApp;
#endif
    char *bundleName;
    char *vendor;
    char *label;
    char *iconPath;
    ProfileVersion profileVersion;
    ProfileApiVersion profileApiVersion;
    ModuleInfo moduleInfo;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    AbilityInfo *abilityInfos;
    uint32_t numOfAbility;
#endif
};

struct Permissions {
    int32_t permNum;
    PermissionTrans *permissionTrans;
};

struct InstallRecord {
    char *bundleName;
    char *codePath;
    char *appId; // it contains bundleName and cert publicKey
    int32_t versionCode;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    int32_t uid;
    int32_t gid;
#endif
};
}  // namespace OHOS
#endif  // OHOS_BUNDLE_COMMON_H
