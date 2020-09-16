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
#include "sa_store.h"
#include <ohos_errno.h>
#include <securec.h>
#include "common.h"
#include "memory_adapter.h"

#define GROW_STEP 4
#define MAX_SA_NUM 300
static void FreeTreeNode(SAStore *saStore, ListNode *node);
static void SASTORA_ClearServiceByHandle(SAStore *saStore, uint32 handle);
static inline ListNode *FindServiceByName(ListNode *curNode, const char *service)
{
    while (curNode != NULL) {
        if (strncmp(curNode->info.name, service, MAX_NAME_LEN) == 0) {
            break;
        }
        curNode = curNode->next;
    }
    return curNode;
}

static inline FeatureNode *FindFeatureByName(FeatureNode *curNode, const char *feature)
{
    while (curNode != NULL) {
        if ((feature == NULL && curNode->isDefault) ||
            (feature != NULL && strncmp(curNode->name, feature, MAX_NAME_LEN) == 0)) {
            break;
        }
        curNode = curNode->next;
    }
    return curNode;
}

int SASTORA_Save(SAStore *saStore, const char *service, const char *feature, const SvcIdentity *identity)
{
    if (saStore == NULL || service == NULL || identity == NULL) {
        return EC_INVALID;
    }

    ListNode *curNode = FindServiceByName(saStore->root, service);
    FeatureNode *fNode = (curNode == NULL) ? NULL : curNode->info.head;
    fNode = FindFeatureByName(fNode, feature);
    if (fNode != NULL) {
        return EC_SUCCESS;
    }

    if (saStore->saSize >= MAX_SA_NUM) {
        return EC_NOSPACE;
    }

    fNode = SAMGR_Malloc(sizeof(FeatureNode));
    if (fNode == NULL) {
        return EC_NOMEMORY;
    }

    fNode->token = identity->token;
    fNode->isDefault = feature == NULL;
    fNode->name[0] = 0;
    if (feature != NULL) {
        if (strcpy_s(fNode->name, MAX_NAME_LEN, feature) != EOK) {
            SAMGR_Free(fNode);
            return EC_INVALID;
        }
    }

    if (curNode == NULL) {
        curNode = SAMGR_Malloc(sizeof(ListNode));
        if (curNode == NULL) {
            SAMGR_Free(fNode);
            return EC_NOMEMORY;
        }
        if (strcpy_s(curNode->info.name, MAX_NAME_LEN, service) != EOK) {
            SAMGR_Free(fNode);
            SAMGR_Free(curNode);
            return EC_INVALID;
        }

        curNode->info.handle = identity->handle;
        curNode->info.head = NULL;
        curNode->next = saStore->root;
        saStore->root = curNode;
    }
    fNode->next = curNode->info.head;
    curNode->info.head = fNode;
    saStore->saSize++;
    return EC_SUCCESS;
}

int SASTORA_SaveHandleByPid(SAStore *saStore, PidHandle handle)
{
    PidHandle saved = {.handle = INVALID_INDEX};
    int index = SASTORA_FindHandleByPid(saStore, handle.pid, &saved);
    if (saved.handle == handle.handle) {
        return EC_SUCCESS;
    }
    if (index != INVALID_INDEX) {
        saStore->maps[index] = handle;
        return EC_SUCCESS;
    }

    if (saStore->mapSize <= saStore->mapTop) {
        PidHandle *newMap = (PidHandle *)SAMGR_Malloc(sizeof(PidHandle) * (saStore->mapSize + GROW_STEP));
        if (newMap == NULL) {
            return EC_NOMEMORY;
        }

        if (saStore->maps != NULL) {
            (void)memcpy_s(newMap, sizeof(PidHandle) * (saStore->mapSize + GROW_STEP),
                           saStore->maps, sizeof(PidHandle) * saStore->mapSize);
        }
        PidHandle *oldMap = saStore->maps;
        saStore->maps = newMap;
        saStore->mapSize += GROW_STEP;
        SAMGR_Free(oldMap);
    }
    int i;
    for (i = saStore->mapTop - 1; i >= 0; --i) {
        if (saStore->maps[i].pid < handle.pid) {
            break;
        }
        saStore->maps[i + 1] = saStore->maps[i];
    }
    saStore->maps[i + 1] = handle;
    ++(saStore->mapTop);
    return EC_SUCCESS;
}

int SASTORA_FindHandleByPid(SAStore *saStore, pid_t callingPid, PidHandle *handle)
{
    if (saStore == NULL || saStore->maps == NULL || handle == NULL) {
        return INVALID_INDEX;
    }
    int16 high = saStore->mapTop - 1;
    int16 low = 0;
    while (low <= high) {
        // binary search need div 2
        int16 mid = (high + low) / 2;
        if (saStore->maps[mid].pid == callingPid) {
            *handle = saStore->maps[mid];
            return mid;
        }
        if (saStore->maps[mid].pid < callingPid) {
            low = mid + 1;
            continue;
        }
        high = mid - 1;
    }
    return INVALID_INDEX;
}

PidHandle SASTORA_FindPidHandleByIpcHandle(const SAStore *saStore, uint32 handle)
{
    PidHandle pidHandle = {INVALID_INDEX, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX};
    if (saStore == NULL || saStore->maps == NULL) {
        return pidHandle;
    }
    int i;
    for (i = 0; i < saStore->mapTop; i++) {
        if (saStore->maps[i].handle == handle) {
            return saStore->maps[i];
        }
    }
    return pidHandle;
}

SvcIdentity SASTORA_Find(SAStore *saStore, const char *service, const char *feature)
{
    SvcIdentity identity = {(uint32)INVALID_INDEX, (uint32)INVALID_INDEX, (uint32)INVALID_INDEX};
    ListNode *curNode = FindServiceByName(saStore->root, service);
    if (curNode == NULL) {
        return identity;
    }

    identity.handle = curNode->info.handle;

    FeatureNode *featureNode = FindFeatureByName(curNode->info.head, feature);
    if (featureNode != NULL) {
        identity.token = featureNode->token;
    }
    return identity;
}

int SASTORA_ClearByPid(SAStore *saStore, pid_t pid)
{
    PidHandle pidHandle;
    int index = SASTORA_FindHandleByPid(saStore, pid, &pidHandle);
    if (index == INVALID_INDEX) {
        return EC_INVALID;
    }

    SASTORA_ClearServiceByHandle(saStore, pidHandle.handle);
    if (saStore->mapTop <= (index + 1)) {
        saStore->mapTop--;
        return EC_SUCCESS;
    }

    errno_t err = memmove_s(&saStore->maps[index], sizeof(PidHandle) * (saStore->mapTop - index),
                            &saStore->maps[index + 1], sizeof(PidHandle) * (saStore->mapTop - index - 1));
    if (err != EOK) {
        return EC_FAILURE;
    }
    saStore->mapTop--;
    return EC_SUCCESS;
}

static void SASTORA_ClearServiceByHandle(SAStore *saStore, uint32 handle)
{
    ListNode *node = saStore->root;
    ListNode *prev = NULL;
    while (node != NULL) {
        if (node->info.handle == handle) {
            ListNode *freeNode = node;
            if (prev != NULL) {
                prev->next = node->next;
                node = node->next;
            } else {
                saStore->root = node->next;
                node = node->next;
            }
            FreeTreeNode(saStore, freeNode);
            continue;
        }
        prev = node;
        node = node->next;
    }
}

static void FreeTreeNode(SAStore *saStore, ListNode *node)
{
    while (node->info.head != NULL) {
        FeatureNode *freeNode = node->info.head;
        node->info.head = node->info.head->next;
        SAMGR_Free(freeNode);
        saStore->saSize--;
    }
    SAMGR_Free(node);
}