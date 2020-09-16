/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup WLAN
 * @{
 *
 * @brief Defines a WLAN module that supports cross-OS migration, component adaptation, and modular assembly and
 * compilation. Driver developers of WLAN vendors can adapt their driver code based on the unified APIs provided
 * by the WLAN module.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hdf_netbuf.h
 *
 * @brief Declares network data buffers and provides APIs for operating buffer queues.
 *
 * This file describes the following network data operations for network device driver development: \n
 *
 * Applying for, releasing, and moving a network data buffer
 * Initializing a network data buffer queue, placing a network data buffer to a queue, and removing a network data
 * buffer from a queue
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HDF_NETBUF_H
#define HDF_NETBUF_H

#include "los_spinlock.h"
#include "hdf_dlist.h"
#include "lwip/pbuf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Enumerates the segments of a network data buffer.
 *
 * The entire network data buffer is divided into three segments: a header, data, and a tail.
 * The header and tail are used to extend both ends of the data segment.
 *
 * @since 1.0
 */
enum {
    E_HEAD_BUF, /**< Header buffer segment */
    E_DATA_BUF, /**< Data segment */
    E_TAIL_BUF, /**< Tail buffer segment */
    MAX_BUF_NUM /**< Maximum number of buffer segments */
};

struct BufField {
    uint32_t offset;
    uint32_t len;
};

/**
 * @brief Defines the reserved field of a network data buffer used to store private information.
 *
 * The length of the reserved field is <b>68</b> bytes.
 */
#define MAX_NETBUF_RESEVER_SIZE     68

/**
 * @brief Records and saves a network data buffer.
 *
 * This structure is used to transmit network data between the protocol stack and network driver.
 *
 * @since 1.0
 */
struct NetBuf {
    struct DListHead dlist;             /**< Doubly linked list. Generally, multiple network data buffers are
                                             linked by using a doubly linked list. */
    struct BufField bufs[MAX_BUF_NUM];  /**< Defines buffer segments used to record the offset address
                                             (based on the memory buffer address) and length of each buffer segment,
                                             including the header buffer segment, data segment, and tail buffer segment.
                                             For details, see {@link MAX_BUF_NUM}. */
    uint8_t     *mem;                   /**< Memory buffer address */
    uint32_t    len;                    /**< Length of the memory buffer */
    uint32_t    dataLen;                /**< Actual data length of the network data buffer */
    void        *dev;                   /**< Network device that receives the network data */
    uint32_t    qmap;                   /**< Queue mappings of the network data buffer */
    uint8_t     rsv[MAX_NETBUF_RESEVER_SIZE]; /**< Reserved field. For details, see {@link MAX_NETBUF_RESEVER_SIZE}. */
};

/**
 * @brief Indicates the queues for storing network data.
 *
 * Queues can be used to process multiple pieces of network data in a centralized manner, improving efficiency.
 *
 * @since 1.0
 */
struct NetBufQueue {
    struct DListHead dlist; /**< Doubly linked list. Generally, multiple network data buffers are linked
                                 by using a doubly linked list. */
    uint32_t     size;      /**< Number of network data buffers in the queue */
    struct Spinlock lock;      /**< Queue operation lock */
};

/**
 * @brief Initializes a network data buffer queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @since 1.0
 */
static inline void NetBufQueueInit(struct NetBufQueue *q)
{
    DListHeadInit(&q->dlist);
    LOS_SpinInit(&q->lock);
    q->size = 0;
}

/**
 * @brief Obtains the size of a network data buffer queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @return Returns the size of the network data buffer queue.
 *
 * @since 1.0
 */
static inline uint32_t NetBufQueueSize(const struct NetBufQueue *q)
{
    return q->size;
}

/**
 * @brief Checks whether the network data buffer queue is empty.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @return Returns <b>true</b> if the queue is empty; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
static inline bool NetBufQueueIsEmpty(const struct NetBufQueue *q)
{
    return DListIsEmpty(&q->dlist);
}

/**
 * @brief Adds a network data buffer to the tail of a queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 * @param nb Indicates the pointer to the network data buffer.
 *
 * @since 1.0
 */
void NetBufQueueEnqueue(struct NetBufQueue *q, struct NetBuf *nb);

/**
 * @brief Adds a network data buffer to the header of a queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 * @param nb Indicates the pointer to the network data buffer.
 *
 * @since 1.0
 */
void NetBufQueueEnqueueHead(struct NetBufQueue *q, struct NetBuf *nb);

/**
 * @brief Obtains a network data buffer from the header of a queue and deletes it from the queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @return Returns the pointer to the first network data buffer if the queue is not empty;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct NetBuf *NetBufQueueDequeue(struct NetBufQueue *q);

/**
 * @brief Obtains a network data buffer from the tail of a queue and deletes it from the queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @return Returns the pointer to the last network data buffer if the queue is not empty;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct NetBuf *NetBufQueueDequeueTail(struct NetBufQueue *q);

/**
 * @brief Obtains the network data buffer from the header of a queue, without deleting it from the queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @return Returns the pointer to the first network data buffer if the queue is not empty;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
static inline struct NetBuf *NetBufQueueAtHead(const struct NetBufQueue *q)
{
    return (DListIsEmpty(&q->dlist)) ? NULL : DLIST_FIRST_ENTRY(&q->dlist, struct NetBuf, dlist);
}

/**
 * @brief Obtains the network data buffer from the tail of a queue, without deleting it from the queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @return Returns the pointer to the last network data buffer if the queue is not empty;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
static inline struct NetBuf *NetBufQueueAtTail(const struct NetBufQueue *q)
{
    return (DListIsEmpty(&q->dlist)) ? NULL : DLIST_LAST_ENTRY(&q->dlist, struct NetBuf, dlist);
}

/**
 * @brief Clears a network data buffer queue and releases the network data buffer in the queue.
 *
 * @param q Indicates the pointer to the network data buffer queue.
 *
 * @since 1.0
 */
void NetBufQueueClear(struct NetBufQueue *q);

/**
 * @brief Moves all network data buffers from one queue to another and clears the source queue.
 *
 * @param q Indicates the pointer to the target network data buffer queue.
 * @param add Indicates the pointer to the source network data buffer queue.
 *
 * @since 1.0
 */
void NetBufQueueConcat(struct NetBufQueue *q, struct NetBufQueue *add);

struct NetDevice;

/**
 * @brief Applies for a network data buffer.
 *
 * @param size Indicates the size of the network data buffer.
 *
 * @return Returns the pointer to the network data buffer if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct NetBuf *NetBufAlloc(uint32_t size);

/**
 * @brief Releases a network data buffer.
 *
 * @param nb Indicates the pointer to the network data buffer.
 *
 * @since 1.0
 */
void NetBufFree(struct NetBuf *nb);

/**
 * @brief Applies for a network data buffer based on the reserved space and requested size set by a network device.
 *
 * @param dev Indicates the pointer to the network device.
 * @param size Indicates the size of the network data buffer applied.
 *
 * @return Returns the pointer to the network data buffer if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct NetBuf *NetBufDevAlloc(const struct NetDevice *dev, uint32_t size);

/**
 * @brief Performs operations based on the segment ID of a network data buffer.
 * The function is opposite to that of {@link NetBufPop}.
 *
 * Description:
 * ID Type | Result
 * -------|---------
 * E_HEAD_BUF | The length of the header buffer segment is increased and the length of the data segment is reduced.
 * E_DATA_BUF | The length of the data segment is increased and the length of the tail buffer segment is reduced.
 * E_TAIL_BUF | The length of the tail buffer segment is increased and the length of the data segment is reduced.
 *
 * @param nb Indicates the pointer to the network data buffer.
 * @param id Indicates the buffer segment ID.
 * @param len Indicates the operation length.
 *
 * @return Returns the start address of the data segment if the operation is successful;
 * returns <b>NULL</b> if the operation length exceeds the space of a specified buffer segment.
 *
 * @since 1.0
 */
void *NetBufPush(struct NetBuf *nb, uint32_t id, uint32_t len);

/**
 * @brief Performs operations based on the segment ID of a network data buffer.
 * The function is opposite to that of {@link NetBufPush}.
 *
 * Description:
 * ID Type | Result
 * -------|---------
 * E_HEAD_BUF | The length of the header buffer segment is reduced and the length of the data segment is increased.
 * E_DATA_BUF| The length of the data segment is reduced and the length of the tail buffer segment is increased.
 * E_TAIL_BUF | The length of the tail buffer segment is reduced and the length of the data segment is increased.
 *
 * @param nb Indicates the pointer to the network data buffer.
 * @param id Indicates the buffer segment ID.
 * @param len Indicates the operation length.
 *
 * @return Returns the start address of the data segment if the operation is successful;
 * returns <b>NULL</b> if the operation length exceeds the space of a specified buffer segment.
 *
 * @since 1.0
 */
void *NetBufPop(struct NetBuf *nb, uint32_t id, uint32_t len);

/**
 * @brief Obtains the address of a specified buffer segment in a network data buffer.
 *
 * @param nb Indicates the pointer to the network data buffer.
 * @param id Indicates the buffer segment ID.
 *
 * @return Returns the address of the specified buffer segment if the operation is successful;
 * returns <b>NULL</b> if the buffer segment ID is invalid.
 *
 * @since 1.0
 */
static inline uint8_t *NetBufGetAddress(const struct NetBuf *nb, uint32_t id)
{
    if (id < MAX_BUF_NUM) {
        return (nb->mem + nb->bufs[id].offset);
    }

    return NULL;
}

/**
 * @brief Obtains the size of a specified buffer segment space in a network data buffer.
 *
 * @param nb Indicates the pointer to the network data buffer.
 * @param id Indicates the buffer segment ID.
 *
 * @return Returns the size of the specified buffer segment space if the operation is successful;
 * returns <b>NULL</b> if the buffer segment ID is invalid.
 *
 * @since 1.0
 */
static inline uint32_t NetBufGetRoom(const struct NetBuf *nb, uint32_t id)
{
    if (id < MAX_BUF_NUM) {
        return nb->bufs[id].len;
    }

    return 0;
}

/**
 * @brief Obtains the actual data length of the data segment of a network data buffer.
 *
 * @param nb Indicates the pointer to the network data buffer.
 *
 * @return Returns the actual data length of the data segment.
 *
 * @since 1.0
 */
static inline uint32_t NetBufGetDataLen(const struct NetBuf *nb)
{
    return nb->dataLen;
}

/**
 * @brief Adjusts the size of a network data buffer space.
 *
 * This function is used to apply for a new network data buffer based on the configured reserved space and
 * the size of the source network data buffer, and copy the actual data to the new network data buffer.
 *
 * @param nb Indicates the pointer to the network data buffer.
 * @param head Indicates the size of the header buffer segment reserved.
 * @param tail Indicates the size of the tail buffer segment reserved.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 *
 * @since 1.0
 */
int32_t NetBufResizeRoom(struct NetBuf *nb, uint32_t head, uint32_t tail);

/**
 * @brief Copies data in a network data buffer to another network data buffer.
 *
 * @param nb Indicates the pointer to the network data buffer.
 * @param cnb Indicates the pointer to the target network data buffer.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a non-zero value otherwise.
 *
 * @since 1.0
 */
uint32_t NetBufConcat(struct NetBuf *nb, struct NetBuf *cnb);

/**
 * @brief Converts the <b>pbuf</b> structure of Lightweight TCP/IP Stack (lwIP) to a network data buffer.
 *
 * When a network device is specified, the reserved space of the network device will be added to
 * the size of the converted network data buffer.
 *
 * @param netdev Indicates the pointer to the network device.
 * @param lwip_buf Indicates the pointer to the data buffer of lwIP.
 *
 * @return Returns the pointer to the network data buffer if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct NetBuf *Pbuf2NetBuf(const struct NetDevice *netdev, struct pbuf *lwipBuf);

/**
 * @brief Converts a network data buffer to the <b>pbuf</b> structure of Lightweight TCP/IP Stack (lwIP).
 *
 * @param nb Indicates the pointer to the network data buffer.
 *
 * @return Returns the pointer to the <b>pbuf</b> structure if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct pbuf *NetBuf2Pbuf(const struct NetBuf *nb);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* HDF_NETBUF_H */
