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

#include "tcp_session_manager.h"

#include <arpa/inet.h>
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include <los_task.h>
#else
#include <pthread.h>
#include "pms_interface.h"
#include "pms_types.h"
#endif
#include <malloc.h>
#include <mbedtls/base64.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include "aes_gcm.h"
#include "auth_conn.h"
#include "auth_interface.h"
#include "bus_manager.h"
#include "cJSON.h"
#include "message.h"
#include "os_adapter.h"
#include "session.h"
#include "tcp_session.h"
#include "tcp_socket.h"
#include "trans_lock.h"
#include "wifi_auth_manager.h"

#define MAX_SESSION_NUM 3
#define MAX_SESSION_SERVER_NUM 8
#define MAX_SESSION_SUM_NUM (MAX_SESSION_NUM * MAX_SESSION_SERVER_NUM)

#define MODULE_SESSION 6
#define AUTH_PACKET_HEAD_SIZE 24
#define TRANS_PACKET_HEAD_SIZE 16
#define TRANS_SEQ_NUM_OFFSET 8
#define RECIVED_BUFF_SIZE 1024
#define LISTEN_BACKLOG 4
#define DEFAULT_SEQNUM 100
#define DEFAULT_TV_SEC 10
#define DEFAULT_TRANS_PORT 0
#define DEFAULT_API_VERSION 2
#define DEFAULT_LONG_LEN 8

#define SESSION_KEY_INDEX_SIZE 4
#define TRANS_FAILED    (-1)

#define DEFAULT_TIMEOUT 200
#define ONE_SEC 1000

#define SIZE_OF_INT         sizeof(int)
#define SIZE_OF_LONG_LONG   sizeof(long long)

#define SEND_BUFF_MAX_SIZE  (RECIVED_BUFF_SIZE - SESSION_KEY_INDEX_SIZE - TRANS_PACKET_HEAD_SIZE - OVERHEAD_LEN)

#define SOFTBUS_PERMISSION_NAME  "ohos.permission.DISTRIBUTED_DATASYNC"

typedef struct {
    char moduleName[NAME_LENGTH];
    char sessionName[NAME_LENGTH];
    struct ISessionListener *listener;
} SessionListenerMap;

typedef struct {
    bool asServer;
    int listenFd;
    bool isSelectLoopRunning;
    struct ISessionListener *callback_;
    TcpSession* sessionMap_[MAX_SESSION_SUM_NUM];
    SessionListenerMap* serverListenerMap[MAX_SESSION_SERVER_NUM];
} TcpSessionMgr;

TcpSessionMgr* g_sessionMgr;

static TcpSession *GetSessionById(int sessionId)
{
    if (g_sessionMgr == NULL) {
        return NULL;
    }
    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if ((g_sessionMgr->sessionMap_[i] != NULL) && (g_sessionMgr->sessionMap_[i]->fd == sessionId)) {
            return g_sessionMgr->sessionMap_[i];
        }
    }
    return NULL;
}

static SessionListenerMap *GetSessionListenerByName(const char *sessionName, int nameSize)
{
    if (nameSize <= 0 || nameSize >= NAME_LENGTH) {
        SOFTBUS_PRINT("[TRANS] GetSessionListenerByName invalid para\n");
        return NULL;
    }
    if (g_sessionMgr == NULL) {
        return NULL;
    }

    SessionListenerMap* sessionListener = NULL;

    for (int i = 0; i < MAX_SESSION_SERVER_NUM; i++) {
        if (g_sessionMgr->serverListenerMap[i] != NULL &&
            strcmp(g_sessionMgr->serverListenerMap[i]->sessionName, sessionName) == 0) {
            sessionListener = g_sessionMgr->serverListenerMap[i];
            break;
        }
    }

    return sessionListener;
}

static int InitSelectList(const TcpSessionMgr *tsm, fd_set *rfds, fd_set *exceptfds)
{
    if (tsm == NULL || tsm->listenFd == -1 || rfds == NULL) {
        return TRANS_FAILED;
    }

    int maxFd = tsm->listenFd;
    FD_ZERO(rfds);
    FD_ZERO(exceptfds);
    FD_SET(tsm->listenFd, rfds);
    if (GetTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if ((tsm->sessionMap_[i]) == NULL) {
            continue;
        }

        int fd = tsm->sessionMap_[i]->fd;
        if (fd >= 0) {
            FD_SET(fd, rfds);
            FD_SET(fd, exceptfds);
            maxFd = (maxFd > fd) ? maxFd : fd;
        }
    }
    if (ReleaseTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }
    return maxFd;
}

static bool RemoveSession(TcpSessionMgr *tsm, int sessionId)
{
    if (tsm == NULL || sessionId < 0) {
        SOFTBUS_PRINT("[TRANS] RemoveSession invalid para\n");
        return false;
    }

    SessionSeqNumNode* node = NULL;
    List* pos = NULL;
    List* tmp = NULL;

    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if (tsm->sessionMap_[i] != NULL && tsm->sessionMap_[i]->fd == sessionId) {
            LIST_FOR_EACH_SAFE(pos, tmp, tsm->sessionMap_[i]->seqNumList) {
                node = (SessionSeqNumNode*)pos;
                if (node == NULL) {
                    continue;
                }
                free(node);
            }
            free(tsm->sessionMap_[i]->seqNumList);
            free(tsm->sessionMap_[i]);
            tsm->sessionMap_[i] = NULL;
            return true;
        }
    }

    return false;
}

static void CloseTransSession(int sessionId)
{
    CloseFd(sessionId);
    TcpSession *session = GetSessionById(sessionId);
    if (session == NULL) {
        SOFTBUS_PRINT("[TRANS] CloseTransSession GetSessionById fail\n");
        return;
    }
    RemoveSession(g_sessionMgr, sessionId);
    SessionListenerMap *serverListener = GetSessionListenerByName(session->sessionName, strlen(session->sessionName));
    if (serverListener == NULL) {
        return;
    }
    serverListener->listener->onSessionClosed(sessionId);
}

static int RemoveExceptSessionFd(const TcpSessionMgr *tsm, fd_set *exceptfds)
{
    if (tsm == NULL || tsm->listenFd == -1 || exceptfds == NULL) {
        return TRANS_FAILED;
    }

    if (FD_ISSET(tsm->listenFd, exceptfds)) {
        return TRANS_FAILED;
    }

    if (GetTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    int result = TRANS_FAILED;
    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if ((tsm->sessionMap_[i]) == NULL) {
            continue;
        }

        int fd = tsm->sessionMap_[i]->fd;
        if (fd >= 0) {
            if (FD_ISSET(fd, exceptfds)) {
                result = 0;
                SOFTBUS_PRINT("Session is closed. %d\r\n", fd);
                CloseTransSession(fd);
            }
        }
    }

    if (ReleaseTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    return result;
}

static bool AddSession(TcpSessionMgr *tsm, TcpSession *session)
{
    if (tsm == NULL || session == NULL) {
        SOFTBUS_PRINT("[TRANS] AddSession invalid para\n");
        return false;
    }

    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if (tsm->sessionMap_[i] == NULL) {
            tsm->sessionMap_[i] = session;
            return true;
        }
    }

    return false;
}

static void ProcessConnection(TcpSessionMgr *tsm)
{
    struct sockaddr_in addr = { 0 };
    socklen_t addrLen = sizeof(addr);

    int cfd = accept(tsm->listenFd, (struct sockaddr *)&addr, &addrLen);
    if (cfd < 0) {
        SOFTBUS_PRINT("[TRANS] ProcessConnection accept fail\n");
        return;
    }

    TcpSession *session = CreateTcpSession();
    if (session == NULL) {
        SOFTBUS_PRINT("[TRANS] ProcessConnection CreateTcpSession fail, fd = %d\n", cfd);
        CloseSession(cfd);
        return;
    }

    AuthConn* authConn = GetOnLineAuthConnByIp(inet_ntoa(addr.sin_addr));
    if (authConn != NULL && strncpy_s(session->deviceId, MAX_DEV_ID_LEN, authConn->deviceId,
        strlen(authConn->deviceId)) != 0) {
        SOFTBUS_PRINT("[TRANS] Error on copy deviceId of session.");
        free(session);
        CloseSession(cfd);
        return;
    }
    session->fd = cfd;
    int result = AddSession(tsm, session);
    if (result == false) {
        SOFTBUS_PRINT("[TRANS] AddSession fail\n");
        free(session);
        CloseSession(cfd);
        return;
    }
    return;
}

static unsigned char* PackBytes(const char *str, int *bufLen)
{
    return AuthConnPackBytes(MODULE_SESSION, 1, DEFAULT_SEQNUM, str, bufLen);
}

static void GetReplyMsg(cJSON *jsonObj, const TcpSession *session)
{
    cJSON_AddNumberToObject(jsonObj, "CODE", 1);
    cJSON_AddNumberToObject(jsonObj, "API_VERSION", DEFAULT_API_VERSION);
    DeviceInfo *local = BusGetLocalDeviceInfo();
    if (local == NULL) {
        return;
    }
    char* deviceId = local->deviceId;
    cJSON_AddStringToObject(jsonObj, "DEVICE_ID", deviceId);
    cJSON_AddNumberToObject(jsonObj, "UID", -1);
    cJSON_AddNumberToObject(jsonObj, "PID", -1);
    cJSON_AddStringToObject(jsonObj, "PKG_NAME", session->sessionName);
    cJSON_AddStringToObject(jsonObj, "CLIENT_BUS_NAME", session->sessionName);
    cJSON_AddStringToObject(jsonObj, "AUTH_STATE", "");
    cJSON_AddNumberToObject(jsonObj, "CHANNEL_TYPE", 1);
}

static int GetIntFromBuf(const char *buf, int offset)
{
    int val = 0;
    if (memcpy_s(&val, SIZE_OF_INT, buf + offset, SIZE_OF_INT) != 0) {
        return TRANS_FAILED;
    }
    return val;
}

static int GetKeyIndex(const char *in, unsigned int inOffset, unsigned int indexLen)
{
    int val = 0;
    if (memcpy_s(&val, indexLen, in + inOffset, indexLen) != EOK) {
        return -1;
    }
    return val;
}

static void CloseAllSession(const TcpSessionMgr *tsm)
{
    if (GetTcpMgrLock() != 0) {
        return;
    }
    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if ((tsm->sessionMap_[i]) == NULL) {
            continue;
        }

        CloseTransSession(tsm->sessionMap_[i]->fd);
    }

    if (ReleaseTcpMgrLock() != 0) {
        return;
    }
}

static cJSON *TransFirstPkg2Json(const char *buffer, int bufferSize)
{
    if (bufferSize < AUTH_PACKET_HEAD_SIZE) {
        SOFTBUS_PRINT("[TRANS] bufferSize < AUTH_PACKET_HEAD_SIZE\n");
        return NULL;
    }
    int offset = 0;
    int headerIdentifier = GetIntFromBuf(buffer, offset);
    if ((unsigned int)headerIdentifier != PKG_HEADER_IDENTIFIER) {
        SOFTBUS_PRINT("[TRANS] TransFirstPkg2Json HEADER_IDENTIFIER invalid: %d\n", headerIdentifier);
        return NULL;
    }

    offset += SIZE_OF_INT;
    offset += SIZE_OF_INT;
    offset += SIZE_OF_LONG_LONG;
    offset += SIZE_OF_INT;
    int dataLen = GetIntFromBuf(buffer, offset) - SESSION_KEY_INDEX_SIZE;
    if (dataLen <= 0 || dataLen > (RECIVED_BUFF_SIZE - AUTH_PACKET_HEAD_SIZE)) {
        return NULL;
    }

    int index = GetKeyIndex(buffer, AUTH_PACKET_HEAD_SIZE, MESSAGE_INDEX_LEN);
    SessionKey *sessionKey = AuthGetSessionKeyByIndex(index);
    if (sessionKey == NULL) {
        SOFTBUS_PRINT("[TRANS] TransFirstPkg2Json GetSessionKey fail\n");
        return NULL;
    }

    char *firstDataJson = (char *)malloc(dataLen);
    if (firstDataJson == NULL) {
        return NULL;
    }

    unsigned char* cipherTxt = (unsigned char*)(buffer + AUTH_PACKET_HEAD_SIZE + SESSION_KEY_INDEX_SIZE);
    AesGcmCipherKey cipherKey = {0};
    cipherKey.keybits = GCM_KEY_BITS_LEN_128;
    int ret = memcpy_s(cipherKey.key, SESSION_KEY_LENGTH, sessionKey->key, AUTH_SESSION_KEY_LEN);
    ret += memcpy_s(cipherKey.iv, IV_LEN, cipherTxt, IV_LEN);
    if (ret != 0) {
        free(firstDataJson);
        return NULL;
    }

    int plainLen = DecryptTransData(&cipherKey, cipherTxt, dataLen, (unsigned char*)firstDataJson, dataLen);
    if (plainLen <= 0) {
        free(firstDataJson);
        return NULL;
    }
    cJSON *receiveObj = cJSON_ParseWithLength(firstDataJson, dataLen);
    free(firstDataJson);
    return receiveObj;
}

static bool AssignValue2Session(TcpSession *session, cJSON *receiveObj)
{
    if (receiveObj == NULL) {
        return false;
    }

    char *recvBus = GetJsonString(receiveObj, "BUS_NAME");
    if (recvBus == NULL) {
        return false;
    }
    if (strncpy_s(session->sessionName, NAME_LENGTH, recvBus, strlen(recvBus)) != 0) {
        return false;
    }

    char *sessionKeyEncoded = GetJsonString(receiveObj, "SESSION_KEY");
    if (sessionKeyEncoded == NULL) {
        return false;
    }

    size_t olen = 0;
    int ret = mbedtls_base64_decode((unsigned char *)session->sessionKey, SESSION_KEY_LENGTH,
        &olen, (unsigned char *)sessionKeyEncoded, strlen(sessionKeyEncoded));
    if (ret != 0) {
        SOFTBUS_PRINT("[TRANS] AssignValue2Session mbedtls_base64_decode error: %d\n", ret);
        return false;
    }

    SOFTBUS_PRINT("[TRANS] AssignValue2Session busname=%s, fd=%d\n", session->sessionName, session->fd);
    return true;
}

static bool ResponseToClient(TcpSession *session)
{
    cJSON *jsonObj = cJSON_CreateObject();
    if (jsonObj == NULL) {
        return false;
    }

    GetReplyMsg(jsonObj, session);
    char *msg = cJSON_PrintUnformatted(jsonObj);
    if (msg == NULL) {
        cJSON_Delete(jsonObj);
        return false;
    }

    int bufLen = 0;
    unsigned char *buf = PackBytes(msg, &bufLen);
    if (buf == NULL) {
        SOFTBUS_PRINT("[TRANS] ResponseToClient PackBytes fail\n");

        free(msg);
        cJSON_Delete(jsonObj);
        return false;
    }

    int dataLen = TcpSendData(session->fd, (char*)buf, bufLen, 0);
    free(msg);
    cJSON_Delete(jsonObj);
    if (dataLen <= 0) {
        free(buf);
        SOFTBUS_PRINT("[TRANS] ResponseToClient TcpSendData fail\n");
        return false;
    }
    free(buf);
    return true;
}

static bool HandleRequestMsg(TcpSession *session)
{
    int ret;
    char data[RECIVED_BUFF_SIZE] = { 0 };

    int32_t size = TcpRecvData(session->fd, data, RECIVED_BUFF_SIZE, 0);
    if (size <= AUTH_PACKET_HEAD_SIZE + SESSION_KEY_INDEX_SIZE) {
        SOFTBUS_PRINT("[TRANS] HandleRequestMsg TcpRecvData fail\n");
        return false;
    }

    cJSON *receiveObj = TransFirstPkg2Json(data, size);
    if (receiveObj == NULL) {
        return false;
    }

    ret = AssignValue2Session(session, receiveObj);
    cJSON_Delete(receiveObj);
    if (ret != true) {
        return false;
    }

    SessionListenerMap *sessionListener = GetSessionListenerByName(session->sessionName, strlen(session->sessionName));
    if (sessionListener == NULL) {
        return false;
    }

    if (!ResponseToClient(session)) {
        SOFTBUS_PRINT("[TRANS] HandleRequestMsg ResponseToClient fail\n");
        return false;
    }

    if (sessionListener->listener == NULL) {
        return false;
    }
    if (sessionListener->listener->onSessionOpened == NULL) {
        return false;
    }

    if (sessionListener->listener->onSessionOpened(session->fd) != 0) {
        return false;
    }
    return true;
}

static SessionSeqNumNode* FindSessionSeqNumNode(const TcpSession* session, int seqNum)
{
    if (session == NULL) {
        return NULL;
    }
    SessionSeqNumNode* node = NULL;
    List* pos = NULL;
    List* tmp = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, session->seqNumList) {
        node = (SessionSeqNumNode*)pos;
        if (node->seqNum == seqNum) {
            return node;
        }
    }

    return NULL;
}

static void FreeSessionRecvMem(char* recvDataBuf, TcpSession* session)
{
    if (recvDataBuf != NULL) {
        free(recvDataBuf);
    }
    if (session == NULL) {
        return;
    }

    CloseSession(session->fd);
    session->fd = -1;
}

static int32_t TcpSessionRecv(TcpSession *session, const char* buf, uint32_t size, int timeout)
{
    if (buf == NULL || session == NULL || session->fd < 0 || size <= 0 || timeout < 0) {
        return TRANS_FAILED;
    }

    char *recvDataBuf = (char *)malloc(size + OVERHEAD_LEN);
    if (recvDataBuf == NULL) {
        return TRANS_FAILED;
    }
    int recvSize = TcpRecvData(session->fd, recvDataBuf, size + OVERHEAD_LEN, 0);
    if (recvSize < TRANS_PACKET_HEAD_SIZE) {
        FreeSessionRecvMem(recvDataBuf, session);
        return TRANS_FAILED;
    }

    long long seq = 0;
    AesGcmCipherKey cipherKey = {0};
    cipherKey.keybits = GCM_KEY_BITS_LEN_256;
    int ret = memcpy_s(&seq, SIZE_OF_LONG_LONG, recvDataBuf + TRANS_SEQ_NUM_OFFSET, SIZE_OF_LONG_LONG);
    ret += memcpy_s(cipherKey.key, SESSION_KEY_LENGTH, session->sessionKey, SESSION_KEY_LENGTH);
    ret += memcpy_s(cipherKey.iv, IV_LEN, recvDataBuf + TRANS_PACKET_HEAD_SIZE, IV_LEN);
    if (ret != 0) {
        FreeSessionRecvMem(recvDataBuf, session);
        return TRANS_FAILED;
    }

    if (memcmp(cipherKey.iv, &seq, SIZE_OF_INT) != 0) {
        SOFTBUS_PRINT("[TRANS] seqNum is not contains in IV.\n");
        FreeSessionRecvMem(recvDataBuf, session);
        return TRANS_FAILED;
    }

    if (FindSessionSeqNumNode(session, seq) != NULL) {
        SOFTBUS_PRINT("[TRANS] seqNum is used.\n");
        FreeSessionRecvMem(recvDataBuf, session);
        return TRANS_FAILED;
    }

    SessionSeqNumNode* node = calloc(1, sizeof(SessionSeqNumNode));
    if (node == NULL) {
        FreeSessionRecvMem(recvDataBuf, session);
        return TRANS_FAILED;
    }
    node->seqNum = seq;
    ListInsertTail(session->seqNumList, &(node->head));

    int plainLen = DecryptTransData(&cipherKey, (unsigned char*)(recvDataBuf + TRANS_PACKET_HEAD_SIZE),
        recvSize - TRANS_PACKET_HEAD_SIZE, (unsigned char*)buf, size);
    free(recvDataBuf);
    if (plainLen <= 0) {
        return TRANS_FAILED;
    }

    return plainLen;
}

static bool OnProcessDataAvailable(TcpSession *session)
{
    if (session == NULL) {
        return false;
    }

    if (strcmp(session->sessionName, "softbus_Lite_unknown") == 0) {
        bool isSuccess = HandleRequestMsg(session);
        if (!isSuccess) {
            CloseSession(session->fd);
            session->fd = -1;
        }
        return isSuccess;
    } else {
        unsigned char* buf = malloc(RECIVED_BUFF_SIZE);
        if (buf == NULL) {
            return false;
        }
        SOFTBUS_PRINT("[TRANS] OnProcessDataAvailable sessionName: %s, fd: %d\n", session->sessionName, session->fd);
        SessionListenerMap *sessionListener = GetSessionListenerByName(session->sessionName,
            strlen(session->sessionName));
        if (sessionListener != NULL && sessionListener->listener != NULL) {
            int recvLen = TcpSessionRecv(session, (char *)buf, RECIVED_BUFF_SIZE, 0);
            if (recvLen < 0) {
                free(buf);
                return false;
            }
            sessionListener->listener->onBytesReceived(session->fd, buf, recvLen);
            free(buf);
            return true;
        }
        free(buf);
    }

    return false;
}

static void ProcessSesssionData(const TcpSessionMgr *tsm, const fd_set *rfds)
{
    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if (tsm->sessionMap_[i] != NULL && tsm->sessionMap_[i]->fd != -1 &&
            FD_ISSET(tsm->sessionMap_[i]->fd, rfds) > 0) {
            if (!OnProcessDataAvailable(tsm->sessionMap_[i])) {
                return;
            }
        }
    }
}

static void ProcessData(TcpSessionMgr *tsm, fd_set *rfds)
{
    if (tsm == NULL || tsm->listenFd == -1) {
        return;
    }

    if (FD_ISSET(tsm->listenFd, rfds)) {
        ProcessConnection(tsm);
        return;
    }

    ProcessSesssionData(tsm, rfds);
}

static void FreeSessionMgr(void)
{
    free(g_sessionMgr);
    g_sessionMgr = NULL;
}

static void SelectSessionLoop(TcpSessionMgr *tsm)
{
    if (tsm == NULL) {
        return;
    }
    SOFTBUS_PRINT("[TRANS] SelectSessionLoop begin\n");
    tsm->isSelectLoopRunning = true;
    while (true) {
        fd_set readfds;
        fd_set exceptfds;
        int maxFd = InitSelectList(tsm, &readfds, &exceptfds);
        if (maxFd < 0) {
            break;
        }

        errno = 0;
        int ret = select(maxFd + 1, &readfds, NULL, &exceptfds, NULL);
        if (ret < 0) {
            SOFTBUS_PRINT("RemoveExceptSessionFd\r\n");
            if (errno == EINTR || RemoveExceptSessionFd(tsm, &exceptfds) == 0) {
                continue;
            }
            SOFTBUS_PRINT("[TRANS] SelectSessionLoop close all Session\n");
            CloseAllSession(tsm);
            break;
        } else if (ret == 0) {
            continue;
        } else {
            ProcessData(tsm, &readfds);
        }
    }
    tsm->isSelectLoopRunning = false;
}

static int CreateSessionServerInner(const char* moduleName, const char* sessionName, struct ISessionListener *listener)
{
    if (g_sessionMgr == NULL || listener == NULL || sessionName == NULL || moduleName == NULL) {
        SOFTBUS_PRINT("[TRANS] CreateSessionServer invalid param\n");
        return TRANS_FAILED;
    }

    if (strlen(moduleName) >= NAME_LENGTH || strlen(sessionName) >= NAME_LENGTH) {
        SOFTBUS_PRINT("[TRANS] CreateSessionServerInner name length is too big\n");
        return TRANS_FAILED;
    }

    int findIndex = -1;
    for (int i = 0; i < MAX_SESSION_SERVER_NUM; i++) {
        if (g_sessionMgr->serverListenerMap[i] == NULL) {
            findIndex = i;
            break;
        }
    }

    if (findIndex == -1) {
        return TRANS_FAILED;
    }

    if (findIndex >= 0 && findIndex < MAX_SESSION_SERVER_NUM) {
        g_sessionMgr->serverListenerMap[findIndex] = malloc(sizeof(SessionListenerMap));
        if (g_sessionMgr->serverListenerMap[findIndex] == NULL) {
            return TRANS_FAILED;
        }
        SessionListenerMap *listenerMap = g_sessionMgr->serverListenerMap[findIndex];
        if (strncpy_s(listenerMap->sessionName, NAME_LENGTH, sessionName, strlen(sessionName)) ||
            strncpy_s(listenerMap->moduleName, NAME_LENGTH, moduleName, strlen(moduleName))) {
            free(listenerMap);
            listenerMap = NULL;
            return TRANS_FAILED;
        }

        listenerMap->listener = listener;
    }

    return 0;
}

static int RemoveSessionServerInner(const char* moduleName, const char *sessionName)
{
    if (g_sessionMgr == NULL) {
        return TRANS_FAILED;
    }
    int removeFd = -1;
    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        if (g_sessionMgr->sessionMap_[i] != NULL &&
            strcmp(g_sessionMgr->sessionMap_[i]->sessionName, sessionName) == 0) {
            removeFd = g_sessionMgr->sessionMap_[i]->fd;
            CloseTransSession(removeFd);
            free(g_sessionMgr->sessionMap_[i]);
            g_sessionMgr->sessionMap_[i] = NULL;
        }
    }
    for (int i = 0; i < MAX_SESSION_SERVER_NUM; i++) {
        SessionListenerMap *serverListener = g_sessionMgr->serverListenerMap[i];
        if (serverListener != NULL && (strcmp(serverListener->sessionName, sessionName) == 0) &&
            (strcmp(serverListener->moduleName, moduleName) == 0)) {
            if (serverListener->listener != NULL && serverListener->listener->onSessionClosed != NULL) {
                serverListener->listener->onSessionClosed(removeFd);
            }
            free(serverListener);
            serverListener = NULL;
            break;
        }
    }
    return 0;
}

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
int StartSelectLoop(TcpSessionMgr *tsm)
{
    if (tsm == NULL) {
        return TRANS_FAILED;
    }

    if (tsm->isSelectLoopRunning) {
        return 0;
    }

    unsigned int sessionLoopTaskId = 0;
    TSK_INIT_PARAM_S serverTask;
    memset_s(&serverTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    serverTask.pfnTaskEntry = (TSK_ENTRY_FUNC)SelectSessionLoop;
    serverTask.usTaskPrio = LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO;
    serverTask.pcName = "trans_session_task";
    serverTask.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    serverTask.uwResved   = LOS_TASK_STATUS_DETACHED;
    serverTask.auwArgs[0] = (uintptr_t)tsm;
    SOFTBUS_PRINT("[TRANS] StartSelectLoop create trans_session_task\n");
    unsigned int ret = LOS_TaskCreate(&sessionLoopTaskId, &serverTask);
    if (ret != 0) {
        SOFTBUS_PRINT("[TRANS] StartSelectLoop TaskCreate fail\n");
        return TRANS_FAILED;
    }

    return 0;
}
#else
#define MIN_STACK_SIZE 0x8000
static pthread_key_t g_localKey = 0;
typedef void *(*Runnable)(void *argv);
typedef struct ThreadAttr ThreadAttr;
struct ThreadAttr {
    const char *name;   // name of the thread
    uint32_t stackSize;   // size of stack
    uint8_t priority;     // initial thread priority
    uint8_t reserved1;    // reserved1 (must be 0)
    uint16_t reserved2;   // reserved2 (must be 0)
};
typedef void *ThreadId;

ThreadId TcpCreate(Runnable run, void *argv, const ThreadAttr *attr)
{
    if (attr == NULL) {
        return NULL;
    }
    int ret;
    pthread_attr_t threadAttr;

    ret = pthread_attr_init(&threadAttr);
    if (ret != 0) {
        return NULL;
    }
    ret = pthread_attr_setstacksize(&threadAttr, (attr->stackSize | MIN_STACK_SIZE));
    if (ret != 0) {
        return NULL;
    }

    struct sched_param sched = {attr->priority};

    ret = pthread_attr_setschedparam(&threadAttr, &sched);
    if (ret != 0) {
        return NULL;
    }
    ret = pthread_key_create(&g_localKey, NULL);
    if (ret != 0) {
        return NULL;
    }

    pthread_t threadId = 0;
    ret = pthread_create(&threadId, &threadAttr, run, argv);
    if (ret != 0) {
        return NULL;
    }
    if (attr->name != NULL) {
        ret = pthread_setname_np(threadId, attr->name);
        if (ret != 0) {
            SOFTBUS_PRINT("[TRANS] TcpCreate setname fail\n");
        }
    }

    return (ThreadId)threadId;
}

int StartSelectLoop(TcpSessionMgr *tsm)
{
    if (tsm == NULL) {
        return TRANS_FAILED;
    }
    if (tsm->isSelectLoopRunning) {
        return 0;
    }
    ThreadAttr attr = {"tcp", 0x800, 20, 0, 0};
    register ThreadId threadId = (ThreadId)TcpCreate((Runnable)SelectSessionLoop, tsm, &attr);
    if (threadId == NULL) {
        return TRANS_FAILED;
    }
    tsm->isSelectLoopRunning = true;
    return 0;
}
#endif

int CreateTcpSessionMgr(bool asServer, const char* localIp)
{
    if (g_sessionMgr != NULL || localIp == NULL) {
        return TRANS_FAILED;
    }
    g_sessionMgr = malloc(sizeof(TcpSessionMgr));
    if (g_sessionMgr == NULL) {
        return TRANS_FAILED;
    }
    (void)memset_s(g_sessionMgr, sizeof(TcpSessionMgr), 0, sizeof(TcpSessionMgr));
    g_sessionMgr->asServer = asServer;
    g_sessionMgr->listenFd = -1;
    g_sessionMgr->isSelectLoopRunning = false;

    if (InitTcpMgrLock() != 0 || GetTcpMgrLock() != 0) {
        FreeSessionMgr();
        return TRANS_FAILED;
    }

    for (int i = 0; i < MAX_SESSION_SUM_NUM; i++) {
        g_sessionMgr->sessionMap_[i] = NULL;
    }

    for (int i = 0; i < MAX_SESSION_SERVER_NUM; i++) {
        g_sessionMgr->serverListenerMap[i] = NULL;
    }

    if (ReleaseTcpMgrLock() != 0) {
        FreeSessionMgr();
        return TRANS_FAILED;
    }

    int listenFd = OpenTcpServer(localIp, DEFAULT_TRANS_PORT);
    if (listenFd < 0) {
        SOFTBUS_PRINT("[TRANS] CreateTcpSessionMgr OpenTcpServer fail\n");
        FreeSessionMgr();
        return TRANS_FAILED;
    }
    int rc = listen(listenFd, LISTEN_BACKLOG);
    if (rc != 0) {
        SOFTBUS_PRINT("[TRANS] CreateTcpSessionMgr listen fail\n");
        CloseSession(listenFd);
        FreeSessionMgr();
        return TRANS_FAILED;
    }
    g_sessionMgr->listenFd = listenFd;

    signal(SIGPIPE, SIG_IGN);
    if (StartSelectLoop(g_sessionMgr) != 0) {
        SOFTBUS_PRINT("[TRANS] CreateTcpSessionMgr StartSelectLoop fail\n");
        CloseSession(listenFd);
        FreeSessionMgr();
        return TRANS_FAILED;
    }
    return GetSockPort(listenFd);
}

int RemoveTcpSessionMgr(void)
{
    if (g_sessionMgr == NULL) {
        return TRANS_FAILED;
    }
    if (GetTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    CloseAllSession(g_sessionMgr);
    CloseFd(g_sessionMgr->listenFd);
    g_sessionMgr->listenFd = -1;
    if (g_sessionMgr != NULL) {
        free(g_sessionMgr);
        g_sessionMgr = NULL;
    }

    if (ReleaseTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }
    return 0;
}

int CreateSessionServer(const char* moduleName, const char* sessionName, struct ISessionListener *listener)
{
    if (g_sessionMgr == NULL || moduleName == NULL || sessionName == NULL || listener == NULL) {
        return TRANS_FAILED;
    }

    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return TRANS_FAILED;
    }

    if (GetTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    int ret = CreateSessionServerInner(moduleName, sessionName, listener);

    if (ReleaseTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }
    return ret;
}
int RemoveSessionServer(const char* moduleName, const char *sessionName)
{
    if (moduleName == NULL || sessionName == NULL) {
        SOFTBUS_PRINT("[TRANS] moduleName == NULL || sessionName == NULL\n");
        return TRANS_FAILED;
    }

    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return TRANS_FAILED;
    }

    if (GetTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    int ret = RemoveSessionServerInner(moduleName, sessionName);

    if (ReleaseTcpMgrLock() != 0) {
        return TRANS_FAILED;
    }

    return ret;
}

static unsigned char *TransPackBytes(TcpSession *session, const unsigned char *sendData, unsigned int sendDataLen,
    int *bufLen)
{
    if (session == NULL || sendData == NULL || bufLen == NULL || sendDataLen > SEND_BUFF_MAX_SIZE || sendDataLen == 0) {
        return NULL;
    }

    int allLen = sendDataLen + TRANS_PACKET_HEAD_SIZE + OVERHEAD_LEN + SESSION_KEY_INDEX_SIZE;
    if (allLen > RECIVED_BUFF_SIZE || allLen <= 0) {
        return NULL;
    }

    int flags = 0;
    int seqNum = session->seqNum++;
    unsigned char *buf = (unsigned char *)malloc(allLen);
    if (buf == NULL) {
        return NULL;
    }

    memset_s(buf, allLen, 0, allLen);
    unsigned int magicnum = PKG_HEADER_IDENTIFIER;

    AesGcmCipherKey cipherKey = {0};
    unsigned char* randomIv = GenerateRandomIv();
    if (randomIv == NULL) {
        free(buf);
        return NULL;
    }

    int offset = 0;
    int ret = memcpy_s(buf + offset, allLen - offset, &magicnum, SIZE_OF_INT);
    offset += SIZE_OF_INT;
    ret += memcpy_s(buf + offset, allLen - offset, &seqNum, SIZE_OF_INT);
    offset += SIZE_OF_INT;
    ret += memcpy_s(buf + offset, allLen - offset, &flags, SIZE_OF_INT);
    offset += SIZE_OF_INT;
    int dataLen = sendDataLen + OVERHEAD_LEN;
    ret += memcpy_s(buf + offset, allLen - offset, &dataLen, SIZE_OF_INT);
    offset += SIZE_OF_INT;
    ret += memcpy_s(cipherKey.key, SESSION_KEY_LENGTH, session->sessionKey, SESSION_KEY_LENGTH);
    ret += memcpy_s(cipherKey.iv, IV_LEN, randomIv, IV_LEN);
    free(randomIv);
    ret += memcpy_s(cipherKey.iv, SIZE_OF_INT, &seqNum, SIZE_OF_INT);
    if (ret != 0) {
        free(buf);
        return NULL;
    }
    int cipherLen = EncryptTransData(&cipherKey, sendData, sendDataLen, buf + offset, sendDataLen + OVERHEAD_LEN);
    if (cipherLen <= 0) {
        SOFTBUS_PRINT("[TRANS] TransPackBytes EncryptTransData fail\n");
        free(buf);
        return NULL;
    }

    *bufLen = cipherLen + TRANS_PACKET_HEAD_SIZE + SESSION_KEY_INDEX_SIZE;
    return buf;
}

int SendBytes(int sessionfd, const void *buf, unsigned int size)
{
    if (buf == NULL || sessionfd < 0 || size == 0 || size > SEND_BUFF_MAX_SIZE) {
        return TRANS_FAILED;
    }

    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return TRANS_FAILED;
    }

    TcpSession *session = GetSessionById(sessionfd);
    if (session == NULL) {
        return TRANS_FAILED;
    }

    int cipherLen = 0;
    char *cipherBuf = (char *)TransPackBytes(session, (unsigned char *)buf, size, &cipherLen);
    if (cipherBuf == NULL) {
        return TRANS_FAILED;
    }

    if (cipherLen <= 0 && cipherBuf != NULL) {
        free(cipherBuf);
        return TRANS_FAILED;
    }
    int32_t bytes = 0;
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(sessionfd, &writefds);
    struct timeval msTimeout;
    msTimeout.tv_sec = DEFAULT_TIMEOUT / ONE_SEC;
    msTimeout.tv_usec = (DEFAULT_TIMEOUT % ONE_SEC) * ONE_SEC;
    int err = select(sessionfd + 1, NULL, &writefds, NULL, &msTimeout);
    if (err <= 0) {
        SOFTBUS_PRINT("[TRANS] SendBytes select err\n");
        free(cipherBuf);
        return TRANS_FAILED;
    }

    while (FD_ISSET(sessionfd, &writefds) && bytes < (int32_t)cipherLen && (sessionfd) >= 0) {
        errno = 0;
        int32_t rc = send(sessionfd, cipherBuf + bytes, cipherLen - bytes, 0);
        if ((rc == -1) && (errno == EAGAIN)) {
            continue;
        } else if (rc <= 0) {
            if (bytes == 0) {
                bytes = -1;
            }
            break;
        }
        bytes += rc;
    }

    free(cipherBuf);
    return 0;
}

int GetMySessionName(int sessionId, char *sessionName, unsigned int len)
{
    if (sessionName == NULL) {
        return TRANS_FAILED;
    }

    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return TRANS_FAILED;
    }

    TcpSession *session = GetSessionById(sessionId);
    if (session == NULL) {
        SOFTBUS_PRINT("[TRANS] GetMySessionName GetSessionById fail\n");
        return TRANS_FAILED;
    }

    char *name = session->sessionName;
    if (strlen(name) > len) {
        SOFTBUS_PRINT("[TRANS] len is too small.\n");
        return TRANS_FAILED;
    }

    if (strncpy_s(sessionName, len, name, strlen(name)) != 0) {
        SOFTBUS_PRINT("[TRANS] devId copy failed.\n");
        return TRANS_FAILED;
    }

    return 0;
}

int GetPeerSessionName(int sessionId, char *sessionName, unsigned int len)
{
    if (sessionName == NULL) {
        SOFTBUS_PRINT("[TRANS] sessionName == NULL\n");
        return TRANS_FAILED;
    }

    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return TRANS_FAILED;
    }

    // Peer session name equal to my session name.
    return GetMySessionName(sessionId, sessionName, len);
}

int GetPeerDeviceId(int sessionId, char *devId, unsigned int len)
{
    if (devId == NULL) {
        SOFTBUS_PRINT("[TRANS] devId == NULL\n");
        return TRANS_FAILED;
    }

    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return TRANS_FAILED;
    }

    TcpSession *session = GetSessionById(sessionId);
    if (session == NULL) {
        SOFTBUS_PRINT("[TRANS] GetPeerDeviceId GetSessionById fail\n");
        return TRANS_FAILED;
    }

    char *id = session->deviceId;
    if (strlen(id) > len) {
        SOFTBUS_PRINT("[TRANS] len is too small.\n");
        return TRANS_FAILED;
    }

    if (strncpy_s(devId, len, id, strlen(id)) != 0) {
        SOFTBUS_PRINT("[TRANS] devId copy failed.\n");
        return TRANS_FAILED;
    }
    return 0;
}

void CloseSession(int sessionId)
{
    if (SoftBusCheckPermission(SOFTBUS_PERMISSION_NAME) != 0) {
        return;
    }

    if (GetTcpMgrLock() != 0) {
        return;
    }
    CloseTransSession(sessionId);
    if (ReleaseTcpMgrLock() != 0) {
        return;
    }
    return;
}
