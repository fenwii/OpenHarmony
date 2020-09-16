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

#ifndef OHOS_BUNDLE_MS_HOST_H
#define OHOS_BUNDLE_MS_HOST_H

#include "bundle_ms_feature.h"
#include "iproxy_server.h"
#include "iunknown.h"
#include "service.h"
#include "want.h"

namespace OHOS {
class BundleMsHost : private Service {
public:
    static BundleMsHost *GetInstance()
    {
        static BundleMsHost instance;
        return &instance;
    }
    ~BundleMsHost() = default;

private:
    BundleMsHost();

    Identity identity_ { 0 };
    static const char *GetServiceName(Service *service);
    static BOOL ServiceInitialize(Service *service, Identity identity);
    static TaskConfig GetServiceTaskConfig(Service *service);
    static BOOL ServiceMessageHandle(Service *service, Request *request);

    DISALLOW_COPY_AND_MOVE(BundleMsHost);
};
} // namespace OHOS
#endif // OHOS_BUNDLE_MS_HOST_H