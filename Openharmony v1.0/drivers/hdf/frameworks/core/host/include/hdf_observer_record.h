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

#ifndef HDF_OBSERVER_RECORD_H
#define HDF_OBSERVER_RECORD_H

#include "hdf_object.h"
#include "hdf_slist.h"
#include "osal_mutex.h"

struct HdfServiceObserverRecord {
    struct HdfSListNode entry;
    uint32_t serviceKey;
    uint16_t policy;
    uint32_t matchId;
    struct OsalMutex obsRecMutex;
    struct HdfSList subscribers;
    struct HdfObject *publisher;
};

uint32_t HdfMakeHardwareId(uint16_t hostId, uint16_t deviceId);
struct HdfServiceObserverRecord *HdfServiceObserverRecordObtain(uint32_t serviceKey);
void HdfServiceObserverRecordRecycle(struct HdfServiceObserverRecord *record);
bool HdfServiceObserverRecordCompare(struct HdfSListNode *listEntry, uint32_t serviceKey);
void HdfServiceObserverRecordNotifySubscribers(
    struct HdfServiceObserverRecord *record, uint32_t matchId, uint16_t policy);
void HdfServiceObserverRecordDelete(struct HdfSListNode *listEntry);

#endif /* HDF_OBSERVER_RECORD_H */
