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
#ifndef OHOS_CAMERA_IMPL_H
#define OHOS_CAMERA_IMPL_H

#include "camera.h"
#include "camera_ability.h"
#include "camera_device.h"
#include "camera_state_callback.h"

namespace OHOS {
namespace Media {
class CameraImpl : public Camera {
public:
    CameraImpl() = delete;
    CameraImpl(std::string &id, const CameraAbility *ability);
    ~CameraImpl() = default;

    std::string GetCameraId() override;
    const CameraConfig *GetCameraConfig() const override;
    FrameConfig *GetFrameConfig(int32_t type) override;

    void Configure(CameraConfig &config) override;
    void Release() override;

    int32_t TriggerLoopingCapture(FrameConfig &frameConfig) override;
    void StopLoopingCapture() override;
    int32_t TriggerSingleCapture(FrameConfig &frameConfig) override;

    const CameraAbility *GetAbility();
    void OnCreate(CameraDevice *device);
    void OnCreateFailed();
    void RegistCb(CameraStateCallback &callback, EventHandler &handler);

private:
    std::string id_;
    std::list<FrameConfig *> frameConfigs_;
    CameraConfig *config_ = nullptr;
    CameraStateCallback *stateCb_ = nullptr;
    EventHandler *handler_ = nullptr;
    const CameraAbility *ability_ = nullptr;
    CameraDevice *device_ = nullptr;
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_IMPL_H
