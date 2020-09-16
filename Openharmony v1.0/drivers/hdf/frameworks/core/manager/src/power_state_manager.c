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

#include "power_state_manager.h"
#include "hdf_object_manager.h"
#include "power_state_token_clnt.h"

static struct PowerStateTokenClnt *PowerStateManagerGetStateTokenClnt(
    struct PowerStateManager *inst, struct IPowerStateToken *tokenIf)
{
    struct HdfSListIterator it;
    if (inst == NULL) {
        return NULL;
    }
    HdfSListIteratorInit(&it, &inst->tokens);
    while (HdfSListIteratorHasNext(&it)) {
        struct PowerStateTokenClnt *tokenClnt =
            (struct PowerStateTokenClnt *)HdfSListIteratorNext(&it);
        if (tokenClnt->tokenIf == tokenIf)  {
            return tokenClnt;
        }
    }
    return NULL;
}

static void PowerStateManagerAcquireWakeLock(
    struct PowerStateManager *inst, struct IPowerStateToken *tokenIf)
{
    if (inst == NULL) {
        return;
    }
    struct HdfSRef *sref = &inst->wakeRef;
    struct PowerStateTokenClnt *stateTokeClnt = PowerStateManagerGetStateTokenClnt(inst, tokenIf);
    if (stateTokeClnt == NULL) {
        return;
    }
    stateTokeClnt->powerState = POWER_STATE_ACTIVE;
    if (sref->Acquire != NULL) {
        sref->Acquire(sref);
    }
}

static void PowerStateManagerReleaseWakeLock(
    struct PowerStateManager *inst, struct IPowerStateToken *tokenIf)
{
    struct HdfSRef *sref = NULL;
    struct PowerStateTokenClnt *stateTokeClnt = PowerStateManagerGetStateTokenClnt(inst, tokenIf);
    if (inst == NULL || stateTokeClnt == NULL) {
        return;
    }
    stateTokeClnt->powerState = POWER_STATE_INACTIVE;
    sref = &inst->wakeRef;
    if (sref->Release != NULL) {
        sref->Release(sref);
    }
}

static void PowerStateManagerConstruct(struct PowerStateManager *inst)
{
    // not support system acquire and release
    static struct IHdfSRefListener wakeLockRefListener = {
        .OnFirstAcquire = NULL,
        .OnLastRelease = NULL,
    };

    inst->AcquireWakeLock = PowerStateManagerAcquireWakeLock;
    inst->ReleaseWakeLock = PowerStateManagerReleaseWakeLock;
    HdfSListInit(&inst->tokens);
    HdfSRefConstruct(&inst->wakeRef, &wakeLockRefListener);
}

struct PowerStateManager *PowerStateManagerGetInstance()
{
    static struct PowerStateManager powerStateManager = { 0 };
    if (powerStateManager.AcquireWakeLock == NULL) {
        PowerStateManagerConstruct(&powerStateManager);
    }
    return &powerStateManager;
}
