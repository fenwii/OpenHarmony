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

#ifndef OHOS_BUNDLE_CALLBACK_UTILS_H
#define OHOS_BUNDLE_CALLBACK_UTILS_H

#include <string>

#include "ability_info.h"
#include "appexecfwk_errors.h"
#include "bundle_info.h"
#include "bundle_manager.h"
#include "bundle_status_callback.h"

namespace OHOS {
const char INSTALL_SUCCESS[] = "install success !";
const char UNINSTALL_SUCCESS[] = "uninstall success !";

enum {
    INSTALL_CALLBACK,
    UNINSTALL_CALLBACK
};

std::string ObtainErrorMessage(uint8_t errorCode);
} // namespace

struct ResultOfQueryAbilityInfo {
    uint8_t resultCode;
    AbilityInfo *abilityInfo;
};

struct ResultOfGetBundleInfo {
    uint8_t resultCode;
    BundleInfo *bundleInfo;
};

struct ResultOfGetBundleInfos {
    uint8_t resultCode;
    int32_t length;
    BundleInfo *bundleInfo;
};

struct ResultOfGetBundleNameForUid {
    uint8_t resultCode;
    char *bundleName;
    int32_t length;
};

struct BundleCallbackInfo {
    BundleStateCallback bundleStateCallback;
    void *data;
};
#endif // OHOS_BUNDLE_CALLBACK_UTILS_H