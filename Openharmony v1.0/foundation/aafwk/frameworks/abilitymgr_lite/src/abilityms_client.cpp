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

#include "abilityms_client.h"

#include "ability_errors.h"
#include "ability_service_interface.h"
#include "liteipc_adapter.h"
#include "log.h"
#include "samgr_lite.h"
#include "serializer.h"
#include "want_utils.h"

namespace OHOS {
const unsigned int ERROR_SLEEP_TIMES = 300000;
const unsigned int RETRY_TIMES = 20;

bool AbilityMsClient::Initialize() const
{
    if (amsProxy_ != nullptr) {
        return true;
    }
    int retry = RETRY_TIMES;
    while (retry--) {
        IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(AMS_SERVICE, AMS_FEATURE);
        if (iUnknown == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "iUnknown is null");
            usleep(ERROR_SLEEP_TIMES); // sleep 300ms
            continue;
        }

        (void)iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&amsProxy_);
        if (amsProxy_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "ams proxy is null");
            usleep(ERROR_SLEEP_TIMES); // sleep 300ms
            continue;
        }

        return true;
    }

    return false;
}

int AbilityMsClient::SchedulerLifecycleDone(uint64_t token, int state) const
{
    if (amsProxy_ == nullptr) {
        return PARAM_NULL_ERROR;
    }
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushUint64(&req, token);
    IpcIoPushInt32(&req, state);
    return amsProxy_->Invoke(amsProxy_, ABILITY_TRANSACTION_DONE, &req, nullptr, nullptr);
}

int AbilityMsClient::ScheduleAms(const Want *want, uint64_t token, const SvcIdentity *sid, int commandType) const
{
    if (amsProxy_ == nullptr) {
        return PARAM_NULL_ERROR;
    }
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, 3);
    if (token != 0) {
        IpcIoPushUint64(&req, token);
    }
    if (sid != nullptr) {
        IpcIoPushSvc(&req, sid);
    }
    if (want != nullptr && !SerializeWant(&req, want)) {
        return SERIALIZE_ERROR;
    }
    return amsProxy_->Invoke(amsProxy_, commandType, &req, nullptr, nullptr);
}
} //  namespace OHOS
