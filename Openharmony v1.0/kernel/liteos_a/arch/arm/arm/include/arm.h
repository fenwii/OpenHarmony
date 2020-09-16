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


#ifndef __LOS_ARM_H__
#define __LOS_ARM_H__

#define CPSR_MODE_USR  0x10
#define CPSR_MODE_MASK 0x1f

#define DSB __asm__ volatile("dsb" ::: "memory")
#define ISB __asm__ volatile("isb" ::: "memory")
#define DMB __asm__ volatile("dmb" ::: "memory")

STATIC INLINE UINT32 OsArmReadSctlr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c1,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteSctlr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c1,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadActlr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c1,c0,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteActlr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c1,c0,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadCpacr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c1,c0,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteCpacr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c1,c0,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTtbr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c2,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTtbr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c2,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTtbr0(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c2,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTtbr0(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c2,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTtbr1(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c2,c0,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTtbr1(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c2,c0,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTtbcr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c2,c0,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTtbcr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c2,c0,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDacr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c3,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDacr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c3,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDfsr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c5,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDfsr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c5,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadIfsr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c5,c0,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteIfsr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c5,c0,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDfar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c6,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDfar(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c6,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadWfar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c6,c0,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteWfar(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c6,c0,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadIfar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c6,c0,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteIfar(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c6,c0,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadFcseidr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c13,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteFcseidr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c13,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadContextidr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c13,c0,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteContextidr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c13,c0,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTpidrurw(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c13,c0,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTpidrurw(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c13,c0,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTpidruro(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c13,c0,3" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTpidruro(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c13,c0,3" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTpidrprw(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c13,c0,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTpidrprw(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c13,c0,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadMidr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c0,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteMidr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c0,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadMpidr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c0,c0,5" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteMpidr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c0,c0,5" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadVbar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c12,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteVbar(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c12,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadCbar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 4, %0, c15,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteCbar(UINT32 val)
{
    __asm__ volatile("mcr p15, 4, %0, c15,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts1cpr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts1cpr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts1cpw(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts1cpw(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts1cur(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts1cur(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts1cuw(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,3" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts1cuw(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,3" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts12nsopr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts12nsopr(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts12nsopw(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,5" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts12nsopw(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,5" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts12nsour(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts12nsour(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadAts12nsouw(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c8,7" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteAts12nsouw(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c8,7" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadPar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c4,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWritePar(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c4,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadBpiall(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c5,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteBpiall(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c5,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadBpimva(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c5,7" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteBpimva(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c5,7" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadBpiallis(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c7,c1,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteBpiallis(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c7,c1,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbiallis(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c3,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbiallis(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c3,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbimvais(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c3,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbimvais(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c3,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbiasidis(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c3,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbiasidis(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c3,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbimvaais(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c3,3" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbimvaais(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c3,3" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadItlbiall(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c5,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteItlbiall(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c5,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadItlbimva(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c5,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteItlbimva(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c5,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadItlbiasid(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c5,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteItlbiasid(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c5,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDtlbiall(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c6,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDtlbiall(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c6,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDtlbimva(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c6,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDtlbimva(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c6,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDtlbiasid(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c6,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDtlbiasid(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c6,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbiall(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c7,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbiall(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c7,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbimva(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c7,1" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbimva(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c7,1" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbiasid(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c7,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbiasid(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c7,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadTlbimvaa(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 0, %0, c8,c7,3" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteTlbimvaa(UINT32 val)
{
    __asm__ volatile("mcr p15, 0, %0, c8,c7,3" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadL2ctlr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 1, %0, c9,c0,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteL2ctlr(UINT32 val)
{
    __asm__ volatile("mcr p15, 1, %0, c9,c0,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadL2ectlr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p15, 1, %0, c9,c0,3" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteL2ectlr(UINT32 val)
{
    __asm__ volatile("mcr p15, 1, %0, c9,c0,3" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbddidr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbddidr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdrar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c1,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdrar(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c1,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdsar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c2,c0,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdsar(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c2,c0,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdscr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c1,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdscr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c1,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdtrtxint(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c5,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdtrtxint(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c5,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdtrrxint(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c5,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdtrrxint(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c5,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgwfar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c6,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgwfar(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c6,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgvcr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c7,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgvcr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c7,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgecr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c9,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgecr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c9,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdsccr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c10,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdsccr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c10,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdsmcr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c11,0" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdsmcr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c11,0" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdtrrxext(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c0,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdtrrxext(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c0,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdscrext(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c2,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdscrext(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c2,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdtrtxext(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c3,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdtrtxext(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c3,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdrcr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c4,2" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdrcr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c4,2" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgvr0(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c0,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgvr0(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c0,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgvr1(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c1,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgvr1(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c1,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgvr2(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c2,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgvr2(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c2,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgbcr0(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c0,5" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgbcr0(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c0,5" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgbcr1(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c1,5" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgbcr1(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c1,5" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgbcr2(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c2,5" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgbcr2(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c2,5" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgwvr0(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c0,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgwvr0(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c0,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgwvr1(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c1,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgwvr1(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c1,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgwcr0(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c0,7" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgwcr0(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c0,7" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgwcr1(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c0,c1,7" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgwcr1(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c0,c1,7" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgoslar(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c1,c0,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgoslar(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c1,c0,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgoslsr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c1,c1,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgoslsr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c1,c1,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgossrr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c1,c2,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgossrr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c1,c2,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgprcr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c1,c4,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgprcr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c1,c4,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgprsr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c1,c5,4" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgprsr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c1,c5,4" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgclaimset(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c7,c8,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgclaimset(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c7,c8,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgclaimclr(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c7,c9,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgclaimclr(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c7,c9,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgauthstatus(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c7,c14,6" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgauthstatus(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c7,c14,6" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

STATIC INLINE UINT32 OsArmReadDbgdevid(VOID)
{
    UINT32 val;
    __asm__ volatile("mrc p14, 0, %0, c7,c2,7" : "=r"(val));
    return val;
}

STATIC INLINE VOID OsArmWriteDbgdevid(UINT32 val)
{
    __asm__ volatile("mcr p14, 0, %0, c7,c2,7" ::"r"(val));
    __asm__ volatile("isb" ::: "memory");
}

#endif /* __LOS_ARM_H__ */
