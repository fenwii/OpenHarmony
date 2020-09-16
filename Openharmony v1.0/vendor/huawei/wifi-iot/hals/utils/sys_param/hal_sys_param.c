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

#include "hal_sys_param.h"
#include <securec.h>

static const char OHOS_PRODUCT_TYPE[] = {"****"};
static const char OHOS_MANUFACTURE[] = {"****"};
static const char OHOS_BRAND[] = {"****"};
static const char OHOS_MARKET_NAME[] = {"****"};
static const char OHOS_PRODUCT_SERIES[] = {"****"};
static const char OHOS_PRODUCT_MODEL[] = {"****"};
static const char OHOS_SOFTWARE_MODEL[] = {"****"};
static const char OHOS_HARDWARE_MODEL[] = {"****"};
static const char OHOS_HARDWARE_PROFILE[] = {"aout:true,display:true"};
static const char OHOS_BOOTLOADER_VERSION[] = {"bootloader"};
static const char OHOS_SECURITY_PATCH_TAG[] = {"2020-09-01"};
static const char OHOS_ABI_LIST[] = {"****"};
static const char OHOS_SERIAL[] = {"1234567890"};  // provided by OEM.

char* HalGetProductType(void)
{
    char* value = (char*)malloc(strlen(OHOS_PRODUCT_TYPE) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_PRODUCT_TYPE) + 1, OHOS_PRODUCT_TYPE) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetManufacture(void)
{
    char* value = (char*)malloc(strlen(OHOS_MANUFACTURE) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_MANUFACTURE) + 1, OHOS_MANUFACTURE) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetBrand(void)
{
    char* value = (char*)malloc(strlen(OHOS_BRAND) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_BRAND) + 1, OHOS_BRAND) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetMarketName(void)
{
    char* value = (char*)malloc(strlen(OHOS_MARKET_NAME) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_MARKET_NAME) + 1, OHOS_MARKET_NAME) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetProductSeries(void)
{
    char* value = (char*)malloc(strlen(OHOS_PRODUCT_SERIES) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_PRODUCT_SERIES) + 1, OHOS_PRODUCT_SERIES) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetProductModel(void)
{
    char* value = (char*)malloc(strlen(OHOS_PRODUCT_MODEL) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_PRODUCT_MODEL) + 1, OHOS_PRODUCT_MODEL) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetSoftwareModel(void)
{
    char* value = (char*)malloc(strlen(OHOS_SOFTWARE_MODEL) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_SOFTWARE_MODEL) + 1, OHOS_SOFTWARE_MODEL) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetHardwareModel(void)
{
    char* value = (char*)malloc(strlen(OHOS_HARDWARE_MODEL) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_HARDWARE_MODEL) + 1, OHOS_HARDWARE_MODEL) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetHardwareProfile(void)
{
    char* value = (char*)malloc(strlen(OHOS_HARDWARE_PROFILE) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_HARDWARE_PROFILE) + 1, OHOS_HARDWARE_PROFILE) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetSerial(void)
{
    char* value = (char*)malloc(strlen(OHOS_SERIAL) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_SERIAL) + 1, OHOS_SERIAL) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetBootloaderVersion(void)
{
    char* value = (char*)malloc(strlen(OHOS_BOOTLOADER_VERSION) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_BOOTLOADER_VERSION) + 1, OHOS_BOOTLOADER_VERSION) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetSecurityPatchTag(void)
{
    char* value = (char*)malloc(strlen(OHOS_SECURITY_PATCH_TAG) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_SECURITY_PATCH_TAG) + 1, OHOS_SECURITY_PATCH_TAG) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

char* HalGetAbiList(void)
{
    char* value = (char*)malloc(strlen(OHOS_ABI_LIST) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(OHOS_ABI_LIST) + 1, OHOS_ABI_LIST) != 0) {
        free(value);
        return NULL;
    }
    return value;
}