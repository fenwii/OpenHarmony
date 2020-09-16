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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "gtest/gtest.h"
#include "XtsActsUtil.h"
#include "XtsActsSchedApiExpect.h"

using namespace testing::ext;

class FuncSchedTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
        errno = 0;
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

class FuncSchedParaTest : public testing::TestWithParam<int> {
};

/**
* @tc.number     SUB_KERNEL_PROCESS_PPRIORITY_0100
* @tc.name       test pthread_setschedprio api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_P(FuncSchedParaTest, testPthreadSetschedprio_0100, TestSize.Level2) {
    int newPriority = GetParam();
    int which = PRIO_PROCESS;
    id_t pid;
    int oldPriority, returnVal, tmpErrno, newPriorityReturn;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    oldPriority = getpriority(which, pid);
    LogPrint("    getpriority which:='PRIO_PROCESS' pid:='%d',   --> oldPriority:='%d'\n", pid, oldPriority);

    returnVal = setpriority(which, pid, newPriority);
    tmpErrno = errno;
    LogPrint("    setpriority which:='PRIO_PROCESS' pid:='%d' priority:='%d',   "
        "--> returnVal:='%d', errno:='%d'\n", pid, newPriority, returnVal, tmpErrno);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: setpriority which:='PRIO_PROCESS' pid:='" << pid << "' priority:='"
        << newPriority << "',   --> returnVal:='" << returnVal << "'";
    EXPECT_EQ(tmpErrno, 0)
        << "ErrInfo: setpriority which:='PRIO_PROCESS' pid:='" << pid << "' priority:='"
        << newPriority << "',   --> returnVal:='" << returnVal << "' errno:='" << tmpErrno << "'";
    
    newPriorityReturn = getpriority(which, pid);
    LogPrint("    getpriority which:='PRIO_PROCESS' pid:='%d',"
        "   --> newPriorityReturn:='%d'\n", pid, newPriorityReturn);

    usleep(10);
}

INSTANTIATE_TEST_CASE_P(FuncSchedTest, FuncSchedParaTest, testing::Range(10, 32));

