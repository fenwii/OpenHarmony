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
 * @file source.h
 *
 * @brief Declares the <b>Source</b> class, which is used to implement source-related operations.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef SOURCE_H
#define SOURCE_H
#include <memory>
#include <map>
#include <string>
#include "format.h"

using std::shared_ptr;

namespace OHOS {
namespace Media {
/**
 * @brief Enumerates media source types.
 *
 * @since 1.0
 * @version 1.0
 */
enum class SourceType : int32_t {
    /** Local file path or network address */
    SOURCE_TYPE_URI = 0,
    /** Local file descriptor */
    SOURCE_TYPE_FD,
    /** Stream data, such as Advanced Audio Coding (AAC) stream data */
    SOURCE_TYPE_STREAM,
};

/**
 * @brief Provides functions to obtain the address of a buffer memory and write the filled buffers into the playback
 * queue. You need to implement the <b>StreamCallback</b> functions in a player object.
 *
 * @since 1.0
 * @version 1.0
 */
struct StreamCallback {
    /**
     * @brief Enumerates buffer types of stream sources.
     *
     * @since 1.0
     * @version 1.0
     */
    enum BufferFlags : uint32_t {
        /** Synchronous frame */
        STREAM_FLAG_SYNCFRAME = 1,
        /** Codec configuration information */
        STREAM_FLAG_CODECCONFIG = 2,
        /** End of Stream (EOS) */
        STREAM_FLAG_EOS = 4,
        /** Part of a frame */
        STREAM_FLAG_PARTIAL_FRAME = 8,
        /** End of a frame. It is used in pair with <b>STREAM_FLAG_PARTIAL_FRAME</b>. */
        STREAM_FLAG_ENDOFFRAME = 16,
        /** Container file data, such as MP4 file data (not supported yet) */
        STREAM_FLAG_MUXER_DATA = 32,
    };

    /**
     * @brief Obtains the virtual address of a buffer memory block based on its index.
     *
     * @param index Indicates the index of the buffer memory block.
     * @return Returns the pointer to the virtual address of the buffer memory block.
     * @since 1.0
     * @version 1.0
     */
    virtual uint8_t *GetBuffer(size_t index) = 0;

    /**
     * @brief Writes the filled buffer memory block into the player memory.
     *
     * @param index Indicates the index of the buffer memory block.
     * @param offset Indicates the start offset into which the buffer memory block will be written.
     * @param size Indicates the size of the data filled in the buffer memory block.
     * @param timestampUs Indicates the timestamp of the frame filled in the buffer memory block. As data in AAC
     * streams can be filled not on a frame basis, set this parameter to <b>0</b> for AAC streams.
     * @param flags Indicates the type of the current buffer memory block. For details, see {@link BufferFlags}.
     * @since 1.0
     * @version 1.0
     */
    virtual void QueueBuffer(size_t index, size_t offset, size_t size, int64_t timestampUs, uint32_t flags) = 0;

    /**
    * @brief Sets additional information about a stream.
    *
    * @param params Indicates the parameters for additional stream information. For details, see {@link Format}.
    * @since 1.0
    * @version 1.0
    */
    virtual void SetParameters(const Format &params) = 0;
};

/**
 * @brief Provides functions related to the stream source for upper-layer applications.
 *
 * After the {@link SetSource} function is called, the player invokes {@link OnBufferAvailable} to notify your
 * application of the buffer memory block that can be filled with data.\n
 * The player can invoke {@link SetStreamCallback} to register a callback for your application. For example,
 * the {@link GetBuffer} callback obtains the address of the buffer block and sends the filled buffer memory block to
 * the player. The buffer memory block is allocated and processed on the player.\n
 * <b>StreamSource</b>is available only for the media source of the <b>SOURCE_TYPE_STREAM</b> type.
 * For details, see {@link SourceType}.\n
 *
 * @since 1.0
 * @version 1.0
 */
struct StreamSource {
    /**
     * @brief Notifies your application of the information about the buffer memory block that can be filled with data.
     *
     * @param index Indicates the index of the buffer memory block.
     * @param offset Indicates the start offset into which the data will be written.
     * @param size Indicates the size of data that the buffer memory block can store.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnBufferAvailable(size_t index, size_t offset, size_t size) = 0;

    /**
     * @brief Sets a callback function for your application.
     *
     * @param callback Indicates the {@link StreamCallback} function to set.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetStreamCallback(const std::shared_ptr<StreamCallback> &callback) = 0;
};

/**
 * @brief Provides functions to implement source-related operations.
 *
 * @since 1.0
 * @version 1.0
 */
class Source {
public:
    /**
     * @brief A constructor used to create a {@link Source} instance based on a specified URI.
     *
     * @param uri Indicates the media source URI, which can be a network URI or local file path.
     * @since 1.0
     * @version 1.0
     */
    explicit Source(const std::string& uri);

    /**
     * @brief A constructor used to create a {@link Source} instance based on a specified URI and header.
     *
     * If the HTTP URL header does not carry valid information for network playback, this function is equivalent to
     * {@link Source(const std::string& uri)}.
     *
     * @param uri Indicates the media source URI.
     * @param header Indicates the header.
     * @since 1.0
     * @version 1.0
     */
    Source(const std::string &uri, const std::map<std::string, std::string> &header);

    /**
     * @brief A constructor used to create a {@link Source} instance based on the stream source and format information.
     *
     *
     *
     * @param stream Indicates the media source stream. For details, see {@link StreamSource}.
     * @param formats Indicates stream data information, which is subject to the stream type. For example, the key
     * is {@link CODEC_MIME}, and the value is {@link MIME_AUDIO_AAC}. For details, see {@link Format}. This parameter
     * can be null if no information needs to be passed.
     * @since 1.0
     * @version 1.0
     */
    Source(const std::shared_ptr<StreamSource> &stream, const Format &formats);

    ~Source() = default;

    /**
     * @brief Obtains the source type.
     *
     * @return Returns the source type. For details, see {@link SourceType}.
     * @since 1.0
     * @version 1.0
     */
    SourceType GetSourceType() const;

    /**
     * @brief Obtains the media source URI.
     *
     * This function is called only when the {@link SourceType} is {@link SOURCE_TYPE_URI}.
     *
     * @return Returns the media source URI.
     * @since 1.0
     * @version 1.0
     */
    const std::string &GetSourceUri() const;

    /**
     * @brief Obtains the HTTP header for the media source.
     *
     * This function is called only when the {@link SourceType} is {@link SOURCE_TYPE_URI}.
     *
     * @return Returns the media source header.
     * @since 1.0
     * @version 1.0
     */
    const std::map<std::string, std::string> &GetSourceHeader() const;

    /**
     * @brief Obtains information about the media source stream.
     *
     * This function is called only when the {@link SourceType} is {@link SOURCE_TYPE_STREAM}.
     *
     * @return Returns information about the media source stream. For details, see {@link StreamSource}.
     * @since 1.0
     * @version 1.0
     */
    const std::shared_ptr<StreamSource> &GetSourceStream() const;

    /**
     * @brief Obtains the media source stream format.
     *
     * @return Returns the media source stream format. For details, see {@link Format}.
     * @since 1.0
     * @version 1.0
     */
    const Format &GetSourceStreamFormat() const;

private:
    std::string uri_;
    SourceType sourceType_;
    std::map<std::string, std::string> header_;
    std::shared_ptr<StreamSource> stream_;
    Format format_;
};
}  // namespace Media
}  // namespace OHOS
#endif  // SOURCE_H
