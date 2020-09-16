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
#ifndef LITE_ENDPOINT_H
#define LITE_ENDPOINT_H

#include <stddef.h>
#include "policy_define.h"
#include "common.h"
#include "iproxy_server.h"
#include "default_client.h"
#include "token_bucket.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define SAMGR_HANDLE 0
#define SAMGR_TOKEN 0
#define SAMGR_COOKIE 0
#define MAX_DATA_LEN 0x100
#define MIN_DATA_LEN 0x40

typedef enum ResourceID {
    RES_ENDPOINT,
    RES_FEATURE,
    RES_BUTT,
} ResourceID;

typedef enum OptionID {
    OP_GET,
    OP_POST,
    OP_PUT,
    OP_DELETE,
} OptionID;
typedef struct Endpoint Endpoint;
typedef int (*RegisterIdentity)(const char *service, const char *feature, SvcIdentity *identity,
                                PolicyTrans **policy, uint32 *policyNum);
typedef int (*RegisterEndpoint)(const IpcContext *context, SvcIdentity *identity);
struct Endpoint {
    const char *name;
    IpcContext *context;
    Vector routers;
    ThreadId boss;
    uint32 deadId;
    int running;
    SvcIdentity identity;
    RegisterEndpoint registerEP;
    TokenBucket bucket;
};

int SAMGR_RegisterRegisterIdentity(RegisterIdentity action);
Endpoint *SAMGR_CreateEndpoint(const char *name, RegisterEndpoint registry);
int SAMGR_AddRouter(Endpoint *endpoint, const SaName *saName, const Identity *id, IUnknown *proxy);
int SAMGR_ProcPolicy(const Endpoint *endpoint, const SaName *saName, int token);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_ENDPOINT_H
