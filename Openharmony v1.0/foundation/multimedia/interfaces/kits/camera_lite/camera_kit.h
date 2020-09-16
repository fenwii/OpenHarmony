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
 * @addtogroup MultiMedia_CameraKit
 * @{
 *
 * @brief Defines the <b>CameraKit</b> class for using camera functionalities.
 * @since 1.0
 * @version 1.0
 */

/**
 * @file camera_kit.h
 *
 * @brief Declares functions in the <b>CameraKit</b> class.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_CAMERA_KIT_H
#define OHOS_CAMERA_KIT_H

#include <list>
#include <string>

#include "camera_ability.h"
#include "camera_device_callback.h"
#include "camera_state_callback.h"
#include "event_handler.h"

namespace OHOS {
namespace Media {
/**
 *
 * @brief Provides functions in the <b>CameraKit</b> class.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class CameraKit {
public:
     /**
     * @brief A destructor used to delete the <b>CameraKit</b> instance.
     *
     */
    ~CameraKit();
     /**
      * @brief Obtains a single instance of the <b>CameraKit</b>.
      * @return Returns the <b>CameraKit</b> instance if obtained; returns <b>NULL</b> otherwise.
      */
    static CameraKit *GetInstance();

    /**
     * @brief Obtains IDs of cameras that are currently available.
     *
     * @return Returns the camera IDs if obtained; returns <b>NULL</b> otherwise.
     */
    std::list<std::string> GetCameraIds();

    /**
     * @brief Obtains the camera capability, including the resolutions and frame rates.
     *
     * @param cameraId Indicates the camera ID.
     * @return Returns the <b>CameraAbility</b> object.
     */
    const CameraAbility *GetCameraAbility(std::string cameraId);

    /**
     * @brief Registers a camera callback for camera status changes
     *        and an event callback to respond to a triggered event.
     *
     * @param callback Indicates the camera callback to register.
     * @param handler Indicates the event callback to register.
     */
    void RegisterCameraDeviceCallback(CameraDeviceCallback &callback, EventHandler &handler);

    /**
     * @brief Unregisters a camera callback.
     *
     * @param callback Indicates the camera callback to unregister.
     */
    void UnregisterCameraDeviceCallback(CameraDeviceCallback &callback);

    /**
     * @brief Creates a camera object.
     *
     * @param cameraId Indicates the camera ID.
     * @param callback Indicates the camera callback.
     * @param handler Indicates the event callback to register.
     */
    void CreateCamera(const std::string &cameraId, CameraStateCallback &callback, EventHandler &handler);

private:
    /**
     * @brief A constructor used to create a <b>CameraDeviceCallback</b> instance.
     *
     */
    CameraKit();
};
} // namespace Media
} // namespace OHOS

#endif // OHOS_CAMERA_KIT_H
