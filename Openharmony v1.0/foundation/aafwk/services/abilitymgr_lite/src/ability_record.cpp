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

#include "ability_record.h"

#include "adapter.h"
#include "securec.h"

namespace OHOS {
AbilityRecord::AbilityRecord()
    : abilityInfo_()
{
}

AbilityRecord::~AbilityRecord()
{
    AdapterFree(appName_);
    AdapterFree(appPath_);
    AdapterFree(appData_);
}

void AbilityRecord::SetAppName(const char *bundleName)
{
    AdapterFree(appName_);
    if (bundleName == nullptr) {
        return;
    }
    int len = strlen(bundleName);
    appName_ = reinterpret_cast<char *>(AdapterMalloc(len + 1));
    if (appName_ == nullptr) {
        return;
    }
    int ret = strncpy_s(appName_, len + 1, bundleName, len);
    if (ret != 0) {
        AdapterFree(appName_);
    }
}

void AbilityRecord::SetAppPath(const char *appPath)
{
    AdapterFree(appPath_);
    if (appPath == nullptr) {
        return;
    }
    int len = strlen(appPath);
    appPath_ = reinterpret_cast<char *>(AdapterMalloc(len + 1));
    if (appPath_ == nullptr) {
        return;
    }
    int ret = strncpy_s(appPath_, len + 1, appPath, len);
    if (ret != 0) {
        AdapterFree(appPath_);
    }
}

void AbilityRecord::SetAppData(const void *appData, uint16_t dataLength)
{
    AdapterFree(appData_);
    dataLength_ = 0;
    if (appData == nullptr || dataLength == 0) {
        return;
    }
    appData_ = reinterpret_cast<void *>(AdapterMalloc(dataLength));
    if (appData_ == nullptr) {
        return;
    }
    int ret = memcpy_s(appData_, dataLength, appData, dataLength);
    if (ret != 0) {
        AdapterFree(appData_);
        return;
    }
    dataLength_ = dataLength;
}

void AbilityRecord::CopyAbilityRecord(AbilityRecord &abilityRecord, AbilityRecord &newAbilityRecord)
{
    newAbilityRecord.SetAppName(abilityRecord.GetAppName());
    newAbilityRecord.SetAppPath(abilityRecord.GetAppPath());
    newAbilityRecord.SetAppData(abilityRecord.GetAppData(), abilityRecord.GetDataLength());
    newAbilityRecord.SetState(abilityRecord.GetState());
    newAbilityRecord.SetToken(abilityRecord.GetToken());
#ifdef APP_PLATFORM_WATCHGT
    newAbilityRecord.SetTaskId(abilityRecord.GetTaskId());
#endif
}
} // namespace OHOS
