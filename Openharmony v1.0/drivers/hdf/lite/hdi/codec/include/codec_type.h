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
 * @addtogroup Codec
 * @{
 *
 * @brief Defines codec-related APIs
 *
 * including custom data types and functions for initializing audio and video codecs,
 * setting parameters, and controlling and transferring data.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file codec_type.h
 *
 * @brief Declares custom data types used in API declarations for the Codec module,
 * including the codec types, audio and video parameters, input and output data, and callbacks.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef CODEC_TYPE_H
#define CODEC_TYPE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Defines the pointer to the codec handle, which is the context information for function calls.
 */
typedef void *CODEC_HANDLETYPE;

/**
 * @brief Enumerates codec types.
 */
typedef enum {
    VIDEO_DECODER, /**< Video decoding */
    VIDEO_ENCODER, /**< Video encoding */
    AUDIO_DECODER, /**< Audio decoding */
    AUDIO_ENCODER, /**< Audio encoding */
    INVALID_TYPE   /**< Invalid type */
} CodecType;

/**
 * @brief Enumerates indexes of parameter types.
 */
typedef enum {
    KEY_MIMETYPE = 0x01,      /**< MIME type. For the value type, see {@link AvCodecMime}. */
    KEY_BUFFERSIZE,           /**< Buffer size. The value type is uint32_t. */
    KEY_LEFT_STREAM_FRAMES,   /**< Number of frames in the remaining data streams. The value type is uint32_t. */
    KEY_CODEC_TYPE,           /**< Codec type. For the value type, see {@link CodecType}. */
    KEY_DIRECTION_TYPE,       /**< Input/Output type. For the value type, see {@link DirectionType}. */

    KEY_BITRATE = 0x500,      /**< Bit rate. The value type is uint32_t. */
    KEY_WIDTH = 0x1000,       /**< Width. The value type is uint32_t. */
    KEY_HEIGHT,               /**< Hight. The value type is uint32_t. */
    KEY_STRIDE,               /**< Stride. The value type is uint32_t. */
    KEY_VIDEO_FIELD,          /**< Video field. For the value type, see {@link VideoField}. */
    KEY_PIXEL_FORMAT,         /**< Pixel format. For the value type, see {@link PixelFormat}. */
    KEY_VIDEO_RC_MODE,        /**< Rate control mode. For the value type, see {@link VenCodeRcMode}. */
    KEY_VIDEO_GOP_MODE,       /**< GOP mode. For the value type, see {@link VenCodeGopMode}. */
    KEY_VIDEO_PIC_SIZE,       /**< Image resolution. For the value type, see {@link PicSize}. */
    KEY_VIDEO_PROFILE,        /**< Codec profile. The value type is uint32_t. */
    KEY_VIDEO_FRAME_RATE,     /**< Frame rate. The value type is uint32_t. */

    KEY_SAMPLE_RATE = 0x1500, /**< Sampling rate. The value type is uint32_t. */
    KEY_AUDIO_PROFILE,        /**< Audio encoding profile. The value type is uint32_t. */
    KEY_CHANNEL_COUNT,        /**< Number of channels. The value type is uint32_t. */
    KEY_BITWITH,              /**< Bit width. For the value type, see {@link AudioBitWidth}. */
    KEY_SOUND_MODE,           /**< Audio channel mode. For the value type, see {@link AudioSoundMode}. */
    KEY_POINT_NUM_PER_FRAME,  /**< Number of sampling points per frame. The value type is uint32_t. */
    KEY_DEVICE_ID,            /**< Device ID. The value type is uint32_t. */
} ParamKey;

/**
 * @brief Enumerates control modes of the channel encoding rate.
 */
typedef enum {
    VENCOD_RC_CBR = 0, /**< Fixed bit rate*/
    VENCOD_RC_VBR,     /**< Variable bit rate */
    VENCOD_RC_AVBR,    /**< Adaptive variable bit rate */
    VENCOD_RC_QVBR,    /**< Quality-defined variable bit rate */
    VENCOD_RC_CVBR,    /**< Constrained variable bit rate */
    VENCOD_RC_QPMAP,   /**< Configuration-mapped quantization parameters */
    VENCOD_RC_FIXQP    /**< Fixed quantization parameters */
} VenCodeRcMode;

/**
 * @brief Enumerates resolutions.
 */
typedef enum {
    Resolution_CIF,     /**< 352x288 */
    Resolution_360P,    /**< 640x360 */
    Resolution_D1_PAL,  /**< 720x576 */
    Resolution_D1_NTSC, /**< 720x480 */
    Resolution_720P,    /**< 1280x720 */
    Resolution_1080P,   /**< 1920x1080 */
    Resolution_INVALID  /**< Invalid resolution */
} PicSize;

/**
 * @brief Enumerates types of group of pictures (GOP).
 */
typedef enum {
    VENCOD_GOPMODE_NORMALP = 0,   /**< P-frames using only one reference frame during encoding */
    VENCOD_GOPMODE_DUALP = 1,     /**< P-frames using two reference frames during encoding */
    VENCOD_GOPMODE_SMARTP = 2,    /**< Smart P-frames for encoding */
    VENCOD_GOPMODE_ADVSMARTP = 3, /**< Advanced smart P-frames for encoding */
    VENCOD_GOPMODE_BIPREDB = 4,   /**< B-frames for encoding */
    VENCOD_GOPMODE_LOWDELAYB = 5, /**< B-frames using only previous frames as references during encoding. */
    VENCOD_GOPMODE_INVALID,       /**< Invalid type */
} VenCodeGopMode;

/**
 * @brief Defines the pointer to the type of the dynamic parameter value.
 */
typedef void *ValueType;

/**
 * @brief Describes the dynamic parameter structure, which is mainly used
 * by {@link CodecCreate} and {@link CodecSetParameter}.
 */
typedef struct {
    ParamKey  key;    /**< Parameter type index */
    void      *val; /**< Pointer to the parameter value */
    int       size; /**< Parameter value size */
} Param;

/**
 * @brief Enumerates video frame fields.
 */
typedef enum {
    VID_FIELD_TOP         = 0x1,    /**< Top fields on even-number lines */
    VID_FIELD_BOTTOM      = 0x2,    /**< Bottom fields on odd-number lines */
    VID_FIELD_INTERLACED  = 0x3,    /**< Interlaced fields */
    VID_FIELD_FRAME       = 0x4,    /**< Non-interlaced frames */
    VID_FIELD_INVALID               /**< Invalid fields */
} VideoField;

/**
 * @brief Enumerates pixel formats.
 */
typedef enum {
    YVU_SEMIPLANAR_420 = 0,  /**< YUV 420 SP */
    YVU_SEMIPLANAR_420_TILE, /**< YUV SP 420 TILE */
    PIX_FORMAT_INVALID       /**< Invalid format */
} PixelFormat;

/**
 * @brief Enumerates audio channel modes.
 */
typedef enum {
    AUD_SOUND_MODE_MONO   = 0, /**< Mono channel */
    AUD_SOUND_MODE_STEREO = 1, /**< Stereo mode*/
    AUD_SOUND_MODE_INVALID     /**< Invalid mode */
} AudioSoundMode;

/**
 * @brief Enumerates audio sampling rates.
 */
typedef enum {
    AUD_SAMPLE_RATE_8000   = 8000,    /**< 8 KHz */
    AUD_SAMPLE_RATE_12000  = 12000,   /**< 12 KHz */
    AUD_SAMPLE_RATE_11025  = 11025,   /**< 11.025 KHz */
    AUD_SAMPLE_RATE_16000  = 16000,   /**< 16 KHz */
    AUD_SAMPLE_RATE_22050  = 22050,   /**< 22.050 KHz */
    AUD_SAMPLE_RATE_24000  = 24000,   /**< 24 KHz */
    AUD_SAMPLE_RATE_32000  = 32000,   /**< 32 KHz  */
    AUD_SAMPLE_RATE_44100  = 44100,   /**< 44.1 KHz */
    AUD_SAMPLE_RATE_48000  = 48000,   /**< 48 KHz */
    AUD_SAMPLE_RATE_64000  = 64000,   /**< 64 KHz */
    AUD_SAMPLE_RATE_96000  = 96000,   /**< 96 KHz */
    AUD_SAMPLE_RATE_INVALID,          /**< Invalid sampling rate */
} AudioSampleRate;

/**
 * @brief Enumerates audio bit rates.
 */
typedef enum {
    AUD_AAC_BPS_8K      = 8000,    /**< 8 kbit/s */
    AUD_AAC_BPS_16K     = 16000,   /**< 16 kbit/s */
    AUD_AAC_BPS_22K     = 22000,   /**< 22 kbit/s */
    AUD_AAC_BPS_24K     = 24000,   /**< 24 kbit/s */
    AUD_AAC_BPS_32K     = 32000,   /**< 32 kbit/s */
    AUD_AAC_BPS_48K     = 48000,   /**< 48 kbit/s */
    AUD_AAC_BPS_64K     = 64000,   /**< 64 kbit/s */
    AUD_AAC_BPS_96K     = 96000,   /**< 96 kbit/s */
    AUD_AAC_BPS_128K    = 128000,  /**< 128 kbit/s */
    AUD_AAC_BPS_256K    = 256000,  /**< 256 kbit/s */
    AUD_AAC_BPS_320K    = 320000,  /**< 320 kbit/s */
} AudioBitRate;

/**
* @brief Enumerates stream flags.
 */
typedef enum {
    STREAM_FLAG_KEYFRAME = 1,             /**< Keyframe */
    STREAM_FLAG_CODEC_SPECIFIC_INF = 2,   /**< Codec specifications */
    STREAM_FLAG_EOS = 4,                  /**< End of streams */
    STREAM_FLAG_PART_OF_FRAME = 8,        /**< Partial frame */
    STREAM_FLAG_END_OF_FRAME = 16,        /**< End of frames, used in pair with <b> STREAM_FLAG_PART_OF_FRAME</b> */
} StreamFlagType;

/**
 * @brief Defines the buffer handle type. The virtual address of a handle maps to its physical address.
 */
typedef struct BufferHandle {
    uint8_t *virAddr;   /**< Virtual address */
    uintptr_t handle;   /**< Physical address */
} BufferHandle;

/**
* @brief Enumerates buffer types.
 */
typedef enum BufferType {
    BUFFER_TYPE_VIRTUAL = 0, /**< Virtual memory */
    BUFFER_TYPE_FD,          /**< File descriptor, which can be used cross processes */
    BUFFER_TYPE_HANDLE,      /**< Handle, which can be used cross processes */
} BufferType;

/**
 * @brief Describes buffer information.
 */
typedef struct {
    BufferType type;          /**< Buffer type */
    /**
     * @brief Describes the buffer address.
     */
    union {
        uint8_t       *addr;  /**< Virtual address */
        int32_t       fd;     /**< File descriptor */
        BufferHandle  handle; /**< Data handle. For details, see {@link BufferHandle} */
    };
    uint32_t offset;          /**< Buffer offset */
    uint32_t length;          /**< Length of valid data */
    uint32_t size;            /**< Total size of buffer blocks*/
} CodecBufferInfo;

/**
 * @brief Describes input information.
 */
typedef struct {
    uint32_t   bufferCnt;     /**< Number of buffers */
    CodecBufferInfo *buffers; /**< Pointer to the buffer description. For details, see {@link CodecBufferInfo}. */
    int64_t  pts;             /**< Input timestamp */
    int32_t  flag;            /**< Input flag. For details, see {@link StreamFlagType}. */
} InputInfo;

/**
 * @brief Describes output information.
 */
typedef struct OutputInfo {
    uint32_t   bufferCnt;      /**< Number of buffers */
    CodecBufferInfo *buffers;  /**< Pointer to the buffer description. For details, see {@link CodecBufferInfo}. */
    int64_t    timeStamp;      /**< Output timestamp */
    uint32_t   sequence;       /**< Corresponding input sequence number */
    uint32_t   flag;           /**< Output flag */
    CodecType  type;           /**< Codec type */
    void       *vendorPrivate; /**< Private information about a device vendor */
} OutputInfo;

/**
 * @brief Enumerates MIME types.
 */
typedef enum {
    MEDIA_MIMETYPE_IMAGE_JPEG = 0, /**< JPEG image */
    MEDIA_MIMETYPE_VIDEO_AVC,      /**< H.264 video */
    MEDIA_MIMETYPE_VIDEO_HEVC,     /**< H.265 video */
    MEDIA_MIMETYPE_AUDIO_AAC,      /**< AAC audio */
    MEDIA_MIMETYPE_INVALID,        /**< Invalid MIME type */
} AvCodecMime;

/**
 * @brief Enumerates codec profiles.
 */
typedef enum {
    INVALID_PROFILE = 0,               /**< Invalid profile */
    AAC_LC_PROFILE = 0x1000,           /**< AAC-Low Complex */
    AAC_MAIN_PROFILE,                  /**< AAC-Main */
    AAC_HE_V1_PROFILE,                 /**< HEAAC,  AAC+, or AACPlusV1 */
    AAC_HE_V2_PROFILE,                 /**< AAC++ or AACPlusV2 */
    AAC_LD_PROFILE,                    /**< AAC-Low Delay */
    AAC_ELD_PROFILE,                   /**< AAC-Enhanced Low Delay */
    AVC_BASELINE_PROFILE = 0x2000,     /**< H.264 Baseline */
    AVC_MAIN_PROFILE,                  /**< H.264 Main */
    AVC_HIGH_PROFILE,                  /**< H.264 High */
    HEVC_MAIN_PROFILE = 0x3000,        /**< H.265 Main */
    HEVC_MAIN_10_PROFILE,              /**< H.265 Main 10 */
} Profile;

/**
 * @brief Enumerates codec levels.
 */
typedef enum {
    INVALID_LEVEL = 0,                 /**< Invalid level */
    AVC_LEVEL_1 = 0x1000,              /**< H.264 level 1 */
    HEVC_LEVEL_MAIN_1 = 0x2000,        /**< H.265 Main level 1 */
    HEVC_LEVEL_MAIN_2,                 /**< H.265 Main level 2 */
} Level;

/**
 * @brief Indicates the maximum number of reserved parameters in the array.
 */
#define ELEMENT_MAX_LEN 50

/**
 * @brief Defines a variable-length queue.
 */
typedef struct {
    uint32_t element[ELEMENT_MAX_LEN]; /**< Array of reserved parameters */
    uint32_t actualLen;                /**< Number of actual parameters */
} ResizableArray;

/**
* @brief Defines the alignment.
 */
typedef struct {
    int widthAlginment;  /**< Value to align with the width */
    int heightAlginment; /**< Value to align with the height */
} Alginment;

/**
 * @brief Defines a rectangle.
 */
typedef struct {
    int32_t width;  /**< Width */
    int32_t height; /**< Height */
} Rect;

/**
 * @brief Enumerates allocation modes of input and output buffers.
 */
typedef enum AllocateBufferMode {
    ALLOCATE_INPUT_BUFFER_CODEC  = 0x1, /**< Input buffer allocated within the Codec module */
    ALLOCATE_INPUT_BUFFER_USER   = 0x2, /**< Input buffer allocated by an external user */
    ALLOCATE_OUTPUT_BUFFER_CODEC = 0x4, /**< Output buffer allocated within the Codec module */
    ALLOCATE_OUTPUT_BUFFER_USER  = 0x8, /**< Output buffer allocated by an external user */
} AllocateBufferMode;

/**
 * @brief Enumerates playback capabilities.
 */
typedef enum CapsMask {
    ADAPTIVE_PLAYBACK  = 0x1, /**< Adaptive playback */
    SECURE_PLAYBACK   = 0x2,  /**< Secure playback */
} CapsMask;

/**
 * @brief Defines the codec capability.
 */
typedef struct Capbility {
    AvCodecMime mime;                   /**< MIME type */
    CodecType type;                     /**< Codec type */
    Alginment whAlignment;              /**< Value to align with the width and height */
    Rect minSize;                       /**< Minimum resolution supported */
    Rect maxSize;                       /**< Maximum resolution supported */
    uint64_t minBitRate;                /**< Minimum bit rate supported */
    uint64_t maxBitRate;                /**< Maximum bit rate supported */
    ResizableArray supportProfiles;     /**< Supported profiles */
    ResizableArray supportLevels;       /**< Supported levels */
    ResizableArray supportPixelFormats; /**< Supported pixel formats */
    uint32_t minInputBufferNum;         /**< Minimum number of input buffers required for running */
    uint32_t minOutputBufferNum;        /**< Minimum number of output buffers required for running */
    uint32_t allocateMask;              /**< Buffer allocation mode. For details, see {@link AllocateBufferMode}. */
    uint32_t capsMask;                  /**< Capability mask. For details, see {@link CapsMask}. */
} CodecCapbility;

/**
 * @brief Enumerates event types.
 */
typedef enum {
    EventError,            /**< Event error */
    EventFlushCompelte,    /**< Buffer flush completed */
    EventStopCompelte,     /**< Codec stopped */
    EventOutFormatChanged, /**< Output format changed */
    EventMax = 0x1FFFFFFF  /**< Maximum event value */
} EventType;

/**
 * @brief Redefines the unsigned pointer type, which is used for pointer conversion.
 */
typedef uintptr_t UINTPTR;

/**
 * @brief Defines callbacks and their parameters.
 */
typedef struct {
    /**
     * @brief Reports an event.
     *
     * Reports event errors and output format changes.
     *
     * @param hComponent Indicates the handle of the codec component.
     * @param pAppData Indicates upper-layer data, which is generally
     * an upper-layer instance passed when this callback is set.
     * @param EVENTTYPE Indicates the event type.
     * @param nData1 Indicates the first value contained in the reported event. This parameter is optional.
     * @param nData2 Indicates the second value contained in the reported event. This parameter is optional.
     * @param pEventData Indicates the pointer to data contained in the reported event. This parameter is optional.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     */
    int (*OnEvent)(UINTPTR comp, UINTPTR appData, EventType event,
        uint32_t data1, uint32_t data2, UINTPTR eventData);

    /**
     * @brief Reports that the input data has been used.
     *
     * This callback is invoked in asynchronous mode.
     *
     * @param hComponent Indicates the handle of the codec component.
     * @param pAppData Indicates upper-layer data, which is generally
     * an upper-layer instance passed when this callback is set.
     * @param pBuffer Indicates the pointer to the input data that has been used.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     */
    int (*InputBufferAvailable)(UINTPTR comp, UINTPTR appData, InputInfo *inBuf);

    /**
     * @brief Reports that the output is complete.
     *
     * This callback is invoked in asynchronous mode.
     *
     * @param hComponent Indicates the handle of the codec component.
     * @param pAppData Indicates upper-layer data, which is generally
     * an upper-layer instance passed when this callback is registered.
     * @param pBuffer Indicates the pointer to the output data that has been generated.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     */
    int (*OutputBufferAvailable)(UINTPTR comp, UINTPTR appData, OutputInfo *outBuf);
} CodecCallback;

/**
 * @brief Enumerates input and output types.
 */
typedef enum {
    INPUT_TYPE,  /**< Input */
    OUTPUT_TYPE, /**< Output */
    ALL_TYPE,    /**< Input and output */
} DirectionType;

/**
 * @brief Enumerates allocation types.
 */
typedef enum {
    INTERNAL, /**< Internal */
    EXTERNAL, /**< External */
} BufferMode;

/**
 * @brief Enumerates codec error types.
 */
enum {
    CODEC_ERR_STREAM_BUF_FULL = 100, /**< Elementary stream buffer queue is full. */
    CODEC_ERR_FRAME_BUF_EMPTY,       /**< Frame buffer queue is empty. */
    CODEC_RECEIVE_EOS,               /**< End of streams */
    CODEC_ERR_INVALID_OP,            /**< Invalid operation */
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* CODEC_TYPE_H */
/** @} */