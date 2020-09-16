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
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "hal_token.h"
#include "init_perms.h"
#include "log.h"
#include "ohos_errno.h"

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

static int UidVerify(void)
{
    uid_t uid;

    uid = getuid();
    if (uid != DEFAULT_UID_KIT_FRAMEWORK) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "uid verify failed, get uid:%d", uid);
        return EC_FAILURE;
    }

    return EC_SUCCESS;
}

int ReadToken(char *token, unsigned int len)
{
    int ret;

    if (token == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "token is nullptr");
        return EC_FAILURE;
    }

    if (UidVerify()) {
        return EC_FAILURE;
    }

    pthread_mutex_lock(&g_mutex);
    ret = HalReadToken(token, len);
    pthread_mutex_unlock(&g_mutex);

    return ret;
}

int WriteToken(const char *token, unsigned int len)
{
    int ret;

    if (token == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "token is nullptr");
        return EC_FAILURE;
    }

    if (UidVerify()) {
        return EC_FAILURE;
    }

    pthread_mutex_lock(&g_mutex);
    ret = HalWriteToken(token, len);
    pthread_mutex_unlock(&g_mutex);

    return ret;
}

int GetAcKey(char *acKey, unsigned int len)
{
    if (acKey == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "acKey is nullptr");
        return EC_FAILURE;
    }

    if (UidVerify()) {
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