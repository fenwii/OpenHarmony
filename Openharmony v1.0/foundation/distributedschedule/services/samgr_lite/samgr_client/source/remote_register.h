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
#ifndef LITE_REMOTE_REGISTER_H
#define LITE_REMOTE_REGISTER_H

#include "common.h"
#include "endpoint.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
typedef struct RemoteRegister RemoteRegister;
struct RemoteRegister {
    MutexId mtx;
    Endpoint *endpoint;
    Vector clients;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_REMOTE_REGISTER_H
