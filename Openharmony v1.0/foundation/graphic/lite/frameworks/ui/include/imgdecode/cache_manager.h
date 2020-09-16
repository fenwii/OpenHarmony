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

#ifndef GRAPHIC_LITE_CACHE_MANAGER_H
#define GRAPHIC_LITE_CACHE_MANAGER_H

#include "file_img_decoder.h"

namespace OHOS {
class CacheEntry : public HeapBase {
public:
    CacheEntry() : dsc_{0}, life_(0) {}

    ~CacheEntry() {}

    ImageSrcType GetImgSrcType() const
    {
        return dsc_.srcType;
    }

    const uint8_t* GetImgData() const;

    ImageHeader GetImgHeader() const
    {
        return dsc_.imgInfo.header;
    }

    ImageInfo GetImageInfo() const
    {
        return dsc_.imgInfo;
    }

    RetCode ReadLine(const Point& start, int16_t bufSize, uint8_t* buf);

    bool InCache() const
    {
        return dsc_.inCache_;
    }

private:
    static constexpr uint16_t MAX_SRC_LENGTH = 4096;

    friend class CacheManager;

    void Clear();
    void ClearSrc();
    RetCode SetSrc(const char* path);

    FileImgDecoder::ImgResDsc dsc_;
    int32_t life_;
};

class CacheManager : public HeapBase {
public:
    static CacheManager& GetInstance()
    {
        static CacheManager instance;
        return instance;
    }

    RetCode Init(uint16_t size);

    uint16_t GetSize()
    {
        return size_;
    }

    RetCode Open(const char* path, const Style& style, CacheEntry& entry);

    RetCode Close(const char* path);

    RetCode Reset();

    RetCode ReadToCache(CacheEntry& entry);

    bool GetImageHeader(const char* path, ImageHeader& header);

private:
    static constexpr uint8_t MAX_CACHE_ENTRY_NUM = 32;

    CacheManager() : size_(0), entryArr_(nullptr){}

    ~CacheManager() {}

    void Clear(CacheEntry& entry);

    void AgingAll(int32_t time = AGING_INTERVAL);

    RetCode GetIndex(const char* src, uint16_t& hittedIndex);

    RetCode SelectEntryToReplace(uint16_t& selectedIndex);

    RetCode TryDecode(const char* path, const Style& style, CacheEntry& entry);

    uint16_t size_;
    CacheEntry* entryArr_;
    static constexpr uint8_t AGING_INTERVAL = 1;
    static constexpr uint8_t LIFE_GAIN_INTERVAL = 1;
    static constexpr uint16_t LIFE_LIMIT = 1000;
};
} // namespace OHOS

#endif