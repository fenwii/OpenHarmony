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

// tested api in this file: getpid getppid getpgrp setpgrp  getpgid setpgid

#include <unistd.h>
#include <sys/types.h>
#include <gtest/gtest.h>
#include "log.h"
#include "utils.h"
#include "KernelConstants.h"

using namespace testing::ext;

class PidTest : public testing::Test {
protected:
    const char* mChildELF = RES_DIR_KERNEL "process/executor";
};

/**
 * @tc.number SUB_KERNEL_PM_PID_Getppid_0100
 * @tc.name   getpid and getppid test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(PidTest, testGetPpid, TestSize.Level1)
{
    pid_t parentPid = getpid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        pid_t pPid = getppid();
        if (pPid != parentPid) {
            LOG("getppid fail, expect:%d, but get:%d", parentPid, pPid);
            exit(1);
        }
        exit(0);
    } else { // parent
        Msleep(100);
        AssertProcExitedOK(pid);
    }
}

/**
 * @tc.number SUB_KERNEL_PM_PID_SetGetPgrp_0100
 * @tc.name   setpgrp and getpgrp test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(PidTest, testSetGetPgrp, TestSize.Level1)
{
    pid_t parentPid = getpid();
    int rt = setpgrp();
    ASSERT_EQ(rt, 0);

    pid_t pgid = getpgrp();
    ASSERT_EQ(pgid, parentPid);

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        pid_t childPgid = getpgrp();
        if (childPgid != pgid) {
            LOG("child getpgrp fail, expect:%d, but get:%d", pgid, childPgid);
            exit(1);
        }
        exit(0);
    } else { // parent
        Msleep(30);
        AssertProcExitedOK(pid);
    }
}

/**
 * @tc.number SUB_KERNEL_PM_PID_SetGetPgid_0100
 * @tc.name   setpgid and getpgid basic test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(PidTest, testSetGetPgid, TestSize.Level1)
{
    pid_t parentPid = getpid();
    int rt = setpgid(0, parentPid);
    ASSERT_EQ(rt, 0);
    rt = setpgid(0, 0);
    ASSERT_EQ(rt, 0);

    pid_t pgid = getpgid(0);
    ASSERT_EQ(pgid, parentPid);

    pid_t pid1 = fork();
    ASSERT_TRUE(pid1 >= 0) << "======== Fork Error! =========";
    if (pid1 == 0) { // child
        pid_t childPgid = getpgid(0);
        if (childPgid != pgid) {
            LOG("child getpgid fail, expect:%d, but get:%d", pgid, childPgid);
            exit(1);
        }
        Msleep(40);
        childPgid = getpgid(0);
        pid_t childPid = getpid();
        if (childPgid != childPid) {
            LOG("child new pgid check fail, pid=%d, pgid:%d", childPid, childPgid);
            exit(1);
        }
        exit(0);
    } else { // parent
        Msleep(30);
        rt = setpgid(pid1, pid1);
        ASSERT_EQ(rt, 0);
        pid_t pgid2 = getpgid(pid1);
        ASSERT_EQ(pgid2, pid1);
        Msleep(50);
        AssertProcExitedOK(pid1);
    }
}
/**
 * @tc.number SUB_KERNEL_PM_PID_SetGetPgid_0200
 * @tc.name   setpgid and getpgid test for sibling process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(PidTest, testSetGetSiblingPgid, TestSize.Level1)
{
    pid_t parentPid = getpid();
    int rt = setpgid(0, parentPid);
    ASSERT_EQ(rt, 0);
    rt = setpgid(0, 0);
    ASSERT_EQ(rt, 0);
    pid_t pgid = getpgid(0);
    ASSERT_EQ(pgid, parentPid);

    pid_t pid1 = fork();
    ASSERT_TRUE(pid1 >= 0) << "======== Fork Error! =========";
    if (pid1 == 0) { // child1
        Msleep(20);
        exit(0);
    } else { // parent
        pid_t pid2 = fork();
        ASSERT_TRUE(pid2 >= 0) << "======== Fork Error! =========";
        if (pid2 == 0) { // child2
            int exitCode = 0;
            pid_t siblingPgid = getpgid(pid1);
            if (siblingPgid != parentPid) {
                LOG("child2: get sibling pgid fail, rt=%d, errno=%d", siblingPgid, errno);
                exitCode = 1;
            }
            rt = setpgid(pid1, pid1);
            if (rt != -1) {
                LOG("child2: setpgid for sibling should fail");
                exitCode = 1;
            }
            if (errno != ESRCH) {
                LOG("child2: setpgid errno fail, expected %d, but get %d", ESRCH, errno);
                exitCode = 1;
            }
            exit(exitCode);
        }
        // parent
        Msleep(50);
        AssertProcExitedOK(pid1);
        AssertProcExitedOK(pid2);
    }
}
/**
 * @tc.number SUB_KERNEL_PM_PID_SetGetPgid_0300
 * @tc.name   setpgid fail test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(PidTest, testGetpgidFail, TestSize.Level3)
{
    pid_t pgid = getpgid(-1);
    EXPECT_EQ(pgid, -1);
    EXPECT_EQ(errno, EINVAL);

    pgid = getpgid(-1000001);
    EXPECT_EQ(pgid, -1);
    EXPECT_EQ(errno, EINVAL);

    pid_t nonExitPid = GetNonExistPid(); // valid but not exist pid
    if (nonExitPid != -1) {
        pgid = getpgid(nonExitPid);
        EXPECT_EQ(pgid, -1);
        EXPECT_EQ(errno, ESRCH);
    }

    pgid = getpgid(MAX_PROCESS_NUMBER + 1);
    EXPECT_EQ(pgid, -1);
    EXPECT_EQ(errno, EINVAL);

    pgid = getpgid(100000);
    EXPECT_EQ(pgid, -1);
    EXPECT_EQ(errno, EINVAL);

    pgid = getpgid(1);
    EXPECT_EQ(pgid, 1) << "get init process-groups-ID fail\n";
}

/**
 * @tc.number SUB_KERNEL_PM_PID_SetGetPgid_0400
 * @tc.name   setpgid fail test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(PidTest, testSetpgidFail, TestSize.Level3)
{
    pid_t pid = getpid();
    int rt = setpgrp();
    ASSERT_EQ(rt, 0);

    LOG("invalid pid test...");
    rt = setpgid(-1, 0);
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EINVAL);

    rt = setpgid(-1000001, 0);
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EINVAL);

    pid_t nonExitPid = GetNonExistPid(); // valid but not exist pid
    if (nonExitPid != -1) {
        rt = setpgid(nonExitPid, 0);
        EXPECT_EQ(rt, -1);
        EXPECT_EQ(errno, ESRCH);    
    }

    rt = setpgid(MAX_PROCESS_NUMBER + 1, 0);
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EINVAL);

    rt = setpgid(100000, 0);
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EINVAL);

    rt = setpgid(1, pid); // init
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EPERM);

    rt = setpgid(2, pid); // kProcess
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EPERM);

    LOG("invalid pgid test...");
    rt = setpgid(0, -1);
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EINVAL);

    nonExitPid = GetNonExistPid(); // valid but not exist pid
    if (nonExitPid != -1) {
        rt = setpgid(0, nonExitPid);
        EXPECT_EQ(rt, -1);
        EXPECT_EQ(errno, EPERM);        
    }

    rt = setpgid(0, 10001);
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EINVAL);

    rt = setpgid(0, 1); // init
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EPERM);

    rt = setpgid(0, 2); // kProcess
    EXPECT_EQ(rt, -1);
    EXPECT_EQ(errno, EPERM);
}
