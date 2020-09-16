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

/**
 * @addtogroup MuiltiMedia_CameraDeviceCallback
 * @{
 *
 * @brief Defines the <b>CameraDeviceCallback</b> class to response to device changes.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file camera_device_callback.h
 *
 * @brief Declares functions in the <b>CameraDeviceCallback</b> class to response to device changes.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_CAMERA_DEVICE_CALLBACK_H
#define OHOS_CAMERA_DEVICE_CALLBACK_H

#include <string>

namespace OHOS {
namespace Media {
constexpr int32_t CAMERA_DEVICE_STATE_AVAILABLE = 0;
constexpr int32_t CAMERA_DEVICE_STATE_UNAVAILABLE = 1;
/**
 *
 * @brief Provides functions to response to device changes.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class CameraDeviceCallback {
public:
    /**
     * @brief A constructor used to create a <b>CameraDeviceCallback</b> instance.
     *
     */
    CameraDeviceCallback() = default;

     /**
     * @brief A destructor used to delete the <b>CameraDeviceCallback</b> instance.
     *
     */
    virtual ~CameraDeviceCallback() = default;

    /**
     * @brief Called when the camera state changes.
     *
     * @param cameraId Indicates the camera ID.
     * @param status Indicates the camera state.
     */
    virtual void OnCameraStatus(std::string cameraId, int32_t status) {}
};
} // namespace Media
} // namespace OHOS
#endif
