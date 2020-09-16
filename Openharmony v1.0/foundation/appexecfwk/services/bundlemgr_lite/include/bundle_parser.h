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

#ifndef OHOS_BUNDLE_PARSER_H
#define OHOS_BUNDLE_PARSER_H

#include "adapter.h"
#include "bundle_common.h"
#include "bundle_info.h"
#include "stdint.h"

#include <string>

#include "cJSON.h"

namespace OHOS {
class BundleParser {
public:
    BundleParser() = default;
    ~BundleParser() = default;

    BundleInfo *ParseHapProfile(const char *path);
    uint8_t ParseHapProfile(const std::string &path, Permissions &permissions, BundleRes &bundleRes,
        BundleInfo **bundleInfo);
    static int8_t ParseBundleParam(const char *path, char **bundleName, int32_t &versionCode);
private:
    static uint8_t ParseJsonInfo(const cJSON *appObject, const cJSON *configObject, const cJSON *moduleObject,
        BundleProfile &bundleProfile, BundleRes &bundleRes);
    static uint8_t ParseDeviceConfig(const cJSON *configObject, BundleProfile &bundleProfile);
    static uint8_t ParseModuleInfo(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes);
    static uint8_t ParseModuleMetaData(const cJSON *moduleObject, BundleProfile &bundleProfile);
    static uint8_t ParseDeviceType(const cJSON *object, BundleProfile &bundleProfile);
    static uint8_t ParseAbilityInfos(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes);
    static uint8_t ParseAllAbilityInfo(const cJSON *abilityObjects, BundleProfile &bundleProfile,
        BundleRes &bundleRes);
    static uint8_t ParseAbilityType(const cJSON *abilityObjectItem, AbilityInfo &abilityInfo);
    static uint8_t ParseAbilityLauchMode(const cJSON *abilityObjectItem, AbilityInfo &abilityInfo);
    static uint8_t ParseAbilityVisible(const cJSON *abilityObjectItem, AbilityInfo &abilityInfo);
    static uint8_t ParsePerAbilityInfo(const cJSON *abilityObjectItem, BundleProfile &bundleProfile,
        AbilityRes &abilityRes, uint32_t index);
    static uint8_t ParseModuleDesc(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes);
    static uint8_t ParseAbilityDesc(const cJSON *abilityObject, BundleProfile &bundleProfile, AbilityRes &abilityRes,
        int32_t index);
    static uint8_t ParseAbilityIcon(const cJSON *abilityObject, BundleProfile &bundleProfile, AbilityRes &abilityRes,
        int32_t index);
    static uint8_t ParseAbilityLabel(const cJSON *abilityObject, BundleProfile &bundleProfile, AbilityRes &abilityRes,
        int32_t index);
    static char *ParseValue(const cJSON *object, const char *key);
    static int32_t ParseValue(const cJSON *object, const char *key, int32_t defaultValue);
    static cJSON *ParseValue(const cJSON *object, const char *key, cJSON *defaultValue);
    static bool CheckBundleNameIsValid(const char *bundleName);
    static uint8_t ParsePermissions(const cJSON *object, Permissions &permissions);
    static bool SetReqPermission(const cJSON *object, PermissionTrans *permission);
};

#define CHECK_NULL(object, errorCode)          \
    do {                                       \
        if (object == nullptr) {               \
            return errorCode;                  \
        }                                      \
    } while (0)

#define CHECK_LENGTH(length, maxLength, errorCode)           \
    do {                                                     \
        if (length > maxLength) {                            \
            return errorCode;                                \
        }                                                    \
    } while (0)

#define CHECK_IS_TRUE(result, errorCode)     \
    do {                                     \
        if (!result) {                       \
            return errorCode;                \
        }                                    \
    } while (0)

#define CHECK_PARSE_RESULT(errorCode, object, bundleProfile) \
    do {                                                     \
        if (errorCode != ERR_OK) {                           \
            FREE_BUNDLE_PROFILE(bundleProfile);              \
            cJSON_Delete(object);                            \
            return errorCode;                                \
        }                                                    \
    } while (0)

#define FREE_BUNDLE_PROFILE(bundleProfile)                      \
    do {                                                        \
        AdapterFree(bundleProfile.abilityInfos);                \
        for (uint8_t i = 0; i < METADATA_SIZE; i++) {           \
            AdapterFree(bundleProfile.moduleInfo.metaData[i]);  \
        }                                                       \
    } while (0)
} // namespace OHOS
#endif  // OHOS_BUNDLE_PARSER_H
