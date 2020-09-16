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

#include "los_user_init.h"
#include "los_syscall.h"

#define SYS_CALL_VALUE 0x900001

#ifdef LOSCFG_KERNEL_DYNLOAD
LITE_USER_SEC_RODATA STATIC CHAR *g_initPath = "/bin/init";
#endif

LITE_USER_SEC_TEXT STATIC UINT32 sys_call3(UINT32 nbr, UINT32 parm1, UINT32 parm2, UINT32 parm3)
{
    register UINT32 reg7 __asm__("r7") = (UINT32)(nbr);
    register UINT32 reg2 __asm__("r2") = (UINT32)(parm3);
    register UINT32 reg1 __asm__("r1") = (UINT32)(parm2);
    register UINT32 reg0 __asm__("r0") = (UINT32)(parm1);

    __asm__ __volatile__
    (
        "svc %1"
        : "=r"(reg0)
        : "i"(SYS_CALL_VALUE), "r"(reg7), "r"(reg0), "r"(reg1), "r"(reg2)
        : "memory", "r14"
    );

    return reg0;
}

LITE_USER_SEC_ENTRY VOID OsUserInit(VOID *args)
{
#ifdef LOSCFG_KERNEL_DYNLOAD
    sys_call3(__NR_execve, (UINTPTR)g_initPath, 0, 0);
#endif
    while (1) {
    }
}
