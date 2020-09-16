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

#ifndef OHOS_APP_SPAWN_CLIENT_H
#define OHOS_APP_SPAWN_CLIENT_H

#include "app_record.h"
#include "iproxy_client.h"
#include "util/abilityms_status.h"

namespace OHOS {
class AppSpawnClient {
public:
    AppSpawnClient() = default;
    ~AppSpawnClient() = default;
    AbilityMsStatus SpawnProcess(AppRecord &appRecord);
private:
    AbilityMsStatus Initialize();
    IClientProxy *spawnClient_ { nullptr };
};
}
#endif // OHOS_APP_SPAWN_CLIENT_H
