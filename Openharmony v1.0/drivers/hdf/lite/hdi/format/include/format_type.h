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
 * @addtogroup format
 * @{
 *
 * @brief Defines format-related APIs.
 *
 * For example, you use this module to define custom data types and to initialize, create,
 * destroy the muxer and demuxer, and set their parameters. Also, you can read demuxer data frames,
 * select demuxer tracks, add muxer tracks, and write data frames into a container.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file format_type.h
 *
 * @brief Declares format-related structures and enumerations, including custom data types for file information,
 * programs, information about audio and video subtitle tracks, source data types, output data types, split types,
 * and data frames.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef FORMAT_TYPE_H
#define FORMAT_TYPE_H

#include <stdint.h>
#include <stdbool.h>
#include "parameter_item.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define FORMAT_MAX_LANGUAGE_NUM 4    /**< Indicates the number of languages in the subtitle file. */
#define FORMAT_LANGUAGE_LEN 4        /**< Indicates the number of characters contained in the language description. */
#define FORMAT_TITLE_LEN 64          /**< Indicates the number of title characters. */
#define FORMAT_INVALID_TRACK_ID -1   /**< Indicates an invalid track ID. */
#define FORMAT_INVALID_PROGRAM_ID -1 /**< Indicates an invalid program ID. */

/**
 * @brief Enumerates data frame types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    FRAME_TYPE_NONE,  /**< Unknown type, which can be used for transport stream (TS) packets */
    FRAME_TYPE_AUDIO, /**< Audio frame */
    FRAME_TYPE_VIDEO, /**< Video frame */
    FRAME_TYPE_IMAGE, /**< Image frame */
    FRAME_TYPE_SUB,   /**< Subtitle frame */
    FRAME_TYPE_DATA,  /**< Data */
    FRAME_TYPE_BUT,   /**< Undefined type */
} FrameType;

/**
 * @brief Enumerates seek modes.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    FORMAT_SEEK_MODE_FORWARD_KEY,  /**< Seeks forwards for the keyframe closest to specified position. */
    FORMAT_SEEK_MODE_BACKWARD_KEY, /**< Seeks backwards for the keyframe closest to specified position. */
    FORMAT_SEEK_MODE_CLOSEST_KEY,  /**< Seeks for the keyframe closest to specified position. */
    SEEK_MODE_BUT                  /**< Undefined mode */
} FormatSeekMode;

/**
 * @brief Enumerates audio, video, and image encoding formats.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    CODEC_H264 = 0, /**< H264 or AVC */
    CODEC_H265,     /**< H265 or HEVC */
    CODEC_JPEG,     /**< JPEG */
    CODEC_AAC,      /**< AAC */
    CODEC_G711A,    /**< G711A */
    CODEC_G711U,    /**< G711u */
    CODEC_PCM,      /**< PCM */
    CODEC_MP3,      /**< MP3 */
    CODEC_BUT,      /**< Undefined format */
} CodecFormat;

/**
* @brief Enumerates audio sampling formats.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    AUDIO_SAMPLE_FMT_S8 = 0, /**< 8-bit integer for a single sample */
    AUDIO_SAMPLE_FMT_S16,    /**< 16-bit integer for a single sample */
    AUDIO_SAMPLE_FMT_S24,    /**< 24-bit integer for a single sample */
    AUDIO_SAMPLE_FMT_S32,    /**< 32-bit integer for a single sample */
    AUDIO_SAMPLE_FMT_FLOAT,  /**< Single-precision floating point number for a single sample */
} AudioSampleFmt;

/**
 * @brief Enumerates subtitle frame types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    HI_SVR_SUBTITLE_BITMAP = 0x0, /**< Bitmap (BMP) */
    HI_SVR_SUBTITLE_TEXT,         /**< Text */
} SubtitleFrameType;

/**
 * @brief Defines the buffer configuration.
 *
 * If <b>maxSize</b> and <b>maxDurationMs</b> are valid at the same time,
 * the smaller value is used as the upper limit for the buffer.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int64_t maxSize;       /**< Maximum buffer size */
    int64_t maxDurationMs; /**< Maximum duration of a media file */
} FormatBufferSetting;

/**
 * @brief Defines the data frame, which is used for data transferring.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    FrameType frameType; /**< Data frame type. For details, see {@link FrameType}. */
    uint32_t trackId;    /**< Index of the track where the data frame is located */
    bool isKeyFrame;     /**< Keyframe flag. <b>false</b>: The data frame is not a keyframe.
                          * <b>true</b>: The data frame is a keyframe.
                          */
    int64_t timestampUs; /**< Timestamp of a data frame, in us */
    int64_t durationUs;  /**< Data frame duration, in us */
    uint8_t* data;       /**< Address of the data frame buffer */
    uint32_t len;        /**< Data frame length */
    uint32_t frameIndex; /**< Data frame index. For the MPF container, the value indicates
                          * the index of the sub-image frame.
                          */
    int64_t position;    /**< Position of the data frame in the file */
    int32_t itemCnt;     /**< Number of parameters, which can be used for information such as side data,
                          * PSSH, DRM, and HDR.
                          */
    ParameterItem *item; /**< Pointer to the parameter array */
} FormatFrame;

/**
 * @brief Enumerates subtitle file formats.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    FORMAT_SUB_ASS = 0x0, /**< ASS */
    FORMAT_SUB_LRC,       /**< LRC */
    FORMAT_SUB_SRT,       /**< SRT */
    FORMAT_SUB_SMI,       /**< SMI */
    FORMAT_SUB_SUB,       /**< SUB */
    FORMAT_SUB_TXT,       /**< RAW UTF-8 */
    FORMAT_SUB_HDMV_PGS,  /**< HDMV PGS */
    FORMAT_SUB_DVB_SUB,   /**< DVB */
    FORMAT_SUB_DVD_SUB,   /**< DVD */
    FORMAT_SUB_TTML,      /**< TTML */
    FORMAT_SUB_WEBVTT,    /**< WebVTT */
    FORMAT_SUB_BUTT       /**< Undefined format */
} SubtitleFormat;

/**
 * @brief Defines audio track information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    CodecFormat format; /**< Audio encoding format. For details, see {@link CodecFormat}. */
    uint32_t profile; /**< Audio encoding profile, for example, <b>0x160(WMAV1)</b> and <b>0x161 (WMAV2)</b>. */
    uint32_t sampleRate; /**< Audio sampling rate, for example, <b>8000</b>, <b>16000</b>, <b>24000</b>, <b>32000</b>,
                          * <b>11025</b>, <b>22050</b>, <b>441000</b>, and <b>48000</b>
                          */
    uint16_t sampleFmt; /**< Data storage format of one sample in an audio channel.
                         * For details, see {@link AudioSampleFmt}.
                         */
    uint16_t channels; /**< Number of audio channels */
    int32_t subStreamID; /**< ID of the subsidiary audio stream, which is used when the encoding or decoding format
                          * of the primary stream is not supported for audio rendering.
                          */
    uint32_t bitrate; /**< Audio and video bit rate */
    char language[FORMAT_LANGUAGE_LEN]; /**< Audio track language */
    int64_t durationMs; /**< Stream duration, in milliseconds */
} AudioTrackInfo;

/**
 * @brief Defines video track information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    CodecFormat format; /**< Video encoding format. For details, see {@link CodecFormat}. */
    uint16_t profile; /**< Profile */
    uint16_t width; /**< Width, in pixels */
    uint16_t height; /**< Height, in pixels*/
    uint16_t fpsNum; /**< Numerator of the frame rate */
    uint16_t fpsDen; /**< Denominator of the frame rate */
    uint32_t bitrate; /**< <Video bit rate, in bit/s */
    uint32_t rotate; /**< Video rotation angle. The value can be <b>90</b>, <b>180</b>, or <b>270</b>.
                      * The default value is <b>0</b>.
                      */
    int64_t durationMs; /**< Track duration, in milliseconds */
}VideoTrackInfo;

/**
 * @brief Defines image information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    CodecFormat format; /**< Image encoding format. For details, see {@link CodecFormat}. */
    uint16_t width; /**< Width, in pixels */
    uint16_t height; /**< Height, in pixels*/
    uint32_t rotate; /**< Image rotation angle. The value can be <b>90</b>, <b>180</b>, or <b>270</b>.
                      * The default value is <b>0</b>.
                      */
    uint32_t dataLength; /**< Image size */
    bool thumbnail; /**< Thumbnail flag */
} SubImageInfo;

/**
 * @brief Defines image stream information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int32_t subImageNum;        /**< Number of sub-images */
    SubImageInfo *subImageInfo; /**< Detailed information about a sub-image */
} ImageTrackInfo;

/**
 * @brief Defines subtitle stream information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    SubtitleFormat format; /**< Subtitle encoding and decoding format. For details, see {@link SubtitleFormat} */
    uint32_t charSet; /**< Character encoding format */
    char language[FORMAT_MAX_LANGUAGE_NUM][FORMAT_LANGUAGE_LEN]; /**< Subtitle language */
    uint16_t originalFrameWidth; /**< Width of the original image. This variable is valid for the image subtitle. */
    uint16_t originalFrameHeight; /**< Height of the original image. This variable is valid for the image subtitle. */
} SubtitleTrackInfo;

/**
 * @brief Enumerates track types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    TRACK_TYPE_VIDEO, /**< Video track */
    TRACK_TYPE_AUDIO, /**< Audio track */
    TRACK_TYPE_IMAGE, /**< Image track */
    TRACK_TYPE_SUB, /**< Subtitle track */
    TRACK_TYPE_DATA, /**< Data track */
    TRACK_TYPE_BUT, /**< Undefined track */
} TrackType;

/**
 * @brief Defines track information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    TrackType trackType; /**< Track type. For details, see {@link TrackType} */
    int32_t trackId; /**< Track index */
    union {
        VideoTrackInfo vidTrack; /**< Video track information */
        AudioTrackInfo audTrack; /**< Audio track information */
        SubtitleTrackInfo subTrack; /**< Subtitle track information */
        ImageTrackInfo imgTrack; /**< Image track information */
    };
    int32_t itemCnt; /**< Number of extra track information entries */
    ParameterItem *item; /**< Pointer to the array of extra track information, including HDR, DRM, and CAS */
} TrackInfo;

/**
 * @brief Defines program information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int32_t programId;  /**< Program index */
    int64_t durationMs; /**< Program duration */
    uint32_t trackNum;  /**< Number of tracks of the current program */
    TrackInfo *track;   /**< Pointer to the array of current program information */
} ProgramInfo;

/**
 * @brief Defines movie file information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    char *formatName; /**< Pointer to the name of the movie file container format */
    uint32_t bitrate; /**< Bit rate of the movie file */
    uint32_t programNum; /**< Number of programs */
    ProgramInfo *programInfo; /**< Pointer to the array of information about the movie file program */
} FileInfo;

/**
 * @brief Enumerates flags of raw stream data.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    DATA_FLAG_NONE = 0, /**< None */
    DATA_FLAG_SYNCFRAME = 1, /**< Synchronization frame */
    DATA_FLAG_CODECCONFIG = 2, /**< Codec configuration information */
    DATA_FLAG_EOS = 4, /**< End of a single stream */
    DATA_FLAG_PARTIAL_FRAME = 8, /**< Partial synchronization frame. This flag is used for multiple
                                  * segments (except for the last one) into which a single frame is divided.
                                  */
    DATA_FLAG_ENDOFFRAME = 16, /**< End of a frame. This flag is used in pair with <b>DATA_FLAG_PARTIAL_FRAME</b> for
                                * the last segment of the frame.
                                */
    DATA_FLAG_MUXER_DATA = 32, /**< Encapsulated data with its container */
} DataFlags;

/**
 * @brief Defines the function for reading stream data.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
    * @brief Reads data from streams, save the data to the buffer pointed by <b>data</b> with the specified <b>size</b>,
    * and returns the size of the read data and type.
    *
    * @param handle Indicates the pointer to the context handle.
    * @param data Indicates the pointer to the buffer to store the read data. The memory is allocated by the caller.
    * @param size Indicates the size of the available buffer memory.
    * @param timeOutMs Indicates read operation wait time. The value <b>0</b> means no wait time.
    * @param flags Indicates the pointer to the type of the read data, see {@link DataFlags}.
    * @return Returns the size of the read data.
    */
    int32_t (*ReadData)(void *handle, uint8_t *data, int32_t size, int32_t timeOutMs, DataFlags *flags);

    /**
    * @brief Obtains the size of data that can be read.
    *
    * Before reading data, you should call this function to check whether there is data to read.
    *
    * @param handle Indicates the pointer to the context handle.
    * @return Returns the size of the read data.
    */
    int32_t (*GetReadableSize)(const void *handle);

    void *handle; /**< Context handle */
} BufferStream;

/**
 * @brief Enumerates types of the demuxer data source.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    SOURCE_TYPE_FD = 0, /**< File descriptor */
    SOURCE_TYPE_URI, /**< URI, which can be a network address or a local file path */
    SOURCE_TYPE_STREAM, /**< Streams */
    SOURCE_TYPE_BUT /**< Undefined source */
} SourceType;

#define URL_LEN 4096 /**< Indicates the URL length. */

/**
 * @brief Defines the demuxer data source.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    SourceType type; /**< Data source type. For details, see {@link SourceType}. */
    /**
     * @brief Defines information about different types of data sources.
     */
    union {
        int fd; /**< Local file descriptor */
        char url[URL_LEN]; /**< Network URI or local file path. The maximum length is specified by <b>URL_LEN</b>. */
        BufferStream *stream; /**< Pointer to the function for reading buffer stream data */
    };
} FormatSource;

/**
 * @brief Enumerates output file formats.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    OUTPUT_FORMAT_MPEG_4 = 0, /**< MP4 */
    OUTPUT_FORMAT_TS = 1, /**< TS */
    OUTPUT_FORMAT_THREE_GPP = 2, /**< 3GPP */
    OUTPUT_FORMAT_HEIF = 3, /**< HEIF */
    OUTPUT_FORMAT_OGG = 4, /**< Ogg */
    OUTPUT_FORMAT_INVALID /**< Invalid format */
} OutputFormat;

/**
 * @brief Enumerates types of callback information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    MUXER_INFO_MAX_DURATION_APPROACHING = 0, /**< The capturing duration is reaching the threshold specified by
                                              * {@link FormatMuxerSetMaxFileDuration}. This information is reported
                                              * when only one second or 10% is left to reach the allowed duration.
                                              */
    MUXER_INFO_MAX_FILESIZE_APPROACHING,     /**< The captured file size is reaching the threshold specified by
                                              * {@link FormatMuxerSetMaxFileSize}. This information is reported when
                                              * only 100 KB or 10% is left to reach the allowed size.
                                              */
    MUXER_INFO_MAX_DURATION_REACHED,         /**< The capturing duration reached the threshold specified by
                                              * {@link FormatMuxerSetMaxFileDuration}, and the capturing is ended.
                                              * If the file is set by a file descriptor, the caller needs to close
                                              * the file.
                                              */
    MUXER_INFO_MAX_FILESIZE_REACHED,         /**< The captured file size reached the threshold specified by
                                              * {@link FormatMuxerSetMaxFileSize}, and the capturing is ended.
                                              * If the file is set by a file descriptor, the caller needs to
                                              * close the file.
                                              */
    MUXER_INFO_NEXT_OUTPUT_FILE_STARTED,     /**< The capturing started for the next output file. */
    MUXER_INFO_FILE_SPLIT_FINISHED,          /**< Manual file split is completed. */
    MUXER_INFO_FILE_START_TIME_MS,           /**< Start time of the captured file */

    DEMUXER_INFO_PREPARED = 10000,           /**< The prepare function is asynchronously executed. This information
                                              * is reported after the execution is complete.
                                              */
    DEMUXER_INFO_SEEK_COMPLETE,              /**< The seek function is asynchronously executed. This information is
                                              * reported after the execution is complete.
                                              */
    DEMUXER_INFO_NETWORK_DISCONNECTED,       /**< The network is disconnected during network playback. */
    DEMUXER_INFO_NETWORK_RECONNECTED,        /**< The network is automatically reconnected during network playback. */
} FormatInfoType;

/**
 * @brief Enumerates callback error types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    ERROR_UNKNOWN = 0 /** Unknown error */
} FormatErrorType;

/**
 * @brief Enumerates muxer output types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    OUTPUT_TYPE_FD = 0, /**< File descriptor */
    OUTPUT_TYPE_URI,    /**< Local file URI */
    OUTPUT_TYPE_INVALID /**< Undefined type */
} OutputType;

/**
 * @brief Defines the muxer output configuration.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    OutputType type;        /**< Output type. For details, see {@link OutputType}. */
    union {
        int32_t fd;         /**< File descriptor */
        char url[URL_LEN];  /**< File path. For details, see {@link URL_LEN}. */
    };
    OutputFormat format;    /**< File format */
} FormatOutputConfig;

/**
 * @brief Enumerates manual split types for the muxer.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    MANUAL_SPLIT_POST = 0, /**< Search forwards from the current I-frame and split the file at the closest I-frame. */
    MANUAL_SPLIT_PRE,      /**< Search backwards from the current I-frame and split the file at the closest I-frame. */
    MANUAL_SPLIT_NORMAL    /**< Normal split */
} ManualSplitType;

/**
 * @brief Enumerates types of the muxer source track.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    TRACK_SOURCE_TYPE_VIDEO = 0, /**< Video track */
    TRACK_SOURCE_TYPE_AUDIO, /**< Audio track */
    TRACK_SOURCE_TYPE_DATA, /**< Data track */
    TRACK_SOURCE_TYPE_INVALID /**< Invalid type */
} TrackSourceType;

/**
 * @brief Defines information about the muxer video source.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    CodecFormat codecType; /**< Video encoding type, for details, see {@link CodecFormat}. */
    uint32_t width; /**< Video width */
    uint32_t height; /**< Video height */
    uint32_t bitRate; /**< Encoding bit rate, in bit/s */
    uint32_t frameRate; /**< Encoding frame rate */
    float speed; /**< Video speed */
    uint32_t keyFrameInterval; /**< Keyframe interval */
} VideoTrackSourceInfo;

/**
 * @brief Defines information about the muxer audio source.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    CodecFormat codecType; /**< Audio encoding type, for details, see {@link CodecFormat}. */
    uint32_t sampleRate; /**< Sampling rate */
    uint32_t channelCount; /**< Number of audio channels */
    AudioSampleFmt sampleBitWidth; /**< Bit width */
    uint32_t samplesPerFrame; /**< Number of samples per frame */
    uint32_t avgBytesPerSec; /**< Average bit rate, in byte/s */
} AudioTrackSourceInfo;

/**
 * @brief Defines information about the muxer data source.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    uint32_t frameRate; /**< Frame rate */
    uint32_t bitRate; /**< Bit rate */
} DataTrackSourceInfo;

/**
 * @brief Defines information about the muxer source.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    TrackSourceType trackSourceType; /**< Stream source type. For details, see {@link TrackSourceType} */
    /**
     * @brief Defines detailed information about different types of stream sources.
     */
    union {
        VideoTrackSourceInfo videoInfo; /**< Video stream. For details, see {@link VideoTrackSourceInfo}. */
        AudioTrackSourceInfo audioInfo; /**< Audio stream. For details, see {@link AudioTrackSourceInfo}. */
        DataTrackSourceInfo dataInfo;   /**< Data stream. For details, see {@link DataTrackSourceInfo} */
    } trackSourceInfo;
} TrackSource;

/**
 * @brief Indicates the pointer to the callback handle for listening the muxer.
 *
 * @since 1.0
 * @version 1.0
 */
typedef void *CALLBACK_HANDLE;

/**
 * @brief Defines listener callbacks for the format.
 */
typedef struct {
    /** Private data handle */
    CALLBACK_HANDLE privateDataHandle;

    /**
     * @brief Called when a format error occurs during capturing. This callback is used to report the errors.
     *
     * @param privateDataHandle Indicates the private data handle.
     * @param errorType Indicates the error type. For details, see {@link FormatErrorType}.
     * @param errorCode Indicates the error code.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*OnError)(CALLBACK_HANDLE privateDataHandle, int32_t errorType, int32_t errorCode);

    /**
     * @brief Called when an information event occurs during capturing.
     * This callback is used to report capturing information.
     *
     * @param privateDataHandle Indicates the private data handle.
     * @param type Indicates the information type. For details, see {@link FormatInfoType}.
     * @param extra Indicates other information, for example, the start time position of the captured file.
     * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*OnInfo)(CALLBACK_HANDLE privateDataHandle, int32_t type, int32_t extra);
} FormatCallback;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // FORMAT_TYPE_H
/** @} */