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
#include "tcp_socket.h"

#include <arpa/inet.h>
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include <lwip/sockets.h>
#else
#include <sys/socket.h>
#endif

#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "data_bus_error.h"
#include "os_adapter.h"

#define SEND_BUF_SIZE           0x200000
#define RECV_BUF_SIZE           0x100000
#define USER_TIMEOUT_MS         5000
#define DEFAULT_SEND_TIMEOUT    200

static int SetReuseAddr(int fd, int on)
{
    int rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (rc != 0) {
        SOFTBUS_PRINT("[TRANS] SetReuseAddr fail\n");
        return -1;
    }
    return 0;
}

static int SetNoDelay(int fd, int on)
{
    int rc = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
    if (rc != 0) {
        SOFTBUS_PRINT("[TRANS] SetNoDelay fail\n");
        return -1;
    }
    return 0;
}

static void SetServerOption(int fd)
{
    SetReuseAddr(fd, 1);
    SetNoDelay(fd, 1);
}

int OpenTcpServer(const char *ip, uint16_t port)
{
    if (ip == NULL) {
        return -DBE_BAD_PARAM;
    }

    struct sockaddr_in addr = {0};
    errno = 0;
    int rc = inet_pton(AF_INET, ip, &addr.sin_addr);
    if (rc <= 0) {
        SOFTBUS_PRINT("[TRANS] OpenTcpServer inet_pton fail, rc=%d:%s\n", rc, strerror(errno));
        return -DBE_BAD_IP;
    }
    SOFTBUS_PRINT("[TRANS] OpenTcpServer inet_pton rc=%d\n", rc);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    errno = 0;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        SOFTBUS_PRINT("[TRANS] OpenTcpServer socket fail, rc=%d:%s\n", rc, strerror(errno));
        return -DBE_OPEN_SOCKET;
    }

    SOFTBUS_PRINT("[TRANS] OpenTcpServer fd=%d\n", fd);

    SetServerOption(fd);

    errno = 0;
    rc = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (rc < 0) {
        SOFTBUS_PRINT("[TRANS] OpenTcpServer bind fail, rc=%d:%s\n", rc, strerror(errno));
        ShutDown(fd);
        return -DBE_BIND_SOCKET;
    }

    return fd;
}

int GetSockPort(int fd)
{
    struct sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);

    int rc = getsockname(fd, (struct sockaddr *)&addr, &addrLen);
    if (rc != 0) {
        SOFTBUS_PRINT("[TRANS] GetSockPort getsockname fail, fd=%d, rc=%d,%s", fd, rc, strerror(errno));
        return rc;
    }
    return ntohs(addr.sin_port);
}

int TcpSendData(int fd, const char *buf, int len, int timeout)
{
    if (fd < 0 || buf == NULL || len == 0) {
        return -1;
    }

    if (timeout == 0) {
        timeout = DEFAULT_SEND_TIMEOUT;
    }

    int32_t bytes = 0;
    while (true) {
        errno = 0;
        if (bytes >= len || bytes < 0) {
            break;
        }
        int32_t rc = send(fd, &buf[bytes], len - bytes, 0);
        if ((rc == -1) && (errno == EAGAIN)) {
            continue;
        } else if (rc <= 0) {
            if (bytes == 0) {
                bytes = -1;
            }
            break;
        }
        bytes += rc;
        if (bytes == len) {
            break;
        }
    }
    return bytes;
}

static int32_t TcpRecvMessages(int fd, char *buf, uint32_t len, int timeout, int flags)
{
    if (fd < 0 || buf == NULL || len == 0 || timeout < 0) {
        return -1;
    }

    errno = 0;
    int32_t rc = recv(fd, buf, len, flags);
    if ((rc == -1) && (errno == EAGAIN)) {
        SOFTBUS_PRINT("[TRANS] TcpRecvMessages recv fail, errno is eagain\n");
        rc = 0;
    } else if (rc <= 0) {
        rc = -1;
        SOFTBUS_PRINT("[TRANS] TcpRecvMessage recv fail, errno is %s\n", strerror(errno));
    }
    return rc;
}

int TcpRecvData(int fd, char *buf, int len, int timeout)
{
    return TcpRecvMessages(fd, buf, len, timeout, 0);
}

void CloseFd(int fd)
{
    if (fd >= 0) {
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
        closesocket(fd);
#else
        close(fd);
#endif
    }
}

void ShutDown(int fd)
{
    if (fd >= 0) {
        SOFTBUS_PRINT("[TRANS] ShutDown fd=%d\n", fd);
        shutdown(fd, SHUT_RDWR);
        CloseFd(fd);
    }
}
