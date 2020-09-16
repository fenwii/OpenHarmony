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

osSemaphoreId_t  g_cmsisSemSema;
#define SEMAPHHORE_COUNT_HEX_MAX    0xFE
#define SEMAPHHORE_COUNT_INT0    0
#define SEMAPHHORE_COUNT_INT1    1
#define SEMAPHHORE_COUNT_INT10    10


/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisTaskFuncTestSuite
 */
LITE_TEST_SUIT(Cmsis, CmsisSem, CmsisSemFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL CmsisSemFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL CmsisSemFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew001, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    (void)osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew002, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT10, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    (void)osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew003, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT0, SEMAPHHORE_COUNT_INT10, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    (void)osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew004, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT0, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew005, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew006, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT10, SEMAPHHORE_COUNT_INT10, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew007, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_HEX_MAX, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreNew008, LEVEL1)
{
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT0, SEMAPHHORE_COUNT_HEX_MAX, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    osSemaphoreDelete(g_cmsisSemSema);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreDelete001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT10, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreDelete002, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT10, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore delete operation with semaphore_id = NULL 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreDelete003, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osSemaphoreDelete(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for acquire
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreAcquire001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreAcquire(g_cmsisSemSema, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for acquire
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreAcquire002, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreAcquire(g_cmsisSemSema, 0);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for acquire
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreAcquire003, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT0, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreAcquire(g_cmsisSemSema, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore acquire operation with semaphore_id = NULL 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreAcquire004, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osSemaphoreAcquire(NULL, 0);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for release
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreRelease001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);

    uwRet = osSemaphoreAcquire(g_cmsisSemSema, 0);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    uwRet = osSemaphoreRelease(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for release
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreRelease002, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);

    uwRet = osSemaphoreRelease(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    uwRet = osSemaphoreRelease(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for release
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreRelease003, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);

    uwRet = osSemaphoreRelease(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    uwRet = osSemaphoreAcquire(g_cmsisSemSema, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osSemaphoreRelease(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    uwRet = osSemaphoreRelease(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);

    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore release operation with semaphore_id = NULL 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreRelease004, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osSemaphoreRelease(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for get count
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreGetCount001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreGetCount(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(1, uwRet);
    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_HEX_MAX, SEMAPHHORE_COUNT_HEX_MAX, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreGetCount(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(SEMAPHHORE_COUNT_HEX_MAX, uwRet);
    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for get count
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreGetCount002, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT1, SEMAPHHORE_COUNT_INT0, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreGetCount(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_INT0, SEMAPHHORE_COUNT_INT1, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreGetCount(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(1, uwRet);
    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore operation for get count
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreGetCount003, LEVEL1)
{
    osStatus_t uwRet;    
    g_cmsisSemSema = osSemaphoreNew(SEMAPHHORE_COUNT_HEX_MAX, SEMAPHHORE_COUNT_HEX_MAX, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisSemSema);
    uwRet = osSemaphoreAcquire(g_cmsisSemSema, osWaitForever);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    
    uwRet = osSemaphoreGetCount(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(SEMAPHHORE_COUNT_HEX_MAX - 1, uwRet);
    uwRet = osSemaphoreDelete(g_cmsisSemSema);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_SEM_OPERATION_100
 * @tc.name      : semaphore get count operation with semaphore_id = NULL 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisSemFuncTestSuite, testOsSemaphoreGetCount004, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osSemaphoreGetCount(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);

};

RUN_TEST_SUITE(CmsisSemFuncTestSuite);
