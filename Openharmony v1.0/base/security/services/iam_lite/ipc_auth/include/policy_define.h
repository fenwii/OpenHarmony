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

#ifndef POLICY_DEFINE_H
#define POLICY_DEFINE_H

#define UID_SIZE 8
#define POLICY_SIZE 8

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct RegParams {
    char *service;
    char *feature;
    unsigned int uid;
    unsigned int pid;
} RegParams;

typedef struct AuthParams {
    char *providerService;
    char *providerfeature;
    unsigned int providerUid;
    unsigned int providerPid;
    unsigned int consumerUid;
    unsigned int consumerPid;
} AuthParams;

enum PolicyType {
    RANGE = 1,
    FIXED = 2,
    BUNDLENAME = 3
};

typedef struct PolicyTrans {
    enum PolicyType type;
    int fixedUid[UID_SIZE];
    int uidMin;
    int uidMax;
} PolicyTrans;

typedef struct IpcPolicy {
    enum PolicyType type;
    int fixedUid[UID_SIZE];
    int uidMin;
    int uidMax;
    char *bundleName;
} IpcPolicy;

typedef struct FeaturePolicy {
    char *feature;
    IpcPolicy policies[POLICY_SIZE];
} FeaturePolicy;

typedef struct PolicySetting {
    char *service;
    FeaturePolicy *features;
    int featureNum;
} PolicySetting;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // POLICY_DEFINE_H