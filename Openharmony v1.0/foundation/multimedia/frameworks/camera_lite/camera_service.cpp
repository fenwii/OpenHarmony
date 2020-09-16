/*
 * Copyright(c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "camera_service.h"
#include "media_log.h"

using namespace std;
namespace OHOS {
namespace Media {
const string g_mainCamera = "main";

CameraService::CameraService() {}

CameraService::~CameraService()
{
    if (ability_) {
        delete ability_;
    }

    if (device_) {
        device_->UnInitialize();
        delete device_;
    }
}

CameraService *CameraService::GetInstance()
{
    static CameraService instance;
    return &instance;
}

void CameraService::Initialize(CameraServiceCallback *callback)
{
    MEDIA_DEBUG_LOG("Camera service initializing.");
    cameraServiceCb_ = callback;
    // TODO: init camera devices asycronize
    InitCameraDevices();

    list<string> cameraList = {g_mainCamera};
    cameraServiceCb_->OnCameraServiceInitialized(cameraList);
}

const CameraAbility *CameraService::GetCameraAbility(std::string &cameraId)
{
    // TODO:fill ability
    if (cameraId == g_mainCamera && device_ != nullptr) {
        return ability_;
    } else {
        return nullptr;
    }
}

void CameraService::CreateCamera(string cameraId)
{
    if (cameraId != g_mainCamera) {
        MEDIA_ERR_LOG("This camera does not exists. (cameraId=%s)", cameraId.c_str());
        return;
    }
    cameraServiceCb_->OnCameraStatusChange(cameraId, CameraServiceCallback::CAMERA_STATUS_CREATED, device_);
}

int32_t CameraService::InitCameraDevices()
{
    /* Only one camera device now, support more camera in future */
    device_ = new (nothrow) CameraDevice;
    if (device_ == nullptr) {
        goto NEW_ERROR;
    }
    ability_ = new (nothrow) CameraAbility;
    if (ability_ == nullptr) {
        delete device_;
        device_ = nullptr;
        goto NEW_ERROR;
    }

    if (device_->Initialize(*ability_) != MEDIA_OK) {
        delete device_;
        delete ability_;
        device_ = nullptr;
        ability_ = nullptr;
        return MEDIA_ERR;
    }
    return MEDIA_OK;

NEW_ERROR:
    MEDIA_FATAL_LOG("New object failed.");
    return MEDIA_ERR;
}
} // namespace Media
} // namespace OHOS