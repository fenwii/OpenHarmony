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
#include "client_factory.h"
#include <ohos_errno.h>
#include "registry.h"
#include "memory_adapter.h"
#include "thread_adapter.h"
#include "default_client.h"

typedef struct Factory Factory;
struct Factory {
    SaName key;
    Creator creator;
    Destroyer destroyer;
};

static Vector g_factories;
static MutexId g_mutex;
static Factory *GetFactory(const char *service, const char *feature);

void *SAMGR_CreateIClient(const char *service, const char *feature, uint32 size)
{
    if (service == NULL) {
        return NULL;
    }

    if (g_mutex == NULL) {
        return NULL;
    }

    Factory *factory = GetFactory(service, feature);
    if (factory == NULL) {
        return NULL;
    }

    return factory->creator(service, feature, size);
}

int SAMGR_ReleaseIClient(const char *service, const char *feature, void *iClient)
{
    if (service == NULL || iClient == NULL) {
        return EC_INVALID;
    }

    if (g_mutex == NULL) {
        return EC_NOHANDLER;
    }

    Factory *factory = GetFactory(service, feature);
    if (factory == NULL) {
        return EC_NOHANDLER;
    }
    factory->destroyer(service, feature, iClient);
    return EC_SUCCESS;
}

int SAMGR_RegisterFactory(const char *service, const char *feature, Creator creator, Destroyer destroyer)
{
    if (service == NULL || creator == NULL || destroyer == NULL) {
        return EC_INVALID;
    }

    if (g_mutex == NULL) {
        g_factories = VECTOR_Make(NULL, (VECTOR_Compare)SAMGR_CompareSAName);
        g_mutex = MUTEX_InitValue();
        if (g_mutex == NULL) {
            return EC_NOMEMORY;
        }
    }

    Factory *factory = GetFactory(service, feature);
    if (factory != NULL) {
        return EC_SUCCESS;
    }

    MUTEX_Lock(g_mutex);
    factory = SAMGR_Malloc(sizeof(Factory));
    if (factory == NULL) {
        MUTEX_Unlock(g_mutex);
        return EC_NOMEMORY;
    }
    factory->key.service = service;
    factory->key.feature = feature;
    factory->creator = creator;
    factory->destroyer = destroyer;
    int ret = VECTOR_Add(&g_factories, factory);
    MUTEX_Unlock(g_mutex);
    if (ret == INVALID_INDEX) {
        SAMGR_Free(factory);
        return EC_NOMEMORY;
    }
    return EC_SUCCESS;
}

static Factory *GetFactory(const char *service, const char *feature)
{
    SaName key = {service, feature};
    Factory *factory = NULL;
    MUTEX_Lock(g_mutex);
    int index = VECTOR_FindByKey(&g_factories, &key);
    if (index != INVALID_INDEX) {
        factory = VECTOR_At(&g_factories, index);
    }
    MUTEX_Unlock(g_mutex);
    return factory;
}
