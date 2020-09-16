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

#ifndef OHOS_ABILITY_HELPER_H
#define OHOS_ABILITY_HELPER_H

#include <sched.h>

#include "abilityms_log.h"
#include "abilityms_status.h"
#include "ability_state.h"
#include "bundle_info.h"
#include "want.h"

namespace OHOS {
class AbilityMsHelper {
public:
    static bool IsLauncherAbility(const char *bundleName);
    static bool IsAceAbility(const char *abilityName);
    static AbilityMsStatus SetLauncherWant(Want &want);
    static AbilityMsStatus SetKeepAliveWant(const BundleInfo &bundleInfo, Want &want);
#ifdef OHOS_DEBUG
    static std::string AbilityStateToString(State state);
#endif
    static bool IsLegalBundleName(const char *bundleName);
    static bool CheckVisiblePermission(pid_t callingUid, pid_t targetUid, bool isVisible);

    static const pid_t SYSTEM_UID = 0;
};
}
#endif // OHOS_ABILITY_HELPER_H
