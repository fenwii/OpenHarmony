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

#ifndef HCTEST_INTERNAL_H
#define HCTEST_INTERNAL_H

#include "common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct TestResult TestResult;
struct TestResult {
    const int8  result;
    const char* messages;
};

typedef struct CTestCase CTestCase;
struct CTestCase {
    /**
    * @brief test case level
    * */
    const char *suite_name;

    /**
    * @brief test case level
    * */
    const char *case_name;

    /**
    * @brief test case level
    * */
    int8 level;

    /**
    * @brief test case line number
    * */
    int16 line_num;

    /**
    * @brief test case setup.
    * @param the test case addr.
    * @return TRUE success
    * */
    BOOL (*lite_setup)(void);

    /**
    * @brief  test case teardown.
    * @param the test case addr.
    * @return TRUE success
    * */
    BOOL (*lite_teardown)(void);

    /**
    * @brief execute the test case.
    * @param the test case addr.
    * @return test results
    * */
    void (*execute_func)(void);
};

/**
  * test case level
  */
enum TestLevel {
    LEVEL0 = 0,
    LEVEL1 = 1,
    LEVEL2 = 2,
    LEVEL3 = 3,
    LEVEL4 = 4,
    LEVEL_All = 9,
};

typedef struct CTestSuite CTestSuite;
struct CTestSuite {
    const char* subsystem_name;
    const char* module_name;
    const char* suite_name;
    const char* file;
    int16 times;
    Vector test_cases;
};

#define HCTEST_SERVICE "HCTEST"
#define TEST_FLAG 0x02
#define MSG_START_TEST 1
#define MAXIMUM_TRY_TIMES 3

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

