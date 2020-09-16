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

#ifndef OHOS_GT_BUNDLE_PARSER_H
#define OHOS_GT_BUNDLE_PARSER_H

#include "bundle_common.h"
#include "bundle_info.h"
#include "stdint.h"

#include "cJSON.h"

namespace OHOS {
class GtBundleParser {
public:
    static BundleInfo *ParseHapProfile(const char *path);
    static uint8_t ParseHapProfile(int32_t fp, uint32_t fileSize, Permissions &permissions, BundleRes &bundleRes,
        BundleInfo **bundleInfo);
    static bool ParseBundleAttr(const char *path, char **bundleName, int32_t &versionCode);
    static uint8_t ConvertResInfoToBundleInfo(const char *path, uint32_t labelId, uint32_t iconId,
        BundleInfo *bundleInfo);
private:
    static uint8_t ParseJsonInfo(const cJSON *appObject, const cJSON *configObject, const cJSON *moduleObject,
        BundleProfile &bundleProfile, BundleRes &bundleRes);
    static BundleInfo *CreateBundleInfo(const char *path, const BundleProfile &bundleProfile,
        const BundleRes &bundleRes);
    static bool ConvertIconResToBundleInfo(const char *resPath, uint32_t iconId, BundleInfo *bundleInfo);
    static uint8_t ParseModuleInfo(const cJSON *moduleObject, BundleProfile &bundleProfile, BundleRes &bundleRes);
    static uint8_t ParseAbilityInfo(const cJSON *abilityInfoObjects, BundleProfile &bundleProfile,
        BundleRes &bundleRes);
    static uint8_t ParseModuleMetaData(const cJSON *moduleObject, BundleProfile &bundleProfile);
    static bool SetModuleInfos(const BundleProfile &bundleProfile, BundleInfo *bundleInfo);
    static uint8_t SaveBundleInfo(const BundleProfile &bundleProfile, const BundleRes &bundleRes,
        BundleInfo **bundleInfo);
    static bool SetBundleInfo(const BundleProfile &bundleProfile, const BundleRes &bundleRes, BundleInfo *bundleInfo);
    static char *ParseValue(const cJSON *object, const char *key);
    static int32_t ParseValue(const cJSON *object, const char *key, int32_t defaultValue);
    static cJSON *ParseValue(const cJSON *object, const char *key, cJSON *defaultValue);
    static uint8_t ParsePermissions(const cJSON *object, Permissions &permissions);
    static bool SetReqPermission(const cJSON *object, PermissionTrans *permission);
    static bool CheckDeviceTypeIsValid(const cJSON *deviceTypeObject);
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

#define FREE_BUNDLE_PROFILE(bundleProfile)                           \
    do {                                                             \
        for (int32_t i = 0; i < METADATA_SIZE; i++) {                \
            AdapterFree(bundleProfile.moduleInfo.metaData[i]);       \
        }                                                            \
    } while (0)

#define FREE_BUNDLE_RES(bundleRes)                          \
    do {                                                    \
        if (bundleRes.abilityRes != nullptr) {              \
            AdapterFree(bundleRes.abilityRes);              \
        }                                                   \
    } while (0)

#define CHECK_PARSE_RESULT(errorCode, object, bundleProfile, bundleRes)   \
    do {                                                                  \
        if (errorCode != ERR_OK) {                                        \
            FREE_BUNDLE_PROFILE(bundleProfile);                           \
            FREE_BUNDLE_RES(bundleRes);                                   \
            cJSON_Delete(object);                                         \
            return errorCode;                                             \
        }                                                                 \
    } while (0)
} // namespace OHOS
#endif  // OHOS_GT_BUNDLE_PARSER_H
