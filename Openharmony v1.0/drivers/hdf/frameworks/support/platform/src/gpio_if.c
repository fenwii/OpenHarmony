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

#include "gpio_if.h"
#include "devsvc_manager_clnt.h"
#include "gpio_core.h"
#include "hdf_base.h"
#include "hdf_log.h"

#define HDF_LOG_TAG gpio_if

static struct GpioCntlr *GpioGetCntlr(void)
{
    static struct GpioCntlr *service = NULL;

    if (service != NULL) {
        return service;
    }
    service = (struct GpioCntlr*)DevSvcManagerClntGetService("HDF_PLATFORM_GPIO");
    if (service == NULL) {
        HDF_LOGE("GpioGetCntlr: get service fail!\n");
    }
    return service;
}


int32_t GpioRead(uint16_t gpio, uint16_t *val)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }

    return GpioCntlrRead(cntlr, gpio, val);
}

int32_t GpioWrite(uint16_t gpio, uint16_t val)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrWrite(cntlr, gpio, val);
}

int32_t GpioSetDir(uint16_t gpio, uint16_t dir)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrSetDir(cntlr, gpio, dir);
}

int32_t GpioGetDir(uint16_t gpio, uint16_t *dir)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrGetDir(cntlr, gpio, dir);
}

int32_t GpioSetIrq(uint16_t gpio, uint16_t mode, GpioIrqFunc func, void *arg)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrSetIrq(cntlr, gpio, mode, func, arg);
}

int32_t GpioUnSetIrq(uint16_t gpio)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrUnsetIrq(cntlr, gpio);
}

int32_t GpioEnableIrq(uint16_t gpio)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrEnableIrq(cntlr, gpio);
}

int32_t GpioDisableIrq(uint16_t gpio)
{
    struct GpioCntlr *cntlr = GpioGetCntlr();

    if (cntlr == NULL) {
        return HDF_ERR_INVALID_OBJECT;
    }
    return GpioCntlrDisableIrq(cntlr, gpio);
}
