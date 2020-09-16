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
#include "service_impl.h"
#include <string.h>
#include "memory_adapter.h"
#include "thread_adapter.h"
#include "time_adapter.h"
#include "feature_impl.h"
#include "service_registry.h"

static const char *GetFeatureName(const FeatureImpl *featureImpl);

ServiceImpl *SAMGR_CreateServiceImpl(Service *service, uint8 step)
{
    ServiceImpl *impl = (ServiceImpl *)SAMGR_Malloc(sizeof(ServiceImpl));
    if (impl == NULL) {
        return NULL;
    }
    impl->service = service;
    impl->defaultApi = NULL;
    impl->taskPool = NULL;
    impl->features = VECTOR_Make((VECTOR_Key)GetFeatureName, (VECTOR_Compare)strcmp);
    impl->serviceId = INVALID_INDEX;
    impl->inited = SVC_INIT;
    impl->ops.abnormal = 0;
    impl->ops.messages = 0;
    impl->ops.step = step;
    impl->ops.timestamp = (uint32)SAMGR_GetProcessTime();
    return impl;
}

int16 DEFAULT_AddFeature(ServiceImpl *serviceImpl, Feature *feature)
{
    if (serviceImpl == NULL || feature == NULL) {
        return INVALID_INDEX;
    }

    if (VECTOR_Num(&(serviceImpl->features)) >= MAX_FEATURE_NUM) {
        return INVALID_INDEX;
    }

    FeatureImpl *impl = FEATURE_CreateInstance(feature);
    if (impl == NULL) {
        return INVALID_INDEX;
    }

    int16 featureId = VECTOR_Add(&(serviceImpl->features), impl);
    if (featureId == INVALID_INDEX) {
        SAMGR_Free(impl);
    }
    return featureId;
}

void DEFAULT_Initialize(ServiceImpl *impl)
{
    if (impl == NULL) {
        return;
    }
    Identity id = {impl->serviceId, INVALID_INDEX, (impl->taskPool != NULL) ? impl->taskPool->queueId : NULL};

    impl->service->Initialize(impl->service, id);
    const char *serviceName = impl->service->GetName(impl->service);
    SAMGR_RegisterServiceApi(serviceName, NULL, &id, impl->defaultApi);

    int16 size = VECTOR_Size(&impl->features);
    int16 i;
    for (i = 0; i < size; ++i) {
        FeatureImpl *feature = (FeatureImpl *)VECTOR_At(&(impl->features), i);
        if (feature == NULL) {
            continue;
        }
        id.featureId = i;
        feature->feature->OnInitialize(feature->feature, impl->service, id);
        SAMGR_RegisterServiceApi(serviceName, feature->feature->GetName(feature->feature), &id, feature->iUnknown);
    }
}

void DEFAULT_MessageHandle(ServiceImpl *serviceImpl, const Identity *identity, Request *msg)
{
    if (serviceImpl->serviceId != identity->serviceId) {
        return;
    }

    if (identity->featureId < 0) {
        if (serviceImpl->service->MessageHandle != NULL) {
            serviceImpl->service->MessageHandle(serviceImpl->service, msg);
        }
        return;
    }

    if (VECTOR_Size(&serviceImpl->features) <= identity->featureId) {
        return;
    }

    FeatureImpl *featureImpl = (FeatureImpl *)VECTOR_At(&(serviceImpl->features), identity->featureId);
    if (featureImpl == NULL) {
        return;
    }
    featureImpl->feature->OnMessage(featureImpl->feature, msg);
}

void DEFAULT_StopService(ServiceImpl *service)
{
    if (service == NULL) {
        return;
    }

    Identity id = {service->serviceId, INVALID_INDEX, (service->taskPool != NULL) ? service->taskPool->queueId : NULL};
    int16 size = VECTOR_Size(&service->features);
    int16 i;
    for (i = 0; i < size; ++i) {
        FeatureImpl *featureImpl = (FeatureImpl *)VECTOR_At(&(service->features), i);
        if (featureImpl == NULL) {
            continue;
        }
        id.featureId = i;
        featureImpl->feature->OnStop(featureImpl->feature, id);
    }
    service->inited = SVC_INIT;
}

FeatureImpl *DEFAULT_GetFeature(ServiceImpl *serviceImpl, const char *featureName)
{
    if (serviceImpl == NULL || featureName == NULL) {
        return NULL;
    }

    short pos = VECTOR_FindByKey(&(serviceImpl->features), (void *)featureName);
    return (FeatureImpl *)VECTOR_At(&(serviceImpl->features), pos);
}

Identity DEFAULT_GetFeatureId(ServiceImpl *serviceImpl, const char *feature)
{
    Identity identity = {INVALID_INDEX, INVALID_INDEX, NULL};
    if (serviceImpl == NULL) {
        return identity;
    }

    identity.serviceId = serviceImpl->serviceId;
    if (serviceImpl->taskPool != NULL) {
        identity.queueId = serviceImpl->taskPool->queueId;
    }

    int16 pos = VECTOR_FindByKey(&(serviceImpl->features), (void *)feature);
    FeatureImpl *featureImpl = (FeatureImpl *)VECTOR_At(&(serviceImpl->features), pos);
    if (featureImpl == NULL) {
        return identity;
    }
    identity.featureId = pos;
    return identity;
}

Feature *DEFAULT_DeleteFeature(ServiceImpl *serviceImpl, const char *featureName)
{
    if (serviceImpl == NULL || featureName == NULL) {
        return NULL;
    }

    int16 pos = VECTOR_FindByKey(&(serviceImpl->features), (void *)featureName);
    if (pos < 0 || !SAMGR_IsNoInterface((FeatureImpl *)VECTOR_At(&serviceImpl->features, pos))) {
        return NULL;
    }

    FeatureImpl *featureImpl = (FeatureImpl *)VECTOR_Swap(&(serviceImpl->features), pos, NULL);
    if (featureImpl == NULL) {
        return NULL;
    }

    Identity id = {serviceImpl->serviceId, INVALID_INDEX, NULL};
    featureImpl->feature->OnStop(featureImpl->feature, id);

    Feature *feature = featureImpl->feature;
    SAMGR_Free(featureImpl);
    return feature;
}

static const char *GetFeatureName(const FeatureImpl *featureImpl)
{
    if (featureImpl == NULL) {
        return NULL;
    }
    return featureImpl->feature->GetName(featureImpl->feature);
}
