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

#ifndef OHOS_ABILITY_SERVICE_H
#define OHOS_ABILITY_SERVICE_H

#include <stdlib.h>

#include "ability_kit.h"
#include "ability_list.h"
#include "ability_record.h"
#include "ability_stack.h"
#include "adapter.h"
#include "js_app_host.h"
#include "nocopyable.h"

namespace OHOS {
struct AbilitySvcInfo {
    char *bundleName;
    char *path;
    void *data;
    uint16_t dataLength;
};

struct RegisterInfo {
    char *bundleName;
    SuccessCallback success;
    FailCallback fail;
};

class AbilityService : public NoCopyable {
public:
    static AbilityService& GetInstance()
    {
        static AbilityService instance;
        return instance;
    }
    ~AbilityService() override;
    uint8_t DumpAbilityInfo(char **abilities);
    void AbortAbility(const char *bundleName);
    int32_t RegisterReceiver(const char *bundleName, SuccessCallback success, FailCallback fail);
    int32_t UnregisterReceiver(const char *bundleName);
    int32_t SendMsgToPeerApp(bool isLocalMsg, const char *callingPkgName, const char *calledPkgName,
                             const uint8_t *msgBody, uint32_t length);
    void StartBundleTimer(void *arg);
    void StopBundleTimer();
    static void ForceStopAbilityProc(void *arg);
    void ServiceMsgProcess(MC_MSG_S *msg);
    AbilityState GetJsState(const char *bundleName) const;

private:
    AbilityService();
    void StartLauncher();
    void StartAbility(AbilitySvcInfo *info);
    int32_t TerminateAbility(uint16_t token);
    void PreCheckStartAbility(const char *bundleName, const char *path, const void *data, uint16_t dataLength);
    void CheckResponse(const char *bundleName, bool isAllow);
    void CreateAppTask(AbilityRecord *record);
    static uint16_t GenerateToken();
    void ForceStopAbility();
    void StopAbility();

    void OnStart(uint16_t token);
    void OnActive(uint16_t token);
    void OnBackground(uint16_t token);
    void OnDestroy(uint16_t token);
    void HandleButtonEvent();
    void DeleteRecordInfo(uint16_t token);
    bool SendMsgToLauncherAbility(const char *bundleName, AbilityExitReason reason, uint32_t id);
    bool SendMsgToJsAbility(ACELite::AbilityMsgId msgId, const AbilityRecord *record);
    void InnerSendMsg(AbilityRecord *record);
    int32_t SendMsg(FeatureAbilityDataInfo *dataInfo);
    void Register(RegisterInfo *info);
    void Unregister(const char *bundleName);

    AbilityList *abilityList_ { nullptr };
    AbilityStack *abilityStack_ { nullptr };
    bool isBackPressed_ { false };
    bool isLongTimeIdle_ { false };
    osTimerId_t bundleRspTimerID_ { nullptr };
    TimerDefineInfo bundleRspTimer_ { nullptr };
};
} // namespace OHOS
#endif  // OHOS_ABILITY_SERVICE_H
