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

osEventFlagsId_t g_eventId;
UINT16 g_cmsisTestEventCount;
#define EVENT_MASK_HEX_1 0x01
#define EVENT_MASK_HEX_2 0x02
#define EVENT_MASK_HEX_4 0x04
#define EVENT_MASK_HEX_10 0x10
#define EVENT_MASK_HEX_11 0x11
#define TIMEOUT_NUM_3 3
#define TIMEOUT_NUM_10 10
#define INVALID_FLAG_OPTION 0x00000004U

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisEventFuncTestSuite
 */
LITE_TEST_SUIT(Cmsis, Cmsisevent, CmsisEventFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL CmsisEventFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL CmsisEventFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

static void CmsisEventFlagsWaitFunc001(void const *argument)
{
    (void)argument;
    UINT32 uwRet;
    g_cmsisTestEventCount++;
    uwRet = osEventFlagsWait(g_eventId, EVENT_MASK_HEX_11, (osFlagsWaitAll | osFlagsNoClear), osWaitForever);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_11, uwRet);
    g_cmsisTestEventCount++;
    osThreadExit();
}

static void CmsisEventFlagsSetFunc002(void const *argument)
{
    (void)argument;
    UINT32 uwRet;
    g_cmsisTestEventCount++;
    uwRet = osEventFlagsWait(g_eventId, EVENT_MASK_HEX_11, (osFlagsWaitAll | osFlagsNoClear), TIMEOUT_NUM_3);
    TEST_ASSERT_EQUAL_INT(osErrorTimeout, uwRet);
    g_cmsisTestEventCount++;

    uwRet = osEventFlagsWait(g_eventId, EVENT_MASK_HEX_4, (osFlagsWaitAll | osFlagsNoClear), osWaitForever);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_4, uwRet);
    g_cmsisTestEventCount++;
    osThreadExit();
}

static void CmsisEventFlagsClearFunc001(void const *argument)
{
    (void)argument;
    UINT32 uwRet;
    g_cmsisTestEventCount++;
    uwRet = osEventFlagsWait(g_eventId, EVENT_MASK_HEX_1, osFlagsWaitAll, osWaitForever);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_1, uwRet);
    g_cmsisTestEventCount++;
    osThreadExit();
}

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsNew001, LEVEL1)
{
    g_eventId = osEventFlagsNew(NULL);
    TEST_ASSERT_NOT_NULL(g_eventId);
    (void)osEventFlagsDelete(g_eventId);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for delete 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsDelete001, LEVEL1)
{
    UINT32 uwRet;
    g_eventId = osEventFlagsNew(NULL);
    TEST_ASSERT_NOT_NULL(g_eventId);
    
    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event delete operation with EventFlagsId = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsDelete002, LEVEL1)
{
    UINT32 uwRet;
    
    uwRet = osEventFlagsDelete(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for flags set
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsSet001, LEVEL1)
{
    UINT32 uwRet;
    g_eventId = osEventFlagsNew(NULL);
    uwRet = osEventFlagsSet(g_eventId, EVENT_MASK_HEX_10);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_10, uwRet);
    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for flags set
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsSet002, LEVEL1)
{
    UINT32 uwRet;
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;    

    g_cmsisTestEventCount = 0;
    g_eventId = osEventFlagsNew(NULL);
    TEST_ASSERT_NOT_NULL(g_eventId);
    id = osThreadNew((osThreadFunc_t)CmsisEventFlagsSetFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);

    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestEventCount);
    g_cmsisTestEventCount++;
    uwRet=osEventFlagsSet(g_eventId, EVENT_MASK_HEX_2);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestEventCount);

    g_cmsisTestEventCount++;
    uwRet=osEventFlagsSet(g_eventId, EVENT_MASK_HEX_11);
    osDelay(DELAY_TICKS_5);

    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_4, g_cmsisTestEventCount);
    uwRet=osEventFlagsSet(g_eventId, EVENT_MASK_HEX_4);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_5, g_cmsisTestEventCount);
    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event flags set operation with EventFlagsId = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsSet003, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osEventFlagsSet(NULL, EVENT_MASK_HEX_10);
    TEST_ASSERT_EQUAL_INT(osFlagsErrorParameter, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for wait
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsWait001, LEVEL1)
{
    UINT32 uwRet;
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;

    g_cmsisTestEventCount = 0;
    g_eventId = osEventFlagsNew(NULL);
    TEST_ASSERT_NOT_NULL(g_eventId);   
    id = osThreadNew((osThreadFunc_t)CmsisEventFlagsWaitFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);

    uwRet = osEventFlagsSet(g_eventId, EVENT_MASK_HEX_10);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_10, uwRet);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestEventCount);

    uwRet = osEventFlagsSet(g_eventId, EVENT_MASK_HEX_1);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_11, uwRet);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestEventCount);

    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for invalid option
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsWait002, LEVEL1)
{
    UINT32 uwRet;
    g_eventId = osEventFlagsNew(NULL);
    TEST_ASSERT_NOT_NULL(g_eventId);   

    uwRet = osEventFlagsWait(g_eventId, EVENT_MASK_HEX_11, INVALID_FLAG_OPTION, osWaitForever);
    TEST_ASSERT_EQUAL_INT(osFlagsErrorParameter, uwRet);

    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event wait operation with EventFlagsId = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsWait003, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osEventFlagsWait(NULL, EVENT_MASK_HEX_11, (osFlagsWaitAll | osFlagsNoClear), osWaitForever);
    TEST_ASSERT_EQUAL_INT(osFlagsErrorParameter, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for flags get
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsGet001, LEVEL1)
{
    UINT32 uwRet;
    g_eventId = osEventFlagsNew(NULL);
    uwRet = osEventFlagsSet(g_eventId, EVENT_MASK_HEX_10);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_10, uwRet);
    uwRet = 0;
    uwRet = osEventFlagsGet(g_eventId);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_10, uwRet);
    
    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event flags get operation with EventFlagsId = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsGet002, LEVEL1)
{
    UINT32 uwRet; 
    uwRet = osEventFlagsGet(NULL);
    TEST_ASSERT_EQUAL_INT(osFlagsErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event operation for flags clear
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsClear001, LEVEL1)
{
    UINT32 uwRet;
    osThreadId_t id;

    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;

    g_cmsisTestEventCount = 0;
    g_eventId = osEventFlagsNew(NULL);
    id = osThreadNew((osThreadFunc_t)CmsisEventFlagsClearFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    uwRet = osEventFlagsSet(g_eventId, EVENT_MASK_HEX_10);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_10, uwRet);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestEventCount);
    
    uwRet = osEventFlagsClear(g_eventId, 0xffff);
    TEST_ASSERT_EQUAL_INT(EVENT_MASK_HEX_10, uwRet);
    uwRet = osEventFlagsGet(g_eventId);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
    uwRet = osEventFlagsSet(g_eventId, EVENT_MASK_HEX_1);
    // after the event is triggered, the flag is reset to be zero
    TEST_ASSERT_EQUAL_INT(0, uwRet);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestEventCount);
    uwRet = osEventFlagsDelete(g_eventId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_EVENT_OPERATION_100
 * @tc.name      : event flags clear operation with EventFlagsId = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisEventFuncTestSuite, testOsEventFlagsClear002, LEVEL1)
{
    UINT32 uwRet; 
    uwRet = osEventFlagsClear(NULL, 0xffff);
    TEST_ASSERT_EQUAL_INT(osFlagsErrorParameter, uwRet);
};

RUN_TEST_SUITE(CmsisEventFuncTestSuite);
