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

#ifndef WATCHDOG_CORE_H
#define WATCHDOG_CORE_H

#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "osal_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

struct WatchdogCntlr;
struct WatchdogMethod;

struct WatchdogCntlr {
    struct IDeviceIoService service;
    struct HdfDeviceObject *device;
    OsalSpinlock lock;
    struct WatchdogMethod *ops;
    int16_t wdtId;
    void *priv;
};

struct WatchdogMethod {
    int32_t (*getStatus)(struct WatchdogCntlr *wdt, int32_t *status);
    int32_t (*setTimeout)(struct WatchdogCntlr *wdt, uint32_t seconds);
    int32_t (*getTimeout)(struct WatchdogCntlr *wdt, uint32_t *seconds);
    int32_t (*start)(struct WatchdogCntlr *wdt);
    int32_t (*stop)(struct WatchdogCntlr *wdt);
    int32_t (*feed)(struct WatchdogCntlr *wdt);
};

/**
 * @brief Add a new WatchdogCntlr to HDF.
 *
 * @param cntlr The watchdog conroller to be added.
 *
 * @return Returns 0 on success; returns a negative value otherwise.
 * @since 1.0
 */
int32_t WatchdogCntlrAdd(struct WatchdogCntlr *cntlr);

/**
 * @brief Remove the watchdog controller from HDF.
 *
 * @param cntlr The watchdog controller to be removed.
 *
 * @since 1.0
 */
void WatchdogCntlrRemove(struct WatchdogCntlr *cntlr);


/**
 * @brief Turn HdfDeviceObject to an Watchdog.
 *
 * @param device Indicates a HdfDeviceObject.
 *
 * @return Retrns the pointer of the WatchdogCntlr on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct WatchdogCntlr *WatchdogCntlrFromDevice(struct HdfDeviceObject *device)
{
    return (device == NULL) ? NULL : (struct WatchdogCntlr *)device->service;
}

/**
 * @brief Turn WatchdogCntlr to a HdfDeviceObject.
 *
 * @param wdt Indicates the WATCHDOG wdt device.
 *
 * @return Retrns the pointer of the HdfDeviceObject on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct HdfDeviceObject *WatchdogCntlrToDevice(struct WatchdogCntlr *wdt)
{
    return (wdt == NULL) ? NULL : wdt->device;
}

int32_t WatchdogCntlrGetStatus(struct WatchdogCntlr *cntlr, int32_t *status);

int32_t WatchdogCntlrStart(struct WatchdogCntlr *cntlr);

int32_t WatchdogCntlrStop(struct WatchdogCntlr *cntlr);

int32_t WatchdogCntlrSetTimeout(struct WatchdogCntlr *cntlr, uint32_t seconds);

int32_t WatchdogCntlrGetTimeout(struct WatchdogCntlr *cntlr, uint32_t *seconds);

int32_t WatchdogCntlrFeed(struct WatchdogCntlr *cntlr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* WATCHDOG_CORE_H */
