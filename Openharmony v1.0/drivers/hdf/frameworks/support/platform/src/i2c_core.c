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

#include "i2c_core.h"
#include <string.h>
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG i2c_core

int32_t I2cCntlrTransfer(struct I2cCntlr *cntlr, struct I2cMsg *msgs, int16_t count)
{
    int32_t ret;

    if (cntlr == NULL) {
        HDF_LOGE("I2cCntlrTransfer: cntlr is null\n");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->ops == NULL || cntlr->ops->transfer == NULL) {
        HDF_LOGE("I2cCntlrTransfer: ops or transfer is null\n");
        return HDF_ERR_NOT_SUPPORT;
    }

    ret = cntlr->ops->transfer(cntlr, msgs, count);
    return ret;
}

int32_t I2cCntlrAdd(struct I2cCntlr *cntlr)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->device == NULL) {
        HDF_LOGE("I2cCntlrAdd: no device associated!\n");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->ops == NULL) {
        HDF_LOGE("I2cCntlrAdd: no ops supplied!\n");
        return HDF_ERR_INVALID_OBJECT;
    }
    if (OsalMutexInit(&cntlr->lock) != HDF_SUCCESS) {
        HDF_LOGE("I2cCntlrAdd: init lock fail!\n");
        return HDF_FAILURE;
    }
    cntlr->device->service = &cntlr->service;
    return HDF_SUCCESS;
}

void I2cCntlrRemove(struct I2cCntlr *cntlr)
{
    if (cntlr == NULL) {
        return;
    }

    if (cntlr->device == NULL) {
        HDF_LOGE("I2cCntlrBind: no device associated!\n");
        return;
    }

    cntlr->device->service = NULL;
    (void)OsalMutexDestroy(&cntlr->lock);
}
