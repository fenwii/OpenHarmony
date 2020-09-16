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
 * @addtogroup MultiMedia_Camera
 * @{
 *
 * @brief Defines the <b>Camera</b> class for camera-related operations.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file camera.h
 *
 * @brief Declares functions in the <b>Camera</b> class to implement camera
 * operations.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_CAMERA_H
#define OHOS_CAMERA_H

#include <list>
#include <string>

#include "camera_config.h"
#include "frame_config.h"

namespace OHOS {
namespace Media {
/**
 *
 * @brief Provides functions in the <b>Camera</b> class to implement camera operations.
 * operations.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class Camera {
public:
    /**
     * @brief A destructor used to delete the <b>Camera</b> instance.
     *
     */
    virtual ~Camera() = default;

    /**
     * @brief Obtains the camera ID.
     *
     * @return Returns the camera ID if obtained; returns the "Error" string if
     * the camera fails to be created.
     */
    virtual std::string GetCameraId()
    {
        return std::string();
    }

    /**
     * @brief Obtains the camera configuration.
     *        You can use the obtained <b>CameraConfig</b> object to configure the
     * camera.
     * @return Returns the pointer to the <b>CameraConfig</b> object if obtained;
     * returns <b>NULL</b> otherwise.
     */
    virtual const CameraConfig *GetCameraConfig() const
    {
        return nullptr;
    }

    /**
     * @brief Obtains the frame configuration.
     *
     * @param type Indicates the type of the frame configuration.
     * @return Returns the pointer to the <b>FrameConfig</b> object if obtained;
     * returns <b>NULL</b> otherwise.
     */
    virtual FrameConfig *GetFrameConfig(int32_t type)
    {
        return nullptr;
    }

    /**
     * @brief Configures the camera using the <b>CameraConfig</b> object.
     *
     * @param config Indicates the pointer to the <b>CameraConfig</b> object.
     */
    virtual void Configure(CameraConfig &config) {}

    /**
     * @brief Triggers looping-frame capture.
     *
     * @param fc Indicates the frame configuration.
     * @return Returns <b>true</b> if the looping-frame capture is successfully
     * started; returns <b>false</b> otherwise.
     */
    virtual int32_t TriggerLoopingCapture(FrameConfig &frameConfig)
    {
        return -1;
    }

    /**
     * @brief Stops looping-frame capture.
     *
     * @return Returns <b>true</b> if the looping-frame capture is successfully
     * stopped; returns <b>false</b> otherwise.
     */
    virtual void StopLoopingCapture() {}

    /**
     * @brief Starts single-frame capture. The frame parameters are set through
     * the <b>FrameConfig</b> object, and the captured image data is stored in the
     * surface of the <b>FrameConfig</b> object.
     *
     * @param fc Indicates the frame configuration.
     * @return Returns <b>true</b> if the single-frame capture is successfully
     * started and the data is stored; returns <b>false</b> otherwise.
     */
    virtual int32_t TriggerSingleCapture(FrameConfig &frameConfig)
    {
        return -1;
    }

    /**
     * @brief Releases the <b>Camera</b> object and associated resources.
     *
     */
    virtual void Release() {}

protected:
    /**
     * @brief A constructor used to create a <b>Camera</b> instance.
     *
     */
    Camera() = default;
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_H
