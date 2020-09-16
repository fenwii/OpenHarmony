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

#include <cstdio>
#include "gtest/gtest.h"
#include "parameter.h"
using namespace std;
using namespace testing::ext;

namespace StartUpLite {
    static const int GET_DEF_PARA_FUN_MAX = 24;
    static const int MAX_LEN = 128;
    static const int WRONG_LEN = 2;
class ParameterTest : public testing::Test {
protected:
    static void SetUpTestCase(void) 
    {
        mkdir("/data", S_IRUSR | S_IWUSR);
        mkdir("/data/system", S_IRUSR | S_IWUSR);
        mkdir("/data/system/param", S_IRUSR | S_IWUSR);
    }
    static void TearDownTestCase(void) {}
    virtual void SetUp() {}
    virtual void TearDown() {}
    string defSysParam = "data of sys param ***...";
    using GetRdonlyPara = char* (*)();
    using GetDefParaNode = struct TagGetDefParaNode {
        char const *funName;
        GetRdonlyPara fun;
    };
    GetDefParaNode getDefPara[StartUpLite::GET_DEF_PARA_FUN_MAX] = {
        {"GetProductType", GetProductType},
        {"GetManufacture", GetManufacture},
        {"GetBrand", GetBrand},
        {"GetMarketName", GetMarketName},
        {"GetProductSeries", GetProductSeries},
        {"GetProductModel", GetProductModel},
        {"GetSoftwareModel", GetSoftwareModel},
        {"GetHardwareModel", GetHardwareModel},
        {"GetHardwareProfile", GetHardwareProfile},
        {"GetOsName", GetOsName},
        {"GetDisplayVersion", GetDisplayVersion},
        {"GetBootloaderVersion", GetBootloaderVersion},
        {"GetSecurityPatchTag", GetSecurityPatchTag},
        {"GetAbiList", GetAbiList},
        {"GetFirstApiLevel", GetFirstApiLevel},
        {"GetSdkApiLevel", GetSdkApiLevel},
        {"GetIncrementalVersion", GetIncrementalVersion},
        {"GetVersionId", GetVersionId},
        {"GetBuildType", GetBuildType},
        {"GetBuildUser", GetBuildUser},
        {"GetBuildHost", GetBuildHost},
        {"GetBuildTime", GetBuildTime},
        {"GetBuildRootHash", GetBuildRootHash},
        {"GetSerial", GetSerial},
    };
};

/**
 * @tc.number    : SUB_START_Para_Setting_Legal_0010 
 * @tc.name      : SetParameter legal test with Lowercase alphanumeric, underscore, dot
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_Legal_0010, TestSize.Level0)
{
    int ret;

    char key[] = "rw.sys.version";
    char value[] = "OEM-hisi-10.1.0";
    ret = SetParameter(key, value);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_START_Para_Setting_Legal_0020 
 * @tc.name      : SetParameter legal test with key 31 bytes, value 127 bytes
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_Legal_0020, TestSize.Level0)
{
    int ret;

    char key1[] = "rw.sys.version.version.version.";
    char value1[] = "set with key = 31";
    ret = SetParameter(key1, value1);
    EXPECT_EQ(ret, 0);

    char key2[] = "rw.sys.version.version";
    char value2[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrs";
    ret = SetParameter(key2, value2);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_START_Para_Setting_ilLegal_0010 
 * @tc.name      : SetParameter legal test with key is nullptr, value is nullptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_ilLegal_0010, TestSize.Level2)
{
    int ret;

    char value[] = "test with null";
    ret = SetParameter(nullptr, value);
    EXPECT_EQ(ret, -9);

    char key[] = "rw.sys.version";
    ret = SetParameter(key, nullptr);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Setting_ilLegal_0020 
 * @tc.name      : SetParameter legal test with key is NULL, value is NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_ilLegal_0020, TestSize.Level2)
{
    int ret = SetParameter("\0", "\0");
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Setting_ilLegal_key_0010 
 * @tc.name      : SetParameter legal test with key 32 or more than 32 bytes
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_ilLegal_key_0010, TestSize.Level2)
{
    int ret;

    char key1[] = "rw.sys.version.version.version.v";
    char value1[] = "set with key = 32";
    ret = SetParameter(key1, value1);
    EXPECT_EQ(ret, -9);

    char key2[] = "rw.sys.version.version.version.version";
    char value2[] = "set with key > 32";
    ret = SetParameter(key2, value2);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Setting_ilLegal_key_0030 
 * @tc.name      : SetParameter legal test with illegal characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_ilLegal_key_0030, TestSize.Level2)
{
    int ret;

    char key[] = "rw.sys.version*%version";
    char value[] = "set value with illegal key";
    ret = SetParameter(key, value);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Setting_ilLegal_value_0010 
 * @tc.name      : SetParameter legal test with value is 128 or more than 128 bytes
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Setting_ilLegal_value_0010, TestSize.Level2)
{
    int ret;

    char key1[] = "rw.sys.version.version";
    char value1[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrst";
    ret = SetParameter(key1, value1);
    EXPECT_EQ(ret, -9);

    char key2[] = "rw.sys.version.version";
    char value2[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890";
    ret = SetParameter(key2, value2);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Getting_Legal_0010 
 * @tc.name      : GetParameter legal test with Lowercase alphanumeric, underscore, dot
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_Legal_0010, TestSize.Level0)
{
    int ret;

    char key[] = "rw.sys.version";
    char rightVal[] = "OEM-hisi-10.1.0";
    char value[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key, defSysParam.c_str(), value, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, strlen(rightVal));
    EXPECT_STREQ(value, rightVal);
}

/**
 * @tc.number    : SUB_START_Para_Getting_Legal_0020 
 * @tc.name      : GetParameter legal test with defaut value point is nullptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_Legal_0020, TestSize.Level0)
{
    int ret;

    char key[] = "rw.sys.version";
    char rightVal[] = "OEM-hisi-10.1.0";
    char value[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key, nullptr, value, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, strlen(rightVal));
    EXPECT_STREQ(value, rightVal);
}

/**
 * @tc.number    : SUB_START_Para_Getting_Legal_0030 
 * @tc.name      : GetParameter legal test with length is 31 bytes, value is 127 bytes
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_Legal_0030, TestSize.Level0)
{
    int ret;

    char key1[] = "rw.sys.version.version.version.";
    char rightVal1[] = "set with key = 31";
    char value1[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key1, defSysParam.c_str(), value1, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, strlen(rightVal1));
    EXPECT_STREQ(value1, rightVal1);

    char key2[] = "rw.sys.version.version";
    char rightVal2[] = "abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\
abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrs";
    char value2[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key2, defSysParam.c_str(), value2, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, strlen(rightVal2));
    EXPECT_STREQ(value2, rightVal2);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ilLegal_0010 
 * @tc.name      : GetParameter legal test with value length is too short
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ilLegal_0010, TestSize.Level2)
{
    int ret;

    char key[] = "rw.sys.version";
    char value[StartUpLite::WRONG_LEN] = {0};
    ret = GetParameter(key, defSysParam.c_str(), value, StartUpLite::WRONG_LEN);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ilLegal_0020 
 * @tc.name      : GetParameter legal test with value point is nullptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ilLegal_0020, TestSize.Level2)
{
    int ret;

    char key[] = "rw.sys.version";
    ret = GetParameter(key, defSysParam.c_str(), nullptr, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ilLegal_0030 
 * @tc.name      : GetParameter legal test with key is not exist and vlan len is too short
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ilLegal_0030, TestSize.Level2)
{
    int ret;

    char key1[] = "rw.product.not.exist";
    char value1[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key1, defSysParam.c_str(), value1, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, strlen(defSysParam.c_str()));
    EXPECT_STREQ(value1, defSysParam.c_str());

    char value2[StartUpLite::WRONG_LEN] = {0};
    ret = GetParameter(key1, defSysParam.c_str(), value2, StartUpLite::WRONG_LEN);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ilLegal_0040 
 * @tc.name      : GetParameter legal test with key is 32 bytes
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ilLegal_0040, TestSize.Level2)
{
    int ret;

    char key[] = "rw.sys.version.version.version.v";
    char value[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key, defSysParam.c_str(), value, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ilLegal_0050 
 * @tc.name      : GetParameter legal test with key is nullptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ilLegal_0050, TestSize.Level2)
{
    int ret;

    char value[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(nullptr, defSysParam.c_str(), value, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ilLegal_0060 
 * @tc.name      : GetParameter legal test with key is illegal with Special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ilLegal_0060, TestSize.Level2)
{
    int ret;

    char key[] = "rw.sys.version*%version";
    char value[StartUpLite::MAX_LEN] = {0};
    ret = GetParameter(key, defSysParam.c_str(), value, StartUpLite::MAX_LEN);
    EXPECT_EQ(ret, -9);
}

/**
 * @tc.number    : SUB_START_Para_Getting_ReadOnly_0010 
 * @tc.name      : GetParameter read only parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(ParameterTest, SUB_START_Para_Getting_ReadOnly_0010, TestSize.Level0)
{
    char *value = nullptr;

    for (int loop = 0; loop < StartUpLite::GET_DEF_PARA_FUN_MAX; loop++) {
        value = getDefPara[loop].fun();
        EXPECT_STRNE(value, (char *)nullptr);
        if (value != nullptr) {
            free(value);
        }
    }
}
}