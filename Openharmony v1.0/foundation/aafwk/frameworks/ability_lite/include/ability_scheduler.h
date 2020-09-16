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

#ifndef OHOS_ABILITY_SCHEDULER_H
#define OHOS_ABILITY_SCHEDULER_H

#include <app_info.h>

#include "ability_event_handler.h"
#include "nocopyable.h"
#include "liteipc_adapter.h"
#include "serializer.h"
#include "want.h"

namespace OHOS {
class Scheduler {
public:
    virtual ~Scheduler() = default;

    /* perform application start and stop */
    virtual void PerformAppInit(const AppInfo& appInfo) = 0;
    virtual void PerformAppExit() = 0;

    /* perform transact ability lifecycle state */
    virtual void PerformTransactAbilityState(const Want &want, int state, uint64_t token, int abilityType) = 0;
    /* perform connect ability */
    virtual void PerformConnectAbility(const Want &want, uint64_t token) = 0;
    virtual void PerformDisconnectAbility(const Want &want, uint64_t token) = 0;
    /* perform dump ability info */
    virtual void PerformDumpAbility(const Want &want, uint64_t token) = 0;
};

class AbilityScheduler : public NoCopyable {
public:
    AbilityScheduler() = delete;
    AbilityScheduler(AbilityEventHandler &eventHandler, Scheduler &scheduler);
    ~AbilityScheduler() override = default;

    static int32_t AmsCallback(const IpcContext* context, void *ipcMsg, IpcIo *data, void *arg);

private:
    void PerformAppInit(const AppInfo& appInfo);
    void PerformTransactAbilityState(const Want &want, int state, uint64_t token, int abilityType);
    void PerformConnectAbility(const Want &want, uint64_t token);
    void PerformDisconnectAbility(const Want &want, uint64_t token);
    void PerformAppExit();
    void PerformDumpAbility(const Want &want, uint64_t token);
    static void ClearIpcMsg(void *ipcMsg);

    AbilityEventHandler &eventHandler_;
    Scheduler &scheduler_;
};
} // namespace OHOS
#endif // OHOS_ABILITY_SCHEDULER_H
