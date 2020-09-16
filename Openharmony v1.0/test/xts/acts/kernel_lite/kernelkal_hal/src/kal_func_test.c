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
#include "kal.h"
#include "cmsis_os2.h"
#include "los_task_pri.h"


UINT16 g_kalTestCount;
#define MILLISEC_NUM_10 10
#define MILLISEC_NUM_1000 1000
#define TICK_NUM_10 10
#define TICK_NUM_20 20
#define TICK_NUM_30 30
#define TICK_NUM_40 40
#define TICK_NUM_1000 1000
#define TESTCOUNT_NUM_1 1
#define TESTCOUNT_NUM_2 2
#define TESTCOUNT_NUM_3 3
#define TESTCOUNT_NUM_4 4
#define TESTCOUNT_NUM_5 5
#define TEST_TASK_STACK_SIZE      0x600
#define TEST_TASK_PRIORITY_LOW          osPriorityBelowNormal       // tskIDLE_PRIORITY + 10
#define TEST_TASK_PRIORITY_NORMAL       osPriorityNormal            // tskIDLE_PRIORITY + 11
#define TEST_TASK_PRIORITY_HIGH         osPriorityAboveNormal       // tskIDLE_PRIORITY + 12
#define PRIORITY_TRANSFORM_NUM 39


/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisTaskFuncTestSuite
 */
LITE_TEST_SUIT(Kal, KalApi, KalFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL KalFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL KalFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

static void KalTimerProc001Func001(void *argument)
{
    (void)argument;
    g_kalTestCount++;
    return;
}

static void KalThreadGetInfo001Func001(void const *argument)
{
    (void)argument;
    int ret;
    LosTaskCB *pid;
    ThreadInfo info;
    pid = (LosTaskCB*)osThreadGetId();
    ret = KalThreadGetInfo(pid->taskID, &info);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING("testThreadGetInfo001", info.name);
    TEST_ASSERT_EQUAL_INT(TEST_TASK_STACK_SIZE, info.stackSize);
    // Priorities defined in KAL are different in CMSIS,need to transform
    TEST_ASSERT_EQUAL_INT(TEST_TASK_PRIORITY_HIGH, PRIORITY_TRANSFORM_NUM - info.priority);
    osThreadExit();
}

static void KalDelayUs001Func001(void const *argument)
{
    (void)argument;
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_kalTestCount);
    g_kalTestCount++;
    osThreadExit();
}

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal api for delay us 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalDelayUs001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "test";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = TEST_TASK_PRIORITY_NORMAL;
    g_kalTestCount = 0;
    g_kalTestCount++;
    id = osThreadNew((osThreadFunc_t)KalDelayUs001Func001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    KalDelayUs(MILLISEC_NUM_10);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_kalTestCount);

};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal get thread Info
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalThreadGetInfo001, LEVEL1)
{
    osThreadId_t id;
    osThreadAttr_t attr;
    attr.name = "testThreadGetInfo001";
    attr.attr_bits = 1U;
    attr.cb_mem = NULL;
    attr.cb_size = 2U;
    attr.stack_mem = NULL;
    attr.stack_size = TEST_TASK_STACK_SIZE;
    attr.priority = TEST_TASK_PRIORITY_HIGH;
    printf("KalThreadGetInfo ThreadAttr Name = %s \r\n", attr.name);
    printf("KalThreadGetInfo ThreadAttr StackSize = %x \r\n", attr.stack_size);
    printf("KalThreadGetInfo ThreadAttr Priority = %d \r\n", attr.priority);
    id = osThreadNew((osThreadFunc_t)KalThreadGetInfo001Func001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal get thread Info when info = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalThreadGetInfo002, LEVEL1)
{
    int ret;
    LosTaskCB *pid;
    pid = (LosTaskCB*)osThreadGetId();
    ret = KalThreadGetInfo(pid->taskID, NULL);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer create 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerCreate001, LEVEL1)
{
    KalTimerId id;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer create input kalTimerproc exception 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerCreate002, LEVEL1)
{
    g_kalTestCount = 0; 
    KalTimerId id;    
    id = KalTimerCreate(NULL, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NULL(id);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer create repeat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerCreate003, LEVEL1)
{
    g_kalTestCount = 0; 
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_PERIODIC, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    osDelay(TICK_NUM_30);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_kalTestCount);
    osDelay(TICK_NUM_20);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_2, g_kalTestCount);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer start
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerStart001, LEVEL1)
{
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer start input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerStart002, LEVEL1)
{
    KalErrCode kRet;
    kRet = KalTimerStart(NULL);
    TEST_ASSERT_EQUAL_INT(KAL_ERR_PARA, kRet);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is running
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerIsRunning001, LEVEL1)
{
    KalTimerId id;
    UINT32 uwRet;
    KalErrCode kRet;    
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);    
    kRet = KalTimerStart(id);    
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    uwRet = KalTimerIsRunning(id);
    TEST_ASSERT_EQUAL_INT(TRUE, uwRet);
    (void)KalTimerDelete(id);    
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is running input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerIsRunning002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = KalTimerIsRunning(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is running deal
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerIsRunning003, LEVEL1)
{
    g_kalTestCount = 0; 
    KalTimerId id;
    KalErrCode kRet;
    UINT32 uwRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    uwRet = KalTimerIsRunning(id);
    TEST_ASSERT_EQUAL_INT(TRUE, uwRet);
    osDelay(TICK_NUM_10);
    TEST_ASSERT_EQUAL_INT(0, g_kalTestCount);
    osDelay(TICK_NUM_10);
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_kalTestCount);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is stop
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerStop001, LEVEL1)
{
    g_kalTestCount = 0; 
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    kRet = KalTimerStop(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is stop input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerStop002, LEVEL1)
{
    KalErrCode kRet;
    KalTimerId id = NULL;
    kRet = KalTimerStop(id);
    TEST_ASSERT_EQUAL_INT(KAL_ERR_PARA, kRet);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is stop deal
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerStop003, LEVEL1)
{
    g_kalTestCount = 0;
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    osDelay(TICK_NUM_10);
    TEST_ASSERT_EQUAL_INT(0, g_kalTestCount);
    kRet = KalTimerStop(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    osDelay(TICK_NUM_20);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    TEST_ASSERT_EQUAL_INT(0, g_kalTestCount);
    osDelay(TICK_NUM_20); 
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_kalTestCount);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer change
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerChange001, LEVEL1)
{
    g_kalTestCount = 0;
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerChange(id, TICK_NUM_40);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer change start exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerChange002, LEVEL1)
{
    g_kalTestCount = 0;
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    kRet = KalTimerChange(id, TICK_NUM_40);
    TEST_ASSERT_EQUAL_INT(KAL_ERR_TIMER_STATE, kRet);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is stop input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerChange003, LEVEL1)
{
    KalErrCode kRet;
    KalTimerId id = NULL;
    kRet = KalTimerChange(id, TICK_NUM_20);
    TEST_ASSERT_EQUAL_INT(KAL_ERR_PARA, kRet);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is stop deal
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerChange004, LEVEL1)
{
    g_kalTestCount = 0;
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerChange(id, TICK_NUM_40);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    kRet = KalTimerStart(id);    
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    osDelay(TICK_NUM_30);    
    TEST_ASSERT_EQUAL_INT(0, g_kalTestCount);
    osDelay(TICK_NUM_20);    
    TEST_ASSERT_EQUAL_INT(TESTCOUNT_NUM_1, g_kalTestCount);
    (void)KalTimerDelete(id);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerDelete001, LEVEL1)
{
    g_kalTestCount = 0; 
    KalTimerId id;
    KalErrCode kRet;
    id = KalTimerCreate(KalTimerProc001Func001, KAL_TIMER_ONCE, NULL, TICK_NUM_20);
    TEST_ASSERT_NOT_NULL(id);
    kRet = KalTimerStart(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    kRet = KalTimerDelete(id);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal timer is stop input exception
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTimerDelete002, LEVEL1)
{
    KalErrCode kRet;
    KalTimerId id = NULL;    
    kRet = KalTimerDelete(id);
    TEST_ASSERT_EQUAL_INT(KAL_ERR_PARA, kRet);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal get mem info
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalGetMemInfo001, LEVEL1)
{
    g_kalTestCount = 0; 
    KalErrCode kRet;
    MemInfo *pmemInfo;
    pmemInfo = malloc(sizeof(MemInfo));
    if (pmemInfo == NULL) {
        TEST_ASSERT_EQUAL_INT(0, 1);
    }
    kRet = KalGetMemInfo(pmemInfo);
    TEST_ASSERT_EQUAL_INT(KAL_OK, kRet);
    printf("KalGetMemInfo: pmemInfo total [%d] \r\n", pmemInfo->total);	
    printf("KalGetMemInfo: pmemInfo used[%d] \r\n", pmemInfo->used);
    printf("KalGetMemInfo: pmemInfo free[%d] \r\n", pmemInfo->free);
    printf("KalGetMemInfo: pmemInfo freeNodeNum[%d] \r\n", pmemInfo->freeNodeNum);
    printf("KalGetMemInfo: pmemInfo usedNodeNum[%d] \r\n", pmemInfo->usedNodeNum);
    printf("KalGetMemInfo: pmemInfo maxFreeNodeSize[%d] \r\n", pmemInfo->maxFreeNodeSize);
    printf("KalGetMemInfo: pmemInfo mallocFailCount[%d] \r\n", pmemInfo->mallocFailCount);
    printf("KalGetMemInfo: pmemInfo peekSize[%d] \r\n", pmemInfo->peekSize);
    printf("KalGetMemInfo: pmemInfo totalLmp[%d] \r\n", pmemInfo->totalLmp);
    printf("KalGetMemInfo: pmemInfo usedLmp[%d] \r\n", pmemInfo->usedLmp);
    printf("KalGetMemInfo: pmemInfo freeLmp[%d] \r\n", pmemInfo->freeLmp);
    free(pmemInfo);
    pmemInfo = NULL;

};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal ms to tick
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalMsToTick001, LEVEL1)
{
    UINT32 tick = 0;
    UINT32 ms = 1;
    while (tick < TICK_NUM_10) {
        ms = ms * TICK_NUM_10;
        tick = KalMsToTick(ms);
        printf("KalMsToTick: ms[%d] to tick[%d] \r\n", ms, tick);
    }
    TEST_ASSERT_GREATER_OR_EQUAL(TICK_NUM_10, tick);
    TEST_ASSERT_LESS_THAN_INT(TICK_NUM_1000, tick);
};

/**
 * @tc.number    : SUB_KERNEL_Kal_OPERATION_100
 * @tc.name      : kal tick to ms
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KalFuncTestSuite, testKalTickToMs001, LEVEL1)
{
    UINT32 tick = 1;
    UINT32 ms = 0;
    while (ms < MILLISEC_NUM_10) {
        tick = tick * MILLISEC_NUM_10;
        ms = KalTickToMs(tick);
        printf("KalTickToMs: tick[%d] to ms[%d] \r\n", tick, ms);
    }
    TEST_ASSERT_GREATER_OR_EQUAL(MILLISEC_NUM_10, ms);
    TEST_ASSERT_LESS_THAN_INT(MILLISEC_NUM_1000, ms);
};

RUN_TEST_SUITE(KalFuncTestSuite);
