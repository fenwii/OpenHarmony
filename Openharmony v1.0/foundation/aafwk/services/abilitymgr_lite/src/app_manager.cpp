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

#include "app_manager.h"

#include <inttypes.h>
#include <string.h>

#include "token_generate.h"
#include "util/abilityms_log.h"

namespace OHOS {
AppRecord *AppManager::StartAppProcess(const BundleInfo &bundleInfo)
{
    CHECK_NULLPTR_RETURN_PTR(bundleInfo.bundleName, "AppManager", "invalid argument");
    AppRecord *appRecord = GetAppRecordByBundleName(bundleInfo.bundleName);
    if (appRecord != nullptr) {
        PRINTI("AppManager", "%{public}s AppRecord is already exist", bundleInfo.bundleName);
        return appRecord;
    }
    uint64_t token = TokenGenerate::GenerateToken();
    appRecord = new AppRecord(bundleInfo, token);
    AbilityMsStatus status = spawnClient_.SpawnProcess(*appRecord);
    if (!status.IsOk()) {
        status.LogStatus();
        delete appRecord;
        return nullptr;
    }
    PRINTD("AppManager", "start app name:%{public}s, token: %{private}" PRIu64,
        appRecord->GetBundleInfo().bundleName, token);
    appRecords_.emplace_back(appRecord);
    return appRecord;
}

void AppManager::RemoveAppRecord(const AppRecord &appRecord)
{
    for (auto iterator = appRecords_.begin(); iterator != appRecords_.end();) {
        AppRecord *current = *iterator;
        if (current != nullptr && current->GetIdentityId() == appRecord.GetIdentityId()) {
            PRINTD("AppManager", "remove process %{private}" PRIu64, current->GetIdentityId());
            current->UnloadPermission();
            iterator = appRecords_.erase(iterator);
            delete current;
        } else {
            ++iterator;
        }
    }
}

AbilityMsStatus AppManager::TerminateAppProcess(const char *bundleName)
{
    AppRecord *current = GetAppRecordByBundleName(bundleName);
    if (current == nullptr) {
        PRINTI("AppManager", "app record is not find");
        return AbilityMsStatus::Ok();
    }
    // exit app process
    AbilityMsStatus status = current->AppExitTransaction();
    CHECK_RESULT(status);
    RemoveAppRecord(*current);
    return status;
}

void AppManager::RemoveAppRecord(const char *bundleName)
{
    CHECK_NULLPTR_RETURN(bundleName, "AppManager", "start");
    for (auto iterator = appRecords_.cbegin(); iterator != appRecords_.cend();) {
        const AppRecord *current = *iterator;
        if (current != nullptr && current->GetBundleInfo().bundleName != nullptr &&
            (strcmp(current->GetBundleInfo().bundleName, bundleName) == 0)) {
            PRINTD("AppManager", "remove process name:%{public}s", bundleName);
            current->UnloadPermission();
            iterator = appRecords_.erase(iterator);
            delete current;
        } else {
            ++iterator;
        }
    }
}

const AppRecord *AppManager::GetAppRecordByToken(uint64_t token, pid_t pid)
{
    for (const auto &appRecord : appRecords_) {
        if (appRecord != nullptr && appRecord->GetIdentityId() == token && appRecord->GetPid() == pid) {
            return appRecord;
        }
    }
    return nullptr;
}

AppRecord *AppManager::GetAppRecordByBundleName(const char *bundleName)
{
    CHECK_NULLPTR_RETURN_PTR(bundleName, "AppManager", "invalid argument");
    for (const auto &appRecord : appRecords_) {
        if (appRecord != nullptr && appRecord->GetBundleInfo().bundleName != nullptr &&
            (strcmp(appRecord->GetBundleInfo().bundleName, bundleName) == 0)) {
            return appRecord;
        }
    }
    return nullptr;
}
}
