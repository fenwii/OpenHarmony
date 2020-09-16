/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description : los atomic.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
 * ---------------------------------------------------------------------------- */

/**
 * @defgroup los_atomic Atomic
 * @ingroup kernel
 */

#ifndef _LOS_ATOMIC_H
#define _LOS_ATOMIC_H

#include "los_hwi.h"
#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
* @ingroup  los_atomic
* @brief Atomic addition.
*
* @par Description:
* This API is used to implement the atomic addition and return the result value of the augend.
* @attention
* <ul>
* <li>The pointer val must not be NULL.</li>
* <li>If the addtion result is not in the range of representable values for 32-bit signed integer,
* an int integer overflow may occur to the return value</li>
* </ul>
*
* @param  val      [IN] The augend pointer.
* @param  addVal   [IN] The addend.
*
* @retval #INT32  The result value of the augend.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline INT32 LOS_AtomicAdd(volatile INT32 *val, INT32 addVal)
{
    INT32 tmp;
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    tmp = *val;
    tmp += addVal;
    *val = tmp;
    LOS_IntRestore(intStatus);
    return tmp;
}

/**
* @ingroup  los_atomic
* @brief Atomic subtraction.
*
* @par Description:
* This API is used to implement the atomic subtraction and return the result value of the minuend.
* @attention
* <ul>
* <li>The pointer val must not be NULL.</li>
* <li>If the subtraction result is not in the range of representable values for 32-bit signed integer,
* an int integer overflow may occur to the return value</li>
* </ul>
*
* @param  val       [IN] The minuend pointer.
* @param  addVal    [IN] The subtrahend.
*
* @retval #INT32  The result value of the minuend.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline INT32 LOS_AtomicSub(volatile INT32 *val, INT32 addVal)
{
    INT32 tmp;
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    tmp = *val;
    tmp -= addVal;
    *val = tmp;
    LOS_IntRestore(intStatus);
    return tmp;
}
/**
* @ingroup  los_atomic
* @brief Atomic addSelf.
*
* @par Description:
* This API is used to implement the atomic addSelf .
* @attention
* <ul>
* <li>The pointer addr must not be NULL.</li>
* <li>The value which addr point to must not be INT_MAX to avoid integer overflow after adding 1.</li>
* </ul>
*
* @param  addr      [IN] The addSelf variable pointer.
*
* @retval none.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline VOID LOS_AtomicInc(volatile INT32 *addr)
{
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    (*addr)++;
    LOS_IntRestore(intStatus);
}

/**
* @ingroup  los_atomic
* @brief Atomic addSelf.
*
* @par Description:
* This API is used to implement the atomic addSelf and return the result of addSelf.
* @attention
* <ul>
* <li>The pointer addr must not be NULL.</li>
* <li>The value which pswAddr point to must not be INT_MAX to avoid integer overflow after adding 1.</li>
* </ul>
*
* @param  addr      [IN] The addSelf variable pointer.
*
* @retval #INT32 The return value of variable addSelf.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline INT32 LOS_AtomicIncRet(volatile INT32 *addr)
{
    INT32 tmp;
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    tmp = *addr;
    tmp++;
    *addr = tmp;
    LOS_IntRestore(intStatus);
    return tmp;
}

/**
* @ingroup  los_atomic
* @brief Atomic auto-decrement.
*
* @par Description:
* This API is used to implementating the atomic auto-decrement.
* @attention
* <ul>
* <li>The pointer addr must not be NULL.</li>
* <li>The value which pswAddr point to must not be INT_MIN to avoid overflow after reducing 1.</li>
* </ul>
*
* @param  addr      [IN] The auto-decrement variable pointer.
*
* @retval none.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline VOID LOS_AtomicDec(volatile INT32 *addr)
{
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    (*addr)--;
    LOS_IntRestore(intStatus);
}

/**
* @ingroup  los_atomic
* @brief Atomic auto-decrement.
*
* @par Description:
* This API is used to implementating the atomic auto-decrement and return the result of auto-decrement.
* @attention
* <ul>
* <li>The pointer addr must not be NULL.</li>
* <li>The value which pswAddr point to must not be INT_MIN to avoid overflow after reducing 1.</li>
* </ul>
*
* @param  addr      [IN] The addSelf variable pointer.
*
* @retval #INT32  The return value of variable auto-decrement.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline INT32 LOS_AtomicDecRet(volatile INT32 *addr)
{
    INT32 tmp;
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    tmp = *addr;
    tmp--;
    *addr = tmp;
    LOS_IntRestore(intStatus);
    return tmp;
}

/**
* @ingroup  los_atomic
* @brief Atomic exchange for 32-bit variable.
*
* @par Description:
* This API is used to implement the atomic exchange for 32-bit variable and return the previous value of
* the atomic variable.
* @attention
* <ul>The pointer addr must not be NULL.</ul>
*
* @param  addr       [IN] The variable pointer.
* @param  value      [IN] The exchange value.
*
* @retval #INT32       The previous value of the atomic variable
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline INT32 LOS_AtomicXchg32bits(volatile INT32 *addr, INT32 value)
{
    INT32 prevVal;
    UINT32 intStatus;
    intStatus = LOS_IntLock();
    prevVal = *addr;
    *addr = value;
    LOS_IntRestore(intStatus);
    return prevVal;
}

/**
* @ingroup  los_atomic
* @brief Atomic exchange for 32-bit variable with compare.
*
* @par Description:
* This API is used to implement the atomic exchange for 32-bit variable, if the value of variable is equal to swOldVal.
* @attention
* <ul>The pointer addr must not be NULL.</ul>
*
* @param  addr        [IN] The variable pointer.
* @param  newVal      [IN] The new value.
* @param  oldVal      [IN] The old value.
*
* @retval TRUE  The previous value of the atomic variable is not equal to swOldVal.
* @retval FALSE The previous value of the atomic variable is equal to swOldVal.
* @par Dependency:
* <ul><li>los_atomic.h: the header file that contains the API declaration.</li></ul>
* @see
*/
static inline BOOL LOS_AtomicCmpXchg32bits(volatile INT32 *addr, INT32 newVal, INT32 oldVal)
{
    INT32 prevVal;
    UINT32 intStatus = LOS_IntLock();
    prevVal = *addr;
    if (*addr == oldVal) {
        *addr = newVal;
    }
    LOS_IntRestore(intStatus);
    return (prevVal != oldVal);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_ATOMIC_H */
