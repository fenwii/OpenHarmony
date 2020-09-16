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
 * @file format_interface.h
 *
 * @brief Declares format-related APIs.
 *
 * For example, you use the functions provided in this file to define custom data types and to initialize,
 * create, destroy the muxer and demuxer, and set their parameters. Also, you can read demuxer data frames,
 * select demuxer tracks, add muxer tracks, and write data frames into a container.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef FORMAT_INTERFACE_H
#define FORMAT_INTERFACE_H

#include "format_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Initializes the format.
 *
 * You can call this function to initialize the demuxer and muxer.
 * This function should always be called before other format-specific functions,
 * and it can be called only once within a process.
 *
 * @since 1.0
 * @version 1.0
 */
void FormatInit(void);

/**
 * @brief Deinitializes the format.
 *
 * You can call this function to deinitialize the demuxer and muxer.
 * This function works in pair with {@link FormatInit}.
 *
 * @since 1.0
 * @version 1.0
 */
void FormatDeInit(void);

/**
 * @brief Creates a demuxer component and returns its context handle.
 *
 * This function returns the demuxer context handle without probing the container format or
 * obtaining stream information.
 *
 * @param source Indicates the pointer to the format source of the demuxer. For details, see {@link FormatSource}.
 * @param handle Indicates the double pointer to the demuxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t FormatDemuxerCreate(const FormatSource *source, void **handle);

/**
 * @brief Sets demuxer attributes.
 *
 * You can call this function to set the HTTP header, HTTP referer, and other extension items for the demuxer
 * after {@link FormatDemuxerCreate} is called.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param trackId Identifies the track. If the value is an invalid value (<b>-1</b>),
 * this parameter identifies the file or program.
 * @param metaData Indicates the pointer to an array of key-value pairs representing parameter names and values.
 * For details, see {@link ParameterItem}.
 * @param metaDataCnt Indicates the number of key-value pairs in the array.
 * This parameter works in pair with <b>metaData</b>.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerSetParameter(const void *handle, int32_t trackId,
    const ParameterItem *metaData, int32_t metaDataCnt);

/**
 * @brief Obtains demuxer attributes.
 *
 * You can call this function to obtain the HTTP header, HTTP referer, and other extension items for the demuxer
 * after {@link FormatDemuxerCreate} is called. The demuxer will store the value in the <b>metaData</b>
 * based on the key.If the demuxer has allocated memory for the <b>metaData</b> to store the value,
 * the caller should manually free the memory.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param trackId Identifies the track. If the value is an invalid value (<b>-1</b>),
 * this parameter identifies the file or program.
 * @param metaData Indicates the pointer to the buffer for storing the parameters values
 * that the demuxer has searched for based on the input key. For details, see {@link ParameterItem}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerGetParameter(const void *handle, int32_t trackId, ParameterItem *metaData);

/**
 * @brief Sets a callback for the demuxer.
 *
 * The callback will be invoked to notify the upper layer of internal events of the demuxer.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param callBack Indicates the pointer to the callback, as defined in {@link FormatCallback}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerSetCallBack(void *handle, const FormatCallback *callBack);

/**
 * @brief Sets buffer information for the demuxer.
 *
 * If there is a buffer mechanism in the demuxer, you can call this function to set the maximum buffer size and time.
 * Alternatively, you can disable the buffer mechanism by setting the buffer size and time to <b>0</b> in
 * the <b>setting</b> parameter. If there is no buffer mechanism or the default setting is retained,
 * you can skip this function.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param setting Indicates the pointer to the maximum demuxer buffer size and time,
 * as defined in {@link FormatBufferSetting}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t FormatDemuxerSetBufferConfig(void *handle, const FormatBufferSetting *setting);

/**
 * @brief Obtains the buffer information of the demuxer.
 *
 * If there is a buffer mechanism in the demuxer, you can call this function to obtain the maximum buffer size and time.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param setting Indicates the pointer to the maximum demuxer buffer size and time,
 * as defined in {@link FormatBufferSetting}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerGetBufferConfig(const void *handle, FormatBufferSetting *setting);

/**
 * @brief Makes preparations for the demuxer.
 *
 * This function triggers the demuxer to probe the media file container format and parse stream information.
 * You can obtain media file attributes only after this function is called.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerPrepare(void *handle);

/**
 * @brief Obtains the attributes of a media file.
 *
 * The attributes contain file, program, and stream attributes.
 * This function should be called after {@link FormatDemuxerPrepare} is called.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param info Indicates the pointer to the source attributes, as defined in {@link FileInfo}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerGetFileInfo(void *handle, FileInfo *info);

/**
 * @brief Selects a specified media track.
 *
 * The media tracks to select must belong to the same program.
 * If you do not call this function, the default media tracks of the default program are selected.
 * If <b>programId</b> is valid but <b>trackId</b> is invalid, the default media track of the specified program is used.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param programId Identifies the program.
 * @param trackId Identifies the media track. If a valid value is passed, the media track must belong to
 * the specified program. If an invalid value is passed, the default media track of the specified program is used.
 * If multiple audio tracks are specified, the player determines which audio track to use.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerSelectTrack(const void *handle, int32_t programId, int32_t trackId);

/**
 * @brief Unselects a specified media track from which the demuxer reads data frames.
 *
 * The demuxer can read all media tracks of the default program. You can call this function to
 * unselect all or certain tracks of a specified program that the demuxer is expected not to read.
 * If <b>trackId</b> is invalid, the demuxer will read none of the tracks of the specified program.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param programId Identifies the program.
 * @param trackId Identifies the media track that the demuxer will unselect.
 * This parameter works in pair with <b>programId</b>. If a valid value is passed, the media track must belong to
 * the program specified by <b>programId</b>. If an invalid value is passed, and all media tracks of the specified
 * program are unselected.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerUnselectTrack(const void *handle, int32_t programId, int32_t trackId);

/**
 * @brief Starts the demuxer.
 *
 * After being started, the caller can read data frames from the demuxer.
 * This function should be called after {@link FormatDemuxerPrepare} is called.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerStart(void *handle);

/**
 * @brief Obtains the ID of the media track selected by the demuxer for output.
 *
 * The demuxer automatically selects the default program and its media tracks.
 * However, if the program and media tracks have changed after {@link FormatDemuxerSelectTrack} and
 * {@link FormatDemuxerUnselectTrack} are called, you can obtain the currently selected program and media tracks
 * by calling this function (<b>FormatDemuxerGetSelectedTrack</b>.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param programId Identifies the pointer to the program.
 * @param trackId Identifies the array of selected media tracks. This parameter works in pair with <b>nums</b>.
 * @param nums Indicates the pointer to the total number of selected media tracks.
 * This parameter works in pair with <b>trackId</b>.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerGetSelectedTrack(const void *handle, int32_t *programId, int32_t trackId[], int32_t *nums);

/**
 * @brief Reads data frames.
 *
 * After the data frames are read,
 * you need to call {@link FormatDemuxerFreeFame} to free them.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param frame Indicates the pointer to the data structure {@link FormatFrame}.
 * @param timeOutMs Indicates the time required for waiting data frame read.
 * The value <b>0</b> indicates that data frames are immediately read without any wait.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerReadFrame(const void *handle, FormatFrame *frame, int32_t timeOutMs);

/**
 * @brief Frees data frames.
 *
 * You can call this function to free the data frames obtained by calling {@link FormatDemuxerReadFrame}.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param frame Indicates the pointer to the data structure {@link FormatFrame}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerFreeFrame(void *handle, FormatFrame *frame);

/**
 * @brief Seeks for a specified position for the demuxer.
 *
 * After being started, the demuxer seeks for a specified position to read data frames.
 * You can specify the position close to the time specified by <b>streamIndex</b>.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @param streamIndex Identifies the stream in the media file.
 * @param timeStampUs Indicates the target position, in microseconds.
 * @param mode Indicates the seek mode, as defined in {@link FormatSeekMode}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerSeek(const void *handle, int32_t streamIndex, int64_t timeStampUs, FormatSeekMode mode);

/**
 * @brief Stops the demuxer from working.
 *
 * After this function is called, the demuxer cannot resume decapsulation.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerStop(void *handle);

/**
 * @brief Destroys demuxer resources.
 *
 * This function works in pair with {@link FormatDemuxerCreate}.
 * If you do not call this function, resource leakage may occur.
 *
 * @param handle Indicates the pointer to the demuxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatDemuxerDestory(void *handle);

/**
 * @brief Creates a muxer and returns its context handle.
 *
 * @param handle Indicates the double pointer to the muxer context handle.
 * @param outputConfig Indicates the pointer to the muxer output configuration,
 * as defined in {@link FormatOutputConfig}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerCreate(void **handle, FormatOutputConfig *outputConfig);

/**
 * @brief Destroys a muxer and release its resources created by calling {@link FormatMuxerCreate}.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerDestory(const void *handle);

/**
 * @brief Adds a media track source for the muxer. For details about track sources, see {@link TrackSource}.
 *
 * This function must be called after {@link FormatMuxerCreate} is successfully called and
 * before {@link FormatMuxerStart} is called.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param trackSource Indicates the pointer to the track source.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerAddTrack(void *handle, const TrackSource *trackSource);

/**
 * @brief Sets a callback for the muxer. For details about the callback, see {@link FormatCallback}.
 *
 * This function should be called after {@link FormatMuxerCreate} is successfully called.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param FormatCallback Indicates the pointer to the muxer callback to set.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetCallBack(void *handle, const FormatCallback *callBack);

/**
 * @brief Sets the orientation of the video track for the muxer.
 *
 * This function should be called after {@link FormatMuxerAddTrack} is successfully called.
 * The following degrees are supported: 0, 90, 180, and 270.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param degrees Indicates the clockwise angle of the video track.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetOrientation(void *handle, int degrees);

/**
 * @brief Sets the geographical information for the output file of the muxer.
 *
 * This function should be called after {@link FormatMuxerCreate} is successfully called.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param latitude Indicates the latitude, within the range [-90,90].
 * @param longitude Indicates the longitude, within the range [-180,180].
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetLocation(const void *handle, int latitude, int longitude);

/**
 * @brief Sets the maximum size (in bytes) for the output file of the muxer.
 *
 * This function should be called after {@link FormatMuxerCreate} is successfully called.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param bytes Indicates the maximum size of a file, in bytes. If the value is <b>0</b> or negative,
 * the operation fails and the maximum size does not take effect. In this case, the maximum size of a single file
 * supported by the current file system is used as the value of this parameter.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetMaxFileSize(void *handle, int64_t bytes);

/**
 * @brief Sets the maximum duration (in seconds) for the output file.
 *
 * You need to call this function before calling {@link FormatMuxerStart}. If the maximum duration you set is valid
 * and capturing is approaching 90% of that duration or the remaining duration is 1s, the message
 * {@link MUXER_INFO_MAX_DURATION_APPROACHING} is reported via {@link OnInfo} of {@link FormatCallback}. If the output
 * file has been set by calling {@link FormatMuxerCreate}, you need to call {@link FormatMuxerSetNextOutputFile}
 * to set the next output file. Otherwise, the current output file will be overwritten when the capturing reaches
 * the maximum duration you set.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param duration Indicates the maximum duration to set, in seconds. If the value is <b>0</b> or negative,
 * the operation fails. In this case, the default duration (60 seconds) will be used.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetMaxFileDuration(void *handle, int64_t durationUs);

/**
 * @brief Manually splits a file.
 *
 * This function can be called after {@link FormatMuxerStart} is called. Once this function is called,
 * the file is split based on the manual split type. After manual split is complete, file split will proceed to
 * use the initially set split type. You can call this function again only after
 * the {@link MUXER_INFO_FILE_SPLIT_FINISHED} event is reported.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param type Indicates the file split type, as defined in {@link FileSplitType}.
 * @param timestamp Indicates the file split timestamp. This parameter is not supported currently.
 * The value <b>¨C1</b> indicates that the file is split at the time this function is called.
 * @param duration Indicates the period from the file split time to the time the next output file starts.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetFileSplitDuration(const void *handle, ManualSplitType type,
                                        int64_t timestampUs, uint32_t durationUs);

/**
 * @brief Starts the muxer.
 *
 * You can call this function to encapsulate media data after the muxer is created, media tracks are added,
 * and related parameters are set.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerStart(void *handle);

/**
 * @brief Writes data frames into the muxer.
 *
 * This function should be called after {@link FormatMuxerCreate} is successfully called.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param frameData Indicates the pointer to the data structure {@link FormatFrame}.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerWriteFrame(const void *handle, const FormatFrame *frameData);

/**
 * @brief Sets the descriptor for the next output file.
 *
 * If {@link FormatMuxerCreate} is successfully called and the file descriptor involved is valid, you can call
 * this function (<b>FormatMuxerSetNextOutputFile</b>) upon receiving the message
 * {@link MUXER_INFO_MAX_FILESIZE_APPROACHING} or {@link MUXER_INFO_MAX_DURATION_APPROACHING}.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param fd Indicates the file descriptor to set.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetNextOutputFile(const void *handle, int32_t fd);

/**
 * @brief Stops the muxer that was started by calling {@link FormatMuxerStart}.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param block Indicates how to stop the muxer. The value <b>true</b> indicates that the muxer is stopped
 * after all buffered data is processed, and <b>false</b> indicates that the buffered data is discarded and
 * the muxer is immediately stopped.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerStop(const void *handle, bool block);

/**
 * @brief Sets muxer attributes.
 *
 * This is an extended function that can be used to add MP4-dedicated boxes and tags (such as <b>exif</b>).
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param trackId Identifies the media track. If the value is {@link FORMAT_INVALID_TRACK_ID},
 * this function sets the muxer attributes.
 * @param item Indicates the pointer to the items carrying muxer attributes. You can specify multiple items at a time
 * in this parameter, which works in pair with <b>itemNum</b>.
 * @param itemNum Indicates the number of attributes set at a time.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerSetParameter(void *handle, int32_t trackId, const ParameterItem *item, int32_t itemNum);

/**
 * @brief Obtains muxer attributes.
 *
 * This is an extended function that can be used to obtain muxer or track attributes.
 * The demuxer then obtains the muxer attributes based on the key contained in <b>item</b>.
 *
 * @param handle Indicates the pointer to the muxer context handle.
 * @param trackId Identifies the media track. If the value is {@link FORMAT_INVALID_TRACK_ID},
 * this function obtains the muxer attributes.
 * @param item Indicates the pointer to the items carrying muxer attributes. You can specify multiple items at a time
 * in this parameter, which works in pair with <b>itemNum</b>.
 * @param itemNum Indicates the number of attributes set at a time.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value if any requested attribute
 * fails to be obtained or is not found.
 * @since 1.0
 * @version 1.0
 */
int32_t FormatMuxerGetParameter(void *handle, int32_t trackId, ParameterItem *item, int32_t itemNum);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // FORMAT_INTERFACE_H
/** @} */