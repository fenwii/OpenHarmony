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
#include "pub_sub_implement.h"
#include "securec.h"
#include "ohos_errno.h"
#include "memory_adapter.h"
#include "thread_adapter.h"

static int AddTopic(IUnknown *iUnknown, const Topic *topic);
static int Subscribe(IUnknown *iUnknown, const Topic *topic, Consumer *consumer);
static Consumer *ModifyConsumer(IUnknown *iUnknown, const Topic *topic, Consumer *oldConsumer, Consumer *newConsumer);
static Consumer *Unsubscribe(IUnknown *iUnknown, const Topic *topic, const Consumer *consumer);
static BOOL Publish(IUnknown *iUnknown, const Topic *topic, uint8 *data, int16 len);
static void DefaultHandle(const Request *request, const Response *response);
static BOOL ImmediatelyPublish(PubSubFeature *feature, const Topic *topic, const Request *request);

static PubSubImplement g_pubSubImplement = {
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .subscriber.AddTopic = AddTopic,
    .subscriber.Subscribe = Subscribe,
    .subscriber.ModifyConsumer = ModifyConsumer,
    .subscriber.Unsubscribe = Unsubscribe,
    .provider.Publish = Publish,
    DEFAULT_IUNKNOWN_ENTRY_END,
    .feature = NULL
};
PubSubImplement *BCE_CreateInstance(Feature *feature)
{
    g_pubSubImplement.feature = (PubSubFeature *)feature;
    return &g_pubSubImplement;
}


static int AddTopic(IUnknown *iUnknown, const Topic *topic)
{
    if (iUnknown == NULL || topic == NULL) {
        return EC_INVALID;
    }

    PubSubImplement *broadcast = GET_OBJECT(iUnknown, PubSubImplement, iUnknown);
    if (broadcast->feature == NULL || broadcast->feature->GetRelation == NULL) {
        return EC_FAILURE;
    }

    if (broadcast->feature->GetRelation(broadcast->feature, topic) != NULL) {
        return EC_FAILURE;
    }

    Relation *head = &broadcast->feature->relations;
    Relation *newRelation = (Relation *)SAMGR_Malloc(sizeof(Relation));
    if (newRelation == NULL) {
        return EC_NOMEMORY;
    }
    newRelation->topic = *topic;
    newRelation->callbacks.consumer = NULL;
    UtilsListInit(&newRelation->callbacks.node);

    MUTEX_Lock(broadcast->feature->mutex);
    UtilsListAdd(&head->node, &(newRelation->node));
    MUTEX_Unlock(broadcast->feature->mutex);
    return EC_SUCCESS;
}

static int Subscribe(IUnknown *iUnknown, const Topic *topic, Consumer *consumer)
{
    if (iUnknown == NULL || topic == NULL || consumer == NULL) {
        return EC_INVALID;
    }

    PubSubImplement *broadcast = GET_OBJECT(iUnknown, PubSubImplement, iUnknown);
    if (broadcast->feature == NULL || broadcast->feature->GetRelation == NULL) {
        return EC_FAILURE;
    }

    Relation *relation = broadcast->feature->GetRelation(broadcast->feature, topic);
    if (relation == NULL) {
        return EC_FAILURE;
    }

    MUTEX_Lock(broadcast->feature->mutex);
    ConsumerNode *item = NULL;
    UTILS_DL_LIST_FOR_EACH_ENTRY(item, &relation->callbacks.node, ConsumerNode, node) {
        if (item->consumer->Equal(item->consumer, consumer)) {
            MUTEX_Unlock(broadcast->feature->mutex);
            return EC_ALREADY_SUBSCRIBED;
        }
    }
    MUTEX_Unlock(broadcast->feature->mutex);
    ConsumerNode *consumerNode = (ConsumerNode *)SAMGR_Malloc(sizeof(ConsumerNode));
    if (consumerNode == NULL) {
        return EC_NOMEMORY;
    }

    UtilsListInit(&consumerNode->node);
    consumerNode->consumer = consumer;
    MUTEX_Lock(broadcast->feature->mutex);
    ConsumerNode *head = &relation->callbacks;
    UtilsListAdd(&head->node, &consumerNode->node);
    MUTEX_Unlock(broadcast->feature->mutex);
    return EC_SUCCESS;
}

static Consumer *ModifyConsumer(IUnknown *iUnknown, const Topic *topic, Consumer *oldConsumer, Consumer *newConsumer)
{
    if (iUnknown == NULL || topic == NULL || oldConsumer == NULL || newConsumer == NULL) {
        return NULL;
    }

    PubSubImplement *broadcast = GET_OBJECT(iUnknown, PubSubImplement, iUnknown);
    if (broadcast->feature == NULL || broadcast->feature->GetRelation == NULL) {
        return NULL;
    }

    Relation *relation = broadcast->feature->GetRelation(broadcast->feature, topic);
    if (relation == NULL) {
        return NULL;
    }

    MUTEX_Lock(broadcast->feature->mutex);
    ConsumerNode *item = NULL;
    UTILS_DL_LIST_FOR_EACH_ENTRY(item, &relation->callbacks.node, ConsumerNode, node) {
        if (item->consumer->Equal(item->consumer, oldConsumer)) {
            Consumer *older = item->consumer;
            item->consumer = newConsumer;
            MUTEX_Unlock(broadcast->feature->mutex);
            return older;
        }
    }
    MUTEX_Unlock(broadcast->feature->mutex);
    return NULL;
}

static Consumer *Unsubscribe(IUnknown *iUnknown, const Topic *topic, const Consumer *consumer)
{
    if (iUnknown == NULL || topic == NULL || consumer == NULL) {
        return NULL;
    }

    PubSubImplement *broadcast = GET_OBJECT(iUnknown, PubSubImplement, iUnknown);
    if (broadcast->feature == NULL || broadcast->feature->GetRelation == NULL) {
        return NULL;
    }

    Relation *relation = broadcast->feature->GetRelation(broadcast->feature, topic);
    if (relation == NULL) {
        return NULL;
    }
    MUTEX_Lock(broadcast->feature->mutex);
    ConsumerNode *item = NULL;
    UTILS_DL_LIST_FOR_EACH_ENTRY(item, &relation->callbacks.node, ConsumerNode, node) {
        if (item->consumer->Equal(item->consumer, consumer)) {
            UtilsListDelete(&item->node);
            break;
        }
    }
    MUTEX_Unlock(broadcast->feature->mutex);
    if (item == &relation->callbacks || item == NULL) {
        return NULL;
    }
    Consumer *oldConsumer = item->consumer;
    SAMGR_Free(item);
    return oldConsumer;
}

static BOOL Publish(IUnknown *iUnknown, const Topic *topic, uint8 *data, int16 len)
{
    PubSubImplement *broadcast = GET_OBJECT(iUnknown, PubSubImplement, iUnknown);
    PubSubFeature *feature = broadcast->feature;
    if (feature == NULL) {
        return FALSE;
    }

    Request request = {MSG_PUBLISH, 0, NULL, *(uint32 *)topic};
    if (data != NULL && len > 0) {
        request.data = (uint8 *)SAMGR_Malloc(len);
        if (request.data == NULL) {
            return FALSE;
        }
        request.len = len;
        // There is no problem, the request.data length is equal the input data length.
        (void)memcpy_s(request.data, request.len, data, len);
    }

    if (!ImmediatelyPublish(feature, topic, &request)) {
        (void)SAMGR_Free(request.data);
        request.data = NULL;
        request.len = 0;
        return FALSE;
    }
    return TRUE;
}

static BOOL ImmediatelyPublish(PubSubFeature *feature, const Topic *topic, const Request *request)
{
    if (feature->GetRelation == NULL) {
        return FALSE;
    }

    Relation *relation = feature->GetRelation(feature, topic);
    if (relation == NULL) {
        return FALSE;
    }

    if (UtilsListEmpty(&relation->callbacks.node)) {
        return FALSE;
    }

    BOOL needAync = FALSE;
    ConsumerNode *item = NULL;
    uint32 *token = NULL;
    MUTEX_Lock(feature->mutex);
    UTILS_DL_LIST_FOR_EACH_ENTRY(item, &relation->callbacks.node, ConsumerNode, node) {
        if (item->consumer->identity == NULL) {
            needAync = TRUE;
            continue;
        }

        Response response = {item->consumer, 0};
        int ret = SAMGR_SendSharedDirectRequest(item->consumer->identity, request, &response, &token, DefaultHandle);
        if (ret != EC_SUCCESS) {
            needAync = FALSE;
            break;
        }
    }
    if (needAync) {
        token = SAMGR_SendSharedRequest(&feature->identity, request, token, NULL);
    }
    MUTEX_Unlock(feature->mutex);
    return (token != NULL);
}

static void DefaultHandle(const Request *request, const Response *response)
{
    Consumer *consumer = (Consumer *)response->data;
    if (consumer == NULL || consumer->Notify == NULL || g_pubSubImplement.feature == NULL) {
        return;
    }

    // wait ImmediatelyPublish finished.
    MUTEX_Lock(g_pubSubImplement.feature->mutex);
    MUTEX_Unlock(g_pubSubImplement.feature->mutex);
    Topic topic = request->msgValue;
    consumer->Notify(consumer, &topic, request);
}