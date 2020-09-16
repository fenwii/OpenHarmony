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

#ifndef GPIO_CORE_H
#define GPIO_CORE_H

#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "gpio_if.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

struct GpioCntlr;
struct GpioMethod;

struct GpioCntlr {
    struct IDeviceIoService service;
    struct HdfDeviceObject *device;
    void *priv;
    struct GpioMethod *ops;
};

struct GpioMethod {
    int32_t (*request)(struct GpioCntlr *cntlr, uint16_t gpio);
    int32_t (*release)(struct GpioCntlr *cntlr, uint16_t gpio);
    int32_t (*write)(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t val);
    int32_t (*read)(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *val);
    int32_t (*setDir)(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t dir);
    int32_t (*getDir)(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *dir);
    int32_t (*toIrq)(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *irq);
    int32_t (*setIrq)(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t mode, GpioIrqFunc func, void *arg);
    int32_t (*unsetIrq)(struct GpioCntlr *cntlr, uint16_t gpio);
    int32_t (*enableIrq)(struct GpioCntlr *cntlr, uint16_t gpio);
    int32_t (*disableIrq)(struct GpioCntlr *cntlr, uint16_t gpio);
};

/**
 * @brief Add the Gpio Controller to HDF, and do some checking.
 *
 * @param cntlr Indicates the GPIO controller device.
 *
 * @return Returns 0 on success; returns a negative value otherwise.
 * @since 1.0
 */
int32_t GpioCntlrAdd(struct GpioCntlr *cntlr);

/**
 * @brief Remove the Gpio Controller from HDF.
 *
 * @param cntlr Indicates the I2C controller device.
 *
 * @since 1.0
 */
void GpioCntlrRemove(struct GpioCntlr *cntlr);

/**
 * @brief Turn HdfDeviceObject to an GpioCntlr.
 *
 * @param device Indicates a HdfDeviceObject.
 *
 * @return Retrns the pointer of the GpioCntlr on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct GpioCntlr *GpioCntlrFromDevice(struct HdfDeviceObject *device)
{
    return (device == NULL) ? NULL : (struct GpioCntlr *)device->service;
}

int32_t GpioCntlrWrite(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t val);

int32_t GpioCntlrRead(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *val);

int32_t GpioCntlrSetDir(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t dir);

int32_t GpioCntlrGetDir(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *dir);

int32_t GpioCntlrToIrq(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t *irq);

int32_t GpioCntlrSetIrq(struct GpioCntlr *cntlr, uint16_t gpio, uint16_t mode, GpioIrqFunc func, void *arg);

int32_t GpioCntlrUnsetIrq(struct GpioCntlr *cntlr, uint16_t gpio);

int32_t GpioCntlrEnableIrq(struct GpioCntlr *cntlr, uint16_t gpio);

int32_t GpioCntlrDisableIrq(struct GpioCntlr *cntlr, uint16_t gpio);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* GPIO_CORE_H */
