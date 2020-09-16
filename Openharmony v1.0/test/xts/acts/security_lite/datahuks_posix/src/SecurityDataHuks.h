/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TEST_XTS_ACTS_SECURITY_LITE_DATAHUKS_POSIX_SRC_SECURITYDATAHUKS_H
#define TEST_XTS_ACTS_SECURITY_LITE_DATAHUKS_POSIX_SRC_SECURITYDATAHUKS_H
#include "hks_client.h"
#include "hks_types.h"
#include <securec.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hks_file_api.h>
#include "gtest/gtest.h"
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>
#include "hks_errno.h"
#include <sys/time.h>
#include <hks_hardware_api.h>

#define DOUBLE_INT(x) ((x) * 2)
#define DOUBLE_STR_LEN(x) ((x) * 2 + 1)
#define FILE_ERROR -1
#define FILE_PATH_LENGTH  256
#define HICHAIN_FILEPATH "/storage/"
#define HKS_FREE_PTR1(p) { if ((p) != NULL) { free(p); (p) = NULL; }}

constexpr int NUM1 = 1;
constexpr int NUM2 = 2;
constexpr int NUM3 = 3;
constexpr int NUM4 = 4;
constexpr int NUM5 = 5;
constexpr int NUM6 = 6;
constexpr int NUM8 = 8;
constexpr int NUM9 = 9;
constexpr int NUM10 = 10;
constexpr int NUM11 = 11;
constexpr int NUM15 = 15;
constexpr int NUM16 = 16;
constexpr int NUM20 = 20;
constexpr int NUM30 = 30;
constexpr int NUM21 = 21;
constexpr int NUM24 = 24;
constexpr int NUM32 = 32;
constexpr int NUM60 = 60;
constexpr int NUM62 = 62;
constexpr int NUM64 = 64;
constexpr int NUM65 = 65;
constexpr int NUM88 = 88;
constexpr int NUM100 = 100;
constexpr int NUM128 = 128;
constexpr int NUM192 = 192;
constexpr int NUM256 = 256;
constexpr int NUM1025 = 1025;
constexpr int NUM2048 = 2048;
constexpr int NUM1234567 = 1234567;
constexpr int NUM1000000 = 1000000;
constexpr int NUM134 = -134;
constexpr int NUM135 = -135;
constexpr int NUM142 = -142;
constexpr int NUM1000 = -1000;
constexpr int NUM1006 = -1006;
constexpr int NUM1007 = -1007;
constexpr int NUM1010 = -1010;
constexpr int G_COUNT_MEM = 10000;
constexpr int MAX_INT = 2147483647;

using namespace std;
using namespace testing::ext;
using errno_t = int32_t;

static errno_t FopenS(FILE **fp, const char *filename, const char *modes)
{
    *fp = fopen(filename, modes);
    return 0;
}

static int32_t FileSize(const char *filename)
{
    FILE *fp = nullptr;
    errno_t err;
    int32_t size;

    if (filename == nullptr) {
        return -1;
    }

    err = FopenS(&fp, filename, "rb");
    if (err != 0 || fp == nullptr) {
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    size = ftell(fp);
    fclose(fp);

    return size;
}
static int32_t FileWrite(const char *filename, uint32_t offset, const uint8_t *buf, uint32_t len) 
{
    FILE *fp = nullptr;
    errno_t err;
    size_t size;
    char path[256] = {0};

    if (filename == NULL || buf == NULL) {
        return -1;
    }

    err = FopenS(&fp, filename, "wb+");
    if (err != 0 || fp == nullptr) {
        return -1;
    }

    size = fwrite(buf, 1, len, fp);
    fclose(fp);

    if (size != len) {
        return -1;
    }

    return 0;
}

static int32_t FileRead(const char *filename, uint32_t offset, uint8_t *buf, uint32_t len) 
{
    FILE* fp = nullptr;
    errno_t err;
    size_t size;

    if (filename == NULL || buf == NULL) {
        return -1;
    }

    if (access(filename, 0) == -1) {
        return 0;
    }

    err = FopenS(&fp, filename, "rb");
    if (err == NUM2) {
        return 0;
    }
    if (err != 0 || fp == nullptr) {
        return -1;
    }

    size = fread(buf, 1, len, fp);
    fclose(fp);

    if (size == 0) {
        return -1;
    }

    return size;
}

static uint64_t GetTimeMs()
{
    struct timeval timeVal;
    gettimeofday(&timeVal, nullptr);

    return (uint64_t)NUM1000000 * timeVal.tv_sec + timeVal.tv_usec;
}

static void AddLog(const char* logType, const char *tag, const char *func, const char *format, const va_list* ap)
{
    char* buf = (char*)malloc(NUM2048);
    if (buf == nullptr) {
        return;
    }
    int offset = sprintf_s(buf, (NUM2048), "[%s][%llu]%s %s: ", logType, (unsigned long long)GetTimeMs(), tag, func);

    offset += vsprintf_s(buf + offset, (NUM2048) - offset, format, *ap);

    free(buf);
    buf = nullptr;
}

static void Logi(const char *tag, const char *func, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    AddLog("Info", tag, func, format, &args);
    va_end(args);
}

static void Logw(const char *tag, const char *func, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    AddLog("Warn", tag, func, format, &args);
    va_end(args);
}

static void Loge(const char *tag, const char *func, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    AddLog("Error", tag, func, format, &args);
    va_end(args);
}

static void Logd(const char *tag, const char *func, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    AddLog("Debug", tag, func, format, &args);
    va_end(args);
}


static uint8_t g_hksHardwareUdidId[32] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0C, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1A, 0x1C, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
};

static int32_t HksTestGetHardwareUdid(uint8_t* udid, uint32_t udidLen)
{
    int err;
    if ((udid == NULL) || (udidLen != NUM32)) {
        return -1;
    }

    int32_t rc = 1234567;
    if (rc <= 0) {
        err = memcpy_s(udid, NUM32, g_hksHardwareUdidId, NUM32);
        if (err !=  EOK) {
            return -1;
        }
    }

    char buf[128] = {0};
    uint32_t offset = 0;
    for (uint32_t i = 0; i < udidLen; ++i) {
        offset += sprintf_s(buf + offset, NUM128 - offset, "%02x ", udid[i]);
    }

    Logd("[hks_tester]", __func__, buf);
    return 0;
}

static void HksStBlobInit1(struct hks_blob *blob, size_t nmemb, size_t size, uint8_t type)
{
    if (blob == nullptr || nmemb == 0 || size == 0) {
        EXPECT_EQ(0, 1);
        return;
    }
    blob->data = (uint8_t *)calloc(nmemb, size);
    if (blob->data == NULL) {
        EXPECT_EQ(0, 1);
        return;
    }
    if (memset_s(blob->data, size, 0, size) != EOK) {
        EXPECT_EQ(0, 1);
        return;
     }
    blob->size = size;
    blob->type = type;
}

static void HksBlobDestroyT1(struct hks_blob *blob)
{
    if (blob == nullptr) {
        EXPECT_EQ(0, 1);
        return;
    }
    if (blob && blob->data) {
        if (memset_s(blob->data, blob->size, 0, blob->size) != EOK) {
        EXPECT_EQ(0, 1);
        return;
        }
        HKS_FREE_PTR1(blob->data);
    }
    blob->data = NULL;
    blob->size = 0;
    blob->type = HKS_BLOB_TYPE_RAW;
}

static void HexStringToByte(const char *str, int nLen, unsigned char *pHex)
{
    unsigned int number = 4;
    if (nLen % NUM2) {
        EXPECT_EQ(0, 1);
        return;
    }
    int nHexLen = nLen / NUM2;
    unsigned char nibble[2];
    if (nHexLen < MAX_INT) {
        for (int i = 0; i < nHexLen; i++) {
            nibble[0] = str[i * NUM2];
            nibble[1] = str[i * NUM2 + NUM1];
            for (int j = 0; j < NUM2; j++) {
                if (nibble[j] <= 'F' && nibble[j] >= 'A') {
                    nibble[j] = nibble[j] - 'A' + NUM10;
                } else if (nibble[j] <= 'f' && nibble[j] >= 'a') {
                    nibble[j] = nibble[j] - 'a' + NUM10;
                } else if (nibble[j] >= '0' && nibble[j] <= '9') {
                    nibble[j] = nibble[j] - '0';
                } else {
                    EXPECT_EQ(0, 1);
                    return;
                }
            }
            pHex[i] = nibble[0] << number;
            pHex[i] |= nibble[1];
        }
    }
}

static void BuildBlobData(struct hks_blob *param, const char *str, uint8_t type, uint32_t size, uint8_t isDataNull)
{
    if (param == nullptr) {
        EXPECT_EQ(0, 1);
        return;
    }
    param->type = type;
    param->size = size;
    if (isDataNull == 1)
        param->data = NULL;
    else {
        if (size + NUM2 == 0) {
            EXPECT_EQ(0, 1);
            return;
        }
        unsigned char *buff = (unsigned char *)malloc(size + NUM2);
        if (buff == nullptr) {
            EXPECT_EQ(0, 1);
            return;
        }
        if (memset_s(buff, size + NUM2, 0, size + NUM2) != EOK) {
            EXPECT_EQ(0, 1);
            return;
        }
        HexStringToByte(str, size * NUM2, buff);
        param->data = (uint8_t *)buff;
    }
}

static void TestInitKeyParam1(struct hks_key_param *keyParam, uint32_t keyType, uint32_t keyLen, uint32_t keyMode,
    uint32_t keyUsage)
{
    keyParam->key_type = keyType;
    keyParam->key_len = keyLen;
    keyParam->key_pad = HKS_PADDING_NONE;
    keyParam->key_mode = keyMode;
    keyParam->key_domain = HKS_ECC_CURVE_ED25519;
    keyParam->key_usage = keyUsage;

    const char tmpData1[] = "111111";
    BuildBlobData(&keyParam->key_auth_id, tmpData1, HKS_BLOB_TYPE_AUTH_ID, NUM3, 0);
}

#endif
