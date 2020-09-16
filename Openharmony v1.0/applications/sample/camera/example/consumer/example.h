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
#ifndef LITE_EXAMPLE_H
#define LITE_EXAMPLE_H

#include <iunknown.h>
#include <iproxy_server.h>
#include <iproxy_client.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define EXAMPLE_SERVICE "ex_service"
#define EXAMPLE_FEATURE "ex_feature"
typedef struct DefaultFeatureApi {
    INHERIT_SERVER_IPROXY;
    void (*SyncCall)(IUnknown *iUnknown);
} DefaultFeatureApi;

struct Payload {
    int id;
    const char *name;
    int value;
};
typedef void *IOwner;
typedef void (*INotifyFunc)(IOwner owner, const char *resp);
typedef struct ClientDemo {
    INHERIT_CLIENT_IPROXY;
    BOOL (*AsyncCall)(IUnknown *iUnknown, const char *buff);
    BOOL (*AsyncTimeCall)(IUnknown *iUnknown);
    BOOL (*SyncCall)(IUnknown *iUnknown, struct Payload *payload);
    BOOL (*AsyncCallBack)(IUnknown *iUnknown, const char *buff, IOwner notify, INotifyFunc handler);
} ClientDemo;
void DEMO_DestroyClient(const char *service, const char *feature, void *iproxy);
void *DEMO_CreatClient(const char *service, const char *feature, uint32 size);
void RunServiceTestCase(void);
void RunFeatureTestCase(void);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_EXAMPLE_H
