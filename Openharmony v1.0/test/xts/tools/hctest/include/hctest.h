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

#ifndef HCTEST_H
#define HCTEST_H
#ifndef HCTEST_REPEAT_TIMES
#define HCTEST_REPEAT_TIMES 1
#endif
#include <hos_init.h>
#include "unity.h"
#include "hctest_internal.h"

#define CONST_EMPTY_STRING    "" 
#define CONST_STRING_SPACE    " "
#define CONST_DOT_STRING      ","

#define TEST_INIT(func) LAYER_INITCALL_DEF(func, test, "test")
#define TEST_INIT_PRI(func, priority) LAYER_INITCALL(func, test, "test", priority)
typedef struct TestSuiteManager {
    /**
    * @brief get the test suite by suite name
    * @param the test suite name
    * @return the TestSuite point
    * */
    CTestSuite* (*GetTestSuite)(const char *test_suite);
    BOOL (*RegisterTestSuite)(CTestSuite *testSuite);

    /**
    * @brief remove the test suite.
    * @param the test case addr.
    * @return TRUE success
    * */
    BOOL (*RemoveTestSuite)(CTestSuite *testSuite);

    /**
    * @brief remove the test suite.
    * @param the test case addr.
    * @return TRUE success
    * */
    void (*AddTestCase)(CTestCase *testCase);

    /**
     * @brief remove special test suite.
     * @param caseName
     */
    void (*RunSpecialTestSuite)(const char *subSystemName,
                               const char *moduleName,
                               const char *suiteName,
                               const char *caseName,
                               int caseLevel);

    void  (*RunTestSuite)(const char* suite_name);

    Vector test_suites;
}TestSuiteManager;
TestSuiteManager *GetTestMgrInstance(void);

#define LITE_TEST_SUIT(subsystem, module, test_suite) \
static CTestSuite suite_object##test_suite;\
static void initSuite##test_suite(void) {\
    suite_object##test_suite.subsystem_name = #subsystem;\
    suite_object##test_suite.module_name = #module;\
    suite_object##test_suite.suite_name = #test_suite;\
    suite_object##test_suite.file = __FILE__;\
    suite_object##test_suite.times = HCTEST_REPEAT_TIMES;\
    suite_object##test_suite.test_cases = VECTOR_Make(NULL, NULL);\
    TestSuiteManager* testMgr = GetTestMgrInstance();\
    testMgr->RegisterTestSuite(&(suite_object##test_suite));\
}\
SYS_SERVICE_INIT(initSuite##test_suite);

#define LITE_TEST_CASE(test_suite, case_object, test_level) \
static void case_object##_runTest(void);\
static CTestCase create##case_object;\
static void initCase##case_object(void) {\
    create##case_object.suite_name = #test_suite;\
    create##case_object.case_name = #case_object;\
    create##case_object.level = test_level;\
    create##case_object.line_num = __LINE__; \
    create##case_object.lite_setup = test_suite##SetUp; \
    create##case_object.lite_teardown = test_suite##TearDown;\
    create##case_object.execute_func = case_object##_runTest;\
    TestSuiteManager* testMgr = GetTestMgrInstance();\
    testMgr->AddTestCase(&(create##case_object));\
}\
SYS_RUN(initCase##case_object);\
static void case_object##_runTest(void)


#define RUN_TEST_SUITE(test_suite) \
static void runSuite##test_suite(void) {\
    TestSuiteManager* testMgr = GetTestMgrInstance(); \
    testMgr->RunTestSuite(#test_suite); \
}\
TEST_INIT(runSuite##test_suite);

void LiteTestPrint(const char *fmt, ...);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* HCTEST_H */