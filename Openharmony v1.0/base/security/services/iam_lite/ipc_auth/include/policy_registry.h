/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef POLICY_REGISTRY_H
#define POLICY_REGISTRY_H

#include "policy_define.h"

FeaturePolicy regSvc1Feature[] = {
    {
        "feature1",
        {
            {
                .type=RANGE,
                .uidMin=100,
                .uidMax=110
            },
            {
                .type=FIXED,
                .fixedUid={75, 85, 95}
            },
            {
                .type=BUNDLENAME,
                .bundleName="OHOS"
            },
        }
    },
    {
        "feature2",
        {
            {
                .type=RANGE,
                .uidMin=100,
                .uidMax=110
            },
            {
                .type=FIXED,
                .fixedUid={75, 85, 95}
            },
            {
                .type=BUNDLENAME,
                .bundleName="OHOS"
            },
        }
    },
};

static PolicySetting g_registryPolicies[] = {
    {"regSvc1", regSvc1Feature, 2},
};

static int g_regPoliciesSize = sizeof(g_registryPolicies) / sizeof(PolicySetting);

#endif // POLICY_REGISTRY_H