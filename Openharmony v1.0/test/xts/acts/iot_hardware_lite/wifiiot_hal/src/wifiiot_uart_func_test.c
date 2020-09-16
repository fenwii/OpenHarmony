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
#include "wifiiot_uart.h"
#include "wifiiot_uart_ex.h"

#define TEST_UART_SIZE 8
#define INIT_BAUD_RATE 115200
#define TEST_BUF_SIZE 10000

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotUartFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotUartFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotUartFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart007, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_NONE;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_2, &getUartAttr, &getExtraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart008, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_2, &getUartAttr, &getExtraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart009, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_EVEN;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_2, &getUartAttr, &getExtraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart010, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_2;
    uartAttr.parity = WIFI_IOT_UART_PARITY_NONE;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_USE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    if (ret == 0)
    {
        TEST_ASSERT_EQUAL_INT(0, ret); 
    }else if ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))
    {
        TEST_ASSERT_EQUAL_INT(1, 1); 
        return;
    }else
    {
        TEST_FAIL();
        return;
    }

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_2, &getUartAttr, &getExtraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart011, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_2;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_USE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    if (ret == 0)
    {
        TEST_ASSERT_EQUAL_INT(0, ret); 
    }else if ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))
    {
        TEST_ASSERT_EQUAL_INT(1, 1); 
        return;
    }else
    {
        TEST_FAIL();
        return;
    }

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_2, &getUartAttr, &getExtraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart012, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_2;
    uartAttr.parity = WIFI_IOT_UART_PARITY_EVEN;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_USE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_USE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    if (ret == 0)
    {
        TEST_ASSERT_EQUAL_INT(0, ret); 
    }else if ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))
    {
        TEST_ASSERT_EQUAL_INT(1, 1); 
        return;
    }else
    {
        TEST_FAIL();
        return;
    }

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_2, &getUartAttr, &getExtraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart013, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_NONE;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    WifiIotUartAttribute getUartAttr = {0};
    WifiIotUartExtraAttr getExtraAttr = {0};
    ret = UartGetAttribute(WIFI_IOT_UART_IDX_MAX, &getUartAttr, &getExtraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart015, LEVEL1)
{
    unsigned int ret;
    unsigned char busy = 0;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_NONE;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartIsBusy(WIFI_IOT_UART_IDX_2, &busy);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart016, LEVEL1)
{
    unsigned int ret;
    unsigned char busy = 0;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_NONE;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartIsBusy(WIFI_IOT_UART_IDX_MAX, &busy);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart018, LEVEL1)
{
    unsigned int ret;
    unsigned char empty = 0;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartIsBufEmpty(WIFI_IOT_UART_IDX_2, &empty);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart019, LEVEL1)
{
    unsigned int ret;
    unsigned char empty = 0;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartIsBufEmpty(WIFI_IOT_UART_IDX_MAX, &empty);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart021, LEVEL1)
{
    unsigned int ret;
    int len;
    unsigned char uartWriteBuff[] = "hello uart!";
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_EVEN;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    len = UartWrite(WIFI_IOT_UART_IDX_2, uartWriteBuff, sizeof(uartWriteBuff));
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, len);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart022, LEVEL1)
{
    unsigned int ret;
    int len;
    unsigned char uartWriteBuff[] = "hello uart!";
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_EVEN;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    len = UartWrite(WIFI_IOT_UART_IDX_MAX, uartWriteBuff, sizeof(uartWriteBuff));
    TEST_ASSERT_EQUAL_INT(-1, len);
    
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart024, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_2, WIFI_IOT_FLOW_CTRL_RTS_CTS); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_2, WIFI_IOT_FLOW_CTRL_RTS_ONLY); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_2, WIFI_IOT_FLOW_CTRL_CTS_ONLY); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_2, WIFI_IOT_FLOW_CTRL_NONE); 
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1000
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart025, LEVEL1)
{
    unsigned int ret;
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_MAX, WIFI_IOT_FLOW_CTRL_RTS_CTS); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
    
    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_MAX, WIFI_IOT_FLOW_CTRL_RTS_ONLY); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
    
    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_MAX, WIFI_IOT_FLOW_CTRL_CTS_ONLY); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
    
    ret = UartSetFlowCtrl(WIFI_IOT_UART_IDX_MAX, WIFI_IOT_FLOW_CTRL_NONE); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart027, LEVEL1)
{
    unsigned int ret;
    int len;
    unsigned char uartWriteBuff[] = "hello uart!";
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_EVEN;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    len = UartWriteImmediately(WIFI_IOT_UART_IDX_2, uartWriteBuff, sizeof(uartWriteBuff));
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, len);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart028, LEVEL1)
{
    unsigned int ret;
    int len;
    unsigned char uartWriteBuff[] = "hello uart!";
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_EVEN;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    len = UartWriteImmediately(WIFI_IOT_UART_IDX_MAX, uartWriteBuff, sizeof(uartWriteBuff));
    TEST_ASSERT_EQUAL_INT(-1, len);
    
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart030, LEVEL1)
{
    unsigned int ret;
    int len;
    unsigned char uartReadBuff[TEST_UART_SIZE] = {0};
    unsigned char uartWriteBuff[] = "hello uart!";
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UartInit(WIFI_IOT_UART_IDX_2, &uartAttr, &extraAttr);
    TEST_ASSERT_EQUAL_INT(0, ret);

    UartWrite(WIFI_IOT_UART_IDX_2, uartWriteBuff, sizeof(uartWriteBuff));
    len = UartRead(WIFI_IOT_UART_IDX_2, uartReadBuff, sizeof(uartReadBuff));
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, len);

    ret = UartDeinit(WIFI_IOT_UART_IDX_2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1100
 * @tc.name      : Uart operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotUartFuncTestSuite, testWifiIotUart031, LEVEL1)
{
    unsigned int ret;
    int len;
    unsigned char uartReadBuff[TEST_UART_SIZE] = {0};
    WifiIotUartAttribute uartAttr;
    uartAttr.baudRate = INIT_BAUD_RATE, 
    uartAttr.dataBits = WIFI_IOT_UART_DATA_BIT_8;     
    uartAttr.stopBits = WIFI_IOT_UART_STOP_BIT_1;
    uartAttr.parity = WIFI_IOT_UART_PARITY_ODD;
    uartAttr.pad ='M';
    
    WifiIotUartExtraAttr extraAttr;
    (void)memset_s(&extraAttr, sizeof(WifiIotUartExtraAttr), 0, sizeof(WifiIotUartExtraAttr));
    extraAttr.txFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.rxFifoLine = WIFI_IOT_FIFO_LINE_ONE_EIGHT;
    extraAttr.flowFifoLine = WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS;
    extraAttr.txBlock = WIFI_IOT_UART_BLOCK_STATE_BLOCK;
    extraAttr.rxBlock = WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK;
    extraAttr.txBufSize = TEST_BUF_SIZE;
    extraAttr.rxBufSize = TEST_BUF_SIZE;
    extraAttr.txUseDma = WIFI_IOT_UART_NONE_DMA;
    extraAttr.rxUseDma = WIFI_IOT_UART_NONE_DMA;

    ret = UartDeinit(WIFI_IOT_UART_IDX_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    ret = UartInit(WIFI_IOT_UART_IDX_MAX, &uartAttr, &extraAttr);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_UART_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_UART_NOT_BLOCK_MODE))))
    {
        TEST_FAIL();
    }

    len = UartRead(WIFI_IOT_UART_IDX_MAX, uartReadBuff, sizeof(uartReadBuff));
    TEST_ASSERT_EQUAL_INT(-1, len);
};

RUN_TEST_SUITE(WifiIotUartFuncTestSuite);
