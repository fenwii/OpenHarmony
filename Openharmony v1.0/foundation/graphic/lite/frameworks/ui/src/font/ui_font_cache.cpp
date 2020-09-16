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

#include "font/ui_font_cache.h"
#include <cstddef>

namespace OHOS {
UIFontCache::UIFontCache(uint8_t* ram, uint32_t size)
{
    allocator_.SetRamAddr(ram, size);
    allocator_.SetMinChunkSize(FONT_CACHE_MIN_SIZE + sizeof(Bitmap));

    uint32_t hashTableSize = sizeof(ListHead) * FONT_CACHE_HASH_NR;
    hashTable_ = reinterpret_cast<ListHead*>(allocator_.Allocate(hashTableSize));
    for (uint8_t i = 0; i < FONT_CACHE_HASH_NR; i++) {
        ListInit(hashTable_ + i);
    }

    ListInit(&lruList_);
}

UIFontCache::~UIFontCache() {}

void UIFontCache::UpdateLru(Bitmap* bitmap)
{
    ListDel(&bitmap->lruHead);
    ListInit(&bitmap->lruHead);
    ListAdd(&bitmap->lruHead, &lruList_);
}

uint8_t* UIFontCache::GetSpace(uint8_t fontId, uint32_t unicode, uint32_t size)
{
    Bitmap* bitmap = nullptr;

    uint32_t allocSize = sizeof(Bitmap) + size;
    while (bitmap == nullptr) {
        bitmap = reinterpret_cast<Bitmap*>(allocator_.Allocate(allocSize));
        if (bitmap == nullptr) {
            Bitmap* toFree = reinterpret_cast<struct Bitmap*>(reinterpret_cast<uint8_t*>(lruList_.prev) -
                                                              offsetof(struct Bitmap, lruHead)); // ListEntry
            ListDel(&toFree->hashHead);
            ListDel(&toFree->lruHead);
            allocator_.Free(toFree);
        }
    }

    ListInit(&bitmap->hashHead);
    ListInit(&bitmap->lruHead);
    ListAdd(&bitmap->hashHead, hashTable_ + fontId % FONT_CACHE_HASH_NR);
    ListAdd(&bitmap->lruHead, &lruList_);

    bitmap->fontId = fontId;
    bitmap->unicode = unicode;

    return reinterpret_cast<uint8_t*>(bitmap->data);
}

void UIFontCache::PutSpace(uint8_t* addr)
{
    if (addr == nullptr) {
        return;
    }
    Bitmap* bitmap = reinterpret_cast<Bitmap*>(addr - sizeof(Bitmap));

    ListDel(&bitmap->hashHead);
    ListDel(&bitmap->lruHead);

    allocator_.Free(bitmap);
}

uint8_t* UIFontCache::GetBitmap(uint8_t fontId, uint32_t unicode)
{
    Bitmap* bitmap = nullptr;
    ListHead* node = nullptr;

    ListHead* head = hashTable_ + fontId % FONT_CACHE_HASH_NR;
    for (node = head->next; node != head; node = node->next) {
        bitmap = reinterpret_cast<struct Bitmap*>(reinterpret_cast<uint8_t*>(node) -
                                                  offsetof(struct Bitmap, hashHead));
        if (bitmap->fontId == fontId && bitmap->unicode == unicode) {
            UpdateLru(bitmap);
            return reinterpret_cast<uint8_t*>(bitmap->data);
        }
    }

    return nullptr;
}
} // namespace OHOS
