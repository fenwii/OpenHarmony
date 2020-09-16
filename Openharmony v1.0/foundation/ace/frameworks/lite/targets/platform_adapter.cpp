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

#include "platform_adapter.h"
#include <cstdlib>
#include "acelite_config.h"
#if (defined(__LINUX__) || defined(__LITEOS__))
#include "ace_ability.h"
#endif
#include "ace_log.h"
#include "ace_version.h"
#include "js_fwk_common.h"

namespace OHOS {
namespace ACELite {
void PrintVersionTrace()
{
#ifdef TARGET_SIMULATOR
    // output version trace on simulator
    HILOG_DEBUG(HILOG_MODULE_ACE, "ACELite version: %s", ACEVersion::GetStr());
    HILOG_DEBUG(HILOG_MODULE_ACE, "ACELite commit: %s", ACEVersion::GetCommit());
    HILOG_DEBUG(HILOG_MODULE_ACE, "ACELite build stamp: %s", ACEVersion::GetTimeStamp());
#endif // TARGET_SIMULATOR
}

void SetEngineSnapshotMode(bool &mode)
{
#ifndef TARGET_SIMULATOR
    mode = true;
#else
    mode = false;
#endif
}

void SetEngineSnapshotModeManually(bool &mode)
{
#ifndef TARGET_SIMULATOR
    // if not startting debugger, on real device, give a chance to use JS mode manually
    mode = !(IsFileExisted(RUNTIME_MODE_FILE_PATH));
#endif // TARGET_SIMULATOR
}

#ifdef FEATURE_TERMINATE_ABILITY
extern "C" int TerminateAbility(uint16_t token);
#endif
void Terminate(uint16_t token)
{
#ifndef TARGET_SIMULATOR // no AMS support on PC simulator
#ifdef FEATURE_TERMINATE_ABILITY
    (void)TerminateAbility(token);
#else
    AceAbility::TerminateSelf();
#endif
#endif
}

void Srand(unsigned seed)
{
#ifdef TARGET_SIMULATOR
    srand(seed);
#endif // TARGET_SIMULATOR
}
} // namespace ACELite
} // namespace OHOS
