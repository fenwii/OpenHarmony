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

#include "dmslite_tlv_common.h"

#include <stdbool.h>
#include <string.h>

#include "securec.h"

#include "dmslite_log.h"

/* Notice: currently only four type of nodes, i.e. command id, callee package name and ability name,
caller signature are supported */
#define MAX_VALID_NODES 4

#define HIGH_BIT_MASK 0xFF
#define LOW_BIT_MASK 0x7F
#define TLV_LENGTH_SHIFT_BITS 7

#define BREAK_IF_FAILURE(errCode);       \
    if ((errCode) != DMS_TLV_SUCCESS) {  \
        break;                           \
    }                                    \

static inline bool IsNextTlvLength(uint8_t num)
{
    /* 128-16383 : 0b1xxxxxxx 0b0xxxxxxx */
    return (((num) & HIGH_BIT_MASK) >> TLV_LENGTH_SHIFT_BITS) == 0x00;
}

static inline void TlvByteToLength(uint8_t byte, uint16_t *len)
{
    *len = ((*len) << TLV_LENGTH_SHIFT_BITS) | (byte & LOW_BIT_MASK);
}

static inline bool IsValidNodeNum(uint8_t num)
{
    return num == MAX_VALID_NODES;
}

static TLV_ERR_CODE TlvBytesToLength(const uint8_t *bytesBuffer, uint16_t bufLength,
                                     uint16_t *length, uint8_t *bytesNumber)
{
    uint8_t bytesNum = 0;
    uint16_t len = 0;
    /* compute TLV's L, when value > 127, the L should be two bytes, else L is one byte long
       0-127      :  0b0xxxxxxx
       128-16383  :  0b1xxxxxxx 0b0xxxxxxx */
    for (uint8_t i = 0; i < bufLength; i++) {
        TlvByteToLength(bytesBuffer[i], &len);
        bytesNum++;
        if (IsNextTlvLength(bytesBuffer[i])) {
            HILOGD("[bytes num = %d]", bytesNum);
            break;
        }
        if (bytesNum >= TLV_MAX_LENGTH_BYTES) {
            return DMS_TLV_ERR_LEN;
        }
    }
    /* it is meaningless to have a node with length being zero */
    if (len == 0) {
        return DMS_TLV_ERR_LEN;
    }

    *length = len;
    *bytesNumber = bytesNum;

    return DMS_TLV_SUCCESS;
}

static TLV_ERR_CODE TlvFillNode(const uint8_t *byteBuffer, uint16_t bufLength,
                                TLV_NODE_S *node, uint16_t *actualHandledLen)
{
    if (bufLength <= TLV_TYPE_LEN) {
        HILOGE("[Bad bufLength = %d]", bufLength);
        return DMS_TLV_ERR_LEN;
    }

    /* fill TLV's T(type) */
    node->type = *byteBuffer;
    uint16_t curTlvNodeLen = TLV_TYPE_LEN;

    /* fill TLV's L(length) */
    uint16_t length = 0;
    uint8_t bytesNum = 0;
    const uint8_t *lengthPartAddr = byteBuffer + curTlvNodeLen;
    TLV_ERR_CODE errCode = TlvBytesToLength(lengthPartAddr, bufLength - curTlvNodeLen,
        &length, &bytesNum);
    if (errCode != DMS_TLV_SUCCESS) {
        return DMS_TLV_ERR_LEN;
    }
    node->length = length;
    curTlvNodeLen += bytesNum;

    /* fill TLV's V(value) */
    node->value = byteBuffer + curTlvNodeLen;
    curTlvNodeLen += length;
    if (curTlvNodeLen > bufLength) {
        return DMS_TLV_ERR_LEN;
    } else {
        *actualHandledLen = curTlvNodeLen;
    }

    return DMS_TLV_SUCCESS;
}

static inline TLV_NODE_S* MallocTlvNode()
{
    TLV_NODE_S *node = malloc(sizeof(TLV_NODE_S));
    if (node == NULL) {
        HILOGE("[Out of memory]");
        return NULL;
    }
    /* won't fail */
    (void) memset_s(node, sizeof(TLV_NODE_S), 0x00, sizeof(TLV_NODE_S));

    return node;
}

static inline TLV_ERR_CODE CheckNodeNum(uint8_t handledNodeNum)
{
    /* check node num */
    if (!IsValidNodeNum(handledNodeNum)) {
        HILOGE("[Bad node num = %d]", handledNodeNum);
        return DMS_TLV_ERR_BAD_NODE_NUM;
    }

    return DMS_TLV_SUCCESS;
}

static inline TLV_ERR_CODE CheckNodeSequence(uint8_t handledNodeNum, const TLV_NODE_S *curNode)
{
    if (handledNodeNum != curNode->type) {
        HILOGE("[Bad node type sequence '%d' is expected but '%d' appears]",
            handledNodeNum, curNode->type);
        return DMS_TLV_ERR_OUT_OF_ORDER;
    }

    return DMS_TLV_SUCCESS;
}


static inline TLV_ERR_CODE PreCheck(uint16_t remainingLen, uint16_t curTlvNodeLen, uint8_t handledNodeNum)
{
    if (remainingLen < curTlvNodeLen) {
        HILOGE("[Bad length remainingLen = %d, curTlvNodeLen = %d]", remainingLen, curTlvNodeLen);
        return DMS_TLV_ERR_LEN;
    }

    if (handledNodeNum > MAX_VALID_NODES) {
        return DMS_TLV_ERR_BAD_NODE_NUM;
    }

    return DMS_TLV_SUCCESS;
}

static inline TLV_ERR_CODE MoveToNextTlvNode(TLV_NODE_S **curNode)
{
    TLV_NODE_S *next = MallocTlvNode();
    if (next == NULL) {
        return DMS_TLV_ERR_NO_MEM;
    }

    (*curNode)->next = next;
    *curNode = next;
    return DMS_TLV_SUCCESS;
}

TLV_ERR_CODE TlvBytesToNode(const uint8_t *byteBuffer, uint16_t bufLength, TLV_NODE_S **tlv)
{
    if ((tlv == NULL) || (byteBuffer == NULL)) {
        HILOGE("[Bad parameter]");
        return DMS_TLV_ERR_PARAM;
    }
    /* bufLength is longer than TLV_TYPE_LEN + 1(means length should be at least 1 byte) */
    if (bufLength <= (TLV_TYPE_LEN + 1)) {
        HILOGE("[Bad Length = %d]", bufLength);
        return DMS_TLV_ERR_LEN;
    }

    TLV_NODE_S *head = MallocTlvNode();
    if (head == NULL) {
        return DMS_TLV_ERR_NO_MEM;
    }
    TLV_NODE_S *node = head;

    /* translate bytes to tlv node until the end of buffer */
    uint16_t remainingLen = bufLength;
    uint8_t handledNodeNum = 0;
    const uint8_t *nodeStartAddr = byteBuffer;
    TLV_ERR_CODE errCode = DMS_TLV_SUCCESS;
    while (true) {
        uint16_t curTlvNodeLen = 0;
        errCode = TlvFillNode(nodeStartAddr, remainingLen, node, &curTlvNodeLen);
        BREAK_IF_FAILURE(errCode);

        /* check whether there is need to continue processing the remaining nodes */
        handledNodeNum++;
        errCode = PreCheck(remainingLen, curTlvNodeLen, handledNodeNum);
        BREAK_IF_FAILURE(errCode);

        /* check node type sequence: the type of node must appear in strictly increasing order */
        errCode = CheckNodeSequence(handledNodeNum, node);
        BREAK_IF_FAILURE(errCode);

        remainingLen -= curTlvNodeLen;
        if (remainingLen == 0) {
            /* check node num if all bytes in buffer are processed done */
            errCode = CheckNodeNum(handledNodeNum);
            break;
        }

        /* if all is ok, then move to the T part of the next tlv node */
        nodeStartAddr += curTlvNodeLen;
        errCode = MoveToNextTlvNode(&node);
        BREAK_IF_FAILURE(errCode);
    }

    /* NOTICE: free nodes in caller */
    *tlv = head;

    return errCode;
}