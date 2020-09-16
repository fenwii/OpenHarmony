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
 * @addtogroup MultiMedia_CameraConfig
 * @{
 *
 * @brief Defines the <b>CameraConfig</b> class for operations on camera configurations.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file camera_config.h
 *
 * @brief Declares functions in the <b>CameraConfig</b> class.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_CAMERA_CONFIG_H
#define OHOS_CAMERA_CONFIG_H

#include "event_handler.h"
#include "frame_state_callback.h"

namespace OHOS {
namespace Media {
/**
 *
 * @brief Provides functions to configure camera parameters.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class CameraConfig {
public:
    /**
     * @brief A destructor used to delete the <b>CameraAbility</b> instance.
     *
     */
    virtual ~CameraConfig() {}

    /**
     * @brief Creates the <b>CameraConfig</b> instance of this singleton class to configure
     *        and read the required parameters.
     *
     * @return Returns the <b>CameraConfig</b> instance if created; returns <b>NULL</b> otherwise.
     */
    static CameraConfig *CreateCameraConfig();

    /**
     * @brief Sets a frame state callback to responds to state changes.
     *
     * @param callback Indicates the frame state callback.
     * @param handler Indicates the event handler.
     */
    virtual void SetFrameStateCallback(FrameStateCallback *callback, EventHandler *handler) {}

    /**
     * @brief Obtains the <b>EventHandler</b> object.
     *
     * @return Returns the pointer to the <b>EventHandler</b> object if obtained; returns <b>NULL</b> otherwise.
     */
    virtual EventHandler *GetEventHandler() const
    {
        return nullptr;
    }

    /**
     * @brief Obtains a <b>FrameStateCallback</b> object.
     *
     * @return Returns the pointer to the <b>FrameStateCallback</b> object if obtained; returns <b>NULL</b> otherwise.
     */
    virtual FrameStateCallback *GetFrameStateCb() const
    {
        return nullptr;
    }

protected:
    /**
     * @brief A constructor used to create a <b>CameraConfig</b> instance.
     *
     */
    CameraConfig() {}
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_CONFIG_H
