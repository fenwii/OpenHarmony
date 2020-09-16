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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include "log.h"
#include "utils.h"
#include "KernelConstants.h"

using namespace testing::ext;

class FifoTest : public::testing::Test {
};

/**
 * @tc.number   SUB_KERNEL_IPC_FIFO_0100
 * @tc.name     basic function test : hello world
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FifoTest, testHelloWorld, TestSize.Level0)
{
    const char fifoPath[] = "/dev/xtsTestFifo";
    char buffer[80];
    int fd;
    char sentence[] = "Hello World";
    unlink(fifoPath);

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "> parent: fork : error";
    if (pid == 0) {
        Msleep(20);
        fd = open(fifoPath, O_WRONLY);
        write(fd, sentence, sizeof(sentence));
        LOG("> child: write: %s", sentence);
        close(fd);
        exit(0);
    }
    // parent
    int ret = mkfifo(fifoPath, 0666);
    EXPECT_EQ(ret, 0) << "> parent: mkfifo errno = " << errno;
    fd = open(fifoPath, O_RDONLY);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    EXPECT_NE(read(fd, buffer, sizeof(buffer)), -1) << "> read errno = " << errno;
    EXPECT_STREQ(sentence, buffer) << "> parent: read = " << buffer;
    LOG("> parent: read: %s", buffer);
    close(fd);

    Msleep(100);
    EXPECT_NE(remove(fifoPath), -1) << "> remove errno = " << errno;
    AssertProcExitedOK(pid);
}

/**
 * @tc.number   SUB_KERNEL_IPC_FIFO_0700
 * @tc.name     mkfifo() Duplicate creation and delete
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FifoTest, testFifoAddDelete, TestSize.Level0)
{
    char fifoPath[50];
    const int loopNum = 32;

    for (int i = 0; i < loopNum; i++) {
        sprintf(fifoPath, "/dev/xtsTestFifo_%d", i);
        unlink(fifoPath);

        LOG("> Create fifo %d", i);
        ASSERT_EQ(mkfifo(fifoPath, 0666), 0) << "> mkfifo errno = " << errno;

        LOG("> Delete fifo %d", i);
        EXPECT_NE(remove(fifoPath), -1) << "> remove errno = " << errno;
    }
}

/**
 * @tc.number   SUB_KERNEL_IPC_FIFO_0800
 * @tc.name     test O_NONBLOCK
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FifoTest, testFifoNonblack, TestSize.Level1)
{
    const int arrSize = MAX_PIPE_BUFFER + 1000;
    const char fifoPath[] = "/dev/xtsTestFifo";
    int fd;
    int tmpInt;
    char buffer[80];
    char testBuffer[arrSize];
    memset(testBuffer, '1', sizeof(testBuffer));

    unlink(fifoPath);
    int ret = mkfifo(fifoPath, 0666);
    EXPECT_EQ(ret, 0) << "> parent: mkfifo errno = " << errno;

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "> parent : fork : error";
    if (pid == 0) {
        char readBuffer[arrSize];
        memset(readBuffer, 0, sizeof(readBuffer));
        fd = open(fifoPath, O_RDONLY);
        if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
            LOG("> fcntl errno = %d", errno);
        }
        Msleep(60);
        tmpInt = read(fd, readBuffer, arrSize);
        if (tmpInt != MAX_PIPE_BUFFER) {
            LOG("> child: tmpInt = %d", tmpInt);
            LOG("> child: errno = %d", errno);
            close(fd);
            exit(1);
        }
        if (strncmp(testBuffer, readBuffer, MAX_PIPE_BUFFER) != 0) {
            close(fd);
            exit(1);
        }
        close(fd);
        exit(0);
    }
    // parent
    char writeBuffer[arrSize];
    memset(writeBuffer, '1', sizeof(writeBuffer));
    fd = open(fifoPath, O_WRONLY);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    EXPECT_NE(fcntl(fd, F_SETFL, O_NONBLOCK), -1) << "> fcntl errno = " << errno;
    Msleep(30);
    tmpInt = write(fd, writeBuffer, arrSize);
    EXPECT_EQ(tmpInt, MAX_PIPE_BUFFER) << "> parent: errno = " <<errno;
    LOG("> parent: write num = %d", tmpInt);
    close(fd);

    Msleep(100);
    EXPECT_NE(remove(fifoPath), -1) << "> remove errno = " << errno;
    AssertProcExitedOK(pid);
}
