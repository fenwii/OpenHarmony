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

#include "eapol.h"
#include <stdint.h>
#include "securec.h"
#include "osal_time.h"
#include "osal_mem.h"
#include "hdf_log.h"

#define HDF_LOG_TAG             HDF_WIFI_EAPOL

#define RETURN_IF_INPUT_VALID(netDevice, buff) do {                 \
        if ((netDevice) == NULL || (buff) == NULL) {                        \
            HDF_LOGE("%s, netdevice = null or buf = null.", __func__); \
            return HDF_ERR_INVALID_PARAM;                               \
        }                                                               \
        if ((netDevice)->specialProcPriv == NULL) {                       \
            HDF_LOGE("%s : specialProcPriv = null", __func__);          \
            return HDF_ERR_INVALID_PARAM;                               \
        }                                                               \
    } while (0)                                                          \

static int32_t EnableEapol(const struct NetDevice *netDevice, struct EapolEnable *buff)
{
    RETURN_IF_INPUT_VALID(netDevice, buff);
    struct EapolData *eapol = (struct EapolData *)netDevice->specialProcPriv;
    eapol->regFlag = true;
    eapol->context = buff->context;
    eapol->notify = buff->notify;
    return HDF_SUCCESS;
}

static int32_t DisableEapol(const struct NetDevice *netDevice)
{
    if (netDevice == NULL || netDevice->specialProcPriv == NULL) {
        HDF_LOGE("%s: netDevice = null or specialProcPriv = null!", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    struct EapolData *eapol = (struct EapolData *)netDevice->specialProcPriv;
    eapol->regFlag = false;
    eapol->context = NULL;
    eapol->notify = NULL;
    return HDF_SUCCESS;
}

static int32_t GetEapol(const struct NetDevice *netDevice, struct EapolRx *buff)
{
    RETURN_IF_INPUT_VALID(netDevice, buff);
    struct EapolData *eapol = (struct EapolData *)netDevice->specialProcPriv;
    struct EapolRx *eapolRx = buff;
    struct NetBuf *netBuff = NULL;
    if (NetBufQueueIsEmpty(&eapol->eapolQueue)) {
        HDF_LOGE("%s fail : eapolQueue empty!", __func__);
        return HDF_FAILURE;
    }
    netBuff = NetBufQueueDequeue(&eapol->eapolQueue);
    if (netBuff == NULL) {
        HDF_LOGE("%s fail : dequeue netBuff = null!", __func__);
        return HDF_FAILURE;
    }

    uint8_t *p = NetBufGetAddress(netBuff, E_DATA_BUF);
    uint32_t len = NetBufGetDataLen(netBuff);
    if (len > eapolRx->len) {
        HDF_LOGE("%s fail : eapolRx->len too small! netBuff->len(%d) > eapolRx->len(%d).",
            __func__, netBuff->len, eapolRx->len);
        NetBufFree(netBuff);
        return HDF_FAILURE;
    }
    if (p != NULL) {
        if (memcpy_s(eapolRx->buff, eapolRx->len, p, len) != EOK) {
            HDF_LOGE("%s::mem safe function err!", __func__);
            NetBufFree(netBuff);
            return HDF_FAILURE;
        }
    }
    eapolRx->len = len;
    NetBufFree(netBuff);
    return HDF_SUCCESS;
}

static int32_t SendEapol(struct NetDevice *netDevice, struct EapolTx *buff)
{
    if (netDevice == NULL || buff == NULL) {
        HDF_LOGE("%s : netdevice = null or buff = null.", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    if ((netDevice->netDeviceIf == NULL) || (netDevice->netDeviceIf->xmit == NULL)) {
        HDF_LOGE("%s : netDeviceIf NULL.", __func__);
        return HDF_FAILURE;
    }

    struct EapolTx *eapolTx = buff;
    if (eapolTx->buff == NULL) {
        HDF_LOGE("%s::eapolTx->buff = null!", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    struct NetBuf *netBuff = NetBufDevAlloc(netDevice, eapolTx->len);
    if (netBuff == NULL) {
        HDF_LOGE("%s : netBuff alloc fail!", __func__);
        return HDF_FAILURE;
    }
    NetBufPush(netBuff, E_DATA_BUF, eapolTx->len);
    if (memcpy_s(NetBufGetAddress(netBuff, E_DATA_BUF), eapolTx->len,
        eapolTx->buff, eapolTx->len) != EOK) {
        NetBufFree(netBuff);
        HDF_LOGE("%s::mem safe function err!", __func__);
        return HDF_FAILURE;
    }
    return netDevice->netDeviceIf->xmit(netDevice, netBuff);
}

static void HandleEapolQueue(struct EapolData *eapol)
{
    if (eapol == NULL) {
        return;
    }
    int64_t currentTime = 0;
    int64_t intervalTime = 0;
    OsalTimespec timeSpec;
    struct NetBuf *netBuf = NULL;
    if (OsalGetTime(&timeSpec) == HDF_SUCCESS) {
        currentTime = timeSpec.sec;
    }
    uint16_t maxCount = (eapol->maxCount != 0) ? eapol->maxCount : EAPOL_MAX_COUNT;
    /* The queue is empty to update enqueueTime and count */
    if (NetBufQueueIsEmpty(&eapol->eapolQueue)) {
        eapol->enqueueTime = currentTime;
        eapol->count = 0;
        return;
    }

    /* prevent a large amount of netbuff resources being used when WPA is abnormal */
    if (currentTime > eapol->enqueueTime) {
        intervalTime = currentTime - eapol->enqueueTime;
    }
    if (intervalTime > EAPOL_MAX_ENQUEUE_TIME || eapol->count >= maxCount) {
        /* output log to solve problem */
        if (intervalTime > EAPOL_MAX_ENQUEUE_TIME) {
            HDF_LOGE("%s discard pre netbuf : intervalTime(%lld) > EAPOL_MAX_ENQUEUE_TIME.", __func__,
                intervalTime);
        } else {
            HDF_LOGE("%s discard pre netbuf : eapol->count(%d) = maxCount(%d).", __func__, eapol->count, maxCount);
        }
        eapol->count--;
        eapol->enqueueTime = currentTime;
        netBuf = NetBufQueueDequeue(&eapol->eapolQueue);
        if (netBuf == NULL) {
            HDF_LOGE("%s error : netbuff = null!", __func__);
            return;
        }
        NetBufFree(netBuf);
    }
    return;
}

static int32_t WriteEapolToQueue(const struct NetDevice *netDevice, struct NetBuf *buff)
{
    RETURN_IF_INPUT_VALID(netDevice, buff);
    struct EapolData *eapol = (struct EapolData *)netDevice->specialProcPriv;
    if (eapol->regFlag && (eapol->notify != NULL)) {
        HandleEapolQueue(eapol);
        /* eapol data enqueue and notify wap processing */
        eapol->count++;
        NetBufQueueEnqueue(&eapol->eapolQueue, buff);
        eapol->notify(netDevice->name, eapol->context);
        return HDF_SUCCESS;
    } else {
        /* free netbuff when not register notify. */
        NetBufFree(buff);
        HDF_LOGE("%s fail : eapol process is not register.", __func__);
        return HDF_SUCCESS;
    }
}

static struct EapolInterface g_eapolInterface = {
    .enableEapol = EnableEapol,
    .disableEapol = DisableEapol,
    .getEapol = GetEapol,
    .sendEapol = SendEapol,
    .writeEapolToQueue = WriteEapolToQueue,
};

struct Eapol g_eapol = {
    .eapolOp = &g_eapolInterface,
};

int32_t CreateEapolData(struct NetDevice *netDevice)
{
    if (netDevice == NULL) {
        HDF_LOGE("%s fail : netdev = null!", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    if (netDevice->specialProcPriv != NULL) {
        HDF_LOGI("%s already create!", __func__);
        return HDF_SUCCESS;
    }
    struct EapolData *eapolData = (struct EapolData *)OsalMemCalloc(sizeof(struct EapolData));
    if (eapolData == NULL) {
        HDF_LOGE("%s fail : malloc fail!", __func__);
        return HDF_FAILURE;
    }
    (void)memset_s(eapolData, sizeof(struct EapolData), 0, sizeof(struct EapolData));
    NetBufQueueInit(&eapolData->eapolQueue);
    netDevice->specialProcPriv = eapolData;
    HDF_LOGI("%s success!", __func__);
    return HDF_SUCCESS;
}

void DestroyEapolData(struct NetDevice *netDevice)
{
    if (netDevice == NULL || netDevice->specialProcPriv == NULL) {
        HDF_LOGE("%s already free!", __func__);
        return;
    }
    struct EapolData *eapolData = (struct EapolData *)netDevice->specialProcPriv;
    NetBufQueueClear(&eapolData->eapolQueue);
    OsalMemFree(eapolData);
    netDevice->specialProcPriv = NULL;
    HDF_LOGE("%s success!", __func__);
    return;
}

const struct Eapol *EapolGetInstance(void)
{
    return &g_eapol;
}
