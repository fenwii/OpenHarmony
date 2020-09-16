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
 * @addtogroup Audio
 * @{
 *
 * @brief Defines audio-related APIs, including custom data types and functions for loading drivers,
 * accessing a driver adapter, and rendering and capturing audios.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file audio_adapter.h
 *
 * @brief Declares APIs for operations related to the audio adapter.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_ADAPTER_H
#define AUDIO_ADAPTER_H

#include "audio_types.h"
#include "audio_render.h"
#include "audio_capture.h"

/**
 * @brief Provides audio adapter capabilities, including initializing ports, creating rendering and capturing tasks,
 * and obtaining the port capability set.
 *
 * @see AudioRender
 * @see AudioCapture
 * @since 1.0
 * @version 1.0
 */
struct AudioAdapter {
    /**
     * @brief Initializes all ports of an audio adapter.
     *
     * Call this function before calling other driver functions to check whether the initialization is complete.
     * If the initialization is not complete, wait for a while (for example, 100 ms) and perform the check again
     * until the port initialization is complete.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @return Returns <b>0</b> if the initialization is successful; returns a negative value otherwise.
     */
    int32_t (*InitAllPorts)(struct AudioAdapter *adapter);

    /**
     * @brief Creates an <b>AudioRender</b> object.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param desc Indicates the pointer to the descriptor of the audio adapter to start.
     * @param attrs Indicates the pointer to the audio sampling attributes to open.
     * @param render Indicates the double pointer to the <b>AudioRender</b> object.
     * @return Returns <b>0</b> if the <b>AudioRender</b> object is created successfully;
     * returns a negative value otherwise.
     * @see GetPortCapability
     * @see DestroyRender
     */
    int32_t (*CreateRender)(struct AudioAdapter *adapter, const struct AudioDeviceDescriptor *desc,
                            const struct AudioSampleAttributes *attrs, struct AudioRender **render);

    /**
     * @brief Destroys an <b>AudioRender</b> object.
     *
     * @attention Do not destroy the object during audio rendering.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param render Indicates the pointer to the <b>AudioRender</b> object to operate.
     * @return Returns <b>0</b> if the <b>AudioRender</b> object is destroyed; returns a negative value otherwise.
     * @see CreateRender
     */
    int32_t (*DestroyRender)(struct AudioAdapter *adapter, struct AudioRender *render);

    /**
     * @brief Creates an <b>AudioCapture</b> object.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param desc Indicates the pointer to the descriptor of the audio adapter to start.
     * @param attrs Indicates the pointer to the audio sampling attributes to open.
     * @param capture Indicates the double pointer to the <b>AudioCapture</b> object.
     * @return Returns <b>0</b> if the <b>AudioCapture</b> object is created successfully;
     * returns a negative value otherwise.
     * @see GetPortCapability
     * @see DestroyCapture
     */
    int32_t (*CreateCapture)(struct AudioAdapter *adapter, const struct AudioDeviceDescriptor *desc,
                             const struct AudioSampleAttributes *attrs, struct AudioCapture **capture);

    /**
     * @brief Destroys an <b>AudioCapture</b> object.
     *
     * @attention Do not destroy the object during audio capturing.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param capture Indicates the pointer to the <b>AudioCapture</b> object to operate.
     * @return Returns <b>0</b> if the <b>AudioCapture</b> object is destroyed; returns a negative value otherwise.
     * @see CreateCapture
     */
    int32_t (*DestroyCapture)(struct AudioAdapter *adapter, struct AudioCapture *capture);

    /**
     * @brief Obtains the capability set of the port driver for the audio adapter.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param port Indicates the pointer to the port.
     * @param capability Indicates the pointer to the capability set to obtain.
     * @return Returns <b>0</b> if the capability set is successfully obtained; returns a negative value otherwise.
     */
    int32_t (*GetPortCapability)(struct AudioAdapter *adapter, const struct AudioPort *port,
                                 struct AudioPortCapability *capability);

    /**
     * @brief Sets the passthrough data transmission mode of the audio port driver.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param port Indicates the pointer to the port.
     * @param mode Indicates the passthrough transmission mode to set.
     * @return Returns <b>0</b> if the setting is successful; returns a negative value otherwise.
     * @see GetPassthroughMode
     */
    int32_t (*SetPassthroughMode)(struct AudioAdapter *adapter, const struct AudioPort *port,
                                  enum AudioPortPassthroughMode mode);

    /**
     * @brief Obtains the passthrough data transmission mode of the audio port driver.
     *
     * @param adapter Indicates the pointer to the audio adapter to operate.
     * @param port Indicates the pointer to the port.
     * @param mode Indicates the pointer to the passthrough transmission mode to obtain.
     * @return Returns <b>0</b> if the mode is successfully obtained; returns a negative value otherwise.
     * @see SetPassthroughMode
     */
    int32_t (*GetPassthroughMode)(struct AudioAdapter *adapter, const struct AudioPort *port,
                                  enum AudioPortPassthroughMode *mode);
};

#endif /* AUDIO_ADAPTER_H */
/** @} */
