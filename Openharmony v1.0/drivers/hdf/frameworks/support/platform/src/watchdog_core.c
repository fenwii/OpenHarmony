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

#include "watchdog_core.h"
#include <string.h>
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG watchdog_core

int32_t WatchdogCntlrAdd(struct WatchdogCntlr *cntlr)
{
    int32_t ret;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->device == NULL) {
        HDF_LOGE("WatchdogCntlrAdd: no device associated!");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->ops == NULL) {
        HDF_LOGE("WatchdogCntlrAdd: no ops supplied!");
        return HDF_ERR_INVALID_OBJECT;
    }

    ret = OsalSpinInit(&cntlr->lock);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("WatchdogCntlrAdd: spinlock init fail!");
        return ret;
    }

    cntlr->device->service = &cntlr->service;
    return HDF_SUCCESS;
}

void WatchdogCntlrRemove(struct WatchdogCntlr *cntlr)
{
    if (cntlr == NULL) {
        return;
    }

    if (cntlr->device == NULL) {
        HDF_LOGE("WatchdogCntlrRemove: no device associated!");
        return;
    }

    cntlr->device->service = NULL;
    (void)OsalSpinDestroy(&cntlr->lock);
}

int32_t WatchdogCntlrGetStatus(struct WatchdogCntlr *cntlr, int32_t *status)
{
    int32_t ret;
    uint32_t flags;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->getStatus == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    if (status == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }

    if (OsalSpinLockIrqSave(&cntlr->lock, &flags) != HDF_SUCCESS) {
        return HDF_ERR_DEVICE_BUSY;
    }
    ret = cntlr->ops->getStatus(cntlr, status);
    (void)OsalSpinUnlockIrqRestore(&cntlr->lock, &flags);
    return ret;
}

int32_t WatchdogCntlrStart(struct WatchdogCntlr *cntlr)
{
    int32_t ret;
    uint32_t flags;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->start == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }

    if (OsalSpinLockIrqSave(&cntlr->lock, &flags) != HDF_SUCCESS) {
        return HDF_ERR_DEVICE_BUSY;
    }
    ret = cntlr->ops->start(cntlr);
    (void)OsalSpinUnlockIrqRestore(&cntlr->lock, &flags);
    return ret;
}

int32_t WatchdogCntlrStop(struct WatchdogCntlr *cntlr)
{
    int32_t ret;
    uint32_t flags;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->stop == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }

    if (OsalSpinLockIrqSave(&cntlr->lock, &flags) != HDF_SUCCESS) {
        return HDF_ERR_DEVICE_BUSY;
    }
    ret = cntlr->ops->stop(cntlr);
    (void)OsalSpinUnlockIrqRestore(&cntlr->lock, &flags);
    return ret;
}

int32_t WatchdogCntlrSetTimeout(struct WatchdogCntlr *cntlr, uint32_t seconds)
{
    int32_t ret;
    uint32_t flags;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->setTimeout == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }

    if (OsalSpinLockIrqSave(&cntlr->lock, &flags) != HDF_SUCCESS) {
        return HDF_ERR_DEVICE_BUSY;
    }
    ret = cntlr->ops->setTimeout(cntlr, seconds);
    (void)OsalSpinUnlockIrqRestore(&cntlr->lock, &flags);
    return ret;
}

int32_t WatchdogCntlrGetTimeout(struct WatchdogCntlr *cntlr, uint32_t *seconds)
{
    int32_t ret;
    uint32_t flags;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->getTimeout == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    if (seconds == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }

    if (OsalSpinLockIrqSave(&cntlr->lock, &flags) != HDF_SUCCESS) {
        return HDF_ERR_DEVICE_BUSY;
    }
    ret = cntlr->ops->getTimeout(cntlr, seconds);
    (void)OsalSpinUnlockIrqRestore(&cntlr->lock, &flags);
    return ret;
}

int32_t WatchdogCntlrFeed(struct WatchdogCntlr *cntlr)
{
    int32_t ret;
    uint32_t flags;

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->feed == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }

    if (OsalSpinLockIrqSave(&cntlr->lock, &flags) != HDF_SUCCESS) {
        return HDF_ERR_DEVICE_BUSY;
    }
    ret = cntlr->ops->feed(cntlr);
    (void)OsalSpinUnlockIrqRestore(&cntlr->lock, &flags);
    return ret;
}
