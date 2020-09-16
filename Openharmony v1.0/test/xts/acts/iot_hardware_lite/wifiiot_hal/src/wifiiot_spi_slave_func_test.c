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
#ifdef CONFIG_SPI_SUPPORT
#include "wifiiot_spi.h"
#endif

#define TEST_SPI_SIZE 20
#define TEST_FREQ_SIZE 2000000
#define TEST_SPI_TIMEOUT 1000

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotSpiSlaveFuncTestSuite);

#ifdef CONFIG_SPI_SUPPORT
/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSpiSlaveFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSpiSlaveFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi037, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi038, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi039, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi040, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi041, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi042, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi043, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi044, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi045, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi046, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi047, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi048, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi049, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi050, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi051, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi052, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi053, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi054, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 1;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi055, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi056, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi057, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi058, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi059, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi060, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi061, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi062, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi063, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_0;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_0;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_LITTLE;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_0, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi064, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi065, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi066, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi067, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi068, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi069, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_TI;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi070, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi071, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2200
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiSlaveFuncTestSuite, testWifiIotSpi072, LEVEL1)
{
    unsigned int ret;   
    char send_buf[] = "SpiDemoTest";
    char recv_buf[TEST_SPI_SIZE] = {0};
    WifiIotSpiCfgBasicInfo spi_para;
    spi_para.cpol = WIFI_IOT_SPI_CFG_CLOCK_CPOL_1;
    spi_para.cpha = WIFI_IOT_SPI_CFG_CLOCK_CPHA_1;
    spi_para.framMode = WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE;
    spi_para.dataWidth = WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT;
    spi_para.endian = WIFI_IOT_SPI_CFG_ENDIAN_BIG;
    spi_para.pad = 0;
    spi_para.freq = TEST_FREQ_SIZE;

    WifiIotSpiCfgInitParam init_param;
    init_param.isSlave = 0;
    init_param.pad = 0;

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiInit(WIFI_IOT_SPI_ID_1, init_param, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetDmaMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSlaveRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf), TEST_SPI_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiDeinit(WIFI_IOT_SPI_ID_1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }
};
#endif

RUN_TEST_SUITE(WifiIotSpiSlaveFuncTestSuite);
