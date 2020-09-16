/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "wpa_hal_event.h"
#include "driver.h"
#include "common.h"
#include "eloop.h"
#include "utils/hdf_base.h"
#include "l2_packet/l2_packet.h"
#include "wpa_hal.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static inline int IsZeroAddr(const uint8_t *addr, const uint8_t len)
{
    if (len != ETH_ADDR_LEN) {
        return -EFAIL;
    }
    // 0 1 2 3 4 5 : mac index
    return !(addr[0] | addr[1] | addr[2] | addr[3] | addr[4] | addr[5]);
}

static void WifiWpaEventNewStaProcess(const WifiDriverData *drv, struct HdfSBuf *reqData)
{
    WifiNewStaInfo staInfo;
    union wpa_event_data event;
    uint32_t len = 0;
    (void)memset_s(&event, sizeof(union wpa_event_data), 0, sizeof(union wpa_event_data));
    if (!HdfSbufReadInt32(reqData, &staInfo.reassoc)) {
        wpa_printf(MSG_ERROR, "%s: fail to get reassoc", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&staInfo.ie), &staInfo.ieLen)) {
        wpa_printf(MSG_ERROR, "%s: fail to get ie", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&staInfo.macAddr), &len) || (len != ETH_ADDR_LEN)) {
        wpa_printf(MSG_ERROR, "%s: fail to get macAddr", __func__);
        return;
    }

    if (IsZeroAddr(staInfo.macAddr, ETH_ADDR_LEN)) {
        wpa_supplicant_event(drv->ctx, EVENT_DISASSOC, NULL);
    } else {
        event.assoc_info.reassoc     = staInfo.reassoc;
        event.assoc_info.req_ies     = staInfo.ie;
        event.assoc_info.req_ies_len = staInfo.ieLen;
        event.assoc_info.addr        = staInfo.macAddr;
        wpa_supplicant_event(drv->ctx, EVENT_ASSOC, &event);
    }
    wpa_printf(MSG_INFO, "WifiWpaEventNewStaProcess done");
}

static void WifiWpaEventDelStaProcess(const WifiDriverData *drv, struct HdfSBuf *reqData)
{
    union wpa_event_data event;
    uint32_t len = 0;

    (void)memset_s(&event, sizeof(union wpa_event_data), 0, sizeof(union wpa_event_data));
    if ((!HdfSbufReadBuffer(reqData, (const void **)(&event.disassoc_info.addr), &len)) || (len != ETH_ADDR_LEN)) {
        wpa_printf(MSG_ERROR, "%s: fail to get macAddr", __func__);
        return;
    }
    if (drv->ctx != NULL) {
        wpa_supplicant_event(drv->ctx, EVENT_DISASSOC, &event);
        wpa_printf(MSG_INFO, "WifiWpaEventDelStaProcess done");
    }
}

static void WifiWpaEventRxMgmtProcess(const WifiDriverData *drv, struct HdfSBuf *reqData)
{
    WifiRxMgmt rxMgmt;
    union wpa_event_data event;

    (void)memset_s(&event, sizeof(union wpa_event_data), 0, sizeof(union wpa_event_data));
    if (!HdfSbufReadInt32(reqData, &rxMgmt.freq)) {
        wpa_printf(MSG_ERROR, "%s: fail to get freq", __func__);
        return;
    }
    if (!HdfSbufReadInt32(reqData, &rxMgmt.sigMbm)) {
        wpa_printf(MSG_ERROR, "%s: fail to get sigMbm", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&rxMgmt.buf), &rxMgmt.len)) {
        wpa_printf(MSG_ERROR, "%s: fail to get buf", __func__);
        return;
    }

    event.rx_mgmt.frame = rxMgmt.buf;
    event.rx_mgmt.frame_len = rxMgmt.len;
    event.rx_mgmt.ssi_signal = rxMgmt.sigMbm;
    event.rx_mgmt.freq = rxMgmt.freq;

    wpa_supplicant_event(drv->ctx, EVENT_RX_MGMT, &event);
    wpa_printf(MSG_INFO, "WifiWpaEventRxMgmtProcess done");
}

static void WifiWpaEventTxStatusProcess(const WifiDriverData *drv, struct HdfSBuf *reqData)
{
    uint16_t fc;
    struct ieee80211_hdr *hdr = NULL;
    WifiTxStatus txStatus = { 0 };
    union wpa_event_data event;

    (void)memset_s(&event, sizeof(union wpa_event_data), 0, sizeof(union wpa_event_data));
    if (!HdfSbufReadUint8(reqData, &txStatus.ack)) {
        wpa_printf(MSG_ERROR, "%s: fail to get ack", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&txStatus.buf), &txStatus.len)) {
        wpa_printf(MSG_ERROR, "%s: fail to get buf", __func__);
        return;
    }

    hdr = (struct ieee80211_hdr *)txStatus.buf;
    fc = le_to_host16(hdr->frame_control);
    event.tx_status.type = WLAN_FC_GET_TYPE(fc);
    event.tx_status.stype = WLAN_FC_GET_STYPE(fc);
    event.tx_status.dst = hdr->addr1;
    event.tx_status.data = txStatus.buf;
    event.tx_status.data_len = txStatus.len;
    event.tx_status.ack = (txStatus.ack != FALSE);

    wpa_supplicant_event(drv->ctx, EVENT_TX_STATUS, &event);
    wpa_printf(MSG_INFO, "WifiWpaEventTxStatusProcess done");
}


static void WifiWpaEventScanDoneProcess(WifiDriverData *drv, struct HdfSBuf *reqData)
{
    uint32_t status = 0;

    if (drv->ctx == NULL) {
        wpa_printf(MSG_ERROR, "%s: ctx is null", __func__);
        return;
    }
    if (!HdfSbufReadUint32(reqData, &status)) {
        wpa_printf(MSG_ERROR, "%s: fail to get status", __func__);
        return;
    }

    eloop_cancel_timeout(WifiWpaScanTimeout, drv, drv->ctx);
    if (status != WIFI_SCAN_SUCCESS) {
        return;
    }
    wpa_supplicant_event(drv->ctx, EVENT_SCAN_RESULTS, NULL);
    wpa_printf(MSG_INFO, "WifiWpaEventScanDoneProcess done");
}

static int32_t WifiScanResultParse(WifiScanResult *scanResult, uint8_t **ie, uint8_t **beaconIe,
    struct HdfSBuf *reqData)
{
    uint32_t len = 0;
    if (scanResult == NULL || ie == NULL || beaconIe == NULL) {
        return -EFAIL;
    }

    if (!HdfSbufReadInt16(reqData, &(scanResult->beaconInt))) {
        wpa_printf(MSG_ERROR, "%s: fail to get beaconInt", __func__);
        return HDF_FAILURE;
    }
    if (!HdfSbufReadInt16(reqData, &(scanResult->caps))) {
        wpa_printf(MSG_ERROR, "%s: fail to get caps", __func__);
        return HDF_FAILURE;
    }
    if (!HdfSbufReadInt32(reqData, &(scanResult->level))) {
        wpa_printf(MSG_ERROR, "%s: fail to get level", __func__);
        return HDF_FAILURE;
    }
    if (!HdfSbufReadInt32(reqData, &(scanResult->freq))) {
        wpa_printf(MSG_ERROR, "%s: fail to get freq", __func__);
        return HDF_FAILURE;
    }
    if (!HdfSbufReadInt32(reqData, &(scanResult->flags))) {
        wpa_printf(MSG_ERROR, "%s: fail to get flags", __func__);
        return HDF_FAILURE;
    }
    if ((!HdfSbufReadBuffer(reqData, (const void **)(&(scanResult->bssid)), &len)) || len != ETH_ADDR_LEN) {
        wpa_printf(MSG_ERROR, "%s: fail to get bssid", __func__);
        return HDF_FAILURE;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)ie, &(scanResult->ieLen))) {
        wpa_printf(MSG_ERROR, "%s: fail to get ie", __func__);
        return HDF_FAILURE;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)beaconIe, &(scanResult->beaconIeLen))) {
        wpa_printf(MSG_ERROR, "%s: fail to get beaconIe", __func__);
        return HDF_FAILURE;
    }

    return SUCC;
}

static void WifiWpaEventScanResultProcess(WifiDriverData *drv, struct HdfSBuf *reqData)
{
    WifiScanResult scanResult = { 0 };
    uint8_t *ie = NULL;
    uint8_t *beaconIe = NULL;
    struct wpa_scan_res *res = NULL;
    errno_t rc;

    if (WifiScanResultParse(&scanResult, &ie, &beaconIe, reqData) != SUCC) {
        goto failed;
    }

    wpa_printf(MSG_INFO, "%s: ie_len=%d, beacon_ie_len=%d", __func__, scanResult.ieLen, scanResult.beaconIeLen);

    res = (struct wpa_scan_res *)os_zalloc(sizeof(struct wpa_scan_res) + scanResult.ieLen + scanResult.beaconIeLen);
    if (res == NULL) {
        goto failed;
    }
    res->flags      = scanResult.flags;
    res->freq       = scanResult.freq;
    res->caps       = scanResult.caps;
    res->beacon_int = scanResult.beaconInt;
    res->qual       = 0;
    res->level      = scanResult.level;
    res->age        = 0;
    res->ie_len     = scanResult.ieLen;
    res->beacon_ie_len = scanResult.beaconIeLen;
    rc = memcpy_s(res->bssid, ETH_ADDR_LEN, scanResult.bssid, ETH_ADDR_LEN);
    if (rc != EOK) {
        goto failed;
    }
    rc = memcpy_s(&res[1], scanResult.ieLen, ie, scanResult.ieLen);
    if (rc != EOK) {
        goto failed;
    }
    rc = memcpy_s(((uint8_t *)(&res[1]) + scanResult.ieLen), scanResult.beaconIeLen, beaconIe, scanResult.beaconIeLen);
    if (rc != EOK) {
        goto failed;
    }
    if (drv->scanNum >= SCAN_AP_LIMIT) {
        wpa_printf(MSG_ERROR, "WifiWpaEventScanResultProcess: drv->scanNum >= SCAN_AP_LIMIT");
        goto failed;
    }
    drv->scanRes[drv->scanNum++] = res;
    wpa_printf(MSG_INFO, "WifiWpaEventScanResultProcess done");
    return;

failed:
    if (res != NULL) {
        os_free(res);
        res = NULL;
    }
}

static void WifiWpaEventConnectResultProcess(WifiDriverData *drv, struct HdfSBuf *reqData)
{
    WifiConnectResult result = { 0 };
    union wpa_event_data event;
    uint32_t len = 0;
    errno_t rc;

    (void)memset_s(&event, sizeof(union wpa_event_data), 0, sizeof(union wpa_event_data));
    if (!HdfSbufReadUint16(reqData, &(result.status))) {
        wpa_printf(MSG_ERROR, "%s: fail to get status", __func__);
        return;
    }
    if (!HdfSbufReadUint16(reqData, &(result.freq))) {
        wpa_printf(MSG_ERROR, "%s: fail to get freq", __func__);
        return;
    }
    if ((!HdfSbufReadBuffer(reqData, (const void **)(&(result.bssid)), &len)) || len != ETH_ADDR_LEN) {
        wpa_printf(MSG_ERROR, "%s: fail to get bssid", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&(result.reqIe)), &(result.reqIeLen))) {
        wpa_printf(MSG_ERROR, "%s: fail to get reqIe", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&(result.respIe)), &(result.respIeLen))) {
        wpa_printf(MSG_ERROR, "%s: fail to get respIe", __func__);
        return;
    }

    if (result.status != 0) {
        drv->associated = WIFI_DISCONNECT;
        wpa_supplicant_event(drv->ctx, EVENT_DISASSOC, NULL);
    } else {
        drv->associated = WIFI_CONNECT;
        rc = memcpy_s(drv->bssid, ETH_ADDR_LEN, result.bssid, ETH_ALEN);
        if (rc != EOK) {
            return;
        }
        event.assoc_info.req_ies      = result.reqIe;
        event.assoc_info.req_ies_len  = result.reqIeLen;
        event.assoc_info.resp_ies     = result.respIe;
        event.assoc_info.resp_ies_len = result.respIeLen;
        event.assoc_info.addr         = result.bssid;
        event.assoc_info.freq         = result.freq;
        wpa_supplicant_event(drv->ctx, EVENT_ASSOC, &event);
    }
    wpa_printf(MSG_INFO, "WifiWpaEventConnectResultProcess done");
}

static void WifiWpaEventDisconnectProcess(WifiDriverData *drv, struct HdfSBuf *reqData)
{
    WifiDisconnect result = { 0 };
    union wpa_event_data event;

    (void)memset_s(&event, sizeof(union wpa_event_data), 0, sizeof(union wpa_event_data));
    if (!HdfSbufReadUint16(reqData, &(result.reason))) {
        wpa_printf(MSG_ERROR, "%s: fail to get reason", __func__);
        return;
    }
    if (!HdfSbufReadBuffer(reqData, (const void **)(&(result.ie)), &(result.ieLen))) {
        wpa_printf(MSG_ERROR, "%s: fail to get bssid", __func__);
        return;
    }

    drv->associated = WIFI_DISCONNECT;
    event.disassoc_info.reason_code = result.reason;
    event.disassoc_info.ie          = result.ie;
    event.disassoc_info.ie_len      = result.ieLen;
    wpa_supplicant_event(drv->ctx, EVENT_DISASSOC, &event);
    wpa_printf(MSG_INFO, "WifiWpaEventDisconnectProcess done");
}

extern void l2_packet_receive(void *eloop_ctx, void *sock_ctx);
static inline void WifiWpaDriverEventEapolRecvProcess(WifiDriverData *drv, struct HdfSBuf *reqData)
{
    wpa_printf(MSG_INFO, "WifiWpaDriverEventEapolRecvProcess call");
    l2_packet_receive(drv->eapolSock, NULL);
}

int32_t WifiWpaDriverEventProcess(const char *ifname, uint32_t event, struct HdfSBuf *reqData)
{
    WifiDriverData *drv = GetDrvData();
    int32_t ret = SUCC;

    if (ifname == NULL || drv == NULL || reqData == NULL) {
        return -EFAIL;
    }
    wpa_printf(MSG_INFO, "WifiWpaDriverEventProcess event=%d", event);
    switch (event) {
        case WPA_ELOOP_EVENT_NEW_STA:
            WifiWpaEventNewStaProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_DEL_STA:
            WifiWpaEventDelStaProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_RX_MGMT:
            WifiWpaEventRxMgmtProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_TX_STATUS:
            WifiWpaEventTxStatusProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_SCAN_DONE:
            WifiWpaEventScanDoneProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_SCAN_RESULT:
            WifiWpaEventScanResultProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_CONNECT_RESULT:
            WifiWpaEventConnectResultProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_DISCONNECT:
            WifiWpaEventDisconnectProcess(drv, reqData);
            break;
        case WPA_ELOOP_EVENT_EAPOL_RECV:
            WifiWpaDriverEventEapolRecvProcess(drv, reqData);
            break;
        default:
            break;
    }

    return ret;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
