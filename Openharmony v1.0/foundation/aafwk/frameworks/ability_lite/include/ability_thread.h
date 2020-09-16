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

#ifndef OHOS_ABILITY_THREAD_H
#define OHOS_ABILITY_THREAD_H

#include <ability.h>
#include <map>
#include <memory>

#include "abilityms_client.h"
#include "ability_scheduler.h"
#include "ability_event_handler.h"

namespace OHOS {
class AbilityThread : public Scheduler, public NoCopyable {
public:
    ~AbilityThread() override;
    static void ThreadMain(uint64_t token);

private:
    AbilityThread() = default;

    void PerformAppInit(const AppInfo &appInfo) override;
    void PerformAppExit() override;
    void PerformTransactAbilityState(const Want &want, int state, uint64_t token, int abilityType) override;
    void PerformConnectAbility(const Want &want, uint64_t token) override;
    void PerformDisconnectAbility(const Want &want, uint64_t token) override;
    void PerformDumpAbility(const Want &want, uint64_t token) override;

#ifdef ABILITY_WINDOW_SUPPORT
    static void *UITaskPost(void *arg);
    void InitUITaskEnv();
#endif
    void StartAbilityCallback(const Want &want);
    static void HandleLifecycleTransaction(Ability &ability, const Want &want, int state);
    void AttachBundle(uint64_t token);
    void Run();

    AbilityEventHandler *eventHandler_ { nullptr };
    AbilityScheduler *abilityScheduler_ { nullptr };
    std::map<uint64_t, Ability *> abilities_ {};
    SvcIdentity *identity_ { nullptr };
    std::list<void *> handle_ {};
    static bool isNativeApp_;
    static bool isAppRunning_;
    static bool isDisplayInited_;
};
} // namespace OHOS
#endif // OHOS_ABILITY_THREAD_H
