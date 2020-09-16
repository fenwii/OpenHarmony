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

#include "hdf_netbuf.h"
#include "osal.h"
#include "los_memory.h"
#include "lwip/prot/ethernet.h"


#define HDF_LOG_TAG             NetBuf


/*
 * Net buffer is a continuous memory which consists of three parts: head buffer, data buffer and tail buffer.
 *
 *  -----------------------------------------------------
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  ^               ^                   ^               ^
 *  |               |                   |               |
 *  |<--head buff-->|<----data buff---->|<--tail buff-->|
 *                  |<----data len----->|
 *  |<---------------------len------------------------->|
 */

/*
 * Enqueue the new net buffer to the tail of buffer queue.
 *
 * @param  : q The pointer to the net buffer queue
 *           nb The new net buffer
 * @return : void
 */
void NetBufQueueEnqueue(struct NetBufQueue *q, struct NetBuf *nb)
{
    uint32_t intSave;
    LOS_SpinLockSave(&q->lock, &intSave);
    DListInsertTail(&nb->dlist, &q->dlist);
    q->size++;
    LOS_SpinUnlockRestore(&q->lock, intSave);
}

/*
 * Enqueue the new net buffer to the head of buffer queue.
 *
 * @param  : q The pointer to the net buffer queue
 *           nb The new net buffer
 * @return : void
 */
void NetBufQueueEnqueueHead(struct NetBufQueue *q, struct NetBuf *nb)
{
    uint32_t intSave;
    LOS_SpinLockSave(&q->lock, &intSave);
    DListInsertHead(&nb->dlist, &q->dlist);
    q->size++;
    LOS_SpinUnlockRestore(&q->lock, intSave);
}

/*
 * Dequeue the first net buffer from net buffer queue.
 *
 * @param  : q The pointer to the net buffer queue
 * @return : The first net buffer in net buffer queue
 */
struct NetBuf *NetBufQueueDequeue(struct NetBufQueue *q)
{
    struct NetBuf *nb = NULL;

    uint32_t intSave;
    LOS_SpinLockSave(&q->lock, &intSave);
    if (!DListIsEmpty(&q->dlist)) {
        nb = DLIST_FIRST_ENTRY(&q->dlist, struct NetBuf, dlist);
        DListRemove(&nb->dlist);
        q->size--;
    }
    LOS_SpinUnlockRestore(&q->lock, intSave);

    return nb;
}

/*
 * Dequeue the last net buffer from net buffer queue.
 *
 * @param  : q The pointer to the net buffer queue
 * @return : The last net buffer in net buffer queue
 */
struct NetBuf *NetBufQueueDequeueTail(struct NetBufQueue *q)
{
    struct NetBuf *nb = NULL;

    uint32_t intSave;
    LOS_SpinLockSave(&q->lock, &intSave);
    if (!DListIsEmpty(&q->dlist)) {
        nb = DLIST_LAST_ENTRY(&q->dlist, struct NetBuf, dlist);
        DListRemove(&nb->dlist);
        q->size--;
    }
    LOS_SpinUnlockRestore(&q->lock, intSave);

    return nb;
}

/*
 * Clear the net buffer queue and free all net buffer in net buffer queue.
 *
 * @param  : q The pointer to the net buffer queue
 * @return : void
 */
void NetBufQueueClear(struct NetBufQueue *q)
{
    struct NetBuf *nb = NULL;

    if (q == NULL) {
        return;
    }

    while ((nb = NetBufQueueDequeue(q)) != NULL) {
        NetBufFree(nb);
    }
}

/*
 * Merge two net buffer queues.
 *
 * @param  : q The pointer to the net buffer queue for added.
 *           add The pointer to the net buffer queue to add.
 * @return : void
 */
void NetBufQueueConcat(struct NetBufQueue *q, struct NetBufQueue *add)
{
    if (!NetBufQueueIsEmpty(add)) {
        DListMerge(&add->dlist, &q->dlist);
        q->size += add->size;
        add->size = 0;
    }
}

/*
 * Alloc a net buffer.
 *
 * @param  : size The net buffer size
 * @return : A new net buffer or NULL on fail
 */
struct NetBuf *NetBufAlloc(uint32_t size)
{
    struct NetBuf *nb = NULL;
    uint8_t *data = NULL;

    nb = (struct NetBuf *)LOS_MemAllocAlign(m_aucSysMem0, sizeof(*nb), CACHE_ALIGNED_SIZE);
    if (nb == NULL) {
        HDF_LOGE("%s alloc net buf fail", __func__);
        return NULL;
    }

    data = (uint8_t *)LOS_MemAllocAlign(m_aucSysMem0, size, CACHE_ALIGNED_SIZE);
    if (data == NULL) {
        HDF_LOGE("%s alloc data fail, size:%u", __func__, size);
        LOS_MemFree(m_aucSysMem0, nb);
        return NULL;
    }

    (void)memset_s(nb, sizeof(struct NetBuf), 0, sizeof(struct NetBuf));

    nb->mem = data;
    nb->len = size;
    nb->dataLen = 0;
    nb->bufs[E_HEAD_BUF].offset = 0;
    nb->bufs[E_HEAD_BUF].len    = 0;
    nb->bufs[E_DATA_BUF].offset = 0;
    nb->bufs[E_DATA_BUF].len    = 0;
    nb->bufs[E_TAIL_BUF].offset = 0;
    nb->bufs[E_TAIL_BUF].len    = size;

    return nb;
}

/*
 * Free a net buffer.
 *
 * @param  : nb A net buffer
 * @return : void
 */
void NetBufFree(struct NetBuf *nb)
{
    if (nb == NULL) {
        return;
    }

    if (nb->mem != NULL) {
        LOS_MemFree(m_aucSysMem0, nb->mem);
        nb->mem = NULL;
    }

    LOS_MemFree(m_aucSysMem0, nb);
}

/*
 * Pop head room and add to data buffer
 *
 * @param  : nb A net buffer
 *           len The length of remove data
 * @return : The new start address of net buffer data on success or NULL on fail.
 */
void *NetBufPush(struct NetBuf *nb, uint32_t id, uint32_t len)
{
    struct BufField  *headBuf = &nb->bufs[E_HEAD_BUF];
    struct BufField  *dataBuf = &nb->bufs[E_DATA_BUF];
    struct BufField  *tailBuf = &nb->bufs[E_TAIL_BUF];

    switch (id) {
        case E_HEAD_BUF:
            if (dataBuf->len < len || nb->dataLen < len) {
                HDF_LOGE("%s fail, datasize[%u], dataroom[%u], len[%u]", __func__, nb->dataLen, dataBuf->len, len);
                return NULL;
            }

            headBuf->len += len;
            dataBuf->offset += len;
            dataBuf->len -= len;
            nb->dataLen -= len;
            break;
        case E_DATA_BUF:
            if (tailBuf->len < len) {
                HDF_LOGE("%s fail, tailroom[%u], len[%u]", __func__, tailBuf->len, len);
                return NULL;
            }

            nb->dataLen += len;
            dataBuf->len += len;
            tailBuf->offset += len;
            tailBuf->len -= len;
            break;
        case E_TAIL_BUF:
            if (dataBuf->len < len) {
                HDF_LOGE("%s fail, datasize[%u], len[%u]", __func__, dataBuf->len, len);
                return NULL;
            }

            dataBuf->len -= len;
            if (nb->dataLen > len) {
                nb->dataLen -= len;
            }
            tailBuf->offset -= len;
            tailBuf->len += len;
            break;
        default:
            break;
    }

    return (nb->mem + dataBuf->offset);
}

/*
 * reduce data buffer and push to head room.
 *
 * @param  : nb A net buffer
 *           len The length of add data
 * @return : The new start address of net buffer data on success or NULL on fail.
 */
void *NetBufPop(struct NetBuf *nb, uint32_t id, uint32_t len)
{
    struct BufField  *headBuf = &nb->bufs[E_HEAD_BUF];
    struct BufField  *dataBuf = &nb->bufs[E_DATA_BUF];
    struct BufField  *tailBuf = &nb->bufs[E_TAIL_BUF];

    switch (id) {
        case E_HEAD_BUF:
            if (headBuf->len < len || dataBuf->offset < len) {
                HDF_LOGE("%s fail, headroom[%u], len[%u]", __func__, headBuf->len, len);
                return NULL;
            }

            headBuf->len -= len;
            dataBuf->offset -= len;
            dataBuf->len += len;
            nb->dataLen += len;
            break;
        case E_DATA_BUF:
            if (nb->dataLen < len || dataBuf->len < len) {
                HDF_LOGE("%s fail, datasize[%u], dataroom[%u], len[%u]",
                    __func__, nb->dataLen, dataBuf->len, len);
                return NULL;
            }
            headBuf->len += len;
            dataBuf->offset += len;
            dataBuf->len -= len;
            nb->dataLen -= len;
            break;
        case E_TAIL_BUF:
            if (tailBuf->len < len) {
                HDF_LOGE("%s fail, tailroom[%u], len[%u]", __func__, tailBuf->len, len);
                return NULL;
            }
            tailBuf->len -= len;
            tailBuf->offset += len;
            dataBuf->len += len;
            nb->dataLen += len;
            break;
        default:
            break;
    }

    return (nb->mem + dataBuf->offset);
}

/*
 * Expand a net buffer
 *
 * @param  : nb A net buffer
 *           head The reserved size at head room
 *           tail The reserved size at tail room
 * @return : 0 for success and others for failure
 */
int32_t NetBufResizeRoom(struct NetBuf *nb, uint32_t head, uint32_t tail)
{
    uint8_t *data = NULL;
    uint32_t size = head + nb->len + tail;
    uint32_t offset;

    size = ALIGN(size, CACHE_ALIGNED_SIZE);
    data = (uint8_t *)LOS_MemAllocAlign(m_aucSysMem0, size, CACHE_ALIGNED_SIZE);
    if (data == NULL) {
        HDF_LOGE("%s mem alloc fail, size:%u", __func__, size);
        return HDF_FAILURE;
    }

    if (memcpy_s(data + head, size - head, nb->mem, nb->bufs[E_TAIL_BUF].offset) != EOK) {
        HDF_LOGE("%s memcopy failed", __func__);
    }

    offset = nb->bufs[E_HEAD_BUF].len;

    LOS_MemFree(m_aucSysMem0, nb->mem);
    nb->mem = data;
    nb->len = size;
    nb->bufs[E_HEAD_BUF].offset = 0;
    nb->bufs[E_HEAD_BUF].len = offset + head;
    nb->bufs[E_DATA_BUF].offset = offset + head;
    nb->bufs[E_DATA_BUF].len = nb->dataLen;
    nb->bufs[E_TAIL_BUF].offset += head;
    nb->bufs[E_TAIL_BUF].len += tail;

    return HDF_SUCCESS;
}

/*
 * Concat a net buffer to another net buffer and free the net buffer for concatted.
 *
 * @param  : nb A net buffer
 *           cnb The concat net buffer
 * @return : 0 for success and others for failure
 */
uint32_t NetBufConcat(struct NetBuf *nb, struct NetBuf *cnb)
{
    uint32_t tailroom;

    if (nb == NULL || cnb == NULL) {
        return HDF_FAILURE;
    }

    tailroom = NetBufGetRoom(nb, E_TAIL_BUF);
    if (tailroom < cnb->dataLen) {
        HDF_LOGE("%s can not concat, tailroom[%u], len[%u]", __func__, tailroom, cnb->len);
        return HDF_FAILURE;
    }

    if (nb->mem != NULL) {
        uint8_t *src = cnb->mem + cnb->bufs[E_DATA_BUF].offset;
        uint8_t *dst = nb->mem + nb->bufs[E_TAIL_BUF].offset;

        if (memcpy_s(dst, tailroom, src, cnb->dataLen) != EOK) {
            return HDF_FAILURE;
        }
        NetBufPush(nb, E_DATA_BUF, cnb->dataLen);
    }

    NetBufFree(cnb);

    return HDF_SUCCESS;
}

/*
 * Convert net buffer to LWIP pbuf.
 *
 * @param  : nb The net buffer
 * @return : pbuf for lwip
 */
struct pbuf *NetBuf2Pbuf(const struct NetBuf *nb)
{
    struct pbuf *p  = NULL;
    struct eth_hdr *hdr = NULL;
    uint32_t len = NetBufGetDataLen(nb);

    p = pbuf_alloc(PBUF_RAW, (uint16_t)(len + ETH_PAD_SIZE), PBUF_RAM);
    if (p == NULL) {
        HDF_LOGE("%s pbuf_alloc failed! len = %d", __func__, len);
        return NULL;
    }

    hdr = (struct eth_hdr *)p->payload;
    if (memcpy_s(&hdr->dest, len, NetBufGetAddress(nb, E_DATA_BUF), len) != EOK) {
        pbuf_free(p);
        HDF_LOGE("%s memcpy err!", __func__);
        return NULL;
    }

    return p;
}

/*
 * Convert LWIP pbuf to net buffer.
 *
 * @param  : netdev The net device object
 *           lwip_buf The LWIP net buffer
 * @return : The net buffer
 */
struct NetBuf *Pbuf2NetBuf(const struct NetDevice *netdev, struct pbuf *lwipBuf)
{
    struct NetBuf *nb   = NULL;
    struct pbuf   *tmp  = NULL;
    uint32_t index = 0;
    uint32_t offset = 0;

    nb = NetBufDevAlloc(netdev, lwipBuf->tot_len);
    if (nb == NULL) {
        HDF_LOGE("%s alloc net buffer failed! len = %d", __func__, lwipBuf->tot_len);
        return NULL;
    }

    offset = nb->bufs[E_DATA_BUF].offset;

    for (tmp = lwipBuf; tmp != NULL; tmp = tmp->next, index++) {
        if (tmp->len == 0 || tmp->payload == NULL) {
            continue;
        }

        if (NetBufGetRoom(nb, E_TAIL_BUF) < tmp->len) {
            HDF_LOGE("%s fail, tailroom[%d], len[%d], idx[%d]",
                __func__, NetBufGetRoom(nb, E_TAIL_BUF), tmp->len, index);
            NetBufFree(nb);
            return NULL;
        }

        if (memcpy_s(nb->mem + offset, tmp->len, tmp->payload, tmp->len) != EOK) {
            HDF_LOGE("%s memcpy_s err!", __func__);
        }
        NetBufPush(nb, E_DATA_BUF, tmp->len);

        offset += tmp->len;
    }

    return nb;
}
