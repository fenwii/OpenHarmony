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

#ifndef UI_FONT_CACHE_H
#define UI_FONT_CACHE_H

#include "ui_font_allocator.h"

namespace OHOS {
class UIFontCache {
public:
    static constexpr uint8_t FONT_CACHE_HASH_NR = 32;
    static constexpr uint32_t FONT_CACHE_MIN_SIZE = 20 * 20;
    struct ListHead {
        ListHead* prev;
        ListHead* next;
    };
    struct Bitmap {
        ListHead hashHead;
        ListHead lruHead;
        uint8_t fontId;
        uint32_t unicode;
        uint8_t data[];
    };

    UIFontCache(uint8_t* ram, uint32_t size);

    ~UIFontCache();

    uint8_t* GetSpace(uint8_t fontId, uint32_t unicode, uint32_t size);

    void PutSpace(uint8_t* addr);

    uint8_t* GetBitmap(uint8_t fontId, uint32_t unicode);

private:
    void UpdateLru(Bitmap* bitmap);
    void ListInit(ListHead* head)
    {
        head->prev = head;
        head->next = head;
    }
    void ListAdd(ListHead* node, ListHead* head)
    {
        head->next->prev = node;
        node->next = head->next;
        node->prev = head;
        head->next = node;
    }
    void ListDel(ListHead* node)
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    UIFontAllocator allocator_;
    ListHead* hashTable_;
    ListHead lruList_;
};
} // namespace OHOS
#endif /* UI_FONT_CACHE_H */