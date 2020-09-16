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

#include "font/ui_font_allocator.h"

namespace OHOS {
UIFontAllocator::UIFontAllocator() : ram_(nullptr), ramSize_(0), freeSize_(0),
    minSize_(0), end_(nullptr), free_(nullptr) {}

UIFontAllocator::~UIFontAllocator() {}

void UIFontAllocator::SetRamAddr(uint8_t* ram, uint32_t size)
{
    struct Chunk* chunk = nullptr;

    ram_ = ram;
    ramSize_ = size - sizeof(struct Chunk) * 2; // head and tail two chunk
    chunk = reinterpret_cast<struct Chunk*>(ram_);
    chunk->next = size - sizeof(struct Chunk);
    chunk->prev = 0;
    chunk->used = false;

    end_ = reinterpret_cast<struct Chunk*>(ram_ + size - sizeof(struct Chunk));
    end_->next = size - sizeof(struct Chunk);
    end_->prev = size - sizeof(struct Chunk);
    end_->used = true;

    free_ = chunk;
    freeSize_ = size - sizeof(struct Chunk);
}

void UIFontAllocator::SetMinChunkSize(uint32_t size)
{
    minSize_ = AlignSize(size);
}

void* UIFontAllocator::Allocate(uint32_t size)
{
    uint32_t free, left;
    uint32_t ptr, ptr2;
    struct Chunk* chunk = nullptr;
    struct Chunk* chunk2 = nullptr;
    struct Chunk* chunk3 = nullptr;

    size = AlignSize(size);
    if (size < minSize_) {
        size = minSize_;
    }

    for (ptr = reinterpret_cast<uint8_t*>(free_) - ram_; ptr < ramSize_;
         ptr = reinterpret_cast<struct Chunk*>(ram_ + ptr)->next) {
        chunk = reinterpret_cast<struct Chunk*>(ram_ + ptr);
        if (chunk->used) {
            continue;
        }
        free = chunk->next - ptr;
        if (free < sizeof(struct Chunk) + size) {
            continue;
        }
        left = free - sizeof(struct Chunk) - size;
        if (left >= sizeof(struct Chunk) + minSize_) {
            ptr2 = ptr + sizeof(struct Chunk) + size;
            chunk2 = reinterpret_cast<struct Chunk*>(ram_ + ptr2);
            chunk2->used = false;
            chunk2->next = chunk->next;
            chunk2->prev = ptr;
            chunk->next = ptr2;
            chunk->used = true;
            if (chunk2->next != end_->next) {
                chunk3 = reinterpret_cast<struct Chunk*>(ram_ + chunk2->next);
                chunk3->prev = ptr2;
            }
            freeSize_ -= size + sizeof(struct Chunk);
        } else {
            chunk->used = true;
            freeSize_ -= chunk->next - ptr;
        }

        if (chunk == free_) {
            struct Chunk* cur = free_;
            while (cur->used && cur != end_) {
                cur = reinterpret_cast<struct Chunk*>(ram_ + cur->next);
            }
            free_ = cur;
        }

        return reinterpret_cast<uint8_t*>(chunk) + sizeof(struct Chunk);
    }

    return nullptr;
}

void UIFontAllocator::CombineFree(struct Chunk* chunk)
{
    if (chunk == nullptr) {
        return;
    }
    struct Chunk* nextChunk = nullptr;
    struct Chunk* prevChunk = nullptr;

    nextChunk = reinterpret_cast<struct Chunk*>(ram_ + chunk->next);
    if ((nextChunk != chunk && !(nextChunk->used)) && (nextChunk != end_)) {
        if (free_ == nextChunk) {
            free_ = chunk;
        }
        chunk->next = nextChunk->next;
        reinterpret_cast<struct Chunk*>(ram_ + nextChunk->next)->prev = reinterpret_cast<uint8_t*>(chunk) - ram_;
    }

    prevChunk = reinterpret_cast<struct Chunk*>(ram_ + chunk->prev);
    if (prevChunk != chunk && !(prevChunk->used)) {
        if (free_ == chunk) {
            free_ = prevChunk;
        }
        prevChunk->next = chunk->next;
        reinterpret_cast<struct Chunk*>(ram_ + chunk->next)->prev = reinterpret_cast<uint8_t*>(prevChunk) - ram_;
    }
}

void UIFontAllocator::Free(void* addr)
{
    struct Chunk* chunk = nullptr;

    if (addr == nullptr) {
        return;
    }

    if (reinterpret_cast<uint8_t*>(addr) < ram_ ||
        reinterpret_cast<uint8_t*>(addr) > reinterpret_cast<uint8_t*>(end_)) {
        return;
    }

    chunk = reinterpret_cast<struct Chunk*>(static_cast<uint8_t*>(addr) - sizeof(struct Chunk));
    chunk->used = false;
    if (chunk < free_) {
        free_ = chunk;
    }

    freeSize_ += chunk->next - (reinterpret_cast<uint8_t*>(chunk) - ram_);
    CombineFree(chunk);
}
} // namespace OHOS
