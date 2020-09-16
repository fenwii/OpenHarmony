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

#include "util/abilityms_status.h"

#include "util/abilityms_log.h"

namespace OHOS {
AbilityMsStatus::AbilityMsStatus(StatusCode code, const char *key, const char *msg)
{
    code_ = code;
    if (key != nullptr) {
        key_ = key;
    }
    if (msg != nullptr) {
        state_ = msg;
    }
}

void AbilityMsStatus::LogStatus() const
{
    std::string result;
    switch (code_) {
        case OK:
            result = "success: ";
            break;
        case PERMISSION_DENIED:
            result = "permission denied: ";
            break;
        case BMS_QUERY_NOT_FOUND:
            result = "bms query not found: ";
            break;
        case ABILITY_TASK_ERROR:
            result = "task " + key_ + " exec failure: ";
            break;
        case APP_TRANSACT_ERROR:
            result = "app transanct failure: ";
            break;
        case LIFE_CYCLE_ILLEGAL:
            result = "life cycle illegal: ";
            break;
        case PROCESS_ERROR:
            result = "process exception: ";
            break;
        case NO_ACTIVE_ABILITY:
            result = "no active ability when " + key_ + ": ";
            break;
        case ABILITY_HELP_ERROR:
            result = "help failure: ";
            break;
        default:
            break;
    }
    result += state_;
    HILOG_ERROR(LOG_DOMAIN, "%s", result.c_str());
}
}
