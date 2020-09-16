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

class ActsSchedApiTest : public testing::Test {
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

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_GETPRIORITY_0100
* @tc.name       test getpriority api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testGetpriority, TestSize.Level1) {
    int which = PRIO_PROCESS;
    id_t pid;
    int returnPriority;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    returnPriority = getpriority(which, pid);
    LogPrint("    getpriority which:='PRIO_PROCESS' pid:='%d',   "
        "--> returnPriority:='%d'\n", pid, returnPriority);
    EXPECT_GE(returnPriority, XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MIN)
        << "ErrInfo: " << "getpriority which:='PRIO_PROCESS' pid:='"
        << pid << "',   --> returnPriority:='" << returnPriority << "'";
    EXPECT_LE(returnPriority, XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MAX)
        << "ErrInfo: " << "getpriority which:='PRIO_PROCESS' pid:='"
        << pid << "',   --> returnPriority:='" << returnPriority << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SCHED_GET_PRIORITY_MAX_0100
* @tc.name       test sched_get_priority_max api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedGetPriorityMax, TestSize.Level1) {
    int returnPriority;

    returnPriority = sched_get_priority_max(SCHED_FIFO);
    LogPrint("    sched_get_priority_max policy:='SCHED_FIFO',   --> returnPriority:='%d'\n", returnPriority);
    EXPECT_EQ(returnPriority, XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MAX)
        << "ErrInfo:" << " sched_get_priority_max policy:='SCHED_FIFO',   --> returnPriority:='"
        << returnPriority << "'";

    returnPriority = sched_get_priority_max(SCHED_RR);
    LogPrint("    sched_get_priority_max policy:='SCHED_RR',   --> returnPriority:='%d'\n", returnPriority);
    EXPECT_EQ(returnPriority, XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MAX)
        << "ErrInfo:" << " sched_get_priority_max policy:='SCHED_RR',   --> returnPriority:='"
        << returnPriority << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SCHED_GET_PRIORITY_MIN_0100
* @tc.name       test sched_get_priority_min api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedGetPriorityMin, TestSize.Level1) {
    int returnPriority;

    returnPriority = sched_get_priority_min(SCHED_FIFO);
    LogPrint("    sched_get_priority_min policy:='SCHED_FIFO',   --> returnPriority:='%d'\n", returnPriority);
    EXPECT_EQ(returnPriority, XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MIN) << "ErrInfo: "
        << "sched_get_priority_min policy:='SCHED_FIFO',   --> returnPriority:='" << returnPriority << "'";

    returnPriority = sched_get_priority_min(SCHED_RR);
    LogPrint("    sched_get_priority_min policy:='SCHED_RR',   --> returnPriority:='%d'\n", returnPriority);
    EXPECT_EQ(returnPriority, XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MIN) << "ErrInfo: "
        << "sched_get_priority_min policy:='SCHED_FIFO',   --> returnPriority:='" << returnPriority << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SCHED_GETPARAM_0100
* @tc.name       test sched_getparam api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedGetParam, TestSize.Level1) {
    struct sched_param params;
    id_t pid;
    int returnVal;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    returnVal = sched_getparam(pid, &params);
    LogPrint("    sched_getparam pid:='%d' &params:='int sched_priority',"
        "   --> returnVal:='%d', params.sched_priority:='%d'\n", pid, returnVal, params.sched_priority);
    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: sched_getparam pid:='" << pid
        << "' &params:='int sched_priority',   --> returnVal:='" << returnVal << "', params.sched_priority:='"
        << params.sched_priority <<"'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SCHED_GETSCHEDULER_0100
* @tc.name       test sched_getscheduler api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedGetScheduler, TestSize.Level1) {
    struct sched_param params;
    id_t pid;
    int returnVal;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    returnVal = sched_getscheduler(pid);
    LogPrint("    sched_getscheduler pid:='%d',   --> returnVal:='%d'\n", pid, returnVal);
    EXPECT_EQ(returnVal, SCHED_RR)
        << "ErrInfo: sched_getscheduler pid:='" << pid
        << "',   --> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_RR_GET_INTERVAL_0100
* @tc.name       test sched_rr_get_interval api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedRRGetInterval, TestSize.Level1) {
    struct timespec intervalS1;
    struct timespec intervalS2;
    id_t pid;
    int returnVal1 = -1;
    int returnVal2 = -1;
    intervalS1.tv_sec = -1;
    intervalS1.tv_nsec = -1;
    intervalS2.tv_sec = -1;
    intervalS2.tv_nsec = -1;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    returnVal1 = sched_rr_get_interval(pid, &intervalS1);
    returnVal2 = sched_rr_get_interval(0, &intervalS2);
    LogPrint("    sched_rr_get_interval pid:='%d' *ts:='&intervalS1',   "
        "--> returnVal1:='%d' intervalS1.tv_sec:='%lld', intervalS1.tv_nsec:='%ld'\n",
        pid, returnVal1, intervalS1.tv_sec, intervalS1.tv_nsec);
    LogPrint("    sched_rr_get_interval pid:='0' *ts:='&intervalS2',   "
        "--> returnVal2:='%d' intervalS2.tv_sec:='%lld', intervalS2.tv_nsec:='%ld'\n",
        returnVal2, intervalS2.tv_sec, intervalS2.tv_nsec);
    EXPECT_EQ(returnVal1, returnVal2)
        << "ErrInfo: sched_rr_get_interval pid:='" << pid
        << ",0' *ts:='&intervalS1,&intervalS2',   --> returnVal1:='" << returnVal1 << "' returnVal2:='"
        << returnVal2 << "'";
    EXPECT_EQ(intervalS1.tv_sec, intervalS2.tv_sec)
        << "ErrInfo: sched_rr_get_interval pid:='" << pid
        << ",0' *ts:='&intervalS1,&intervalS2',   --> return intervalS1.tv_sec:='" << intervalS1.tv_sec
        << "' intervalS2.tv_sec:='" << intervalS2.tv_sec << "'";
    EXPECT_EQ(intervalS1.tv_nsec, intervalS2.tv_nsec)
        << "ErrInfo: sched_rr_get_interval pid:='" << pid
        << ",0' *ts:='&intervalS1,&intervalS2',   --> return intervalS1.tv_nsec:='" << intervalS1.tv_nsec
        << "' intervalS2.tv_nsec:='" << intervalS2.tv_nsec << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SCHED_SETPARAM_0100
* @tc.name       test sched_setparam api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedSetParam, TestSize.Level1) {
    struct sched_param params;
    id_t pid;
    int policy, oldPriority, newPriority, tmpErrno;
    int returnVal1, returnVal2, returnVal3;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    returnVal1 = sched_getparam(pid, &params);
    LogPrint("    sched_getparam pid:='%d' &params:='*param',   "
        "--> returnVal1:='%d', params.sched_priority:='%d'\n", pid, returnVal1, params.sched_priority);
    oldPriority = params.sched_priority;
	
    newPriority = params.sched_priority == XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MIN ?
        (params.sched_priority = XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MAX):
        (params.sched_priority = XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MIN);

    LogPrint("    newPriority:='%d'\n", newPriority);

    returnVal2 = sched_setparam(pid, &params);
    tmpErrno = errno;
    LogPrint("    sched_setparam pid:='%d' &params:='*param',   "
        "--> returnVal2:='%d', params.sched_priority:='%d'\n", pid, returnVal2, params.sched_priority);
    newPriority = params.sched_priority;
    EXPECT_EQ(returnVal2, 0) << "ErrInfo: sched_setparam pid:='" << pid
        << "' &params:='int sched_priority',   --> returnVal2:='" << returnVal2 << "', params.sched_priority:='"
        << params.sched_priority <<"'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SCHED_SETSCHEDULER_0100
* @tc.name       test sched_setscheduler api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSchedSetScheduler, TestSize.Level1) {
    struct sched_param params;
    int which = PRIO_PROCESS;
    id_t pid;
    int returnVal, oldPolicy, oldPriority, newPolicy, returnNewPolicy, tmpErrno;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    oldPolicy = sched_getscheduler(pid);
    LogPrint("    sched_getscheduler pid:='%d',   --> return oldPolicy:='%d'\n", pid, oldPolicy);
    oldPriority = getpriority(which, pid);
    LogPrint("    getpriority which:='PRIO_PROCESS' pid:='%d',   --> oldPriority:='%d'\n", pid, oldPriority);
	
    newPolicy = oldPolicy == SCHED_RR ? (newPolicy = SCHED_FIFO) : (newPolicy = SCHED_RR);
    LogPrint("    newPolicy:='%d'\n", newPolicy);
	
    params.sched_priority = XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MIN;
	
    returnVal = sched_setscheduler(pid, newPolicy, &params);
    tmpErrno = errno;
    LogPrint("    sched_setscheduler pid:='%d' policy:='%d' params.sched_priority:='%d',   "
        "--> returnVal:='%d'\n", pid, newPolicy, params.sched_priority, returnVal);
    EXPECT_NE(returnVal, -1)
        << "ErrInfo: sched_setscheduler pid:='" << pid << "' policy:='" << newPolicy
        << "' params.sched_priority:='" << params.sched_priority << "',   --> returnVal:='" << returnVal << "'";
    EXPECT_EQ(tmpErrno, 0)
        << "ErrInfo: sched_setscheduler pid:='" << pid << "' policy:='" << newPolicy
        << "' params.sched_priority:='" << params.sched_priority << "',   --> returnVal:='" << returnVal
        << "' errno:='" << errno << "'";
    
    returnNewPolicy = sched_getscheduler(pid);
    LogPrint("    sched_getscheduler pid:='%d',   --> returnNewPolicy:='%d'\n", pid, returnNewPolicy);
    EXPECT_EQ(returnNewPolicy, newPolicy)
        << "ErrInfo: sched_setscheduler pid:='" << pid << "' policy:='"
        << newPolicy << "' params.sched_priority:='" << params.sched_priority << "',   --> returnNewPolicy:='"
        << returnNewPolicy << "'";
	
    // teardown
    params.sched_priority = oldPriority;
    sched_setscheduler(pid, oldPolicy, &params);
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SCHED_SETPRIORITY_0100
* @tc.name       test setpriority api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsSchedApiTest, testSetpriority, TestSize.Level1) {
    int which = PRIO_PROCESS;
    id_t pid;
    int oldPriority, newPriority, returnVal, tmpErrno;

    pid = getpid();
    LogPrint("    getpid,   --> pid:='%d'\n", pid);

    oldPriority = getpriority(which, pid);
    LogPrint("    getpriority which:='PRIO_PROCESS' pid:='%d',   --> oldPriority:='%d'\n", pid, oldPriority);
	
    newPriority = oldPriority == XTS_ACTS_SCHED_API_EXPECT_USER_PRIORITY_MAX ?
        (newPriority = oldPriority - 1):
        (newPriority = oldPriority + 1);

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
}
