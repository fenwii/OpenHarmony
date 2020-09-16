/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "token.h"
#include "hal_token.h"
#include "log.h"
#include "ohos_errno.h"

int ReadToken(char *token, unsigned int len)
{
    if (token == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "token is nullptr\n");
        return EC_FAILURE;
    }
    int ret = HalReadToken(token, len);
    return ret;
}

int WriteToken(const char *token, unsigned int len)
{
    if (token == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "token is nullptr\n");
        return EC_FAILURE;
    }
    int ret = HalWriteToken(token, len);
    return ret;
}

int GetAcKey(char *acKey, unsigned int len)
{
    if (acKey == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "acKey is nullptr");
        return EC_FAILURE;
    }

    return HalGetAcKey(acKey, len);
}

int GetProdId(char productId[], size_t len)
{
    if (productId == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "productId is nullptr");
        return EC_FAILURE;
    }

    return HalGetProdId(productId, len);
}