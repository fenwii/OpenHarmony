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

#ifndef LITE_FEATUREIMPL_H
#define LITE_FEATUREIMPL_H

#include "common.h"
#include "iunknown.h"
#include "feature.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
typedef struct FeatureImpl FeatureImpl;

struct FeatureImpl {
    Feature *feature;
    IUnknown *iUnknown;
};

inline static BOOL IsInvalidFeature(Feature *feature)
{
    return (feature == NULL || feature->GetName == NULL || feature->OnInitialize == NULL ||
            feature->OnMessage == NULL || feature->OnStop == NULL);
}

inline static BOOL IsInvalidIUnknown(IUnknown *iUnknown)
{
    return (iUnknown == NULL || iUnknown->QueryInterface == NULL || iUnknown->AddRef == NULL ||
            iUnknown->Release == NULL);
}
BOOL SAMGR_AddInterface(FeatureImpl *featureImpl, IUnknown *iUnknown);
IUnknown *SAMGR_DelInterface(FeatureImpl *featureImpl);
IUnknown *SAMGR_GetInterface(FeatureImpl *featureImpl);
BOOL SAMGR_IsNoInterface(FeatureImpl *featureImpl);
FeatureImpl *FEATURE_CreateInstance(Feature *feature);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // LITE_FEATUREIMPL_H
