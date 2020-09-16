/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hctest.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/tcp.h"
#include "securec.h"
#include "cmsis_os2.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define LOCAL_HOST "127.0.0.1"
#define STACK_PORT 2277
#define STACK_IP LOCAL_HOST
#define PEER_PORT STACK_PORT
#define PEER_IP LOCAL_HOST
#define UDP_MSG "Hi, I am UDP"
#define SRV_MSG "Hi, I am TCP server"
#define CLI_MSG "Hi, I am TCP client"
#define BUF_SIZE (1024 * 8)
#define LWIP_TEST_SUCCESS 0
#define LWIP_TEST_FAIL (-1)
#define DEF_TASK_STACK 2000
#define DEF_TASK_PRIORITY 20
#define ONE_SECOND 1
#define TIMEOUT 4

static char g_buf[BUF_SIZE + 1] = {0};
static int g_clientWait = 0;
static int g_clientWaitOver = 0;
static int g_serverWait = 0;
static int g_serverWaitOver = 0;
static int g_clientResult = 0;
static int g_serverResult = 0;

static void waitClient(void)
{
    while (1) {
        sleep(ONE_SECOND);
        if (g_clientWait) {
            break;
        }
    }
    g_clientWaitOver = 1;
    g_clientWait = 0;
}

static void waitServer(void)
{
    while (1) {
        sleep(ONE_SECOND);
        if (g_serverWait) {
            break;
        }
    }
    g_serverWaitOver = 1;
    g_serverWait = 0;
}

static void SampleTcpServerTask(void)
{
    int ret;
    int sfd = -1;
    int lsfd = -1;
    struct msghdr msg = {0};
    struct iovec iov[2] = {};
    struct sockaddr_in srvAddr = {0};
    struct sockaddr_in clnAddr = {0};
    socklen_t clnAddrLen = sizeof(clnAddr);
    static char buf[BUF_SIZE + 1] = {0};

    lsfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("[tcp server]create socket[server]\n");
    TEST_ASSERT_NOT_EQUAL(lsfd, LWIP_TEST_FAIL);

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(STACK_IP);
    srvAddr.sin_port = htons(STACK_PORT);
    ret = bind(lsfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr));
    printf("[tcp server]bind %s:%d,ret=%d\n", inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port), ret);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    ret = listen(lsfd, 0);
    printf("[tcp server]listen,ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    waitServer();
    sfd = accept(lsfd, (struct sockaddr*)&clnAddr, &clnAddrLen);
    printf("[tcp server]accept <%s:%d>\n", inet_ntoa(clnAddr.sin_addr), ntohs(clnAddr.sin_port));
    TEST_ASSERT_NOT_EQUAL(sfd, LWIP_TEST_FAIL);

    int srvMsgLen = strlen(SRV_MSG);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, SRV_MSG);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    ret = send(sfd, buf, srvMsgLen, 0);
    printf("[tcp server]send, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, srvMsgLen);

    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recv(sfd, buf, sizeof(buf), 0);
    printf("[tcp server]recv, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, strlen(CLI_MSG));

    waitServer();
    int len = 2;
    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(PEER_IP);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, SRV_MSG);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    msg.msg_name = &clnAddr;
    msg.msg_namelen = sizeof(clnAddr);
    msg.msg_iov = iov;
    msg.msg_iovlen = len;
    iov[0].iov_base = buf;
    iov[0].iov_len = srvMsgLen;
    iov[1].iov_base = buf;
    iov[1].iov_len = srvMsgLen;
    ret = sendmsg(sfd, &msg, 0);
    printf("[tcp server]sendmsg, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, len * srvMsgLen);

    waitServer();
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recv(sfd, buf, sizeof(buf), 0);
    printf("[tcp server]recv, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, len * strlen(CLI_MSG));

    ret = shutdown(sfd, SHUT_RDWR);
    printf("[tcp server]shutdown, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    lwip_close(sfd);
    lwip_close(lsfd);
    g_serverResult = 1;
    waitServer();
}

static void SampleTcpClientTask(void)
{
    int ret;
    int sfd = -1;
    struct msghdr msg = {0};
    struct iovec iov[2] = {};
    struct sockaddr addr;
    socklen_t addrLen = sizeof(addr);
    struct sockaddr_in srvAddr = {0};
    struct sockaddr_in clnAddr = {0};
    static char buf[BUF_SIZE+1] = {0};

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("[tcp client]create socket[client]\n");
    TEST_ASSERT_NOT_EQUAL(sfd, LWIP_TEST_FAIL);

    waitClient();
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(PEER_IP);
    srvAddr.sin_port = htons(PEER_PORT);
    ret = connect(sfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr));
    printf("[tcp client]connect %s:%d, ret=%d\n", inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port), ret);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    ret = getpeername(sfd, &addr, &addrLen);
    printf("[tcp client]getpeername %s:%d, ret=%d\n", inet_ntoa(((struct sockaddr_in*)&addr)->sin_addr),
        ntohs(((struct sockaddr_in*)&addr)->sin_port), ret);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    TEST_ASSERT_EQUAL_INT(addrLen, sizeof(struct sockaddr_in));
    TEST_ASSERT_EQUAL_INT(((struct sockaddr_in*)&addr)->sin_addr.s_addr, inet_addr(PEER_IP));

    ret = getsockname(sfd, &addr, &addrLen);
    printf("[tcp client]getsockname %s:%d, ret=%d\n", inet_ntoa(((struct sockaddr_in*)&addr)->sin_addr),
        ntohs(((struct sockaddr_in*)&addr)->sin_port), ret);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    TEST_ASSERT_EQUAL_INT(addrLen, sizeof(struct sockaddr_in));
    TEST_ASSERT_EQUAL_INT(((struct sockaddr_in*)&addr)->sin_addr.s_addr, inet_addr(STACK_IP));

    int cliMsgLen = strlen(CLI_MSG);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, CLI_MSG);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    ret = send(sfd, buf, cliMsgLen, 0);
    printf("[tcp client]send, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, cliMsgLen);

    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recv(sfd, buf, sizeof(buf), 0);
    printf("[tcp client]recv,ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, strlen(SRV_MSG));

    waitClient();
    int len = 2;
    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(PEER_IP);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, CLI_MSG);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    msg.msg_name = &clnAddr;
    msg.msg_namelen = sizeof(clnAddr);
    msg.msg_iov = iov;
    msg.msg_iovlen = len;
    iov[0].iov_base = buf;
    iov[0].iov_len = cliMsgLen;
    iov[1].iov_base = buf;
    iov[1].iov_len = cliMsgLen;
    ret = sendmsg(sfd, &msg, 0);
    printf("[tcp client]sendmsg, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, len * cliMsgLen);

    waitClient();
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recv(sfd, buf, sizeof(buf), 0);
    printf("[tcp client]recv, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, len * strlen(SRV_MSG));

    ret = shutdown(sfd, SHUT_RDWR);
    printf("[tcp client]shutdown, ret=%d\n", ret);
    TEST_ASSERT_EQUAL_INT(ret, 0);

    lwip_close(sfd);
    g_clientResult = 1;
    waitClient();
}

/**
 * @tc.desc      : register a test suite, this suite is used to test function
 * @param        : subsystem name is communication
 * @param        : module name is lwip
 * @param        : test suit name is LwipFuncTestSuite
 */
LITE_TEST_SUIT(communication, lwip, LwipFuncTestSuite);

/**
 * @tc.setup     : setup for every testcase
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL LwipFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for every testcase
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL LwipFuncTestSuiteTearDown(void)
{
    printf("+----------------------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0100
 * @tc.name      : test upd
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(LwipFuncTestSuite, testUdp, LEVEL2)
{
    int sfd;
    int ret;
    int len = 2;
    struct msghdr msg = {0};
    struct iovec iov[2] = {0};
    struct sockaddr_in srvAddr = {0};
    struct sockaddr_in clnAddr = {0};
    socklen_t clnAddrLen = sizeof(clnAddr);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    TEST_ASSERT_NOT_EQUAL(sfd, LWIP_TEST_FAIL);

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(STACK_IP);
    srvAddr.sin_port = htons(STACK_PORT);
    ret = bind(sfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(PEER_IP);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(g_buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(g_buf, BUF_SIZE, UDP_MSG);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    ret = sendto(sfd, g_buf, strlen(UDP_MSG), 0, (struct sockaddr*)&clnAddr, (socklen_t)sizeof(clnAddr));
    TEST_ASSERT_NOT_EQUAL(ret, LWIP_TEST_FAIL);

    memset_s(g_buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recvfrom(sfd, g_buf, sizeof(g_buf), 0, (struct sockaddr*)&clnAddr, &clnAddrLen);
    TEST_ASSERT_EQUAL_INT(ret, strlen(UDP_MSG));

    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(PEER_IP);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(g_buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(g_buf, BUF_SIZE, UDP_MSG);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    msg.msg_name = &clnAddr;
    msg.msg_namelen = sizeof(clnAddr);
    msg.msg_iov = iov;
    msg.msg_iovlen = len;
    iov[0].iov_base = g_buf;
    iov[0].iov_len = strlen(UDP_MSG);
    iov[1].iov_base = g_buf;
    iov[1].iov_len = strlen(UDP_MSG);
    ret = sendmsg(sfd, &msg, 0);
    TEST_ASSERT_EQUAL_INT(ret, len * strlen(UDP_MSG));

    ret = lwip_close(sfd);
    TEST_ASSERT_NOT_EQUAL(ret, LWIP_TEST_FAIL);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0200
 * @tc.name      : test socket operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(LwipFuncTestSuite, testSocketOpt, LEVEL2)
{
    int ret;
    struct timeval timeout;
    socklen_t len;

    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    TEST_ASSERT_NOT_EQUAL(fd, LWIP_TEST_FAIL);

    int error = -1;
    len = sizeof(error);
    ret = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    TEST_ASSERT_EQUAL_INT(error, LWIP_TEST_SUCCESS);
    len = sizeof(timeout);
    ret = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, &len);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    int sec = 1000;
    timeout.tv_sec = sec;
    len = sizeof(timeout);
    ret = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    memset_s(&timeout, len, 0, len);
    ret = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, &len);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    error = -1;
    len = sizeof(error);
    ret = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
    TEST_ASSERT_EQUAL_INT(error, LWIP_TEST_SUCCESS);

    int flag = 1;
    ret = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    ret = lwip_close(fd);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0300
 * @tc.name      : test inet conversion
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(LwipFuncTestSuite, testInetConv, LEVEL2)
{
    int ret;
    struct in_addr in;
    ret = inet_pton(AF_INET, "300.10.10.10", &in);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_SUCCESS);

    ret = inet_pton(AF_INET, "10.11.12.13", &in);
    TEST_ASSERT_EQUAL_INT(ret, 1);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    TEST_ASSERT_EQUAL_INT(in.s_addr, 0x0d0c0b0a);
#else
    TEST_ASSERT_EQUAL_INT(in.s_addr, 0x0a0b0c0d);
#endif

    const char *p = inet_ntoa(in);
    TEST_ASSERT_NOT_NULL(p);
    TEST_ASSERT_EQUAL_INT(strcmp(p, "10.11.12.13"), 0);

    int bufLen = 32;
    char buf[bufLen];
    p = inet_ntop(AF_INET, &in, buf, sizeof(buf));
    TEST_ASSERT_NOT_NULL(p);
    TEST_ASSERT_EQUAL_INT(strcmp(p, "10.11.12.13"), 0);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0400
 * @tc.name      : test tcp
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(LwipFuncTestSuite, testTcp, LEVEL2)
{
    osThreadAttr_t attrServer;
    attrServer.name = "SampleTcpServerTask";
    attrServer.attr_bits = 0U;
    attrServer.cb_mem = NULL;
    attrServer.cb_size = 0U;
    attrServer.stack_mem = NULL;
    attrServer.stack_size = DEF_TASK_STACK;
    attrServer.priority = DEF_TASK_PRIORITY;

    osThreadAttr_t attrClient;
    attrClient.name = "SampleTcpClientTask";
    attrClient.attr_bits = 0U;
    attrClient.cb_mem = NULL;
    attrClient.cb_size = 0U;
    attrClient.stack_mem = NULL;
    attrClient.stack_size = DEF_TASK_STACK;
    attrClient.priority = DEF_TASK_PRIORITY;

    osThreadId_t serverTaskId = osThreadNew((osThreadFunc_t)SampleTcpServerTask, NULL, &attrServer);
    TEST_ASSERT_NOT_NULL(serverTaskId);
    if (serverTaskId == NULL) {
        printf("[testTcp]create server task fail!\n");
    }
    osThreadId_t clientTaskId = osThreadNew((osThreadFunc_t)SampleTcpClientTask, NULL, &attrClient);
    TEST_ASSERT_NOT_NULL(clientTaskId);
    if (clientTaskId == NULL) {
        printf("[testTcp]create client task fail!\n");
    }

    sleep(ONE_SECOND);
    int timeout = TIMEOUT;
    g_serverWait = 1;
    g_clientWait = 1;
    while (timeout > 0) {
        if (g_serverWaitOver == 1 && g_clientWaitOver == 1) {
            printf("[testTcp] wait success[1]!\n");
            break;
        }
        timeout--;
        sleep(ONE_SECOND);
        printf("[testTcp] wait[1]...\n");
    }

    sleep(ONE_SECOND);
    timeout = TIMEOUT;
    g_serverWait = 1;
    g_clientWait = 1;
    while (timeout > 0) {
        if (g_serverWaitOver == 1 && g_clientWaitOver == 1) {
            printf("[testTcp] wait success[2]!\n");
            break;
        }
        timeout--;
        sleep(ONE_SECOND);
        printf("[testTcp] wait[2]...\n");
    }

    sleep(ONE_SECOND);
    timeout = TIMEOUT;
    g_serverWait = 1;
    g_clientWait = 1;
    while (timeout > 0) {
        if (g_serverWaitOver == 1 && g_clientWaitOver == 1) {
            printf("[testTcp] wait success[3]!\n");
            break;
        }
        timeout--;
        sleep(ONE_SECOND);
        printf("[testTcp] wait[3]...\n");
    }
    sleep(ONE_SECOND);
    timeout = TIMEOUT;
    g_serverWait = 1;
    g_clientWait = 1;
    while (timeout > 0) {
        if (g_serverWaitOver == 1 && g_clientWaitOver == 1) {
            printf("[testTcp] wait success[4]!\n");
            break;
        }
        timeout--;
        sleep(ONE_SECOND);
        printf("[testTcp] wait[4]...\n");
    }
    TEST_ASSERT_EQUAL_INT(g_clientResult, 1);
    TEST_ASSERT_EQUAL_INT(g_serverResult, 1);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0500
 * @tc.name      : test invalid parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(LwipFuncTestSuite, testInvalidParameter, LEVEL2)
{
    int ret;
    int fdFail = -1;
    int fdSuccess = -1;

    fdFail = socket(0, 0, 0);
    TEST_ASSERT_EQUAL_INT(fdFail, LWIP_TEST_FAIL);
    fdSuccess = socket(AF_INET, SOCK_STREAM, 0);
    TEST_ASSERT_NOT_EQUAL(fdSuccess, LWIP_TEST_FAIL);

    ret = bind(fdFail, NULL, sizeof(struct sockaddr_in));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = bind(fdSuccess, NULL, sizeof(struct sockaddr_in));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = connect(fdFail, NULL, sizeof(struct sockaddr));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = connect(fdSuccess, NULL, sizeof(struct sockaddr));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = accept(fdFail, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = accept(fdSuccess, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = getsockname(fdFail, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = getsockname(fdSuccess, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = getpeername(fdFail, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = getpeername(fdSuccess, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = send(fdFail, NULL, strlen(SRV_MSG), 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = send(fdSuccess, NULL, strlen(SRV_MSG), 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = sendto(fdFail, NULL, strlen(SRV_MSG), 0, NULL, (socklen_t)sizeof(struct sockaddr_in));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = sendto(fdSuccess, NULL, strlen(SRV_MSG), 0, NULL, (socklen_t)sizeof(struct sockaddr_in));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = recv(fdFail, NULL, sizeof(SRV_MSG), 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = recv(fdSuccess, NULL, sizeof(SRV_MSG), 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = recvfrom(fdFail, NULL, sizeof(SRV_MSG), 0, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = recvfrom(fdSuccess, NULL, sizeof(SRV_MSG), 0, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = setsockopt(fdFail, SOL_SOCKET, SO_RCVTIMEO, NULL, (socklen_t)sizeof(struct timeval));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = setsockopt(fdSuccess, SOL_SOCKET, SO_RCVTIMEO, NULL, (socklen_t)sizeof(struct timeval));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = getsockopt(fdFail, SOL_SOCKET, SO_RCVTIMEO, NULL, (socklen_t*)sizeof(struct timeval));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = getsockopt(fdSuccess, SOL_SOCKET, SO_RCVTIMEO, NULL, (socklen_t*)sizeof(struct timeval));
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = sendmsg(fdFail, NULL, 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = sendmsg(fdSuccess, NULL, 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = listen(fdFail, 0);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = listen(fdSuccess, -1);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = select(fdFail, NULL, NULL, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = shutdown(fdFail, SHUT_RD);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);
    ret = shutdown(fdSuccess, -1);
    TEST_ASSERT_EQUAL_INT(ret, LWIP_TEST_FAIL);

    ret = lwip_close(fdSuccess);
    TEST_ASSERT_EQUAL_INT(ret, 0);
}

RUN_TEST_SUITE(LwipFuncTestSuite);