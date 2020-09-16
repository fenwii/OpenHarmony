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

#include "parameter.h"
#include <securec.h>
#include "hal_sys_param.h"
#include "ohos_errno.h"
#include "param_adaptor.h"

#define FILE_RO "ro."
#define VERSION_ID_LEN 256

static char g_roBuildOs[] = {"OpenHarmony"};
static char g_roBuildVerShow[] = {"OpenHarmony 1.0"};
static char g_roSdkApiLevel[] = {"3"};
static char g_roFirstApiLevel[] = {"1"};

static boolean IsValidValue(const char* value, unsigned int len)
{
    if ((value == NULL) || !strlen(value) || (strlen(value) + 1 > len)) {
        return FALSE;
    }
    return TRUE;
}

int GetParameter(const char* key, const char* def, char* value, unsigned int len)
{
    if ((key == NULL) || (value == NULL)) {
        return EC_INVALID;
    }
    if (!CheckPermission()) {
        return EC_FAILURE;
    }
    int ret = GetSysParam(key, value, len);
    if (ret == EC_INVALID) {
        return EC_INVALID;
    }
    if ((ret < 0) && IsValidValue(def, len)) {
        if (strcpy_s(value, len, def) != 0) {
            return EC_FAILURE;
        }
        ret = strlen(def);
    }
    return ret;
}

int SetParameter(const char* key, const char* value)
{
    if ((key == NULL) || (value == NULL)) {
        return EC_INVALID;
    }
    if (!CheckPermission()) {
        return EC_FAILURE;
    }
    if (strncmp(key, FILE_RO, strlen(FILE_RO)) == 0) {
        return EC_INVALID;
    }
    int ret = SetSysParam(key, value);
    return ret;
}

char* GetProductType(void)
{
    return HalGetProductType();
}

char* GetManufacture(void)
{
    return HalGetManufacture();
}

char* GetBrand(void)
{
    return HalGetBrand();
}

char* GetMarketName(void)
{
    return HalGetMarketName();
}

char* GetProductSeries(void)
{
    return HalGetProductSeries();
}

char* GetProductModel(void)
{
    return HalGetProductModel();
}

char* GetSoftwareModel(void)
{
    return HalGetSoftwareModel();
}

char* GetHardwareModel(void)
{
    return HalGetHardwareModel();
}

char* GetHardwareProfile(void)
{
    return HalGetHardwareProfile();
}

char* GetSerial(void)
{
    return HalGetSerial();
}

char* GetBootloaderVersion(void)
{
    return HalGetBootloaderVersion();
}

char* GetSecurityPatchTag(void)
{
    return HalGetSecurityPatchTag();
}

char* GetAbiList(void)
{
    return HalGetAbiList();
}

char* GetOsName(void)
{
    char* value = (char*)malloc(strlen(g_roBuildOs) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(g_roBuildOs) + 1, g_roBuildOs) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetDisplayVersion(void)
{
    char* value = (char*)malloc(strlen(g_roBuildVerShow) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(g_roBuildVerShow) + 1, g_roBuildVerShow) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetSdkApiLevel(void)
{
    char* value = (char*)malloc(strlen(g_roSdkApiLevel) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(g_roSdkApiLevel) + 1, g_roSdkApiLevel) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetFirstApiLevel(void)
{
    char* value = (char*)malloc(strlen(g_roFirstApiLevel) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(g_roFirstApiLevel) + 1, g_roFirstApiLevel) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetIncrementalVersion(void)
{
    char* value = (char*)malloc(strlen(INCREMENTAL_VERSION) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(INCREMENTAL_VERSION) + 1, INCREMENTAL_VERSION) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetVersionId(void)
{
    char* value = (char*)malloc(VERSION_ID_LEN);
    if (value == NULL) {
        return NULL;
    }
    if (memset_s(value, VERSION_ID_LEN, 0, VERSION_ID_LEN) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    char* productType = GetProductType();
    char* manufacture = GetManufacture();
    char* brand = GetBrand();
    char* productSerial = GetProductSeries();
    char* productModel = GetProductModel();
    char* softwareModel = GetSoftwareModel();
    if (productType == NULL || manufacture == NULL || brand == NULL ||
        productSerial == NULL || productModel == NULL || softwareModel == NULL) {
        free(productType);
        free(manufacture);
        free(brand);
        free(productSerial);
        free(productModel);
        free(softwareModel);
        free(value);
        value = NULL;
        return NULL;
    }
    int len = sprintf_s(value, VERSION_ID_LEN, "%s/%s/%s/%s/%s/%s/%s/%s/%s/%s",
        productType, manufacture, brand, productSerial, g_roBuildOs, productModel,
        softwareModel, g_roSdkApiLevel, INCREMENTAL_VERSION, BUILD_TYPE);
    free(productType);
    free(manufacture);
    free(brand);
    free(productSerial);
    free(productModel);
    free(softwareModel);
    if (len < 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetBuildType(void)
{
    char* value = (char*)malloc(strlen(BUILD_TYPE) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(BUILD_TYPE) + 1, BUILD_TYPE) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetBuildUser(void)
{
    char* value = (char*)malloc(strlen(BUILD_USER) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(BUILD_USER) + 1, BUILD_USER) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetBuildHost(void)
{
    char* value = (char*)malloc(strlen(BUILD_HOST) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(BUILD_HOST) + 1, BUILD_HOST) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetBuildTime(void)
{
    char* value = (char*)malloc(strlen(BUILD_TIME) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(BUILD_TIME) + 1, BUILD_TIME) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}

char* GetBuildRootHash(void)
{
    char* value = (char*)malloc(strlen(BUILD_ROOTHASH) + 1);
    if (value == NULL) {
        return NULL;
    }
    if (strcpy_s(value, strlen(BUILD_ROOTHASH) + 1, BUILD_ROOTHASH) != 0) {
        free(value);
        value = NULL;
        return NULL;
    }
    return value;
}