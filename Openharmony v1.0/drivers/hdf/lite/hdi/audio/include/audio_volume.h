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
 * @file audio_volume.h
 *
 * @brief Declares APIs for audio volume.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_VOLUME_H
#define AUDIO_VOLUME_H

#include "audio_types.h"

/**
 * @brief Provides volume-related APIs for audio rendering or capturing, including functions to
 * set the mute operation, volume, and gain.
 *
 * @since 1.0
 * @version 1.0
 */
struct AudioVolume {
    /**
     * @brief Sets the mute operation for the audio.
     *
     * @param handle Indicates the audio handle.
     * @param mute Specifies whether to mute the audio. Value <b>true</b> means to mute the audio,
     * and <b>false</b> means the opposite.
     * @return Returns <b>0</b> if the setting is successful; returns a negative value otherwise.
     * @see GetMute
     */
    int32_t (*SetMute)(AudioHandle handle, bool mute);

    /**
     * @brief Obtains the mute operation set for the audio.
     *
     * @param handle Indicates the audio handle.
     * @param mute Indicates the pointer to the mute operation set for the audio. Value <b>true</b> means that
     * the audio is muted, and <b>false</b> means the opposite.
     * @return Returns <b>0</b> if the mute operation is obtained; returns a negative value otherwise.
     * @see SetMute
     */
    int32_t (*GetMute)(AudioHandle handle, bool *mute);

    /**
     * @brief Sets the audio volume.
     *
     * The volume ranges from 0.0 to 1.0. If the volume level in an audio service ranges from 0 to 15,
     * <b>0.0</b> indicates that the audio is muted, and <b>1.0</b> indicates the maximum volume level (15).
     *
     * @param handle Indicates the audio handle.
     * @param volume Indicates the volume to set. The value ranges from 0.0 to 1.0.
     * @return Returns <b>0</b> if the setting is successful; returns a negative value otherwise.
     * @see GetVolume
     */
    int32_t (*SetVolume)(AudioHandle handle, float volume);

    /**
     * @brief Obtains the audio volume.
     *
     * @param handle Indicates the audio handle.
     * @param volume Indicates the pointer to the volume to obtain. The value ranges from 0.0 to 1.0.
     * @return Returns <b>0</b> if the volume is obtained; returns a negative value otherwise.
     * @see SetVolume
     */
    int32_t (*GetVolume)(AudioHandle handle, float *volume);

    /**
     * @brief Obtains the range of the audio gain.
     *
     * The audio gain can be expressed in one of the following two ways (depending on the chip platform),
     * corresponding to two types of value ranges:
     * <ul>
     *   <li>Actual audio gain values, for example, ranging from -50 to 6 dB</li>
     *   <li>Float numbers ranging from 0.0 to 1.0, where <b>0.0</b> means to mute the audio,
     *     and <b>1.0</b> means the maximum gain value, for example, 6 dB</li>
     * </ul>
     * @param handle Indicates the audio handle.
     * @param min Indicates the pointer to the minimum value of the range.
     * @param max Indicates the pointer to the maximum value of the range.
     * @return Returns <b>0</b> if the range is obtained; returns a negative value otherwise.
     * @see GetGain
     * @see SetGain
     */
    int32_t (*GetGainThreshold)(AudioHandle handle, float *min, float *max);

    /**
     * @brief Obtains the audio gain.
     *
     * @param handle Indicates the audio handle.
     * @param gain Indicates the pointer to the audio gain.
     * @return Returns <b>0</b> if the audio gain is obtained; returns a negative value otherwise.
     * @see GetGainThreshold
     * @see SetGain
     */
    int32_t (*GetGain)(AudioHandle handle, float *gain);

    /**
     * @brief Sets the audio gain.
     *
     * @param handle Indicates the audio handle.
     * @param gain Indicates the audio gain to set.
     * @return Returns <b>0</b> if the setting is successful; returns a negative value otherwise.
     * @see GetGainThreshold
     * @see GetGain
     */
    int32_t (*SetGain)(AudioHandle handle, float gain);
};

#endif /* AUDIO_VOLUME_H */
/** @} */
