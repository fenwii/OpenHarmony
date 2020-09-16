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

#ifndef LITE_WIFI_AUTH_MANAGER_H
#define LITE_WIFI_AUTH_MANAGER_H

#include "cJSON.h"

#include "auth_conn.h"
#include "msg_get_deviceid.h"

#define BUS_UNKNOWN 0
#define BUS_V1 1
#define BUS_V2 2

#define FLAG_REPLY 1
#define AUTH_UNKNOWN 0
#define AUTH_INIT 1

typedef struct {
    int module;
    int flags;
    long long seq;
    int dataLen;
} Packet;

void AuthMngInit(int authPort, int SessionPort);
void AuthMngDeInit(void);
void ProcessConnectEvent(int fd, const char *ip);
void ProcessDataEvent(int fd);
void CloseConn(const AuthConn *conn);
AuthConn* GetOnLineAuthConnByIp(const char *ip);

#endif
