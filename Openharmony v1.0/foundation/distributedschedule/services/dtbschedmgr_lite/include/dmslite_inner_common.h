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

#ifndef OHOS_DMSLITE_INNER_COMMON_H
#define OHOS_DMSLITE_INNER_COMMON_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum DmsAllowedUids {
    FOUNDATION_UID = 7,
    SHELL_UID = 2,
};

/**
* @brief Callback for parsing dmslite tlv message
* @param errCode indicates the result of parsing tlv message
* @param dmsMsg parsed request message from remote if success, otherwise is NULL
*/
typedef void (*TlvParseCallback) (int8_t errCode, const void *dmsMsg);

/**
* @brief Callback for starting ability
* @param errCode indicates the result of starting ability
*/
typedef void (*StartAbilityCallback) (int8_t errCode);

typedef struct {
    TlvParseCallback onTlvParseDone;
    StartAbilityCallback onStartAbilityDone;
} IDmsFeatureCallback;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  // OHOS_DMSLITE_INNER_COMMON_H
