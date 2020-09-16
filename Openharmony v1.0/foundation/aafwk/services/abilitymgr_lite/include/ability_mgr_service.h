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

#ifndef OHOS_ABILITYMGRSERVICE_SERVICE_H
#define OHOS_ABILITYMGRSERVICE_SERVICE_H

#include "service.h"

#include "nocopyable.h"

namespace OHOS {
class AbilityMgrService : public Service {
public:
    static AbilityMgrService *GetInstance()
    {
        static AbilityMgrService instance;
        return &instance;
    }
    ~AbilityMgrService() = default;
private:
    AbilityMgrService();
    static const char *GetServiceName(Service *service);
    static BOOL ServiceInitialize(Service *service, Identity identity);
    static TaskConfig GetServiceTaskConfig(Service *service);
    static BOOL ServiceMessageHandle(Service *service, Request *request);

private:
    Identity identity_;
    DISALLOW_COPY_AND_MOVE(AbilityMgrService);
};
} // namespace OHOS
#endif // OHOS_ABILITYMGRSERVICE_SERVICE_H
