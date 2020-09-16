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
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "gtest/gtest.h"
#include "XtsActsUtil.h"
#include "XtsActsProcessApiExpect.h"

using namespace testing::ext;

class ActsProcessApiTest : public testing::Test {
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

jmp_buf g_buf;
void TestLongjmp01(void)
{
    LogPrint("    TestLongjmp() Start\n");
    _longjmp(g_buf, 1);
    LogPrint("    TestLongjmp() End\n");
}

void TestLongjmp02(void)
{
    LogPrint("    TestLongjmp() Start\n");
    longjmp(g_buf, 1);
    LogPrint("    TestLongjmp() End\n");
}

static void *ThreadFunc(void* arg)
{
    LogPrint("    This is ThreadFunc()\n");
    return NULL;
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_LONGJMP_0100
* @tc.name       test _longjmp api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testLongjmp0100, TestSize.Level1) {
    int flagVal = 1;

    if(setjmp(g_buf)) {
        LogPrint("    back TestLongjmp()\n");
        flagVal = 0;
    } else {
        LogPrint("    first time to setjmp\n");
        flagVal = 1;
        TestLongjmp01();
    }
	
    EXPECT_EQ(flagVal, 0) << "ErrInfo: _longjmp fail.";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_LONGJMP_0200
* @tc.name       test longjmp api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testLongjmp0200, TestSize.Level1) {
    int flagVal = 1;

    if (setjmp(g_buf)) {
        LogPrint("    back TestLongjmp()\n");
        flagVal = 0;
    } else {
        LogPrint("    first time to setjmp\n");
        flagVal = 1;
        TestLongjmp02();
    }
	
    EXPECT_EQ(flagVal, 0) << "ErrInfo: longjmp fail.";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_SETJMP_0100
* @tc.name       test _setjmp api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testSetjmp0100, TestSize.Level1) {
    int returnVal;

    returnVal = _setjmp(g_buf);
    LogPrint("    _setjmp env:='struct jmp_buf',   --> returnVal:='%d'\n", returnVal);

    if (returnVal != 0) {
        LogPrint("    back testLongjmp()\n");
        ASSERT_NE(returnVal, 0) << "ErrInfo: second time _setjmp EQ 0,   --> returnVal:='" << returnVal << "'";
    } else {
        LogPrint("    first time to setjmp\n");
        ASSERT_EQ(returnVal, 0) << "ErrInfo: first time _setjmp not EQ 0,   --> returnVal:='" << returnVal << "'";
        TestLongjmp01();
    }
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_SETJMP_0200
* @tc.name       test setjmp api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testSetjmp0200, TestSize.Level1) {
    int returnVal;

    returnVal = setjmp(g_buf);
    LogPrint("    setjmp env:='struct jmp_buf',   returnVal:='%d'\n", returnVal);

    if(returnVal != 0) {
        LogPrint("    back testLongjmp()\n");
        ASSERT_NE(returnVal, 0) << "ErrInfo: second time setjmp EQ 0,   --> returnVal:='" << returnVal << "'";
    } else {
        LogPrint("    first time to setjmp\n");
        ASSERT_EQ(returnVal, 0) << "ErrInfo: first time setjmp not EQ 0,   --> returnVal:='" << returnVal << "'";
        TestLongjmp02();
    }
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_PTHREAD_SETNAME_NP_0100
* @tc.name       test pthread_setname_np api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testPthreadSetnameNp0100, TestSize.Level1) {
    pthread_t thisThread;
    int returnVal;

    thisThread = pthread_self();
    LogPrint("    pthread_self(),   --> return pthread_t:='%u(0x%x)'\n",
        (unsigned int)thisThread, (unsigned int)thisThread);
    
    returnVal = pthread_setname_np(thisThread, "funcThreadName");
    LogPrint("    pthread_setname_np thread:='%u(0x%x)' *name:='funcThreadName',   "
        "--> returnVal:='%d'\n", thisThread, thisThread, returnVal);
    
    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: pthread_setname_np thread:='" << thisThread
        << "(0x" << thisThread << ")' *name:='funcThreadName',   "
        << "--> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_PTHREAD_SETNAME_NP_1000
* @tc.name       test pthread_setname_np api para stringlong
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testPthreadSetnameNp1000, TestSize.Level1) {
    pthread_t thisThread;
    int returnVal;

    thisThread = pthread_self();
    LogPrint("    pthread_self(),   --> return pthread_t:='%u(0x%x)'\n",
        (unsigned int)thisThread, (unsigned int)thisThread);
    
    returnVal = pthread_setname_np(thisThread, "funcThreadNamelongName");
    LogPrint("    pthread_setname_np thread:='%u(0x%x)' *name:='funcThreadNamelongName',   "
        "--> returnVal:='%d'\n", thisThread, thisThread, returnVal);
    
    EXPECT_NE(returnVal, 0)
        << "ErrInfo: pthread_setname_np thread:='" << thisThread
        << "(0x" << thisThread << ")' *name:='funcThreadNamelongName',"
        << "   --> returnVal:='" << returnVal << "'";
    EXPECT_EQ(returnVal, ERANGE)
        << "ErrInfo: pthread_setname_np thread:='" << thisThread
        << "(0x" << thisThread << ")' *name:='funcThreadNamelongName',"
        << "   --> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_PROCESS_PTHREAD_ATTR_GETGUARDSIZE_0100
* @tc.name       test pthread_attr_getguardsize api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsProcessApiTest, testPthreadAttrGetguardsize0100, TestSize.Level1) {
    pthread_t newThread;
    pthread_attr_t threadAttr = {};
    int returnVal;

    returnVal = pthread_create(&newThread, &threadAttr, ThreadFunc, NULL);
    LogPrint("    pthread_create *thread:='&newThread' *attr:='&threadAttr' "
        "*start_routine:='ThreadFunc' arg:='NULL', \n");
    LogPrint("    --> returnVal:='%d',newThread:='%u(0x%x)'\n", returnVal, newThread, newThread);
    
    size_t guardsize;
    returnVal = pthread_attr_getguardsize(&threadAttr, &guardsize);
    LogPrint("    pthread_attr_getguardsize attr:='&threadAttr' guardsize:='&guardsize',"
        "    --> returnVal:='%d', guardsize:='%d'\n", returnVal, guardsize);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: pthread_attr_getguardsize attr:='&threadAttr' guardsize:='&guardsize',"
        << "    --> returnVal:='" << returnVal << "', guardsize:='" << guardsize << "'";
	
    returnVal = pthread_attr_setguardsize(&threadAttr, 4096);
    LogPrint("    pthread_attr_setguardsize attr:='&threadAttr' guardsize:='4096',"
        "    --> returnVal:='%d', guardsize:='%d'\n", returnVal, guardsize);
    
    returnVal = pthread_attr_getguardsize(&threadAttr, &guardsize);
    LogPrint("    pthread_attr_getguardsize attr:='&threadAttr' guardsize:='&guardsize',"
        "    --> returnVal:='%d', guardsize:='%d'\n", returnVal, guardsize);

    EXPECT_EQ(returnVal, 0)
        << "ErrInfo: pthread_attr_getguardsize attr:='&threadAttr' guardsize:='&guardsize',"
        << "    --> returnVal:='" << returnVal << "', guardsize:='" << guardsize << "'";
    EXPECT_EQ(guardsize, 4096)
        << "ErrInfo: pthread_attr_getguardsize attr:='&threadAttr' guardsize:='&guardsize',"
        << "    --> returnVal:='" << returnVal << "', guardsize:='" << guardsize << "'";
}
