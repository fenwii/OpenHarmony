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

#ifndef HOS_LITE_HIVIEW_CACHE_H
#define HOS_LITE_HIVIEW_CACHE_H

#include "hos_types.h"
#include "hiview_util.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef enum {
    CORE_CACHE = 0,
    LOG_CACHE,
    JS_LOG_CACHE,
    DUMP_CACHE,
    FAULT_EVENT_CACHE,
    UE_EVENT_CACHE,
    STAT_EVENT_CACHE,
} HiviewCacheType;

#pragma pack(1)
typedef struct {
    HiviewMutexId_t mutex;
    uint16 wCursor;    // 0-65535
    uint16 usedSize;   // 0-65535
    uint16 size;       // cache size 0-65535
    HiviewCacheType type;
    uint8 *buffer;     // Circular buffer
} HiviewCache;
#pragma pack()

/**
 * Initialize the cache object using static memory.
 * @param cache Operation object.
 * @param type cache type.
 * @param buffer External static memory.
 * @param size Static memory size.
 * @return TRUE/FALSE.
 **/
boolean InitHiviewStaticCache(HiviewCache *cache, HiviewCacheType type, uint8 *buffer, uint16 size);

/**
 * Initialize the cache object.
 * @param cache Operation object.
 * @param type cache type.
 * @param size cache size.
 * @return TRUE/FALSE.
 **/
boolean InitHiviewCache(HiviewCache *cache, HiviewCacheType type, uint16 size);

/**
 * Write data to cache.
 * @param cache Operation object.
 * @param data Data to be written to the cache.
 * @param wLen The length of the data to be written.
 * @return Length write.
 **/
int32 WriteToCache(HiviewCache *cache, const uint8 *data, uint16 wLen);

/**
 * Read data form cache.
 * @param cache Operation object.
 * @param data Read buffer.
 * @param rLen The length of the data to be read.
 * @return Length read.
 **/
int32 ReadFromCache(HiviewCache *cache, uint8 *data, uint16 rLen);

/**
 * Preread data form cache.
 * Use this method when you don't want to modify the read status of the cache.
 * @param cache Operation object.
 * @param data Read buffer.
 * @param rLen The length of the data to be read.
 * @return Length read.
 * @attention The value of rCursor will not be changed.
 **/
int32 PrereadFromCache(HiviewCache *cache, uint8 *data, uint16 rLen);

/**
 * Discard all cache data.
 * Use this method when an unrecoverable data exception is detected.
 * @param cache Operation object.
 **/
void DiscardCacheData(HiviewCache *cache);

/**
 * Destroy the cache and release the memory.
 * @param cache Operation object.
 **/
void DestroyCache(HiviewCache *cache);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HOS_LITE_HIVIEW_CACHE_H */
