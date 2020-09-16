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

#ifndef LITE_AUTH_INTERFACE_H
#define LITE_AUTH_INTERFACE_H

#include "auth_conn.h"

#define AUTH_PIN_DEFAULT "softbus"
#define AUTH_DEFAULT_ID "default"
#define AUTH_DEFAULT_ID_LEN 7
#define AUTH_SESSION_KEY_LEN 16
#define AUTH_SESSION_KEY_MAX_NUM 2
#define AUTH_SESSION_MAX_NUM 2

typedef struct SessionKey {
    char key[AUTH_SESSION_KEY_LEN];
    int index;
    int fd;
} SessionKey;

typedef struct SessionKeyNode {
    List head;
    SessionKey sKey;
} SessionKeyNode;

typedef struct AuthSession {
    int isUsed;
    long long seqId;
    uint32_t sessionId;
    AuthConn *conn;
} AuthSession;

void AuthInterfaceOnDataReceived(const AuthConn *conn, int module, long long seqId, const char *data, int dataLen);
SessionKey *AuthGetSessionKeyByIndex(int index);
SessionKey *AuthGetNewSessionKey(void);
void ClearSessionKeyByFd(int fd);

#endif
