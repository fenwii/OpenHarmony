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
#include "hos_errno.h"
#include "kv_store.h"
#include "utils_config.h"
#include "wifiiot_watchdog.h"

#define MAX_KEY_LEN_TEST    32
#define MAX_VALUE_LEN_TEST    128
#define MAX_KEY_NUM_TEST    50
#define MAX_CACHE_NUM_TEST    10
#define INVALID_KEY_NUM    128

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is kvStore
 * @param        : test suit name is KvStoreFuncTestSuite
 */
LITE_TEST_SUIT(utils, kvStore, KvStoreFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL KvStoreFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL KvStoreFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/* Create files in batches. */
bool SetKVFiles (int num, const char* key, const char* value) 
{
    int size;
    int ret;
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
            TEST_ASSERT_EQUAL_INT(0, ret);
        } else {
            TEST_ASSERT_EQUAL_INT(-1, ret);
        }
        ret = UtilsGetValue(keytemp, temp, MAX_VALUE_LEN_TEST);
        if (i <= MAX_KEY_NUM_TEST) {
#ifdef FEATURE_KV_CACHE
            TEST_ASSERT_EQUAL_INT(0, ret);
#else
            TEST_ASSERT_GREATER_THAN_INT(0, ret);
#endif
            TEST_ASSERT_EQUAL_STRING(valuetemp, temp); 
        } else {
            TEST_ASSERT_EQUAL_INT(-1, ret);
        }   
        memset_s(keytemp, MAX_KEY_LEN_TEST, 0, MAX_KEY_LEN_TEST);
        memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
        memset_s(valuetemp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
        WatchDogKick();
    }
    WatchDogKick();
    return true;
}

/* Read files in batches. */
bool ReadKVFiles (int num, const char* key, const char* value) 
{
    int size;
    int ret;
    int i = 1;
    char keytemp[MAX_KEY_LEN_TEST] = {0};
    char valuetemp[MAX_VALUE_LEN_TEST] = {0};
    char temp[MAX_VALUE_LEN_TEST] = {0};
    if (num <= 0) {
        return false;
    }
    for (int loop = num; loop > 0; loop--) {
        size = sprintf_s(keytemp, MAX_KEY_LEN_TEST, "%s_%d", key, loop);
        if (size < 0) {
            return false;
        }
        size = sprintf_s(valuetemp, MAX_VALUE_LEN_TEST, "%s_%d", value, loop);
        if (size < 0) {
            return false;
        }    
        ret = UtilsGetValue(keytemp, temp, MAX_VALUE_LEN_TEST);
        if (loop <= MAX_KEY_NUM_TEST) {
            if (i <= MAX_CACHE_NUM_TEST) {
#ifdef FEATURE_KV_CACHE
                TEST_ASSERT_EQUAL_INT(0, ret);
#else
                TEST_ASSERT_GREATER_THAN_INT(0, ret);
#endif
            } else {
                TEST_ASSERT_GREATER_THAN_INT(0, ret);
            }
            TEST_ASSERT_EQUAL_STRING(valuetemp, temp); 
            i++;
        } else {
            TEST_ASSERT_EQUAL_INT(-1, ret);
        }   
        memset_s(keytemp, MAX_KEY_LEN_TEST, 0, MAX_KEY_LEN_TEST);
        memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
        memset_s(valuetemp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
        WatchDogKick();
    }
    WatchDogKick();
    return true;
}

/* Delete files in batches. */
bool DeleteKVFiles (int num, const char* key) 
{
    int size;
    int ret;
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
            TEST_ASSERT_EQUAL_INT(0, ret);
        } else {
            TEST_ASSERT_EQUAL_INT(-1, ret);
        }    
        memset_s(keytemp, MAX_KEY_LEN_TEST, 0, MAX_KEY_LEN_TEST);
        WatchDogKick();       
    }
    WatchDogKick();
    return true;
}

/**
 * @tc.number    : SUB_UTILS_KV_STORE_100 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue001, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_500 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue002, LEVEL1)
{
    char key[] = "rw.sys.version_100";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_800 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue003, LEVEL1)
{
    char key[] = "100";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_600 
 * @tc.name      : UtilsSetValue parameter legal test(key = 31 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue004, LEVEL1)
{
    char key[] = "rw.sys.version.utilskvparameter";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_700 
 * @tc.name      : UtilsSetValue parameter Illegal test(key = 32 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue005, LEVEL1)
{
    char key[] = "rw.sys.version.utilskvparameter1";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_700 
 * @tc.name      : UtilsSetValue parameter Illegal test(key > 32 Byte)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue006, LEVEL1)
{
    char key[] = "rw.sys.version.utilskvparameterforillegal";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1100 
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue007, LEVEL1)
{
    char key[] = "Rw.sys.version";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1200 
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue008, LEVEL1)
{
    char key[] = "rw.sys.version-r3";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1200 
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue009, LEVEL1)
{
    char key[] = "re+r3";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1200 
 * @tc.name      : UtilsSetValue parameter Illegal test(key is an invalid character)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue010, LEVEL1)
{
    char key[] = "rw.sys.version*r3";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_900 
 * @tc.name      : UtilsSetValue parameter legal test(Value is equal to 127 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue011, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strangesleeping";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1000 
 * @tc.name      : UtilsSetValue parameter Illegal test(Value is equal to 128 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue012, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange sleeping";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1000 
 * @tc.name      : UtilsSetValue parameter Illegal test(Value greater than 128 characters)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue013, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange  Are you sleeping";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1100 
 * @tc.name      : Value greater than 128 characters and key is an invalid character
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue014, LEVEL1)
{
    char key[] = "Rw.sys.version";
    char value[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strange  Are you sleeping";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_100 
 * @tc.name      : UtilsSetValue parameter legal test(Lowercase alphanumeric, underscore, dot)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue015, LEVEL1)
{
    char key[] = "_._..__...___";
    char value[] = "！@#￥%……&*（）——+~《》？，。、“‘；：、12345767890";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1200 
 * @tc.name      : UtilsSetValue parameter Illegal test(key contains space)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue016, LEVEL1)
{
    char key[] = "rw.sys.version space test";
    char value[] = "Hello world !";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_100 
 * @tc.name      : UtilsSetValue parameter legal test(value contains only space)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreSetValue017, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "                                                   ";
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreGetValue001, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
#ifdef FEATURE_KV_CACHE
        TEST_ASSERT_EQUAL_INT(0, ret);
#else
        TEST_ASSERT_GREATER_THAN_INT(0, ret);
#endif
    TEST_ASSERT_EQUAL_STRING(value, temp); 
    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreGetValue002, LEVEL1)
{
    char key[] = "100";
    char value[] = "！@#￥%……&*（）——+~《》？，。、“‘；：、12345767890";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
#ifdef FEATURE_KV_CACHE
        TEST_ASSERT_EQUAL_INT(0, ret);
#else
        TEST_ASSERT_GREATER_THAN_INT(0, ret);
#endif
    TEST_ASSERT_EQUAL_STRING(value, temp); 
    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_200 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreGetValue003, LEVEL1)
{
    char key[] = "rw.sys.version.utilskvparameter";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    // Update the value of key
    char value1[] = "Two tigers Two tigers two tiger running so fast \
running so fast one has no ears one has no tail How strange How strangesleeping";
    ret = UtilsSetValue(key, value1);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
#ifdef FEATURE_KV_CACHE
        TEST_ASSERT_EQUAL_INT(0, ret);
#else
        TEST_ASSERT_GREATER_THAN_INT(0, ret);
#endif
    TEST_ASSERT_EQUAL_STRING(value1, temp); 
    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : UtilsGetValue parameter Illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreGetValue004, LEVEL1)
{
    char key[] = "Rw.sys.version";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(UtilsGetValue) to get the kv value(cache)
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreGetValue005, LEVEL1)
{
    char key[] = "_._..__...___";
    char value[] = "                                                 ";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
#ifdef FEATURE_KV_CACHE
        TEST_ASSERT_EQUAL_INT(0, ret);
#else
        TEST_ASSERT_GREATER_THAN_INT(0, ret);
#endif
    TEST_ASSERT_EQUAL_STRING(value, temp); 
    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_400 
 * @tc.name      : UtilsDeleteValue parameter Illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreDeleteValue, LEVEL1)
{
    char key[] = "Rw.sys.version";
    int ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(EC_INVALID, ret);
};

#ifdef FEATURE_KV_CACHE
/**
 * @tc.number    : SUB_UTILS_KV_STORE_300 
 * @tc.name      : Use the interface(ClearKVCache) to clear cache
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreClearCache001, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Get the value of key
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING(value, temp); 
    // Clear cache
    ret = ClearKVCache();
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Get the value of key
    memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);   
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    TEST_ASSERT_GREATER_THAN_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING(value, temp); 
    // Clear key
    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_200 
 * @tc.name      : Use the interface(ClearKVCache) to clear cache
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreClearCache002, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    char temp[MAX_VALUE_LEN_TEST] = {0};
    int ret = UtilsSetValue(key, value);
    TEST_ASSERT_EQUAL_INT(0, ret);

    // Update the value of key
    char value1[] = "Two tigers,Two tigers,two tiger,running so fast";
    ret = UtilsSetValue(key, value1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Get the value of key
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING(value1, temp); 
    // Clear cache
    ret = ClearKVCache();
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Get the value of key
    memset_s(temp, MAX_VALUE_LEN_TEST, 0, MAX_VALUE_LEN_TEST);
    ret = UtilsGetValue(key, temp, MAX_VALUE_LEN_TEST);
    TEST_ASSERT_GREATER_THAN_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING(value1, temp); 
    // Clear key
    ret = UtilsDeleteValue(key);
    TEST_ASSERT_EQUAL_INT(0, ret);
};
#endif

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1600 
 * @tc.name      : Specification test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreCacheSize001, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    bool ret = false;

    ret = SetKVFiles(MAX_CACHE_NUM_TEST-1, key, value);
    if (ret != true)
    {
        TEST_FAIL();
    }
    ret = ReadKVFiles(MAX_CACHE_NUM_TEST-1, key, value);
    if (ret != true)
    {
        TEST_FAIL();
    } 
    ret = DeleteKVFiles(MAX_CACHE_NUM_TEST-1, key);
    if (ret != true)
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1600 
 * @tc.name      : Specification test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreCacheSize002, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    bool ret = false;

    ret = SetKVFiles(MAX_CACHE_NUM_TEST, key, value);
    if (ret != true)
    {
        TEST_FAIL();
    }
    ret = ReadKVFiles(MAX_CACHE_NUM_TEST, key, value);
    if (ret != true)
    {
        TEST_FAIL();
    } 
    ret = DeleteKVFiles(MAX_CACHE_NUM_TEST, key);
    if (ret != true)
    {
        TEST_FAIL();
    }
};

/**
 * @tc.number    : SUB_UTILS_KV_STORE_1600 
 * @tc.name      : Specification test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(KvStoreFuncTestSuite, testKvStoreCacheSize003, LEVEL1)
{
    char key[] = "rw.sys.version";
    char value[] = "It is never too old to learn";
    bool ret = false;

    ret = SetKVFiles(MAX_CACHE_NUM_TEST+1, key, value);
    if (ret != true)
    {
        TEST_FAIL();
    }
    ret = ReadKVFiles(MAX_CACHE_NUM_TEST+1, key, value);
    if (ret != true)
    {
        TEST_FAIL();
    } 
    ret = DeleteKVFiles(MAX_CACHE_NUM_TEST+1, key);
    if (ret != true)
    {
        TEST_FAIL();
    }
};

RUN_TEST_SUITE(KvStoreFuncTestSuite);
