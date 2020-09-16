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
 * @file audio_scene.h
 *
 * @brief Declares APIs for audio scenes.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_SCENE_H
#define AUDIO_SCENE_H

#include "audio_types.h"

/**
 * @brief Provides scene-related APIs for audio rendering or capturing, including functions to
 * select an audio scene and check whether the configuration of an audio scene is supported.
 *
 * @since 1.0
 * @version 1.0
 */
struct AudioScene {
    /**
     * @brief Checks whether the configuration of an audio scene is supported.
     *
     * @param handle Indicates the audio handle.
     * @param scene Indicates the pointer to the descriptor of the audio scene.
     * @param supported Indicates the pointer to the variable specifying whether the configuration is supported.
     * Value <b>true</b> means that the configuration is supported, and <b>false</b> means the opposite.
     * @return Returns <b>0</b> if the result is obtained; returns a negative value otherwise.
     * @see SelectScene
     */
    int32_t (*CheckSceneCapability)(AudioHandle handle, const struct AudioSceneDescriptor *scene, bool *supported);

    /**
     * @brief Selects an audio scene.
     *
     * <ul>
     *   <li>To select a specific audio scene, you need to specify both the application scenario and output device.
     *     For example, to select a scene using a smartphone speaker as the output device, set <b>scene</b> according
     *     to the scenarios where the speaker is used. For example:</li>
     *     <ul>
     *       <li>For media playback, set the value to <b>media_speaker</b>.</li>
     *       <li>For a voice call, set the value to <b>voice_speaker</b>.</li>
     *     </ul>
     *   <li>To select only the application scenario, such as media playback, movie, or gaming, you can set
     *     <b>scene</b> to <b>media</b>, <b>movie</b>, or <b>game</b>, respectively.</li>
     *   <li>To select only the output device, such as media receiver, speaker, or headset, you can set
     *     <b>scene</b> to <b>receiver</b>, <b>speaker</b>, or <b>headset</b>, respectively.</li>
     * </ul>
     * @param handle Indicates the audio handle.
     * @param scene Indicates the pointer to the descriptor of the audio scene to select.
     * @return Returns <b>0</b> if the scene is selected successfully; returns a negative value otherwise.
     * @see CheckSceneCapability
     */
    int32_t (*SelectScene)(AudioHandle handle, const struct AudioSceneDescriptor *scene);
};

#endif /* AUDIO_SCENE_H */
/** @} */
