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

#ifndef OHOS_ABILITYKIT_H
#define OHOS_ABILITYKIT_H

#include "stdint.h"

typedef int32_t (*SuccessCallback)(void *data);
typedef int32_t (*FailCallback)(void *data, uint16_t dataLength, uint16_t errorCode);

namespace OHOS {
struct FeatureAbilityDataInfo {
    char *bundleName { nullptr };
    void *message { nullptr };
    uint32_t messageLength { 0 };
    char *abilityName { nullptr };
    char *deviceID { nullptr };
};

class AbilityKit {
public:
    AbilityKit();
    ~AbilityKit();

    static int32_t RegisterReceiver(const char *bundleName, SuccessCallback success, FailCallback fail);
    static int32_t UnregisterReceiver(const char *bundleName);
    static int32_t SendMsgToPeerApp(bool isLocalMsg, const char *callingPkgName, const char *calledPkgName,
                                    const uint8_t *msgBody, uint32_t length);
};
} // namespace OHOS
#endif // OHOS_ABILITYKIT_H