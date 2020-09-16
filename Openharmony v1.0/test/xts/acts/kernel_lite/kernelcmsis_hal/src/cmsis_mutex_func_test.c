/**
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "hos_types.h"
#include <securec.h>
#include "hctest.h"
#include "los_config.h"
#include "cmsis_os2.h"
#include "kernel_test.h"

#define LOS_WAIT_FOREVER 0xFFFFFFFF

UINT16 g_cmsisTestMutexCount;
osMutexId_t g_cmsisMutexId;
osMutexAttr_t g_cmsisMutexAttr;

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisMutexFuncTestSuite
 */
LITE_TEST_SUIT(Cmsis, Cmsismutex, CmsisMutexFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL CmsisMutexFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL CmsisMutexFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

static void CmsisMutexGetOwnerFunc001(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    osThreadId_t id1;
    osThreadId_t id2;
    osThreadAttr_t attr;
    g_cmsisMutexId = osMutexNew(&g_cmsisMutexAttr);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);

    uwRet = osMutexAcquire(g_cmsisMutexId, LOS_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    id1 = osMutexGetOwner(g_cmsisMutexId);
    id2 = osThreadGetId(); 
    TEST_ASSERT_EQUAL_STRING(id1, id2);

    attr.name = osThreadGetName(id1);
    TEST_ASSERT_EQUAL_STRING("testMutexGetOwner001", attr.name);
    
    uwRet = osMutexRelease(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    osThreadExit();
}

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexNew001, LEVEL1)
{
    g_cmsisMutexId = osMutexNew(NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);
    (void)osMutexDelete(g_cmsisMutexId);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexNew002, LEVEL1)
{
    g_cmsisMutexId = osMutexNew(&g_cmsisMutexAttr);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);
    (void)osMutexDelete(g_cmsisMutexId);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexDelete001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMutexId = osMutexNew(NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);
    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexDelete002, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMutexId = osMutexNew(&g_cmsisMutexAttr);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);
    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for acquire
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexDelete003, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMutexId = osMutexNew(NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);

    osMutexAcquire(g_cmsisMutexId, LOS_WAIT_FOREVER);
    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    osMutexRelease(g_cmsisMutexId);
    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex delete operation with mutex_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexDelete004, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osMutexDelete(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex acquire operation with mutex_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexAcquire001, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osMutexAcquire(NULL, LOS_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for acquire
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexAcquire002, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMutexId = osMutexNew(&g_cmsisMutexAttr);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);

    uwRet = osMutexAcquire(g_cmsisMutexId, LOS_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    (void)osMutexRelease(g_cmsisMutexId);
    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for release
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexRelease001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMutexId = osMutexNew(&g_cmsisMutexAttr);
    TEST_ASSERT_NOT_NULL(g_cmsisMutexId);

    uwRet = osMutexAcquire(g_cmsisMutexId, LOS_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    uwRet = osMutexRelease(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMutexDelete(g_cmsisMutexId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex release operation with mutex_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexRelease002, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osMutexRelease(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex operation for get owner
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexGetOwner001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "testMutexGetOwner001";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisMutexGetOwnerFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MUTEX_OPERATION_100
 * @tc.name      : mutex get owner operation with mutex_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMutexFuncTestSuite, testOsMutexGetOwner002, LEVEL1)
{
    osThreadId_t id;
    id = osMutexGetOwner(NULL);
    TEST_ASSERT_NULL(id);
};

RUN_TEST_SUITE(CmsisMutexFuncTestSuite);
