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
#include <securec.h>
#include "hctest.h"
#include "parameter.h"
#include "parameter_utils.h"

#define MAX_LEN    128
#define INVALID_LEN    2
#define COMMON_ERROR (-1)
#define INVALID_PARAMETER (-9)

static const char* g_defSysParam = "data of sys param ***...";

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is parameter
 * @param        : test suit name is ParameterFuncTestSuite
 */
LITE_TEST_SUIT(utils, parameter, ParameterFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL ParameterFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL ParameterFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara001, LEVEL1)
{
    char* value = GetProductType();
    printf("Product Type=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara002, LEVEL1)
{
    char* value = GetManufacture();
    printf("Manufacture=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara003, LEVEL1)
{
    char* value = GetBrand();
    printf("Brand=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara004, LEVEL1)
{
    char* value = GetMarketName();
    printf("Market Name=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara005, LEVEL1)
{
    char* value = GetProductSeries();
    printf("Product Series=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara006, LEVEL1)
{
    char* value = GetProductModel();
    printf("Product Model=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara007, LEVEL1)
{
    char* value = GetHardwareModel();
    printf("Hardware Model=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara008, LEVEL1)
{
    char* value = GetHardwareProfile();
    printf("Hardware Profile=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara009, LEVEL1)
{
    char* value = GetSerial();
    printf("Serial=%s\n", value);
    if (value == NULL) {
        printf("The serial number needs to be written\n");
        TEST_IGNORE();
    } else {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara010, LEVEL1)
{
    char* value = GetOsName();
    printf("Os Name=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara011, LEVEL1)
{
    char* value = GetDisplayVersion();
    printf("Display Version=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara012, LEVEL1)
{
    char* value = GetBootloaderVersion();
    printf("Bootloader Version=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara013, LEVEL1)
{
    char* value = GetSecurityPatchTag();
    printf("Secure Patch Level=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara014, LEVEL1)
{
    char* value = GetAbiList();
    printf("Abi List=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara015, LEVEL1)
{
    char* value = GetFirstApiLevel();
    printf("First Api Level=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara016, LEVEL1)
{
    char* value = GetIncrementalVersion();
    printf("Incremental Version=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara017, LEVEL1)
{
    char* value = GetVersionId();
    printf("Version Id=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara018, LEVEL1)
{
    char* value = GetBuildType();
    printf("Build Type=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara019, LEVEL1)
{
    char* value = GetBuildUser();
    printf("Build User=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara020, LEVEL1)
{
    char* value = GetBuildHost();
    printf("Build Host=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara021, LEVEL1)
{
    char* value = GetBuildTime();
    printf("Build Time=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara022, LEVEL1)
{
    char* value = GetBuildRootHash();
    printf("Build Root Hash=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara023, LEVEL1)
{
    char* value = GetSoftwareModel();
    printf("Software Model=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Obtaining system parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testObtainSysPara024, LEVEL1)
{
    char* value = GetSdkApiLevel();
    printf("Sdk Api Level=%s\n", value);
    IsEmpty(value);
    free(value);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter001, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version_606";
    char value[] = "OEM-hisi-10.1.0";
    ret = SetParameter(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter002, LEVEL1)
{
    int ret;

    char key[] = "_._..__...___";
    char value[] = "！@#￥%……&*（）——+~《》？，。、“‘；：、12345767890";
    ret = SetParameter(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter003, LEVEL1)
{
    int ret;

    char key[] = "keywithonlylowercase";
    char value[] = "test key with only lowercase";
    ret = SetParameter(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter004, LEVEL1)
{
    int ret;

    char key[] = "202006060602";
    char value[] = "test key with only number";
    ret = SetParameter(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter legal test(length:key 31 bytes, value 127 bytes)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter005, LEVEL1)
{
    int ret;

    char key1[] = "rw.sys.version.version.version.";
    char value1[] = "set with key = 31";
    ret = SetParameter(key1, value1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    char key2[] = "rw.sys.version.version";
    char value2[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrs";
    ret = SetParameter(key2, value2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(key is nullptr, value is nullptr)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter006, LEVEL1)
{
    int ret;

    char value[] = "test with null";
    ret = SetParameter(NULL, value);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }

    char key[] = "rw.sys.version";
    ret = SetParameter(key, NULL);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(key is NULL, value is NULL)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter007, LEVEL1)
{
    int ret;

    char value[] = "test with null";
    ret = SetParameter("\0", value);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }

    char key[] = "rw.sys.version";
    ret = SetParameter(key, "\0");
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(key len is 32 or more than 32 bytes)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter008, LEVEL1)
{
    int ret;

    char key1[] = "rw.sys.version.version.version.v";
    char value1[] = "set with key = 32";
    ret = SetParameter(key1, value1);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }

    char key2[] = "rw.sys.version.version.version.version";
    char value2[] = "set with key > 32";
    ret = SetParameter(key2, value2);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(key with uppercase)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter009, LEVEL1)
{
    int ret;

    char key[] = "Rw.Sys.Version.Version";
    char value[] = "set value with uppercase";
    ret = SetParameter(key, value);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(key with blank)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter010, LEVEL1)
{
    int ret;

    char key[] = "rw sys version version";
    char value[] = "set value with blank";
    ret = SetParameter(key, value);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(key with special characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter011, LEVEL1)
{
    int ret;

    char key[] = "rw+sys&version%version*";
    char value[] = "set value with special characters";
    ret = SetParameter(key, value);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter illegal test(value length is 128 or more than 128 bytes)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter012, LEVEL1)
{
    int ret;

    char key1[] = "rw.sys.version.version1";
    char value1[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrst";
    ret = SetParameter(key1, value1);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }

    char key2[] = "rw.sys.version.version2";
    char value2[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890";
    ret = SetParameter(key2, value2);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : SetParameter parameter legal test(value contains only blanks)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testSetParameter013, LEVEL1)
{
    int ret;

    char key[] = "key_for_blank_value";
    char value[] = "                         ";
    ret = SetParameter(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter001, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version_606";
    char rightVal[] = "OEM-hisi-10.1.0";
    char value[MAX_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter002, LEVEL1)
{
    int ret;

    char key[] = "_._..__...___";
    char rightVal[] = "！@#￥%……&*（）——+~《》？，。、“‘；：、12345767890";
    char value[MAX_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter003, LEVEL1)
{
    int ret;

    char key[] = "keywithonlylowercase";
    char rightVal[] = "test key with only lowercase";
    char value[MAX_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter004, LEVEL1)
{
    int ret;

    char key[] = "202006060602";
    char rightVal[] = "test key with only number";
    char value[MAX_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(defaut value point is nullptr)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter005, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version_606";
    char rightVal[] = "OEM-hisi-10.1.0";
    char value[MAX_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, NULL, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(none exist key)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter006, LEVEL1)
{
    int ret;

    char key[] = "none.exist.key";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(g_defSysParam), ret);
    TEST_ASSERT_EQUAL_STRING(g_defSysParam, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(length:key is 31 bytes, value is 127 bytes)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter007, LEVEL1)
{
    int ret;

    char key1[] = "rw.sys.version.version.version.";
    char rightVal1[] = "set with key = 31";
    char value1[MAX_LEN] = {0};
    SetParameter(key1, rightVal1);
    ret = GetParameter(key1, g_defSysParam, value1, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal1), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal1, value1); 

    char key2[] = "rw.sys.version.version";
    char rightVal2[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrs";
    char value2[MAX_LEN] = {0};
    SetParameter(key2, rightVal2);
    ret = GetParameter(key2, g_defSysParam, value2, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal2), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal2, value2); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(value length is too short)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter008, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version_606";
    char rightVal[] = "OEM-hisi-10.1.0";
    char value[INVALID_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, value, INVALID_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(value point is nullptr)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter009, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version_606";
    char rightVal[] = "OEM-hisi-10.1.0";
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, NULL, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key is not exist and value len is too short)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter010, LEVEL1)
{
    int ret;

    char key[] = "none.exist.key";
    char value[INVALID_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, INVALID_LEN);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key is not exist and defaut value point is nullptr)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter011, LEVEL1)
{
    int ret;

    char key[] = "none.exist.key";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, NULL, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key len is 32 bytes)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter012, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version.version.version.v";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key len is more than 32 bytes)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter013, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version.version.version.version";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key is nullptr)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter014, LEVEL1)
{
    int ret;

    char value[MAX_LEN] = {0};
    ret = GetParameter(NULL, g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key with uppercase)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter015, LEVEL1)
{
    int ret;

    char key[] = "Rw.Sys.Version.Version";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key with blank)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter016, LEVEL1)
{
    int ret;

    char key[] = "rw sys version version";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key with special characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter017, LEVEL1)
{
    int ret;

    char key[] = "rw+sys&version%version*";
    char value[MAX_LEN] = {0};
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter illegal test(key is NULL)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter018, LEVEL1)
{
    int ret;

    char value[MAX_LEN] = {0};
    ret = GetParameter("\0", g_defSysParam, value, MAX_LEN);
    if ((ret == COMMON_ERROR) || (ret == INVALID_PARAMETER))
    {
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : GetParameter parameter legal test(value contains only blanks)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter019, LEVEL1)
{
    int ret;

    char key[] = "key_for_blank_value";
    char rightVal[] = "                         ";
    char value[MAX_LEN] = {0};
    SetParameter(key, rightVal);
    ret = GetParameter(key, g_defSysParam, value, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal, value); 
};

/**
 * @tc.number    : SUB_UTILS_PARAMETER_100
 * @tc.name      : Update value of parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ParameterFuncTestSuite, testGetParameter020, LEVEL1)
{
    int ret;

    char key[] = "rw.sys.version_606";
    char rightVal1[] = "OEM-hisi-10.1.0";
    char value1[MAX_LEN] = {0};
    ret = SetParameter(key, rightVal1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = GetParameter(key, g_defSysParam, value1, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal1), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal1, value1); 

    char rightVal2[] = "update the value of OEM-hisi-10.1.0";
    char value2[MAX_LEN] = {0};
    ret = SetParameter(key, rightVal2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = GetParameter(key, g_defSysParam, value2, MAX_LEN);
    TEST_ASSERT_EQUAL_INT(strlen(rightVal2), ret);
    TEST_ASSERT_EQUAL_STRING(rightVal2, value2); 
};

RUN_TEST_SUITE(ParameterFuncTestSuite);
