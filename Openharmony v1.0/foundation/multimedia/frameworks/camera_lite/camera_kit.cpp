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
#include "camera_kit.h"
#include "camera_manager.h"
#include "pms_interface.h"

using namespace std;
namespace OHOS {
namespace Media {
CameraManager *cameraManager_ = nullptr;
CameraKit::CameraKit()
{
    cameraManager_ = CameraManager::GetInstance();
}

CameraKit::~CameraKit() {}

CameraKit *CameraKit::GetInstance()
{
    if (CheckPermission(0, "ohos.permission.CAMERA") != GRANTED) {
        MEDIA_WARNING_LOG("Process can not access camera.");
        return nullptr;
    }
    static CameraKit kit;
    return &kit;
}

list<string> CameraKit::GetCameraIds()
{
    return cameraManager_->GetCameraIds();
}

const CameraAbility *CameraKit::GetCameraAbility(string cameraId)
{
    return cameraManager_->GetCameraAbility(cameraId);
}

void CameraKit::RegisterCameraDeviceCallback(CameraDeviceCallback &callback, EventHandler &handler)
{
    cameraManager_->RegisterCameraDeviceCallback(callback, handler);
}

void CameraKit::UnregisterCameraDeviceCallback(CameraDeviceCallback &callback)
{
    cameraManager_->UnregisterCameraDeviceCallback(callback);
}

void CameraKit::CreateCamera(const string &cameraId, CameraStateCallback &callback, EventHandler &handler)
{
    cameraManager_->CreateCamera(cameraId, callback, handler);
}
} // namespace Media
} // namespace OHOS
