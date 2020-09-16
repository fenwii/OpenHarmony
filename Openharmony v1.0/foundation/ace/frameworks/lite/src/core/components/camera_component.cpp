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

#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_CAMERA

#include "camera_component.h"
#include <fstream>
#include <sstream>
#include <string>
#include "ability_env.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "js_async_work.h"
#include "key_parser.h"
#include "keys.h"
#include <sys/time.h>

using namespace std;

namespace OHOS {
namespace ACELite {
jerry_value_t CameraComponent::successCallback_;
jerry_value_t CameraComponent::failCallback_;
jerry_value_t CameraComponent::completeCallback_;
jerry_value_t CameraComponent::jsContext_;
bool CameraComponent::lastCaptureCompleted_ = true;

const char * const CameraComponent::TAKE_PHOTO = "takePhoto";

const uint32_t CameraComponent::IMAG_W_PIXELS_LOW = 720;
const uint32_t CameraComponent::IMAG_H_PIXELS_LOW = 576;
const uint32_t CameraComponent::IMAG_W_PIXELS_NORMAL = 1280;
const uint32_t CameraComponent::IMAG_H_PIXELS_NORMAL = 720;
const uint32_t CameraComponent::IMAG_W_PIXELS_HIGH = 1920;
const uint32_t CameraComponent::IMAG_H_PIXELS_HIGH = 1080;

void FrameCallback::OnFrameFinished(Media::Camera &camera,
                                    Media::FrameConfig &frameConfig,
                                    Media::FrameResult &frameResult)
{
    if (frameConfig.GetFrameConfigType() != Media::FRAME_CONFIG_CAPTURE) {
        CameraComponent::ReleaseStaticResources();
        return;
    }
    auto surfaceList = frameConfig.GetSurfaces();
    if (surfaceList.empty()) {
        CameraComponent::ReleaseStaticResources();
        return;
    }
    Surface *surface = surfaceList.front();
    SurfaceBuffer *buffer = (surface == nullptr) ? nullptr : surface->AcquireBuffer();
    if (buffer == nullptr) {
        CameraComponent::ReleaseStaticResources();
        return;
    }
    string *filePath = CreateFilePath();
    if (filePath == nullptr) {
        surface->ReleaseBuffer(buffer);
        CameraComponent::ReleaseStaticResources();
        return;
    }

    bool writeSuccess = WriteCapture(*filePath, static_cast<char *>(buffer->GetVirAddr()), buffer->GetSize());
    CallbackData *callbackData = new CallbackData();
    if ((!writeSuccess) || (callbackData == nullptr)) {
        delete filePath;
        filePath = nullptr;
        surface->ReleaseBuffer(buffer);
        CameraComponent::ReleaseStaticResources();
        if (callbackData != nullptr) {
            delete callbackData;
            callbackData = nullptr;
        }
        return;
    }

    callbackData->isSucceed_ = true;
    callbackData->uri_ = filePath;
    if (!JsAsyncWork::DispatchAsyncWork(ExecuteJsCallback, callbackData)) {
        delete callbackData;
        callbackData = nullptr;
        CameraComponent::ReleaseStaticResources();
    }
    surface->ReleaseBuffer(buffer);
}

void FrameCallback::OnFrameError(Media::Camera &camera,
                                 Media::FrameConfig &frameConfig,
                                 int32_t errorCode,
                                 Media::FrameResult &frameResult)
{
    CallbackData *callbackData = new CallbackData();
    if (callbackData == nullptr) {
        CameraComponent::ReleaseStaticResources();
        return;
    }
    callbackData->isSucceed_ = false;
    callbackData->errorCode_ = errorCode;
    callbackData->errorMsg_ = new string("takePhoto failed due to frame error!");
    if (!JsAsyncWork::DispatchAsyncWork(ExecuteJsCallback, callbackData)) {
        delete callbackData;
        callbackData = nullptr;
        CameraComponent::ReleaseStaticResources();
    }
}

void FrameCallback::ExecuteJsCallback(void *data)
{
    CallbackData *callbackData = static_cast<CallbackData *>(data);
    if (callbackData == nullptr) {
        CameraComponent::ReleaseStaticResources();
        return;
    }

    if ((callbackData->isSucceed_) && (callbackData->uri_ != nullptr)) {
        CallSuccessFunc(callbackData->uri_->c_str());
        CallCompleteFunc();
    } else if ((!callbackData->isSucceed_) && (callbackData->errorMsg_ != nullptr)) {
        CallFailFunc(callbackData->errorCode_, callbackData->errorMsg_->c_str());
        CallCompleteFunc();
    }
    delete callbackData;
    callbackData = nullptr;
    CameraComponent::ReleaseStaticResources();
}

string *FrameCallback::CreateFilePath() const
{
    const char *dataPath = GetDataPath();
    if (dataPath == nullptr) {
        return nullptr;
    }
    string dataPathStr(dataPath);
    string prefix = dataPathStr + "/Img_";
    ostringstream oss;
    struct timeval timeVal;
    bool getTimeSuccess = false;
    if (gettimeofday(&timeVal, nullptr) == 0) {
        struct tm *ltm = localtime(&(timeVal.tv_sec));
        if (ltm != nullptr) {
            oss << prefix << (ltm->tm_year) << (ltm->tm_mon + 1) << ltm->tm_mday << "_" << ltm->tm_hour << ltm->tm_min
                << ltm->tm_sec << ".jpg";
            getTimeSuccess = true;
        }
    }
    if (!getTimeSuccess) {
        oss << prefix << ".jpg";
    }
    return new string(oss.str());
}

bool FrameCallback::WriteCapture(string &filePath, const char * const buffer, const uint32_t size) const
{
    if (buffer == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "FrameCallback: write capture with null buffer!");
        return false;
    }
    ofstream file(filePath);
    if (!file.is_open()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "FrameCallback: open file failed when write capture!");
        return false;
    }
    file.write(buffer, size);
    if (file.fail() || file.bad()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "FrameCallback: write file failed when write capture!");
        file.close();
        return false;
    }
    file.close();
    return true;
}

void FrameCallback::CallSuccessFunc(const char * const uri)
{
    if (jerry_value_is_function(CameraComponent::successCallback_) && (uri != nullptr)) {
        const char * const uriKey = "uri";
        jerry_value_t arg = jerry_create_object();
        JerrySetStringProperty(arg, uriKey, uri);
        CallJSFunctionAutoRelease(CameraComponent::successCallback_, CameraComponent::jsContext_, &arg, 1);
        jerry_release_value(arg);
    }
}

void FrameCallback::CallFailFunc(const int32_t errorCode, const char * const errorMsg)
{
    if (jerry_value_is_function(CameraComponent::failCallback_) && (errorMsg != nullptr)) {
        jerry_value_t erromsg = jerry_create_string(reinterpret_cast<const jerry_char_t *>(errorMsg));
        jerry_value_t errocode = jerry_create_number(errorCode);
        jerry_value_t failArg[] = {erromsg, errocode};
        const uint8_t agrc = 2; // 2 arguments for fail callback
        CallJSFunctionAutoRelease(CameraComponent::failCallback_, CameraComponent::jsContext_, failArg, agrc);
        ReleaseJerryValue(erromsg, errocode, VA_ARG_END_FLAG);
    }
}

void FrameCallback::CallCompleteFunc()
{
    if (jerry_value_is_function(CameraComponent::completeCallback_)) {
        CallJSFunctionAutoRelease(CameraComponent::completeCallback_, CameraComponent::jsContext_, nullptr, 0);
    }
}

void CameraCallback::OnCreated(Media::Camera &camera)
{
    frameCallback_ = make_unique<FrameCallback>();
    Media::CameraConfig *config = Media::CameraConfig::CreateCameraConfig();
    if (config == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraCallback: create camera config failed!");
        return;
    }
    config->SetFrameStateCallback(frameCallback_.get(), eventHandler_.get());
    camera.Configure(*config);
    camera_ = &camera;

    if (previewSurface_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraCallback: fail to start preview due to null surface!");
        return;
    }
    frameConfig_ = new Media::FrameConfig(Media::FRAME_CONFIG_PREVIEW);
    if (frameConfig_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraCallback: create frame config for preview failed!");
        return;
    }
    frameConfig_->AddSurface(*previewSurface_);
    camera.TriggerLoopingCapture(*frameConfig_);
}

void CameraCallback::OnCreateFailed(const string cameraId, int32_t errorCode)
{
    HILOG_ERROR(HILOG_MODULE_ACE, "CameraCallback: camera:%s unavailable, errorCode:%d", cameraId.c_str(), errorCode);
    if (jerry_value_is_function(errorCallback_)) {
        const char * const detailKey = "detail";
        const char * const detailValue = "camera unavailable";
        const char * const errorCodeKey = "errorCode";
        jerry_value_t arg = jerry_create_object();
        JerrySetStringProperty(arg, detailKey, detailValue);
        JerrySetNumberProperty(arg, errorCodeKey, errorCode);
        CallJSFunctionAutoRelease(errorCallback_, UNDEFINED, &arg, 1);
        jerry_release_value(arg);
    }
}

CameraComponent::CameraComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager), cameraKit_(nullptr), frameConfig_(nullptr), captureSurface_(nullptr)
{
    SetComponentName(K_CAMERA);
    RegisterNamedFunction(TAKE_PHOTO, TakePhoto);
}

bool CameraComponent::CreateNativeViews()
{
    cameraView_ = make_unique<UISurfaceView>();
    captureSurface_ = Surface::CreateSurface();
    if ((cameraView_ == nullptr) || (captureSurface_ == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraComponent: create camera view failed!");
        return false;
    }
    cameraKit_ = Media::CameraKit::GetInstance();
    cameraCallback_ = make_unique<CameraCallback>();
    frameConfig_ = new Media::FrameConfig(Media::FRAME_CONFIG_CAPTURE);
    if (frameConfig_ != nullptr) {
        frameConfig_->AddSurface(*captureSurface_);
    }
    return true;
}

void CameraComponent::ReleaseNativeViews()
{
    if (cameraCallback_ != nullptr) {
        Media::Camera *camera = const_cast<Media::Camera *>(cameraCallback_->GetCameraInstance());
        if (camera != nullptr) {
            camera->StopLoopingCapture();
        }
        cameraCallback_.reset();
    }
    if (frameConfig_ != nullptr) {
        delete frameConfig_;
        frameConfig_ = nullptr;
    }
    if (captureSurface_ != nullptr) {
        delete captureSurface_;
        captureSurface_ = nullptr;
    }
}

inline UIView *CameraComponent::GetComponentRootView() const
{
    return static_cast<UIView *>(cameraView_.get());
}

bool CameraComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    bool result = false;
    switch (eventTypeId) {
        case K_ERROR: {
            if (cameraCallback_ != nullptr) {
                cameraCallback_->SetErrorCallback(funcValue);
                result = true;
            }
            break;
        }
        default:
            break;
    }
    return result;
}

void CameraComponent::PostRender()
{
    if ((cameraView_ == nullptr) || (cameraKit_ == nullptr) || (cameraCallback_ == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraComponent: post render failed due to null native object!");
        return;
    }
    list<string> camList = cameraKit_->GetCameraIds();
    if (camList.empty()) {
        return;
    }
    const string cameraId = camList.front();
    Surface *previewSurface = cameraView_->GetSurface();
    if (previewSurface != nullptr) {
        previewSurface->SetWidthAndHeight(IMAG_W_PIXELS_NORMAL, IMAG_H_PIXELS_NORMAL);
        cameraCallback_->SetPreviewSurface(*previewSurface);
    }
    cameraKit_->CreateCamera(cameraId, *cameraCallback_.get(), *cameraCallback_->GetEventHandler());
}

jerry_value_t CameraComponent::TakePhoto(const jerry_value_t func,
                                         const jerry_value_t context,
                                         const jerry_value_t args[],
                                         const jerry_length_t size)
{
    // capture processing flag
    if (!lastCaptureCompleted_) {
        HILOG_INFO(HILOG_MODULE_ACE,
                   "Please wait until the last capture processing is over before trying to take a photo");
        return UNDEFINED;
    }
    lastCaptureCompleted_ = false;
    if (size != 1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraComponent: call TakePhoto with invalid arguments!");
        lastCaptureCompleted_ = true;
        return UNDEFINED;
    }

    UISurfaceView *cameraView = static_cast<UISurfaceView *>(ComponentUtils::GetViewFromBindingObject(context));
    CameraComponent *component = static_cast<CameraComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if ((cameraView == nullptr) || (component == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraComponent: call TakePhoto failed due to null component object!");
        lastCaptureCompleted_ = true;
        return UNDEFINED;
    }

    uint16_t length = 0;
    const char * const qualityKey = "quality";
    char *quality = JerryMallocStringProperty(args[0], qualityKey, length);
    successCallback_ = jerryx_get_property_str(args[0], ATTR_SUCCESS);
    failCallback_ = jerryx_get_property_str(args[0], ATTR_FAIL);
    completeCallback_ = jerryx_get_property_str(args[0], ATTR_COMPLETE);
    jsContext_ = jerry_acquire_value(context);

    if (!CaptureFrame(component, quality)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "CameraComponent: capture frame failed!");
        ReleaseStaticResources();
    }
    ACE_FREE(quality);
    return UNDEFINED;
}

void CameraComponent::ReleaseStaticResources()
{
    ReleaseJerryValue(successCallback_, failCallback_, completeCallback_, jsContext_, VA_ARG_END_FLAG);
    lastCaptureCompleted_ = true;
}

bool CameraComponent::CaptureFrame(const CameraComponent *component, const char *quality)
{
    Media::FrameConfig *frameConfig = component->GetFrameConfig();
    Surface *surface = const_cast<Surface *>(component->GetCaptureSurface());
    if ((frameConfig == nullptr) || (surface == nullptr)) {
        return false;
    }

    uint32_t surfWidth = IMAG_W_PIXELS_NORMAL;  // corresponding to default resolution
    uint32_t surfHeight = IMAG_H_PIXELS_NORMAL; // corresponding to default resolution
    if (quality != nullptr) {
        const char * const qualityLow = "low";
        const char * const qualityHigh = "high";
        if (strcmp(quality, qualityLow) == 0) {
            surfWidth = IMAG_W_PIXELS_LOW;
            surfHeight = IMAG_H_PIXELS_LOW;
        } else if (strcmp(quality, qualityHigh) == 0) {
            surfWidth = IMAG_W_PIXELS_HIGH;
            surfHeight = IMAG_H_PIXELS_HIGH;
        }
    }
    surface->SetWidthAndHeight(surfWidth, surfHeight);

    const CameraCallback *cameraCallback = component->GetCameraCallback();
    if (cameraCallback == nullptr) {
        return false;
    }
    Media::Camera *camera = const_cast<Media::Camera *>(cameraCallback->GetCameraInstance());
    if (camera == nullptr) {
        return false;
    }
    return camera->TriggerSingleCapture(*frameConfig) == MEDIA_OK;
}
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_CAMERA