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
 * @tc.name: register a test suit named "StringTestSuite"
 * @param: test subsystem name
 * @param: example module name
 * @param: StringTestSuite test suit name
 */
LITE_TEST_SUIT(test, example, StringTestSuite);

/**
 * @tc.setup: define a setup for test suit, format:"StringTestSuite + SetUp"
 * @return: true——setup success
 */
static BOOL StringTestSuiteSetUp()
{   
    LiteTestPrint("test_demo2 setup\n");
    return TRUE;
}

/**
 * @tc.teardown: define a setup for test suit, format:"StringTestSuite + TearDown"
 * @return: true——teardown success
 */
static BOOL StringTestSuiteTearDown()
{
    LiteTestPrint("test_demo2 tearDown\n");
    return TRUE;
}

/**
 * @tc.number    : Test_Case_300
 * @tc.name      : Verify string check function
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(StringTestSuite, TestCase003, LEVEL1)
{
    const char* value = "testing";
    TEST_ASSERT_EQUAL_STRING(value, "testing1");
};

/**
 * @tc.number    : Test_Case_400
 * @tc.name      : Verify string check function
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(StringTestSuite, TestCase004, LEVEL2)
{
    const char* value = "testing";
    TEST_ASSERT_EQUAL_STRING(value, "testing");
};

RUN_TEST_SUITE(StringTestSuite);