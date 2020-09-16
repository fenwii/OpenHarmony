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
 * @addtogroup MultiMedia_CameraStateCallback
 * @{
 *
 * @brief Provides callbacks for camera states to configure responses to the states.
 *
 * @since 1.0
 * @version 1.0
 */
 /**
 * @file camera_state_callback.h
 *
 * @brief Declares functions in the <b>CameraStateCallback</b> class.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_CAMERA_STATE_CALLBACK_H
#define OHOS_CAMERA_STATE_CALLBACK_H

#include <string>
#include "camera.h"

namespace OHOS {
namespace Media {
/**
*
* @brief Provides functions to response to camera states.
*
* @since 1.0
* @version 1.0
*/
class CameraStateCallback {
public:
    /**
     * @brief A constructor used to create a <b>CameraStateCallback</b> instance.
     *
     */
    CameraStateCallback() = default;
    /**
     * @brief A destructor used to delete the <b>CameraStateCallback</b> instance.
     *
     */
    virtual ~CameraStateCallback() {}
    /**
     * @brief Called when the camera is successfully created.
     *
     * @param c Indicates the <b>Camera</b> object.
     */
    virtual void OnCreated(Camera &c) {}
    /**
     * @brief Called when the camera fails to be created.
     *
     * @param cameraId Indicates the camera ID.
     * @param errorCode Indicates the error code.
     */
    virtual void OnCreateFailed(const std::string cameraId, int32_t errorCode) {}
    /**
     * @brief Called when the camera is released.
     *
     * @param c Indicates the <b>Camera</b> object.
     */
    virtual void OnReleased(Camera &c) {}
    /**
     * @brief Called when the camera is configured.
     * @param c camera Indicates the <b>Camera</b> object.
     */
    virtual void OnConfigured(Camera &c) {}
    /**
     * @brief Called when the camera fails to be configured.
     *
     * @param c Indicates the <b>Camera</b> object.
     * @param errorCode Indicates the error code.
     */
    virtual void OnConfigureFailed(const std::string cameraId, int32_t errorCode) {}
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_STATE_CALLBACK_H
