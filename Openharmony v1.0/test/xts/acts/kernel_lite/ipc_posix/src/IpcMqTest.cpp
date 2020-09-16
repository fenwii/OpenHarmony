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
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "log.h"
#include "utils.h"
#include "KernelConstants.h"

using namespace testing::ext;

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0100
 * @tc.name   mq_send and mq_receive function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqOneLevelCom, TestSize.Level0)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqOneLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";
    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_msgsize == MQ_MSG_SIZE) << "getAttr.mq_msgsize != MQ_MSG_SIZE, " << \
                                                      "getAttr.mq_msgsize = " << getAttr.mq_msgsize;
    EXPECT_TRUE(getAttr.mq_maxmsg == MQ_MAX_MSG) << "getAttr.mq_maxmsg != MQ_MAX_MSG, " << \
                                                    "getAttr.mq_maxmsg = " << getAttr.mq_maxmsg;

    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(prio == 0) << "ERROR: prio != 0, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << "sent != received: sent = " << \
                                                        MQ_MSG << ", received = " << rMsg;
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0200
 * @tc.name   mq_timedsend and mq_timedreceive function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedOneLevelCom, TestSize.Level1)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedOneLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    tts.tv_sec = time(NULL) + 1;
    tts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_msgsize == MQ_MSG_SIZE) << "getAttr.mq_msgsize != MQ_MSG_SIZE, " << \
                                                      "getAttr.mq_msgsize = " << getAttr.mq_msgsize;
    EXPECT_TRUE(getAttr.mq_maxmsg == MQ_MAX_MSG) << "getAttr.mq_maxmsg != MQ_MAX_MSG, " << \
                                                    "getAttr.mq_maxmsg = " << getAttr.mq_maxmsg;
    rts.tv_sec = time(NULL) + 1;
    rts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                            "ERROR: mq_timedreceive() == -1";
    EXPECT_TRUE(prio == 0) << "ERROR: prio != 0, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << "sent != received: sent = " << \
                                                            MQ_MSG << ", received = " << rMsg;
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0300
 * @tc.name   all send and all receive function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
 HWTEST_F(IpcMqTest, testMqAllOneLevelCom, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqAllOneLevelCom_%d", GetRandom(10000));

    memset(&getAttr, 0, sizeof(getAttr));
    memset(&setAttr, 0, sizeof(setAttr));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(mq_getattr(queue, &setAttr) == 0) << "ERROR: mq_getattr() != 0";
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    EXPECT_TRUE(mq_setattr(queue, &setAttr, NULL) == 0) << "ERROR: mq_setattr() != 0";
    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_msgsize == setAttr.mq_msgsize) << "ERROR: getAttr.mq_msgsize != setAttr.mq_msgsize," \
                " getAttr.mq_msgsize = " << getAttr.mq_msgsize << " setAttr.mq_msgsize = " << setAttr.mq_msgsize;
    EXPECT_TRUE(getAttr.mq_maxmsg == setAttr.mq_maxmsg) << "ERROR: getAttr.mq_maxmsg != setAttr.mq_maxmsg," \
                " getAttr.mq_maxmsg = " << getAttr.mq_maxmsg << " setAttr.mq_maxmsg = " << setAttr.mq_maxmsg;
    EXPECT_TRUE(getAttr.mq_curmsgs == 1) << \
                "ERROR: getAttr.mq_curmsgs != 1, getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;

    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << \
                                                    "ERROR: mq_receive() == -1";
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                        "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

    tts.tv_sec = time(NULL) + 1;
    tts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_msgsize == setAttr.mq_msgsize) << "ERROR: getAttr.mq_msgsize != setAttr.mq_msgsize";
    EXPECT_TRUE(getAttr.mq_maxmsg == setAttr.mq_maxmsg) << "ERROR: getAttr.mq_maxmsg != setAttr.mq_maxmsg";
    EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1";

    rts.tv_sec = time(NULL) + 1;
    rts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                        "ERROR: mq_timedreceive() == -1";
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0" << \
                                        " errno = " << errno << " strerror(errno) = " << strerror(errno);
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0400
 * @tc.name   mq_send and mq_receive function test in child and parent process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTwoLevelCom, TestSize.Level1)
{
    mqd_t queue;
    pid_t pid;
    unsigned int prio;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MAX_MQ_MSG_SIZE], sMsg[MAX_MQ_MSG_SIZE];

    for (int i=0; i<MAX_MQ_MSG_SIZE; i++) {
        sMsg[i] = 0x36;
        rMsg[i] = 0x00;
    }

    sprintf(qName, "testMqMaxLenTwoLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MAX_MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    pid = fork();
    if (pid < 0) {
        goto FINISH;
    } else if (pid == 0) {
        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
        EXPECT_TRUE(prio == 0) << "ERROR: prio != 0, prio = " << prio;
        EXPECT_TRUE(strncmp(sMsg, rMsg, MAX_MQ_MSG_SIZE) == 0) << \
                            "sent != received: sent = " << sMsg << ", received = " << rMsg;
        EXPECT_TRUE(mq_send(queue, sMsg, MAX_MQ_MSG_SIZE, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
        exit(0);
    } else {
        int status;
        EXPECT_TRUE(mq_send(queue, sMsg, MAX_MQ_MSG_SIZE, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";

        pid = waitpid(pid, &status, 0);
        EXPECT_TRUE(pid != 0) << "ERROR: pid == 0";
        EXPECT_TRUE(WIFEXITED(status) != 0) << "ERROR: WIFEXITED(status) == 0";
        EXPECT_TRUE(WEXITSTATUS(status) == 0) << "ERROR: WEXITSTATUS(status) != 0" \
                                              << ", WEXITSTATUS(status) = " << WEXITSTATUS(status);
        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
        EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
        EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
        EXPECT_TRUE(strncmp(sMsg, rMsg, MAX_MQ_MSG_SIZE) == 0) << \
                            "sent != received: sent = " << sMsg << ", received = " << rMsg;
    }

FINISH:
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0500
 * @tc.name   mq_timedsend and mq_timedreceive function test in child and parent process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedTwoLevelCom, TestSize.Level1)
{
    mqd_t queue;
    pid_t pid;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedTwoLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    pid = fork();
    if (pid < 0) {
        goto FINISH;
    } else if (pid == 0) {
        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        rts.tv_sec = time(NULL) + 3;
        rts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                            "ERROR: mq_timedreceive() == -1";
        EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != 0, prio = " << prio;
        EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

        tts.tv_sec = time(NULL) + 3;
        tts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";
        exit(0);
    } else {
        int status;
        tts.tv_sec = time(NULL) + 3;
        tts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";

        pid = waitpid(pid, &status, 0);
        EXPECT_TRUE(pid != 0) << "ERROR: pid == 0";
        EXPECT_TRUE(WIFEXITED(status) != 0) << "ERROR: WIFEXITED(status) == 0";
        EXPECT_TRUE(WEXITSTATUS(status) == 0) << "ERROR: WEXITSTATUS(status) != 0" \
                                              << ", WEXITSTATUS(status) = " << WEXITSTATUS(status);
        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
        rts.tv_sec = time(NULL) + 3;
        rts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                            "ERROR: mq_timedreceive() == -1";
        EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != 0, prio = " << prio;
        EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;
    }

FINISH:
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0600
 * @tc.name   all send and all receive function test in child and parent process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqAllTwoLevelCom, TestSize.Level1)
{
    mqd_t queue;
    pid_t pid;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqAllTwoLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    pid = fork();
    if (pid < 0) {
        goto FINISH;
    } else if (pid == 0) {
        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        rts.tv_sec = time(NULL) + 1;
        rts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                                "ERROR: mq_timedreceive() == -1";
        EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
        EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

        tts.tv_sec = time(NULL) + 1;
        tts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";
        exit(0);
    } else {
        int status;
        EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";

        pid = waitpid(pid, &status, 0);
        EXPECT_TRUE(pid != 0) << "ERROR: pid == 0";
        EXPECT_TRUE(WIFEXITED(status) != 0) << "ERROR: WIFEXITED(status) == 0";
        EXPECT_TRUE(WEXITSTATUS(status) == 0) << "ERROR: WEXITSTATUS(status) != 0" \
                                              << ", WEXITSTATUS(status) = " << WEXITSTATUS(status);
        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
        EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
        EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
        EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;
    }

FINISH:
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

static void *PthreadCom(void *arg)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr getAttr;
    char rMsg[MQ_RX_LEN];

    queue = (mqd_t)arg;
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != 0, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;
    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";

    return NULL;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0700
 * @tc.name   mq_send and mq_receive function test in thread and process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTwoThreadCom, TestSize.Level1)
{
    mqd_t queue;
    pthread_t tid;
    unsigned int prio;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTwoLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(pthread_create(&tid, NULL, PthreadCom, (void *)queue) != -1) << "ERROR: pthread_create() == -1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(pthread_join(tid, NULL) == 0) << "ERROR: pthread_join() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != 0, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

static void *PthreadTimedCom(void *arg)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr;
    char rMsg[MQ_RX_LEN];

    queue = (mqd_t)arg;
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    rts.tv_sec = time(NULL) + 1;
    rts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                            "ERROR: mq_timedreceive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

    tts.tv_sec = time(NULL) + 1;
    tts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";

    return NULL;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0800
 * @tc.name   mq_timedsend and mq_timedreceive function test in thread and process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqTimedTwoThreadCom, TestSize.Level1)
{
    mqd_t queue;
    pthread_t tid;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqTimedTwoThreadCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(pthread_create(&tid, NULL, PthreadTimedCom, (void *)queue) != -1) << "ERROR: pthread_create() == -1";

    tts.tv_sec = time(NULL) + 1;
    tts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";
    EXPECT_TRUE(pthread_join(tid, NULL) == 0) << "ERROR: pthread_join() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
    rts.tv_sec = time(NULL) + 1;
    rts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                            "ERROR: mq_timedreceive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

static void *PthreadAllCom(void *arg)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr;
    char rMsg[MQ_RX_LEN];

    queue = (mqd_t)arg;
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    rts.tv_sec = time(NULL) + 1;
    rts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1) << \
                                                            "ERROR: mq_timedreceive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;
    tts.tv_sec = time(NULL) + 1;
    tts.tv_nsec = 0;
    EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0) << "ERROR: mq_timedsend() != 0";

    return NULL;
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_0900
 * @tc.name   all send and all receive function test in thread and process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqAllTwoThreadCom, TestSize.Level1)
{
    mqd_t queue;
    pthread_t tid;
    unsigned int prio;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqAllTwoThreadCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    EXPECT_TRUE(pthread_create(&tid, NULL, PthreadAllCom, (void *)queue) != -1) << "ERROR: pthread_create() == -1";

    EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(pthread_join(tid, NULL) == 0) << "ERROR: pthread_join() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
    EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_1000
 * @tc.name   all send and all receive function test in more process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqThreeLevelCom, TestSize.Level2)
{
    mqd_t queue;
    pid_t pid;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqThreeLevelCom_%d", GetRandom(10000));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    pid = fork();
    if (pid < 0) {
        goto FINISH;
    } else if (pid == 0) {
        pid = fork();
        if (pid == 0) {
            EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
            EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1" << \
                                                " errno = " << errno << " strerror(errno) = " << strerror(errno);
            EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
            EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;
            EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
        } else {
            int status;

            pid = waitpid(pid, &status, 0);
            EXPECT_TRUE(pid != 0) << "ERROR: pid == 0";
            EXPECT_TRUE(WIFEXITED(status) != 0) << "ERROR: WIFEXITED(status) == 0";
            EXPECT_TRUE(WEXITSTATUS(status) == 0) << "ERROR: WEXITSTATUS(status) != 0" \
                                              << ", WEXITSTATUS(status) = " << WEXITSTATUS(status);

            EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
            rts.tv_sec = time(NULL) + 1;
            rts.tv_nsec = 0;
            EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1)
                << "ERROR: mq_timedreceive() == -1";
            EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
            EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                                "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;

            tts.tv_sec = time(NULL) + 1;
            tts.tv_nsec = 0;
            EXPECT_TRUE(mq_timedsend(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO, &tts) == 0)
                << "ERROR: mq_timedsend() != 0";
        }
        exit(0);
    } else {
        int status;
        EXPECT_TRUE(mq_send(queue, MQ_MSG, MQ_MSG_LEN, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";

        pid = waitpid(pid, &status, 0);
        EXPECT_TRUE(pid != 0) << "ERROR: pid == 0";
        EXPECT_TRUE(WIFEXITED(status) != 0) << "ERROR: WIFEXITED(status) == 0";
        EXPECT_TRUE(WEXITSTATUS(status) == 0) << "ERROR: WEXITSTATUS(status) != 0" \
                                              << ", WEXITSTATUS(status) = " << WEXITSTATUS(status);

        EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
        EXPECT_TRUE(getAttr.mq_curmsgs == 1) << "ERROR: getAttr.mq_curmsgs != 1" \
                                             << ", getAttr.mq_curmsgs = " << getAttr.mq_curmsgs;
        rts.tv_sec = time(NULL) + 1;
        rts.tv_nsec = 0;
        EXPECT_TRUE(mq_timedreceive(queue, rMsg, getAttr.mq_msgsize, &prio, &rts) != -1)
            << "ERROR: mq_timedreceive() == -1";
        EXPECT_TRUE(prio == MQ_MSG_PRIO) << "ERROR: prio != MQ_MSG_PRIO, prio = " << prio;
        EXPECT_TRUE(strncmp(MQ_MSG, rMsg, MQ_MSG_LEN) == 0) << \
                            "sent != received: sent = " << MQ_MSG << ", received = " << rMsg;
    }

FINISH:
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_1100
 * @tc.name   mq_send and mq_receive max packet function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqMinMaxLen, TestSize.Level2)
{
    mqd_t queue;
    unsigned int prio;
    struct mq_attr attr;
    struct mq_attr getAttr, setAttr;
    const int max = MAX_MQ_MSG_SIZE;
    char qName[MQ_NAME_LEN], rMsg[MAX_MQ_MSG_SIZE], sMsg[MAX_MQ_MSG_SIZE];

    for (int i=0; i<MAX_MQ_MSG_SIZE; i++) {
        sMsg[i] = 0x36;
        rMsg[i] = 0x00;
    }

    sprintf(qName, "testMqMaxLen_%d", GetRandom(10000));
    setAttr.mq_msgsize = MAX_MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1"<< \
                        " errno = " << errno << " strerror(errno) = " << strerror(errno);
    EXPECT_TRUE(mq_send(queue, sMsg, MAX_MQ_MSG_SIZE, MQ_MSG_PRIO) == 0) << "ERROR: mq_send() != 0";
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE(mq_receive(queue, rMsg, getAttr.mq_msgsize, &prio) != -1) << "ERROR: mq_receive() == -1";
    EXPECT_TRUE(strncmp(sMsg, rMsg, MAX_MQ_MSG_SIZE) == 0) << "sent != received: sent = " << \
                                                        sMsg << ", received = " << rMsg;
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0";
}

/**
 * @tc.number SUB_KERNEL_IPC_MQ_1200
 * @tc.name   mq_setattr set and clean mq_flags for O_NONBLOCK function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcMqTest, testMqSetGetAttr, TestSize.Level1)
{
    mqd_t queue;
    unsigned int prio;
    struct timespec tts, rts;
    struct mq_attr getAttr, setAttr;
    char qName[MQ_NAME_LEN], rMsg[MQ_RX_LEN];

    sprintf(qName, "testMqFunction_%d", GetRandom(10000));

    memset(&setAttr, 0, sizeof(setAttr));
    setAttr.mq_msgsize = MQ_MSG_SIZE;
    setAttr.mq_maxmsg = MQ_MAX_MSG;
    setAttr.mq_flags = O_NONBLOCK;
    queue = mq_open(qName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &setAttr);
    ASSERT_TRUE(queue != (mqd_t)-1) << "ERROR: mq_open() == (mqd_t)-1";

    memset(&getAttr, 0, sizeof(getAttr));
    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    EXPECT_TRUE((getAttr.mq_flags & O_NONBLOCK) == O_NONBLOCK);

    setAttr.mq_flags &= ~O_NONBLOCK;
    EXPECT_TRUE(mq_setattr(queue, &setAttr, NULL) == 0) << "ERROR: mq_setattr() != 0";

    EXPECT_TRUE(mq_getattr(queue, &getAttr) == 0) << "ERROR: mq_getattr() != 0";
    LOG("setAttr.mq_flags = 0x%08x, getAttr.mq_flags = 0x%08x ", setAttr.mq_flags, getAttr.mq_flags);
    EXPECT_TRUE((getAttr.mq_flags & O_NONBLOCK) == 0) << "ERROR: getAttr.mq_flags & O_NONBLOCK != 0," \
                " getAttr.mq_flags = " << getAttr.mq_flags << " setAttr.mq_flags = " << setAttr.mq_flags;
    EXPECT_TRUE(mq_close(queue) == 0) << "ERROR: mq_close() != 0";
    ASSERT_TRUE(mq_unlink(qName) == 0) << "ERROR: mq_unlink() != 0" << " errno = " << \
                                        errno << " strerror(errno) = " << strerror(errno);
}










