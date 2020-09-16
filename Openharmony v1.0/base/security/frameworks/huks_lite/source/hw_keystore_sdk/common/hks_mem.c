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

#if defined(_STD_LIB_SOUTH_) & defined(_HILINK_PRODUCT_)
#include "hks_mem.h"
#include "base/hilink_osadapter.h"
void *hks_south_calloc(size_t n, size_t size)
{
    if (n == 0 || size == 0)
        return NULL;
    if (n > (UINT32_MAX / size))
        return NULL;
    unsigned int len = (unsigned int)(n * size);

    void *data = HKS_MALLOC(len);

    if (data != NULL)
        (void)hilink_memset_s((char *)data, len, 0, len);
    return data;
}
#endif
