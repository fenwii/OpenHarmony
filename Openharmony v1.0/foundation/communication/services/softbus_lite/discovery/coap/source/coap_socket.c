/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "coap_socket.h"

#include "coap_adapter.h"
#include "nstackx_error.h"
#include "os_adapter.h"
#include "securec.h"
typedef void (*TaskHandle)(void *arg);
SocketInfo g_socket = {0};
int g_serverFd = -1;
int g_clientFd = -1;

#define COAP_DEFAULT_PRIO 11

int GetCoapServerSocket(void)
{
    return g_serverFd;
}

int GetCoapClientSocket(void)
{
    return g_clientFd;
}

int CoapCreateUdpServer(const struct sockaddr_in *sockAddr)
{
    if (sockAddr == NULL) {
        return NSTACKX_EINVAL;
    }

    struct sockaddr_in localAddr;
    socklen_t len = sizeof(localAddr);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        return NSTACKX_OVERFLOW;
    }

    (void)memset_s(&localAddr, sizeof(localAddr), 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = sockAddr->sin_port;
    if (sockAddr->sin_addr.s_addr != 0) {
        localAddr.sin_addr.s_addr = sockAddr->sin_addr.s_addr;
    } else {
        localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    if (bind(sockfd, (struct sockaddr *)&localAddr, len) == -1) {
        CloseSocket(&sockfd);
        return NSTACKX_EFAILED;
    }

    if (getsockname(sockfd, (struct sockaddr *)&localAddr, &len) == -1) {
        CloseSocket(&sockfd);
        return NSTACKX_EFAILED;
    }
    return sockfd;
}

int CoapInitSocket(void)
{
    if (g_serverFd >= 0) {
        return NSTACKX_EOK;
    }
    struct sockaddr_in sockAddr;
    (void)memset_s(&sockAddr, sizeof(sockAddr), 0, sizeof(sockAddr));
    sockAddr.sin_port = htons(COAP_DEFAULT_PORT);
    g_serverFd = CoapCreateUdpServer(&sockAddr);
    if (g_serverFd < 0) {
        return NSTACKX_OVERFLOW;
    }
    COAP_SoftBusInitMsgId();
    return NSTACKX_EOK;
}

void CoapDeinitSocket(void)
{
    CloseSocket(&g_serverFd);
    CloseSocket(&g_clientFd);
    SOFTBUS_PRINT("[DISCOVERY] DeinitCoapSocket:%d\n", g_serverFd);
    return;
}

int CoapCreatUdpClient(const struct sockaddr_in *sockAddr)
{
    if (sockAddr == NULL) {
        return NSTACKX_EFAILED;
    }

    struct sockaddr_in tmpAddr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        return NSTACKX_EFAILED;
    }

    int ret = connect(sockfd, (struct sockaddr *)sockAddr, sizeof(struct sockaddr));
    if (ret != 0) {
        CloseSocket(&sockfd);
        return NSTACKX_EFAILED;
    }

    socklen_t srcAddrLen = sizeof(struct sockaddr_in);
    (void)memset_s(&tmpAddr, sizeof(tmpAddr), 0, sizeof(tmpAddr));
    ret = getsockname(sockfd, (struct sockaddr *)&tmpAddr, &srcAddrLen);
    if (ret != 0) {
        CloseSocket(&sockfd);
        return NSTACKX_EFAILED;
    }

    CloseSocket(&g_clientFd);
    g_clientFd = sockfd;

    return NSTACKX_EOK;
}

int CoapSocketSend(const SocketInfo *socket, const uint8_t *buffer, size_t length)
{
    if (buffer == NULL || socket == NULL) {
        return NSTACKX_EFAILED;
    }

    socklen_t dstAddrLen = sizeof(struct sockaddr_in);
    int ret = sendto(socket->cliendFd, buffer, length, 0, (struct sockaddr *)&socket->dstAddr, dstAddrLen);
    return ret;
}

int CoapSocketRecv(int socketFd, uint8_t *buffer, size_t length)
{
    if (buffer == NULL || socketFd < 0) {
        return NSTACKX_EFAILED;
    }

    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    (void)memset_s(&addr, sizeof(addr), 0, sizeof(addr));
    int ret = recvfrom(socketFd, buffer, length, 0, (struct sockaddr *)&addr, &len);
    return ret;
}
