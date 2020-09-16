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

#include "capability_type.h"
#include "los_memory.h"
#include "los_process_pri.h"
#include "user_copy.h"
#include "los_printf.h"

#define CAPABILITY_INIT_STAT            0xffffffff
#define CAPABILITY_GET_CAP_MASK(x)      (1 << ((x) & 31))
#define CAPABILITY_MAX                  31

BOOL IsCapPermit(UINT32 capIndex)
{
    UINT32 capability = OsCurrProcessGet()->capability;
    if (capIndex > CAPABILITY_MAX || capIndex < 0) {
        PRINTK("%s,%d, get invalid capIndex %d\n", __FUNCTION__, __LINE__, capIndex);
        return FALSE;
    }

    return (capability & (CAPABILITY_GET_CAP_MASK(capIndex)));
}

VOID OsInitCapability(LosProcessCB *processCB)
{
    processCB->capability = CAPABILITY_INIT_STAT;
}

VOID OsCopyCapability(LosProcessCB *from, LosProcessCB *to)
{
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    to->capability = from->capability;
    SCHEDULER_UNLOCK(intSave);
}

UINT32 SysCapSet(UINT32 caps)
{
    UINT32 intSave;

    if (!IsCapPermit(CAP_CAPSET)) {
        return -EPERM;
    }

    SCHEDULER_LOCK(intSave);
    OsCurrProcessGet()->capability = caps;
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

UINT32 SysCapGet(UINT32 *caps)
{
    UINT32 intSave;
    UINT32 kCaps;

    SCHEDULER_LOCK(intSave);
    kCaps = OsCurrProcessGet()->capability;
    SCHEDULER_UNLOCK(intSave);

    if (LOS_ArchCopyToUser(caps, &kCaps, sizeof(UINT32)) != LOS_OK) {
        return -EFAULT;
    }

    return LOS_OK;
}
