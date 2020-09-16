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

#include "client/lite_wm_requestor.h"
#include "client/lite_wms_client.h"
#include "graphic_log.h"
#include "input_event_info.h"
#include "common/screen_device_proxy.h"
#include "surface_impl.h"

namespace OHOS {
LiteWMRequestor::LiteWMRequestor() : proxy_(nullptr), listener_(nullptr), surface_(nullptr), sid_({})
{
    proxy_ = LiteWMSClient::GetInstance()->GetClientProxy();
}

int LiteWMRequestor::Callback(void* owner, int code, IpcIo* reply)
{
    if (code != 0) {
        GRAPHIC_LOGE("callback error, code = %d", code);
        return -1;
    }

    if (owner == nullptr) {
        return -1;
    }

    CallBackPara* para = (CallBackPara*)owner;
    switch (para->funcId) {
        case LiteWMS_CreateWindow: {
            LiteWinRequestor** requestor = (LiteWinRequestor**)(para->data);
            int32_t id = IpcIoPopInt32(reply);
            GRAPHIC_LOGI("CreateWindow, id=%d", id);
            if (id == INVALID_WINDOW_ID) {
                *requestor = nullptr;
            } else {
                *requestor = new LiteWinRequestor(id);
            }
            break;
        }
        case LiteWMS_GetEventData: {
            uint32_t size;
            DeviceData* data = static_cast<DeviceData*>(IpcIoPopFlatObj(reply, &size));
            DeviceData* retData = (DeviceData*)(para->data);
            if (data != nullptr && retData != nullptr) {
                *retData = *data;
            }
            break;
        }
        default:
            break;
    }
    return 0;
}

LiteWinRequestor* LiteWMRequestor::CreateWindow(const LiteWinConfig& config)
{
    IpcIo io;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&io, tmpData, DEFAULT_IPC_SIZE, 0);
    IpcIoPushFlatObj(&io, &config, sizeof(LiteWinConfig));

    LiteWinRequestor* requestor = nullptr;
    CallBackPara para = {};
    para.funcId = LiteWMS_CreateWindow;
    para.data = &requestor;
    uint32_t ret = proxy_->Invoke(proxy_, LiteWMS_CreateWindow, &io, &para, Callback);
    if (ret != 0) {
        GRAPHIC_LOGE("CreateWindow failed, ret=%d", ret);
    }

    return requestor;
}

void LiteWMRequestor::RemoveWindow(int32_t id)
{
    IpcIo io;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&io, tmpData, DEFAULT_IPC_SIZE, 0);
    IpcIoPushInt32(&io, id);

    uint32_t ret = proxy_->Invoke(proxy_, LiteWMS_RemoveWindow, &io, NULL, Callback);
    if (ret != 0) {
        GRAPHIC_LOGE("RemoveWindow failed, ret=%d", ret);
    }
}

void LiteWMRequestor::GetEventData(DeviceData* data)
{
    IpcIo io;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&io, tmpData, DEFAULT_IPC_SIZE, 0);

    CallBackPara para = {};
    para.funcId = LiteWMS_GetEventData;
    para.data = data;
    (void)proxy_->Invoke(proxy_, LiteWMS_GetEventData, &io, &para, Callback);
}

int LiteWMRequestor::SurfaceRequestHandler(const IpcContext* context, void* ipcMsg, IpcIo* io, void* arg)
{
    SurfaceImpl* surface = (SurfaceImpl*)arg;
    if (surface == nullptr) {
        return 0;
    }
    surface->DoIpcMsg(ipcMsg, io);
    return 0;
}

void LiteWMRequestor::OnBufferAvailable()
{
    GRAPHIC_LOGD("OnBufferAvailable");
    if (surface_ != nullptr) {
        SurfaceBuffer* buffer = surface_->AcquireBuffer();
        if (buffer != nullptr) {
            uint8_t* virAddr = (uint8_t*)buffer->GetVirAddr();
            uint32_t size = buffer->GetSize();
            if (listener_ != nullptr && virAddr != nullptr) {
                listener_->OnScreenshotEnd(virAddr, size);
            }
            surface_->ReleaseBuffer(buffer);
        }
        UnRegisteIpcCallback(sid_);
        delete surface_;
        surface_ = nullptr;
    }
}

void LiteWMRequestor::Screenshot()
{
    if (surface_ != nullptr || listener_ == nullptr) {
        return;
    }

    surface_ = Surface::CreateSurface();
    if (surface_ == nullptr) {
        return;
    }

    surface_->SetWidthAndHeight(ScreenDeviceProxy::GetInstance()->GetScreenWidth(),
                                ScreenDeviceProxy::GetInstance()->GetScreenHeight());
    surface_->SetFormat(IMAGE_PIXEL_FORMAT_ARGB1555);
    surface_->SetUsage(1);
    surface_->RegisterConsumerListener(*this);

    int32_t ret = RegisteIpcCallback(SurfaceRequestHandler, 0, IPC_WAIT_FOREVER, &sid_, surface_);
    if (ret != LITEIPC_OK) {
        GRAPHIC_LOGE("CalculatorGetAnonymousFunc, RegisteIpcCallback failed.");
        delete surface_;
        surface_ = nullptr;
        return;
    }

    IpcIo io;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&io, tmpData, DEFAULT_IPC_SIZE, 1);
    IpcIoPushSvc(&io, &sid_);
    ret = proxy_->Invoke(proxy_, LiteWMS_Screenshot, &io, NULL, NULL);
    if (ret != 0) {
        GRAPHIC_LOGE("Screenshot failed, ret=%d", ret);
    }
}
} // namespace OHOS