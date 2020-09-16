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

#include "mem.h"
#include <securec.h>
#include "agent.h"
#include "mailbox_mempool.h"
#include "tc_ns_client.h"
#include "tc_ns_log.h"
#include "teek_ns_client.h"
#include "tzdriver_compat.h"

void TcMemFree(TcNsSharedMem *sharedMem)
{
    if (sharedMem == NULL) {
        return;
    }

    if (sharedMem->kernelAddr != NULL) {
        LOS_VFree(sharedMem->kernelAddr);
        sharedMem->kernelAddr = NULL;
    }
    free(sharedMem);
}

TcNsSharedMem *TcMemAllocate(size_t len)
{
    TcNsSharedMem *sharedMem = NULL;
    void *addr = NULL;

    sharedMem = calloc(1, sizeof(*sharedMem));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)sharedMem)) {
        tloge("sharedMem malloc failed\n");
        return ERR_PTR(-ENOMEM);
    }

    len = ALIGN(len, SZ_4K);
    if (len > MAILBOX_POOL_SIZE) {
        tloge("alloc sharemem size(%zu) is too large\n", len);
        free(sharedMem);
        return ERR_PTR(-EINVAL);
    }

    addr = LOS_VMalloc(len);
    if (addr == NULL) {
        tloge("alloc maibox failed\n");
        free(sharedMem);
        return ERR_PTR(-ENOMEM);
    }
    sharedMem->kernelAddr = addr;
    sharedMem->len = len;
    sharedMem->userAddr = NULL;
    sharedMem->userAddrCa = NULL;
    atomic_set(&sharedMem->usage, 0);
    return sharedMem;
}

int TcMemInit(void)
{
    int ret;

    tlogi("TcMemInit\n");

    ret = MailboxMempoolInit();
    if (ret) {
        tloge("tz mailbox init failed\n");
        return -ENOMEM;
    }

    return 0;
}

void TcMemDestroy(void)
{
    tlogi("tc_client exit\n");

    MailboxMempoolDestroy();
}
