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

#ifndef FOUNDATION_APP_MANAGER_H
#define FOUNDATION_APP_MANAGER_H

#include <vector>

#include "app_record.h"
#include "bundle_info.h"
#include "client/app_spawn_client.h"
#include "nocopyable.h"

namespace OHOS {
class AppManager : public NoCopyable {
public:
    static AppManager &GetInstance()
    {
        static AppManager instance;
        return instance;
    }
    ~AppManager() = default;
    AppRecord *StartAppProcess(const BundleInfo &bundleInfo);
    AbilityMsStatus TerminateAppProcess(const char *bundleName);
    const AppRecord *GetAppRecordByToken(uint64_t token, pid_t callingPid);
    AppRecord *GetAppRecordByBundleName(const char *bundleName);
    void RemoveAppRecord(const AppRecord &appRecord);
    void RemoveAppRecord(const char *bundleName);
private:
    AppManager() = default;
    AppSpawnClient spawnClient_;
    std::vector<AppRecord *> appRecords_;
};
} // namespace OHOS
#endif // FOUNDATION_APP_MANAGER_H
