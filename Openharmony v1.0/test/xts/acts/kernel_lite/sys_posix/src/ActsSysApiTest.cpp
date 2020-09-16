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
#include "XtsActsSysApiExpect.h"

using namespace testing::ext;

class ActsSysApiTest : public testing::Test {
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
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
* @tc.number     SUB_KERNEL_NDKAPI_SYS_SECUREGETENV_0100
* @tc.name       test secure_getenv api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsSysApiTest, testSecureGetenv_0100, TestSize.Level2) {
    char* envPath;

    envPath = secure_getenv("HOME");
    LogPrint("    secure_getenv name:='HOME',   --> return envPath:='%s'\n", envPath);
    EXPECT_STREQ(envPath, NULL);

    envPath = secure_getenv("INCLUDE");
    LogPrint("    secure_getenv name:='INCLUDE',   --> return envPath:='%s'\n", envPath);
    EXPECT_STREQ(envPath, NULL);

    envPath = secure_getenv("ROOT");
    LogPrint("    secure_getenv name:='ROOT',   --> return envPath:='%s'\n", envPath);
    EXPECT_STREQ(envPath, NULL);

    envPath = secure_getenv("USER");
    LogPrint("    secure_getenv name:='USER',   --> return envPath:='%s'\n", envPath);
    EXPECT_STREQ(envPath, NULL);
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_SYS_SETENV_0100
* @tc.name       test setenv api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsSysApiTest, testSetenv_0100, TestSize.Level2) {
    int returnVal;
    char srcPara[] = "/bin";

    char* envSrc;
    envSrc = secure_getenv("PATH");
    LogPrint("    secure_getenv name:='PATH',   --> return envSrc:='%s'\n", envSrc);
    
    returnVal = setenv("PATH", srcPara, 1);
    LogPrint("    setenv name:='PATH' value:='%s' overwrite:='1', "
        "   --> returnVal:='%d'\n", srcPara, returnVal);

    char* envDst;
    envDst = secure_getenv("PATH");
    LogPrint("    secure_getenv name:='PATH',   --> return envDst:='%s'\n", envDst);
    EXPECT_STREQ(envDst, srcPara);
}
