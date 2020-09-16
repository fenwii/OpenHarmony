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
#ifndef OHOS_CAMERA_CONFIG_IMPL_H
#define OHOS_CAMERA_CONFIG_IMPL_H

#include "camera_config.h"

#include "media_log.h"

namespace OHOS {
namespace Media {
class CameraConfigImpl : public CameraConfig {
public:
    CameraConfigImpl() = default;
    ~CameraConfigImpl() = default;
    void SetFrameStateCallback(FrameStateCallback *callback, EventHandler *handler) override
    {
        if (inUse_) {
            MEDIA_ERR_LOG("This config is in use, do not support config modify.");
        }
        if (callback == nullptr || handler == nullptr) {
            MEDIA_ERR_LOG("Invalid parameter.(callback=%p, handler=%p)", callback, handler);
        }

        callback_ = callback;
        handler_ = handler;
        inUse_ = true;
    }

    EventHandler *GetEventHandler() const override
    {
        return handler_;
    }

    FrameStateCallback *GetFrameStateCb() const override
    {
        return callback_;
    }

private:
    FrameStateCallback *callback_ = nullptr;
    EventHandler *handler_ = nullptr;
    bool inUse_ = false;
};

CameraConfig *CameraConfig::CreateCameraConfig()
{
    return new (std::nothrow) CameraConfigImpl();
}
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_CONFIG_IMPL_H