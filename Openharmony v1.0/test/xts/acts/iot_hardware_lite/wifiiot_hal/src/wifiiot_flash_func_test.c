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
#include "wifiiot_flash.h"
#include "wifiiot_flash_ex.h"

#define TEST_FLASH_SIZE 8
#define TEST_FLASH_SIZE_4K 4096
#define TEST_FLASH_OFFSET 0x1FF000

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is wifiiot
 * @param        : module name is wifiiotlite
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(wifiiot, wifiiotlite, WifiIotFlashFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotFlashFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiIotFlashFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_IOT_API_100
 * @tc.name      : Flash operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFlashFuncTestSuite, testWifiIotFlashEx, LEVEL1)
{
    unsigned int ret;
    char readtmp[TEST_FLASH_SIZE+1] = {0};   
    ret = FlashDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = FlashInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    (void)memset_s(readtmp, TEST_FLASH_SIZE, 0x0, TEST_FLASH_SIZE);
    ret = FlashIoctl(0, readtmp);
    if (!(ret == 0 || (((ret >= WIFI_IOT_ERR_FLASH_NOT_INIT) && (ret <= WIFI_IOT_ERR_FLASH_PROTECT_NOT_FIND_CHIP))
    ||((ret >= WIFI_IOT_ERR_FLASH_CRYPTO_INVALID_PARAM) && (ret <= WIFI_IOT_ERR_FLASH_CRYPTO_KERNEL_ADDR_ERR)))))
    {
        TEST_FAIL();
    }
};


/**
 * @tc.number    : SUB_UTILS_IOT_API_100
 * @tc.name      : Flash operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFlashFuncTestSuite, testWifiIotFlash001, LEVEL1)
{
    unsigned int ret;
    char writetmp[TEST_FLASH_SIZE+1] = {0}; 
    ret = FlashDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = FlashInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    (void)sprintf_s(writetmp, sizeof(writetmp), "test");
    ret = FlashWrite(TEST_FLASH_OFFSET, TEST_FLASH_SIZE, (const uint8 *)writetmp, 1);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_200
 * @tc.name      : Flash operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFlashFuncTestSuite, testWifiIotFlash002, LEVEL1)
{
    unsigned int ret;
    char readtmp[TEST_FLASH_SIZE+1] = {0};   
    ret = FlashDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = FlashInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    (void)memset_s(readtmp, TEST_FLASH_SIZE, 0x0, TEST_FLASH_SIZE);
    ret = FlashRead(TEST_FLASH_OFFSET, TEST_FLASH_SIZE, (uint8 *)readtmp);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_200
 * @tc.name      : Flash operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFlashFuncTestSuite, testWifiIotFlash003, LEVEL1)
{
    unsigned int ret;
    ret = FlashDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = FlashInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = FlashErase(TEST_FLASH_OFFSET, TEST_FLASH_SIZE_4K);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_IOT_API_200
 * @tc.name      : Flash operation
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(WifiIotFlashFuncTestSuite, testWifiIotFlash004, LEVEL1)
{
    unsigned int ret;
    char writetmp[TEST_FLASH_SIZE+1] = {0};
    char readtmp[TEST_FLASH_SIZE+1] = {0};   
    ret = FlashDeinit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = FlashInit();
    TEST_ASSERT_EQUAL_INT(0, ret);

    (void)sprintf_s(writetmp, sizeof(writetmp), "test");
    ret = FlashWrite(TEST_FLASH_OFFSET, TEST_FLASH_SIZE, (const uint8 *)writetmp, 1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    (void)memset_s(readtmp, TEST_FLASH_SIZE, 0x0, TEST_FLASH_SIZE);
    ret = FlashRead(TEST_FLASH_OFFSET, TEST_FLASH_SIZE, (uint8 *)readtmp);
    TEST_ASSERT_EQUAL_INT(0, ret);

    if (strcmp(readtmp, writetmp) != 0) {
        TEST_FAIL();
    }
    
    ret = FlashErase(TEST_FLASH_OFFSET, TEST_FLASH_SIZE_4K);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

RUN_TEST_SUITE(WifiIotFlashFuncTestSuite);
