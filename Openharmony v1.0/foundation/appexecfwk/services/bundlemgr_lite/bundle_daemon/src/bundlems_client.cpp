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

#include "bundlems_client.h"

#include "bundle_daemon_interface.h"

namespace OHOS {
BundleMsClient::BundleMsClient(const SvcIdentity &svcIdentity)
    : svcIdentity_(svcIdentity)
{
}

int32 BundleMsClient::SendReply(int32 result)
{
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushInt32(&request, result);
    return Transact(nullptr, svcIdentity_, BDS_CALLBACK, &request, nullptr, LITEIPC_FLAG_ONEWAY, nullptr);
}
} // OHOS
