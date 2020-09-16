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

#ifndef GRAPHIC_LITE_LITE_WM_REQUESTOR_H
#define GRAPHIC_LITE_LITE_WM_REQUESTOR_H

#include "client/lite_win_requestor.h"
#include "geometry2d.h"
#include "common/lite_wm_type.h"
#include <iproxy_client.h>
#include "client/iwindows_manager.h"
#include "liteipc_adapter.h"

namespace OHOS {
class LiteWMRequestor : public IBufferConsumerListener {
public:
    static LiteWMRequestor* GetInstance()
    {
        static LiteWMRequestor requestor;
        return &requestor;
    }
    static int Callback(void* owner, int code, IpcIo *reply);

    static int32_t WMRequestHandler(void *ipcMsg, IpcIo *data, void *arg);

    static int SurfaceRequestHandler(const IpcContext* context, void *ipcMsg, IpcIo *io, void *arg);
    virtual void OnBufferAvailable() override;

    LiteWinRequestor* CreateWindow(const LiteWinConfig& config);
    void RemoveWindow(int32_t id);
    void GetEventData(DeviceData* data);

    void Screenshot();
    void SetScreenshotListener(IWindowsManager::ScreenshotListener* listener)
    {
        listener_ = listener;
    }

private:
    LiteWMRequestor();
    ~LiteWMRequestor() {}
    IClientProxy* proxy_;

    IWindowsManager::ScreenshotListener* listener_;
    Surface* surface_;
    SvcIdentity sid_;
};
}
#endif