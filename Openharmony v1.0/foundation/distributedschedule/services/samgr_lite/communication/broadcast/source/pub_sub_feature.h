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

#ifndef LITE_PUB_SUB_FEATURE_H
#define LITE_PUB_SUB_FEATURE_H

#include "utils_list.h"
#include "message.h"
#include "feature.h"
#include "common.h"
#include "broadcast_interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct ConsumerNode {
    UTILS_DL_LIST node;
    Consumer *consumer;
} ConsumerNode;

typedef struct Relation {
    UTILS_DL_LIST node;
    ConsumerNode callbacks;
    Topic topic;
} Relation;
typedef struct PubSubFeature PubSubFeature;

struct PubSubFeature {
    INHERIT_FEATURE;
    Relation *(*GetRelation)(PubSubFeature *feature, const Topic *topic);
    MutexId mutex;
    Relation relations;
    Identity identity;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_PUB_SUB_FEATURE_H
