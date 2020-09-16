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

#ifndef UI_FONT_ALLOCATOR_H
#define UI_FONT_ALLOCATOR_H

#include <stdint.h>

namespace OHOS {
class UIFontAllocator {
    static constexpr uint8_t MEM_ALIGNMENT = 4;

    struct Chunk {
        uint32_t next;
        uint32_t prev;
        bool used;
    };

public:
    UIFontAllocator();

    ~UIFontAllocator();

    void SetRamAddr(uint8_t* ram, uint32_t size);

    void SetMinChunkSize(uint32_t size);

    void* Allocate(uint32_t size);

    void Free(void* addr);

private:
    uint32_t AlignSize(uint32_t size)
    {
        return (size + MEM_ALIGNMENT - 1U) & ~(MEM_ALIGNMENT - 1U);
    }
    void CombineFree(Chunk* cache);

    uint8_t* ram_;
    uint32_t ramSize_;
    uint32_t freeSize_;
    uint32_t minSize_;
    struct Chunk* end_;
    struct Chunk* free_;
};
} // namespace OHOS
#endif /* UI_FONT_ALLOCATOR_H */