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

#include "hdf_sref.h"
#include "hdf_log.h"

#define HDF_LOG_TAG hdf_sref

void HdfSRefAcquire(struct HdfSRef *sref)
{
    int32_t lockRef;
    if (sref == NULL) {
        HDF_LOGE("Acquire input sref is null");
        return;
    }
    OsalAtomicInc(&sref->refs);
    lockRef = OsalAtomicRead(&sref->refs);
    if ((lockRef == 1) && (sref->listener != NULL)) {
        struct IHdfSRefListener *listener = sref->listener;
        if (listener->OnFirstAcquire != NULL) {
            listener->OnFirstAcquire(sref);
        }
    }
}

void HdfSRefRelease(struct HdfSRef *sref)
{
    int32_t lockRef;
    if (sref == NULL) {
        HDF_LOGE("Release input sref is null");
        return;
    }
    OsalAtomicDec(&sref->refs);
    lockRef = OsalAtomicRead(&sref->refs);
    if ((lockRef == 0) && (sref->listener != NULL)) {
        struct IHdfSRefListener *listener = sref->listener;
        if (listener->OnLastRelease != NULL) {
            listener->OnLastRelease(sref);
        }
    }
}

void HdfSRefConstruct(struct HdfSRef *sref, struct IHdfSRefListener *listener)
{
    if ((sref == NULL) || (listener == NULL)) {
        HDF_LOGE("Input params is invalid");
        return;
    }
    OsalAtomicSet(&sref->refs, 0);
    sref->listener = listener;
    sref->Acquire = HdfSRefAcquire;
    sref->Release = HdfSRefRelease;
}

