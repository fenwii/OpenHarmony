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

osThreadId_t g_priTaskID01;
osPriority_t g_setPriority;

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisTaskPriFuncTestSuite
 */
LITE_TEST_SUIT(Cmsis, Cmsistask, CmsisTaskPriFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL CmsisTaskPriFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL CmsisTaskPriFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

static void CmsisThreadGetPriorityFunc001(void const *argument)
{
    (void)argument;
    osThreadAttr_t attr;
    g_priTaskID01 = osThreadGetId();
    attr.priority = osThreadGetPriority(g_priTaskID01);
    TEST_ASSERT_EQUAL_INT(g_setPriority, attr.priority);
    osThreadExit();
}

static void CmsisThreadSetPriorityFunc001(void const *argument)
{
    (void)argument;
    osThreadAttr_t attr;
    UINT32 uwRet;
    g_priTaskID01 = osThreadGetId();
    uwRet = osThreadSetPriority(g_priTaskID01, g_setPriority);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    attr.priority = osThreadGetPriority(g_priTaskID01);
    TEST_ASSERT_EQUAL_INT(g_setPriority, attr.priority);
    osThreadExit();
}

static void CmsisThreadSetPriorityFunc002(void const *argument)
{
    (void)argument;
    UINT32 uwRet;
    g_priTaskID01 = osThreadGetId();
    uwRet = osThreadSetPriority(g_priTaskID01, g_setPriority);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
    osThreadExit();
}

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityLow1;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadGetPriority(NULL);
    TEST_ASSERT_EQUAL_INT(osPriorityError, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority003, LEVEL1)
{
    UINT32 uwRet;
    g_priTaskID01 =  osThreadGetId();
    uwRet = osThreadGetPriority(g_priTaskID01);
    TEST_ASSERT_EQUAL_INT(osPriorityNormal, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityLow7;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityBelowNormal;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityBelowNormal7;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityNormal;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityNormal7;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityAboveNormal;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadGetPriority010, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_setPriority = osPriorityAboveNormal6;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_setPriority;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetPriorityFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input1 exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority001, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadSetPriority(NULL, osPriorityNormal);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input2 exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority002, LEVEL1)
{
    UINT32 uwRet;
    g_priTaskID01 =  osThreadGetId();
    uwRet = osThreadSetPriority(g_priTaskID01, osPriorityNone);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority003, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityNone;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityIdle;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityLow;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityLow1;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityLow7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityBelowNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityBelowNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority010, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority011, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority012, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority013, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityAboveNormal6;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority014, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityAboveNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority015, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityHigh;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority016, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityHigh7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority017, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityRealtime;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority018, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityRealtime7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority019, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityISR;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority020, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityError;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority021, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1; 
    g_setPriority = osPriorityReserved;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority022, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityNone;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority023, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityIdle;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority024, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityLow;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority025, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityLow1;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority026, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityLow7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority027, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityBelowNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority028, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityBelowNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority029, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority030, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority031, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority032, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityAboveNormal6;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority033, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityAboveNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority034, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityHigh;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority035, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityHigh7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority036, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityRealtime;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority037, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityRealtime7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority038, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityISR;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority039, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityError;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority040, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal; 
    g_setPriority = osPriorityReserved;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority041, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityNone;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority042, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityIdle;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority043, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityLow;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority044, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityLow1;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority045, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityLow7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority046, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityBelowNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority047, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityBelowNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority048, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority049, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority050, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority051, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityAboveNormal6;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority052, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityAboveNormal7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority053, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityHigh;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority054, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityHigh7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority055, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityRealtime;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority056, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityRealtime7;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority057, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityISR;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority058, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityError;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for set priority input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsThreadSetPriority059, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6; 
    g_setPriority = osPriorityReserved;
    id = osThreadNew((osThreadFunc_t)CmsisThreadSetPriorityFunc002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : delay operation 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1

 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsDelay001, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : delay operation 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1

 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsDelay002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osDelay(0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : delay until operation 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1

 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsDelayUntil001, LEVEL1)
{
    UINT32 uwRet;
    UINT32 uwTickCnt;
    UINT32 uwUntilTickCnt;
    uwTickCnt = osKernelGetTickCount();
    uwUntilTickCnt = uwTickCnt + DELAY_TICKS_10;
    uwRet = osDelayUntil(uwUntilTickCnt);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : delay until operation input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsDelayUntil002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osDelayUntil(DELAY_TICKS_1);
    TEST_ASSERT_EQUAL_INT(osError, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : delay until operation input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskPriFuncTestSuite, testOsDelayUntil003, LEVEL1)
{
    UINT32 uwRet;
    UINT32 uwTickCnt;
    UINT32 uwUntilTickCnt;
    uwTickCnt = osKernelGetTickCount();
    uwUntilTickCnt = uwTickCnt - DELAY_TICKS_10;
    uwRet = osDelayUntil(uwUntilTickCnt);
    TEST_ASSERT_EQUAL_INT(osError, uwRet);
};

RUN_TEST_SUITE(CmsisTaskPriFuncTestSuite);
