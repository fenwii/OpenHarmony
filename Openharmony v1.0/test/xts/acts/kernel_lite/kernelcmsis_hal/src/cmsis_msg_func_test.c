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

osMessageQueueId_t g_cmsisMessageQId;
#define MSGQUEUE_COUNT    16
#define MSGQUEUE_SPACE_COUNT    13
#define MSGQUEUE_PUT_COUNT    3
#define MSG_SIZE    4
#define MSGINFO_LEN    4
#define TIMEOUT_COUNT    1000
#define BUF_LEN    32
#define MSGQUEUE_COUNT_INDEX_0    0
#define MSGQUEUE_COUNT_INDEX_1    1
#define MSGQUEUE_COUNT_INDEX_2    2
static char *g_cmsisMessageInfo[] = {"msg1", "msg2", "msg3", "msg4", "msg5", "msg6", "msg7", "msg8"};

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is CmsisMsgFuncTestSuite
 */
LITE_TEST_SUIT(Cmsis, Cmsismsg, CmsisMsgFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL CmsisMsgFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL CmsisMsgFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

static void CmsisMessageQueueGetFunc001(void const *argument)
{
    (void)argument;
    osStatus_t uwRet;
    UINT8 msg_prio = 0;
    CHAR   uctemp[MSGINFO_LEN] = "";
    UINT32 uwCmp;
    uwRet = osMessageQueueGet(g_cmsisMessageQId, uctemp, &msg_prio, TIMEOUT_COUNT);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    uwCmp = memcmp(uctemp, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_0], MSGINFO_LEN);
    TEST_ASSERT_EQUAL_INT(0, uwCmp);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    osThreadExit();
}

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for creat
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueNew001, LEVEL1)
{
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);
    (void)osMessageQueueDelete(g_cmsisMessageQId);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for creat when msg_count = 0
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueNew002, LEVEL1)
{
    g_cmsisMessageQId = osMessageQueueNew(0, MSG_SIZE, NULL);
    TEST_ASSERT_NULL(g_cmsisMessageQId);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for creat when msg_size = 0
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueNew003, LEVEL1)
{
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, 0, NULL);
    TEST_ASSERT_NULL(g_cmsisMessageQId);
    osDelay(DELAY_TICKS_5);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueDelete001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);
    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue delete operation with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueDelete002, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osMessageQueueDelete(NULL);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for put
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueuePut001, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_0], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue put operation with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueuePut002, LEVEL1)
{
    osStatus_t uwRet;
    uwRet = osMessageQueuePut(NULL, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_0], 0, 0);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for put when msg_ptr = 0
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueuePut003, LEVEL1)
{
    osStatus_t uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, NULL, 0, 0);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for get
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGet001, LEVEL1)
{
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
    osKernelLock();
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    id = osThreadNew((osThreadFunc_t)CmsisMessageQueueGetFunc001, NULL, &attr);
    TEST_ASSERT_NOT_NULL(id);
    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_0], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
    osKernelUnlock();
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue get operation with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGet002, LEVEL1)
{
    osStatus_t uwRet;
    UINT8 msg_prio = 0;
    CHAR   uctemp[MSGINFO_LEN] = "";
    uwRet = osMessageQueueGet(NULL, uctemp, &msg_prio, TIMEOUT_COUNT);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for get when msg_ptr = 0
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGet003, LEVEL1)
{
    osStatus_t uwRet; 
    UINT8 msg_prio = 0;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    uwRet = osMessageQueueGet(g_cmsisMessageQId, NULL, &msg_prio, TIMEOUT_COUNT);
    TEST_ASSERT_EQUAL_INT(osErrorParameter, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for get msg size
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetMsgSize001, LEVEL1)
{
    UINT32 uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    uwRet = osMessageQueueGetMsgSize(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(MSG_SIZE, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue get msg size with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetMsgSize002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osMessageQueueGetMsgSize(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for get capacity
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetCapacity001, LEVEL1)
{
    UINT32 uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);
    uwRet = osMessageQueueGetCapacity(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(MSGQUEUE_COUNT, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue get capacity with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetCapacity002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osMessageQueueGetCapacity(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for get count
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetCount001, LEVEL1)
{
    UINT32 uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_0], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_1], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_2], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueueGetCount(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(MSGQUEUE_PUT_COUNT, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue get count with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetCount002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osMessageQueueGetCount(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue operation for get space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetSpace001, LEVEL1)
{
    UINT32 uwRet;
    g_cmsisMessageQId = osMessageQueueNew(MSGQUEUE_COUNT, MSG_SIZE, NULL);
    TEST_ASSERT_NOT_NULL(g_cmsisMessageQId);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_0], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_1], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueuePut(g_cmsisMessageQId, g_cmsisMessageInfo[MSGQUEUE_COUNT_INDEX_2], 0, 0);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);

    uwRet = osMessageQueueGetSpace(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(MSGQUEUE_SPACE_COUNT, uwRet);

    uwRet = osMessageQueueDelete(g_cmsisMessageQId);
    TEST_ASSERT_EQUAL_INT(osOK, uwRet);
};

/**
 * @tc.number    : SUB_KERNEL_CMSIS_MSG_OPERATION_100
 * @tc.name      : message queue get space with mq_id = NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(CmsisMsgFuncTestSuite, testOsMessageQueueGetSpace002, LEVEL1)
{
    UINT32 uwRet;
    uwRet = osMessageQueueGetSpace(NULL);
    TEST_ASSERT_EQUAL_INT(0, uwRet);
};

RUN_TEST_SUITE(CmsisMsgFuncTestSuite);
