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

#include "client/wms_client.h"

#include "hos_errno.h"
#include "iproxy_client.h"
#ifdef ABILITY_WINDOW_SUPPORT
#include "lite_wm_type.h"
#endif
#include "liteipc_adapter.h"
#include "samgr_lite.h"
#include "util/abilityms_log.h"

namespace OHOS {
#ifdef ABILITY_WINDOW_SUPPORT
namespace {
    const unsigned long RETRY_SLEEP_TIMES = 200000; // sleep 200ms
}

void WMSClient::WaitUntilWmsReady()
{
    PRINTI("WMSClient", "wait for window manager service start");
    IClientProxy *wmsProxy = nullptr;
    while (wmsProxy == nullptr) {
        IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(SERVICE_NAME);
        if (iUnknown == nullptr) {
            usleep(RETRY_SLEEP_TIMES);
            continue;
        }
        int result = iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)(&wmsProxy));
        if (result != EC_SUCCESS || wmsProxy == nullptr) {
            usleep(RETRY_SLEEP_TIMES);
            continue;
        }
    }
    PRINTI("WMSClient", "get window manager service proxy success");
    wmsProxy->Release(reinterpret_cast<IUnknown *>(wmsProxy));
}
#endif
} // namespace OHOS
