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

#include "wifi_auth_manager.h"

#include <stdlib.h>

#include "aes_gcm.h"
#include "auth_conn.h"
#include "auth_conn_manager.h"
#include "auth_interface.h"
#include "bus_manager.h"
#include "message.h"
#include "msg_get_deviceid.h"
#include "os_adapter.h"
#include "securec.h"

#define DEFAULT_INT_LEN 4
#define DEFAULT_LONG_LEN 8
#define AUTH_CONN_MAX_NUM 32

static int g_authPort = -1;
static int g_sessionPort = -1;
static List *g_fdMap = NULL;

#ifdef SOFTBUS_DEBUG
char g_peerAuthId[MAX_AUTH_ID_LEN] = {0};
#endif

static int AddAuthConnToList(AuthConn *aconn)
{
    if (aconn == NULL) {
        return -1;
    }
    if (g_fdMap == NULL) {
        g_fdMap = calloc(1, sizeof(List));
        if (g_fdMap == NULL) {
            return -1;
        }
        ListInitHead(g_fdMap);
    }

    if (ListLength(g_fdMap) >= AUTH_CONN_MAX_NUM) {
        return -1;
    }
    AuthConnNode *node = calloc(1, sizeof(AuthConnNode));
    if (node == NULL) {
        return -1;
    }

    node->aconn = aconn;
    ListInsertTail(g_fdMap, &node->head);

    SOFTBUS_PRINT("[AUTH] AddAuthConnToList add new node(%d) ok\n", aconn->fd);
    return 0;
}

static AuthConn* FindAuthConnByFd(int fd)
{
    if (g_fdMap == NULL) {
        return NULL;
    }

    AuthConnNode *node = NULL;
    List *pos = NULL;
    List *tmp = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, g_fdMap) {
        node = (AuthConnNode*)pos;
        if (node->aconn == NULL) {
            continue;
        }
        if (node->aconn->fd == fd) {
            return node->aconn;
        }
    }

    return NULL;
}

AuthConn* GetOnLineAuthConnByIp(const char *ip)
{
    if (ip == NULL || g_fdMap == NULL) {
        return NULL;
    }

    AuthConnNode *node = NULL;
    List *pos = NULL;
    List *tmp = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, g_fdMap) {
        node = (AuthConnNode*)pos;
        if (node->aconn == NULL) {
            continue;
        }
        if (strcmp(node->aconn->deviceIp, ip) == 0 &&
            node->aconn->onlineState == ONLINE_YES) {
            return node->aconn;
        }
    }

    return NULL;
}


static void DelAuthConnNode(int fd)
{
    if (g_fdMap == NULL) {
        return;
    }

    AuthConnNode *node = NULL;
    List *pos = NULL;
    List *tmp = NULL;
    bool flag = false;

    LIST_FOR_EACH_SAFE(pos, tmp, g_fdMap) {
        node = (AuthConnNode*)pos;
        if (node->aconn == NULL) {
            continue;
        }
        if (node->aconn->fd == fd) {
            flag = true;
            break;
        }
    }

    if (flag) {
        SOFTBUS_PRINT("[AUTH] DelAuthConnNode fd = %d\n", node->aconn->fd);
        char *buf = node->aconn->db.buf;
        if (buf != NULL) {
            free(buf);
            buf = NULL;
            node->aconn->db.buf = NULL;
        }

        free(node->aconn);
        node->aconn = NULL;

        ListRemoveNode(&(node->head));
        free(node);
        node = NULL;
    }

    return;
}

void AuthMngInit(int authPort, int sessionPort)
{
    g_authPort = authPort;
    g_sessionPort = sessionPort;
}

void AuthMngDeInit(void)
{
    g_authPort = -1;
    g_sessionPort = -1;
}

void AuthConnClose(const AuthConn *conn)
{
    if (conn == NULL) {
        return;
    }
    SOFTBUS_PRINT("[AUTH] AuthConnClose fd = %d\n", conn->fd);

    CloseAuthSessionFd(conn->fd);
    return;
}

void CloseConn(const AuthConn *conn)
{
    if (conn == NULL) {
        return;
    }

    ClearSessionKeyByFd(conn->fd);
    AuthConnClose(conn);
    DelAuthConnNode(conn->fd);
    SOFTBUS_PRINT("[AUTH] CloseConn ok\n");
}

void ProcessConnectEvent(int fd, const char *ip)
{
    SOFTBUS_PRINT("[AUTH] ProcessConnectEvent fd = %d\n", fd);
    if (fd < 0 || ip == NULL) {
        return;
    }

    AuthConn *aconn = FindAuthConnByFd(fd);
    if (aconn != NULL) {
        CloseConn(aconn);
        return;
    }

    aconn = calloc(1, sizeof(AuthConn));
    if (aconn == NULL) {
        return;
    }

    int ret = strcpy_s(aconn->deviceIp, sizeof(aconn->deviceIp), ip);
    if (ret != EOK) {
        free(aconn);
        aconn = NULL;
        return;
    }
    aconn->fd = fd;

    ret = AddAuthConnToList(aconn);
    if (ret != 0) {
        AuthConnClose(aconn);
        free(aconn);
        aconn = NULL;
        return;
    }

    SOFTBUS_PRINT("[AUTH] ProcessConnectEvent ok\n");
}

void OnVerifyIp(AuthConn *conn, long long seq, const cJSON *request)
{
    if (conn == NULL || request == NULL) {
        return;
    }

    DeviceInfo *localDevInfo = BusGetLocalDeviceInfo();
    if (localDevInfo == NULL) {
        return;
    }

    ConnInfo connInfo = {0};
    connInfo.maxVersion = BUS_V2;
    connInfo.minVersion = BUS_V2;

    int ret = MsgVerifyIpUnPack(request, &connInfo, conn);
    if (ret != 0) {
        return;
    }

    cJSON *reply = MsgVerifyIpPack(&connInfo, localDevInfo, g_authPort, g_sessionPort);
    if (reply == NULL) {
        return;
    }

    ret = AuthConnPostMessage(conn->fd, MODULE_CONNECTION, FLAG_REPLY, seq, reply);
    cJSON_Delete(reply);
    reply = NULL;
    if (ret != 0) {
        return;
    }

    conn->onlineState = ONLINE_YES;

    SOFTBUS_PRINT("[AUTH] OnVerifyIp ok\n");
}

void OnVerifyDeviceId(const AuthConn *conn, long long seq, const cJSON *request)
{
    if (conn == NULL || request == NULL) {
        return;
    }

    char *deviceId = GetJsonString(request, "DEVICE_ID");
    if (deviceId == NULL) {
        return;
    }

    DeviceInfo *info = BusGetLocalDeviceInfo();
    if (info == NULL) {
        return;
    }

    cJSON *reply = MsgVerifyDeviceIdPack(info);
    if (reply == NULL) {
        return;
    }

    (void)AuthConnPostMessage(conn->fd, MODULE_CONNECTION, FLAG_REPLY, seq, reply);
    cJSON_Delete(reply);
    reply = NULL;

    SOFTBUS_PRINT("[AUTH] OnVerifyDeviceId ok\n");
    return;
}

void OnMessageReceived(AuthConn *conn, long long seq, const cJSON *msg)
{
    if (conn == NULL || msg == NULL) {
        return;
    }

    SOFTBUS_PRINT("[AUTH] OnMessageReceived begin\n");
    cJSON *codeJson = cJSON_GetObjectItem(msg, "CODE");
    if ((codeJson == NULL) || (!cJSON_IsNumber(codeJson))) {
        return;
    }

    int code = codeJson->valueint;
    switch (code) {
        case CODE_VERIFY_IP: {
            OnVerifyIp(conn, seq, msg);
            break;
        }
        case CODE_VERIFY_DEVID: {
            OnVerifyDeviceId(conn, seq, msg);
            break;
        }
        default:
            break;
    }
}

void OnMsgOpenChannelReq(AuthConn *conn, long long seq, const cJSON *msg)
{
    int ret = MsgGetDeviceIdUnPack(msg, conn);
    if (ret != 0) {
        CloseConn(conn);
        return;
    }

#ifdef SOFTBUS_DEBUG
    if (strcpy_s(g_peerAuthId, MAX_AUTH_ID_LEN, conn->authId) != EOK) {
        SOFTBUS_PRINT("[AUTH] OnMsgOpenChannelReq save peer auth id fail\n");
    }
#endif

    DeviceInfo *localDevInfo = BusGetLocalDeviceInfo();
    if (localDevInfo == NULL) {
        CloseConn(conn);
        return;
    }

    cJSON *reply = MsgGetDeviceIdPack(localDevInfo);
    if (reply == NULL) {
        CloseConn(conn);
        SOFTBUS_PRINT("[AUTH] OnMsgOpenChannelReq pack reply fail\n");
        return;
    }

    ret = AuthConnPostMessage(conn->fd, MODULE_TRUST_ENGINE, FLAG_REPLY, seq, reply);
    if (ret != 0) {
        SOFTBUS_PRINT("[AUTH] OnMsgOpenChannelReq post msg fail\n");
        CloseConn(conn);
    }
    cJSON_Delete(reply);

    SOFTBUS_PRINT("[AUTH] OnMsgOpenChannelReq ok\n");
}

static void OnModuleMessageReceived(AuthConn *conn, int module, int flags, long long seq, const cJSON *msg)
{
    switch (module) {
        case MODULE_TRUST_ENGINE: {
            if (((unsigned int)flags & FLAG_REPLY) == 0) {
                OnMsgOpenChannelReq(conn, seq, msg);
            }
            break;
        }
        case MODULE_CONNECTION: {
            OnMessageReceived(conn, seq, msg);
            break;
        }
        default: {
            break;
        }
    }

    return;
}

static int GetKeyIndex(const char *in, unsigned int inOffset, unsigned int indexLen)
{
    int val = 0;
    if (memcpy_s(&val, indexLen, in + inOffset, indexLen) != EOK) {
        return -1;
    }
    return val;
}

static cJSON *DecryptMessage(int module, const char *data, int dataLen)
{
    if (data == NULL) {
        return NULL;
    }
    if (!ModuleUseCipherText(module)) {
        return cJSON_Parse(data);
    }

    if (dataLen < MESSAGE_ENCRYPT_OVER_HEAD_LEN) {
        return NULL;
    }

    int index = GetKeyIndex(data, 0, MESSAGE_INDEX_LEN);
    SessionKey *sKey = AuthGetSessionKeyByIndex(index);
    if (sKey == NULL) {
        SOFTBUS_PRINT("[AUTH] DecryptMessage get session key fail\n");
        return NULL;
    }

    unsigned int len = dataLen - MESSAGE_ENCRYPT_OVER_HEAD_LEN + 1;
    unsigned char *output = malloc(len);
    if (output == NULL) {
        return NULL;
    }
    if (memset_s((void *)output, len, 0, len) != EOK) {
        free(output);
        output = NULL;
        return NULL;
    }

    AesGcmCipherKey cipherKey = {0};
    cipherKey.keybits = GCM_KEY_BITS_LEN_128;
    int ret = memcpy_s(cipherKey.key, SESSION_KEY_LENGTH, sKey->key, AUTH_SESSION_KEY_LEN);
    ret += memcpy_s(cipherKey.iv, IV_LEN, data + MESSAGE_INDEX_LEN, IV_LEN);
    if (ret != 0) {
        free(output);
        output = NULL;
        return NULL;
    }

    ret = DecryptTransData(&cipherKey,
        (unsigned char*)&data[MESSAGE_INDEX_LEN], dataLen - MESSAGE_INDEX_LEN, output, len);
    if (ret <= 0) {
        SOFTBUS_PRINT("[AUTH] DecryptMessage DecryptTransData fail\n");
        free(output);
        output = NULL;
        return NULL;
    }

    cJSON *msg = cJSON_Parse((char*)output);
    free(output);
    output = NULL;

    return msg;
}

static void OnDataReceived(AuthConn *conn, const Packet *pkt, const char *data)
{
    SOFTBUS_PRINT("[AUTH] OnDataReceived\n");
    if ((pkt->module > MODULE_HICHAIN) && (pkt->module <= MODULE_AUTH_SDK)) {
        AuthInterfaceOnDataReceived(conn, pkt->module, pkt->seq, data, pkt->dataLen);
        return;
    }

    cJSON *msg = DecryptMessage(pkt->module, data, pkt->dataLen);
    if (msg == NULL) {
        SOFTBUS_PRINT("[AUTH] OnDataReceived DecryptMessage fail\n");
        return;
    }

    OnModuleMessageReceived(conn, pkt->module, pkt->flags, pkt->seq, msg);
    cJSON_Delete(msg);
    msg = NULL;
}

static int GetIntFromBuf(const char *buf, int offset)
{
    int val = 0;
    if (memcpy_s(&val, sizeof(int), buf + offset, sizeof(int)) != EOK) {
        return -1;
    }
    return val;
}

static int GetLongFromBuf(const char *buf, int offset, long long *val)
{
    if (buf == NULL || val == NULL) {
        return -1;
    }
    if (memcpy_s(val, sizeof(long long), buf + offset, sizeof(long long)) != EOK) {
        return -1;
    }
    return 0;
}

static Packet *ParsePacketHead(const char *buf, int offset, int len, int size)
{
    if ((buf == NULL) || (offset < 0) || (len < PACKET_HEAD_SIZE) ||
        (offset + len <= 0) || (offset + len > size)) {
        return NULL;
    }

    unsigned int identifier = GetIntFromBuf(buf, offset);
    if (identifier != PKG_HEADER_IDENTIFIER) {
        SOFTBUS_PRINT("[AUTH] ParsePacketHead invalid magic number\n");
        return NULL;
    }

    offset += DEFAULT_INT_LEN;
    int module = GetIntFromBuf(buf, offset);
    offset += DEFAULT_INT_LEN;
    long long seq = 0;
    if (GetLongFromBuf(buf, offset, &seq) != 0) {
        return NULL;
    }
    offset += DEFAULT_LONG_LEN;
    int flags = GetIntFromBuf(buf, offset);
    offset += DEFAULT_INT_LEN;
    int dataLen = GetIntFromBuf(buf, offset);

    SOFTBUS_PRINT("[AUTH] ParsePacketHead module=%d, seq=%lld, flags=%d, datalen=%d\n", module, seq, flags, dataLen);
    if (module < 0 || flags < 0 || dataLen < 0) {
        return NULL;
    }

    Packet *packet = (Packet *)malloc(sizeof(Packet));
    if (packet == NULL) {
        return NULL;
    }
    packet->module = module;
    packet->seq = seq;
    packet->flags = flags;
    packet->dataLen = dataLen;

    return packet;
}

static int ProcessPackets(AuthConn *conn, const char *buf, int size, int used)
{
    int processed = 0;
    while (processed + PACKET_HEAD_SIZE < used) {
        Packet *pkt = ParsePacketHead(buf, processed, used - processed, size);
        if (pkt == NULL) {
            SOFTBUS_PRINT("[AUTH] ProcessPackets ParsePacketHead fail\n");
            return -1;
        }

        int len = pkt->dataLen;
        if ((len > PACKET_DATA_SIZE) || (processed + PACKET_HEAD_SIZE + len > used)) {
            free(pkt);
            pkt = NULL;
            break;
        }
        processed += PACKET_HEAD_SIZE;

        OnDataReceived(conn, pkt, buf + processed);
        processed += len;
        free(pkt);
        pkt = NULL;
    }

    return processed;
}

void ProcessDataEvent(int fd)
{
    SOFTBUS_PRINT("[AUTH] ProcessDataEvent fd = %d\n", fd);
    AuthConn *conn = FindAuthConnByFd(fd);
    if (conn == NULL) {
        SOFTBUS_PRINT("ProcessDataEvent get authConn fail\n");
        return;
    }

    if (conn->db.buf == NULL) {
        conn->db.buf = (char *)malloc(DEFAULT_BUF_SIZE);
        if (conn->db.buf == NULL) {
            return;
        }
        (void)memset_s(conn->db.buf, DEFAULT_BUF_SIZE, 0, DEFAULT_BUF_SIZE);
        conn->db.size = DEFAULT_BUF_SIZE;
        conn->db.used = 0;
    }

    DataBuffer *db = &conn->db;
    char *buf = db->buf;
    int used = db->used;
    int size = db->size;

    int rc = AuthConnRecv(fd, buf, used, size - used, 0);
    if (rc == 0) {
        return;
    } else if (rc < 0) {
        CloseConn(conn);
        return;
    }

    used += rc;
    int processed = ProcessPackets(conn, buf, size, used);
    if (processed > 0) {
        used -= processed;
        if (used != 0) {
            if (memmove_s(buf, processed, buf, used) != EOK) {
                CloseConn(conn);
                return;
            }
        }
    } else if (processed < 0) {
        CloseConn(conn);
        return;
    }

    db->used = used;
    SOFTBUS_PRINT("[AUTH] ProcessDataEvent ok\n");
}

