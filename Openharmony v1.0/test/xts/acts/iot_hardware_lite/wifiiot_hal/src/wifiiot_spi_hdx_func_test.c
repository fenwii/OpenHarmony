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

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotSpiHdxFuncTestSuite);

#ifdef CONFIG_SPI_SUPPORT
/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSpiHdxFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSpiHdxFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi001, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi002, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi003, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi004, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi005, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi006, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi007, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi008, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi009, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi010, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi011, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi012, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi013, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi014, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi015, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi016, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi017, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi018, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi019, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi020, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi021, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi022, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi023, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi024, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi025, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi026, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi027, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_0, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_0, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_0, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi028, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi029, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi030, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi031, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi032, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi033, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi034, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi035, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2300
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiHdxFuncTestSuite, testWifiIotSpi036, LEVEL1)
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

    ret = SpiSetBasicInfo(WIFI_IOT_SPI_ID_1, &spi_para);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWrite(WIFI_IOT_SPI_ID_1, send_buf, sizeof(send_buf));
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostRead(WIFI_IOT_SPI_ID_1, recv_buf, sizeof(recv_buf));
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

RUN_TEST_SUITE(WifiIotSpiHdxFuncTestSuite);
