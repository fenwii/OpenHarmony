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

#include "power_state_token.h"
#include "devmgr_service_clnt.h"
#include "hdf_device_desc.h"
#include "hdf_slist.h"
#include "osal_mem.h"

static void PowerStateTokenAcqureWakeLock(struct IPowerStateToken *token)
{
    struct HdfSRef *sref = NULL;
    struct PowerStateToken *stateToken = (struct PowerStateToken *)token;
    if (stateToken == NULL) {
        return;
    }
    sref = (struct HdfSRef *)&stateToken->wakeRef;
    if ((sref != NULL) && (sref->Acquire != NULL)) {
        sref->Acquire(sref);
    }
}

static void PowerStateTokenReleaseWakeLock(struct IPowerStateToken *token)
{
    struct HdfSRef *sref = NULL;
    struct PowerStateToken *stateToken = (struct PowerStateToken *)token;
    if (stateToken == NULL) {
        return;
    }
    sref = (struct HdfSRef *)&stateToken->wakeRef;
    if ((sref != NULL) && (sref->Release != NULL)) {
        sref->Release(sref);
    }
}

static void PowerStateTokenOnFirstAcquire(struct HdfSRef *sref)
{
    if (sref == NULL) {
        return;
    }
    struct PowerStateToken *stateToken = (struct PowerStateToken *)HDF_SLIST_CONTAINER_OF(
        struct HdfSRef, sref, struct PowerStateToken, wakeRef);
    if (stateToken->state != POWER_STATE_ACTIVE) {
        struct IDevmgrService *devMgrSvcIf = NULL;
        struct IPowerEventListener* listener = stateToken->listener;
        struct DevmgrServiceClnt *inst = DevmgrServiceClntGetInstance();
        if (inst == NULL) {
            return;
        }
        devMgrSvcIf = (struct IDevmgrService *)inst->devMgrSvcIf;
        if (devMgrSvcIf->AcquireWakeLock == NULL) {
            return;
        }
        devMgrSvcIf->AcquireWakeLock(devMgrSvcIf, &stateToken->super);
        if (stateToken->state == POWER_STATE_INACTIVE) {
            if ((listener != NULL) && (listener->Resume != NULL)) {
                listener->Resume(stateToken->deviceObject);
            }
        }
        stateToken->state = POWER_STATE_ACTIVE;
    }
}

static void PowerStateTokenOnLastRelease(struct HdfSRef *sref)
{
    if (sref == NULL) {
        return;
    }
    struct PowerStateToken *stateToken = (struct PowerStateToken *)HDF_SLIST_CONTAINER_OF(
        struct HdfSRef, sref, struct PowerStateToken, wakeRef);
    if (stateToken->state == POWER_STATE_ACTIVE) {
        struct IDevmgrService *devMgrSvcIf = NULL;
        struct IPowerEventListener *listener = stateToken->listener;
        struct DevmgrServiceClnt *inst = DevmgrServiceClntGetInstance();
        if (inst == NULL) {
            return;
        }
        devMgrSvcIf = (struct IDevmgrService *)inst->devMgrSvcIf;
        if ((devMgrSvcIf == NULL) || (devMgrSvcIf->AcquireWakeLock == NULL)) {
            return;
        }
        devMgrSvcIf->ReleaseWakeLock(devMgrSvcIf, &stateToken->super);
        if ((listener != NULL) && (listener->Suspend != NULL)) {
            listener->Suspend(stateToken->deviceObject);
        }
        stateToken->state = POWER_STATE_INACTIVE;
    }
}

static void PowerStateTokenConstruct(
    struct PowerStateToken *powerStateToken, struct HdfDeviceObject *deviceObject, struct IPowerEventListener *listener)
{
    struct IPowerStateToken *tokenIf = (struct IPowerStateToken *)powerStateToken;
    struct IHdfSRefListener *srefListener = (struct IHdfSRefListener *)OsalMemCalloc(sizeof(struct IHdfSRefListener));
    if (srefListener == NULL) {
        return;
    }

    tokenIf->AcquireWakeLock = PowerStateTokenAcqureWakeLock;
    tokenIf->ReleaseWakeLock = PowerStateTokenReleaseWakeLock;

    srefListener->OnFirstAcquire = PowerStateTokenOnFirstAcquire;
    srefListener->OnLastRelease = PowerStateTokenOnLastRelease;

    powerStateToken->state = POWER_STATE_IDLE;
    powerStateToken->listener = listener;
    powerStateToken->deviceObject = deviceObject;
    HdfSRefConstruct(&powerStateToken->wakeRef, srefListener);
}

struct PowerStateToken *PowerStateTokenNewInstance(
    struct HdfDeviceObject *deviceObject, struct IPowerEventListener *listener)
{
    struct PowerStateToken *stateToken =
        (struct PowerStateToken *)OsalMemCalloc(sizeof(struct PowerStateToken));
    if (stateToken != NULL) {
        PowerStateTokenConstruct(stateToken, deviceObject, listener);
    }
    return stateToken;
}

void PowerStateTokenFreeInstance(struct PowerStateToken *stateToken)
{
    if (stateToken != NULL) {
        if (stateToken->wakeRef.listener != NULL) {
            OsalMemFree(stateToken->wakeRef.listener);
            stateToken->wakeRef.listener = NULL;
        }
        OsalMemFree(stateToken);
    }
}
