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

#ifndef OHOS_ACELITE_ACE_MEM_BASE_H
#define OHOS_ACELITE_ACE_MEM_BASE_H

#include <cstddef>

namespace OHOS {
namespace ACELite {
/**
 * @brief Allocate the required memory space and return a pointer to it
 *
 * @param [in] size: size of memory block,in bytes
 *
 * @return a pointer to the allocated memory block.if the request fails,return NULL
 */
void *ace_malloc(size_t size);

/**
 * @brief Allocate the required memory space and return a pointer to it
 *
 * @param [in] num: number of elements to be allocated
 * @param [in] size: size of memory block,in bytes
 *
 * @return a pointer to the allocated memory block.if the request fails,return NULL
 */
void *ace_calloc(size_t num, size_t size);

/**
 * @brief Free the memory space allocated by malloc(),calloc() or realloc()
 *
 * @param [in] ptr: pointer points to a memory block to be freed
 */
void ace_free(void *ptr);
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_ACE_MEM_BASE_H
