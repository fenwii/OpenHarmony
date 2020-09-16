/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "wpa_hal_cmd.h"
#include "wpa_hal.h"
#include "hdf_sbuf.h"
#include "utils/hdf_base.h"
#include "wpa_hal_service.h"
#include "common.h"
#include "driver.h"
#include "securec.h"
#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

int32_t WifiWpaEapolPacketSend(const char *ifname, const uint8_t *srcAddr, const uint8_t *dstAddr, uint8_t *buf,
    uint32_t length)
{
    uint32_t cmd = WIFI_WPA_CMD_SEND_EAPOL;
    int32_t ret;
    (void)srcAddr;
    (void)dstAddr;
    if (ifname == NULL || buf == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, buf, length);
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

#define DEFAULT_EAPOL_PACKAGE_SIZE 800

int32_t WifiWpaEapolPacketReceive(const char *ifname, WifiRxEapol *rxEapol)
{
    uint32_t cmd = WIFI_WPA_CMD_RECEIVE_EAPOL;
    int32_t ret;
    WifiRxEapol eapol = { 0 };

    if (ifname == NULL || rxEapol == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *respData = HdfSBufObtain(DEFAULT_EAPOL_PACKAGE_SIZE);
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL || respData == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
    if (!HdfSbufWriteString(data, ifname)) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
        goto RELEASE_DATA;
    }

    ret = WifiWpaCmdBlockSyncSend(cmd, data, respData);
    if (ret != HDF_SUCCESS) {
        wpa_printf(MSG_ERROR, "WifiWpaEapolPacketReceive failed ret = %d", ret);
        goto RELEASE_DATA;
    }
    if (!HdfSbufReadBuffer(respData, (const void **)(&(eapol.buf)), &(eapol.len))) {
        ret = -EFAIL;
        wpa_printf(MSG_ERROR, "WifiWpaEapolPacketReceive HdfSbufReadBuffer failed");
        goto RELEASE_DATA;
    }

    rxEapol->buf = NULL;
    rxEapol->len = 0;
    if (eapol.len != 0) {
        // wpa free
        rxEapol->buf = os_malloc(eapol.len);
        if (rxEapol->buf == NULL) {
            ret = -EFAIL;
            goto RELEASE_DATA;
        }
        if (memcpy_s(rxEapol->buf, eapol.len, eapol.buf, eapol.len) != EOK) {
            wpa_printf(MSG_ERROR, "memcpy failed");
        }
        rxEapol->len = eapol.len;
    }

RELEASE_DATA:
    HdfSBufRecycle(respData);
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaEapolEnable(const char *ifname)
{
    uint32_t cmd = WIFI_WPA_CMD_ENALBE_EAPOL;
    int32_t ret;

    if (ifname == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }

    if (HdfSbufWriteString(data, ifname)) {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    } else {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    }
    HdfSBufRecycle(data);

    return ret;
}

int32_t WifiWpaEapolDisable(const char *ifname)
{
    uint32_t cmd = WIFI_WPA_CMD_DISABLE_EAPOL;
    int32_t ret;

    if (ifname == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }
    if (HdfSbufWriteString(data, ifname)) {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    } else {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdSetAp(const char *ifname, WifiApSetting *apsettings)
{
    uint32_t cmd = WIFI_WPA_CMD_SET_AP;
    int32_t ret;

    if (ifname == NULL || apsettings == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings, sizeof(WifiApSetting));
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->beaconData.head, apsettings->beaconData.headLen);
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->beaconData.tail, apsettings->beaconData.tailLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->ssid, apsettings->ssidLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->meshSsid, apsettings->meshSsidLen);
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdChangeBeacon(const char *ifname, WifiApSetting *apsettings)
{
    uint32_t cmd = WIFI_WPA_CMD_CHANGE_BEACON;
    int32_t ret;

    if (ifname == NULL || apsettings == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }

    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings, sizeof(WifiApSetting));
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->beaconData.head, apsettings->beaconData.headLen);
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->beaconData.tail, apsettings->beaconData.tailLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->ssid, apsettings->ssidLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, apsettings->meshSsid, apsettings->meshSsidLen);
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdSendMlme(const char *ifname, WifiMlmeData *mlme)
{
    uint32_t cmd = WIFI_WPA_CMD_SEND_MLME;
    int32_t ret;

    if (ifname == NULL || mlme == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }

    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, mlme, sizeof(WifiMlmeData));
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, mlme->data, mlme->dataLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, mlme->cookie, sizeof(*mlme->cookie));
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

static int32_t WifiWpaCmdOperKey(const char *ifname, uint32_t cmd, WifiKeyExt *keyExt)
{
    if (ifname == NULL || keyExt == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        wpa_printf(MSG_ERROR, "Init HdfSBuf failed");
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, keyExt, sizeof(WifiKeyExt));
    if (keyExt->addr == NULL) {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, keyExt->addr, 0);
    } else {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, keyExt->addr, ETH_ADDR_LEN);
    }
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, keyExt->key, keyExt->keyLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, keyExt->seq, keyExt->seqLen);

    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(cmd, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}
int32_t WifiWpaCmdNewKey(const char *ifname, WifiKeyExt *keyExt)
{
    return WifiWpaCmdOperKey(ifname, WIFI_WPA_CMD_NEW_KEY, keyExt);
}

int32_t WifiWpaCmdDelKey(const char *ifname, WifiKeyExt *keyExt)
{
    return WifiWpaCmdOperKey(ifname, WIFI_WPA_CMD_DEL_KEY, keyExt);
}

int32_t WifiWpaCmdSetKey(const char *ifname, WifiKeyExt *keyExt)
{
    return WifiWpaCmdOperKey(ifname, WIFI_WPA_CMD_SET_KEY, keyExt);
}

int32_t WifiWpaCmdSetMode(const char *ifname, WifiSetMode *setMode)
{
    if (ifname == NULL || setMode == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, setMode, sizeof(*setMode));
    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_SET_MODE, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdGetOwnMac(const char *ifname, void *buf, uint32_t len)
{
    if (ifname == NULL || buf == NULL) {
        return -EFAIL;
    }
    (void)len;
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    struct HdfSBuf *reply = HdfSBufObtainDefaultSize();
    int32_t ret;
    if (data == NULL || reply == NULL) {
        ret = -EFAIL;
        goto RELEASE_DATA;
    }

    if (HdfSbufWriteString(data, ifname)) {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_GET_ADDR, data, reply);
    } else {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    }
    if (ret) {
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
    uint32_t replayDataSize = 0;
    const uint8_t *replayData = 0;
    if (!HdfSbufReadBuffer(reply, (const void **)(&replayData), &replayDataSize) || replayDataSize != ETH_ADDR_LEN) {
        wpa_printf(MSG_ERROR, "WifiWpaCmdGetOwnMac fail or data size mismatch");
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
    if (memcpy_s(buf, len, replayData, replayDataSize) != EOK) {
        wpa_printf(MSG_ERROR, "%s memcpy failed", __func__);
        ret = -EFAIL;
    }

RELEASE_DATA:
    HdfSBufRecycle(reply);
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdGetHwFeature(const char *ifname, WifiHwFeatureData *hwFeatureData)
{
    if (ifname == NULL || hwFeatureData == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    struct HdfSBuf *reply = HdfSBufObtainDefaultSize();
    int32_t ret = SUCC;
    if (data == NULL || reply == NULL) {
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
    if (HdfSbufWriteString(data, ifname)) {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_GET_HW_FEATURE, data, reply);
    } else {
        ret = -EFAIL;
    }
    if (ret) {
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
    const WifiHwFeatureData *respFeaturenData = NULL;
    uint32_t dataSize = 0;
    if (!HdfSbufReadBuffer(reply, (const void **)(&respFeaturenData), &dataSize) ||
        dataSize != sizeof(WifiHwFeatureData)) {
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
    if (memcpy_s(hwFeatureData, sizeof(WifiHwFeatureData), respFeaturenData, dataSize) != EOK) {
        wpa_printf(MSG_ERROR, "%s memcpy failed", __func__);
        ret = -EFAIL;
        goto RELEASE_DATA;
    }
RELEASE_DATA:
    HdfSBufRecycle(reply);
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdScan(const char *ifname, WifiScan *scan)
{
    int32_t ret;

    if (ifname == NULL || scan == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    if (scan->bssid == NULL) {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, scan->bssid, 0);
    } else {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, scan->bssid, ETH_ADDR_LEN);
    }
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, scan->ssids, sizeof(scan->ssids[0]) * scan->numSsids);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, scan->extraIes, scan->extraIesLen);
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, scan->freqs, sizeof(scan->freqs[0]) * scan->numFreqs);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint8(data, scan->prefixSsidScanFlag);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint8(data, scan->fastConnectFlag);
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_SCAN, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdDisconnet(const char *ifname, int32_t reasonCode)
{
    if (ifname == NULL) {
        return -EFAIL;
    }

    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint16(data, reasonCode);
    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_DISCONNECT, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdAssoc(const char *ifname, WifiAssociateParams *assocParams)
{
    if (ifname == NULL || assocParams == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    if (assocParams->bssid == NULL) {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, assocParams->bssid, 0);
    } else {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, assocParams->bssid, ETH_ADDR_LEN);
    }
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, assocParams->ssid, assocParams->ssidLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, assocParams->ie, assocParams->ieLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, assocParams->key, assocParams->keyLen);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint8(data, assocParams->authType);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint8(data, assocParams->privacy);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint8(data, assocParams->keyIdx);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint8(data, assocParams->mfp);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteUint32(data, assocParams->freq);
    isSerializeFailed =
        isSerializeFailed || !HdfSbufWriteBuffer(data, assocParams->crypto, sizeof(assocParams->crypto[0]));
    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_ASSOC, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdSetMaxStaNum(const char *ifname, void *buf, uint32_t len)
{
    if (ifname == NULL || buf == NULL) {
        return -EFAIL;
    }
    (void)len;
    return SUCC;
}

int32_t WifiWpaCmdSetNetdev(const char *ifname, WifiSetNewDev *info)
{
    if (ifname == NULL || info == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, info, sizeof(WifiSetNewDev));
    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_SET_NETDEV, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdStaRemove(const char *ifname, const uint8_t *addr, uint32_t addrLen)
{
    if (ifname == NULL || addr == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, addr, addrLen);
    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_STA_REMOVE, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

int32_t WifiWpaCmdSendAction(const char *ifname, WifiActionData *actionData)
{
    if (ifname == NULL || actionData == NULL) {
        return -EFAIL;
    }
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        return -EFAIL;
    }
    bool isSerializeFailed = false;
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteString(data, ifname);
    if (actionData->bssid == NULL) {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->bssid, 0);
    } else {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->bssid, ETH_ADDR_LEN);
    }
    if (actionData->dst == NULL) {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->dst, 0);
    } else {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->dst, ETH_ADDR_LEN);
    }
    if (actionData->src == NULL) {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->src, 0);
    } else {
        isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->src, ETH_ADDR_LEN);
    }
    isSerializeFailed = isSerializeFailed || !HdfSbufWriteBuffer(data, actionData->data, actionData->dataLen);
    int32_t ret;
    if (isSerializeFailed) {
        wpa_printf(MSG_ERROR, "Serialize failed!");
        ret = -EFAIL;
    } else {
        ret = WifiWpaCmdBlockSyncSend(WIFI_WPA_CMD_SEND_ACTION, data, NULL);
    }
    HdfSBufRecycle(data);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
