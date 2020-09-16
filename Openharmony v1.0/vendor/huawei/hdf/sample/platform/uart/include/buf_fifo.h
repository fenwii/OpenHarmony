/* Copyright 2020 Huawei Device Co., Ltd.
 *
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

#ifndef BUF_FIFO_H
#define BUF_FIFO_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct BufferFifo {
    volatile uint32_t readPosition;
    volatile uint32_t writePosition;
    uint16_t bufSizeMask;
    uint8_t *buffer;
};

static inline uint16_t BufferFifoGetDataSize(struct BufferFifo *fifo)
{
    return (fifo->writePosition - fifo->readPosition);
}

static inline bool IsPowerOfTwo(int num)
{
    return (num > 0) && (num & (num - 1)) == 0;
}

bool BufferFifoInit(struct BufferFifo *fifo, uint8_t *buf, uint16_t bufSize);

#endif // BUF_FIFO_H

