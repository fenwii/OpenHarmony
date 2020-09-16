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
#ifndef LITE_SA_STORE_H
#define LITE_SA_STORE_H

#include <ohos_types.h>
#include <liteipc_adapter.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_NAME_LEN 16
typedef struct ServiceInfo ServiceInfo;
typedef struct FeatureNode FeatureNode;
typedef struct SAStore SAStore;
typedef struct ListNode ListNode;
typedef struct PidHandle PidHandle;
struct ServiceInfo {
    char name[MAX_NAME_LEN];
    uint32 handle;
    FeatureNode *head;
};

struct FeatureNode {
    char name[MAX_NAME_LEN];
    uint32 isDefault;
    uint32 token;
    FeatureNode *next;
};

struct SAStore {
    int saSize;
    ListNode *root;
    int16 mapSize;
    int16 mapTop;
    PidHandle *maps;
};

struct ListNode {
    ListNode *next;
    ServiceInfo info;
};

struct PidHandle {
    pid_t pid;
    uid_t uid;
    uint32 handle;
    uint32 deadId;
};

static inline void SASTORA_Init(SAStore *saStore)
{
    saStore->saSize = 0;
    saStore->root = NULL;
    saStore->mapTop = 0;
    saStore->mapSize = 0;
    saStore->maps = NULL;
}

int SASTORA_Save(SAStore *saStore, const char *service, const char *feature, const SvcIdentity *identity);
int SASTORA_SaveHandleByPid(SAStore *saStore, PidHandle handle);
int SASTORA_FindHandleByPid(SAStore *saStore, pid_t callingPid, PidHandle *handle);
SvcIdentity SASTORA_Find(SAStore *saStore, const char *service, const char *feature);
int SASTORA_ClearByPid(SAStore *saStore, pid_t pid);
PidHandle SASTORA_FindPidHandleByIpcHandle(const SAStore *saStore, uint32 handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_SA_STORE_H
