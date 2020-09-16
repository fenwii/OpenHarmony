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
 * @defgroup los_bitmap Bitmap
 * @ingroup kernel
 */

#ifndef _LOS_BITMAP_H
#define _LOS_BITMAP_H

#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* Trick to get a 1 of the right size */
#define _ONE(x) (1 + ((x) - (x)))
#define BIT(n)  (1U << (n))
#define BIT_GET(x, bit) ((x) & (_ONE(x) << (bit)))
#define BIT_SHIFT(x, bit) (((x) >> (bit)) & 1)
#define BITS_GET(x, high, low) ((x) & (((_ONE(x) << ((high) + 1)) - 1) & ~((_ONE(x) << (low)) - 1)))
#define BITS_SHIFT(x, high, low) (((x) >> (low)) & ((_ONE(x) << ((high) - (low) + 1)) - 1))
#define BIT_SET(x, bit) (((x) & (_ONE(x) << (bit))) ? 1 : 0)
#define BITMAP_BITS_PER_WORD (sizeof(UINTPTR) * 8)
#define BITMAP_NUM_WORDS(x) (((x) + BITMAP_BITS_PER_WORD - 1) / BITMAP_BITS_PER_WORD)
#define BITMAP_WORD(x) ((x) / BITMAP_BITS_PER_WORD)
#define BITMAP_BIT_IN_WORD(x) ((x) & (BITMAP_BITS_PER_WORD - 1))
#define BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) % BITMAP_BITS_PER_WORD))
#define BITMAP_LAST_WORD_MASK(nbits) \
    (((nbits) % BITMAP_BITS_PER_WORD) ? (1UL << ((nbits) % BITMAP_BITS_PER_WORD)) - 1 : ~0UL)
#define BITMAP_BITS_PER_INT (sizeof(INTPTR) * 8)
#define BITMAP_BIT_IN_INT(x) ((x) & (BITMAP_BITS_PER_INT - 1))
#define BITMAP_INT(x) ((x) / BITMAP_BITS_PER_INT)
#define BIT_MASK(x) (((x) >= sizeof(UINTPTR) * 8) ? (0UL - 1) : ((1UL << (x)) - 1))

/**
 * @ingroup los_bitmap
 * Flag that indicates the invalid bit index.
 *
 * The effective bit index is from 0 to 31.
 */
#define LOS_INVALID_BIT_INDEX 32

/**
 * @ingroup los_bitmap
 * @brief Set one bit.
 *
 * @par Description:
 * This API is used to set one bit of variable according to the parameter.
 * @attention
 * <ul>
 * <li>When the value of pos is greater than 31, the bit (pos & 0x1f) of bitmap will be set.</li>
 * </ul>
 * @param bitmap   [IN] The bitmap variable pointer.
 * @param pos       [IN] The number bit to be set.
 *
 * @retval None
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_BitmapClr
 */
VOID LOS_BitmapSet(UINT32 *bitmap, UINT16 pos);

/**
 * @ingroup los_bitmap
 * @brief Clear one bit.
 *
 * @par Description:
 * This API is used to clear one bit of variable according to the parameter.
 * @attention
 * <ul>
 * <li>When the value of pos is greater than 31, the bit (pos & 0x1f) of bitmap will be clear.</li>
 * </ul>
 * @param bitmap   [IN] The bitmap variable pointer.
 * @param pos          [IN] The number bit to be cleared.
 *
 * @retval none.
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_BitmapSet.
 */
VOID LOS_BitmapClr(UINT32 *bitmap, UINT16 pos);

/**
 * @ingroup los_bitmap
 * @brief Find the lowest one bit that is set.
 *
 * @par Description:
 * This API is used to find the lowest one bit that is set and return the bit index.
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 * @param bitmap   [IN] The bitmap variable.
 *
 * @retval UINT16 The bit index of the lowest one bit that is set.
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HighBitGet
 */
UINT16 LOS_LowBitGet(UINT32 bitmap);

/**
 * @ingroup los_bitmap
 * @brief Find the highest one bit that is set.
 *
 * @par Description:
 * This API is used to find the highest one bit that is set and return the bit index.
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 * @param bitmap   [IN] The bitmap variable.
 *
 * @retval UINT16 The bit index of the highest one bit that is set.
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_LowBitGet
 */
UINT16 LOS_HighBitGet(UINT32 bitmap);

/**
 * @ingroup los_bitmap
 * @brief Find the first zero bit starting from LSB.
 *
 * @par Description:
 * This API is used to find the first zero bit starting from LSB and return the bit index.
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 * @param *bitmap   [IN] The bitmap pointer.
 *
 * @retval int The bit index of the first zero bit from LSB.
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_BitmapFfz
 */
int LOS_BitmapFfz(UINTPTR *bitmap, UINT32 numBits);

/**
 * @ingroup los_bitmap
 * @brief Set the number of bit to 1 from start.
 *
 * @par Description:
 * This API is used to set the number of bit to 1 from start.
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 * @param *bitmap   [IN] The bitmap pointer.
 * @param start     [IN] The start bit.
 * @param numsSet   [IN] The number of set bits
 *
 * @retval none.
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_BitmapSetNBits
 */
VOID LOS_BitmapSetNBits(UINTPTR *bitmap, UINT32 start, UINT32 numsSet);

/**
 * @ingroup los_bitmap
 * @brief Clear the number of bit to zero from start.
 *
 * @par Description:
 * This API is used to set the number of bit to zero from start.
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 * @param *bitmap   [IN] The bitmap pointer.
 * @param start     [IN] The start bit.
 * @param numsClear [IN] The number of clear bits
 *
 * @retval none.
 * @par Dependency:
 * <ul><li>los_bitmap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_BitmapClrNBits
 */
VOID LOS_BitmapClrNBits(UINTPTR *bitmap, UINT32 start, UINT32 numsClear);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_BITMAP_H */
