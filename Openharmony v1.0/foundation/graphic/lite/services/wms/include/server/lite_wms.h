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

#ifndef GRAPHIC_LITE_LITE_WMS_H
#define GRAPHIC_LITE_LITE_WMS_H

#include "common/lite_wm_type.h"
#include "geometry2d.h"
#include "liteipc_adapter.h"
#include "serializer.h"

namespace OHOS {
class LiteWMS {
public:
    static LiteWMS* GetInstance()
    {
        static LiteWMS wms;
        return &wms;
    }

    static void WMSRequestHandle(int funcId, void *origin, IpcIo *req, IpcIo *reply);
private:
    LiteWMS() {};
    ~LiteWMS() {}
    static int SurfaceRequestHandler(const IpcContext* context, void *ipcMsg, IpcIo *io, void *arg);

    void GetSurface(IpcIo *req, IpcIo *reply);
    void Show(IpcIo *req, IpcIo *reply);
    void Hide(IpcIo *req, IpcIo *reply);
    void RaiseToTop(IpcIo *req, IpcIo *reply);
    void LowerToBottom(IpcIo *req, IpcIo *reply);
    void MoveTo(IpcIo *req, IpcIo *reply);
    void Resize(IpcIo *req, IpcIo *reply);
    void Update(IpcIo *req, IpcIo *reply);
    void CreateWindow(IpcIo *req, IpcIo *reply);
    void RemoveWindow(IpcIo *req, IpcIo *reply);
    void GetEventData(IpcIo *req, IpcIo *reply);
    void Screenshot(IpcIo *req, IpcIo *reply);
};
}
#endif
