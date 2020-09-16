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

#ifndef OHOS_IAM_PERMLITE_FEATURE_H
#define OHOS_IAM_PERMLITE_FEATURE_H

#include "feature.h"
#include "iunknown.h"
#include "pms_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct PmsInnerApi {
    INHERIT_IUNKNOWN;
    int (*CheckPermission)(int taskID, const char *permissionName);
    int (*QueryPermission)(const char *identifier, PermissionSaved **permissions, int *permNum);
    int (*GrantPermission)(const char *identifier, const char *permName);
    int (*RevokePermission)(const char *identifier, const char *permName);
    int (*GrantRuntimePermission)(int taskID, const char *permissionName);
    int (*RequestPermission)(int taskID, const char *permissionName);
} PmsInnerApi;

typedef struct PmsInner {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(PmsInnerApi);
    Identity identity;
} PmsInner;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // OHOS_IAM_PERMLITE_FEATURE_H