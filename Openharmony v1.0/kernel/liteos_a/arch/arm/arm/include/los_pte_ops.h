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
 * @defgroup los_pte_ops page table entry operations
 * @ingroup kernel
 */

#ifndef __LOS_PTE_OPS_H__
#define __LOS_PTE_OPS_H__

#include "los_typedef.h"
#include "arm.h"
#include "los_mmu_descriptor_v6.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC INLINE VOID OsSavePte1(PTE_T *pte1Ptr, PTE_T pte1)
{
    DMB;
    *pte1Ptr = pte1;
    DSB;
}

STATIC INLINE ADDR_T OsTruncPte1(ADDR_T addr)
{
    return MMU_DESCRIPTOR_L1_SECTION_ADDR(addr);
}

STATIC INLINE UINT32 OsGetPte1Index(vaddr_t va)
{
    return va >> MMU_DESCRIPTOR_L1_SMALL_SHIFT;
}

STATIC INLINE VOID OsClearPte1(PTE_T *pte1Ptr)
{
    OsSavePte1(pte1Ptr, 0);
}

STATIC INLINE PTE_T *OsGetPte1Ptr(PTE_T *pte1BasePtr, vaddr_t va)
{
    return (pte1BasePtr + OsGetPte1Index(va));
}

STATIC INLINE PTE_T OsGetPte1(PTE_T *pte1BasePtr, vaddr_t va)
{
    return *OsGetPte1Ptr(pte1BasePtr, va);
}

STATIC INLINE BOOL OsIsPte1PageTable(PTE_T pte1)
{
    return (pte1 & MMU_DESCRIPTOR_L1_TYPE_MASK) == MMU_DESCRIPTOR_L1_TYPE_PAGE_TABLE;
}

STATIC INLINE BOOL OsIsPte1Invalid(PTE_T pte1)
{
    return (pte1 & MMU_DESCRIPTOR_L1_TYPE_MASK) == MMU_DESCRIPTOR_L1_TYPE_INVALID;
}

STATIC INLINE BOOL OsIsPte1Section(PTE_T pte1)
{
    return (pte1 & MMU_DESCRIPTOR_L1_TYPE_MASK) == MMU_DESCRIPTOR_L1_TYPE_SECTION;
}

STATIC INLINE UINT32 OsGetPte2Index(vaddr_t va)
{
    return (va % MMU_DESCRIPTOR_L1_SMALL_SIZE) >> MMU_DESCRIPTOR_L2_SMALL_SHIFT;
}

STATIC INLINE PTE_T *OsGetPte2Ptr(PTE_T *pte2BasePtr, vaddr_t va)
{
    return (pte2BasePtr + OsGetPte2Index(va));
}

STATIC INLINE PTE_T OsGetPte2(PTE_T *pte2BasePtr, vaddr_t va)
{
    return *(pte2BasePtr + OsGetPte2Index(va));
}

STATIC INLINE VOID OsSavePte2(PTE_T *pte2Ptr, PTE_T pte2)
{
    DMB;
    *pte2Ptr = pte2;
    DSB;
}

STATIC INLINE UINT32 OsSavePte2Continuous(PTE_T *pte2BasePtr, UINT32 index, PTE_T pte2, UINT32 count)
{
    UINT32 saveCounts = 0;
    if (count == 0) {
        return 0;
    }

    DMB;
    do {
        pte2BasePtr[index++] = pte2;
        count--;
        pte2 += MMU_DESCRIPTOR_L2_SMALL_SIZE;
        saveCounts++;
    } while ((count != 0) && (index != MMU_DESCRIPTOR_L2_NUMBERS_PER_L1));
    DSB;

    return saveCounts;
}

STATIC INLINE VOID OsClearPte2Continuous(PTE_T *pte2Ptr, UINT32 count)
{
    UINT32 index = 0;

    DMB;
    while (count > 0) {
        pte2Ptr[index++] = 0;
        count--;
    }
    DSB;
}

STATIC INLINE BOOL OsIsPte2SmallPage(PTE_T pte2)
{
    return (pte2 & MMU_DESCRIPTOR_L2_TYPE_MASK) == MMU_DESCRIPTOR_L2_TYPE_SMALL_PAGE;
}

STATIC INLINE BOOL OsIsPte2SmallPageXN(PTE_T pte2)
{
    return (pte2 & MMU_DESCRIPTOR_L2_TYPE_MASK) == MMU_DESCRIPTOR_L2_TYPE_SMALL_PAGE_XN;
}

STATIC INLINE BOOL OsIsPte2LargePage(PTE_T pte2)
{
    return (pte2 & MMU_DESCRIPTOR_L2_TYPE_MASK) == MMU_DESCRIPTOR_L2_TYPE_LARGE_PAGE;
}

STATIC INLINE BOOL OsIsPte2Invalid(PTE_T pte2)
{
    return (pte2 & MMU_DESCRIPTOR_L2_TYPE_MASK) == MMU_DESCRIPTOR_L2_TYPE_INVALID;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LOS_PTE_OPS_H__ */
