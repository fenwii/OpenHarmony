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
 * @file audio_types.h
 *
 * @brief Defines custom data types used in API declarations for the audio module, including audio ports,
 * adapter descriptors, device descriptors, scene descriptors, sampling attributes, and timestamp.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_TYPES_H
#define AUDIO_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Defines the audio handle.
 */
typedef void *AudioHandle;

/**
 * @brief Enumerates the audio port type.
 */
enum AudioPortDirection {
    PORT_OUT    = 0x1u, /**< Output port */
    PORT_IN     = 0x2u, /**< Input port */
    PORT_OUT_IN = 0x3u, /**< Input/output port, supporting both audio input and output */
};

/**
 * @brief Defines the audio port.
 */
struct AudioPort {
    enum AudioPortDirection dir; /**< Audio port type. For details, see {@link AudioPortDirection} */
    uint32_t portId;             /**< Audio port ID */
    const char *portName;        /**< Audio port name */
};

/**
 * @brief Defines the audio adapter descriptor.
 *
 * An audio adapter is a set of port drivers for a sound card, including the output and input ports.
 * One port corresponds to multiple pins, and each pin belongs to a physical component (such as a
 * speaker or a wired headset).
 */
struct AudioAdapterDescriptor {
    const char *adapterName; /**< Name of the audio adapter */
    uint32_t portNum;        /**< Number of ports supported by an audio adapter */
    struct AudioPort *ports; /**< List of ports supported by an audio adapter */
};

/**
 * @brief Enumerates the pin of an audio adapter.
 */
enum AudioPortPin {
    PIN_NONE        = 0x0u,       /**< Invalid pin */
    PIN_OUT_SPEAKER = 0x1u,       /**< Speaker output pin */
    PIN_OUT_HEADSET = 0x2u,       /**< Wired headset pin for output */
    PIN_OUT_LINEOUT = 0x4u,       /**< Line-out pin */
    PIN_OUT_HDMI    = 0x8u,       /**< HDMI output pin */
    PIN_IN_MIC      = 0x8000001u, /**< Microphone input pin */
    PIN_IN_HS_MIC   = 0x8000002u, /**< Wired headset microphone pin for input */
    PIN_IN_LINEIN   = 0x8000004u, /**< Line-in pin */
};

/**
 * @brief Defines the audio device descriptor.
 */
struct AudioDeviceDescriptor {
    uint32_t portId;        /**< Audio port ID */
    enum AudioPortPin pins; /**< Pins of audio ports (input and output). For details, see {@link AudioPortPin}. */
    const char *desc;       /**< Audio device name */
};

/**
 * @brief Enumerates the audio category.
 */
enum AudioCategory {
    AUDIO_IN_MEDIA = 0,     /**< Media */
    AUDIO_IN_COMMUNICATION, /**< Communications */
};

/**
 * @brief Defines the audio scene descriptor.
 */
struct AudioSceneDescriptor {
    /**
     * @brief Describes the audio scene.
     */
    union SceneDesc {
        uint32_t id;                   /**< Audio scene ID */
        const char *desc;              /**< Name of the audio scene */
    } scene;                           /**< The <b>scene</b> object */
    struct AudioDeviceDescriptor desc; /**< Audio device descriptor */
};

/**
 * @brief Enumerates the audio format.
 */
enum AudioFormat {
    AUDIO_FORMAT_PCM_8_BIT  = 0x1u,       /**< 8-bit PCM */
    AUDIO_FORMAT_PCM_16_BIT = 0x2u,       /**< 16-bit PCM */
    AUDIO_FORMAT_PCM_24_BIT = 0x3u,       /**< 24-bit PCM */
    AUDIO_FORMAT_PCM_32_BIT = 0x4u,       /**< 32-bit PCM */
    AUDIO_FORMAT_AAC_MAIN   = 0x1000001u, /**< AAC main */
    AUDIO_FORMAT_AAC_LC     = 0x1000002u, /**< AAC LC */
    AUDIO_FORMAT_AAC_LD     = 0x1000003u, /**< AAC LD */
    AUDIO_FORMAT_AAC_ELD    = 0x1000004u, /**< AAC ELD */
    AUDIO_FORMAT_AAC_HE_V1  = 0x1000005u, /**< AAC HE_V1 */
    AUDIO_FORMAT_AAC_HE_V2  = 0x1000006u, /**< AAC HE_V2 */
};

/**
 * @brief Enumerates the audio channel mask.
 *
 * A mask describes an audio channel position.
 */
enum AudioChannelMask {
    AUDIO_CHANNEL_FRONT_LEFT  = 0x1,  /**< Front left channel */
    AUDIO_CHANNEL_FRONT_RIGHT = 0x2,  /**< Front right channel */
    AUDIO_CHANNEL_MONO        = 0x1u, /**< Mono channel */
    AUDIO_CHANNEL_STEREO      = 0x3u, /**< Stereo channel, consisting of front left and front right channels */
};

/**
 * @brief Enumerates masks of audio sampling rates.
 */
enum AudioSampleRatesMask {
    AUDIO_SAMPLE_RATE_MASK_8000    = 0x1u,        /**< 8 kHz */
    AUDIO_SAMPLE_RATE_MASK_12000   = 0x2u,        /**< 12 kHz */
    AUDIO_SAMPLE_RATE_MASK_11025   = 0x4u,        /**< 11.025 kHz */
    AUDIO_SAMPLE_RATE_MASK_16000   = 0x8u,        /**< 16 kHz */
    AUDIO_SAMPLE_RATE_MASK_22050   = 0x10u,       /**< 22.050 kHz */
    AUDIO_SAMPLE_RATE_MASK_24000   = 0x20u,       /**< 24 kHz */
    AUDIO_SAMPLE_RATE_MASK_32000   = 0x40u,       /**< 32 kHz */
    AUDIO_SAMPLE_RATE_MASK_44100   = 0x80u,       /**< 44.1 kHz */
    AUDIO_SAMPLE_RATE_MASK_48000   = 0x100u,      /**< 48 kHz */
    AUDIO_SAMPLE_RATE_MASK_64000   = 0x200u,      /**< 64 kHz */
    AUDIO_SAMPLE_RATE_MASK_96000   = 0x400u,      /**< 96 kHz */
    AUDIO_SAMPLE_RATE_MASK_INVALID = 0xFFFFFFFFu, /**< Invalid sampling rate */
};

/**
 * @brief Defines audio sampling attributes.
 */
struct AudioSampleAttributes {
    enum AudioCategory type; /**< Audio type. For details, see {@link AudioCategory} */
    bool interleaved;        /**< Interleaving flag of audio data */
    enum AudioFormat format; /**< Audio data format. For details, see {@link AudioFormat}. */
    uint32_t sampleRate;     /**< Audio sampling rate */
    uint32_t channelCount;   /**< Number of audio channels. For example, for the mono channel, the value is 1,
                              * and for the stereo channel, the value is 2.
                              */
};

/**
 * @brief Defines the audio timestamp, which is a substitute for POSIX <b>timespec</b>.
 */
struct AudioTimeStamp {
    int64_t tvSec;  /**< Seconds */
    int64_t tvNSec; /**< Nanoseconds */
};

/**
 * @brief Enumerates the passthrough data transmission mode of an audio port.
 */
enum AudioPortPassthroughMode {
    PORT_PASSTHROUGH_LPCM    = 0x1, /**< Stereo PCM */
    PORT_PASSTHROUGH_RAW     = 0x2, /**< HDMI passthrough */
    PORT_PASSTHROUGH_HBR2LBR = 0x4, /**< Blu-ray next-generation audio output with reduced specifications */
    PORT_PASSTHROUGH_AUTO    = 0x8, /**< Mode automatically matched based on the HDMI EDID */
};

/**
 * @brief Defines the sub-port capability.
 */
struct AudioSubPortCapability {
    uint32_t portId;                    /**< Sub-port ID */
    const char *desc;                   /**< Sub-port name */
    enum AudioPortPassthroughMode mask; /**< Passthrough mode of data transmission. For details,
                                         * see {@link AudioPortPassthroughMode}.
                                         */
};

/**
 * @brief Defines the audio port capability.
 */
struct AudioPortCapability {
    uint32_t deviceType;                     /**< Device type (output or input) */
    uint32_t deviceId;                       /**< Device ID used for device binding */
    bool hardwareMode;                       /**< Whether to support device binding */
    uint32_t formatNum;                      /**< Number of the supported audio formats */
    enum AudioFormat *formats;               /**< Supported audio formats. For details, see {@link AudioFormat}. */
    uint32_t sampleRateMasks;                /**< Supported audio sampling rates (8 kHz, 16 kHz, 32 kHz, and 48 kHz) */
    enum AudioChannelMask channelMasks;      /**< Audio channel layout mask of the device. For details,
                                              * see {@link AudioChannelMask}.
                                              */
    uint32_t channelCount;                   /**< Supported maximum number of audio channels */
    uint32_t subPortsNum;                    /**< Number of supported sub-ports (for output devices only) */
    struct AudioSubPortCapability *subPorts; /**< List of supported sub-ports */
};

/**
 * @brief Enumerates channel modes for audio rendering.
 *
 * @attention The following modes are set for rendering dual-channel audios. Others are not supported.
 */
enum AudioChannelMode {
    AUDIO_CHANNEL_NORMAL = 0, /**< Normal mode. No processing is required. */
    AUDIO_CHANNEL_BOTH_LEFT,  /**< Two left channels */
    AUDIO_CHANNEL_BOTH_RIGHT, /**< Two right channels */
    AUDIO_CHANNEL_EXCHANGE,   /**< Data exchange between the left and right channels. The left channel takes the audio
                               * stream of the right channel, and the right channel takes that of the left channel.
                               */
    AUDIO_CHANNEL_MIX,        /**< Mix of streams of the left and right channels */
    AUDIO_CHANNEL_LEFT_MUTE,  /**< Left channel muted. The stream of the right channel is output. */
    AUDIO_CHANNEL_RIGHT_MUTE, /**< Right channel muted. The stream of the left channel is output. */
    AUDIO_CHANNEL_BOTH_MUTE,  /**< Both left and right channels muted */
};

#endif /* AUDIO_TYPES_H */
