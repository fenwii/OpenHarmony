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

#include "samgr_lite.h"
#include <hos_init.h>
#include <securec.h>
#include <los_base.h>
#include "hctest.h"
#include "parameter.h"

void setUp() {}
void tearDown() {}
void suiteSetUp(void) { }
int suiteTearDown(int num_failures) { return num_failures; }


static TestSuiteManager g_testSuiteManager;
static BOOL CompareInputType(const char *source, const char *input);
static void RunSingleTestCase(CTestCase* cTestCase,
                              const char *caseName, const int8 level);
static void runSingleTestSuite(CTestSuite* testSuite)
{
    int16 size = 0;
    if (testSuite == NULL) {
        return;
    }
    size = VECTOR_Size(&(testSuite->test_cases));
    UnityBegin(testSuite->file);
    int8 i;
    for (i = size - 1; i >= 0; i--) {
        CTestCase* cTestCase = (CTestCase *)(VECTOR_At(
            &(testSuite->test_cases), i));
        RunSingleTestCase(cTestCase, cTestCase->case_name, cTestCase->level);
    }
    UnityEnd();
}

static CTestSuite* GetTestSuite(const char *test_suite)
{
    CTestSuite* suite = NULL;
    TestSuiteManager* testMgr = GetTestMgrInstance();
    int16 size = VECTOR_Size(&(testMgr->test_suites));
    if (test_suite != NULL) {
        int8 i;
        for (i = 0; i < size; i++) {
            CTestSuite* curSuite = (CTestSuite *)(VECTOR_At(&(testMgr->test_suites), i));
            if (strcmp(curSuite->suite_name, test_suite) == 0) {
                suite = curSuite;
                break;
            }
        }
    }
    return suite;
}

static BOOL RegisterTestSuite(CTestSuite *testSuite)
{
    VECTOR_Add(&(g_testSuiteManager.test_suites), testSuite);
    return TRUE;
}

static BOOL RemoveTestSuite(CTestSuite *testSuite)
{
    VECTOR_Swap(&(g_testSuiteManager.test_suites),
                VECTOR_Find(&(g_testSuiteManager.test_suites), testSuite),
                testSuite);
    return TRUE;
}

static void AddTestCase(CTestCase *testCase)
{
    if (testCase == NULL) {
        return;
    }
    CTestSuite* suite = GetTestSuite(testCase->suite_name);
    if (suite == NULL) {
        CTestSuite suite_object;
        suite_object.subsystem_name = NULL;
        suite_object.module_name = NULL;
        suite_object.suite_name = testCase->suite_name;
        suite_object.test_cases = VECTOR_Make(NULL, NULL);
        suite = &suite_object;
        VECTOR_Add(&(g_testSuiteManager.test_suites), suite);
    }
    VECTOR_Add(&(suite->test_cases), testCase);
    return;
}

static BOOL CompareInputType(const char *source, const char *input)
{
    if (strcmp(input, CONST_STRING_SPACE) != 0 && strcmp(input, source) != 0) {
        return TRUE;
    }
    return FALSE;
}

static BOOL g_isBreak = FALSE;
static void RunSingleTestCase(CTestCase* cTestCase,
                              const char *caseName, const int8 level)
{
    if (cTestCase != NULL) {
        if (CompareInputType(cTestCase->case_name, caseName)
            || (cTestCase->level != level && level != LEVEL_All)) {
            g_isBreak = TRUE;
            return;
        }
        cTestCase->lite_setup();
        UnityDefaultTestRun(cTestCase->execute_func, cTestCase->case_name, cTestCase->line_num);
        cTestCase->lite_teardown();
    }
}

static void RunSpecialTestSuite(const char *subSystemName,
                               const char *moduleName,
                               const char *suiteName,
                               const char *caseName,
                               int caseLevel)
{
    int8 i;
    int8 j;
    int16 size = VECTOR_Size(&(g_testSuiteManager.test_suites));
    UNITY_BEGIN();
    for (i = 0; i < size; i++) {
        if (g_isBreak) {
            break;
        }
        CTestSuite* curSuite = (CTestSuite *)(VECTOR_At(
                                 &(g_testSuiteManager.test_suites), i));
        if (curSuite != NULL) {
            if (CompareInputType(curSuite->subsystem_name, subSystemName)
                || CompareInputType(curSuite->module_name, moduleName)
                || CompareInputType(curSuite->suite_name, suiteName)) {
                continue;
            }
            for (j = 0; j < VECTOR_Size(&(curSuite->test_cases)); j++) {
                CTestCase* cTestCase = (CTestCase *)(VECTOR_At(
                    &(curSuite->test_cases), j));
                RunSingleTestCase(cTestCase, caseName, caseLevel);
            }
        }
    }
    UNITY_END();
}

static void RunTestSuite(const char* suite_name)
{
    printf("Start to run test suite:%s\n", suite_name);
    CTestSuite* curSuite = GetTestSuite(suite_name);
    if (curSuite != NULL) {
        int16 times = curSuite->times;
        int16 i;
        for (i = 0; i < times; i++) {
            printf("Run test suite %d times\n", i+1);
            runSingleTestSuite(curSuite);
        }
    }
}

void LiteTestPrint(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf(fmt, ap);
    va_end(ap);
}

void ObtainSystemParams(void)
{
    printf("******To Obtain Product Params Start******\n");
    printf("The VersionID is [%s]\n", GetVersionId());
    printf("The Sdk Api Level is [%s]\n", GetFirstApiLevel());
    printf("The Security Patch is [%s]\n", GetSecurityPatchTag());
    printf("The AbiList is [%s]\n", GetAbiList());
    printf("The OS Version is [%s]\n", GetDisplayVersion());
    printf("The BuildRootHash is [%s]\n", GetBuildRootHash());
    printf("The HardwareModel is [%s]\n", GetHardwareModel());
    printf("The HardwareProfile is [%s]\n", GetHardwareProfile());
    printf("******To Obtain Product Params End  ******\n");
    return;
}

static void InitTestSuiteMgr(void)
{
    g_testSuiteManager.test_suites = VECTOR_Make(NULL, NULL);
    g_testSuiteManager.GetTestSuite = GetTestSuite;
    g_testSuiteManager.RegisterTestSuite = RegisterTestSuite;
    g_testSuiteManager.AddTestCase = AddTestCase;
    g_testSuiteManager.RemoveTestSuite = RemoveTestSuite;
    g_testSuiteManager.RunSpecialTestSuite = RunSpecialTestSuite;
    g_testSuiteManager.RunTestSuite = RunTestSuite;
    printf("[%10s] HCTest Framework inited.\n",  "HCtest Service");
    ObtainSystemParams();
}
CORE_INIT(InitTestSuiteMgr);
TestSuiteManager* GetTestMgrInstance(void)
{
    return &g_testSuiteManager;
}