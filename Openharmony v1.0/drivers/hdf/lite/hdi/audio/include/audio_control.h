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
 * @file audio_control.h
 *
 * @brief Declares APIs for audio control.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_CONTROL_H
#define AUDIO_CONTROL_H

#include "audio_types.h"

/**
 * @brief Provides control-related APIs for audio rendering or capturing, including functions to
 * start, stop, pause, and resume audio rendering or capturing, and flush data in the audio buffer.
 *
 * @since 1.0
 * @version 1.0
 */
struct AudioControl {
    /**
     * @brief Starts audio rendering or capturing.
     *
     * @param handle Indicates the audio handle.
     * @return Returns <b>0</b> if the rendering or capturing is successfully started;
     * returns a negative value otherwise.
     * @see Stop
     */
    int32_t (*Start)(AudioHandle handle);

    /**
     * @brief Stops audio rendering or capturing.
     *
     * @param handle Indicates the audio handle.
     * @return Returns <b>0</b> if the rendering or capturing is successfully stopped;
     * returns a negative value otherwise.
     * @see Start
     */
    int32_t (*Stop)(AudioHandle handle);

    /**
     * @brief Pauses audio rendering or capturing.
     *
     * @param handle Indicates the audio handle.
     * @return Returns <b>0</b> if the rendering or capturing is successfully paused;
     * returns a negative value otherwise.
     * @see Resume
     */
    int32_t (*Pause)(AudioHandle handle);

    /**
     * @brief Resumes audio rendering or capturing.
     *
     * @param handle Indicates the audio handle.
     * @return Returns <b>0</b> if the rendering or capturing is successfully resumed;
     * returns a negative value otherwise.
     * @see Pause
     */
    int32_t (*Resume)(AudioHandle handle);

    /**
     * @brief Flushes data in the audio buffer.
     *
     * @param handle Indicates the audio handle.
     * @return Returns <b>0</b> if the flush is successful; returns a negative value otherwise.
     */
    int32_t (*Flush)(AudioHandle handle);
};

#endif /* AUDIO_CONTROL_H */
/** @} */
