/*
  Copyright (c) 2020 Huawei Device Co., Ltd.
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

#ifndef OHOS_ABILITY_DUMP_TASK_H
#define OHOS_ABILITY_DUMP_TASK_H

#include "ability_task.h"
#include "ability_mgr_context.h"
#include "client/ability_dump_client.h"

namespace OHOS {
class AbilityDumpTask : public AbilityTask {
public:
    AbilityDumpTask(AbilityMgrContext *context, const AbilityDumpClient *client);
    ~AbilityDumpTask() override = default;

    AbilityMsStatus Execute() override;
private:
    const AbilityDumpClient *client_ { nullptr };
};
}  // namespace OHOS
#endif  // OHOS_ABILITY_DUMP_TASK_H
