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

#ifndef OHOS_ABILITY_CONNECT_TASK_H
#define OHOS_ABILITY_CONNECT_TASK_H

#include "ability_task.h"

namespace OHOS {
class AbilityMgrContext;

class AbilityConnectTask : public AbilityTask {
public:
    AbilityConnectTask(AbilityMgrContext *context, const Want &want, const SvcIdentity &identity, uint64_t token);
    ~AbilityConnectTask() override = default;

    AbilityMsStatus Execute() override;
private:
    AbilityMsStatus PerformConnectTask(PageAbilityRecord *service);

    Want want_;
    SvcIdentity connectSid_;
    uint64_t token_;
};
}  // namespace OHOS

#endif  // OHOS_ABILITY_CONNECT_TASK_H
