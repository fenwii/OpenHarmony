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

#define _GNU_SOURCE
#include "los_syscall.h"
#include "los_task_pri.h"
#include "los_process_pri.h"
#include "los_printf.h"
#include "time.h"
#include "utime.h"
#include "poll.h"
#include "mqueue.h"
#include "los_futex_pri.h"
#include "sys/times.h"
#ifdef LOSCFG_FS_VFS
#include "fs/fs.h"
#include "fs/file.h"
#endif
#include "dirent.h"
#include "fcntl.h"
#include "unistd.h"

#include "sys/mount.h"
#include "sys/resource.h"
#include "sys/mman.h"
#include "sys/uio.h"
#include "sys/prctl.h"
#include "sys/socket.h"
#include "sys/utsname.h"
#include "poll.h"
#include "sys/uio.h"
#ifdef LOSCFG_SHELL
#include "shmsg.h"
#endif
#ifdef LOSCFG_SECURITY_CAPABILITY
#include "capability_api.h"
#endif
#include "sys/shm.h"


#define SYS_CALL_NUM    (__NR_syscallend + 1)
#define NARG_BITS       4
#define NARG_MASK       0x0F
#define NARG_PER_BYTE   2

typedef UINT32 (*SyscallFun1)(UINT32);
typedef UINT32 (*SyscallFun3)(UINT32, UINT32, UINT32);
typedef UINT32 (*SyscallFun5)(UINT32, UINT32, UINT32, UINT32, UINT32);
typedef UINT32 (*SyscallFun7)(UINT32, UINT32, UINT32, UINT32, UINT32, UINT32, UINT32);

static UINTPTR g_syscallHandle[SYS_CALL_NUM] = {0};
static UINT8 g_syscallNArgs[(SYS_CALL_NUM + 1) / NARG_PER_BYTE] = {0};

void SyscallHandleInit(void)
{
#define SYSCALL_HAND_DEF(id, fun, rType, nArg)                                             \
    if ((id) < SYS_CALL_NUM) {                                                             \
        g_syscallHandle[(id)] = (UINTPTR)(fun);                                            \
        g_syscallNArgs[(id) / NARG_PER_BYTE] |= ((id) & 1) ? (nArg) << NARG_BITS : (nArg); \
    }                                                                                      \

    #include "syscall_lookup.h"
#undef SYSCALL_HAND_DEF
}

/* The SYSCALL ID is in R7 on entry.  Parameters follow in R0..R6 */
LITE_OS_SEC_TEXT UINT32 *OsArmA32SyscallHandle(UINT32 *regs)
{
    UINT32 ret;
    UINT8 nArgs;
    UINTPTR handle;
    UINT32 cmd = regs[REG_R7];

    if (cmd >= SYS_CALL_NUM) {
        PRINT_ERR("Syscall ID: error %d !!!\n", cmd);
        return regs;
    }

    if (cmd == __NR_sigreturn) {
        OsRestorSignalContext(regs);
        return regs;
    }

    handle = g_syscallHandle[cmd];
    nArgs = g_syscallNArgs[cmd / NARG_PER_BYTE]; /* 4bit per nargs */
    nArgs = (cmd & 1) ? (nArgs >> NARG_BITS) : (nArgs & NARG_MASK);
    if ((handle == 0) || (nArgs > ARG_NUM_7)) {
        PRINT_ERR("Unsupport syscall ID: %d nArgs: %d\n", cmd, nArgs);
        regs[REG_R0] = -ENOSYS;
        return regs;
    }

    switch (nArgs) {
        case ARG_NUM_0:
        case ARG_NUM_1:
            ret = (*(SyscallFun1)handle)(regs[REG_R0]);
            break;
        case ARG_NUM_2:
        case ARG_NUM_3:
            ret = (*(SyscallFun3)handle)(regs[REG_R0], regs[REG_R1], regs[REG_R2]);
            break;
        case ARG_NUM_4:
        case ARG_NUM_5:
            ret = (*(SyscallFun5)handle)(regs[REG_R0], regs[REG_R1], regs[REG_R2], regs[REG_R3],
                                         regs[REG_R4]);
            break;
        default:
            ret = (*(SyscallFun7)handle)(regs[REG_R0], regs[REG_R1], regs[REG_R2], regs[REG_R3],
                                         regs[REG_R4], regs[REG_R5], regs[REG_R6]);
    }

    regs[REG_R0] = ret;

    OsSaveSignalContext(regs);

    /* Return the last value of curent_regs.  This supports context switches on return from the exception.
     * That capability is only used with theSYS_context_switch system call.
     */
    return regs;
}
