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

#include "imgdecode/cache_manager.h"
#include "file.h"
#include "graphic_log.h"
#include "hal_tick.h"
#include "securec.h"

namespace OHOS {
const uint8_t* CacheEntry::GetImgData() const
{
    return dsc_.imgInfo.data;
}

RetCode CacheEntry::ReadLine(const Point& start, int16_t len, uint8_t* buf)
{
    RetCode ret;
    if (dsc_.decoder != nullptr) {
        ret = dsc_.decoder->ReadLine(dsc_, start, len, buf);
    } else {
        ret = RetCode::FAIL;
    }

    return ret;
}

void CacheEntry::Clear()
{
    if (dsc_.decoder != nullptr) {
        dsc_.decoder->Close(dsc_);
    }

    dsc_.decoder = nullptr;
    ClearSrc();
    dsc_.imgInfo.data = nullptr;
    dsc_.fd = FILE_RET_FAIL;
    dsc_.srcType = IMG_SRC_UNKNOWN;
    life_ = 0;
}

void CacheEntry::ClearSrc()
{
    if (dsc_.srcType == IMG_SRC_FILE) {
        UIFree(const_cast<char*>(dsc_.path));
    }
    dsc_.path = nullptr;
}

RetCode CacheEntry::SetSrc(const char* path)
{
    ClearSrc();
    if (dsc_.srcType == IMG_SRC_FILE) {
        size_t strLen = strlen(path);
        if (strLen > MAX_SRC_LENGTH) {
            return RetCode::FAIL;
        }
        char* newStr = static_cast<char*>(UIMalloc(static_cast<uint32_t>(strLen) + 1));
        if (newStr == nullptr) {
            return RetCode::FAIL;
        }
        if (memcpy_s(newStr, strLen + 1, path, strLen) != EOK) {
            UIFree(reinterpret_cast<void*>(newStr));
            newStr = nullptr;
            return RetCode::FAIL;
        }
        newStr[strLen] = '\0';
        dsc_.path = newStr;
    } else {
        dsc_.path = path;
    }
    return RetCode::OK;
}

RetCode CacheManager::Init(uint16_t size)
{
    if (size == 0 || size > MAX_CACHE_ENTRY_NUM) {
        return RetCode::FAIL;
    }
    Reset();
    if (entryArr_ != nullptr) {
        UIFree(reinterpret_cast<void*>(entryArr_));
    }

    uint32_t tmpCacheSize = size * sizeof(CacheEntry);
    entryArr_ = static_cast<CacheEntry*>(UIMalloc(tmpCacheSize));
    if (entryArr_ == nullptr) {
        size_ = 0;
        return RetCode::FAIL;
    }

    if (memset_s(entryArr_, tmpCacheSize, 0, tmpCacheSize) != EOK) {
        UIFree(reinterpret_cast<void*>(entryArr_));
        entryArr_ = nullptr;
        return RetCode::FAIL;
    }

    size_ = size;
    return RetCode::OK;
}

RetCode CacheManager::Open(const char* path, const Style& style, CacheEntry& entry)
{
    if (path == nullptr || GetSize() <= 0) {
        return RetCode::FAIL;
    }

    AgingAll();
    uint16_t indexHitted = 0;
    RetCode ret = GetIndex(path, indexHitted);
    if (ret == RetCode::OK) {
        ReadToCache(entryArr_[indexHitted]);
        entry = entryArr_[indexHitted];
        return RetCode::OK;
    }

    SelectEntryToReplace(indexHitted);
    if (entryArr_[indexHitted].dsc_.path != nullptr) {
        entryArr_[indexHitted].dsc_.decoder->Close(entryArr_[indexHitted].dsc_);
    }

    uint32_t startTime = HALTick::GetInstance().GetTime();
    entryArr_[indexHitted].life_ = 0;

    ret = TryDecode(path, style, entryArr_[indexHitted]);
    if (ret != RetCode::OK) {
        return ret;
    }
    ReadToCache(entryArr_[indexHitted]);
    entryArr_[indexHitted].life_ = HALTick::GetInstance().GetElapseTime(startTime);
    entry = entryArr_[indexHitted];
    return RetCode::OK;
}

RetCode CacheManager::Close(const char* path)
{
    if (path == nullptr) {
        return RetCode::FAIL;
    }

    for (uint16_t index = 0; index < GetSize(); index++) {
        if (entryArr_[index].dsc_.srcType == IMG_SRC_FILE) {
            if (entryArr_[index].dsc_.path == nullptr) {
                continue;
            }
            if (strcmp(entryArr_[index].dsc_.path, path) == 0) {
                entryArr_[index].dsc_.decoder->Close(entryArr_[index].dsc_);
                Clear(entryArr_[index]);
                break;
            }
        } else {
            if (entryArr_[index].dsc_.path == path) {
                entryArr_[index].dsc_.decoder->Close(entryArr_[index].dsc_);
                Clear(entryArr_[index]);
                break;
            }
        }
    }

    return RetCode::OK;
}

bool CacheManager::GetImageHeader(const char* path, ImageHeader& header)
{
    CacheEntry entry;
    Style useless;
    RetCode ret = Open(path, useless, entry);
    if (ret != RetCode::OK) {
        GRAPHIC_LOGW("CacheManager::GetImageHeader Image get info found unknown src type\n");
        return false;
    }

    header = entry.GetImgHeader();
    return true;
}

RetCode CacheManager::Reset()
{
    if (entryArr_ == nullptr) {
        return RetCode::OK;
    }

    for (uint16_t index = 0; index < GetSize(); index++) {
        if (entryArr_[index].dsc_.path != nullptr) {
            entryArr_[index].dsc_.decoder->Close(entryArr_[index].dsc_);
            Clear(entryArr_[index]);
        }
    }

    return RetCode::OK;
}

RetCode CacheManager::ReadToCache(CacheEntry& entry)
{
    return entry.dsc_.decoder->ReadToCache(entry.dsc_);
}

void CacheManager::Clear(CacheEntry& entry)
{
    entry.Clear();
}

void CacheManager::AgingAll(int32_t time)
{
    for (uint16_t index = 0; index < GetSize(); index++) {
        if (entryArr_[index].life_ > INT32_MIN + AGING_INTERVAL) {
            entryArr_[index].life_ -= time;
        }
    }
}

RetCode CacheManager::GetIndex(const char* path, uint16_t& hittedIndex)
{
    for (uint16_t index = 0; index < GetSize(); index++) {
        if (entryArr_[index].dsc_.srcType == IMG_SRC_FILE) {
            if (entryArr_[index].dsc_.path != nullptr && strcmp(path, entryArr_[index].dsc_.path) == 0) {
                entryArr_[index].life_ += entryArr_[index].dsc_.timeToOpen * LIFE_GAIN_INTERVAL;
                if (entryArr_[index].life_ > LIFE_LIMIT) {
                    entryArr_[index].life_ = LIFE_LIMIT;
                }
                hittedIndex = index;
                return RetCode::OK;
            }
        } else {
            ImageInfo* imgDsc = reinterpret_cast<ImageInfo*>(const_cast<char*>(path));
            if (entryArr_[index].dsc_.path == path && entryArr_[index].dsc_.imgInfo.data == imgDsc->data) {
                entryArr_[index].life_ += entryArr_[index].dsc_.timeToOpen * LIFE_GAIN_INTERVAL;
                if (entryArr_[index].life_ > LIFE_LIMIT) {
                    entryArr_[index].life_ = LIFE_LIMIT;
                }
                hittedIndex = index;
                return RetCode::OK;
            }
        }
    }

    return RetCode::FAIL;
}

RetCode CacheManager::SelectEntryToReplace(uint16_t& selectedIndex)
{
    selectedIndex = 0;
    for (uint16_t index = 0; index < GetSize(); index++) {
        if (entryArr_[index].life_ < entryArr_[selectedIndex].life_) {
            selectedIndex = index;
        }
    }

    return RetCode::OK;
}

RetCode CacheManager::TryDecode(const char* path, const Style& style, CacheEntry& entry)
{
    FileImgDecoder* decoder = &(FileImgDecoder::GetInstance());
    if (decoder == nullptr) {
        Clear(entry);
        return RetCode::FAIL;
    }

    entry.dsc_.srcType = IMG_SRC_FILE;
    RetCode ret = entry.SetSrc(path);
    if (ret != RetCode::OK) {
        Clear(entry);
        return ret;
    }
    entry.dsc_.decoder = decoder;

    ret = entry.dsc_.decoder->GetHeader(entry.dsc_);
    if (ret != RetCode::OK) {
        Clear(entry);
        return ret;
    }

    ret = entry.dsc_.decoder->Open(entry.dsc_);
    if (ret != RetCode::OK) {
        Clear(entry);
        return ret;
    }

    return ret;
}
} // namespace OHOS
