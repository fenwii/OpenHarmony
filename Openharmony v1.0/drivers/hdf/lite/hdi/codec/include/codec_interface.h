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
 * @file codec_interface.h
 *
 * @brief Declares codec-related APIs, including functions for initializing audio and video codecs,
 * setting parameters, and controlling and transferring data.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef CODEC_INTERFACE_H
#define CODEC_INTERFACE_H

#include "codec_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Initializes the internal audio and video submodules of the codec.
 *
 * This function needs to be called only once in a process.
 *
 * @return Returns <b>0</b> if the initialization is successful; returns a non-zero value otherwise.
 * @see CodecDeinit
 */
int32_t CodecInit();

/**
 * @brief Deinitializes the internal audio and video submodules of the codec.
 *
 * This function needs to be called only once in a process.
 *
 * @return Returns <b>0</b> if the deinitialization is successful; returns a non-zero value otherwise.
 * @see CodecInit
 */
int32_t CodecDeinit();

/**
 * @brief Obtains the capabilities of a specified media type based on an index.
 *
 * You can call this function repeatedly to obtain the codec capabilities until <b>CODEC_END</b> is returned.
 * The corresponding capabilities are described in the {@link Capability} structure,
 * including the maximum and minimum resolutions, maximum and minimum bit rates, and supported profiles and levels.
 * After obtaining the capabilities, determine whether they can meet your requirements, for example,
 * whether specific media files can be played and whether audio and video frames can be compressed.
 *
 * @param index Indicates the index of the capabilities.
 * @param cap Indicates the pointer to the capabilities.
 * @return Returns <b>CODEC_SUCCESS</b> if the capabilities corresponding to the index are available;
 * returns <b>CODEC_END</b> otherwise.
 */
int32_t CodecEnumerateCapbility(uint32_t index, CodecCapbility *cap);

/**
 * @brief Obtains the capabilities of a specified media type.
 *
 * You can call this function to obtain the codec capabilities.
 * The corresponding capabilities are described in the {@link Capability} structure,
 * including the maximum and minimum resolutions, maximum and minimum bit rates, and supported profiles and levels.
 * After obtaining the capabilities, determine whether they can meet your requirements, for example,
 * whether specific media files can be played and whether audio and video frames can be compressed.
 *
 * @param mime Indicates the media type. For details, see {@link AvCodecMime}.
 * @param type Indicates the audio and video codec types. For details, see {@link CodecType}.
 * @param flags Indicates the audio and video codec flags. <b>0</b> indicates hardware codec,
 * and <b>1</b> indicates software codec.
 * @param cap Indicates the pointer to the capabilities.
 * @return Returns <b>0</b> if the codec is supported and capabilities are available;
 * returns a non-zero value if the codec is not supported or the capabilities are unavailable.
 */
int32_t CodecGetCapbility(AvCodecMime mime, CodecType type, uint32_t flags, CodecCapbility *cap);

/**
 * @brief Creates a specific codec component and returns the component context through a handle.
 *
 * You can adjust the parameters required for creating a component based on service requirements.
 *
 * @param name Indicates the pointer to the unique name of the component, for example,
 * <b>codec.avc.hardware.decoder</b>.
 * @param attr Indicates the pointer to the parameters in the array required for creating the component.
 * @param len Indicates the number of elements in the parameter array.
 * @param handle Indicates the pointer to the codec handle returned.
 * @return Returns <b>0</b> if the codec component is created and the handle is available;
 * returns a non-zero value otherwise.
 */
int32_t CodecCreate(const char* name, const Param *attr, int len, CODEC_HANDLETYPE *handle);

/**
 * @brief Destroys a codec component.
 *
 * @param handle Indicates the handle of the codec component.
 * @return Returns <b>0</b> if the codec component is destroyed; returns a non-zero value otherwise.
 * @see CodecCreate
 */
int32_t CodecDestroy(CODEC_HANDLETYPE handle);

/**
 * @brief Sets the input or output buffer mode.
 *
 * You can learn about the support of the codec input/output buffer for internal and external buffer modes
 * by calling {@link CodecGetCapbility}. In this way, you can determine whether to use an internal or
 * external buffer mode. If the current codec can use only the specific buffer mode, you do not need to set it.
 *
 * @param handle Indicates the handle of the codec component.
 * @param type Specifies whether the buffer type is an input type or an output type.
 * @param mode Specifies whether to use an internal or external buffer mode.
 * @return Returns <b>0</b> if the setting is successful; returns a non-zero value otherwise.
 */
int32_t CodecSetPortMode(CODEC_HANDLETYPE handle, DirectionType type, BufferMode mode);

/**
 * @brief Sets parameters required by a codec component.
 *
 * You should call this function to set parameters after {@link CodecCreate} is called
 * but before {@link CodecStart} is called.
 *
 * @param handle Indicates the handle of the codec component.
 * @param params Indicates the pointer to the parameters to set in the array.
 * @param paramCnt Indicates the number of elements in the parameter array.
 * @return Returns <b>0</b> if the setting is successful; returns a non-zero value otherwise.
 * @see CodecGetParameter
 */
int32_t CodecSetParameter(CODEC_HANDLETYPE handle, const Param *params, int paramCnt);

/**
 * @brief Obtains parameters from a codec component.
 *
 * This function must be called after {@link CodecCreate}.
 *
 * @param handle Indicates the handle of the codec component.
 * @param params Indicates the pointer to the parameters in the array used when the component is created.
 * @param paramCnt Indicates the number of elements in the parameter array.
 * @return Returns <b>0</b> if all parameters to obtain are supported; returns a non-zero value otherwise.
 * @see CodecSetParameter
 */
int32_t CodecGetParameter(CODEC_HANDLETYPE handle, Param *params, int paramCnt);

/**
 * @brief Starts a codec component.
 *
 * You can restart a component after it is stopped.
 *
 * @param handle Indicates the handle of the codec component.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecStart(CODEC_HANDLETYPE handle);

/**
 * @brief Stops a codec component.
 *
 * @param handle Indicates the handle of the codec component.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecStop(CODEC_HANDLETYPE handle);

/**
 * @brief Clears the cache when the codec component is the running state.
 *
 * Generally, this function is called when the seek operation is performed during playback.
 *
 * @param handle Indicates the handle of the codec component.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecFlush(CODEC_HANDLETYPE handle, DirectionType directType);

/**
 * @brief Queues input data.
 *
 * This function works with {@link CodecDequeInput} to implement input data transmission.
 *
 * @param handle Indicates the handle of the codec component.
 * @param inputData Indicates the pointer to the input data.
 * @param timeoutMs Indicates the timeout duration.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecQueueInput(CODEC_HANDLETYPE handle, const InputInfo *inputData, uint32_t timeoutMs);

/**
 * @brief Dequeues input data that has been used.
 *
 * This function works with {@link CodecQueueInput} to implement input data transmission.
 *
 * @param handle Indicates the handle of the codec component.
 * @param timeoutMs Indicates the timeout duration. Generally, the value is less than or equal to <b>3</b> seconds.
 * @param inputData Indicates the pointer to the input data that is used.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecDequeInput(CODEC_HANDLETYPE handle, uint32_t timeoutMs, InputInfo *inputData);

/**
 * @brief Queues output data.
 *
 * This function works with {@link CodecDequeueOutput} to implement output data transmission.
 *
 * @param handle Indicates the handle of the codec component.
 * @param outInfo Indicates the pointer to the output data.
 * @param timeoutMs Indicates the timeout duration.
 * @param releaseFenceFd Indicates that the descriptor comes from a buffer consumer.
 * The output data can be used only after waiting for <b>releaseFenceFd</b> is successful.
 * The value <b>-1</b> indicates that <b>releaseFenceFd</b> is invalid.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecQueueOutput(CODEC_HANDLETYPE handle, OutputInfo *outInfo, uint32_t timeoutMs, int releaseFenceFd);

/**
 * @brief Dequeues output data.
 *
 * This function works with {@link CodecQueueOutput} to implement output data transmission.
 *
 * @param handle Indicates the handle of the codec component.
 * @param timeoutMs Indicates the timeout duration.
 * @param acquireFd Indicates that this parameter is derived from the codec mode.
 * The output data can be used only after waiting for <b>acquireFd</b> is successful.
 * The value <b>-1</b> indicates that <b>acquireFd</b> is invalid.
 * @param outInfo Indicates the pointer to the output data.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecDequeueOutput(CODEC_HANDLETYPE handle, uint32_t timeoutMs, int *acquireFd, OutputInfo *outInfo);

/**
 * @brief Sets the callback function.
 *
 * The codec uses the callback function to notify the upper layer of events and asynchronously
 * report available input/output information.
 *
 * @param handle Indicates the handle of the codec component.
 * @param cb Indicates the pointer to the callback function. For details, see {@link CodecCallback}.
 * @param instance Indicates the upper-layer instance to be notified.
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 */
int32_t CodecSetCallback(CODEC_HANDLETYPE handle, const CodecCallback *cb, UINTPTR instance);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* CODEC_INTERFACE_H */
/** @} */