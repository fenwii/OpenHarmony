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
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file sys_info.h
 *
 * @brief Declares the system information about the graphics module, including the function to obtain the information
 *        about FPS, which needs to be enabled by the <b>ENABLE_FPS_SUPPORT</b> macro.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_SYS_INFO_H
#define GRAPHIC_LITE_SYS_INFO_H

#include "graphic_config.h"
#include "heap_base.h"

namespace OHOS {
/**
 * @brief Obtains the system information. Currently, the FPS information can be obtained. To enable the FPS feature,
 *        enable the <b>ENABLE_FPS_SUPPORT</b> macro.
 *
 * @since 1.0
 * @version 1.0
 */
class SysInfo {
public:
    /**
     * @brief Enumerates the FPS capture types.
     *
     * @since 1.0
     * @version 1.0
     */
    enum FPSCalculateType {
        /** Fixed time sampling: The system collects the number of page refresh times within one second. */
        FPS_CT_FIXED_TIME,
        /**
         * Average sampling: The system collects statistics on the average frame rate of 100 frames. No extra space is
         * required to store the data of each frame. The precision is not as high as that of precise sampling.
         */
        FPS_CT_AVERAGE_SAMPLING,
        /**
         * Precise sampling: The system collects statistics on the average frame rate of the current 100 frames. Extra
         * space is required to save the data of each frame. The result is more precise than that of average sampling.
         */
        FPS_CT_PRECISE_SAMPLING
    };

    /**
     * @brief Called when the FPS changes.
     *
     * @since 1.0
     * @version 1.0
     */
    class OnFPSChangedListener : public HeapBase {
    public:
        /**
         * @brief A constructor used to create an <b>OnFPSChangedListener</b> instance with the default sampling type
         *        <b>FPS_CT_FIXED_TIME</b>.
         *
         * @since 1.0
         * @version 1.0
         */
        OnFPSChangedListener() : type_(FPS_CT_FIXED_TIME){};

        /**
         * @brief A destructor used to delete the <b>OnFPSChangedListener</b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        virtual ~OnFPSChangedListener() {}

        /**
         * @brief Called when the FPS data changes.
         *
         * @param newFPS Indicates the FPS data.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnFPSChanged(float newFPS) = 0;

        /**
         * @brief Obtains the FPS sampling type.
         *
         * @return Returns the FPS sampling type. For details, see {@link FPSCalculateType}.
         * @since 1.0
         * @version 1.0
         */
        FPSCalculateType GetFPSCalculateType() const
        {
            return type_;
        }

        /**
         * @brief Sets the FPS sampling type.
         *
         * @param type Indicates the FPS sampling type. For details, see {@link FPSCalculateType}.
         * @since 1.0
         * @version 1.0
         */
        void SetFPSCalculateType(FPSCalculateType type)
        {
            type_ = type;
        }

    private:
        FPSCalculateType type_;
    };

    /**
     * @brief Obtains the FPS data.
     *
     * @return Returns the FPS data.
     * @since 1.0
     * @version 1.0
     */
    static float GetFPS();

    /**
     * @brief Registers the listener for notifying the FPS changes.
     *
     * @param onFPSChangedListener Indicates the pointer to the FPS change notification function. For details, see
     *                             {@link OnFPSChangedListener}.
     * @since 1.0
     * @version 1.0
     */
    static void RegisterFPSChangedListener(OnFPSChangedListener* onFPSChangedListener);

private:
    SysInfo() = default;
    ~SysInfo() = default;
};
} // namespace OHOS
#endif
