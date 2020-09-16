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
#include "pub_sub_feature.h"
#include <ohos_init.h>
#include "samgr_lite.h"
#include "thread_adapter.h"
#include "pub_sub_implement.h"

static const char *GetName(Feature *feature);
static void OnInitialize(Feature *feature, Service *parent, Identity identity);
static void OnStop(Feature *feature, Identity identity);
static BOOL OnMessage(Feature *feature, Request *request);
static Relation *GetRelation(PubSubFeature *feature, const Topic *topic);
static BOOL IsTopicEqual(const Topic *current, const Topic *other);
static PubSubFeature g_broadcastFeature = {
    .GetName = GetName,
    .OnInitialize = OnInitialize,
    .OnStop = OnStop,
    .OnMessage = OnMessage,
    .GetRelation = GetRelation,
};

static void Init(void)
{
    PubSubFeature *feature = &g_broadcastFeature;
    feature->relations.topic = -1;
    feature->relations.callbacks.consumer = NULL;
    UtilsListInit(&feature->relations.callbacks.node);
    UtilsListInit(&feature->relations.node);
    feature->mutex = MUTEX_InitValue();
    SAMGR_GetInstance()->RegisterFeature(BROADCAST_SERVICE, (Feature *)feature);

    PubSubImplement *apiEntry = BCE_CreateInstance((Feature *)feature);
    SAMGR_GetInstance()->RegisterFeatureApi(BROADCAST_SERVICE, PUB_SUB_FEATURE, GET_IUNKNOWN(*apiEntry));
}
SYS_FEATURE_INIT(Init);

static const char *GetName(Feature *feature)
{
    (void)feature;
    return PUB_SUB_FEATURE;
}

static void OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    (void)parent;
    ((PubSubFeature *)feature)->identity = identity;
}

static void OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL OnMessage(Feature *feature, Request *request)
{
    PubSubFeature *broadcast = (PubSubFeature *)feature;
    switch (request->msgId) {
        case MSG_PUBLISH: {
            Topic topic = request->msgValue;
            Relation *relation = broadcast->GetRelation(broadcast, &topic);
            if (relation == NULL) {
                return FALSE;
            }
            MUTEX_Lock(broadcast->mutex);
            ConsumerNode *item = NULL;
            UTILS_DL_LIST_FOR_EACH_ENTRY(item, &relation->callbacks.node, ConsumerNode, node) {
                if (item->consumer->identity == NULL) {
                    item->consumer->Notify(item->consumer, &topic, request);
                }
            }
            MUTEX_Unlock(broadcast->mutex);
        }
            break;
        default:
            break;
    }
    return TRUE;
}

static Relation *GetRelation(PubSubFeature *feature, const Topic *topic)
{
    if (feature == NULL || topic == NULL) {
        return NULL;
    }

    UTILS_DL_LIST *list = &feature->relations.node;
    Relation *item = NULL;
    MUTEX_Lock(feature->mutex);
    UTILS_DL_LIST_FOR_EACH_ENTRY(item, list, Relation, node) {
        if (IsTopicEqual(&item->topic, topic)) {
            MUTEX_Unlock(feature->mutex);
            return item;
        }
    }
    MUTEX_Unlock(feature->mutex);
    return NULL;
}

static BOOL IsTopicEqual(const Topic *current, const Topic *other)
{
    return *current == *other;
}
