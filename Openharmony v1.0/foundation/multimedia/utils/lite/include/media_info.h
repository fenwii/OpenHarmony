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
 * @addtogroup MultiMedia_MediaCommon
 * @{
 *
 * @brief Provides data types and media formats required for recording and playing audio and videos.
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file media_info.h
 *
 * @brief Declares the <b>media_info</b> class and provides various audio, video, and codec types.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef MEDIA_INFO_H
#define MEDIA_INFO_H
#include <string>

/**
 * Indicates the constant quality mode. In this mode, the bit rate is not limited to guarantee the image quality to
 * the largest extent.
 */
const int BITRATE_MODE_CQ  = 0;

/**
 * Indicates the variable bit rate mode. In this mode, the codec dynamically adjusts the output bit rate based on
 * the image complexity. The codec increases the bit rate if the image is complex and decreases the bit rate if the
 * image is simple.
 */
const int BITRATE_MODE_VBR = 1;

/** Indicates the constant bit rate mode. In this mode, the codec keeps the output bit rate as constant as possible. */
const int BITRATE_MODE_CBR = 2;

/** Indicates the ARGB8888 color format. */
const int32_t COLOR_FORMAT_ARGB8888_32BIT  = 16;

/** Indicates the YUV420SP color format. */
const int32_t COLOR_FORMAT_YUV420SP        = 21;

/** Indicates that the current frame is an Instantaneous Decoder Refresh (IDR) frame. */
const std::string KEY_IS_SYNC_FRAME = "is-sync-frame";

/** Indicates the frame timestamp. */
const std::string KEY_TIME_US = "timeUs";

/**
 * @brief Enumerates audio source types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** Invalid audio source */
    AUDIO_SOURCE_INVALID = -1,
    /** Default audio source */
    AUDIO_SOURCE_DEFAULT = 0,
    /** Microphone */
    AUDIO_MIC = 1,
    /** Uplink voice */
    AUDIO_VOICE_UPLINK = 2,
    /** Downlink voice */
    AUDIO_VOICE_DOWNLINK = 3,
    /** Voice call */
    AUDIO_VOICE_CALL = 4,
    /** Camcorder */
    AUDIO_CAMCORDER = 5,
    /** Voice recognition */
    AUDIO_VOICE_RECOGNITION = 6,
    /** Voice communication */
    AUDIO_VOICE_COMMUNICATION = 7,
    /** Remote submix */
    AUDIO_REMOTE_SUBMIX = 8,
    /** Unprocessed audio */
    AUDIO_UNPROCESSED = 9,
    /** Voice performance */
    AUDIO_VOICE_PERFORMANCE = 10,
    /** Echo reference */
    AUDIO_ECHO_REFERENCE = 1997,
    /** Radio tuner */
    AUDIO_RADIO_TUNER = 1998,
    /** Hotword */
    AUDIO_HOTWORD = 1999,
    /** Extended remote submix */
    AUDIO_REMOTE_SUBMIX_EXTEND = 10007,
} AudioSourceType;

/**
 * @brief Defines the audio Device Descriptor.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /** Device name */
    std::string deviceName;
    /** Type of the audio input source */
    AudioSourceType inputSourceType;
    /** Bits 31-24: reserved bits; bits 23-16: mode ID; bits 15-8: device ID; bits 7-0: channel ID */
    uint32_t deviceId;
} AudioDeviceDesc;

/**
 * @brief Enumerates audio stream types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** Default audio stream type */
    TYPE_DEFAULT = -1,
    /** Media */
    TYPE_MEDIA = 0,
    /** Voice call */
    TYPE_VOICE_COMMUNICATION = 1,
    /** System sound */
    TYPE_SYSTEM = 2,
    /** Ringtone */
    TYPE_RING = 3,
    /** Music */
    TYPE_MUSIC = 4,
    /** Alarm */
    TYPE_ALARM = 5,
    /** Notification */
    TYPE_NOTIFICATION = 6,
    /** Bluetooth Synchronous Connection-Oriented (SCO) */
    TYPE_BLUETOOTH_SCO = 7,
    /** Enforced audible */
    TYPE_ENFORCED_AUDIBLE = 8,
    /** Dual-tone multi-frequency (DTMF) */
    TYPE_DTMF = 9,
    /** Text-To-Speech (TTS) */
    TYPE_TTS = 10,
    /** Accessibility */
    TYPE_ACCESSIBILITY = 11,
} AudioStreamType;

/**
 * @brief Enumerates video codec formats.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** Default format */
    VIDEO_DEFAULT = 0,
    /** H.264 */
    H264 = 2,
    /** High Efficiency Video Coding (HEVC) */
    HEVC = 5,
} VideoCodecFormat;

/**
 * @brief Enumerates audio codec formats.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** Default format */
    AUDIO_DEFAULT = 0,
    /** Advanced Audio Coding Low Complexity (AAC-LC) */
    AAC_LC      =   1,
    /** High-Efficiency Advanced Audio Coding (AAC-HE), previously known as AAC+ or aacPlus v1 */
    AAC_HE_V1   =   2,
    /** AAC++ or aacPlus v2 */
    AAC_HE_V2   =   3,
    /** Advanced Audio Coding Low Delay (AAC-LD) */
    AAC_LD      =   4,
    /** Advanced Audio Coding Enhanced Low Delay (AAC-ELD) */
    AAC_ELD     =   5,
    /** Invalid value */
    FORMAT_BUTT,
} AudioCodecFormat;

/**
 * @brief Enumerates audio bit widths.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** 8-bit width */
    BIT_WIDTH_8   = 8,
    /** 16-bit width */
    BIT_WIDTH_16  = 16,
    /** 24-bit width */
    BIT_WIDTH_24  = 24,
    /** Invalid value */
    BIT_WIDTH_BUTT,
} AudioBitWidth;
#endif  // MEDIA_INFO_H
