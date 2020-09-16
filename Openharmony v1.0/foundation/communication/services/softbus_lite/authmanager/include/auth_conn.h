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

#ifndef LITE_AUTH_CONN_H
#define LITE_AUTH_CONN_H

#include "cJSON.h"
#include "common_info_manager.h"
#include "comm_defs.h"


#define MESSAGE_INDEX_LEN 4
#define MESSAGE_GCM_NONCE_LEN 12
#define MESSAGE_GCM_MAC_LEN 16
#define MESSAGE_ENCRYPT_OVER_HEAD_LEN (MESSAGE_INDEX_LEN + MESSAGE_GCM_NONCE_LEN + MESSAGE_GCM_MAC_LEN)

#define DEFAULT_BUF_SIZE 1536
#define PACKET_HEAD_SIZE 24
#define PACKET_DATA_SIZE (DEFAULT_BUF_SIZE - PACKET_HEAD_SIZE)
#define PKG_HEADER_IDENTIFIER 0xBABEFACE

#define ONLINE_UNKNOWN 0
#define ONLINE_YES 1
#define ONLINE_NO (-1)

#define MODULE_NONE 0
#define MODULE_TRUST_ENGINE 1
#define MODULE_HICHAIN 2
#define MODULE_AUTH_SDK 3
#define MODULE_HICHAIN_SYNC 4
#define MODULE_CONNECTION 5
#define MODULE_SESSION 6
#define MODULE_SMART_COMM 7
#define MODULE_AUTH_CHANNEL 8
#define MODULE_AUTH_MSG 9

#define FLAG_REPLY 1
#define AUTH_UNKNOWN 0
#define AUTH_INIT 1

typedef struct DataBuffer {
    char *buf;
    int size;
    int used;
} DataBuffer;

typedef struct AuthConn {
    int fd;
    char authId[MAX_AUTH_ID_LEN];
    char deviceId[MAX_DEV_ID_LEN];
    char deviceIp[MAX_DEV_IP_LEN];
    int busVersion;
    int authPort;
    int sessionPort;
    int authState;
    int onlineState;
    DataBuffer db;
} AuthConn;

typedef struct AuthConnNode {
    List head;
    AuthConn *aconn;
} AuthConnNode;

typedef struct ConnInfo {
    int maxVersion;
    int minVersion;
    char deviceName[MAX_DEV_NAME_LEN];
    char deviceType[MAX_DEV_TYPE_LEN];
} ConnInfo;

int AuthConnRecv(int fd, char *buf, int offset, int count, int timeout);
int AuthConnPostBytes(int fd, int module, int flags, long long seq, const char *data);
int AuthConnPostMessage(int fd, int module, int flags, long long seqNum, const cJSON *msg);
bool ModuleUseCipherText(int module);
unsigned char* AuthConnPackBytes(int module, int flags, long long seqNum, const char *str, int *bufLen);


#endif
