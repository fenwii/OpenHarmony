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
#include "wifiiot_watchdog.h"
#include "wifiiot_partition.h"
#include "wifiiot_at.h"
#include "wifiiot_kal.h"
#ifdef CONFIG_I2S_SUPPORT
#include "wifiiot_i2s.h"
#endif
#ifdef CONFIG_PWM_SUPPORT
#include "wifiiot_pwm.h"
#endif

#define TEST_REGISTER_CMD 2
#define TEST_PWM_PORT 1200
#define TEST_PWM_DUTY 1500
#define TEST_I2S_SIZE 8
#define TEST_I2S_TIMEOUT 1000

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_1200
 * @tc.name      : Watchdog operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotWatchdog, LEVEL1)
{
    WatchDogEnable();
    WatchDogKick();
    WatchDogDisable();
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1300
 * @tc.name      : Partition operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotPartition, LEVEL1)
{    
    unsigned int ret;
    char *table = 0;

    ret = FlashPartitionInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    
    table = (char *)GetPartitionTable();
    if (table == 0) {
        TEST_FAIL();    
    }
};

int DemoAtExeTest1Cmd(void)
{
    int ret = AtPrintf("DemoAtExeTest1Cmd!\n");
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    return 0;
}

int DemoAtExeTest2Cmd(void)
{
    int ret = AtPrintf("DemoAtExeTest2Cmd!\n");
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    return 0;
}

AtCmdTbl g_regatcmdtbl[] = {
    {"+TEST1", 6, 0, 0, 0, (AtCallbackFunc)DemoAtExeTest1Cmd},
    {"+TEST2", 6, 0, 0, 0, (AtCallbackFunc)DemoAtExeTest2Cmd},
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1600
 * @tc.name      : Partition operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotAt001, LEVEL1)
{    
    unsigned int ret;
    ret = AtInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    AtSysCmdRegister();
    AtCheckUartBusy(1);
    ret = AtRegisterCmd(g_regatcmdtbl, TEST_REGISTER_CMD);
    if (!(((ret >= WIFI_IOT_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED) && (ret <= WIFI_IOT_ERR_AT_INVALID_PARAMETER))
    || ret == 0))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1700
 * @tc.name      : Partition operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotAt002, LEVEL1)
{    
    unsigned int ret;
    ret = AtInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    AtSysCmdRegister();
    AtCheckUartBusy(0);
    ret = AtRegisterCmd(g_regatcmdtbl, TEST_REGISTER_CMD);
    if (!(((ret >= WIFI_IOT_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED) && (ret <= WIFI_IOT_ERR_AT_INVALID_PARAMETER))
    || ret == 0))
    {
        TEST_FAIL();
    }
};

#ifdef CONFIG_PWM_SUPPORT
/**
 * @tc.number    : SUB_UTILS_IOT_API_1400
 * @tc.name      : Pwm operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotPwm001, LEVEL1)
{    
    unsigned int ret;
    ret = PwmDeinit(WIFI_IOT_PWM_PORT_PWM0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    } 
    ret =PwmInit(WIFI_IOT_PWM_PORT_PWM0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret =PwmStart(WIFI_IOT_PWM_PORT_PWM0, TEST_PWM_PORT, TEST_PWM_DUTY);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret = PwmStop(WIFI_IOT_PWM_PORT_PWM0); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret = PwmDeinit(WIFI_IOT_PWM_PORT_PWM0);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    } 
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1400
 * @tc.name      : Pwm operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotPwm002, LEVEL1)
{    
    unsigned int ret;
    ret = PwmDeinit(WIFI_IOT_PWM_PORT_PWM5);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    } 
    ret =PwmInit(WIFI_IOT_PWM_PORT_PWM5);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret =PwmStart(WIFI_IOT_PWM_PORT_PWM5, TEST_PWM_PORT, TEST_PWM_DUTY);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret = PwmStop(WIFI_IOT_PWM_PORT_PWM5); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret = PwmDeinit(WIFI_IOT_PWM_PORT_PWM5);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    } 
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_1400
 * @tc.name      : Pwm operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotPwm003, LEVEL1)
{    
    unsigned int ret;
    ret = PwmDeinit(WIFI_IOT_PWM_PORT_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    } 
    ret =PwmInit(WIFI_IOT_PWM_PORT_MAX);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret =PwmStart(WIFI_IOT_PWM_PORT_MAX, TEST_PWM_PORT, TEST_PWM_DUTY);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
    ret = PwmStop(WIFI_IOT_PWM_PORT_MAX); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_PWM_NO_INIT) && (ret <= WIFI_IOT_ERR_PWM_INVALID_PARAMETER))))
    {
        TEST_FAIL();
    }
};
#endif

#ifdef CONFIG_I2S_SUPPORT
/**
 * @tc.number    : SUB_UTILS_IOT_API_2500
 * @tc.name      : I2s operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotI2s001, LEVEL1)
{    
    unsigned int ret;
    unsigned char writeBuf[] = "I2sDemoTest";
    unsigned char readBuf[TEST_I2S_SIZE] = "";
    
    WifiIotI2sAttribute i2s_cfg;
    i2s_cfg.sampleRate = WIFI_IOT_I2S_SAMPLE_RATE_8K;
    i2s_cfg.resolution = WIFI_IOT_I2S_RESOLUTION_16BIT;

    ret = I2sDeinit();
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sInit(&i2s_cfg); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sWrite(writeBuf, sizeof(writeBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }

    ret = I2sRead(readBuf, sizeof(readBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2500
 * @tc.name      : I2s operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotI2s002, LEVEL1)
{    
    unsigned int ret;
    unsigned char writeBuf[] = "I2sDemoTest";
    unsigned char readBuf[TEST_I2S_SIZE] = "";
    
    WifiIotI2sAttribute i2s_cfg;
    i2s_cfg.sampleRate = WIFI_IOT_I2S_SAMPLE_RATE_8K;
    i2s_cfg.resolution = WIFI_IOT_I2S_RESOLUTION_24BIT;

    ret = I2sDeinit();
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sInit(&i2s_cfg); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sWrite(writeBuf, sizeof(writeBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }

    ret = I2sRead(readBuf, sizeof(readBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2500
 * @tc.name      : I2s operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotI2s003, LEVEL1)
{    
    unsigned int ret;
    unsigned char writeBuf[] = "I2sDemoTest";
    unsigned char readBuf[TEST_I2S_SIZE] = "";
    
    WifiIotI2sAttribute i2s_cfg;
    i2s_cfg.sampleRate = WIFI_IOT_I2S_SAMPLE_RATE_48K;
    i2s_cfg.resolution = WIFI_IOT_I2S_RESOLUTION_16BIT;

    ret = I2sDeinit();
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sInit(&i2s_cfg); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sWrite(writeBuf, sizeof(writeBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }

    ret = I2sRead(readBuf, sizeof(readBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2500
 * @tc.name      : I2s operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotI2s004, LEVEL1)
{    
    unsigned int ret;
    unsigned char writeBuf[] = "I2sDemoTest";
    unsigned char readBuf[TEST_I2S_SIZE] = "";
    
    WifiIotI2sAttribute i2s_cfg;
    i2s_cfg.sampleRate = WIFI_IOT_I2S_SAMPLE_RATE_48K;
    i2s_cfg.resolution = WIFI_IOT_I2S_RESOLUTION_24BIT;

    ret = I2sDeinit();
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sInit(&i2s_cfg); 
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
    ret = I2sWrite(writeBuf, sizeof(writeBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }

    ret = I2sRead(readBuf, sizeof(readBuf), TEST_I2S_TIMEOUT);
    if (!(ret == 0 || ((ret >= WIFI_IOT_ERR_I2S_INVALID_PARAMETER) && (ret <= WIFI_IOT_ERR_I2S_WRITE_TIMEOUT))))
    {
        TEST_FAIL();
    }
};
#endif

void TickCB(void)
{
    printf("Tick callback function\n");
    KalTickRegisterCallback(0);
}
void IdleCB(void)
{
    printf("Idle task callback function\n");
    KalThreadRegisterIdleCallback(0);
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_2600
 * @tc.name      : Kal operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotKal001, LEVEL1)
{
    KalTickRegisterCallback(TickCB);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_2700
 * @tc.name      : Kal operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFuncTestSuite, testWifiIotKal002, LEVEL1)
{
    KalThreadRegisterIdleCallback(IdleCB);
};

RUN_TEST_SUITE(WifiIotFuncTestSuite);
