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

#ifndef OHOS_DISTRIBUTEDSCHEDULE_TLVCOMMON_H
#define OHOS_DISTRIBUTEDSCHEDULE_TLVCOMMON_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define TLV_ONE_BYTE_LENGTH  127
#define TLV_MAX_LENGTH_BYTES 2
#define TLV_TYPE_LEN         1

typedef struct TLV_NODE_S {
    uint8_t type;
    uint16_t length;
    const uint8_t *value;
    struct TLV_NODE_S *next;
} TLV_NODE_S;

typedef enum {
    DMS_TLV_SUCCESS = 0,
    DMS_TLV_ERR_NO_MEM = 1,
    DMS_TLV_ERR_PARAM = 2,
    DMS_TLV_ERR_LEN = 3,
    DMS_TLV_ERR_OUT_OF_ORDER = 4,
    DMS_TLV_ERR_BAD_NODE_NUM = 5,
    DMS_TLV_ERR_UNKNOWN_TYPE = 6,
    DMS_TLV_ERR_BAD_SOURCE = 7,
} TLV_ERR_CODE;

/**
* @brief Translates bytes array to tlv struct, remember free nodes in caller
* @param byteBuffer bytes
* @param bufLength the length of bytes
* @param tlv tlv struct head pointer
* @return TLV_ERR_CODE
*/
TLV_ERR_CODE TlvBytesToNode(const uint8_t *byteBuffer, uint16_t bufLength, TLV_NODE_S **tlv);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* OHOS_DISTRIBUTEDSCHEDULE_TLVCOMMON_H */