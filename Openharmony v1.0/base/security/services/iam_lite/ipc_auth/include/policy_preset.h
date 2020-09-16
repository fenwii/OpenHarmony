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

#ifndef POLICY_PERSET_H
#define POLICY_PERSET_H

#include "policy_define.h"

FeaturePolicy pmsFeature[] = {
    {
        "PmsFeature",
        {
            {
                .type=RANGE,
                .uidMin=0,
                .uidMax=__INT_MAX__,
            },
        }
    },
};

FeaturePolicy amsFeature[] = {
    {
        "AmsFeature",
        {
            {
                .type=RANGE,
                .uidMin=0,
                .uidMax=__INT_MAX__,
            },
        }
    },
    {
        "AmsInnerFeature",
        {
            {
                .type=FIXED,
                .fixedUid={2}
            },
        }
    },
};

FeaturePolicy bmsFeature[] = {
    {
        "BmsFeature",
        {
            {
                .type=FIXED,
                .fixedUid={2, 3, 8}
            },
            {
                .type=RANGE,
                .uidMin=100,
                .uidMax=__INT_MAX__,
            },
        }
    },
    {
        "BmsInnerFeature",
        {
            {
                .type=FIXED,
                .fixedUid={2, 3, 8}
            },
            {
                .type=RANGE,
                .uidMin=100,
                .uidMax=999,
            },
        }
    },
};

FeaturePolicy bdsFeature[] = {
    {
        NULL,
        {
            {
                .type=FIXED,
                .fixedUid={7}
            },
        }
    },
};

FeaturePolicy dmsFeature[] = {
    {
        "dmslite",
        {
            {
                .type=RANGE,
                .uidMin=0,
                .uidMax=__INT_MAX__,
            },
        }
    },
};

FeaturePolicy samgrFeature[] = {
    {
        NULL,
        {
            {
                .type=RANGE,
                .uidMin=0,
                .uidMax=__INT_MAX__,
            },
        }
    },
};

FeaturePolicy appspawnFeature[] = {
    {
        NULL,
        {
            {
                .type=FIXED,
                .fixedUid={7}
            },
        }
    },
};

FeaturePolicy wmsFeature[] = {
    {
        NULL,
        {
            {
                .type=RANGE,
                .uidMin=100,
                .uidMax=__INT_MAX__,
            },
            {
                .type=FIXED,
                .fixedUid={2, 7}
            },
        }
    },
};

static PolicySetting g_presetPolicies[] = {
    {"permissionms", pmsFeature, 1},
    {"abilityms", amsFeature, 2},
    {"bundlems", bmsFeature, 2},
    {"dtbschedsrv", dmsFeature, 1},
    {"samgr", samgrFeature, 1},
    {"appspawn", appspawnFeature, 1},
    {"WMS", wmsFeature, 1},
    {"bundle_daemon", bdsFeature, 1},
};

static int g_presetPolicySize = sizeof(g_presetPolicies) / sizeof(PolicySetting);

#endif // POLICY_PERSET_H
