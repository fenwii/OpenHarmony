/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef COAP_H
#define COAP_H

#include "coap_def.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    enum COAP_ProtocolTypeEnum protocol;
    enum COAP_MsgTypeEnum type;
    unsigned char code;
    unsigned short msgId;
    COAP_Option *options;
    unsigned char optionsNum;
} COAP_PacketParam;

#define COAP_VERSION 1
#define DEFAULT_TOK_LEN 0
#define MAX_TOK_LEN 8
#define HEADER_LEN 4

typedef struct {
    char *readWriteBuf;
    unsigned int len;
    unsigned int size;
} COAP_ReadWriteBuffer;

enum ErrorTypeEnum {
    DISCOVERY_ERR_SUCCESS                      = 0,
    DISCOVERY_ERR_HEADER_INVALID_SHORT         = 1,
    DISCOVERY_ERR_VER_INVALID                  = 2,
    DISCOVERY_ERR_TOKEN_INVALID_SHORT          = 3,
    DISCOVERY_ERR_OPT_INVALID_SHORT_FOR_HEADER = 4,
    DISCOVERY_ERR_OPT_INVALID_SHORT            = 5,
    DISCOVERY_ERR_OPT_OVERRUNS_PKT             = 6,
    DISCOVERY_ERR_OPT_INVALID_BIG              = 7,
    DISCOVERY_ERR_OPT_INVALID_LEN              = 8,
    DISCOVERY_ERR_BUF_INVALID_SMALL            = 9,
    DISCOVERY_ERR_NOT_SUPPORTED                = 10,
    DISCOVERY_ERR_OPT_INVALID_DELTA            = 11,
    DISCOVERY_ERR_PKT_EXCEED_MAX_PDU           = 12,
    DISCOVERY_ERR_TCP_TYPE_INVALID             = 13,
    DISCOVERY_ERR_UNKNOWN_MSG_TYPE             = 14,
    DISCOVERY_ERR_INVALID_PKT                  = 15,
    DISCOVERY_ERR_INVALID_TOKEN_LEN            = 16,
    DISCOVERY_ERR_INVALID_ARGUMENT             = 17,
    DISCOVERY_ERR_TRANSPORT_NOT_UDP_OR_TCP     = 18,
    DISCOVERY_ERR_INVALID_EMPTY_MSG            = 19,
    DISCOVERY_ERR_SERVER_ERR                   = 20,
    DISCOVERY_ERR_BAD_REQ                      = 21,
    DISCOVERY_ERR_UNKNOWN_METHOD               = 22,
    DISCOVERY_ERR_BLOCK_NO_PAYLOAD             = 23
};

int COAP_SoftBusDecode(COAP_Packet *pkt, const unsigned char *buf, unsigned int bufLen);
int COAP_SoftBusEncode(COAP_Packet *pkt, const COAP_PacketParam *param, const COAP_Buffer *token,
    const COAP_Buffer *payload, COAP_ReadWriteBuffer *buf);
void COAP_SoftBusInitMsgId(void);
int BuildSendPkt(const COAP_Packet *pkt, const char* remoteIp,
    const char *pktPayload, COAP_ReadWriteBuffer *sndPktBuff);
#ifdef __cplusplus
}
#endif

#endif /* HILINK_COAP_H */
