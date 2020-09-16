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

#ifndef OHOS_ABILITYMS_STATUS_H
#define OHOS_ABILITYMS_STATUS_H

#include <string>

namespace OHOS {
class AbilityMsStatus {
public:
    AbilityMsStatus() : code_(OK) {}
    ~AbilityMsStatus() = default;
    static AbilityMsStatus Ok()
    {
        return AbilityMsStatus();
    }

    static AbilityMsStatus BmsQueryStatus(const char *msg)
    {
        return AbilityMsStatus(BMS_QUERY_NOT_FOUND, nullptr, msg);
    }

    static AbilityMsStatus AppTransanctStatus(const char *msg)
    {
        return AbilityMsStatus(APP_TRANSACT_ERROR, nullptr, msg);
    }

    static AbilityMsStatus TaskStatus(const char *key, const char *msg)
    {
        return AbilityMsStatus(ABILITY_TASK_ERROR, key, msg);
    }

    static AbilityMsStatus LifeCycleStatus(const char *msg)
    {
        return AbilityMsStatus(LIFE_CYCLE_ILLEGAL, nullptr, msg);
    }

    static AbilityMsStatus ProcessStatus(const char *msg)
    {
        return AbilityMsStatus(PROCESS_ERROR, nullptr, msg);
    }

    static AbilityMsStatus NoActiveAbilityStatus(const char *key, const char *msg)
    {
        return AbilityMsStatus(NO_ACTIVE_ABILITY, key, msg);
    }

    static AbilityMsStatus HelpStatus(const char *msg)
    {
        return AbilityMsStatus(ABILITY_HELP_ERROR, nullptr, msg);
    }

    static AbilityMsStatus DumpStatus(const char *msg)
    {
        return AbilityMsStatus(ABILITY_DUMP, nullptr, msg);
    }

    static AbilityMsStatus PermissionStatus(const char *msg)
    {
        return AbilityMsStatus(PERMISSION_DENIED, nullptr, msg);
    }

    void DumpAppend(const AbilityMsStatus &status)
    {
        if (code_ == ABILITY_DUMP) {
            state_ += status.state_;
        }
    }

    void DumpAppend(const char *msg)
    {
        if (code_ == ABILITY_DUMP) {
            state_ += msg;
        }
    }

    const char *Dump() const
    {
        if (code_ == ABILITY_DUMP) {
            return state_.c_str();
        }
        return "";
    }

    bool IsOk() const
    {
        return code_ == OK;
    }

    bool IsNoActiveAbility() const
    {
        return code_ == NO_ACTIVE_ABILITY;
    }

    bool IsProcessError() const
    {
        return code_ == PROCESS_ERROR;
    }

    bool IsTransactError() const
    {
        return code_ == APP_TRANSACT_ERROR;
    }

    void LogStatus() const;
private:
    enum StatusCode {
        OK = 0,
        BMS_QUERY_NOT_FOUND,
        PERMISSION_DENIED,
        ABILITY_TASK_ERROR,
        APP_TRANSACT_ERROR,
        LIFE_CYCLE_ILLEGAL,
        PROCESS_ERROR,
        NO_ACTIVE_ABILITY,
        ABILITY_HELP_ERROR,
        ABILITY_DUMP,
    };
    AbilityMsStatus(StatusCode code, const char *key, const char *msg);
    StatusCode code_ = OK;
    std::string state_;
    std::string key_;
};

#define CHECK_RESULT_LOG_CODE(status, code)  \
    do {                                     \
        if (!status.IsOk()) {                \
            status.LogStatus();              \
            return code;                     \
        }                                    \
    } while (0)

#define CHECK_RESULT_LOG(status)       \
    do {                               \
        if (!status.IsOk()) {          \
            status.LogStatus();        \
            return;                    \
        }                              \
    } while (0)

#define CHECK_RESULT(status)           \
    do {                               \
        if (!status.IsOk()) {          \
            return status;             \
        }                              \
    } while (0)
}
#endif // OHOS_ABILITY_CONST_H
