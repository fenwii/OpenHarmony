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

#ifndef PERM_DEFINE_H
#define PERM_DEFINE_H

#include "pms_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PKG_NAME_LEN 64

enum GrantTime {
    INUSE, ALWAYS
};

enum GrantType {
    USER_GRANT = 0,
    SYSTEM_GRANT = 1,
};

enum IsUpdate {
    FIRST_INSTALL = 0,
    UPDATE = 1,
};

enum IsRestricted {
    RESTRICTED = 0,
    NOT_RESTRICTED = 1,
};

typedef struct {
    char name[PERM_NAME_LEN];
    enum GrantType type;
    enum IsRestricted isRestricted;
} PermissionDef;

typedef struct {
    char name[PERM_NAME_LEN];
    char desc[PERM_DESC_LEN];
    enum GrantTime when;
} PermissionTrans;

typedef struct PermNode {
    PermissionSaved perm;
    struct PermNode *next;
} PNode;

typedef struct PermList {
    PNode *head;
} PList;

typedef struct TaskNode {
    int taskID;
    char pkgName[PKG_NAME_LEN];
    PermissionSaved *permList;
    int permNum;
    struct TaskNode *next;
} TNode;

typedef struct TaskList {
    TNode *head;
} TList;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // PERM_DEFINE_H