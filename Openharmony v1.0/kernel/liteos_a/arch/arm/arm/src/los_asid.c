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
 * @defgroup los_asid mmu address space id
 * @ingroup kernel
 */

#include "los_typedef.h"
#include "los_asid.h"
#include "los_spinlock.h"
#include "los_mmu_descriptor_v6.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC SPIN_LOCK_INIT(g_cpuAsidLock);
STATIC UINTPTR g_asidPool[BITMAP_NUM_WORDS(1UL << MMU_ARM_ASID_BITS)];

/* allocate and free asid */
status_t OsAllocAsid(UINT32 *asid)
{
    UINT32 flags;
    LOS_SpinLockSave(&g_cpuAsidLock, &flags);
    UINT32 firstZeroBit = LOS_BitmapFfz(g_asidPool, 1UL << MMU_ARM_ASID_BITS);
    if (firstZeroBit >= 0 && firstZeroBit < (1UL << MMU_ARM_ASID_BITS)) {
        LOS_BitmapSetNBits(g_asidPool, firstZeroBit, 1);
        *asid = firstZeroBit;
        LOS_SpinUnlockRestore(&g_cpuAsidLock, flags);
        return LOS_OK;
    }

    LOS_SpinUnlockRestore(&g_cpuAsidLock, flags);
    return firstZeroBit;
}

VOID OsFreeAsid(UINT32 asid)
{
    UINT32 flags;
    LOS_SpinLockSave(&g_cpuAsidLock, &flags);
    LOS_BitmapClrNBits(g_asidPool, asid, 1);
    LOS_SpinUnlockRestore(&g_cpuAsidLock, flags);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
