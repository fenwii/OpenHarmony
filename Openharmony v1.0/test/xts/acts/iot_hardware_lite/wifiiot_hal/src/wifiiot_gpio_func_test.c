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
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"

#define TEST_GPIO_SIZE 8

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotGpioFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotGpioFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotGpioFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO001, LEVEL1)
{ 
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_0;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_OUT);
    TEST_ASSERT_EQUAL_INT(0, ret); 

    ret = GpioGetDir(gpioOutNum, &val); 
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO002, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_7;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_OUT);
    TEST_ASSERT_EQUAL_INT(0, ret); 

    ret = GpioGetDir(gpioOutNum, &val); 
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO003, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_14;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_OUT);
    TEST_ASSERT_EQUAL_INT(0, ret); 

    ret = GpioGetDir(gpioOutNum, &val); 
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO004, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_MAX;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_OUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioGetDir(gpioOutNum, &val); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO005, LEVEL1)
{ 
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_0;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_IN);
    TEST_ASSERT_EQUAL_INT(0, ret); 

    ret = GpioGetDir(gpioOutNum, &val); 
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO006, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_7;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_IN);
    TEST_ASSERT_EQUAL_INT(0, ret); 

    ret = GpioGetDir(gpioOutNum, &val); 
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO007, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_14;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_IN);
    TEST_ASSERT_EQUAL_INT(0, ret); 

    ret = GpioGetDir(gpioOutNum, &val); 
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO008, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_MAX;
    WifiIotGpioDir val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetDir(gpioOutNum, WIFI_IOT_GPIO_DIR_IN);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioGetDir(gpioOutNum, &val); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO009, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_0;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetOutputVal(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO010, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_7;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetOutputVal(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO011, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_14;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE0);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetOutputVal(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO012, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_MAX;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioGetOutputVal(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO0013, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_0;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetOutputVal(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO0014, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_7;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetOutputVal(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO015, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_14;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetOutputVal(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO016, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_GPIO_IDX_MAX;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetOutputVal(gpioOutNum, WIFI_IOT_GPIO_VALUE1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioGetOutputVal(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO017, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetInputVal(gpioInNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO018, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetInputVal(gpioInNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO019, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetInputVal(gpioInNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO020, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;
    WifiIotGpioValue val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioGetInputVal(gpioInNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

void IOT_IsrFunc(char *arg)
{
    int gpioInNum = (intptr_t)arg;
    unsigned int ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
    printf("GpioIsrFunc callback successfully\n");
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO021, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO022, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO023, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO024, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO025, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO026, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO027, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO028, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_LEVEL,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO029, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO030, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO031, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO032, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO033, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO034, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO035, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO036, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioRegisterIsrFunc(gpioInNum, WIFI_IOT_INT_TYPE_EDGE,
                         WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH, IOT_IsrFunc, (char *)(intptr_t)gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioUnregisterIsrFunc(gpioInNum);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO037, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO038, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO039, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 0);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO040, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMask(gpioInNum, 1);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = GpioSetIsrMask(gpioInNum, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO041, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO042, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO043, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO044, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO045, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO046, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO047, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_300
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO048, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_LEVEL, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO0849, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO050, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO051, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO052, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO053, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_0;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO054, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_7;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO055, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_14;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_400
 * @tc.name      : GPIO operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO056, LEVEL1)
{
    unsigned int ret;
    int gpioInNum = WIFI_IOT_GPIO_IDX_MAX;

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioSetIsrMode(gpioInNum,
                    WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO057, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_UP);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO058, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_DOWN);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO059, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO060, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_NONE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO061, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_UP);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO062, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_DOWN);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO063, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO064, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_NONE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO065, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_UP);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO066, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_DOWN);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO067, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO068, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_NONE);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetPull(gpioOutNum, &val);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO069, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_UP);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO070, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_DOWN);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO071, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO072, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoPull val = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetPull(gpioOutNum, WIFI_IOT_IO_PULL_NONE);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetPull(gpioOutNum, &val);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO073, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    char gpioOutNumFunc = WIFI_IOT_IO_FUNC_GPIO_0_GPIO;
    unsigned char gpioGetFunc[TEST_GPIO_SIZE+1] = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetFunc(gpioOutNum, gpioOutNumFunc);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetFunc(gpioOutNum, gpioGetFunc);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO074, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    char gpioOutNumFunc = WIFI_IOT_IO_FUNC_GPIO_7_SPI0_RXD;
    unsigned char gpioGetFunc[TEST_GPIO_SIZE+1] = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetFunc(gpioOutNum, gpioOutNumFunc);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetFunc(gpioOutNum, gpioGetFunc);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO075, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    char gpioOutNumFunc = WIFI_IOT_IO_FUNC_GPIO_14_I2C0_SCL;
    unsigned char gpioGetFunc[TEST_GPIO_SIZE+1] = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetFunc(gpioOutNum, gpioOutNumFunc);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoGetFunc(gpioOutNum, gpioGetFunc);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO076, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    char gpioOutNumFunc = WIFI_IOT_IO_FUNC_GPIO_9_I2S0_MCLK;
    unsigned char gpioGetFunc[TEST_GPIO_SIZE+1] = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IoSetFunc(gpioOutNum, gpioOutNumFunc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IoGetFunc(gpioOutNum, gpioGetFunc);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO077, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO078, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_7);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO079, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_0;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO080, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO081, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_7);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_500
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO082, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_7;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO083, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO084, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_7);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO085, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_GPIO_14;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO086, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO087, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_7);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_600
 * @tc.name      : GPIO_EX operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotGpioFuncTestSuite, testWifiIotGPIO088, LEVEL1)
{
    unsigned int ret;
    int gpioOutNum = WIFI_IOT_IO_NAME_MAX;
    WifiIotIoDriverStrength gpioGetDriverStrength = {0};

    ret = GpioDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = GpioInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = IOSetDriverStrength(gpioOutNum, WIFI_IOT_IO_DRIVER_STRENGTH_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }

    ret = IOGetDriverStrength(gpioOutNum, &gpioGetDriverStrength);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_GPIO_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_GPIO_NOT_SUPPORT))))
    {
        TEST_FAIL();
    }
};

RUN_TEST_SUITE(WifiIotGpioFuncTestSuite);
