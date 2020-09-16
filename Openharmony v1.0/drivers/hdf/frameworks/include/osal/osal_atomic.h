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
 * @file osal_atomic.h
 *
 * @brief Declares atomic and bit operation interfaces.
 *
 * This file provides interfaces such as reading and setting an atomic,
 * incrementing and decrementing an atomic counter by 1.
 * This file also provides interfaces such as checking the bit status of a variable,
 * and setting and clearing the bit value of a variable.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OSAL_ATOMIC_H
#define OSAL_ATOMIC_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Describes an atomic.
 */
typedef struct {
    volatile int32_t counter;/**< Counter (an atomic variable).
                               * An operation on the atomic is to operate this variable.
                               */
} OsalAtomic;

/**
 * @brief Reads the counter of an atomic.
 *
 * @param v Indicates the pointer to the atomic {@link OsalAtomic}.
 *
 * @return Returns the counter.
 * @since 1.0
 * @version 1.0
 */
int32_t OsalAtomicRead(const OsalAtomic *v);

/**
 * @brief Sets the counter for an atomic.
 *
 * @param v Indicates the pointer to the atomic {@link OsalAtomic}.
 * @param counter Indicates the counter to set.
 *
 * @since 1.0
 * @version 1.0
 */
void OsalAtomicSet(OsalAtomic *v, int32_t counter);

/**
 * @brief Increments the counter of an atomic by 1.
 *
 * @param v Indicates the pointer to the atomic {@link OsalAtomic}.
 *
 * @since 1.0
 * @version 1.0
 */
void OsalAtomicInc(OsalAtomic *v);

/**
 * @brief Decrements the counter of an atomic by 1.
 *
 * @param v Indicates the pointer to the atomic {@link OsalAtomic}.
 *
 * @since 1.0
 * @version 1.0
 */
void OsalAtomicDec(OsalAtomic *v);

/**
 * @brief Tests the value of a specified bit of a variable.
 *
 * @param nr Indicates the bit of the variable. The value ranges from <b>0</b> to <b>31</b>.
 * @param addr Indicates the pointer to the variable.
 *
 * @return Returns the bit value.
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTestBit(unsigned long nr, const volatile unsigned long *addr);

/**
 * @brief Sets the value of a specified bit of the variable and returns the bit value before the setting.
 *
 * @param nr Indicates the bit of the variable. The value ranges from <b>0</b> to <b>31</b>.
 * @param addr Indicates the pointer to the variable.
 *
 * @return Returns the bit value before the setting.
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTestSetBit(unsigned long nr, volatile unsigned long *addr);

/**
 * @brief Clears the value of a specified bit of the variable and returns the bit value before clearing.
 *
 * @param nr Indicates the bit of the variable. The value ranges from <b>0</b> to <b>31</b>.
 * @param addr Indicates the pointer to the variable.
 *
 * @return Returns the bit value before the bit is cleared.
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTestClearBit(unsigned long nr, volatile unsigned long *addr);

/**
 * @brief Clears the value of a specified bit of the variable.
 *
 * @param nr Indicates the bit of the variable. The value ranges from <b>0</b> to <b>31</b>.
 * @param addr Indicates the pointer to the variable.
 *
 * @since 1.0
 * @version 1.0
 */
void OsalClearBit(unsigned long nr, volatile unsigned long *addr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_ATOMIC_H */
/** @} */
