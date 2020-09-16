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

#ifndef _LOS_PROCESS_H
#define _LOS_PROCESS_H

#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

extern INT32 LOS_Fork(UINT32 flags, const CHAR *name, const TSK_ENTRY_FUNC entry, UINT32 stackSize);

extern UINT32 LOS_ProcessYield(VOID);

extern INT32 LOS_SetProcessPriority(INT32 pid, UINT16 prio);

extern INT32 LOS_GetProcessPriority(INT32 pid);

extern INT32 LOS_GetProcessScheduler(INT32 pid);

extern INT32 LOS_SetProcessScheduler(INT32 pid, UINT16 policy, UINT16 prio);

extern UINT32 LOS_GetCurrProcessID(VOID);

extern INT32 LOS_Wait(INT32 pid, USER INT32 *status, UINT32 options, VOID *rusage);

extern INT32 LOS_GetCurrProcessGroupID(VOID);

extern INT32 LOS_GetProcessGroupID(UINT32 pid);

extern VOID LOS_Exit(INT32 status);

#ifdef LOSCFG_SECURITY_CAPABILITY
extern BOOL LOS_CheckInGroups(UINT32 gid);
#endif
extern INT32 LOS_GetUserID(VOID);
extern INT32 LOS_GetGroupID(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
