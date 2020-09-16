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

UINT32 g_threadCount;
UINT16 g_cmsisTestTaskCount;
osThreadId_t g_puwTaskID01;
osThreadId_t g_puwTaskID02;
osPriority_t g_threadPriority;

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisTaskFuncTestSuite
 */
LITE_TEST_SUIT(Cmsis, Cmsistask, CmsisTaskFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL CmsisTaskFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL CmsisTaskFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

static void CmsisThreadCreatFunc(void const *argument)
{
    (void)argument;
    osThreadExit();
}

static void CmsisThreadCreat002Func001(void const *argument)
{
    (void)argument;
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadCreat002Func002(void const *argument)
{
    (void)argument;
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadCreat003Func001(void const *argument)
{
    (void)argument;
    TEST_ASSERT_EQUAL_INT(0, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    osThreadExit();
}

static void CmsisThreadCreat003Func002(void const *argument)
{
    (void)argument;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;    
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_4, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    osThreadExit();
}

static void CmsisThreadCreat004Func002(void const *argument)
{
    (void)argument;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    osThreadExit();
}

static void CmsisThreadCreat004Func001(void const *argument)
{
    (void)argument;
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6;
    TEST_ASSERT_EQUAL_INT(0, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreat004Func002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    osThreadExit();
}

static void CmsisThreadCreat005Func001(void const *argument)
{
    (void)argument;
    UINT32 uwIndex;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
    for (uwIndex = 0; uwIndex < TEST_TIME; uwIndex++) { 
        printf("test the thread running delay:%d \t\n", uwIndex);
    }
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadGetIDFunc001(void const *argument)
{
    (void)argument;
    g_puwTaskID01 = osThreadGetId();
    TEST_ASSERT_NOT_NULL(g_puwTaskID01);
    osThreadExit();
}

static void CmsisThreadGetNameFunc001(void const *argument)
{
    (void)argument;
    osThreadAttr_t attr;
    g_puwTaskID01 = osThreadGetId();
    attr.name = osThreadGetName(g_puwTaskID01);
    TEST_ASSERT_EQUAL_STRING("testThreadGetName", attr.name);
    osThreadExit();
}

static void CmsisThreadGetStateFunc001(void const *argument)
{
    (void)argument;
    osThreadState_t state;
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    
    g_puwTaskID02 = osThreadGetId();
    state = osThreadGetState(g_puwTaskID02);
    TEST_ASSERT_EQUAL_INT(osThreadRunning, state);
    osThreadExit();
}

static void CmsisThreadGetStateFunc002(void const *argument)
{
    (void)argument;
    osThreadState_t state;
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadReady, state);
    
    g_puwTaskID02 = osThreadGetId();
    state = osThreadGetState(g_puwTaskID02);
    TEST_ASSERT_EQUAL_INT(osThreadRunning, state);
    osThreadExit();
}

static void CmsisThreadSuspendFunc001(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    g_puwTaskID01 = osThreadGetId();
    uwRet = osThreadSuspend(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    osThreadExit();
}

static void CmsisThreadGetStackSizeFunc001(void const *argument)
{
    (void)argument;
    osThreadAttr_t attr;
    g_puwTaskID01 = osThreadGetId();
    attr.stack_size = osThreadGetStackSize(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(TEST_TASK_STACK_SIZE, attr.stack_size);
    osThreadExit();
}

static void CmsisThreadGetStackSpaceFunc001(void const *argument)
{
    (void)argument;
    UINT32 uwCount;
    g_puwTaskID01 =  osThreadGetId();
    uwCount = osThreadGetStackSpace(g_puwTaskID01);
    TEST_ASSERT_GREATER_THAN_INT32(0, uwCount);
    osThreadExit();
}

static void CmsisThreadYieldFunc002(void const *argument)
{
    (void)argument;
    osThreadState_t state;
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadReady, state);
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadYieldFunc001(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    osThreadId_t id;
    osThreadState_t state;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
    g_puwTaskID01 =  osThreadGetId();
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadRunning, state);
    uwRet = osThreadYield();  
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadYieldFunc003(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    osThreadId_t id;
    osThreadState_t state;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    g_puwTaskID01 =  osThreadGetId();
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadRunning, state);
    uwRet = osThreadYield();  
    TEST_ASSERT_EQUAL_INT(osError, uwRet);
    osThreadExit();
}

static void CmsisThreadResumeFunc002(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    osDelay(DELAY_TICKS_5);
    osThreadExit();
}

static void CmsisThreadResumeFunc001(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew((osThreadFunc_t)CmsisThreadResumeFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    uwRet = osThreadSuspend(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadTerminateFunc001(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    g_puwTaskID01 = osThreadGetId();
    uwRet = osThreadTerminate(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
    osThreadExit();
}

static void CmsisThreadGetCountFunc002(void const *argument)
{
    (void)argument;
    UINT32 uwRet;
    uwRet = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(1, uwRet);
    osThreadExit();
}

static void CmsisThreadGetCountFunc001(void const *argument)
{
    (void)argument;
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osThreadExit();
}

static void CmsisThreadGetCountFunc003(void const *argument)
{
    (void)argument;
    UINT32 uwRet;
    uwRet = osThreadGetCount();
    TEST_ASSERT_EQUAL_INT(g_threadCount + 1, uwRet);
    osThreadExit();
}

static void CmsisOSKernelLockFunc002(void const *argument)
{
    (void)argument;
    g_cmsisTestTaskCount++;
    osThreadExit();
}

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew001, LEVEL1)
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
    
    osDelay(DELAY_TICKS_5);
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, NULL);
    TEST_ASSERT_NULL(id);
    id = osThreadNew(NULL, NULL, NULL);
    TEST_ASSERT_NULL(id);
    id = osThreadNew(NULL, NULL, &attr);
    TEST_ASSERT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew002, LEVEL1)
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
    g_cmsisTestTaskCount = 0;
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreat002Func001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(0, g_cmsisTestTaskCount);

    g_cmsisTestTaskCount++;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreat002Func002, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for delay scheduler 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew003, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    osThreadAttr_t attr1;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadCreat003Func001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
    g_cmsisTestTaskCount++;
    attr1.name = "test1";
    attr1.attr_bits = 0U;
    attr1.cb_mem = NULL;
    attr1.cb_size = 0U;
    attr1.stack_mem = NULL;
    attr1.stack_size = TEST_TASK_STACK_SIZE;
    attr1.priority = osPriorityAboveNormal;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadCreat003Func002, NULL, &attr1);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_5, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for nesting schedule 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    g_cmsisTestTaskCount = 0;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreat004Func001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for cycle schdule 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew005, LEVEL1)
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
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreat005Func001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_1);
    g_cmsisTestTaskCount++;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNone;

    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityIdle;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew009, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew0010, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew011, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew012, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew013, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew014, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew015, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew016, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew017, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew018, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityHigh;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew019, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityHigh7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew020, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityRealtime;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew021, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityRealtime7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew022, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityISR;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew023, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityError;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for creat fail
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew024, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityReserved;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread creat operation with func = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew025, LEVEL1)
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
    
    id = osThreadNew(NULL, NULL, &attr);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread creat operation with attr = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadNew026, LEVEL1)
{
    osThreadId_t id;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadCreatFunc, NULL, NULL);
    TEST_ASSERT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal;

    g_cmsisTestTaskCount = 0;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend001, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId001, LEVEL1)
{
    g_puwTaskID01 = osThreadGetId();
    TEST_ASSERT_NOT_NULL(g_puwTaskID01);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId002, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId003, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId006, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId009, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetIDFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT((uintptr_t)id, (uintptr_t)g_puwTaskID01);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get ID 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetId010, LEVEL1)
{
    g_puwTaskID01 = osThreadGetId();
    TEST_ASSERT_NOT_NULL(g_puwTaskID01);
    osThreadExit();
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_cmsisTestTaskCount = 0;
    g_puwTaskID01 = 0;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace001, LEVEL1)
{
    UINT32 uwCount;
    g_cmsisTestTaskCount = 0;
    g_puwTaskID01 =  osThreadGetId();
    uwCount = osThreadGetStackSpace(g_puwTaskID01);
    TEST_ASSERT_GREATER_THAN_INT32(0, uwCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityLow1;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield002, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityLow7;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield003, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityBelowNormal;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityBelowNormal7;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityNormal;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityNormal7;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityAboveNormal;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for yield 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    g_threadPriority = osPriorityAboveNormal6;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = g_threadPriority;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc001, NULL, &attr);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread yield operation for thread with different priority
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadYield009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadYieldFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for resume 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadResume001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadResumeFunc001, NULL, &attr);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_3, g_cmsisTestTaskCount);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate001, LEVEL1)
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
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount003, LEVEL1)
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
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount007, LEVEL1)
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
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for count 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetCount010, LEVEL1)
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
    g_threadCount = osThreadGetCount();
    TEST_ASSERT_GREATER_THAN_INT32(0, g_threadCount);
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetCountFunc003, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName002, LEVEL1)
{
    osThreadAttr_t attr;
    attr.name = osThreadGetName(NULL);
    TEST_ASSERT_NULL(attr.name);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName003, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow1;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "testThreadGetName";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetNameFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get name 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetName010, LEVEL1)
{
    osThreadAttr_t attr;
    g_puwTaskID01 = osThreadGetId();
    attr.name = osThreadGetName(g_puwTaskID01);
    TEST_ASSERT_NOT_NULL(attr.name);
    osThreadExit();
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState002, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osThreadGetState(NULL);
    TEST_ASSERT_EQUAL_INT(osThreadError, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState003, LEVEL1)
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
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState007, LEVEL1)
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
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState009, LEVEL1)
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
    
    g_puwTaskID01 = osThreadGetId();
    id = osThreadNew ((osThreadFunc_t)CmsisThreadGetStateFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get state 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetState010, LEVEL1)
{
    osThreadState_t state;
    g_puwTaskID01 = osThreadGetId();
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadRunning, state);
    osThreadExit();
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend002, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osThreadSuspend(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend003, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend004, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend005, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend006, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend007, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend008, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for suspend  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadSuspend009, LEVEL1)
{
    osThreadId_t id;
    osStatus_t uwRet;
    osThreadAttr_t attr;
    osThreadState_t state;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal6;
    id = osThreadNew ((osThreadFunc_t)CmsisThreadSuspendFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    state = osThreadGetState(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osThreadBlocked, state);
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadGetStackSize(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize003, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize007, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSizeFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack size 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSize010, LEVEL1)
{
    osThreadAttr_t attr;
    g_puwTaskID01 = osThreadGetId();
    attr.stack_size = osThreadGetStackSize(g_puwTaskID01);
    TEST_ASSERT_GREATER_THAN_INT32(0, attr.stack_size);
    osThreadExit();
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadGetStackSpace(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace003, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace006, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace007, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace009, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;

    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for get stack space 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadGetStackSpace010, LEVEL1)
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
    
    id = osThreadNew((osThreadFunc_t)CmsisThreadGetStackSpaceFunc001, NULL, &attr);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for resume input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1

 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadResume002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadResume(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for resume input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1

 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadResume003, LEVEL1)
{
    UINT32 uwRet;
    g_puwTaskID01 = osThreadGetId();
    uwRet = osThreadResume(g_puwTaskID01);
    TEST_ASSERT_EQUAL_INT(osErrorResource, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osThreadTerminate(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate003, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityLow7;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate004, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate005, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityBelowNormal7;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate006, LEVEL1)
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
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    osDelay(DELAY_TICKS_5);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate007, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityNormal7;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate008, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : thread operation for terminate 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsThreadTerminate009, LEVEL1)
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
    g_cmsisTestTaskCount = 0;
    g_cmsisTestTaskCount++;
    id = osThreadNew((osThreadFunc_t)CmsisThreadTerminateFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for get info
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelGetInfo001, LEVEL1)
{
    CHAR infobuf[100];
    osVersion_t osv;
    osStatus_t status;
    status = osKernelGetInfo(&osv, infobuf, sizeof(infobuf));
    TEST_ASSERT_EQUAL_INT(osOK, status); 
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for get state
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelGetState001, LEVEL1)
{
    osKernelState_t uwRet;
    uwRet = osKernelGetState();
    TEST_ASSERT_EQUAL_INT(osKernelRunning, uwRet);    
};

/**
 * @tc.number    : SUB_KERNEL_Cmsis_TASK_OPERATION_100
 * @tc.name      : kernel operation for get state
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelGetState002, LEVEL1)
{
    osKernelLock ();
    osKernelState_t uwRet;
    uwRet = osKernelGetState();
    TEST_ASSERT_EQUAL_INT(osKernelLocked, uwRet); 
    osKernelUnlock ();   
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for lock
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelLock001, LEVEL1)
{
    UINT32 uwRet;    
    uwRet = osKernelLock();     
    TEST_ASSERT_EQUAL_INT(0, uwRet);  
    uwRet = osKernelLock();     
    TEST_ASSERT_EQUAL_INT(1, uwRet);    
    osKernelUnlock();
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for lock 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1

 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelLock002, LEVEL1)
{
    UINT32 uwRet;
    osThreadId_t id;
    osThreadAttr_t attr;
    g_cmsisTestTaskCount = 0;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = osPriorityAboveNormal;
    
    uwRet = osKernelLock();     
    TEST_ASSERT_EQUAL_INT(0, uwRet);  
    id = osThreadNew((osThreadFunc_t)CmsisOSKernelLockFunc002, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    TEST_ASSERT_EQUAL_INT(0, g_cmsisTestTaskCount);    
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(1, uwRet);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_cmsisTestTaskCount);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for unlock 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelUnLock001, LEVEL1)
{
    UINT32 uwRet; 
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(0, uwRet); 
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for unlock
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelUnLock002, LEVEL1)
{
    UINT32 uwRet;        
    (void)osKernelLock();
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(1, uwRet);
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(0, uwRet); 
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for unlock
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelUnLock003, LEVEL1)
{
    UINT32 uwRet;        
    (void)osKernelLock();
    (void)osKernelLock();
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(1, uwRet);
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(0, uwRet); 
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for restore lock 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelRestoreLock001, LEVEL1)
{
    UINT32 uwRet;   
    (void)osKernelLock(); 
    uwRet = osKernelRestoreLock(0);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for restore lock 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelRestoreLock002, LEVEL1)
{
    UINT32 uwRet;   
    (void)osKernelLock(); 
    (void)osKernelLock(); 
    uwRet = osKernelRestoreLock(0);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_TASK_OPERATION_100
 * @tc.name      : kernel operation for restore lock 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisTaskFuncTestSuite, testOsKernelRestoreLock003, LEVEL1)
{
    UINT32 uwRet;  
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(0, uwRet);
    uwRet = osKernelRestoreLock(1);
    TEST_ASSERT_EQUAL_INT(1, uwRet);
    uwRet = osKernelUnlock();
    TEST_ASSERT_EQUAL_INT(1, uwRet);
};

RUN_TEST_SUITE(CmsisTaskFuncTestSuite);
