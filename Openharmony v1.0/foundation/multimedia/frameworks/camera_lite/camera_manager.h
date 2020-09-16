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
#ifndef OHOS_CAMERA_MANAGER_H
#define OHOS_CAMERA_MANAGER_H

#include <list>
#include <string>

#include "camera_ability.h"
#include "camera_device_callback.h"
#include "camera_state_callback.h"
#include "event_handler.h"

namespace OHOS {
namespace Media {
class CameraManager {
public:
    ~CameraManager() = default;
    static CameraManager *GetInstance();

    virtual std::list<std::string> GetCameraIds()
    {
        std::list<std::string> emptyList;
        return emptyList;
    }
    virtual const CameraAbility *GetCameraAbility(const std::string &cameraId)
    {
        return nullptr;
    }
    virtual void RegisterCameraDeviceCallback(CameraDeviceCallback &callback, EventHandler &handler) {}
    virtual void UnregisterCameraDeviceCallback(CameraDeviceCallback &callback) {}
    virtual void CreateCamera(const std::string &cameraId, CameraStateCallback &callback, EventHandler &handler) {}

protected:
    CameraManager() {}
};
} // namespace Media
} // namespace OHOS

#endif // OHOS_CAMERA_MANAGER_H
