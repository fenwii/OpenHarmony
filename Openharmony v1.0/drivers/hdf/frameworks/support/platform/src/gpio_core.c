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

#include "gpio_core.h"
#include <string.h>
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG gpio_core

static struct GpioCntlr *g_cntlr;

int32_t GpioCntlrAdd(struct GpioCntlr *cntlr)
{
    if (g_cntlr != NULL) {
        HDF_LOGE("GpioCntlrAdd: already has a gpio controller!");
        return HDF_ERR_NOT_SUPPORT;
    }

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->device == NULL) {
        HDF_LOGE("GpioCntlrAdd: no device associated!");
        return HDF_ERR_INVALID_OBJECT;
    }

    if (cntlr->ops == NULL) {
        HDF_LOGE("GpioCntlrAdd: no ops supplied!");
        return HDF_ERR_INVALID_OBJECT;
    }

    cntlr->device->service = &cntlr->service;
    g_cntlr = cntlr;
    return HDF_SUCCESS;
}

void GpioCntlrRemove(struct GpioCntlr *cntlr)
{
    if (cntlr == NULL) {
        return;
    }

    if (cntlr->device == NULL) {
        HDF_LOGE("GpioCntlrRemove: no device associated!\n");
        return;
    }

    cntlr->device->service = NULL;
    g_cntlr = NULL;
}

int32_t GpioCntlrWrite(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t val)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->write == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->write(cntlr, gpio, val);
}

int32_t GpioCntlrRead(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *val)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->read == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    if (val == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return cntlr->ops->read(cntlr, gpio, val);
}

int32_t GpioCntlrSetDir(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t dir)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->setDir == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->setDir(cntlr, gpio, dir);
}

int32_t GpioCntlrGetDir(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *dir)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->getDir == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    if (dir == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return cntlr->ops->getDir(cntlr, gpio, dir);
}

int32_t GpioCntlrToIrq(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *irq)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->toIrq == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->toIrq(cntlr, gpio, irq);
}

int32_t GpioCntlrSetIrq(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t mode, GpioIrqFunc func, void *arg)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->setIrq == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->setIrq(cntlr, gpio, mode, func, arg);
}

int32_t GpioCntlrUnsetIrq(struct GpioCntlr *cntlr, uint16_t gpio)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->unsetIrq == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->unsetIrq(cntlr, gpio);
}

int32_t GpioCntlrEnableIrq(struct GpioCntlr *cntlr, uint16_t gpio)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->enableIrq == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->enableIrq(cntlr, gpio);
}

int32_t GpioCntlrDisableIrq(struct GpioCntlr *cntlr, uint16_t gpio)
{
    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    if (cntlr->ops == NULL || cntlr->ops->disableIrq == NULL) {
        return HDF_ERR_NOT_SUPPORT;
    }
    return cntlr->ops->disableIrq(cntlr, gpio);
}
