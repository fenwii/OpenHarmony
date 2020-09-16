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

#include "hctest.h"

/**
 * @tc.name: register a test suit named "IntTestSuite"
 * @param: test subsystem name
 * @param: example module name
 * @param: IntTestSuite test suit name
 */
LITE_TEST_SUIT(test, example, IntTestSuite);

/**
 * @tc.setup: define a setup for test suit, format:"IntTestSuite + SetUp"
 * @return: true setup success
 */
static BOOL IntTestSuiteSetUp()
{   
    LiteTestPrint("test_demo1 setup\n");
    return TRUE;
}

/**
 * @tc.teardown: define a setup for test suit, format:"IntTestSuite + TearDown"
 * @return: true teardown success
 */
static BOOL IntTestSuiteTearDown()
{
    LiteTestPrint("test_demo1 tearDown\n");
    return TRUE;
}

/**
 * @tc.number    : Test_Case_100
 * @tc.name      : Verify int check function
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(IntTestSuite, TestCase001, LEVEL1)
{
    TEST_ASSERT_EQUAL_INT(LEVEL2, LEVEL3);
};

/**
 * @tc.number    : Test_Case_200
 * @tc.name      : Verify int check function
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(IntTestSuite, TestCase002, LEVEL2)
{
    TEST_ASSERT_EQUAL_INT(LEVEL2, LEVEL2);
};

RUN_TEST_SUITE(IntTestSuite);