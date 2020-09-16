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
 * @file audio_attribute.h
 *
 * @brief Declares APIs for audio attributes.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_ATTRIBUTE_H
#define AUDIO_ATTRIBUTE_H

#include "audio_types.h"

/**
 * @brief Provides attribute-related APIs for audio rendering or capturing, including functions to
 * obtain frame information and set audio sampling attributes.
 *
 * @since 1.0
 * @version 1.0
 */
struct AudioAttribute {
    /**
     * @brief Obtains the audio frame size, that is, the length (in bytes) of a frame.
     *
     * @param handle Indicates the audio handle.
     * @param size Indicates the pointer to the audio frame size (in bytes).
     * @return Returns <b>0</b> if the audio frame size is obtained; returns a negative value otherwise.
     */
    int32_t (*GetFrameSize)(AudioHandle handle, uint64_t *size);

    /**
     * @brief Obtains the number of audio frames in the audio buffer.
     *
     * @param handle Indicates the audio handle.
     * @param count Indicates the pointer to the number of audio frames in the audio buffer.
     * @return Returns <b>0</b> if the number of audio frames is obtained; returns a negative value otherwise.
     */
    int32_t (*GetFrameCount)(AudioHandle handle, uint64_t *count);

    /**
     * @brief Sets audio sampling attributes.
     *
     * @param handle Indicates the audio handle.
     * @param attrs Indicates the pointer to the audio sampling attributes to set, such as the sampling rate,
     * sampling precision, and channel.
     * @return Returns <b>0</b> if the setting is successful; returns a negative value otherwise.
     * @see GetSampleAttributes
     */
    int32_t (*SetSampleAttributes)(AudioHandle handle, const struct AudioSampleAttributes *attrs);

    /**
     * @brief Obtains audio sampling attributes.
     *
     * @param handle Indicates the audio handle.
     * @param attrs Indicates the pointer to the audio sampling attributes, such as the sampling rate,
     * sampling precision, and channel.
     * @return Returns <b>0</b> if audio sampling attributes are obtained; returns a negative value otherwise.
     * @see SetSampleAttributes
     */
    int32_t (*GetSampleAttributes)(AudioHandle handle, struct AudioSampleAttributes *attrs);

    /**
     * @brief Obtains the data channel ID of the audio.
     *
     * @param handle Indicates the audio handle.
     * @param channelId Indicates the pointer to the data channel ID.
     * @return Returns <b>0</b> if the data channel ID is obtained; returns a negative value otherwise.
     */
    int32_t (*GetCurrentChannelId)(AudioHandle handle, uint32_t *channelId);
};

#endif /* AUDIO_ATTRIBUTE_H */
/** @} */
