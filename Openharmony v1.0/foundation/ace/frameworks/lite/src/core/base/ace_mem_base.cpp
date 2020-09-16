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
#include "ace_mem_base.h"

#include <cstdio>
#include "acelite_config.h"

#if defined(FEATURE_ACELITE_MC_MEMORY_POOL) && defined(FEATURE_ACELITE_MEMORY_POOL)
#error Only one marco can be defined
#elif defined(FEATURE_ACELITE_MC_MEMORY_POOL) && (defined(_WIN32) || defined(_WIN64))
#error Only one marco can be defined
#elif defined(FEATURE_ACELITE_PRODUCT_MEMORY_POOL) && (defined(_WIN32) || defined(_WIN64))
#error Only one macro can be defined
#elif defined(FEATURE_ACELITE_MEMORY_POOL) && (defined(_WIN32) || defined(_WIN64))
#error Only one macro can be defined
#endif

#if defined(FEATURE_ACELITE_MC_MEMORY_POOL)
#include "mc_memory.h"
#elif defined(FEATURE_ACELITE_PRODUCT_MEMORY_POOL)
#include "mem_pool.h"
#elif defined(FEATURE_ACELITE_MEMORY_POOL)
#include "hos_errno.h"
#include "hos_memory.h"
#elif (defined(_WIN32) || defined(_WIN64))
#include <stdlib.h>
#elif (defined(__LINUX__) || defined(__LITEOS__))
#include <stdlib.h>
#else
#error One macro must be defined
#endif

namespace OHOS {
namespace ACELite {
void* ace_malloc(size_t size)
{
#if defined(FEATURE_ACELITE_MC_MEMORY_POOL)
    return MC_UI_MEM_ALLOC(size);
#elif defined(FEATURE_ACELITE_PRODUCT_MEMORY_POOL)
    return MemPool::GetInstance()->Malloc(size);
#elif defined(FEATURE_ACELITE_MEMORY_POOL)
    return HOS_MemAlloc(0, size);
#elif (defined(_WIN32) || defined(_WIN64))
    return malloc(size);
#elif (defined(__LINUX__) || defined(__LITEOS__))
    return malloc(size);
#else
    #error One macro must be defined
#endif
}

void* ace_calloc(size_t num, size_t size)
{
#if (defined(_WIN32) || defined(_WIN64))
    return calloc(num, size);
#else
    return nullptr;
#endif
}

void ace_free(void* ptr)
{
#if defined(FEATURE_ACELITE_MC_MEMORY_POOL)
    MC_UI_MEM_FREE(ptr);
#elif defined(FEATURE_ACELITE_PRODUCT_MEMORY_POOL)
    MemPool::GetInstance()->Free(ptr);
#elif defined(FEATURE_ACELITE_MEMORY_POOL)
    HOS_MemFree(0, ptr);
#elif (defined(_WIN32) || defined(_WIN64))
    free(ptr);
#elif (defined(__LINUX__) || defined(__LITEOS__))
    free(ptr);
#else
    #error One macro must be defined
#endif
}
} // namespace ACELite
} // namespace OHOS
