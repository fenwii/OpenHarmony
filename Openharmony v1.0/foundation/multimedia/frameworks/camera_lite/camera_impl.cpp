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

#include "camera_impl.h"
#include "camera_service.h"
#include "media_log.h"

using namespace std;

namespace OHOS {
namespace Media {
CameraImpl::CameraImpl(std::string &id, const CameraAbility *ability)
{
    id_ = id;
    ability_ = ability;
}

string CameraImpl::GetCameraId()
{
    return id_;
}

const CameraConfig *CameraImpl::GetCameraConfig() const
{
    return config_;
}

FrameConfig *CameraImpl::GetFrameConfig(int32_t type)
{
    for (auto i : frameConfigs_) {
        if (i->GetFrameConfigType() == type) {
            return i;
        }
    }
    return nullptr;
}

void CameraImpl::Configure(CameraConfig &config)
{
    if (config_ != nullptr) {
        return;
    }

    if (config.GetFrameStateCb() == nullptr || config.GetEventHandler() == nullptr) {
        return;
    }

    int32_t ret = device_->SetCameraConfig(config);
    if (ret != MEDIA_OK) {
        handler_->Post([this, ret] { this->stateCb_->OnConfigureFailed(this->GetCameraId(), ret); });
        return;
    }
    config_ = &config;
    handler_->Post([this] { this->stateCb_->OnConfigured(*this); });
}

void CameraImpl::Release()
{
    if (config_ != nullptr) {
        delete config_;
        config_ = nullptr;
    }
    handler_->Post([this] { this->stateCb_->OnReleased(*this); });
}

int32_t CameraImpl::TriggerLoopingCapture(FrameConfig &fc)
{
    if (config_ == nullptr) {
        MEDIA_ERR_LOG("Cannot find available configuration, configure the camera first.");
        return MEDIA_INVALID_PARAM;
    }
    FrameConfig *curFc = GetFrameConfig(fc.GetFrameConfigType());
    if (curFc != nullptr) {
        MEDIA_ERR_LOG("Frame config of the input type is already existed.");
        return MEDIA_OK;
    }
    int32_t ret = device_->TriggerLoopingCapture(dynamic_cast<FrameConfig &>(fc));
    if (ret != MEDIA_OK) {
        MEDIA_ERR_LOG("Camera device start looping capture failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }
    frameConfigs_.emplace_back(&fc);

    return MEDIA_OK;
}

void CameraImpl::StopLoopingCapture()
{
    device_->StopLoopingCapture();
    FrameStateCallback *fsc = config_->GetFrameStateCb();
    if (fsc == nullptr) {
        return;
    }
    EventHandler *eventhdl = config_->GetEventHandler();
    if (eventhdl == nullptr) {
        return;
    }

    for (auto i : frameConfigs_) {
        eventhdl->Post([fsc, this, i] {
            FrameResult frameResult;
            fsc->OnFrameFinished(*this, *i, frameResult);
        });
    }
    frameConfigs_.clear();
}

int32_t CameraImpl::TriggerSingleCapture(FrameConfig &fc)
{
    if (config_ == nullptr) {
        MEDIA_ERR_LOG("Cannot find available configuration, configure the camera first.");
        return MEDIA_INVALID_PARAM;
    }
    MEDIA_DEBUG_LOG("Capture frame.(device=%p)", device_);
    int32_t ret = device_->TriggerSingleCapture(dynamic_cast<FrameConfig &>(fc));
    FrameStateCallback *fsc = config_->GetFrameStateCb();
    if (fsc == nullptr) {
        return MEDIA_ERR;
    }
    EventHandler *eventhdl = config_->GetEventHandler();
    if (eventhdl == nullptr) {
        return MEDIA_ERR;
    }
    if (ret != MEDIA_OK) {
        eventhdl->Post([fsc, this, &fc] {
            FrameResult frameResult;
            fsc->OnFrameError(*this, fc, -1, frameResult);
        });
        return MEDIA_ERR;
    }
    eventhdl->Post([fsc, this, &fc] {
        FrameResult frameResult;
        fsc->OnFrameFinished(*this, fc, frameResult);
    });
    return MEDIA_OK;
}

const CameraAbility *CameraImpl::GetAbility()
{
    return ability_;
}

void CameraImpl::OnCreate(CameraDevice *device)
{
    device_ = device;
    if (stateCb_ == nullptr || handler_ == nullptr) {
        return;
    }
    handler_->Post([this] { this->stateCb_->OnCreated(*this); });
}

void CameraImpl::OnCreateFailed()
{
    if (stateCb_ == nullptr || handler_ == nullptr) {
        return;
    }
    handler_->Post([this] { this->stateCb_->OnCreateFailed(id_, MEDIA_ERR); });
}

void CameraImpl::RegistCb(CameraStateCallback &callback, EventHandler &handler)
{
    handler_ = &handler;
    stateCb_ = &callback;
}
} // namespace Media
} // namespace OHOS