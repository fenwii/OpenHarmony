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

#include "IpcMqTest.h"
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "log.h"
#include "utils.h"
#include "KernelConstants.h"

using namespace testing::ext;

/**
 * @tc.number SUB_KERNEL_IPC_MQ_OPEN_0100
 * @tc.name   mq_open function errno for EEXIST test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOpenEEXIST, TestSize.Level2)
{
    char qName[MQ_NAME_LEN];
    mqd_t queue, queueOther;

    sprintf(qName, "testMqOpenEEXIST_%d", GetRandom(10000));
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    queueOther = mq_open(qName, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, NULL);
    EXPECT_TRUE(queueOther == (mqd_t)-1) << "ERROR: mq_open() != (mqd_t)-1, queueOther = " << queueOther;
    EXPECT_TRUE(errno == EEXIST) << "ERROR: errno != EEXIST" << \
            " errno = " << errno << " strerror(errno) = " << strerror(errno);
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_OPEN_0200
 * @tc.name   mq_open function errno for EINVAL test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOpenEINVAL, TestSize.Level2)
{
    int i;
    mqd_t queue;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN];
    const int max = 65535;

    sprintf(qName, "testMqOpenEINVAL_%d", GetRandom(10000));

    for (i = 0; i<6; i++) {
        switch (i) {
            case 0:
                attr.mq_msgsize = -1;
                attr.mq_maxmsg = max;
                break;
            case 1:
                /* attr.mq_msgsize > USHRT_MAX - 4 */
                attr.mq_msgsize = max;
                attr.mq_maxmsg = max;
                break;
            case 2:
                attr.mq_msgsize = 10;
                attr.mq_maxmsg = -1;
                break;
            case 3:
                attr.mq_msgsize = 10;
                attr.mq_maxmsg = max + 1;
                break;

            case 4:
                attr.mq_msgsize = 0;
                attr.mq_maxmsg = 16;
                break;

            case 5:
                attr.mq_msgsize = 64;
                attr.mq_maxmsg = 0;
                break;
        }

        queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
        EXPECT_TRUE(queue == (mqd_t)-1) << "ERROR: mq_open() != (mqd_t)-1, i = " << i;

        if (queue != (mqd_t)-1) {
            mq_close(queue);
            mq_unlink(qName);
        }

        /* if NOT call mq_close & mq_unlink then errno == ENOENT */
        EXPECT_TRUE(errno == EINVAL) << "errno != EINVAL, errno = " << errno << " i = " << i << " qName = " << qName;
    }

    for (i=0; i<MQ_NAME_LEN; i++) {
        qName[i] = 0;
    }
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    EXPECT_TRUE(errno == EINVAL) << "errno != EINVAL, errno = " << errno << " i = " << i << " qName = " << qName;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_OPEN_0300
 * @tc.name   mq_open function errno for ENAMETOOLONG test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOpenENAMETOOLONG, TestSize.Level2)
{
    char qName[MAX_MQ_NAME_LEN + 10];
    mqd_t queue;
    int i;

    for (i=0; i<MAX_MQ_NAME_LEN + 5; i++) {
        qName[i] = '8';
    }
    qName[i] = '\0';

    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
    EXPECT_TRUE(queue == (mqd_t)-1) << "ERROR: mq_open() != (mqd_t)-1 ";

    if (queue != (mqd_t)-1) {
        mq_close(queue);
        mq_unlink(qName);
    }

    ASSERT_TRUE(errno == ENAMETOOLONG) << "errno != ENAMETOOLONG, errno = " << errno;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_OPEN_0400
 * @tc.name   mq_open function errno for ENOENT test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOpenENOENT, TestSize.Level3)
{
    mqd_t queue;
    char qName[MQ_NAME_LEN];

    sprintf(qName, "testMqOpenENOENT_%d", GetRandom(10000));
    queue = mq_open(qName, O_RDWR, S_IRUSR | S_IWUSR, NULL);
    EXPECT_TRUE(queue == (mqd_t)-1) << "ERROR: mq_open() != (mqd_t)-1 ";

    if (queue != (mqd_t)-1) {
        mq_close(queue);
        mq_unlink(qName);
    }
    ASSERT_TRUE(errno == ENOENT) << "errno != ENOENT, errno = " << errno;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_OPEN_0500
 * @tc.name   mq_open function errno for ENFILE test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOpenENFILE, TestSize.Level3)
{
    char qName[MAX_MQ_NUMBER + 1][30];
    mqd_t queue[MAX_MQ_NUMBER + 1];
    int i, failure = 0, flag = 0;

    for (i=0; i<MAX_MQ_NUMBER + 1; i++) {
        sprintf(qName[i], "testMqOpenENFILE_%d", i);
    }

    for (i=0; i<MAX_MQ_NUMBER; i++) {
        queue[i] = mq_open(qName[i], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);

        if (queue[i] == (mqd_t)-1) {
            flag = 1;
            LOG("break: i = %d", i);
            break;
        }

        EXPECT_TRUE(queue[i] != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1, i = " << \
                        i << " errno = " << errno << " strerror(errno) = " << strerror(errno);
    }

    LOG("func: i = %d", i);
    if (flag == 0) {
        queue[i] = mq_open(qName[i], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
    }
    EXPECT_TRUE(queue[i] == (mqd_t)-1) << "ERROR: mq_open() != (mqd_t)-1, i = " << i << \
                " queue = " << queue[i] << " errno = " << errno << " strerror(errno) = " << strerror(errno);
    EXPECT_TRUE(errno == ENFILE) << "ERROR: errno != ENFILE, i = " << \
                        i << " errno = " << errno << " strerror(errno) = " << strerror(errno);

    for (i=0; i<MAX_MQ_NUMBER+1; i++) {
        mq_close(queue[i]);
        mq_unlink(qName[i]);
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_OPEN_0600
 * @tc.name   mq_open function errno for ENOSPC test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOpenENOSPC, TestSize.Level3)
{
    mqd_t queue;
    struct mq_attr setAttr;
    char qName[MQ_NAME_LEN];

    sprintf(qName, "testMqOpenENOSPC_%d", GetRandom(10000));
    setAttr.mq_msgsize = MAX_MQ_MSG_SIZE + 1;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    EXPECT_TRUE(queue == (mqd_t)-1) << "ERROR: mq_open() != (mqd_t)-1 ";

    if (queue != (mqd_t)-1) {
        mq_close(queue);
        mq_unlink(qName);
    }
    ASSERT_TRUE(errno == ENOSPC) << "errno != ENOSPC, errno = " << errno;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_CLOSE_0100
 * @tc.name   mq_close function errno for EBADF test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqCloseEBADF, TestSize.Level2)
{
    ASSERT_TRUE(mq_close(NULL) == -1) << "ERROR: mq_close() != -1";
    ASSERT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_SEND_0100
 * @tc.name   mq_send function errno for EAGAIN test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqSendEAGAIN, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN];

    sprintf(qName, "testMqSendEAGAIN_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = 1;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, 0) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, 0) == -1) << "ERROR: mq_send() != -1";
    EXPECT_TRUE(errno == EAGAIN) << "ERROR: errno != EAGAIN, errno = " << errno << " EAGAIN = " << EAGAIN;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_SEND_0200
 * @tc.name   mq_send function errno for EBADF and EMSGSIZE test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqSendEBADFEMSGSIZE, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN];

    sprintf(qName, "testMqSendEAGAIN_%d", GetRandom(10000));
    attr.mq_msgsize = 1;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(NULL, MQ_MSG, 1, MQ_MSG_PRIO) == -1) << "ERROR: mq_send() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == -1) << "ERROR: mq_send() != -1";
    EXPECT_TRUE(errno == EMSGSIZE) << "ERROR: errno != EMSGSIZE, errno = " << errno << " EMSGSIZE = " << EMSGSIZE;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";

    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDONLY | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == -1) << "ERROR: mq_send() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    attr.mq_flags |= O_NONBLOCK;
    EXPECT_TRUE(mq_setattr(queue, &attr, NULL) == 0) << "ERROR: mq_setattr() != 0";
    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == -1) << "ERROR: mq_send() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_SEND_0300
 * @tc.name   mq_send function errno for EINVAL  test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqSendEINVAL, TestSize.Level3)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN];

    sprintf(qName, "testMqSendEINVAL_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, 0, MQ_MSG_PRIO) == -1) << "ERROR: mq_send() != -1";
    EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " << errno << " EINVAL = " << EINVAL;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_RECEIVE_0100
 * @tc.name   mq_receive function errno for EAGAIN test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqReceiveEAGAIN, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr, getAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqReceiveEAGAIN_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << "ERROR: strncmp() != 0, sent != received: sent = "\
                                                        << MQ_MSG << ", received = " << rMsg;
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) == -1) << "ERROR: mq_receive() != -1";
    EXPECT_TRUE(errno == EAGAIN) << "ERROR: errno != EAGAIN, errno = " << errno << " EAGAIN = " << EAGAIN;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_RECEIVE_0200
 * @tc.name   mq_receive function errno for EBADF and EMSGSIZE test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqReceiveEBADFEMSGSIZE, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr, getAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN], rMsgErr[1];

    sprintf(qName, "testMqReceiveEAGAIN_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << "ERROR: strncmp() != 0, sent != received: sent = "\
                                                        << MQ_MSG << ", received = " << rMsg;

    EXPECT_TRUE(mq_receive(NULL, rMsg, getAttr.mq_msgsize, &prio) == -1) << "ERROR: mq_receive() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(mq_receive(queue, rMsgErr, sizeof(rMsgErr), &prio) == -1) << "ERROR: mq_receive() != -1";
    EXPECT_TRUE(errno == EMSGSIZE) << "ERROR: errno != EMSGSIZE, errno = " << errno << " EMSGSIZE = " << EMSGSIZE;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";

    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_WRONLY | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) == -1) << "ERROR: mq_receive() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    attr.mq_flags |= O_NONBLOCK;
    EXPECT_TRUE(mq_setattr(queue, &attr, NULL) == 0) << "ERROR: mq_setattr() != 0";
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) == -1) << "ERROR: mq_receive() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_RECEIVE_0300
 * @tc.name   mq_receive function errno for EINVAL test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqReceiveEINVAL, TestSize.Level3)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr, getAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqReceiveEINVAL_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_receive(queue, rMsg, 0, &prio) == -1) << "ERROR: mq_receive() != -1";
    EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " << errno << " EINVAL = " << EINVAL;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMESEND_0100
 * @tc.name   mq_timedsend function errno for EAGAIN and EBADF test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedSendEAGAINEBADF, TestSize.Level2)
{
    mqd_t queue;
    struct timespec ts;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedSendEAGAIN_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = 1;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    ts.tv_sec = time(NULL) + 1;
    ts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == 0) << "ERROR: mq_timedsend() != 0";

    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1) << "ERROR: mq_timedsend() != 0";
    EXPECT_TRUE(errno == EAGAIN) << "ERROR: errno != EAGAIN, errno = " << errno << " EAGAIN = " << EAGAIN;

    EXPECT_TRUE(mq_timedsend(NULL, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1) << "ERROR: mq_timedsend() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";

    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDONLY | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1) << "ERROR: mq_timedsend() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    attr.mq_flags |= O_NONBLOCK;
    EXPECT_TRUE(mq_setattr(queue, &attr, NULL) == 0) << "ERROR: mq_setattr() != 0";
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1) << "ERROR: mq_timedsend() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMESEND_0200
 * @tc.name   mq_timedsend function errno for EINVAL test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedSendEINVAL, TestSize.Level2)
{
    mqd_t queue;
    int i;
    struct timespec ts;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN], rMsg[MQ_NAME_LEN];

    sprintf(qName, "testMqTimedSendEINVAL_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    for (i = 0; i<3; i++) {
        switch (i) {
            case 0:
                ts.tv_sec = -1;
                ts.tv_nsec = 0;
                break;
            case 1:
                ts.tv_sec = time(NULL) + 1;
                ts.tv_nsec = -1;
                break;
            case 2:
                ts.tv_sec = time(NULL) + 1;
                ts.tv_nsec = 1000000000UL + 1UL;
                break;
        }

        EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1)
            << "ERROR: mq_timedsend() != -1, i = " << i;
        EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " 
            << errno << " EINVAL = " << EINVAL << " i = " << i;
    }

    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, 0, MQ_MSG_PRIO, &ts) == -1) << \
                                                        "ERROR: mq_timedsend() != -1";
    EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " << \
                                        errno << " EINVAL = " << EINVAL;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMESEND_0300
 * @tc.name   mq_timedsend function errno for EMSGSIZE test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedSendEMSGSIZE, TestSize.Level3)
{
    mqd_t queue;
    struct timespec ts;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedSendEMSGSIZE_%d", GetRandom(10000));
    attr.mq_msgsize = 1;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    ts.tv_sec = time(NULL) + 1;
    ts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1) << "ERROR: mq_timedsend() != -1";
    EXPECT_TRUE(errno == EMSGSIZE) << "ERROR: errno != EMSGSIZE, errno = " << errno << " EMSGSIZE = " << EMSGSIZE;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMESEND_0400
 * @tc.name   mq_timedsend function errno for ETIMEDOUT test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedSendETIMEDOUT, TestSize.Level3)
{
    mqd_t queue;
    struct timespec ts;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedSendETIMEDOUT_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = 1;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    ts.tv_sec = time(NULL) + 1;
    ts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == 0) << "ERROR: mq_timedsend() != 0";

    ts.tv_sec = 0;
    ts.tv_nsec = 100;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &ts) == -1) << "ERROR: mq_timedsend() != -1";
    EXPECT_TRUE(errno == ETIMEDOUT) << "ERROR: errno != ETIMEDOUT, errno = " << errno << " ETIMEDOUT = " << ETIMEDOUT;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMERECEIVE_0100
 * @tc.name   mq_timedreceive function errno for EAGAIN and EBADF test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedReceiveEAGAINEBADF, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec ts;
    struct mq_attr attr, getAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedReceiveEAGAIN_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    ts.tv_sec = time(NULL) + 1;
    ts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &ts) == -1) << "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == EAGAIN) << "ERROR: errno != EAGAIN, errno = " << errno << " EAGAIN = " << EAGAIN;

    EXPECT_TRUE(mq_timedreceive(NULL, rMsg, getAttr.mq_msgsize, &prio, &ts) == -1) << "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";

    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_WRONLY | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_timedreceive(NULL, rMsg, getAttr.mq_msgsize, &prio, &ts) == -1) << "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    attr.mq_flags |= O_NONBLOCK;
    EXPECT_TRUE(mq_setattr(queue, &attr, NULL) == 0) << "ERROR: mq_setattr() != 0";
    EXPECT_TRUE(mq_timedreceive(NULL, rMsg, getAttr.mq_msgsize, &prio, &ts) == -1) << "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMERECEIVE_0200
 * @tc.name   mq_timedreceive function errno for EINVAL test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedReceiveEINVAL, TestSize.Level2)
{
    mqd_t queue;
    int i;
    unsigned int prio;
    struct timespec ts;
    struct mq_attr attr, getAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedReceiveEINVAL_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    for (i = 0; i<3; i++) {
        switch (i) {
            case 0:
                ts.tv_sec = -1;
                ts.tv_nsec = 0;
                break;
            case 1:
                ts.tv_sec = time(NULL) + 1;
                ts.tv_nsec = -1;
                break;
            case 2:
                ts.tv_sec = time(NULL) + 1;
                ts.tv_nsec = 1000000000UL + 1UL;
                break;
        }

        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &ts) == -1) << \
                                                        "ERROR: mq_timedreceive() != -1, i = " << i;
        EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " << \
                                        errno << " EINVAL = " << EINVAL << " i = " << i;
    }

    EXPECT_TRUE(mq_timedreceive(queue, rMsg, 0, &prio, &ts) == -1) << \
                                                        "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " << \
                                        errno << " EINVAL = " << EINVAL;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMERECEIVE_0300
 * @tc.name   mq_timedreceive function errno for ETIMEDOUT test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedReceiveETIMEDOUT, TestSize.Level3)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec ts;
    struct mq_attr attr, getAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];
    const char *sMsg = "MessageToSend";

    sprintf(qName, "testMqTimedReceiveETIMEDOUT_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    ts.tv_sec = 0;
    ts.tv_nsec = 100;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &ts) == -1) << "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == ETIMEDOUT) << "ERROR: errno != ETIMEDOUT, errno = " << errno << " ETIMEDOUT = " << ETIMEDOUT;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_TIMERECEIVE_0400
 * @tc.name   mq_timedreceive function errno for EMSGSIZE test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedReceiveEMSGSIZE, TestSize.Level3)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec ts;
    struct mq_attr attr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedReceiveEMSGSIZE_%d", GetRandom(10000));
    attr.mq_msgsize = MQ_MSG_SIZE;
    attr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    ts.tv_sec = time(NULL) + 1;
    ts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, 1, &prio, &ts) == -1) << "ERROR: mq_timedreceive() != -1";
    EXPECT_TRUE(errno == EMSGSIZE) << "ERROR: errno != EMSGSIZE, errno = " << errno << " EMSGSIZE = " << EMSGSIZE;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_UNLINK_0100
 * @tc.name   mq_unlink function errno for ENAMETOOLONG test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqUnlinkENAMETOOLONG, TestSize.Level2)
{
    char qName[MAX_MQ_NAME_LEN + 10];
    mqd_t queue;
    int i;

    for (i=0; i<MAX_MQ_NAME_LEN + 5; i++) {
        qName[i] = '8';
    }
    qName[i] = '\0';

    ASSERT_TRUE(mq_unlink(qName) == -1) << "ERROR: mq_unlink() != -1";
    ASSERT_TRUE(errno == ENAMETOOLONG) << "ERROR: errno != ENAMETOOLONG";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_UNLINK_0200
 * @tc.name   mq_unlink function errno for ENOENT test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqUnlinkENOENT, TestSize.Level2)
{
    char qName[MQ_NAME_LEN] = "/mq_file-does-not-exit";

    ASSERT_TRUE(mq_unlink(qName) == -1) << "ERROR: mq_unlink() != -1";
    ASSERT_TRUE(errno == ENOENT) << "ERROR: errno != ENOENT";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_UNLINK_0300
 * @tc.name   mq_unlink function errno for EINVAL test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqUnlinkEINVAL, TestSize.Level3)
{
    ASSERT_TRUE(mq_unlink("") == -1) << "ERROR: mq_unlink() != -1";
    ASSERT_TRUE(errno == EINVAL) << "ERROR: errno != ENOENT";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_GETATTR_0100
 * @tc.name   mq_getattr function errno for EBAD and EINVALF test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqGetAttrEBADFEINVAL, TestSize.Level2)
{
    int ret;
    mqd_t queue;
    struct mq_attr mqstat;
    char qName[MQ_NAME_LEN];

    memset(&mqstat, 0, sizeof(mqstat));

    sprintf(qName, "testMqSendEINVAL_%d", GetRandom(10000));
    queue = mq_open(qName, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, NULL);

    ret = mq_getattr(NULL, &mqstat);
    EXPECT_TRUE(ret == -1) << "ERROR: mq_getattr() != -1, ret = " << ret;
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    ret = mq_getattr(queue, NULL);
    EXPECT_TRUE(ret == -1) << "ERROR: mq_getattr() != -1, ret = " << ret;
    EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL , errno = " << errno << " EINVAL  = " << EINVAL;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_SETATTR_0100
 * @tc.name   mq_receive function errno for EBADF and EINVAL test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqSetAttrEBADFEINVAL, TestSize.Level2)
{
    char qName[MQ_NAME_LEN];
    mqd_t queue;
    struct mq_attr gMqstat, sMqstat;

    sprintf(qName, "testMqSetAttrEBADFEINVAL_%d", GetRandom(10000));
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 0);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    memset(&gMqstat, 0, sizeof(gMqstat));
    memset(&sMqstat, 0, sizeof(sMqstat));
    EXPECT_TRUE(mq_getattr(queue, &gMqstat) == 0) << "ERROR: mq_getattr() != 0";

    sMqstat.mq_flags |= O_NONBLOCK;
    EXPECT_TRUE(mq_setattr(queue, &sMqstat, NULL) == 0) << "ERROR: mq_setattr() != 0";
    EXPECT_TRUE(mq_getattr(queue, &gMqstat) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(gMqstat.mq_flags != sMqstat.mq_flags) << "ERROR: gMqstat != sMqstat, gMqstat.mq_flags = " \
                                                     << gMqstat.mq_flags << "sMqstat.mq_flags = " << sMqstat.mq_flags;

    EXPECT_TRUE(mq_setattr(NULL, &sMqstat, NULL) == -1) << "ERROR: mq_setattr() != -1";
    EXPECT_TRUE(errno == EBADF) << "ERROR: errno != EBADF, errno = " << errno << " EBADF = " << EBADF;

    EXPECT_TRUE(mq_setattr(queue, NULL, NULL) == -1) << "ERROR: mq_setattr() != -1";
    EXPECT_TRUE(errno == EINVAL) << "ERROR: errno != EINVAL, errno = " << errno << " EINVAL = " << EINVAL;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}


