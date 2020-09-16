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

#include "client/lite_proxy_windows_manager.h"

#include "client/lite_wm_requestor.h"
#include "client/lite_wms_client.h"
#include "color.h"
#include "graphic_log.h"

namespace OHOS {
int LiteProxyWindowsManager::Init()
{
    GRAPHIC_LOGI("Init");
    LiteWMSClient::GetInstance()->InitLiteWMSClient();
    return 0;
}

IWindow* LiteProxyWindowsManager::CreateWindow(const LiteWinConfig& config)
{
    LiteWinRequestor* requstor = LiteWMRequestor::GetInstance()->CreateWindow(config);
    if (requstor == nullptr) {
        return nullptr;
    } else {
        return new LiteProxyWindow(requstor);
    }
}

void LiteProxyWindowsManager::RemoveWindow(IWindow* window)
{
    if (window != nullptr) {
        LiteWMRequestor::GetInstance()->RemoveWindow(window->GetWindowId());
        delete window;
    }
}

void LiteProxyWindowsManager::GetEventData(DeviceData* data)
{
    LiteWMRequestor::GetInstance()->GetEventData(data);
}

void LiteProxyWindowsManager::Screenshot()
{
    LiteWMRequestor::GetInstance()->Screenshot();
}

void LiteProxyWindowsManager::SetScreenshotListener(ScreenshotListener* listener)
{
    LiteWMRequestor::GetInstance()->SetScreenshotListener(listener);
}
}