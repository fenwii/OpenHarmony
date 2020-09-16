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

#ifndef GRAPHIC_LITE_LITE_WMS_CLIENT_H
#define GRAPHIC_LITE_LITE_WMS_CLIENT_H

#include <unistd.h>
#include <iunknown.h>
#include <iproxy_server.h>
#include <iproxy_client.h>

namespace OHOS {
static const int32_t DEFAULT_IPC_SIZE = 100;

class LiteWMSClient {
public:
    static LiteWMSClient* GetInstance()
    {
        static LiteWMSClient client;
        return &client;
    }

    bool InitLiteWMSClient();

    IClientProxy* GetClientProxy()
    {
        return proxy_;
    }
private:
    LiteWMSClient() : proxy_(nullptr){}
    ~LiteWMSClient() {}

    IClientProxy* proxy_;
};
}
#endif