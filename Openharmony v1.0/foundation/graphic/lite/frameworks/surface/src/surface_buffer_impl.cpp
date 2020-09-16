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

#include "surface_buffer_impl.h"

#include "securec.h"

namespace OHOS {
const uint16_t MAX_USER_DATA_COUNT = 1000;

SurfaceBufferImpl::SurfaceBufferImpl() : len_(0)
{
    struct SurfaceBufferData bufferData = {{0}, 0, 0, 0, BUFFER_STATE_NONE, NULL};
    bufferData_ = bufferData;
}

int32_t SurfaceBufferImpl::SetInt32(uint32_t key, int32_t value)
{
    return SetData(key, BUFFER_DATA_TYPE_INT_32, &value, sizeof(value));
}

int32_t SurfaceBufferImpl::GetInt32(uint32_t key, int32_t& value)
{
    uint8_t type = BUFFER_DATA_TYPE_NONE;
    void *data = NULL;
    uint8_t size;
    if (GetData(key, &type, &data, &size) != SURFACE_ERROR_OK || type != BUFFER_DATA_TYPE_INT_32) {
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    if (size != sizeof(value)) {
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    value = *(reinterpret_cast<int32_t *>(data));
    return SURFACE_ERROR_OK;
}

int32_t SurfaceBufferImpl::SetInt64(uint32_t key, int64_t value)
{
    return SetData(key, BUFFER_DATA_TYPE_INT_64, &value, sizeof(value));
}

int32_t SurfaceBufferImpl::GetInt64(uint32_t key, int64_t& value)
{
    uint8_t type = BUFFER_DATA_TYPE_NONE;
    void *data = NULL;
    uint8_t size;
    if (GetData(key, &type, &data, &size) != SURFACE_ERROR_OK || type != BUFFER_DATA_TYPE_INT_64) {
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    if (size != sizeof(value)) {
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    value = *(reinterpret_cast<int64_t *>(data));
    return SURFACE_ERROR_OK;
}

int32_t SurfaceBufferImpl::SetData(uint32_t key, uint8_t type, const void* data, uint8_t size)
{
    if (type <= BUFFER_DATA_TYPE_NONE ||
        type >= BUFFER_DATA_TYPE_MAX ||
        size <= 0 ||
        size > sizeof(int64_t)) {
        GRAPHIC_LOGI("Invaild Param");
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    if (extDatas_.size() > MAX_USER_DATA_COUNT) {
        GRAPHIC_LOGI("Has save more ext datas, could not save one more.");
        return SURFACE_ERROR_SYSTEM_ERROR;
    }
    ExtraData extData = {0};
    std::map<uint32_t, ExtraData>::iterator iter = extDatas_.find(key);
    if (iter != extDatas_.end()) {
        extData = iter->second;
        if (size != extData.size) {
            free(extData.value);
            extData.value = NULL;
        }
    }
    if (extData.value == NULL) {
        extData.value = malloc(size);
        if (extData.value == NULL) {
            GRAPHIC_LOGE("Couldn't allocate %zu bytes for ext data", size);
            return SURFACE_ERROR_SYSTEM_ERROR;
        }
    }
    if (memcpy_s(extData.value, size, data, size) != EOK) {
        free(extData.value);
        GRAPHIC_LOGW("Couldn't copy %zu bytes for ext data", size);
        return SURFACE_ERROR_SYSTEM_ERROR;
    }
    extData.size = size;
    extData.type = type;
    extDatas_[key] = extData;
    return SURFACE_ERROR_OK;
}

int32_t SurfaceBufferImpl::GetData(uint32_t key, uint8_t* type, void** data, uint8_t* size)
{
    std::map<uint32_t, ExtraData>::iterator iter = extDatas_.find(key);
    if (iter == extDatas_.end()) {
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    ExtraData extData = extDatas_[key];
    *data = extData.value;
    *size = extData.size;
    *type = extData.type;
    return SURFACE_ERROR_OK;
}

#ifndef _SURFACE_LINUX_
void SurfaceBufferImpl::ReadFromIpcIo(IpcIo& io)
{
    bufferData_.handle.key =  IpcIoPopUint32(&io);
    bufferData_.handle.phyAddr = IpcIoPopUint64(&io);
    bufferData_.size = IpcIoPopUint32(&io);
    bufferData_.usage = IpcIoPopUint32(&io);
    uint32_t extDataSize = IpcIoPopUint32(&io);
    if (extDataSize > 0 && extDataSize < MAX_USER_DATA_COUNT) {
        for (uint32_t i = 0; i < extDataSize; i++) {
            uint32_t key = IpcIoPopUint32(&io);
            uint32_t type = IpcIoPopUint32(&io);
            switch (type) {
                case BUFFER_DATA_TYPE_INT_32: {
                    int32_t value = IpcIoPopInt32(&io);
                    SetInt32(key, value);
                    break;
                }
                case BUFFER_DATA_TYPE_INT_64: {
                    int64_t value = IpcIoPopInt64(&io);
                    SetInt64(key, value);
                    break;
                }
                default:
                    break;
            }
        }
    }
}
void SurfaceBufferImpl::WriteToIpcIo(IpcIo& io)
{
    IpcIoPushUint32(&io, bufferData_.handle.key);
    IpcIoPushUint64(&io, bufferData_.handle.phyAddr);
    IpcIoPushUint32(&io, bufferData_.size);
    IpcIoPushUint32(&io, bufferData_.usage);
    IpcIoPushUint32(&io, extDatas_.size());
    if (!extDatas_.empty()) {
        std::map<uint32_t, ExtraData>::iterator iter;
        for (iter = extDatas_.begin(); iter != extDatas_.end(); iter++) {
            uint32_t key = iter->first;
            ExtraData value = iter->second;
            IpcIoPushUint32(&io, key);
            IpcIoPushUint32(&io, value.type);
            switch (value.type) {
                case BUFFER_DATA_TYPE_INT_32:
                    IpcIoPushInt32(&io, *(reinterpret_cast<int32_t *>(value.value)));
                    break;
                case BUFFER_DATA_TYPE_INT_64:
                    IpcIoPushInt64(&io, *(reinterpret_cast<int64_t *>(value.value)));
                    break;
                default:
                    break;
            }
        }
    }
}
#endif

void SurfaceBufferImpl::CopyExtraData(SurfaceBufferImpl& buffer)
{
    extDatas_ = buffer.extDatas_;
    buffer.extDatas_.clear();
}

void SurfaceBufferImpl::ClearExtraData()
{
    if (!extDatas_.empty()) {
        std::map<uint32_t, ExtraData>::iterator iter;
        for (iter = extDatas_.begin(); iter != extDatas_.end(); iter++) {
            ExtraData value = iter->second;
            free(value.value);
            value.value = NULL;
        }
        extDatas_.clear();
    }
}

SurfaceBufferImpl::~SurfaceBufferImpl()
{
    ClearExtraData();
    struct SurfaceBufferData bufferData = {{0}, 0, 0, 0, BUFFER_STATE_NONE, NULL};
    bufferData_ = bufferData;
}
}