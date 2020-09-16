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

#include "client/lite_wms_client.h"
#include "common/lite_wm_type.h"
#include "graphic_log.h"
#include "samgr_lite.h"

extern "C" void __attribute__((weak)) HOS_SystemInit(void)
{
    SAMGR_Bootstrap();
}

namespace OHOS {
bool LiteWMSClient::InitLiteWMSClient()
{
    HOS_SystemInit();
    if (proxy_ == nullptr) {
        IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(SERVICE_NAME);
        if (iUnknown == nullptr) {
            GRAPHIC_LOGE("iUnknown is NULL");
            return false;
        }
        (void)iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&proxy_);
        if (proxy_ == nullptr) {
            GRAPHIC_LOGE("QueryInterface failed!");
            return false;
        }
    }
    return true;
}
}