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

#include "i2c_if.h"
#include "devsvc_manager_clnt.h"
#include "hdf_base.h"
#include "hdf_log.h"
#include "i2c_core.h"
#include "osal_mem.h"
#include "securec.h"

#define HDF_LOG_TAG i2c_if

#define SERVICE_NAME_LEN 32
#define I2C_BUS_MAX 8

static struct I2cCntlr *I2cCntlrGetByNumber(int16_t num)
{
    struct I2cCntlr *cntlr = NULL;
    char *cntlrName = NULL;

    if (num < 0 || num >= I2C_BUS_MAX) {
        HDF_LOGE("I2cCntlrGetByNumber: invalid num:%d\n", num);
        return NULL;
    }
    cntlrName = OsalMemCalloc(SERVICE_NAME_LEN + 1);
    if (cntlrName == NULL) {
        return NULL;
    }
    if (snprintf_s(cntlrName, SERVICE_NAME_LEN + 1, SERVICE_NAME_LEN,
        "HDF_PLATFORM_I2C_%d", num) < 0) {
        HDF_LOGE("I2cCntlrGetByNumber: format cntlr name fail!\n");
        OsalMemFree(cntlrName);
        return NULL;
    }
    cntlr = (struct I2cCntlr *)DevSvcManagerClntGetService(cntlrName);
    if (cntlr == NULL) {
        HDF_LOGE("I2cCntlrGetByNumber: get cntlr fail!\n");
    }
    OsalMemFree(cntlrName);
    return cntlr;
}

struct DevHandle *I2cOpen(int16_t number)
{
    struct DevHandle *handle = NULL;
    struct I2cCntlr *cntlr = NULL;

    cntlr = I2cCntlrGetByNumber(number);
    if (cntlr == NULL) {
        return NULL;
    }
    handle = OsalMemCalloc(sizeof(*handle));
    if (handle == NULL) {
        return NULL;
    }
    handle->object = cntlr;
    return handle;
}

void I2cClose(struct DevHandle *handle)
{
    if (handle != NULL) {
        handle->object = NULL;
        OsalMemFree(handle);
    }
}

int32_t I2cTransfer(struct DevHandle *handle, struct I2cMsg *msgs, int16_t count)
{
    if (handle == NULL || handle->object == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }

    return I2cCntlrTransfer((struct I2cCntlr *)handle->object, msgs, count);
}
