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

#include "client/ability_dump_client.h"

#include "ability_kit_command.h"
#include "liteipc_adapter.h"
#include "securec.h"
#include "util/abilityms_log.h"

namespace OHOS {
AbilityDumpClient::AbilityDumpClient(const Want &want)
{
    if (want.element != nullptr) {
        SetWantElement(&want_, *(want.element));
    }
    if (want.data != nullptr) {
        SetWantData(&want_, want.data, want.dataLength);
    }
    if (want.sid != nullptr) {
        SetWantSvcIdentity(&want_, *(want.sid));
    }
}
AbilityDumpClient::~AbilityDumpClient()
{
    ClearWant(&want_);
}

const Want &AbilityDumpClient::GetWant() const
{
    return want_;
}

AbilityMsStatus AbilityDumpClient::AbilityDumpTransaction(const char *info) const
{
    if (want_.sid == nullptr) {
        return AbilityMsStatus::DumpStatus("null SvcIdentity");
    }
    PRINTD("AbilityThreadClient", "start");
    if (info == nullptr) {
        info = "";
    }
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, 1);
    BuffPtr buffPtr;
    buffPtr.buff = const_cast<char *>(info);
    buffPtr.buffSz = strlen(info) + 1;
    IpcIoPushDataBuff(&req, &buffPtr);
    if (Transact(nullptr, *(want_.sid), SCHEDULER_DUMP_ABILITY, &req, nullptr,
        LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::AppTransanctStatus("dump ability ipc error");
    }
    return AbilityMsStatus::Ok();
}
}
