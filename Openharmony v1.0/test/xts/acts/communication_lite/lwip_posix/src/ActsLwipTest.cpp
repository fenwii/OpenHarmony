/**
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/tcp.h"
#include "securec.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>

using namespace std;
using namespace testing::ext;

static const int STACK_PORT = 2277;
static const int PEER_PORT = 2277;
static const int BUF_SIZE = (1024 * 8);
static const int LWIP_TEST_SUCCESS = 0;
static const int LWIP_TEST_FAIL = -1;
static char g_buf[BUF_SIZE + 1] = {0};
static const char* g_udpMsg = "Hi, I am UDP";
static const char* g_srvMsg = "Hi, I am TCP server";
static const char* g_cliMsg = "Hi, I am TCP client";
static const char* g_localHost = "127.0.0.1";

static pthread_barrier_t g_barrier;
#define WAIT() pthread_barrier_wait(&g_barrier)

class ActsLwipTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void) {}
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp() {}
    // Testcase teardown
    virtual void TearDown() {}
};

static void* SampleTcpServerTask(void *p)
{
    int ret;
    int sfd = -1;
    int lsfd = -1;
    static char buf[BUF_SIZE + 1] = {0};
    struct msghdr msg = {0};
    struct iovec iov[2] = {};
    struct sockaddr_in srvAddr = {0};
    struct sockaddr_in clnAddr = {0};
    socklen_t clnAddrLen = sizeof(clnAddr);

    lsfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("[tcp server]create socket[server]\n");
    EXPECT_NE(lsfd, LWIP_TEST_FAIL);

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(g_localHost);
    srvAddr.sin_port = htons(STACK_PORT);
    ret = ::bind(lsfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr));
    printf("[tcp server]bind %s:%d,ret=%d\n", inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port), ret);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = listen(lsfd, 0);
    printf("[tcp server]listen,ret=%d\n", ret);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    WAIT();
    sfd = accept(lsfd, (struct sockaddr*)&clnAddr, &clnAddrLen);
    printf("[tcp server]accept <%s:%d>\n", inet_ntoa(clnAddr.sin_addr), ntohs(clnAddr.sin_port));
    EXPECT_NE(sfd, LWIP_TEST_FAIL);

    int srvMsgLen = strlen(g_srvMsg);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, g_srvMsg);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    ret = send(sfd, buf, srvMsgLen, 0);
    printf("[tcp server]send, ret=%d\n", ret);
    EXPECT_EQ(ret, srvMsgLen);

    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recv(sfd, buf, sizeof(buf), 0);
    printf("[tcp server]recv, ret=%d\n", ret);
    EXPECT_EQ(ret, strlen(g_cliMsg));

    WAIT();
    int len = 2;
    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(g_localHost);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, g_srvMsg);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
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
    EXPECT_EQ(ret, len * srvMsgLen);

    WAIT();
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    memset_s(&msg, sizeof(msg), 0, sizeof(msg));
    msg.msg_name = &clnAddr;
    msg.msg_namelen = sizeof(clnAddr);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);
    ret = recvmsg(sfd, &msg, 0);
    printf("[tcp server]recvmsg on socket %d: %d\n", sfd, ret);
    EXPECT_EQ(ret, len * strlen(g_cliMsg));

    ret = shutdown(sfd, SHUT_RDWR);
    printf("[tcp server]shutdown, ret=%d\n", ret);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = close(sfd);
    EXPECT_NE(ret, LWIP_TEST_FAIL);
    ret = close(lsfd);
    EXPECT_NE(ret, LWIP_TEST_FAIL);
    return nullptr;
}

static void* SampleTcpClientTask(void *p)
{
    int ret;
    int sfd = -1;
    struct msghdr msg = {0};
    struct iovec iov[2] = {};
    struct sockaddr addr;
    socklen_t addrLen = sizeof(addr);
    struct sockaddr_in srvAddr = {0};
    struct sockaddr_in clnAddr = {0};
    static char buf[BUF_SIZE + 1] = {0};

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("[tcp client]create socket[client]\n");
    EXPECT_NE(sfd, LWIP_TEST_FAIL);

    WAIT();
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(g_localHost);
    srvAddr.sin_port = htons(PEER_PORT);
    ret = connect(sfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr));
    printf("[tcp client]connect %s:%d, ret=%d\n", inet_ntoa(srvAddr.sin_addr), ntohs(srvAddr.sin_port), ret);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = getpeername(sfd, &addr, &addrLen);
    printf("[tcp client]getpeername %s:%d, ret=%d\n", inet_ntoa(((struct sockaddr_in*)&addr)->sin_addr),
        ntohs(((struct sockaddr_in*)&addr)->sin_port), ret);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    EXPECT_EQ(addrLen, sizeof(struct sockaddr_in));
    EXPECT_EQ(((struct sockaddr_in*)&addr)->sin_addr.s_addr, inet_addr(g_localHost));

    ret = getsockname(sfd, &addr, &addrLen);
    printf("[tcp client]getsockname %s:%d, ret=%d\n", inet_ntoa(((struct sockaddr_in*)&addr)->sin_addr),
        ntohs(((struct sockaddr_in*)&addr)->sin_port), ret);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    EXPECT_EQ(addrLen, sizeof(struct sockaddr_in));
    EXPECT_EQ(((struct sockaddr_in*)&addr)->sin_addr.s_addr, inet_addr(g_localHost));

    int cliMsgLen = strlen(g_cliMsg);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, g_cliMsg);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    ret = send(sfd, buf, cliMsgLen, 0);
    printf("[tcp client]send, ret=%d\n", ret);
    EXPECT_EQ(ret, cliMsgLen);

    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recv(sfd, buf, sizeof(buf), 0);
    printf("[tcp client]recv,ret=%d\n", ret);
    EXPECT_EQ(ret, strlen(g_srvMsg));

    WAIT();
    int len = 2;
    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(g_localHost);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(buf, BUF_SIZE, g_cliMsg);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
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
    EXPECT_EQ(ret, len * cliMsgLen);

    WAIT();
    memset_s(buf, BUF_SIZE, 0, BUF_SIZE);
    memset_s(&msg, sizeof(msg), 0, sizeof(msg));
    msg.msg_name = &clnAddr;
    msg.msg_namelen = sizeof(clnAddr);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);
    ret = recvmsg(sfd, &msg, 0);
    printf("[tcp client]recvmsg, ret=%d\n", ret);
    EXPECT_EQ(ret, len * strlen(g_srvMsg));

    ret = shutdown(sfd, SHUT_RDWR);
    printf("[tcp client]shutdown, ret=%d\n", ret);
    EXPECT_EQ(ret, 0);

    ret = close(sfd);
    EXPECT_NE(ret, LWIP_TEST_FAIL);
    return nullptr;
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0100
 * @tc.name      : test upd
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ActsLwipTest, testUdp, TestSize.Level2)
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
    EXPECT_NE(sfd, LWIP_TEST_FAIL);

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = inet_addr(g_localHost);
    srvAddr.sin_port = htons(STACK_PORT);
    ret = ::bind(sfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr));
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(g_localHost);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(g_buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(g_buf, BUF_SIZE, g_udpMsg);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    ret = sendto(sfd, g_buf, strlen(g_udpMsg), 0, (struct sockaddr*)&clnAddr, (socklen_t)sizeof(clnAddr));
    EXPECT_NE(ret, LWIP_TEST_FAIL);

    memset_s(g_buf, BUF_SIZE, 0, BUF_SIZE);
    ret = recvfrom(sfd, g_buf, sizeof(g_buf), 0, (struct sockaddr*)&clnAddr, &clnAddrLen);
    EXPECT_EQ(ret, strlen(g_udpMsg));

    clnAddr.sin_family = AF_INET;
    clnAddr.sin_addr.s_addr = inet_addr(g_localHost);
    clnAddr.sin_port = htons(PEER_PORT);
    memset_s(g_buf, BUF_SIZE, 0, BUF_SIZE);
    ret = strcpy_s(g_buf, BUF_SIZE, g_udpMsg);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    msg.msg_name = &clnAddr;
    msg.msg_namelen = sizeof(clnAddr);
    msg.msg_iov = iov;
    msg.msg_iovlen = len;
    iov[0].iov_base = g_buf;
    iov[0].iov_len = strlen(g_udpMsg);
    iov[1].iov_base = g_buf;
    iov[1].iov_len = strlen(g_udpMsg);
    ret = sendmsg(sfd, &msg, 0);
    EXPECT_EQ(ret, len*strlen(g_udpMsg));

    ret = close(sfd);
    EXPECT_NE(ret, LWIP_TEST_FAIL);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0200
 * @tc.name      : test socket operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ActsLwipTest, testSocketOpt, TestSize.Level2)
{
    int ret;
    struct timeval timeout;
    socklen_t len;

    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    EXPECT_NE(fd, LWIP_TEST_FAIL);

    int error = -1;
    len = sizeof(error);
    ret = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    EXPECT_EQ(error, LWIP_TEST_SUCCESS);
    len = sizeof(timeout);
    ret = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, &len);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    timeout.tv_sec = 1000;
    len = sizeof(timeout);
    ret = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    memset_s(&timeout, len, 0, len);
    ret = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, &len);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    error = -1;
    len = sizeof(error);
    ret = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    EXPECT_EQ(error, LWIP_TEST_SUCCESS);

    int flag = 1;
    ret = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = close(fd);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0300
 * @tc.name      : test inet conversion
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ActsLwipTest, testInetConv, TestSize.Level2)
{
    int ret;
    struct in_addr in;
    ret = inet_pton(AF_INET, "300.10.10.10", &in);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = inet_pton(AF_INET, "10.11.12.13", &in);
    EXPECT_EQ(ret, 1);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    EXPECT_EQ(in.s_addr, 0x0d0c0b0a);
#else
    EXPECT_EQ(in.s_addr, 0x0a0b0c0d);
#endif

    const char *p = inet_ntoa(in);
    EXPECT_EQ(strcmp(p, "10.11.12.13"), 0);

    int bufLen = 32;
    char buf[bufLen];
    p = inet_ntop(AF_INET, &in, buf, sizeof(buf));
    EXPECT_EQ(strcmp(p, "10.11.12.13"), 0);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0400
 * @tc.name      : test tcp
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ActsLwipTest, testTcp, TestSize.Level2)
{
    int ret;
    pthread_t srv;
    pthread_t cli;

    ret = pthread_barrier_init(&g_barrier, 0, 2);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = pthread_create(&srv, nullptr, SampleTcpServerTask, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    ret = pthread_create(&cli, nullptr, SampleTcpClientTask, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = pthread_join(cli, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
    ret = pthread_join(srv, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);

    ret = pthread_barrier_destroy(&g_barrier);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
}

/**
 * @tc.number    : SUB_COMMUNICATION_LWIP_SDK_0500
 * @tc.name      : test invalid parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ActsLwipTest, testInvalidParameter, TestSize.Level2)
{
    int ret;
    int fdFail = -1;
    int fdSuccess = -1;

    fdFail = socket(0, 0, 0);
    EXPECT_EQ(fdFail, LWIP_TEST_FAIL);
    fdSuccess = socket(AF_INET, SOCK_STREAM, 0);
    EXPECT_NE(fdSuccess, LWIP_TEST_FAIL);

    ret = ::bind(fdFail, nullptr, sizeof(struct sockaddr_in));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = ::bind(fdSuccess, nullptr, sizeof(struct sockaddr_in));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = connect(fdFail, nullptr, sizeof(struct sockaddr));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = connect(fdSuccess, nullptr, sizeof(struct sockaddr));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = accept(fdFail, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = accept(fdSuccess, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = getsockname(fdFail, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = getsockname(fdSuccess, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = getpeername(fdFail, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = getpeername(fdSuccess, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = send(fdFail, nullptr, strlen(g_srvMsg), 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = send(fdSuccess, nullptr, strlen(g_srvMsg), 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = sendto(fdFail, nullptr, strlen(g_srvMsg), 0, nullptr, (socklen_t)sizeof(struct sockaddr_in));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = sendto(fdSuccess, nullptr, strlen(g_srvMsg), 0, nullptr, (socklen_t)sizeof(struct sockaddr_in));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = recv(fdFail, nullptr, sizeof(g_srvMsg), 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = recv(fdSuccess, nullptr, sizeof(g_srvMsg), 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    struct msghdr msg = {0};
    ret = recvmsg(fdFail, &msg, 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = recvmsg(fdSuccess, &msg, 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = recvfrom(fdFail, nullptr, sizeof(g_srvMsg), 0, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = recvfrom(fdSuccess, nullptr, sizeof(g_srvMsg), 0, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = setsockopt(fdFail, SOL_SOCKET, SO_RCVTIMEO, nullptr, (socklen_t)sizeof(struct timeval));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = setsockopt(fdSuccess, SOL_SOCKET, SO_RCVTIMEO, nullptr, (socklen_t)sizeof(struct timeval));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = getsockopt(fdFail, SOL_SOCKET, SO_RCVTIMEO, nullptr, (socklen_t*)sizeof(struct timeval));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = getsockopt(fdSuccess, SOL_SOCKET, SO_RCVTIMEO, nullptr, (socklen_t*)sizeof(struct timeval));
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = sendmsg(fdFail, nullptr, 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = sendmsg(fdSuccess, nullptr, 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = listen(fdFail, 0);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = select(fdFail, nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = shutdown(fdFail, SHUT_RD);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);
    ret = shutdown(fdSuccess, -1);
    EXPECT_EQ(ret, LWIP_TEST_FAIL);

    ret = close(fdSuccess);
    EXPECT_EQ(ret, LWIP_TEST_SUCCESS);
}
