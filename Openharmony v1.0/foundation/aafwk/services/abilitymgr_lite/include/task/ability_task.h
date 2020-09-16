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

#ifndef OHOS_ABILITY_TASK_H
#define OHOS_ABILITY_TASK_H

#include "ability_stack_manager.h"
#include "util/abilityms_status.h"
#include "util/abilityms_log.h"

namespace OHOS {
class AbilityTask {
public:
    AbilityTask() = default;
    explicit AbilityTask(AbilityMgrContext *context) : abilityMgrContext_(context)
    {
    }
    virtual ~AbilityTask()
    {
        abilityMgrContext_ = nullptr;
    }

    virtual AbilityMsStatus Execute() = 0;

protected:
    AbilityMgrContext *abilityMgrContext_ { nullptr };
};
}  // OHOS

#endif  // OHOS_ABILITY_TASK_H
