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
#include <inttypes.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/utsname.h>

#include "gtest/gtest.h"
#include "XtsActsUtil.h"
#include "XtsActsTimeApiExpect.h"

using namespace testing::ext;

class ActsTimeApiTest : public testing::Test {
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
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETRES_0100
* @tc.name       test clock_getres api para CLOCK_REALTIME
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetRes0100, TestSize.Level1) {
    struct timespec res;
    int returnVal;
    
    returnVal = clock_getres(CLOCK_REALTIME, &res);
    LogPrint("    clock_getres clock_id:='CLOCK_REALTIME=%d' &res:='&res',   --> returnVal:='%d', "
        "{res.tv_sec:='%lld' res.tv_nsec:='%ld'}\n", CLOCK_REALTIME, returnVal, res.tv_sec, res.tv_nsec);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_getres clock_id:='CLOCK_REALTIME=" << CLOCK_REALTIME
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', {res.tv_sec:='"
        << res.tv_sec << "' res.tv_nsec:='" << res.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETRES_0200
* @tc.name       test clock_getres api para CLOCK_MONOTONIC
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetRes0200, TestSize.Level1) {
    struct timespec res;
    int returnVal;

    returnVal = clock_getres(CLOCK_MONOTONIC, &res);
    LogPrint("    clock_getres clock_id:='CLOCK_MONOTONIC=%d' &res:='&res',   --> returnVal:='%d', "
        "{res.tv_sec:='%lld' res.tv_nsec:='%ld'}\n", CLOCK_MONOTONIC, returnVal, res.tv_sec, res.tv_nsec);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_getres clock_id:='CLOCK_MONOTONIC=" << CLOCK_MONOTONIC
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', {res.tv_sec:='"
        << res.tv_sec << "' res.tv_nsec:='" << res.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETRES_0400
* @tc.name       test clock_getres api para CLOCK_REALTIME_COARSE
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetRes0400, TestSize.Level1) {
    struct timespec res;
    int returnVal;

    returnVal = clock_getres(CLOCK_REALTIME_COARSE, &res);
    LogPrint("    clock_getres clock_id:='CLOCK_REALTIME_COARSE=%d' &res:='&res',   --> returnVal:='%d', "
        "{res.tv_sec:='%lld', res.tv_nsec:='%ld'}\n", CLOCK_REALTIME_COARSE, returnVal, res.tv_sec, res.tv_nsec);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_getres clock_id:='CLOCK_REALTIME_COARSE=" << CLOCK_REALTIME_COARSE
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', {res.tv_sec:='"
        << res.tv_sec << "' res.tv_nsec:='" << res.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETRES_0500
* @tc.name       test clock_getres api para CLOCK_MONOTONIC_COARSE
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetRes0500, TestSize.Level1) {
    struct timespec res;
    int returnVal;

    returnVal = clock_getres(CLOCK_MONOTONIC_COARSE, &res);
    LogPrint("    clock_getres clock_id:='CLOCK_MONOTONIC_COARSE=%d' &res:='&res',   --> returnVal:='%d', "
        "{res.tv_sec:='%lld', res.tv_nsec:='%ld'}\n", CLOCK_MONOTONIC_COARSE, returnVal, res.tv_sec, res.tv_nsec);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_getres clock_id:='CLOCK_MONOTONIC_COARSE=" << CLOCK_MONOTONIC_COARSE
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', {res.tv_sec:='"
        << res.tv_sec << "' res.tv_nsec:='" << res.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETRES_1000
* @tc.name       test clock_getres api para CLOCK_PROCESS_CPUTIME_ID not support
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetRes1000, TestSize.Level1) {
    struct timespec res;
    int returnVal, thisErrno;

    returnVal = clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res);
    thisErrno = errno;
    LogPrint("    clock_getres clock_id:='CLOCK_PROCESS_CPUTIME_ID=%d' &res:='&res',   --> returnVal:='%d', "
        "errno:='%d'\n", CLOCK_PROCESS_CPUTIME_ID, returnVal, thisErrno);

    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_getres clock_id:='CLOCK_PROCESS_CPUTIME_ID=" << CLOCK_PROCESS_CPUTIME_ID
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EOPNOTSUPP)
        << "ErrInfo: clock_getres clock_id:='" << CLOCK_PROCESS_CPUTIME_ID
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";

    returnVal = clock_getres(CLOCK_PROCESS_CPUTIME_ID + 30, &res);
    thisErrno = errno;
    LogPrint("    clock_getres clock_id:='%d' &res:='&res',   --> returnVal:='%d', "
        "errno:='%d'\n", CLOCK_PROCESS_CPUTIME_ID + 30, returnVal, thisErrno);

    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_getres clock_id:='" << CLOCK_PROCESS_CPUTIME_ID + 30
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EINVAL)
        << "ErrInfo: clock_getres clock_id:='" << CLOCK_PROCESS_CPUTIME_ID + 30
        << "', &res:='&res',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETTIME_0100
* @tc.name       test clock_gettime api para CLOCK_REALTIME
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetTime0100, TestSize.Level1) {
    struct timespec tp;
    int returnVal;
    tp.tv_sec = 0;
    tp.tv_nsec = 0;
    
    returnVal = clock_gettime(CLOCK_REALTIME, &tp);
    LogPrint("    clock_gettime clock_id:='CLOCK_REALTIME=%d' &tp:='&tp',   --> returnVal:='%d', "
        "{tp.tv_sec:='%lld' tp.tv_nsec:='%ld'}\n", CLOCK_REALTIME, returnVal, tp.tv_sec, tp.tv_nsec);
    LogPrint("    time is: %lld.%d\n", tp.tv_sec, tp.tv_nsec);
    LogPrint("    sec  : %lld,   size:%d\n", tp.tv_sec, sizeof(tp.tv_sec));
    LogPrint("    nsec : %ld,   size:%d\n", tp.tv_nsec, sizeof(tp.tv_nsec));
    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_gettime clock_id:='CLOCK_REALTIME=" << CLOCK_REALTIME
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', {tp.tv_sec:='"
        << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETTIME_0200
* @tc.name       test clock_gettime api para CLOCK_MONOTONIC
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetTime0200, TestSize.Level1) {
    struct timespec tp;
    int returnVal;

    returnVal = clock_gettime(CLOCK_MONOTONIC, &tp);
    LogPrint("    clock_gettime clock_id:='CLOCK_MONOTONIC=%d' &tp:='&tp',   --> returnVal:='%d', "
        "{tp.tv_sec:='%lld', tp.tv_nsec:='%ld'}\n", CLOCK_MONOTONIC, returnVal, tp.tv_sec, tp.tv_nsec);
    LogPrint("    time is: %lld.%d\n", tp.tv_sec, tp.tv_nsec);
    LogPrint("    sec  : %lld,   size:%d\n", tp.tv_sec, sizeof(tp.tv_sec));
    LogPrint("    nsec : %ld,   size:%d\n", tp.tv_nsec, sizeof(tp.tv_nsec));
    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_gettime clock_id:='CLOCK_MONOTONIC=" << CLOCK_MONOTONIC
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', {tp.tv_sec:='"
        << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETTIME_0400
* @tc.name       test clock_gettime api para CLOCK_REALTIME_COARSE
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetTime0400, TestSize.Level1) {
    struct timespec tp;
    int returnVal;

    returnVal = clock_gettime(CLOCK_REALTIME_COARSE, &tp);
    LogPrint("    clock_gettime clock_id:='CLOCK_REALTIME_COARSE=%d' &tp:='&tp',   --> returnVal:='%d', "
        "{tp.tv_sec:='%lld', tp.tv_nsec:='%ld'}\n", CLOCK_REALTIME_COARSE, returnVal, tp.tv_sec, tp.tv_nsec);
    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_gettime clock_id:='CLOCK_REALTIME_COARSE=" << CLOCK_REALTIME_COARSE
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', {tp.tv_sec:='"
        << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_sec << "'}";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETTIME_0500
* @tc.name       test clock_gettime api para CLOCK_MONOTONIC_COARSE
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetTime0500, TestSize.Level1) {
    struct timespec tp;
    int returnVal;

    returnVal = clock_gettime(CLOCK_MONOTONIC_COARSE, &tp);
    LogPrint("    clock_gettime clock_id:='CLOCK_MONOTONIC_COARSE=%d' &tp:='&tp',   --> returnVal:='%d', "
        "{tp.tv_sec:='%lld', tp.tv_nsec:='%ld'}\n", CLOCK_MONOTONIC_COARSE, returnVal, tp.tv_sec, tp.tv_nsec);
    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: clock_gettime clock_id:='CLOCK_MONOTONIC_COARSE=" << CLOCK_MONOTONIC_COARSE
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', {tp.tv_sec:='"
        << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_sec << "'}";	
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_GETTIME_1000
* @tc.name       test clock_gettime api para CLOCK_PROCESS_CPUTIME_ID not support
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockGetTime1000, TestSize.Level1) {
    struct timespec tp;
    int returnVal, thisErrno;

    returnVal = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
    thisErrno = errno;
    LogPrint("    clock_gettime clock_id:='CLOCK_PROCESS_CPUTIME_ID=%d' &tp:='&tp',   --> returnVal:='%d', "
        "errno:='%d'\n", CLOCK_PROCESS_CPUTIME_ID, returnVal, thisErrno);
    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_gettime clock_id:='CLOCK_PROCESS_CPUTIME_ID=" << CLOCK_PROCESS_CPUTIME_ID
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EOPNOTSUPP)
        << "ErrInfo: clock_gettime clock_id:='CLOCK_PROCESS_CPUTIME_ID=" << CLOCK_PROCESS_CPUTIME_ID
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";

    returnVal = clock_gettime(CLOCK_PROCESS_CPUTIME_ID + 30, &tp);
    thisErrno = errno;
    LogPrint("    clock_gettime clock_id:='%d' &tp:='&tp',   --> returnVal:='%d', "
        "errno:='%d'\n", CLOCK_PROCESS_CPUTIME_ID + 30, returnVal, thisErrno);
    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_gettime clock_id:='" << CLOCK_PROCESS_CPUTIME_ID + 30
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EINVAL)
        << "ErrInfo: clock_gettime clock_id:='" << CLOCK_PROCESS_CPUTIME_ID +30
        << "', &tp:='&tp',   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_SETTIME_1000
* @tc.name       test clock_settime api para CLOCK_MONOTONIC not support
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockSetTime1000, TestSize.Level1) {
    struct timespec tp;
    int returnVal, thisErrno;
	
    tp.tv_sec = 1565308800;
    tp.tv_nsec = 0;

    returnVal = clock_settime(CLOCK_MONOTONIC, &tp);
    thisErrno = errno;
    LogPrint("    clock_settime clock_id:='CLOCK_MONOTONIC=%d' {tp.tv_sec:='%lld' tp.tv_nsec:='%ld'}   "
        "--> returnVal:='%d', errno:='%d'\n", CLOCK_MONOTONIC, tp.tv_sec, tp.tv_nsec, returnVal, thisErrno);
    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_settime clock_id:='CLOCK_MONOTONIC=" << CLOCK_MONOTONIC
        << "', {tp.tv_sec:='" << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_nsec
        << "'}   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EINVAL)
        << "ErrInfo: clock_settime clock_id:='CLOCK_MONOTONIC=" << CLOCK_MONOTONIC
        << "', {tp.tv_sec:='" << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_nsec
        << "'}   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_SETTIME_1100
* @tc.name       test clock_settime api para CLOCK_PROCESS_CPUTIME_ID not support
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockSetTime1100, TestSize.Level1) {
    struct timespec tp;
    int returnVal, thisErrno;
	
    tp.tv_sec = 1565308800;
    tp.tv_nsec = 0;

    returnVal = clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tp);
    thisErrno = errno;
    LogPrint("    clock_settime clock_id:='CLOCK_PROCESS_CPUTIME_ID=%d' {tp.tv_sec:='%lld' tp.tv_nsec:='%ld'}   "
        "--> returnVal:='%d', errno:='%d'\n", CLOCK_PROCESS_CPUTIME_ID, tp.tv_sec, tp.tv_nsec, returnVal, thisErrno);
    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_settime clock_id:='CLOCK_PROCESS_CPUTIME_ID=" << CLOCK_PROCESS_CPUTIME_ID
        << "', {tp.tv_sec:='" << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_nsec
        << "'}   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EOPNOTSUPP)
        << "ErrInfo: clock_settime clock_id:='CLOCK_PROCESS_CPUTIME_ID=" << CLOCK_PROCESS_CPUTIME_ID
        << "', {tp.tv_sec:='" << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_nsec
        << "'}   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CLOCK_SETTIME_1200
* @tc.name       test clock_settime api para CLOCK_REALTIME nsec less than zero
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testClockSetTime1200, TestSize.Level1) {
    struct timespec tp;
    int returnVal, thisErrno;
	
    tp.tv_sec = 1565308800;
    tp.tv_nsec = -1000;

    returnVal = clock_settime(CLOCK_REALTIME, &tp);
    thisErrno = errno;
    LogPrint("    clock_settime clock_id:='CLOCK_REALTIME=%d' {tp.tv_sec:='%lld' tp.tv_nsec:='%ld'}   "
        "--> returnVal:='%d', errno:='%d'\n", CLOCK_REALTIME, tp.tv_sec, tp.tv_nsec, returnVal, thisErrno);
    EXPECT_NE(returnVal, 0)
        << "ErrInfo: clock_settime clock_id:='CLOCK_REALTIME=" << CLOCK_REALTIME
        << "', {tp.tv_sec:='" << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_nsec
        << "'}   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
    EXPECT_EQ(thisErrno, EINVAL)
        << "ErrInfo: clock_settime clock_id:='CLOCK_REALTIME=" << CLOCK_REALTIME
        << "', {tp.tv_sec:='" << tp.tv_sec << "' tp.tv_nsec:='" << tp.tv_nsec
        << "'}   --> returnVal:='" << returnVal << "', errno:='" << thisErrno << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_ASCTIME_0100
* @tc.name       test asctime api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testAscTime0100, TestSize.Level1) {
    struct tm timeptr;
    char *returnStr;
    int thisErrno;
	
    timeptr.tm_sec = 0;
    timeptr.tm_min = 10;
    timeptr.tm_hour = 10;
    timeptr.tm_mday = 9;
    timeptr.tm_mon = 7;
    timeptr.tm_year = 119;
    timeptr.tm_wday = 5;
    
    returnStr = asctime(&timeptr);
    thisErrno = errno;
    LogPrint("    asctime &timeptr:='{timeptr.tm_year=%d timeptr.tm_mon=%d timeptr.tm_mday=%d}'   "
        "--> returnStr:='%s'\n", timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday, returnStr);
    EXPECT_STREQ("Fri Aug  9 10:10:00 2019\n", returnStr)
        << "ErrInfo: asctime &timeptr:='{timeptr.tm_year=" << timeptr.tm_year
        << " timeptr.tm_mon=" << timeptr.tm_mon << "' timeptr.tm_mday=" << timeptr.tm_mday
        << "}'   --> returnStr:='" << returnStr << "'";
    EXPECT_EQ(thisErrno, 0)
        << "ErrInfo: asctime &timeptr:='{timeptr.tm_year=" << timeptr.tm_year
        << " timeptr.tm_mon=" << timeptr.tm_mon << "' timeptr.tm_mday=" << timeptr.tm_mday
        << "}'   --> returnStr:='" << returnStr << "', errno:='" << thisErrno << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_CTIME_0100
* @tc.name       test ctime api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testCtime0100, TestSize.Level1) {
    time_t curClock;
    char *returnStr;
	
    time(&curClock);
    returnStr = ctime(&curClock);
    LogPrint("    ctime &clock:='&clock'   --> returnStr:='%s'\n", returnStr);
    EXPECT_STRNE(NULL, returnStr)
        << "ErrInfo: ctime &clock:='&clock'   --> returnStr:='" << returnStr << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_DIFFTIME_0100
* @tc.name       test difftime api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testDiffTime0100, TestSize.Level1) {
    time_t timeStart, timeEnd;
    double returnVal;
    
    time(&timeStart);
    sleep(1);
    time(&timeEnd);
	
    returnVal = difftime(timeEnd, timeStart);
    LogPrint("    difftime timeEnd:='%lld' timeStart:='%lld'   "
        "--> returnVal:='%f'\n", timeEnd, timeStart, returnVal);
    LogPrint("    sizeof timeEnd:='%d'   sizeof timeStart:='%d'\n", sizeof(timeEnd), sizeof(timeStart));
    EXPECT_GE(returnVal, 0)
        << "ErrInfo: difftime timeEnd:='" << timeEnd << "' timeStart:='"
        << timeStart << "'   --> returnVal:='" << returnVal << "'";
    EXPECT_LE(returnVal, 2)
        << "ErrInfo: difftime timeEnd:='" << timeEnd << "' timeStart:='"
        << timeStart << "'   --> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_TIME_TIMEGM_0100
* @tc.name       test timegm api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsTimeApiTest, testTimegm_0100, TestSize.Level1) {
    struct tm timeptr;
    time_t timeThis;
	
    timeptr.tm_sec = 0;
    timeptr.tm_min = 10;
    timeptr.tm_hour = 10;
    timeptr.tm_mday = 9;
    timeptr.tm_mon = 7;
    timeptr.tm_year = 119;
    timeptr.tm_wday = 5;
    
    timeThis = timegm(&timeptr);
    LogPrint("    timegm &timeptr:='{timeptr.tm_year=%d timeptr.tm_mon=%d timeptr.tm_mday=%d}'   "
        "--> return timeThis:='%lld'\n", timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday, timeThis);

    EXPECT_GE(timeThis, 1)
        << "ErrInfo: timegm &timeptr:='{timeptr.tm_year=" << timeptr.tm_year
        << " timeptr.tm_mon=" << timeptr.tm_mon << " timeptr.tm_mday="
        << timeptr.tm_mday << "}'   --> return timeThis:='" << timeThis << "'";
}

