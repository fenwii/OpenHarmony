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
#include "wifiiot_adc.h"
#include "wifiiot_errno.h"

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotAdcFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotAdcFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotAdcFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc001, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc002, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc003, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc004, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc005, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc006, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc007, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc008, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc009, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_0, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc010, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc011, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc012, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc013, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc014, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc015, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc016, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc017, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc018, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_7, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc019, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc020, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc021, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_1, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc022, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc023, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc024, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_8, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc025, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_AUTO, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc026, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_3P3V, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1500
 * @tc.name      : Adc operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotAdcFuncTestSuite, testWifiIotAdc027, LEVEL1)
{    
    unsigned int ret;
    unsigned short data = 0;
    ret = AdcRead(WIFI_IOT_ADC_CHANNEL_BUTT, &data, WIFI_IOT_ADC_EQU_MODEL_BUTT, WIFI_IOT_ADC_CUR_BAIS_BUTT, 0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_ADC_PARAMETER_WRONG) && (ret <= WIFI_IOT_ERR_ADC_NOT_INIT))))
    {
        TEST_FAIL();
    }
};

RUN_TEST_SUITE(WifiIotAdcFuncTestSuite);
