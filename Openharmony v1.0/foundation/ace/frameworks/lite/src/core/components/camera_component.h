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

#ifndef OHOS_ACELITE_CAMERA_COMPONENT_H
#define OHOS_ACELITE_CAMERA_COMPONENT_H

#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_CAMERA

#include "component.h"
#include "camera_kit.h"
#include "ui_surface_view.h"

namespace OHOS {
namespace ACELite {
class FrameCallback final : public Media::FrameStateCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(FrameCallback);
    FrameCallback() = default;
    ~FrameCallback() = default;
    static void ExecuteJsCallback(void *data);

    class CallbackData final : public MemoryHeap {
    public:
        ACE_DISALLOW_COPY_AND_MOVE(CallbackData);
        CallbackData() : isSucceed_(false), uri_(nullptr), errorCode_(0), errorMsg_(nullptr) {}
        ~CallbackData()
        {
            if (uri_ != nullptr) {
                delete uri_;
                uri_ = nullptr;
            }
            if (errorMsg_ != nullptr) {
                delete errorMsg_;
                errorMsg_ = nullptr;
            }
        }

        bool isSucceed_;
        std::string *uri_;
        int32_t errorCode_;
        std::string *errorMsg_;
    };

protected:
    void OnFrameFinished(Media::Camera &camera,
                         Media::FrameConfig &frameConfig,
                         Media::FrameResult &frameResult) override;
    void OnFrameError(Media::Camera &camera,
                      Media::FrameConfig &frameConfig,
                      int32_t errorCode,
                      Media::FrameResult &frameResult) override;

private:
    std::string *CreateFilePath() const;
    bool WriteCapture(std::string &filePath, const char * const buffer, const uint32_t size) const;
    static void CallSuccessFunc(const char * const uri);
    static void CallFailFunc(const int32_t errorCode, const char * const errorMsg);
    static void CallCompleteFunc();
};

class CameraCallback final : public Media::CameraStateCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(CameraCallback);
    CameraCallback() : camera_(nullptr), previewSurface_(nullptr), frameConfig_(nullptr), errorCallback_(UNDEFINED)
    {
        eventHandler_ = std::make_unique<Media::EventHandler>();
    }

    ~CameraCallback()
    {
        jerry_release_value(errorCallback_);
        eventHandler_.reset();
        frameCallback_.reset();
        if (frameConfig_ != nullptr) {
            delete frameConfig_;
            frameConfig_ = nullptr;
        }
        if (camera_ != nullptr) {
            camera_->Release();
        }
    }

    void SetPreviewSurface(Surface &surface)
    {
        previewSurface_ = &surface;
    }

    void SetErrorCallback(jerry_value_t callback)
    {
        errorCallback_ = jerry_acquire_value(callback);
    }

    const Media::Camera *GetCameraInstance() const
    {
        return camera_;
    }

    Media::EventHandler *GetEventHandler() const
    {
        return eventHandler_.get();
    }

protected:
    void OnCreated(Media::Camera &camera) override;
    void OnCreateFailed(const std::string cameraId, int32_t errorCode) override;
    void OnReleased(Media::Camera &camera) override {}

private:
    Media::Camera *camera_;
    Surface *previewSurface_;
    Media::FrameConfig *frameConfig_;
    std::unique_ptr<Media::EventHandler> eventHandler_;
    std::unique_ptr<FrameCallback> frameCallback_;
    jerry_value_t errorCallback_;
};

class CameraComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(CameraComponent);
    CameraComponent() = delete;
    CameraComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager);
    ~CameraComponent() override {}
    const CameraCallback *GetCameraCallback() const
    {
        return cameraCallback_.get();
    }

    static void ReleaseStaticResources();
    static jerry_value_t successCallback_;
    static jerry_value_t failCallback_;
    static jerry_value_t completeCallback_;
    static jerry_value_t jsContext_;
    static bool lastCaptureCompleted_;

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;
    void PostRender() override;

private:
    std::unique_ptr<UISurfaceView> cameraView_;
    Media::CameraKit *cameraKit_;
    std::unique_ptr<CameraCallback> cameraCallback_;
    Media::FrameConfig *frameConfig_;
    Surface *captureSurface_;
    static const char * const TAKE_PHOTO;
    static const uint32_t IMAG_W_PIXELS_LOW;
    static const uint32_t IMAG_H_PIXELS_LOW;
    static const uint32_t IMAG_W_PIXELS_NORMAL;
    static const uint32_t IMAG_H_PIXELS_NORMAL;
    static const uint32_t IMAG_W_PIXELS_HIGH;
    static const uint32_t IMAG_H_PIXELS_HIGH;

    Media::FrameConfig *GetFrameConfig() const
    {
        return frameConfig_;
    }

    const Surface *GetCaptureSurface() const
    {
        return captureSurface_;
    }

    static bool CaptureFrame(const CameraComponent *component, const char *quality);
    static jerry_value_t TakePhoto(const jerry_value_t func,
                                   const jerry_value_t context,
                                   const jerry_value_t args[],
                                   const jerry_length_t size);
};
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_CAMERA
#endif // OHOS_ACELITE_CAMERA_COMPONENT_H
