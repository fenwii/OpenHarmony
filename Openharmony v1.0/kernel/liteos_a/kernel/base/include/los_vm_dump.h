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
 * @defgroup los_vm_dump virtual memory dump operation
 * @ingroup kernel
 */

#ifndef __LOS_VM_DUMP_H__
#define __LOS_VM_DUMP_H__

#include "los_vm_map.h"
#include "los_process_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * These macros is used for process memory usage statistics.
 * Include virtual memory, shared memory and physical memory.
 */
#define PROCESS_VM_INDEX_MAX    3
#define PROCESS_MEMINFO_LEN     (sizeof(UINT32) * PROCESS_VM_INDEX_MAX)
#define PROCESS_VM_INDEX        0
#define PROCESS_SM_INDEX        1
#define PROCESS_PM_INDEX        2

const CHAR *OsGetRegionNameOrFilePath(LosVmMapRegion *region);
INT32 OsRegionOverlapCheckUnlock(LosVmSpace *space, LosVmMapRegion *region);
UINT32 OsShellCmdProcessVmUsage(LosVmSpace *space);
VOID OsShellCmdProcessPmUsage(LosVmSpace *space, UINT32 *sharePm, UINT32 *actualPm);
VOID OsUProcessPmUsage(LosVmSpace *space, UINT32 *sharePm, UINT32 *actualPm);
VOID OsKProcessPmUsage(LosVmSpace *kAspace, UINT32 *actualPm);
VOID OsDumpAspace(LosVmSpace *space);
UINT32 OsCountRegionPages(LosVmSpace *space, LosVmMapRegion *region, UINT32 *pssPages);
UINT32 OsCountAspacePages(LosVmSpace *space);
VOID OsDumpAllAspace(VOID);
VOID OsVmPhysDump(VOID);
VOID OsVmPhysUsedInfoGet(UINT32 *usedCount, UINT32 *totalCount);
INT32 OsRegionOverlapCheck(LosVmSpace *space, LosVmMapRegion *region);
VOID OsDumpPte(VADDR_T vaddr);
LosProcessCB *OsGetPIDByAspace(LosVmSpace *space);
CHAR *OsArchFlagsToStr(const UINT32 archFlags);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LOS_VM_DUMP_H__ */
