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
#include "auth_interface.h"

#include "hichain.h"
#include "securec.h"

#include "auth_conn.h"
#include "bus_manager.h"
#include "os_adapter.h"
#include "wifi_auth_manager.h"

static uint32_t g_authSessionId = 1;
static List *g_sessionKeyList = NULL;
static AuthSession *g_authSessionMap = NULL;
static hc_handle g_hcHandle = NULL;

static int AuthSessionMapInit(void)
{
    if (g_authSessionMap != NULL) {
        return 0;
    }

    int len = sizeof(AuthSession) * AUTH_SESSION_MAX_NUM;
    g_authSessionMap = (AuthSession *)malloc(len);
    if (g_authSessionMap == NULL) {
        return -1;
    }
    (void)memset_s(g_authSessionMap, len, 0, len);
    return 0;
}

static AuthSession *AuthGetAuthSessionBySeqId(long long seqId)
{
    if (g_authSessionMap == NULL) {
        return NULL;
    }

    for (int i = 0; i < AUTH_SESSION_MAX_NUM; i++) {
        if (g_authSessionMap[i].isUsed == 0) {
            continue;
        }

        if (g_authSessionMap[i].seqId == seqId) {
            return &g_authSessionMap[i];
        }
    }

    return NULL;
}

static AuthSession *AuthGetAuthSessionBySessionId(uint32_t sessionId)
{
    if (g_authSessionMap == NULL) {
        return NULL;
    }

    for (int i = 0; i < AUTH_SESSION_MAX_NUM; i++) {
        if (g_authSessionMap[i].isUsed == 0) {
            continue;
        }

        if (g_authSessionMap[i].sessionId == sessionId) {
            return &g_authSessionMap[i];
        }
    }

    return NULL;
}

static void AuthDelAuthSessionBySessionId(uint32_t sessionId)
{
    if (g_authSessionMap == NULL) {
        return;
    }

    for (int i = 0; i < AUTH_SESSION_MAX_NUM; i++) {
        if (g_authSessionMap[i].sessionId == sessionId) {
            (void)memset_s(&g_authSessionMap[i], sizeof(AuthSession), 0, sizeof(AuthSession));
            g_authSessionMap[i].isUsed = 0;
            break;
        }
    }

    return;
}

static AuthSession *AuthGetNewAuthSession(const AuthConn *conn, long long seqId, uint32_t sessionId)
{
    if (conn == NULL || g_authSessionMap == NULL) {
        return NULL;
    }

    for (int i = 0; i < AUTH_SESSION_MAX_NUM; i++) {
        if (g_authSessionMap[i].isUsed == 0) {
            g_authSessionMap[i].isUsed = 1;
            g_authSessionMap[i].seqId = seqId;
            g_authSessionMap[i].sessionId = sessionId;
            g_authSessionMap[i].conn = (AuthConn *)conn;

            return &g_authSessionMap[i];
        }
    }

    return NULL;
}


static int AuthSendData(uint32_t sessionId, int module, const char *data)
{
    AuthSession *auth = AuthGetAuthSessionBySessionId(sessionId);
    if (auth == NULL || auth->conn == NULL) {
        return -1;
    }

    int ret = AuthConnPostBytes(auth->conn->fd, module, 0, auth->seqId, data);
    if (ret != 0) {
        return -1;
    }

    SOFTBUS_PRINT("[AUTH] AuthSendData ok\n");
    return 0;
}

static void AuthOnTransmit(const struct session_identity *identity, const void *data, uint32_t length)
{
    SOFTBUS_PRINT("[AUTH] AuthOnTransmit begin\n");
    if (identity == NULL || data == NULL || length == 0) {
        return;
    }

    int ret = AuthSendData(identity->session_id, MODULE_AUTH_SDK, data);
    if (ret != 0) {
        SOFTBUS_PRINT("[AUTH] AuthOnTransmit send data fail\n");
        return;
    }
}

static void AuthGetProtocolParams(const struct session_identity *identity, int32_t operationCode,
    struct hc_pin *hcPin, struct operation_parameter *para)
{
    (void)operationCode;
    SOFTBUS_PRINT("[AUTH] AuthGetProtocolParams operationCode = %d\n", operationCode);
    if (identity == NULL || hcPin == NULL || para == NULL) {
        return;
    }

    hcPin->length = strlen(AUTH_PIN_DEFAULT);
    if (memcpy_s(hcPin->pin, sizeof(hcPin->pin), AUTH_PIN_DEFAULT, sizeof(AUTH_PIN_DEFAULT)) != EOK) {
        return;
    }

    para->key_length = AUTH_SESSION_KEY_LEN;
    AuthSession *authSes = AuthGetAuthSessionBySessionId(identity->session_id);
    if (authSes == NULL || authSes->conn == NULL) {
        SOFTBUS_PRINT("[AUTH] AuthGetProtocolParams get session fail\n");
        return;
    }

    para->peer_auth_id.length = strlen(authSes->conn->authId);
    int ret = memcpy_s(para->peer_auth_id.auth_id, sizeof(para->peer_auth_id.auth_id),
                       authSes->conn->authId, strlen(authSes->conn->authId));
    if (ret != EOK) {
        return;
    }

    DeviceInfo *info = BusGetLocalDeviceInfo();
    if (info == NULL) {
        return;
    }
    para->self_auth_id.length = strlen(info->deviceId);
    ret = memcpy_s(para->self_auth_id.auth_id, sizeof(para->self_auth_id.auth_id),
                   info->deviceId, strlen(info->deviceId));
    if (ret != EOK) {
        return;
    }

    SOFTBUS_PRINT("[AUTH] AuthGetProtocolParams ok\n");
    return;
}

void ClearSessionKeyByFd(int fd)
{
    if (g_sessionKeyList == NULL) {
        return;
    }

    bool flag = false;
    List *pos = NULL;
    List *tmp = NULL;
    SessionKeyNode *node = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, g_sessionKeyList) {
        node = (SessionKeyNode *)pos;
        if (node->sKey.fd == fd) {
            flag = true;
            break;
        }
    }

    if (flag) {
        ListRemoveNode(&(node->head));
        free(node);
        node = NULL;
    }
    SOFTBUS_PRINT("[AUTH] ClearSessionKeyByFd(%d) ok\n", fd);
    return;
}

static void ClearSessionKeyBySeq(long long seq)
{
    if (g_sessionKeyList == NULL) {
        return;
    }

    bool flag = false;
    List *pos = NULL;
    List *tmp = NULL;
    SessionKeyNode *node = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, g_sessionKeyList) {
        node = (SessionKeyNode *)pos;
        if (node->sKey.index == (int)seq) {
            flag = true;
            break;
        }
    }

    if (flag) {
        ListRemoveNode(&(node->head));
        free(node);
        node = NULL;
    }

    return;
}

static int AddNewSessionNode(int fd, int index, const struct hc_session_key *session)
{
    SessionKeyNode *node = calloc(1, sizeof(SessionKeyNode));
    if (node == NULL) {
        return -1;
    }

    node->sKey.index = index;
    node->sKey.fd = fd;
    int ret = memcpy_s(node->sKey.key, sizeof(node->sKey.key), session->session_key, session->length);
    if (ret != EOK) {
        free(node);
        node = NULL;
        return -1;
    }

    ListInsertTail(g_sessionKeyList, &node->head);
    return 0;
}

static int ReplaceOldSessionNode(int fd, int index, const struct hc_session_key *session)
{
    SessionKeyNode *node = (SessionKeyNode *)ListPopFront(g_sessionKeyList);
    if (node == NULL) {
        return -1;
    }

    (void)memset_s(node, sizeof(SessionKeyNode), 0, sizeof(SessionKeyNode));
    node->sKey.index = index;
    node->sKey.fd = fd;
    int ret = memcpy_s(node->sKey.key, sizeof(node->sKey.key), session->session_key, session->length);
    if (ret != EOK) {
        free(node);
        node = NULL;
        return -1;
    }

    ListInsertTail(g_sessionKeyList, &node->head);
    return 0;
}

static int AddSessionKey(const struct session_identity *identity, const struct hc_session_key *session)
{
    AuthSession *auth = AuthGetAuthSessionBySessionId(identity->session_id);
    if (auth == NULL || auth->conn == NULL) {
        return -1;
    }

    if (g_sessionKeyList == NULL) {
        g_sessionKeyList = calloc(1, sizeof(List));
        if (g_sessionKeyList == NULL) {
            return -1;
        }
        ListInitHead(g_sessionKeyList);
    }

    int ret;
    int index = (int)auth->seqId;
    int num = ListLength(g_sessionKeyList);
    if (num >= AUTH_SESSION_KEY_MAX_NUM) {
        ret = ReplaceOldSessionNode(auth->conn->fd, index, session);
    } else {
        ret = AddNewSessionNode(auth->conn->fd, index, session);
    }

    SOFTBUS_PRINT("[AUTH] AddSessionKey ret = %d\n", ret);
    return ret;
}

SessionKey *AuthGetSessionKeyByIndex(int index)
{
    if (g_sessionKeyList == NULL) {
        return NULL;
    }

    List *pos = NULL;
    List *tmp = NULL;
    SessionKeyNode *node = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, g_sessionKeyList) {
        node = (SessionKeyNode *)pos;
        if (node->sKey.index == index) {
            return &node->sKey;
        }
    }

    return NULL;
}

SessionKey *AuthGetNewSessionKey(void)
{
    if (g_sessionKeyList == NULL) {
        return NULL;
    }

    List *pos = NULL;
    List *tmp = NULL;
    SessionKeyNode *node = NULL;
    SessionKey *sKey = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, g_sessionKeyList) {
        node = (SessionKeyNode *)pos;
        sKey = &node->sKey;
    }

    return sKey;
}

static void AuthSetSessionKey(const struct session_identity *identity, const struct hc_session_key *session)
{
    SOFTBUS_PRINT("[AUTH] AuthSetSessionKey\n");
    if (identity == NULL || session == NULL) {
        return;
    }

    if (AddSessionKey(identity, session) != 0) {
        SOFTBUS_PRINT("[AUTH] AuthSetSessionKey add key fail\n");
        return;
    }
}

static void AuthFail(uint32_t sessionId)
{
    AuthSession *auth = AuthGetAuthSessionBySessionId(sessionId);
    if (auth == NULL) {
        return;
    }

    ClearSessionKeyBySeq(auth->seqId);
}

static void DestroyHiChain(void)
{
    SOFTBUS_PRINT("[AUTH] DestroyHiChain\n");
    if (g_hcHandle != NULL) {
        destroy(&g_hcHandle);
        g_hcHandle = NULL;
    }
}

static void AuthSetServiceResult(const struct session_identity *identity, int32_t result)
{
    SOFTBUS_PRINT("[AUTH] AuthSetServiceResult result = %d\n", result);
    if (identity == NULL) {
        return;
    }

    if (result == END_FAILED) {
        AuthFail(identity->session_id);
    }

    if (result == END_SUCCESS || result == END_FAILED) {
        AuthDelAuthSessionBySessionId(identity->session_id);
        DestroyHiChain();
    }
}

/* Callback interface, not used now */
static int32_t AuthConfirmReceiveRequest(const struct session_identity *identity, int32_t operationCode)
{
    (void)identity;
    (void)operationCode;
    return 0;
}

static int AuthInitHiChain(uint32_t sessionId)
{
    SOFTBUS_PRINT("[AUTH] AuthInitHiChain begin\n");
    struct session_identity serverIdentity = {
        sessionId,
        {AUTH_DEFAULT_ID_LEN, AUTH_DEFAULT_ID},
        {AUTH_DEFAULT_ID_LEN, AUTH_DEFAULT_ID},
        0
    };

    struct hc_call_back hiChainCallback = {
        AuthOnTransmit,
        AuthGetProtocolParams,
        AuthSetSessionKey,
        AuthSetServiceResult,
        AuthConfirmReceiveRequest
    };

    g_hcHandle = get_instance(&serverIdentity, HC_ACCESSORY, &hiChainCallback);
    if (g_hcHandle == NULL) {
        return -1;
    }

    SOFTBUS_PRINT("[AUTH] AuthInitHiChain ok\n");
    return 0;
}

static void AuthProcessReceivedData(uint32_t sessionId, const char *data, int dataLen)
{
    if (g_hcHandle == NULL) {
        if (AuthInitHiChain(sessionId) != 0) {
            AuthDelAuthSessionBySessionId(sessionId);
            return;
        }
    }

    struct uint8_buff request = {(uint8_t *)data, dataLen, dataLen};
    if (receive_data(g_hcHandle, &request) != HC_OK) {
        return;
    }
}

void AuthInterfaceOnDataReceived(const AuthConn *conn, int module, long long seqId, const char *data, int dataLen)
{
    SOFTBUS_PRINT("[AUTH] AuthInterfaceOnDataReceived begin\n");
    if (conn == NULL || data == NULL || dataLen > PACKET_DATA_SIZE) {
        return;
    }
    if (AuthSessionMapInit() != 0) {
        return;
    }

    AuthSession *auth = AuthGetAuthSessionBySeqId(seqId);
    if (auth == NULL) {
        auth = AuthGetNewAuthSession(conn, seqId, g_authSessionId);
        if (auth == NULL) {
            return;
        }
        ++g_authSessionId;
    }

    switch (module) {
        case MODULE_AUTH_SDK:
            AuthProcessReceivedData(auth->sessionId, data, dataLen);
            break;
        default:
            break;
    }

    return;
}

