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
#ifdef CONFIG_I2C_SUPPORT
#include "wifiiot_i2c.h"
#include "wifiiot_i2c_ex.h"
#endif

#define SEND_RECV_LEN 3
#define AT24C02_1K 0xa0
#define INIT_BAUD_RATE 10000
#define SET_BAUD_RATE 19200

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotI2cFuncTestSuite);

#ifdef CONFIG_I2C_SUPPORT
/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotI2cFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotI2cFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

void IOT_ResetFunc(void)
{
    printf("Abnormal callback function\n");
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_900
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C001, LEVEL1)
{
    unsigned int ret;
    WifiIotI2cFunc callbackType = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_0, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    callbackType.resetFunc = IOT_ResetFunc;
    (void)I2cRegisterResetBusFunc(WIFI_IOT_I2C_IDX_0, callbackType);

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_900
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C02, LEVEL1)
{
    unsigned int ret;
    WifiIotI2cFunc callbackType = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_1, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    callbackType.resetFunc = IOT_ResetFunc;
    (void)I2cRegisterResetBusFunc(WIFI_IOT_I2C_IDX_1, callbackType);

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_700
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C003, LEVEL1)
{
    unsigned int ret;
    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = I2cInit(WIFI_IOT_I2C_IDX_0, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = I2cSetBaudrate(WIFI_IOT_I2C_IDX_0, SET_BAUD_RATE);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_700
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C004, LEVEL1)
{
    unsigned int ret;
    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = I2cInit(WIFI_IOT_I2C_IDX_1, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = I2cSetBaudrate(WIFI_IOT_I2C_IDX_1, SET_BAUD_RATE);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_700
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C005, LEVEL1)
{
    unsigned int ret;
    char senddata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_0, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    senddata[0] = 0x0;
    senddata[1] = 0x3;
    stdata.sendBuf = (uint8 *)senddata;
    stdata.sendLen = SEND_RECV_LEN;  
    ret= I2cWrite(WIFI_IOT_I2C_IDX_0, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_700
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C006, LEVEL1)
{
    unsigned int ret;
    char senddata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_1, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    senddata[0] = 0x0;
    senddata[1] = 0x3;
    stdata.sendBuf = (uint8 *)senddata;
    stdata.sendLen = SEND_RECV_LEN;  
    ret= I2cWrite(WIFI_IOT_I2C_IDX_1, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_800
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C007, LEVEL1)
{
    unsigned int ret;
    char recvdata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_0, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    stdata.receiveBuf = (uint8 *)recvdata;
    stdata.receiveLen = SEND_RECV_LEN;
    ret = I2cRead(WIFI_IOT_I2C_IDX_0, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_800
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C008, LEVEL1)
{
    unsigned int ret;
    char recvdata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_1, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    stdata.receiveBuf = (uint8 *)recvdata;
    stdata.receiveLen = SEND_RECV_LEN;
    ret = I2cRead(WIFI_IOT_I2C_IDX_1, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_800
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C009, LEVEL1)
{
    unsigned int ret;
    char senddata[SEND_RECV_LEN] = {0};
    char recvdata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_0, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    senddata[0] = 0x0;
    senddata[1] = 0x3;
    stdata.sendBuf = (uint8 *)senddata;
    stdata.sendLen = SEND_RECV_LEN;  
    stdata.receiveBuf = (uint8 *)recvdata;
    stdata.receiveLen = SEND_RECV_LEN;
    ret = I2cWriteread(WIFI_IOT_I2C_IDX_0, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_800
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C0010, LEVEL1)
{
    unsigned int ret;
    char senddata[SEND_RECV_LEN] = {0};
    char recvdata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_1, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    senddata[0] = 0x0;
    senddata[1] = 0x3;
    stdata.sendBuf = (uint8 *)senddata;
    stdata.sendLen = SEND_RECV_LEN;  
    stdata.receiveBuf = (uint8 *)recvdata;
    stdata.receiveLen = SEND_RECV_LEN;
    ret = I2cWriteread(WIFI_IOT_I2C_IDX_1, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_800
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C011, LEVEL1)
{
    unsigned int ret;
    char senddata[SEND_RECV_LEN] = {0};
    char recvdata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_0, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    senddata[0] = 0x0;
    senddata[1] = 0x3;
    stdata.sendBuf = (uint8 *)senddata;
    stdata.sendLen = SEND_RECV_LEN;  
    ret= I2cWrite(WIFI_IOT_I2C_IDX_0, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }
    stdata.receiveBuf = (uint8 *)recvdata;
    stdata.receiveLen = SEND_RECV_LEN;
    ret = I2cRead(WIFI_IOT_I2C_IDX_0, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    if (strcmp(stdata.receiveBuf, stdata.sendBuf) != 0) {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_800
 * @tc.name      : I2C operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotI2cFuncTestSuite, testWifiIotI2C012, LEVEL1)
{
    unsigned int ret;
    char senddata[SEND_RECV_LEN] = {0};
    char recvdata[SEND_RECV_LEN] = {0};
    WifiIotI2cData stdata = {0};

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = I2cInit(WIFI_IOT_I2C_IDX_1, INIT_BAUD_RATE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    senddata[0] = 0x0;
    senddata[1] = 0x3;
    stdata.sendBuf = (uint8 *)senddata;
    stdata.sendLen = SEND_RECV_LEN;  
    ret= I2cWrite(WIFI_IOT_I2C_IDX_1, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }
    stdata.receiveBuf = (uint8 *)recvdata;
    stdata.receiveLen = SEND_RECV_LEN;
    ret = I2cRead(WIFI_IOT_I2C_IDX_1, AT24C02_1K, &stdata);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2C_NOT_INIT) && (ret <= WIFI_IOT_ERR_I2C_WAIT_ACK_ERR))))
    {
        TEST_FAIL();
    }

    if (strcmp(stdata.receiveBuf, stdata.sendBuf) != 0) {
        TEST_FAIL();
    }

    ret = I2cDeinit(WIFI_IOT_I2C_IDX_1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};
#endif

RUN_TEST_SUITE(WifiIotI2cFuncTestSuite);
