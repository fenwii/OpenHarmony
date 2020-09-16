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

#include "osal_mem.h"
#include <stdlib.h>
#include <string.h>
#include "securec.h"
#include "hdf_log.h"

#define HDF_LOG_TAG osal_mem

void *OsalMemAlloc(size_t size)
{
    void *buf = NULL;

    if (size == 0) {
        HDF_LOGE("%s invalid param", __func__);
        return NULL;
    }

    buf = malloc(size);

    return buf;
}

void *OsalMemCalloc(size_t size)
{
    void *buf = NULL;

    if (size == 0) {
        HDF_LOGE("%s invalid param", __func__);
        return NULL;
    }

    buf = OsalMemAlloc(size);
    if (buf != NULL) {
        (void)memset_s(buf, size, 0, size);
    }

    return buf;
}

void OsalMemFree(void *mem)
{
    if (mem != NULL) {
        free(mem);
    }
}

