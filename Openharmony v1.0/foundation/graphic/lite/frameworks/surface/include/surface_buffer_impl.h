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

#ifndef GRAPHIC_LITE_SURFACE_BUFFER_IMPL_H
#define GRAPHIC_LITE_SURFACE_BUFFER_IMPL_H

#include <map>
#include "buffer_common.h"
#ifndef _SURFACE_LINUX_
#include "liteipc_adapter.h"
#include "serializer.h"
#endif
#include "surface_buffer.h"

namespace OHOS {
enum BufferState {
    BUFFER_STATE_NONE = 0,
    BUFFER_STATE_REQUEST,
    BUFFER_STATE_FLUSH,
    BUFFER_STATE_ACQUIRE,
    BUFFER_STATE_RELEASE
};

enum BufferDataType {
    BUFFER_DATA_TYPE_NONE,
    BUFFER_DATA_TYPE_INT_32,
    BUFFER_DATA_TYPE_INT_64,
    BUFFER_DATA_TYPE_MAX,
};

struct SurfaceBufferHandle {
    int32_t key;
    int32_t shmid;
    uint64_t phyAddr;
    bool operator == (const SurfaceBufferHandle &rHandle) const
    {
        return ((key == rHandle.key)
            && (shmid == rHandle.shmid)
            && (phyAddr == rHandle.phyAddr));
    }
};

struct SurfaceBufferData {
    SurfaceBufferHandle handle;
    uint32_t size;
    uint32_t usage;
    uint8_t deletePending;
    BufferState state;
    void* virAddr;
    bool operator == (const SurfaceBufferData &rData) const
    {
        return handle == rData.handle;
    }
};

typedef struct {
    void* value;
    uint8_t size;
    uint8_t type;
} ExtraData;

/**
 * @brief Buffer class. Provide shared memory for graphic and multi media to use.
 */
class SurfaceBufferImpl : public SurfaceBuffer {
public:
    /**
     * @brief Buffer Constructor.
     */
    SurfaceBufferImpl();

    /**
     * @brief Buffer Destructor.
     */
    ~SurfaceBufferImpl();

    /**
     * @brief Get buffer key, for shared virtual memory.
     * @returns The buffer key.
     */
    int32_t GetKey() const
    {
        return bufferData_.handle.key;
    }

    /**
     * @brief Set buffer key, for shared virtual memory.
     * @param [in] The buffer key
     */
    void SetKey(int32_t key)
    {
        bufferData_.handle.key = key;
    }

    /**
     * @brief Get buffer shmid, for shared virtual memory.
     * @returns The buffer shmid.
     */
    int32_t GetShmid() const
    {
        return bufferData_.handle.shmid;
    }

    /**
     * @brief Set buffer key, for shared virtual memory.
     * @param [in] The buffer shmid
     */
    void SetShmid(int32_t shmid)
    {
        bufferData_.handle.shmid = shmid;
    }

    /**
     * @brief Get buffer phyAddr, for shared physical memory.
     * @returns The buffer shmid.
     */
    uint64_t GetPhyAddr() const override
    {
        return bufferData_.handle.phyAddr;
    }

    /**
     * @brief Set buffer phyAddr, for shared physical memory.
     * @param [in] The buffer shmid
     */
    void SetPhyAddr(uint64_t phyAddr)
    {
        bufferData_.handle.phyAddr = phyAddr;
    }

    /**
     * @brief Set buffer virtual addr.
     * @param [in] The virtual addr.
     */
    void SetVirAddr(void* virAddr)
    {
        bufferData_.virAddr = virAddr;
    }

    /**
     * @brief Get buffer virtual addr.
     * @returns The buffer virtual addr.
     */
    void* GetVirAddr() const override
    {
        return bufferData_.virAddr;
    }

    /**
     * @brief Get buffer size.
     * @returns The buffer size.
     */
    uint32_t GetMaxSize() const
    {
        return bufferData_.size;
    }

    /**
     * @brief Set buffer size.
     * @param [in] The buffer size
     */
    void SetMaxSize(uint32_t size)
    {
        bufferData_.size = size;
    }

    /**
     * @brief Get buffer size.
     * @returns The buffer size.
     */
    uint32_t GetSize() const override
    {
        if (len_ == 0) {
            return bufferData_.size;
        }
        return len_;
    }

    /**
     * @brief Set buffer size.
     * @param [in] The buffer size
     */
    void SetSize(uint32_t size) override
    {
        if (size > bufferData_.size) {
            GRAPHIC_LOGI("Input param is invaild");
            return;
        }
        len_ = size;
    }

    /**
     * @brief Get buffer usage. Surface alloc physical or virtual memory buffer.
     *        All usage sees detail in OHOS::BUFFER_CONSUMER_USAGE.
     * @returns The buffer usage.
     */
    uint32_t GetUsage() const
    {
        return bufferData_.usage;
    }

    /**
     * @brief Set buffer usage. Surface alloc physical or virtual memory buffer.
     *        Support usage see detail in OHOS::BUFFER_CONSUMER_USAGE.
     *        Default is BUFFER_CONSUMER_USAGE_SORTWARE, which will alloc virtual memory buffer.
     * @param [in] The buffer usage.
     */
    void SetUsage(uint32_t usage)
    {
        bufferData_.usage = usage;
    }

    /**
     * @brief Get buffer delete state. If deletePending == 1, buffer will be freed when state == BUFFER_STATE_FREE.
     * @returns [in] The buffer delete state
     */
    uint8_t GetDeletePending() const
    {
        return bufferData_.deletePending;
    }

    /**
     * @brief Set buffer delete state. If deletePending == 1, buffer will be freed when state == BUFFER_STATE_FREE.
     * @param [in] The buffer delete state
     */
    void SetDeletePending(uint8_t deletePending)
    {
        bufferData_.deletePending = deletePending;
    }

    /**
     * @brief Get buffer state. Buffer state detail : BUFFER_STATE.
     * @returns [in] The buffer state
     */
    BufferState GetState() const
    {
        return bufferData_.state;
    }

    /**
     * @brief Set buffer state. Buffer state detail : BUFFER_STATE.
     * @param [in] The buffer state
     */

    void SetState(BufferState newState)
    {
        bufferData_.state = newState;
    }
    /**
     * @brief Set int32 extra data for buffer, like <key,value>.
     * @param [in] key, unique uint32_t. If exited, will overlap.
     * @param [in] value, value which storage the value;
     * @returns if succeed, return 0; else return -1.
     */
    int32_t SetInt32(uint32_t key, int32_t value) override;

    /**
     * @brief Get int32 extra data for buffer, like <key,value>.
     * @param [in] key, unique uint32_t..
     * @param [out] value, value which storage the value;
     * @returns if succeed, return 0; else return -1;
     */
    int32_t GetInt32(uint32_t key, int32_t& value) override;

    /**
     * @brief Set int64 extra data for buffer, like <key,value>.
     * @param [in] key, unique uint32_t. If exited, will overlap.
     * @param [in] value, value which storage the value;
     * @returns if succeed, return 0; else return -1.
     */
    int32_t SetInt64(uint32_t key, int64_t value) override;

    /**
     * @brief Get int64 extra data for buffer, like <key,value>.
     * @param [in] key, unique uint32_t..
     * @param [out] value, value which storage the value;
     * @returns if succeed, return 0; else return -1;
     */
    int32_t GetInt64(uint32_t key, int64_t& value) override;

    /**
     * @brief Verify the two surface buffer same or not.
     * @param [in] The other SurfaceBufferImpl object
     * @returns Is same or not.
     */
    bool equals(const SurfaceBufferImpl& buffer) const
    {
        return bufferData_ == buffer.bufferData_;
    }
#ifndef _SURFACE_LINUX_
    /**
     * @brief Get buffer attr from ipc object.
     * @param [in] IpcIo pointer.
     */
    void ReadFromIpcIo(IpcIo& io);

    /**
     * @brief Write buffer attr to ipc object.
     * @param [in] IpcIo object.
     */
    void WriteToIpcIo(IpcIo& io);
#endif
    /**
     * @brief Copy buffer extra data from input buffer to self
     * @param [in] buffer pointer.
     */
    void CopyExtraData(SurfaceBufferImpl& buffer);

    /**
     * @brief Clear buffer extra data.
     */
    void ClearExtraData();
private:
    /**
     * Set extra data for buffer, like <key,value>.
     * @key, unique uint32_t. If exited, will overlap;
     * @type, value type. Current suport see detail enum OHOS::BUFFER_DATA_TYPE
     * @data, value pointer, which storage the value;
     * @size, value lenth.
     */
    int32_t SetData(uint32_t key, uint8_t type, const void* data, uint8_t size);
    int32_t GetData(uint32_t key, uint8_t* type, void** data, uint8_t* size);
    struct SurfaceBufferData bufferData_;
    std::map<uint32_t, ExtraData> extDatas_;
    uint32_t len_;
};
} // end namespace
#endif
