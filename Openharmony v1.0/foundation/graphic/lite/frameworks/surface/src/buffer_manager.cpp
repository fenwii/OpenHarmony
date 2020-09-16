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

#include "buffer_manager.h"

#include "buffer_common.h"
#include "surface_buffer.h"

namespace OHOS {
BufferManager* BufferManager::GetInstance()
{
    static BufferManager BufferManager;
    return &BufferManager;
}

bool BufferManager::Init()
{
    if (grallocFucs_ != nullptr) {
        GRAPHIC_LOGI("BufferManager has init succeed.");
        return true;
    }
    if (GrallocInitialize(&grallocFucs_) != DISPLAY_SUCCESS) {
        return false;
    }
    return true;
}

bool BufferManager::UsageToMemType(MemType& type, uint32_t usage)
{
    switch (usage) {
        case BUFFER_CONSUMER_USAGE_SORTWARE:
            type = SHM_MEM;
            break;
        case BUFFER_CONSUMER_USAGE_HARDWARE:
        case BUFFER_CONSUMER_USAGE_HARDWARE_PRODUCER_CACHE:
            type = NORMAL_MEM;
            break;
        case BUFFER_CONSUMER_USAGE_HARDWARE_CONSUMER_CACHE:
            type = CACHE_MEM;
            break;
        default:
            GRAPHIC_LOGW("Usage to MemType failed.");
            return false;
    }
    return true;
}

void BufferManager::SurfaceBufferToGrallocBuffer(const SurfaceBufferImpl& buffer, GrallocBuffer &graphicBuffer)
{
    graphicBuffer.hdl.key = buffer.GetKey();
    graphicBuffer.hdl.shmid = buffer.GetShmid();
    graphicBuffer.hdl.phyAddr = buffer.GetPhyAddr();
    graphicBuffer.size = buffer.GetMaxSize();
    graphicBuffer.virAddr = buffer.GetVirAddr();
}

SurfaceBufferImpl* BufferManager::AllocBuffer(uint32_t size, uint32_t usage)
{
    RETURN_VAL_IF_FAIL((grallocFucs_ != nullptr), nullptr);
    MemType type;
    if (!UsageToMemType(type, usage)) {
        GRAPHIC_LOGW("Alloc graphic buffer failed --- invaild usage.");
        return nullptr;
    }
    GrallocBuffer grallocBuffer = {
        .hdl = {
            .key = 0,
            .shmid = 0,
            .phyAddr = 0,
        },
        .type = type,
        .size = size,
        .virAddr = NULL
    };
    if (grallocFucs_->AllocMem(&grallocBuffer) != DISPLAY_SUCCESS) {
        GRAPHIC_LOGW("Alloc graphic buffer failed");
        return nullptr;
    }
    SurfaceBufferImpl* buffer = new SurfaceBufferImpl();
    if (buffer != nullptr) {
        buffer->SetMaxSize(grallocBuffer.size);
        buffer->SetUsage(usage);
        buffer->SetVirAddr(grallocBuffer.virAddr);
        buffer->SetKey(grallocBuffer.hdl.key);
        buffer->SetShmid(grallocBuffer.hdl.shmid);
        buffer->SetPhyAddr(grallocBuffer.hdl.phyAddr);
        GRAPHIC_LOGI("Alloc buffer succeed to shared memory segment.");
    } else {
        GRAPHIC_LOGW("Alloc buffer failed to shared memory segment.");
    }
    return buffer;
}

void BufferManager::FreeBuffer(SurfaceBufferImpl* buffer)
{
    RETURN_IF_FAIL((grallocFucs_ != nullptr));
    if (buffer == nullptr) {
        GRAPHIC_LOGW("Input param buffer is null.");
        return;
    }
    MemType type;
    if (!UsageToMemType(type, buffer->GetUsage())) {
        GRAPHIC_LOGW("Free graphic buffer failed --- invaild usage.");
        return;
    }
    GrallocBuffer grallocBuffer;
    SurfaceBufferToGrallocBuffer(*buffer, grallocBuffer);
    grallocBuffer.type = type;
    grallocFucs_->FreeMem(&grallocBuffer);
    GRAPHIC_LOGI("Free buffer succeed.");
    delete buffer;
}

bool BufferManager::MapBuffer(SurfaceBufferImpl& buffer)
{
    RETURN_VAL_IF_FAIL((grallocFucs_ != nullptr), false);
    MemType type;
    if (!UsageToMemType(type, buffer.GetUsage())) {
        GRAPHIC_LOGW("Free graphic buffer failed --- invaild usage.");
        return false;
    }
    GrallocBuffer grallocBuffer;
    SurfaceBufferToGrallocBuffer(buffer, grallocBuffer);
    grallocBuffer.type = type;
    void* virAddr = NULL;
    if (buffer.GetUsage() == BUFFER_CONSUMER_USAGE_HARDWARE ||
        buffer.GetUsage() == BUFFER_CONSUMER_USAGE_HARDWARE_CONSUMER_CACHE ||
        buffer.GetUsage() == BUFFER_CONSUMER_USAGE_SORTWARE) {
        virAddr = grallocFucs_->Mmap(&grallocBuffer);
    } else if (buffer.GetUsage() == BUFFER_CONSUMER_USAGE_HARDWARE_PRODUCER_CACHE) {
        virAddr = grallocFucs_->MmapCache(&grallocBuffer);
    } else {
        GRAPHIC_LOGW("No Suport usage.");
        return false;
    }
    if (virAddr == NULL) {
        GRAPHIC_LOGW("Map Buffer error.");
        return false;
    }
    buffer.SetVirAddr(virAddr);
    return true;
}

void BufferManager::UnmapBuffer(SurfaceBufferImpl& buffer)
{
    RETURN_IF_FAIL((grallocFucs_ != nullptr));
    MemType type;
    if (!UsageToMemType(type, buffer.GetUsage())) {
        GRAPHIC_LOGW("Free graphic buffer failed --- invaild usage.");
        return;
    }
    GrallocBuffer grallocBuffer;
    SurfaceBufferToGrallocBuffer(buffer, grallocBuffer);
    grallocBuffer.type = type;
    if (grallocFucs_->Unmap(&grallocBuffer) != DISPLAY_SUCCESS) {
        GRAPHIC_LOGW("Umap buffer failed.");
    }
}

int32_t BufferManager::FlushCache(const SurfaceBufferImpl& buffer)
{
    RETURN_VAL_IF_FAIL((grallocFucs_ != nullptr), SURFACE_ERROR_NOT_READY);
    MemType type;
    if (!UsageToMemType(type, buffer.GetUsage())) {
        GRAPHIC_LOGW("Free graphic buffer failed --- invaild usage.");
        return SURFACE_ERROR_NOT_READY;
    }
    GrallocBuffer grallocBuffer;
    SurfaceBufferToGrallocBuffer(buffer, grallocBuffer);
    grallocBuffer.type = type;
    if (buffer.GetUsage() == BUFFER_CONSUMER_USAGE_HARDWARE_CONSUMER_CACHE) {
        if (grallocFucs_->FlushCache(&grallocBuffer) != DISPLAY_SUCCESS) {
            GRAPHIC_LOGW("Flush cache buffer failed.");
        }
    } else if (buffer.GetUsage() == BUFFER_CONSUMER_USAGE_HARDWARE_PRODUCER_CACHE) {
        if (grallocFucs_->FlushMCache(&grallocBuffer) != DISPLAY_SUCCESS) {
            GRAPHIC_LOGW("Flush M cache buffer failed.");
        }
    }
    return SURFACE_ERROR_OK;
}
} // namespace OHOS