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

#ifndef TEST_XTS_ACTS_SECURITY_LITE_DATAHUKS_HAL_SRC_SECURITY_DATA_HUKS_H
#define TEST_XTS_ACTS_SECURITY_LITE_DATAHUKS_HAL_SRC_SECURITY_DATA_HUKS_H

#include "hctest.h"
#include "hks_client.h"
#include "hks_types.h"
#include "securec.h"
#include <securec.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM1  1
#define NUM2  2
#define NUM3  3
#define NUM4  4
#define NUM5  5
#define NUM6  6
#define NUM10  10
#define NUM11  11
#define NUM12  12
#define NUM15  15
#define NUM16  16
#define NUM20  20
#define NUM21  21
#define NUM24  24
#define NUM25  25
#define NUM30  30
#define NUM31  31
#define NUM32  32
#define NUM33  33
#define NUM60  60
#define NUM63  63
#define NUM64  64
#define NUM65  65
#define NUM88  88
#define NUM100  100
#define NUM111  111
#define NUM128  128
#define NUM192  192
#define NUM256  256
#define NUM1025  1025
#define NUM134  (-134)
#define NUM135  (-135)
#define NUM138  (-138)
#define NUM142  (-142)
#define NUM1000  (-1000)
#define NUM1004  (-1004)
#define NUM1005  (-1005)
#define NUM1006  (-1006)
#define NUM1007  (-1007)
#define NUM1010  (-1010)
#define MAX_INT  2147483647
#define HKS_FREE_PTR1(p) { if ((p) != NULL) { free(p); (p) = NULL; }}

void HksStBlobInit1(struct hks_blob *blob, size_t nmemb, size_t size, uint8_t type);

void HksBlobDestroyT1(struct hks_blob *blob);

int TestSecShuksGenerateKeyNormal(void);

int TestSecShuksDeleteKeyNormal(void);

int TestSecShuksExportPublicNormal(struct hks_blob *keyAlias, struct hks_blob *publicKey1);

void BuildBlobData(struct hks_blob *param, const char *str, uint8_t type, uint32_t size, uint8_t isDataNull);

void HexStringToByte(const char *str, int nLen, unsigned char *pHex);

void TestInitKeyParam1(struct hks_key_param *keyParam, uint32_t keyType, uint32_t keyLen, uint32_t keyMode,
    uint32_t keyUsage);

int TestSecShuksImportPublicNormal(void);

#endif
