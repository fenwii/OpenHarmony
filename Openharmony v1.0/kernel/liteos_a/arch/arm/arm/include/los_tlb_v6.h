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
 * @defgroup los_tlb_v6 MMU TLB v6
 * @ingroup kernel
 */
#ifndef __LOS_TLB_V6_H__
#define __LOS_TLB_V6_H__

#include "los_typedef.h"
#include "menuconfig.h"
#include "arm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC INLINE VOID OsArmInvalidateTlbBarrier(VOID)
{
#ifdef LOSCFG_KERNEL_SMP
    OsArmWriteBpiallis(0);
#else
    OsArmWriteBpiall(0);
#endif
    DSB;
    ISB;
}

STATIC INLINE VOID OsArmInvalidateTlbMvaNoBarrier(VADDR_T va)
{
#ifdef LOSCFG_KERNEL_SMP
    OsArmWriteTlbimvaais(va & 0xfffff000);
#else
    OsArmWriteTlbimvaa(va & 0xfffff000);
#endif
}

STATIC INLINE VOID OsArmInvalidateTlbMvaRangeNoBarrier(VADDR_T start, UINT32 count)
{
    UINT32 index = 0;

    while (count > 0) {
        OsArmInvalidateTlbMvaNoBarrier(start + (index << MMU_DESCRIPTOR_L2_SMALL_SHIFT));
        index++;
        count--;
    }
}

STATIC INLINE VOID OsCleanTLB(VOID)
{
    UINT32 val = 0;
    __asm volatile("mcr    p15, 0, %0, c8, c7, 0" : : "r"(val));
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LOS_TLB_V6_H__ */

