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

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Defines the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module harmonizes OS interface differences and provides unified OS interfaces externally,
 * including the memory management, thread, mutex, spinlock, semaphore, timer, file, interrupt, time,
 * atomic, firmware, and I/O operation modules.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file osal_mem.h
 *
 * @brief Declares the driver memory request and release interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OSAL_MEM_H
#define OSAL_MEM_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Allocates memory of a specified size.
 *
 * @param size Indicates the size of memory to allocate.
 *
 * @return Returns the pointer to the allocated memory if the operation is successful; returns <b>NULL</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
void *OsalMemAlloc(size_t size);

/**
 * @brief Allocates memory of a specified size, and clears the allocated memory.
 *
 * @param size Indicates the size of memory to allocate.
 *
 * @return Returns the pointer to the allocated memory if the operation is successful; returns <b>NULL</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
void *OsalMemCalloc(size_t size);

/**
 * @brief Allocates memory of a specified size, and aligns the memory address on a given boundary.
 *
 * @param alignment Indicates the memory boundary alignment. The value must be a power of 2.
 * @param size Indicates the size of memory to allocate.
 *
 * @return Returns the pointer to the allocated memory if the operation is successful; returns <b>NULL</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
void *OsalMemAllocAlign(size_t alignment, size_t size);

/**
 * @brief Releases memory.
 *
 * @param mem Indicates the pointer to the memory to release.
 * @since 1.0
 * @version 1.0
 */
void OsalMemFree(void *mem);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_MEM_H */
/** @} */
