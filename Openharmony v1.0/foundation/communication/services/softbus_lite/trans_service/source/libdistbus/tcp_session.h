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

#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include "comm_defs.h"
#include "common_info_manager.h"

#define NAME_LENGTH         64
#define SESSION_KEY_LENGTH  32

typedef struct {
    List head;
    int seqNum;
} SessionSeqNumNode;

typedef struct {
    char sessionName[NAME_LENGTH];
    char deviceId[MAX_DEV_ID_LEN];
    char groupId[NAME_LENGTH];
    char sessionKey[SESSION_KEY_LENGTH];
    long seqNum;
    int fd;
    int busVersion;
    int routeType;
    bool isAccepted;
    uid_t uid;
    pid_t pid;
    List *seqNumList;
} TcpSession;

TcpSession* CreateTcpSession(void);

#endif // TCP_SESSION_H