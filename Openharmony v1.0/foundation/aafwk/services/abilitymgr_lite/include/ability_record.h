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

#ifndef OHOS_ABILITY_RECORD_H
#define OHOS_ABILITY_RECORD_H

#ifdef APP_PLATFORM_WATCHGT
#include "cmsis_os.h"
#endif
#include "ability_info.h"
#include "ability_kit.h"
#include "ability_package_manager.h"

namespace OHOS {
class JsAppHost;

constexpr int FAIL_CALLBACK_ERRORCODE = 200;
class AbilityRecord {
public:
    AbilityRecord();
    ~AbilityRecord();

    void SetAppName(const char *appName);
    const char *GetAppName() const
    {
        return appName_;
    }

    void SetAppPath(const char *appPath);
    const char *GetAppPath() const
    {
        return appPath_;
    }

    void SetAppData(const void *appData, uint16_t dataLength);
    const void *GetAppData() const
    {
        return appData_;
    }

    void SetAbilityInfo(const AbilityInfo abilityInfo)
    {
        abilityInfo_ = abilityInfo;
    }

    AbilityInfo GetAbilityInfo() const
    {
        return abilityInfo_;
    }

    uint16_t GetDataLength() const
    {
        return dataLength_;
    }

    void SetState(const AbilityState state)
    {
        state_ = state;
    }

    AbilityState GetState() const
    {
        return state_;
    }

    bool IsAttached() const
    {
        if ((state_ == SCHEDULE_INACTIVE) || (state_ == SCHEDULE_ACTIVE) || (state_ == SCHEDULE_BACKGROUND)) {
            return true;
        }

        return false;
    }

    void SetToken(uint16_t token)
    {
        token_ = token;
    }
    uint16_t GetToken() const
    {
        return token_;
    }

#ifdef APP_PLATFORM_WATCHGT
    void SetTaskId(UINT32 taskId)
    {
        taskId_ = taskId;
    }

    UINT32 GetTaskId() const
    {
        return taskId_;
    }

    void SetMessageQueueId(const osMessageQueueId_t jsAppQueueId)
    {
        jsAppQueueId_ = jsAppQueueId;
    }

    const osMessageQueueId_t& GetMessageQueueId() const
    {
        return jsAppQueueId_;
    }
#endif

    void SetJsAppHost(const JsAppHost *jsAppHost)
    {
        jsAppHost_ = const_cast<JsAppHost *>(jsAppHost);
    }

    const JsAppHost *GetJsAppHost() const
    {
        return jsAppHost_;
    }

    void SetSuccessCallback(SuccessCallback success)
    {
        successCallback_ = success;
    }

    void TriggerSuccessCallback(void *data) const
    {
        if (successCallback_ != nullptr) {
            successCallback_(data);
        }
    }

    void SetFailCallback(FailCallback fail)
    {
        if (failCallback_ != nullptr) {
            failCallback_ = fail;
        }
    }

    void TriggerFailCallback(void *data, uint16_t dataLength)
    {
        if (failCallback_ != nullptr) {
            failCallback_(data, dataLength, FAIL_CALLBACK_ERRORCODE);
        }
    }

    void SetRegiterState(bool isRegister)
    {
        isRegister_ = isRegister;
    }

    bool GetRegiterState() const
    {
        return isRegister_;
    }

    static void CopyAbilityRecord(AbilityRecord &abilityRecord, AbilityRecord &newAbilityRecord);

private:
    char *appName_ { nullptr };
    char *appPath_ { nullptr };
    AbilityInfo abilityInfo_;
    void *appData_ { nullptr };
    uint16_t dataLength_ { 0 };
    AbilityState state_ { SCHEDULE_INITED };
    uint16_t token_ { 0 };
    bool isRegister_ { false };

#ifdef APP_PLATFORM_WATCHGT
    UINT32 taskId_ { 0 };
    osMessageQueueId_t jsAppQueueId_ { nullptr };
#endif
    JsAppHost *jsAppHost_ { nullptr };
    SuccessCallback successCallback_ { nullptr };
    FailCallback failCallback_ { nullptr };
};
} // namespace OHOS

#endif // OHOS_ABILITY_RECORD_H
