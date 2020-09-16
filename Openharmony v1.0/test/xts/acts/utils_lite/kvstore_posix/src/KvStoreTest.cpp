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

#include <stdio.h>
#include "gtest/gtest.h"
#include <securec.h>

#include "utils_config.h"
#include "kv_store.h"
#include "kvstore_env.h"

using namespace std;
using namespace testing::ext;

const int  MAX_KEY_LEN_TEST = 32;    // Key length specifications
const int  MAX_VALUE_LEN_TEST = 128;  // Value length specifications
const int  MAX_KEY_NUM_TEST = 50;   // Maximum number of keys
const int  MAX_CACHE_NUM_TEST = 10;  // Minimum number of cache
const int  INVALID_PARAMETER = -9;   // Invalid parameter.

class KvStoreTest : public testing::Test {
protected:
    // SetUpTestCase：测试套预置动作，在第一个TestCase之前执行
    static void SetUpTestCase(void) 
    {
        printf("----------test case with KvStoreTest start-------------\n");


        int ret = mkdir("/storage/com.huawei.kv", S_IRUSR | S_IWUSR);
        printf("/storage/com.huawei.kv ret = %d\n", ret);
        ret = UtilsSetEnv("/storage/com.huawei.kv");
        EXPECT_EQ(ret, 0);
    }
    // TearDownTestCase：测试套清理动作，在最后一个TestCase之后执行
    static void TearDownTestCase(void) 
    {
        int ret = rmdir("/storage/com.huawei.kv/kvstore");
        printf("/storage/com.huawei.kv/kvstore ret = %d\n", ret);
        ret = rmdir("/storage/com.huawei.kv");
        printf("/storage/com.huawei.kv ret = %d\n", ret);
        printf("----------test case with KvStoreTest end-------------\n");
    }
    // 用例的预置动作
    virtual void SetUp() {}
    // 用例的清理动作
    virtual void TearDown() {}
    bool TouchKVFiles (int num, const char* key, const char* value);
    bool DeleteKVFiles (int num, const char* key);
    bool ReadKVFiles (int num, const char* key, const char* value); 
};

/* Create files in batches. */
bool KvStoreTest::TouchKVFiles (int num, const char* key, const char* value) 
{
    int size = 0;
    int ret = 0;
    char keytemp[MAX_KEY_LEN_TEST] = {0};
    char valuetemp[MAX_VALUE_LEN_TEST] = {0};
    char temp[MAX_VALUE_LEN_TEST] = {0};
    if (num <= 0) {
        return false;
    }
    for (int i = 1; i <= num; i++) {
        size = sprintf_s(keytemp, MAX_KEY_LEN_TEST, "%s_%d", key, i);
        if (size < 0) {
            return false;
        }
        size = sprintf_s(valuetemp, MAX_VALUE_LEN_TEST, "%s_%d", value, i);
        if (size < 0) {
            return false;
        }    
        ret = UtilsSetValue(keytemp, valuetemp);
        if (i <= MAX_KEY_NUM_TEST) {
            EXPECT_EQ(ret, 0);
        } else {
            EXPECT_EQ(ret, -1);
        }
        ret = UtilsGetValue(keytemp, temp, MAX_VALUE_LEN_TEST);
        if (i <= MAX_KEY_NUM_TEST) {
            EXPECT_EQ(ret, 0);
            EXPECT_STREQ(valuetemp, temp);
        } else {
            EXPECT_EQ(ret, -1);
        }   
        memset_s(keytemp, MAX_KEY_LEN_TEST, 0, MAX_KEY_LEN_TEST);
        memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
        memset_s(valuetemp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
    }
    return true;
}

/* Create files in batches. */
bool KvStoreTest::ReadKVFiles (int num, const char* key, const char* value) 
{
    int size = 0;
    int ret = 0;
    int i = 1;
    char keytemp[MAX_KEY_LEN_TEST] = {0};
    char valuetemp[MAX_VALUE_LEN_TEST] = {0};
    char temp[MAX_VALUE_LEN_TEST] = {0};
    if (num <= 0) {
        return false;
    }
    for (; num > 0; num--) {
        size = sprintf_s(keytemp, MAX_KEY_LEN_TEST, "%s_%d", key, num);
        if (size < 0) {
            return false;
        }
        size = sprintf_s(valuetemp, MAX_VALUE_LEN_TEST, "%s_%d", value, num);
        if (size < 0) {
            return false;
        }    
        ret = UtilsGetValue(keytemp, temp, MAX_VALUE_LEN_TEST);
        if (num <= MAX_KEY_NUM_TEST) {
            if (i <= MAX_CACHE_NUM_TEST) {
                EXPECT_EQ(ret, 0);
            } else {
                EXPECT_GT(ret, 0);
            }
            EXPECT_STREQ(valuetemp, temp);
            i++;
        } else {
            EXPECT_EQ(ret, -1);
        }   
        memset_s(keytemp, MAX_KEY_LEN_TEST, 0, MAX_KEY_LEN_TEST);
        memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
        memset_s(valuetemp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
    }
    return true;
}

/* Delete files in batches. */
bool KvStoreTest::DeleteKVFiles (int num, const char* key) 
{
    int size = 0;
    int ret = 0;
    char keytemp[MAX_KEY_LEN_TEST] = {0};

    if (num <= 0) {
        return false;
    }
    for (int i = 1; i <= num; i++) {
        size = sprintf_s(keytemp, MAX_KEY_LEN_TEST, "%s_%d", key, i);
        if (size < 0) {
            return false;
        }  
        ret = UtilsDeleteValue(keytemp);
        if (i <= MAX_KEY_NUM_TEST) {
            EXPECT_EQ(ret, 0);
        } else {
            EXPECT_EQ(ret, -1);
        }    
        memset_s(keytemp, MAX_KEY_LEN_TEST, 0, MAX_KEY_LEN_TEST);       
    }
    return true;
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_100 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testUtilsSetValue001, TestSize.Level0)
{
    char key[] = "rw.sys.version";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_400 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(KvStoreTest, testUtilsSetValue002, TestSize.Level1)
{
    char key[] = "rw.sys.version_100";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);    
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_500 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(KvStoreTest, testUtilsSetValue003, TestSize.Level1)
{
    char key[] = "100";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);    
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_600 
 * @tc.name      : UtilsSetValue parameter legal test(key = 31 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue004, TestSize.Level2)
{
    char key[] = "rw.sys.version.utilskvparameter";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0); 

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);      
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_700 
 * @tc.name      : UtilsSetValue parameter Illegal test(key = 32 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue005, TestSize.Level2)
{
    char key[] = "rw.sys.version.utilskvparameter1";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);  
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_700  
 * @tc.name      : UtilsSetValue parameter Illegal test(key = 33 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue006, TestSize.Level2)
{
    char key[] = "rw.sys.version.utilskvparameter12";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER); 
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_700  
 * @tc.name      : UtilsSetValue parameter Illegal test(key > 33 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue007, TestSize.Level2)
{
    char key[] = "rw.sys.version.utilskvparameterforillegal";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);  
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1100
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue008, TestSize.Level2)
{
    char key[] = "Rw.sys.version";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1100
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue009, TestSize.Level2)
{
    char key[] = "rw.sys.version-r3";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);  
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1100
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue010, TestSize.Level2)
{
    char key[] = "RE+R3";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER); 
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1100
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue0011, TestSize.Level2)
{
    char key[] = "rw.sys.version*r3";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER); 
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_800 
 * @tc.name      : UtilsSetValue parameter legal test(Value is equal to 121 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testUtilsSetValue012, TestSize.Level0)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange ";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_800 
 * @tc.name      : UtilsSetValue parameter legal test(Value is equal to 126 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(KvStoreTest, testUtilsSetValue013, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange Howstrangesleeping";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_900 
 * @tc.name      : UtilsSetValue parameter legal test(Value is equal to 127 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(KvStoreTest, testUtilsSetValue014, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strangesleeping";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1000 
 * @tc.name      : UtilsSetValue parameter Illegal test(Value is equal to 128 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(KvStoreTest, testUtilsSetValue015, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange sleeping";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1000 
 * @tc.name      : UtilsSetValue parameter Illegal test(Value greater than 128 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue016, TestSize.Level2)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange  Are you sleeping";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1200 
 * @tc.name      : Value greater than 128 characters and key is an invalid character
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(KvStoreTest, testUtilsSetValue017, TestSize.Level2)
{
    char key[] = "Rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange  Are you sleeping";
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, INVALID_PARAMETER);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testUtilsGetValue001, TestSize.Level0)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_EQ(ret, 0);
    EXPECT_STREQ(value, temp);
    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testUtilsGetValue002, TestSize.Level1)
{
    char key[] = "100";
    char value[] = "！@#￥%……&*（）——+~《》？，。、“‘；：、12345767890";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_EQ(ret, 0);
    EXPECT_STREQ(value, temp);
    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_200 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testUtilsGetValue003, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    // Update the value of key
    char value1[] = "Two tigers,Two tigers,two tiger,running so fast";
    int ret = UtilsSetValue(key, value1);
    EXPECT_EQ(ret, 0);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_EQ(ret, 0);
    EXPECT_STREQ(value1, temp);
    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

#ifdef FEATURE_KV_CACHE
/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(ClearKVCache) to clear cache
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testClearKVCache001, TestSize.Level0)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    EXPECT_EQ(ret, 0);
    // Get the value of key
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_EQ(ret, 0);
    EXPECT_STREQ(value, temp);
    // Clear cache
    ret = ClearKVCache();
    EXPECT_EQ(ret, 0);
    // Get the value of key
    memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);   
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_GT(ret, 0);
    EXPECT_STREQ(value, temp);
    // Clear key
    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_200 
 * @tc.name      : Use the interface(ClearKVCache) to clear cache
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testClearKVCache002, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    // Update the value of key
    char value1[] = "Two tigers,Two tigers,two tiger,running so fast";
    int ret = UtilsSetValue(key, value1);
    EXPECT_EQ(ret, 0);
    // Get the value of key
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_EQ(ret, 0);
    EXPECT_STREQ(value1, temp);
    // Clear cache
    ret = ClearKVCache();
    EXPECT_EQ(ret, 0);
    // Get the value of key
    memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    EXPECT_GT(ret, 0);
    EXPECT_STREQ(value1, temp);
    // Clear key
    ret = UtilsDeleteValue(key);
    EXPECT_EQ(ret, 0);
}
#endif

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1300 
 * @tc.name      : Specification test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testKVCacheCacheSize001, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    bool ret = false;

    ret = TouchKVFiles(MAX_CACHE_NUM_TEST-1, key, value);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }
    ret = ReadKVFiles(MAX_CACHE_NUM_TEST-1, key, value);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }    
    ret = DeleteKVFiles(MAX_CACHE_NUM_TEST-1, key);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }   
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1300 
 * @tc.name      : Specification test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testKVCacheCacheSize002, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    bool ret = false;

    ret = TouchKVFiles(MAX_CACHE_NUM_TEST, key, value);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }
    ret = ReadKVFiles(MAX_CACHE_NUM_TEST, key, value);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }   
    ret = DeleteKVFiles(MAX_CACHE_NUM_TEST, key);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }   
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1300 
 * @tc.name      : Specification test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(KvStoreTest, testKVCacheCacheSize003, TestSize.Level1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    bool ret = false;

    ret = TouchKVFiles(MAX_CACHE_NUM_TEST+1, key, value);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }
    ret = ReadKVFiles(MAX_CACHE_NUM_TEST+1, key, value);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }   
    ret = DeleteKVFiles(MAX_CACHE_NUM_TEST+1, key);
    if (ret == true)
    {
        SUCCEED();
    }else
    {
        ADD_FAILURE();
    }   
}