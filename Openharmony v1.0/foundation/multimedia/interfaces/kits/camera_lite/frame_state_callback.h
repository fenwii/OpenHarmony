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
 * @addtogroup MultiMedia_FrameStateCallback
 * @{
 *
 * @brief Provides callbacks for frame state changes, in which you can implement operations to response to the changes.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file camera_kit.h
 *
 * @brief Declares functions in the <b>FrameStateCallback</b> class.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_FRAME_STATE_CALLBACK_H
#define OHOS_FRAME_STATE_CALLBACK_H

namespace OHOS {
namespace Media {
class Camera;
class FrameConfig;
class FrameResult {};
/**
 * @brief Provides functions to listen for frame states and response to the state changes.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class FrameStateCallback {
public:
    /**
     * @brief A constructor used to create a <b>FrameStateCallback</b> instance.
     *
     */
    FrameStateCallback() = default;

    /**
     * @brief A destructor used to delete the <b>FrameStateCallback</b> instance.
     *
     */
    ~FrameStateCallback() = default;

    /**
     * @brief Called when the frame capture is finished.
     *
     * @param camera Indicates the camera.
     * @param frameConfig Indicates the frame configuration.
     * @param frameResult Indicates the capture results.
     */
    virtual void OnFrameFinished(Camera &camera, FrameConfig &frameConfig, FrameResult &frameResult) {}

    /**
     * @brief Called when the frame capture fails.
     *
     * @param camera Indicates the camera.
     * @param frameConfig Indicates the frame configuration.
     * @param errorCode Indicates the error code.
     * @param frameResult Indicates the capture results.
     */
    virtual void OnFrameError(Camera &camera, FrameConfig &frameConfig, int32_t errorCode, FrameResult &frameResult) {}
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_FRAME_STATE_CALLBACK_H
