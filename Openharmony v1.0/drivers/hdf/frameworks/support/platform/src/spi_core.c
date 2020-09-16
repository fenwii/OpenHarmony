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

#include "spi_core.h"
#include <string.h>
#include "hdf_log.h"
#include "osal_mem.h"
#include "spi_if.h"

#define HDF_LOG_TAG spi_core

int32_t SpiCntlrTransfer(struct SpiCntlr *cntlr, uint32_t csNum, struct SpiMsg *msg, uint32_t count)
{
    int32_t ret;

    if (cntlr == NULL) {
        HDF_LOGE("%s: invalid parameter\n", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    if (cntlr->method == NULL || cntlr->method->Transfer == NULL) {
        HDF_LOGE("%s: transfer not support\n", __func__);
        return HDF_ERR_NOT_SUPPORT;
    }

    (void)OsalMutexLock(&(cntlr->lock));
    cntlr->curCs = csNum;
    ret = cntlr->method->Transfer(cntlr, msg, count);
    (void)OsalMutexUnlock(&(cntlr->lock));
    return ret;
}

int32_t SpiCntlrSetCfg(struct SpiCntlr *cntlr, uint32_t csNum, struct SpiCfg *cfg)
{
    int32_t ret;

    if (cntlr == NULL) {
        HDF_LOGE("%s: invalid parameter\n", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (cntlr->method == NULL || cntlr->method->SetCfg == NULL) {
        HDF_LOGE("%s: not support\n", __func__);
        return HDF_ERR_NOT_SUPPORT;
    }

    (void)OsalMutexLock(&(cntlr->lock));
    cntlr->curCs = csNum;
    ret = cntlr->method->SetCfg(cntlr, cfg);
    (void)OsalMutexUnlock(&(cntlr->lock));
    return ret;
}

int32_t SpiCntlrGetCfg(struct SpiCntlr *cntlr, uint32_t csNum, struct SpiCfg *cfg)
{
    int32_t ret;

    if (cntlr == NULL) {
        HDF_LOGE("%s: invalid parameter\n", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (cntlr->method == NULL || cntlr->method->GetCfg == NULL) {
        HDF_LOGE("%s: not support\n", __func__);
        return HDF_ERR_NOT_SUPPORT;
    }

    (void)OsalMutexLock(&(cntlr->lock));
    cntlr->curCs = csNum;
    ret = cntlr->method->GetCfg(cntlr, cfg);
    (void)OsalMutexUnlock(&(cntlr->lock));
    return ret;
}

void SpiCntlrDestroy(struct SpiCntlr *cntlr)
{
    if (cntlr == NULL) {
        return;
    }
    (void)OsalMutexDestroy(&(cntlr->lock));
    OsalMemFree(cntlr);
}

struct SpiCntlr *SpiCntlrCreate(struct HdfDeviceObject *device)
{
    struct SpiCntlr *cntlr = NULL;

    if (device == NULL) {
        HDF_LOGE("%s: invalid parameter\n", __func__);
        return NULL;
    }

    cntlr = (struct SpiCntlr *)OsalMemCalloc(sizeof(*cntlr));
    if (cntlr == NULL) {
        HDF_LOGE("%s: OsalMemCalloc error\n", __func__);
        return NULL;
    }
    cntlr->device = device;
    device->service = &(cntlr->service);
    (void)OsalMutexInit(&cntlr->lock);
    cntlr->priv = NULL;
    return cntlr;
}
