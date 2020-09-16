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

#ifndef BUFFER_SOURCE_H
#define BUFFER_SOURCE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <vector>
#include <stddef.h>
#include <stdint.h>
#include <mutex>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct tagBufferInfo {
    unsigned long long phyAddr;
    void *virAddr;
    int fd;
    int bufLen;
    int offset;
    int size;
    int idx;
} BufferInfo;

typedef struct tagQueBuffer {
    int idx;
    int flag;
    int offset;
    int size;
    long long timestamp;
} QueBuffer;

typedef enum TagBufferFlag {
    BUFFER_FLAG_SYNCFRAME     = 1,
    BUFFER_FLAG_CODECCONFIG   = 2,
    BUFFER_FLAG_EOS           = 4,
    BUFFER_FLAG_PARTIAL_FRAME = 8,
    BUFFER_FLAG_ENDOFFRAME =    16,
    BUFFER_FLAG_MUXER_DATA    = 32,
}BufferFlag;

class BufferSource {
#define QUEUE_SIZE  10
#define BUFER_SIZE       (2* 1024)  /* 2KB */

public:
    BufferSource(void);
    virtual ~BufferSource(void);
    int Init(void);
    int GetQueSize(void);
    int GetBufferInfo(int idx, BufferInfo* info);
    int QueIdleBuffer(const QueBuffer *buffer);
    int DequeIdleBuffer(QueBuffer* buffer, int timeOut);
    size_t GetIdleQueSize(void);
    int QueFilledBuffer(const QueBuffer *buffer);
    int DequeFilledBuffer(QueBuffer* buffer, int timeOut);
    size_t GetFilledQueSize(void);
    int32_t GetFilledQueDataSize(void);
    int GetFilledBuffer(size_t idx, QueBuffer* buffer);

private:
    bool inited_;
    BufferInfo buffer_[QUEUE_SIZE];
    std::vector<QueBuffer> idleBuffer_;
    std::vector<QueBuffer> filledBuffer_;
    std::mutex idleQueMutex_;
    std::mutex filledQueMutex_;
};


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef BUFFER_SOURCE_H */
