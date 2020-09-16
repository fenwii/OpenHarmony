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

#include "hdf_observer_record.h"
#include "hdf_log.h"
#include "hdf_service_subscriber.h"
#include "osal_mem.h"

#define HDF_LOG_TAG observer_record
#define HALF_INT_LEN 16

uint32_t HdfMakeHardwareId(uint16_t hostId, uint16_t deviceId)
{
    uint32_t hardwareId = hostId;
    hardwareId = (hardwareId << HALF_INT_LEN) | deviceId;
    return hardwareId;
}

struct HdfServiceObserverRecord *HdfServiceObserverRecordObtain(uint32_t serviceKey)
{
    struct HdfServiceObserverRecord *observerRecord =
        (struct HdfServiceObserverRecord *)OsalMemCalloc(sizeof(struct HdfServiceObserverRecord));
    if (observerRecord != NULL) {
        observerRecord->serviceKey = serviceKey;
        observerRecord->publisher = NULL;
        if (OsalMutexInit(&observerRecord->obsRecMutex) != HDF_SUCCESS) {
            OsalMemFree(observerRecord);
            return NULL;
        }
        HdfSListInit(&observerRecord->subscribers);
    }
    return observerRecord;
}

void HdfServiceObserverRecordRecycle(struct HdfServiceObserverRecord *observerRecord)
{
    if (observerRecord != NULL) {
        HdfSListFlush(&observerRecord->subscribers, HdfServiceSubscriberDelete);
        OsalMutexDestroy(&observerRecord->obsRecMutex);
        observerRecord->obsRecMutex.realMutex = NULL;
        OsalMemFree(observerRecord);
    }
}

bool HdfServiceObserverRecordCompare(struct HdfSListNode *listEntry, uint32_t serviceKey)
{
    if (listEntry == NULL) {
        return false;
    }
    struct HdfServiceObserverRecord *record = (struct HdfServiceObserverRecord *)listEntry;
    if (record->serviceKey == serviceKey) {
        return true;
    }
    return false;
}

void HdfServiceObserverRecordNotifySubscribers(
    struct HdfServiceObserverRecord *record, uint32_t matchId, uint16_t policy)
{
    struct HdfSListIterator it;
    if (record == NULL) {
        HDF_LOGE("%s: record is null", __func__);
        return;
    }

    OsalMutexLock(&record->obsRecMutex);
    HdfSListIteratorInit(&it, &record->subscribers);
    while (HdfSListIteratorHasNext(&it)) {
        struct HdfServiceSubscriber *subscriber =
            (struct HdfServiceSubscriber *)HdfSListIteratorNext(&it);
        if ((matchId == subscriber->matchId) || (policy != SERVICE_POLICY_PRIVATE)) {
            subscriber->state = HDF_SUBSCRIBER_STATE_READY;
            if (subscriber->callback.OnServiceConnected != NULL) {
                subscriber->callback.OnServiceConnected(subscriber->callback.deviceObject, record->publisher);
            }
        }
    }
    OsalMutexUnlock(&record->obsRecMutex);
}

void HdfServiceObserverRecordDelete(struct HdfSListNode *listEntry)
{
    struct HdfServiceObserverRecord *observerRecord = (struct HdfServiceObserverRecord *)listEntry;
    if (observerRecord != NULL) {
        HdfServiceObserverRecordRecycle(observerRecord);
    }
}

