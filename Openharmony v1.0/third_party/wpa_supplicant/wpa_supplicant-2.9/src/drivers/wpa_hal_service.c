/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "wpa_hal_service.h"
#include "wpa_hal_event.h"
#include "hdf_log.h"
#include "hdf_sbuf.h"
#include "utils/hdf_base.h"
#include "hdf_io_service.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

int OnWiFiEvents(void *priv, uint32_t id, struct HdfSBuf *data)
{
    (void)priv;
    if (data == NULL) {
        HDF_LOGE("%s: params is NULL", __func__);
        return HDF_FAILURE;
    }
    const char *ifname = HdfSbufReadString(data);
    if (ifname == NULL) {
        HDF_LOGE("%s: fail to get ifname", __func__);
        return HDF_FAILURE;
    }
    uint32_t ret = WifiWpaDriverEventProcess(ifname, id, data);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("WifiWpaEventMsg failed cmd=%u, ret=%d", id, ret);
    }
    return ret;
}

static struct HdfIoService *g_wifiService = NULL;

const char *DRIVER_SERVICE_NAME = "hdfwifi";

static struct HdfDevEventlistener g_wifiEventListener = {
    .callBack = OnWiFiEvents,
    .priv = NULL
};

int32_t WpaMsgServiceInit(void)
{
    g_wifiService = HdfIoServiceBind(DRIVER_SERVICE_NAME, 0);
    if (g_wifiService == NULL) {
        HDF_LOGE("%s: fail to get remote service!", __func__);
        return HDF_FAILURE;
    }

    if (HdfDeviceRegisterEventListener(g_wifiService, &g_wifiEventListener) != HDF_SUCCESS) {
        HDF_LOGE("%s: fail to register event listener", __func__);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

void WpaMsgServiceDeinit(void)
{
    if (HdfDeviceUnregisterEventListener(g_wifiService, &g_wifiEventListener)) {
        HDF_LOGE("fail to  unregister listener");
        return;
    }

    HdfIoServiceRecycle(g_wifiService);
}

int32_t WifiWpaCmdBlockSyncSend(const uint32_t cmd, struct HdfSBuf *reqData, struct HdfSBuf *respData)
{
    if (reqData == NULL) {
        HDF_LOGE("%s params is NULL", __func__);
        return HDF_FAILURE;
    }
    if (g_wifiService == NULL || g_wifiService->dispatcher == NULL || g_wifiService->dispatcher->Dispatch == NULL) {
        HDF_LOGE("%s:bad remote service found!", __func__);
        return HDF_FAILURE;
    }
    int32_t ret = g_wifiService->dispatcher->Dispatch(&g_wifiService->object, cmd, reqData, respData);
    HDF_LOGI("%s: cmd=%d, ret=%d", __func__, cmd, ret);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif