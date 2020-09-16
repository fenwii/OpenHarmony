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

#include "securec.h"
#include "hos_types.h"
#include "hiview_cache.h"
#include "hiview_util.h"

static uint16 GetReadCursor(HiviewCache *cache);

boolean InitHiviewStaticCache(HiviewCache *cache, HiviewCacheType type, uint8 *buffer, uint16 size)
{
    if (cache == NULL) {
        return FALSE;
    }

    cache->mutex = HIVIEW_MutexInit();
    cache->usedSize = 0;
    cache->wCursor = 0;
    cache->buffer = buffer;
    cache->size = size;
    cache->type = type;

    return TRUE;
}

boolean InitHiviewCache(HiviewCache *cache, HiviewCacheType type, uint16 size)
{
    if (cache == NULL) {
        return FALSE;
    }

    uint8 *buffer = (uint8 *)HIVIEW_MemAlloc(MEM_POOL_HIVIEW_ID, size);
    if (buffer == NULL) {
        return FALSE;
    }

    cache->mutex = HIVIEW_MutexInit();
    cache->usedSize = 0;
    cache->wCursor = 0;
    cache->buffer = buffer;
    cache->size = size;
    cache->type = type;

    return TRUE;
}

int32 WriteToCache(HiviewCache *cache, const uint8 *data, uint16 wLen)
{
    if (cache == NULL || data == NULL || cache->buffer == NULL) {
        return -1;
    }

    uint16 firstLen;
    uint16 secondLen;
    HIVIEW_MutexLock(cache->mutex);
    if ((cache->size - cache->usedSize) < wLen) {
        HIVIEW_MutexUnlock(cache->mutex);
        return -1;
    }
    // overflow
    if (cache->wCursor + wLen > cache->size) {
        firstLen = cache->size - cache->wCursor;
        if (firstLen > 0) {
            if (memcpy_s(cache->buffer + cache->wCursor, firstLen, data, firstLen) == EOK) {
                cache->wCursor += firstLen;
                cache->usedSize += firstLen;
            } else {
                HIVIEW_MutexUnlock(cache->mutex);
                return -1;
            }
        }
        cache->wCursor = 0;
        secondLen = wLen - firstLen;
        if (secondLen > 0) {
            if (memcpy_s(cache->buffer + cache->wCursor, secondLen, data + firstLen, secondLen) == EOK) {
                cache->wCursor += secondLen;
                cache->usedSize += secondLen;
            } else {
                HIVIEW_MutexUnlock(cache->mutex);
                return firstLen;
            }
        }
    } else {
        if (memcpy_s(cache->buffer + cache->wCursor, wLen, data, wLen) == EOK) {
            cache->wCursor += wLen;
            cache->usedSize += wLen;
        } else {
            HIVIEW_MutexUnlock(cache->mutex);
            return -1;
        }
    }
    HIVIEW_MutexUnlock(cache->mutex);

    return wLen;
}

int32 ReadFromCache(HiviewCache *cache, uint8 *data, uint16 rLen)
{
    if (cache == NULL || data == NULL || cache->buffer == NULL) {
        return -1;
    }

    uint16 firstLen;
    uint16 secondLen;
    uint16 rCursor;
    // This function is the only read operation, so there is no need to lock
    if (cache->usedSize < rLen) {
        return -1;
    }
    rCursor = GetReadCursor(cache);
    // overflow
    if (rCursor + rLen > cache->size) {
        firstLen = cache->size - rCursor;
        if (firstLen > 0) {
            if (memcpy_s(data, firstLen, cache->buffer + rCursor, firstLen) != EOK) {
                return -1;
            }
        }
        secondLen = rLen - firstLen;
        if (secondLen > 0) {
            if (memcpy_s(data + firstLen, secondLen, cache->buffer, secondLen) != EOK) {
                return firstLen;
            }
        }
    } else {
        if (memcpy_s(data, rLen, cache->buffer + rCursor, rLen) != EOK) {
            return -1;
        }
    }
    HIVIEW_MutexLock(cache->mutex);
    cache->usedSize -= rLen;
    HIVIEW_MutexUnlock(cache->mutex);

    return rLen;
}

int32 PrereadFromCache(HiviewCache *cache, uint8 *data, uint16 rLen)
{
    if (cache == NULL || data == NULL || cache->buffer == NULL) {
        return -1;
    }
    if (cache->usedSize < rLen) {
        return -1;
    }

    uint16 firstLen;
    uint16 secondLen;
    uint16 rCursor = GetReadCursor(cache);
    // overflow
    if (rCursor + rLen > cache->size) {
        firstLen = cache->size - rCursor;
        if (firstLen > 0) {
            if (memcpy_s(data, firstLen, cache->buffer + rCursor, firstLen) != EOK) {
                return -1;
            }
        }
        secondLen = rLen - firstLen;
        if (secondLen > 0) {
            if (memcpy_s(data + firstLen, secondLen, cache->buffer, secondLen) != EOK) {
                return firstLen;
            }
        }
    } else {
        if (memcpy_s(data, rLen, cache->buffer + rCursor, rLen) != EOK) {
            return -1;
        }
    }

    return rLen;
}

void DiscardCacheData(HiviewCache *cache)
{
    if (cache == NULL) {
        return;
    }
    cache->wCursor = 0;
    cache->usedSize = 0;
}

void DestroyCache(HiviewCache *cache)
{
    if (cache == NULL) {
        return;
    }
    if (cache->buffer != NULL) {
        HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, cache->buffer);
        cache->buffer = NULL;
    }
    cache->wCursor = 0;
    cache->usedSize = 0;
    cache->size = 0;
}

static uint16 GetReadCursor(HiviewCache *cache)
{
    if (cache == NULL || cache->buffer == NULL) {
        return 0;
    }

    uint16 readCursor;
    HIVIEW_MutexLock(cache->mutex);
    if (cache->wCursor >= cache->usedSize) {
        readCursor = cache->wCursor - cache->usedSize;
    } else {
        readCursor = cache->size - (cache->usedSize - cache->wCursor);
    }
    HIVIEW_MutexUnlock(cache->mutex);
    return readCursor;
}
