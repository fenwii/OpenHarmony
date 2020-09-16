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

#ifndef SPI_CORE_H
#define SPI_CORE_H

#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "hdf_dlist.h"
#include "spi_if.h"
#include "osal_mutex.h"

struct SpiCntlr;
struct SpiCntlrMethod;

struct SpiCntlrMethod {
    int32_t (*GetCfg)(struct SpiCntlr *, struct SpiCfg *);
    int32_t (*SetCfg)(struct SpiCntlr *, struct SpiCfg *);
    int32_t (*Transfer)(struct SpiCntlr *, struct SpiMsg *, uint32_t);
};

struct SpiCntlr {
    struct IDeviceIoService service;
    struct HdfDeviceObject *device;
    uint32_t busNum;
    uint32_t curCs;
    struct OsalMutex lock;
    struct SpiCntlrMethod *method;
    void *priv;
};

struct SpiDev {
    struct SpiCntlr *cntlr;
    struct DListHead list;
    uint32_t csNum;
    uint32_t maxSpeedHz;
    uint16_t mode;
    uint8_t bitsPerWord;
    uint8_t transferMode;
};

struct SpiCntlr *SpiCntlrCreate(struct HdfDeviceObject *device);
void SpiCntlrDestroy(struct SpiCntlr *cntlr);

/**
 * @brief Turn SpiCntlr to a HdfDeviceObject.
 *
 * @param cntlr Indicates the SPI cntlr device.
 *
 * @return Retrns the pointer of the HdfDeviceObject on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct HdfDeviceObject *SpiCntlrToDevice(struct SpiCntlr *cntlr)
{
    return (cntlr == NULL) ? NULL : cntlr->device;
}

/**
 * @brief Turn HdfDeviceObject to an SpiCntlr.
 *
 * @param device Indicates a HdfDeviceObject.
 *
 * @return Retrns the pointer of the SpiCntlr on success; returns NULL otherwise.
 * @since 1.0
 */
static inline struct SpiCntlr *SpiCntlrFromDevice(struct HdfDeviceObject *device)
{
    return (device == NULL) ? NULL : (struct SpiCntlr *)device->service;
}

int32_t SpiCntlrTransfer(struct SpiCntlr *, uint32_t, struct SpiMsg *, uint32_t);
int32_t SpiCntlrSetCfg(struct SpiCntlr *, uint32_t, struct SpiCfg *);
int32_t SpiCntlrGetCfg(struct SpiCntlr *, uint32_t, struct SpiCfg *);

#endif /* SPI_CORE_H */
