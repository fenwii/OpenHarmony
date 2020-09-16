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

#ifndef HKS_MEM_H
#define HKS_MEM_H

#include <stdint.h>
#include <stdlib.h>

#if defined(_STD_LIB_SOUTH_) & defined(_HILINK_PRODUCT_)
#include "base/hilink_osadapter.h"
void *hks_south_calloc(size_t count, size_t size);
#define HKS_MALLOC  hilink_malloc
#define HKS_FREE    hilink_free
#define HKS_CALLOC  hks_south_calloc
#else
/* redefine calloc & free, replace it for hilink */
#define HKS_MALLOC  malloc
#define HKS_CALLOC  calloc
#define HKS_FREE    free
#endif

#define hks_free_ptr(p) { if ((p) != NULL) { HKS_FREE(p); (p) = NULL; }}

#endif /* HKS_MEM_H */
