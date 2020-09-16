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

#ifndef __TEEC_COMPAT_H
#define __TEEC_COMPAT_H

#include <limits.h>

#define AID_SYSTEM 1000
#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#ifdef TEE_LITEOS_A
static inline void Barriers(void)
{
    __asm__ volatile("isb");
    __asm__ volatile("dsb sy");
}
#else
static inline void Barriers(void)
{
}
#endif

#endif
