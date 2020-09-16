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

#include "app_common.h"
#include <stdlib.h>

long long HapGetInt64(const unsigned char *buf, int len)
{
    if (buf == NULL) {
        return 0;
    }
    unsigned long long value = 0;
    if (len != sizeof(long long)) {
        return 0;
    }
    while (len-- > 0) {
        value = (value << BYTE_BITS) | (*(buf + len));
    }
    return (long long)value;
}

int HapGetInt(const unsigned char *buf, int len)
{
    if (buf == NULL) {
        return 0;
    }
    unsigned int value = 0;
    if (len != sizeof(int)) {
        return 0;
    }
    while (len-- > 0) {
        value = (value << BYTE_BITS) | (*(buf + len));
    }
    return (int)value;
}

short HapGetShort(const unsigned char *buf, int len)
{
    if (buf == NULL) {
        return 0;
    }
    unsigned short value = 0;
    if (len != sizeof(short)) {
        return 0;
    }
    while (len-- > 0) {
        value = (value << BYTE_BITS) | (*(buf + len));
    }
    return (short)value;
}

void HapPutInt32(unsigned char *buf, int len, int value)
{
    if (buf == NULL || len < sizeof(int)) {
        return;
    }
    int i;
    unsigned int var = value;
    for (i = 0; i < sizeof(int); i++) {
        buf[i] = var;
        var = var >> (BYTE_BITS);
    }
    return;
}
