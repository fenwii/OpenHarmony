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

#ifndef HILINK_COAP_DEF_H
#define HILINK_COAP_DEF_H
#ifdef __cplusplus
extern "C" {
#endif

#define COAP_MAX_OPTION 16

enum COAP_ProtocolTypeEnum {
    COAP_UDP = 0,
    COAP_TCP
};

enum COAP_MethodTypeEnum {
    COAP_METHOD_GET = 1,
    COAP_METHOD_POST = 2,
    COAP_METHOD_PUT = 3,
    COAP_METHOD_DELETE = 4
};

enum COAP_MsgTypeEnum {
    COAP_TYPE_CON = 0,
    COAP_TYPE_NONCON = 1,
    COAP_TYPE_ACK = 2,
    COAP_TYPE_RESET = 3
};

#define DISCOVERY_MSG_URI_HOST 3
#define DISCOVERY_MSG_URI_PATH 11

typedef struct {
    unsigned int ver : 2;
    unsigned int type : 2;
    unsigned int tokenLen : 4;
    unsigned int code : 8;
    union {
        unsigned short msgLen;
        unsigned short msgId;
    } varSection;
} COAP_Header;

typedef struct {
    const unsigned char *buffer;
    unsigned int len;
} COAP_Buffer;

typedef struct {
    unsigned short num;
    const unsigned char *optionBuf;
    unsigned int len;
} COAP_Option;

typedef struct {
    enum COAP_ProtocolTypeEnum protocol;
    unsigned int len;
    COAP_Header header;
    COAP_Buffer token;
    unsigned char optionsNum;
    COAP_Option options[COAP_MAX_OPTION];
    COAP_Buffer payload;
} COAP_Packet;

typedef COAP_Packet CoapPacket;
#ifdef __cplusplus
}
#endif

#endif /* HILINK_COAP_DEF_H */