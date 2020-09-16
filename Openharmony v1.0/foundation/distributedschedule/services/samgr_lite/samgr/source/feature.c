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
#include "feature.h"
#include "feature_impl.h"
#include "memory_adapter.h"

BOOL SAMGR_AddInterface(FeatureImpl *featureImpl, IUnknown *iUnknown)
{
    if (featureImpl == NULL || iUnknown == NULL || featureImpl->iUnknown != NULL) {
        return FALSE;
    }

    featureImpl->iUnknown = iUnknown;
    return TRUE;
}

IUnknown *SAMGR_DelInterface(FeatureImpl *featureImpl)
{
    if (featureImpl == NULL) {
        return NULL;
    }
    IUnknown *iUnknown = featureImpl->iUnknown;
    featureImpl->iUnknown = NULL;
    return iUnknown;
}

IUnknown *SAMGR_GetInterface(FeatureImpl *featureImpl)
{
    if (featureImpl == NULL) {
        return NULL;
    }
    return featureImpl->iUnknown;
}

BOOL SAMGR_IsNoInterface(FeatureImpl *featureImpl)
{
    return (BOOL)(featureImpl == NULL || featureImpl->iUnknown == NULL);
}

FeatureImpl *FEATURE_CreateInstance(Feature *feature)
{
    if (feature == NULL) {
        return NULL;
    }
    FeatureImpl *featureImpl = (FeatureImpl *)SAMGR_Malloc(sizeof(FeatureImpl));
    if (featureImpl == NULL) {
        return NULL;
    }
    featureImpl->feature = feature;
    featureImpl->iUnknown = NULL;
    return featureImpl;
}