/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hdf_cstring.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "hdf_log.h"
#include "osal_mem.h"
#include "securec.h"

uint32_t HdfStringMakeHashKey(const char *key, uint32_t mask)
{
    uint32_t hashValue = 0;
    const uint32_t seed = 131; // 31 131 1313 13131 131313 etc..
    while ((key != NULL) && *key) {
        hashValue = hashValue * seed + (*key++);
    }
    return (hashValue & 0x7FFFFFFF) | mask;
}

bool HdfStringToInt(const char *str, int *value)
{
    if (str == NULL || value == NULL) {
        return false;
    }

    char *end = NULL;
    errno = 0;
    const int base = 10;
    long result = strtol(str, &end, base);
    if (end == str || end[0] != '\0' || errno == ERANGE || result > INT_MAX || result < INT_MIN) {
        return false;
    }

    *value = (int)result;
    return true;
}

struct HdfCString *HdfCStringObtain(const char *str)
{
    struct HdfCString *instance = NULL;
    if (str != NULL) {
        size_t strLen = strlen(str);
        size_t size = sizeof(struct HdfCString) + strLen + 1;
        instance = (struct HdfCString *)OsalMemCalloc(size);
        if (instance == NULL) {
            HDF_LOGE("HdfCStringObtain failed, alloc memory failed");
            return NULL;
        }
        if (strncpy_s(instance->value, strLen + 1, str, strLen) != EOK) {
            HDF_LOGE("HdfCStringObtain failed, strncpy_s failed");
            OsalMemFree(instance);
            return NULL;
        }
        instance->size = strLen;
    }
    return instance;
}

void HdfCStringRecycle(struct HdfCString *inst)
{
    if (inst != NULL) {
        OsalMemFree(inst);
    }
}
