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

#ifndef HDF_EAPOL_H
#define HDF_EAPOL_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf_netbuf.h"
#include "net_device.h"

#define EAPOL_MAX_COUNT 10
#define EAPOL_MAX_ENQUEUE_TIME 300 /* 300 Second */

struct EapolData {
    bool regFlag;  /* is already regstered */
    uint16_t count; /* eapol frame count in NetBuffQueue. */
    uint16_t maxCount;
    int64_t enqueueTime;                       /* record eapol frame time for dfx. */
    void (*notify)(const char *name, void *context); /* notify eapol frame enqueue message */
    void *context;
    struct NetBufQueue eapolQueue;
};

struct Eapol {
    struct EapolInterface *eapolOp;
};

struct EapolEnable {
    void (*notify)(const char *name, void *context);
    void *context;
};

struct EapolRx {
    uint8_t *buff;
    uint32_t len;
};

struct EapolTx {
    uint8_t *buff;
    uint32_t len;
};

struct EapolInterface {
    int32_t (*enableEapol)(const struct NetDevice *netDevice, struct EapolEnable *buff);
    int32_t (*disableEapol)(const struct NetDevice *netDevice);
    int32_t (*getEapol)(const struct NetDevice *netDevice, struct EapolRx *buff);
    int32_t (*sendEapol)(struct NetDevice *netDevice, struct EapolTx *buff);
    int32_t (*writeEapolToQueue)(const struct NetDevice *netDevice, struct NetBuf *buff);
};

/* API */
const struct Eapol *EapolGetInstance(void);
void DestroyEapolData(struct NetDevice *netDevice);
int32_t CreateEapolData(struct NetDevice *netDevice);

#endif /* HDF_EAPOL_H */