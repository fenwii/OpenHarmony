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

#include "hos_types.h"
#include <hos_init.h>
#include <los_base.h>
#include <securec.h>
#include "hctest.h"
#include "hi_task.h"
#include "hi_time.h"

#include "samgr_lite.h"
#include "wifiiot_errno.h"
#include "wifiiot_sdio.h"

#define TEST_SDIO_LENGTH 8
#define TEST_REG_NUM 10
#define TEST_BYTE_NUM 100
#define MAX_ADMA_INDEX 130
#define MAX_MSG_VALUE 31
#define ADMA_TABLE_PARAM 666

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotSdioFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSdioFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSdioFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

int ReadStartCallbackFunc(unsigned int len, unsigned char *admaTable)
{
    (void)admaTable;
    printf("ReadStartCallbackFunc\n");
    return sizeof(len);
}

int ReadOverCallbackFunc(void)
{
    printf("ReadOverCallbackFunc\n");
    return 0;
}

void ReadErrCallbackFunc(void)
{
    printf("ReadErrCallbackFunc\n");
}

int WriteStartCallbackFunc(unsigned int len, unsigned char *admaTable)
{
    (void)admaTable;
    printf("WriteStartCallbackFunc\n");
    return sizeof(len);
}

int WriteOverCallbackFunc(void)
{
    printf("WriteOverCallbackFunc\n");
    return 0;
}

void ProcessMsgCallbackFunc(unsigned int msg)
{
    (void)msg;
    printf("ProcessMsgCallbackFunc\n");
}

void SoftRstCallbackFunc(void)
{
    printf("SoftRstCallbackFunc\n");
}

void NotifyHostMessageEventFunc(void)
{
    printf("NotifyHostMessageEventFunc\n");
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_1800
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio001, LEVEL1)
{
    unsigned int ret;

    WifiIotSdioIntcallback callback;
    callback.RdstartCallback = ReadStartCallbackFunc;
    callback.RdoverCallback = ReadOverCallbackFunc;
    callback.RderrCallback = ReadErrCallbackFunc;
    callback.WrstartCallback = WriteStartCallbackFunc;
    callback.WroverCallback = WriteOverCallbackFunc;
    callback.ProcessmsgCallback = ProcessMsgCallbackFunc;
    callback.SoftRstCallback = SoftRstCallbackFunc;

    ret = SdioInit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = SdioRegisterCallback(&callback);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    SdioRegisterNotifyMessageCallback(NotifyHostMessageEventFunc);
    SdioSoftReset();
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1900
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio002, LEVEL1)
{
    unsigned int ret;
    WifiIotSdioAdmatable admaTable;
    admaTable.param = ADMA_TABLE_PARAM;
    admaTable.len = TEST_SDIO_LENGTH;
    admaTable.address = 0x11;

    ret = SdioReinit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = SdioIsPendingMsg(0);
    if (!(ret == 0 || ret == 1))
    {
        TEST_FAIL();
    }

    ret = SdioIsSendingMsg(0);
    if (!(ret == 0 || ret == 1))
    {
        TEST_FAIL();
    }

    ret = SdioSetAdmatable((unsigned char*)&admaTable, 0, (const unsigned int *)0x11, TEST_SDIO_LENGTH);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    ret = SdioSetPadAdmatab(TEST_SDIO_LENGTH, (unsigned char*)&admaTable, 0);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    SdioSetPowerdownWhenDeepSleep(1);   
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1900
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio003, LEVEL1)
{
    unsigned int ret;
    WifiIotSdioAdmatable admaTable;
    admaTable.param = ADMA_TABLE_PARAM;
    admaTable.len = TEST_SDIO_LENGTH;
    admaTable.address = 0x11;

    ret = SdioReinit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = SdioIsPendingMsg(MAX_MSG_VALUE);
    if (!(ret == 0 || ret == 1))
    {
        TEST_FAIL();
    }

    ret = SdioIsSendingMsg(MAX_MSG_VALUE);
    if (!(ret == 0 || ret == 1))
    {
        TEST_FAIL();
    }

    ret = SdioSetAdmatable((unsigned char*)&admaTable, MAX_ADMA_INDEX, (const unsigned int *)0x11, TEST_SDIO_LENGTH);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    ret = SdioSetPadAdmatab(TEST_SDIO_LENGTH, (unsigned char*)&admaTable, MAX_ADMA_INDEX);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    SdioSetPowerdownWhenDeepSleep(0);    
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2000
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio004, LEVEL1)
{
    unsigned int ret;
    WifiIotSdioAdmatable admaTable;
    admaTable.param = ADMA_TABLE_PARAM;
    admaTable.len = TEST_SDIO_LENGTH;
    admaTable.address = 0x11;

    WifiIotSdioExtendFunc extendInfo;
    extendInfo.intStat = 0;
    extendInfo.msgStat = 1;
    extendInfo.xferCount = TEST_BYTE_NUM;
    extendInfo.creditInfo = 1;
    extendInfo.creditIsvalid = 1;
    extendInfo.commReg[WIFI_IOT_SDIO_EXTENDREG_COUNT-1] = (uintptr_t)"CommonRegister";
    extendInfo.commregIsvalid = 1;
    extendInfo.validCommregCnt = TEST_REG_NUM;

    ret = SdioReinit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    WifiIotSdioExtendFunc *getExtendInfo;
    getExtendInfo = SdioGetExtendInfo();
    if (0 == getExtendInfo)
    {
        TEST_FAIL();
    }

    ret = SdioWriteExtinfo(&extendInfo);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    SdioSendData(TEST_BYTE_NUM);

    ret = SdioSendMsgAck(0);
    TEST_ASSERT_EQUAL_INT(1, ret);

    ret = SdioCompleteSend((unsigned char*)&admaTable, 0);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2000
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio005, LEVEL1)
{
    unsigned int ret;
    WifiIotSdioAdmatable admaTable;
    admaTable.param = ADMA_TABLE_PARAM;
    admaTable.len = TEST_SDIO_LENGTH;
    admaTable.address = 0x11;

    WifiIotSdioExtendFunc extendInfo;
    extendInfo.intStat = 0;
    extendInfo.msgStat = 1;
    extendInfo.xferCount = TEST_BYTE_NUM;
    extendInfo.creditInfo = 1;
    extendInfo.creditIsvalid = 1;
    extendInfo.commReg[WIFI_IOT_SDIO_EXTENDREG_COUNT-1] = (uintptr_t)"CommonRegister";
    extendInfo.commregIsvalid = 1;
    extendInfo.validCommregCnt = TEST_REG_NUM;

    ret = SdioReinit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    WifiIotSdioExtendFunc *getExtendInfo;
    getExtendInfo = SdioGetExtendInfo();
    if (0 == getExtendInfo)
    {
        TEST_FAIL();
    }

    ret = SdioWriteExtinfo(&extendInfo);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }

    SdioSendData(TEST_BYTE_NUM);

    ret = SdioSendMsgAck(MAX_MSG_VALUE);
    TEST_ASSERT_EQUAL_INT(1, ret);

    ret = SdioCompleteSend((unsigned char*)&admaTable, MAX_ADMA_INDEX);
    if (!(ret == 0 || ret == WIFI_IOT_ERR_SDIO_INVALID_PARAMETER))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2100
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio006, LEVEL1)
{
    unsigned int ret;

    ret = SdioReinit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = SdioSendSyncMsg(0);
    TEST_ASSERT_EQUAL_INT(1, ret);

    ret = SdioProcessMsg(0, MAX_MSG_VALUE);
    TEST_ASSERT_EQUAL_INT(1, ret);

    ret = SdioSchedMsg();
    if (!(ret == 0 || ret == 1))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2100
 * @tc.name      : Sdio operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSdioFuncTestSuite, testWifiIotSdio007, LEVEL1)
{
    unsigned int ret;

    ret = SdioReinit();
    if (ret == 0xffffffff){
        printf("SDIO is absent\n");
        TEST_IGNORE();
        return;
    }
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = SdioSendSyncMsg(MAX_MSG_VALUE);
    TEST_ASSERT_EQUAL_INT(1, ret);

    ret = SdioProcessMsg(MAX_MSG_VALUE, 0);
    TEST_ASSERT_EQUAL_INT(1, ret);

    ret = SdioSchedMsg();
    if (!(ret == 0 || ret == 1))
    {
        TEST_FAIL();
    }
};

RUN_TEST_SUITE(WifiIotSdioFuncTestSuite);
