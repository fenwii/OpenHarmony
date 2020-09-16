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

#ifndef OHOS_BUNDLE_INNER_INTERFACE_H
#define OHOS_BUNDLE_INNER_INTERFACE_H

#include "ability_info.h"
#include "bundle_info.h"
#include "iproxy_server.h"
#include "want.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

const char BMS_SERVICE[] = "bundlems";
const char BMS_FEATURE[] = "BmsFeature";
const char BMS_INNER_FEATURE[] = "BmsInnerFeature";

enum BmsCmd {
    QUERY_ABILITY_INFO = 0,
    GET_BUNDLE_INFO,
    CHANGE_CALLBACK_SERVICE_IDENTITY,
    GET_BUNDLENAME_FOR_UID,
    GET_BUNDLE_INFOS,
    QUERY_KEEPALIVE_BUNDLE_INFOS,
    GET_BUNDLE_INFOS_BY_METADATA,
    BMS_INNER_BEGIN,
    INSTALL = BMS_INNER_BEGIN, // bms install application
    UNINSTALL,
#ifdef OHOS_DEBUG
    SET_EXTERNAL_INSTALL_MODE,
    SET_SIGN_DEBUG_MODE,
    SET_SIGN_MODE,
#endif
    BMS_CMD_END
};

struct BmsServerProxy {
    INHERIT_SERVER_IPROXY;
    uint8_t (*QueryAbilityInfo)(const Want *want, AbilityInfo *abilityInfo);
    uint8_t (*GetBundleInfo)(const char *bundleName, int32_t flags, BundleInfo *bundleInfo);
    uint8_t (*GetBundleInfos)(int flags, BundleInfo **bundleInfos, int32_t *len);
    uint8_t (*QueryKeepAliveBundleInfos)(BundleInfo **bundleInfos, int32_t *len);
    uint8_t (*GetBundleNameForUid)(int32_t uid,  char **bundleName);
};

struct BmsInnerServerProxy {
    INHERIT_SERVER_IPROXY;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* OHOS_BUNDLE_INNER_INTERFACE_H */