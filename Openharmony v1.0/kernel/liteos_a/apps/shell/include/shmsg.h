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

#ifndef _SHMSG_H
#define _SHMSG_H

#include "shell.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define SHELL_ENTRY_STACKSIZE   0x1000
#define SHELL_TASK_STACKSIZE    0x3000

#define SHELL_EXEC_COMMAND          "exec "
#define SHELL_EXEC_COMMAND_BYTES    5

#define CONSOLE_IOC_MAGIC   'c'
#define CONSOLE_CONTROL_REG_USERTASK _IO(CONSOLE_IOC_MAGIC, 7)

#define COLOR_NONE     "\e[0m"
#define COLOR_RED      "\e[0;31m"
#define COLOR_L_RED    "\e[1;31m"
#define SHELL_PROMPT   COLOR_L_RED"OHOS # "COLOR_NONE

typedef void (*OutputFunc)(const char *fmt, ...);
extern int ShellTaskInit(ShellCB *shellCB);
extern int ShellEntryInit(ShellCB *shellCB);
extern void ShellCmdLineParse(char c, OutputFunc outputFunc, ShellCB *shellCB);
extern int ShellNotify(ShellCB *shellCB);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _SHMSG_H */
