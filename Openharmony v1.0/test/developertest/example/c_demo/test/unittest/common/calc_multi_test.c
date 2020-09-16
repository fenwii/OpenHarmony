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

#include "test_framework.h"
#include "calc_multi.h"

/**
 * @tc.register: register a test suit named "CalcMultiTest"
 * @param: test subsystem name
 * @param: c_example module name
 * @param: CalcMultiTest test suit name
 */
LITE_TEST_SUIT(test, c_example, CalcMultiTest);

/**
 * @tc.setup: define a setup for test suit, format:"CalcMultiTest + SetUp"
 * @return: true——setup success
 */
static BOOL CalcMultiTestSetUp()
{
    LiteTestPrint("setup\n");
    return TRUE;
}

/**
 * @tc.teardown: define a setup for test suit, format:"CalcMultiTest + TearDown"
 * @return: true——teardown success
 */
static BOOL CalcMultiTestTearDown()
{
    LiteTestPrint("tearDown\n");
    return TRUE;
}

/**
 * @tc.name: calcMultiTest001
 * @tc.desc: Verify calc_multi function, not equal.
 * @tc.type: FUNC
 * @tc.require: require id
 * @tc.author: xxx
 */
LITE_TEST_CASE(CalcMultiTest, calcMultiTest001, Level1)
{
    TEST_ASSERT_EQUAL_INT(2, calc_multi(2, 2));
};

/**
 * @tc.name: calcMultiTest002
 * @tc.desc: Verify calc_multi function, equal.
 * @tc.type: FUNC
 * @tc.require: require id
 * @tc.author: xxx
 */
LITE_TEST_CASE(CalcMultiTest, calcMultiTest002, Level1)
{
    TEST_ASSERT_EQUAL_INT(2, calc_multi(2, 1));
};