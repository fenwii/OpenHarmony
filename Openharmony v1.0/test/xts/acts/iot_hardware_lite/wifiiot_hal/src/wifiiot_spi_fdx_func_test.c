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
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotSpiFdxFuncTestSuite);

#ifdef CONFIG_SPI_SUPPORT
/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSpiFdxFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotSpiFdxFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

void SpiIsrFuncPrepareProc(void)
{
    printf("SpiIsrFuncPrepareProc \n");
}

void SpiIsrFuncRestoreProc(void)
{
    printf("SpiIsrFuncRestoreProc \n");
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi073, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi074, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi075, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi076, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi077, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi078, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi079, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi080, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi081, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi082, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi083, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi084, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi085, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi086, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi087, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi088, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi089, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi090, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi091, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi092, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi093, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi094, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi095, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi096, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi097, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi098, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi099, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_0, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_0, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_0, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi100, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi101, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi102, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi103, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi104, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi105, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi106, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi107, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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
 * @tc.number    : SUB_UTILS_IOT_API_2400
 * @tc.name      : Spi operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotSpiFdxFuncTestSuite, testWifiIotSpi108, LEVEL1)
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

    ret =  SpiRegisterUsrFunc(WIFI_IOT_SPI_ID_1, SpiIsrFuncPrepareProc, SpiIsrFuncRestoreProc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiSetLoopBackMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret =  SpiSetIrqMode(WIFI_IOT_SPI_ID_1, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_SPI_NOT_INIT) && (ret <= WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA))))
    {
        TEST_FAIL();
    }

    ret = SpiHostWriteread(WIFI_IOT_SPI_ID_1, send_buf, recv_buf, sizeof(recv_buf));
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

RUN_TEST_SUITE(WifiIotSpiFdxFuncTestSuite);
