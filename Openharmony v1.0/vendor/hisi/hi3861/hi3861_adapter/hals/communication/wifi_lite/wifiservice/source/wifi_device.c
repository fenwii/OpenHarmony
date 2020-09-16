/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "wifi_device.h"

#include <securec.h>
#include <stdio.h>
#include <stdlib.h>

#include "wifi_device_util.h"
#include "wifi_hotspot_config.h"

#define WIFI_RECONN_POLICY_ENABLE        1
#define WIFI_RECONN_POLICY_TIMEOUT       60
#define WIFI_RECONN_POLICY_PERIOD        600
#define WIFI_RECONN_POLICY_MAX_TRY_COUNT 3
#define WIFI_DISCONNECT_REASON_NO_AP     1
#define WIFI_DEFAULT_KEY_FOR_PSK    "wifipskmode"

static int g_wifiStaStatus = WIFI_STA_NOT_ACTIVE;
static WifiDeviceConfig g_wifiConfigs[WIFI_MAX_CONFIG_SIZE] = {{{0}, {0}, {0}, 0, WIFI_CONFIG_INVALID, 0, 0}};
static WifiEvent* g_wifiEvents[WIFI_MAX_EVENT_SIZE] = {0};
static int g_connectState = WIFI_STATE_NOT_AVALIABLE;

static void DispatchScanStateChangeEvent(const hi_wifi_event* hisiEvent,
    const WifiEvent* hosEvent, WifiEventState event)
{
    if (hosEvent->OnWifiScanStateChanged == NULL) {
        return;
    }

    int size = 0;
    if (event == WIFI_STATE_NOT_AVALIABLE) {
        hosEvent->OnWifiScanStateChanged(event, size);
        return;
    }

    if (hisiEvent->event == HI_WIFI_EVT_SCAN_DONE) {
        size = hisiEvent->info.wifi_scan_done.bss_num;
        hosEvent->OnWifiScanStateChanged(event, size);
    }
}

static void DispatchConnectEvent(const hi_wifi_event* hisiEvent, const WifiEvent* hosEvent)
{
    if (hosEvent->OnWifiConnectionChanged == NULL) {
        return;
    }

    int cpyErr;
    WifiLinkedInfo info = {0};

    if (hisiEvent->event == HI_WIFI_EVT_CONNECTED) {
        g_connectState = WIFI_STATE_AVALIABLE;
        cpyErr = memcpy_s(&info.ssid, WIFI_MAX_SSID_LEN,
            hisiEvent->info.wifi_connected.ssid, HI_WIFI_MAX_SSID_LEN + 1);
        if (cpyErr != EOK) {
            printf("[wifi_service]:DispatchConnectEvent memcpy failed, err = %d\n", cpyErr);
            return;
        }

        cpyErr = memcpy_s(&info.bssid, WIFI_MAC_LEN,
            hisiEvent->info.wifi_connected.bssid, HI_WIFI_MAC_LEN);
        if (cpyErr != EOK) {
            printf("[wifi_service]:DispatchConnectEvent memcpy failed, err = %d\n", cpyErr);
            return;
        }

        hosEvent->OnWifiConnectionChanged(WIFI_STATE_AVALIABLE, &info);
        return;
    }

    if (hisiEvent->event == HI_WIFI_EVT_STA_FCON_NO_NETWORK && g_connectState == WIFI_STATE_AVALIABLE) {
        return;
    }

    info.disconnectedReason = WIFI_DISCONNECT_REASON_NO_AP;

    if (hisiEvent->event == HI_WIFI_EVT_DISCONNECTED) {
        cpyErr = memcpy_s(&info.bssid, WIFI_MAC_LEN,
            hisiEvent->info.wifi_disconnected.bssid, HI_WIFI_MAC_LEN);
        if (cpyErr != EOK) {
            printf("[wifi_service]:DispatchConnectEvent memcpy failed, err = %d\n", cpyErr);
            return;
        }
        info.disconnectedReason = hisiEvent->info.wifi_disconnected.reason_code;
    }

    hosEvent->OnWifiConnectionChanged(WIFI_STATE_NOT_AVALIABLE, &info);
}

static void DispatchStaConnectEvent(const hi_wifi_event* hisiEvent, const WifiEvent* hosEvent)
{
    int cpyErr;
    StationInfo info = {0};
    if (hisiEvent->event == HI_WIFI_EVT_STA_CONNECTED) {
        if (hosEvent->OnHotspotStaJoin == NULL) {
            return;
        }

        cpyErr = memcpy_s(&info.macAddress, WIFI_MAC_LEN,
            hisiEvent->info.ap_sta_connected.addr, HI_WIFI_MAC_LEN);
        if (cpyErr != EOK) {
            printf("[wifi_service]:DispatchStaConnectEvent memcpy failed, err = %d\n", cpyErr);
            return;
        }

        hosEvent->OnHotspotStaJoin(&info);
        return;
    }

    if (hosEvent->OnHotspotStaLeave == NULL) {
        return;
    }

    cpyErr = memcpy_s(&info.macAddress, WIFI_MAC_LEN,
        hisiEvent->info.ap_sta_disconnected.addr, HI_WIFI_MAC_LEN);
    if (cpyErr != EOK) {
        printf("[wifi_service]:DispatchStaConnectEvent memcpy failed, err = %d\n", cpyErr);
        return;
    }
    info.disconnectedReason = hisiEvent->info.ap_sta_disconnected.reason_code;
    hosEvent->OnHotspotStaLeave(&info);
}

static void DispatchApStartEvent(const WifiEvent* hosEvent)
{
    if (hosEvent->OnHotspotStateChanged == NULL) {
        return;
    }

    hosEvent->OnHotspotStateChanged(WIFI_STATE_AVALIABLE);
}

static void DispatchEvent(const hi_wifi_event* hisiEvent, const WifiEvent* hosEvent)
{
    switch (hisiEvent->event) {
        case HI_WIFI_EVT_SCAN_DONE:
            DispatchScanStateChangeEvent(hisiEvent, hosEvent, WIFI_STATE_AVALIABLE);
            break;
        case HI_WIFI_EVT_CONNECTED:
        case HI_WIFI_EVT_DISCONNECTED:
        case HI_WIFI_EVT_STA_FCON_NO_NETWORK:
            DispatchConnectEvent(hisiEvent, hosEvent);
            break;
        case HI_WIFI_EVT_STA_CONNECTED:
        case HI_WIFI_EVT_STA_DISCONNECTED:
            DispatchStaConnectEvent(hisiEvent, hosEvent);
            break;
        case HI_WIFI_EVT_AP_START:
            DispatchApStartEvent(hosEvent);
            break;
        default:
            // event not supported in current version, do nothing
            break;
    }
}

static void HiWifiWpaEventCb(const hi_wifi_event *hisiEvent)
{
    if (hisiEvent == NULL) {
        return;
    }
    if (LockWifiEventLock() != WIFI_SUCCESS) {
        return;
    }
    for (int i = 0; i < WIFI_MAX_EVENT_SIZE; i++) {
        if (g_wifiEvents[i] == NULL) {
            continue;
        }
        DispatchEvent(hisiEvent, g_wifiEvents[i]);
    }
    if (UnlockWifiEventLock() != WIFI_SUCCESS) {
        return;
    }
}

static void RegisterHisiCallback(void)
{
    int hiRet = hi_wifi_register_event_callback(HiWifiWpaEventCb);
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:RegisterHisiCallback register callback failed\n");
    }
    hiRet = hi_wifi_config_callback(1, 0, 0);
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:ConfigHisiCallback failed\n");
    }
}

WifiErrorCode EnableWifi(void)
{
    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    if (g_wifiStaStatus == WIFI_STA_ACTIVE) {
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_BUSY;
    }

    char ifName[WIFI_IFNAME_MAX_SIZE + 1] = {0};
    int len = sizeof(ifName);
    int hiRet;

    hiRet = hi_wifi_sta_start(ifName, &len);
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:EnableWifi sta start fail\n");
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_NOT_STARTED;
    }

    hiRet = hi_wifi_sta_set_reconnect_policy(WIFI_RECONN_POLICY_ENABLE, WIFI_RECONN_POLICY_TIMEOUT,
        WIFI_RECONN_POLICY_PERIOD, WIFI_RECONN_POLICY_MAX_TRY_COUNT);
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:EnableWifi set reconn policy fail\n");
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_UNKNOWN;
    }

    g_wifiStaStatus = WIFI_STA_ACTIVE;
    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    return WIFI_SUCCESS;
}

WifiErrorCode DisableWifi(void)
{
    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    if (g_wifiStaStatus == WIFI_STA_NOT_ACTIVE) {
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_NOT_STARTED;
    }

    int hiRet;

    hiRet = hi_wifi_sta_stop();
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:DisableWifi failed to stop sta\n");
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_NOT_STARTED;
    }

    g_wifiStaStatus = WIFI_STA_NOT_ACTIVE;
    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    return WIFI_SUCCESS;
}

int IsWifiActive(void)
{
    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    int ret = g_wifiStaStatus;

    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    return ret;
}

WifiErrorCode Scan(void)
{
    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    if (g_wifiStaStatus == WIFI_STA_NOT_ACTIVE) {
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_NOT_STARTED;
    }
    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    if (LockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    for (int i = 0; i < WIFI_MAX_EVENT_SIZE; i++) {
        if (g_wifiEvents[i] == NULL) {
            continue;
        }
        DispatchScanStateChangeEvent(NULL, g_wifiEvents[i], WIFI_STATE_NOT_AVALIABLE);
    }
    if (UnlockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    int hiRet;

    hiRet = hi_wifi_sta_scan();
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:Scan failed to start sta scan\n");
        return ERROR_WIFI_UNKNOWN;
    }

    return WIFI_SUCCESS;
}

static hi_wifi_scan_type ScanTypeSwitch(WifiScanType type)
{
    hi_wifi_scan_type ret = HI_WIFI_BASIC_SCAN;

    switch (type) {
        case WIFI_FREQ_SCAN:
            ret = HI_WIFI_CHANNEL_SCAN;
            break;
        case WIFI_SSID_SCAN:
            ret = HI_WIFI_SSID_SCAN;
            break;
        case WIFI_BSSID_SCAN:
            ret = HI_WIFI_BSSID_SCAN;
            break;
        default:
            break;
    }

    return ret;
}

WifiErrorCode AdvanceScan(WifiScanParams *params)
{
    if (params == NULL) {
        return ERROR_WIFI_UNKNOWN;
    }

    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    if (g_wifiStaStatus == WIFI_STA_NOT_ACTIVE) {
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
            return ERROR_WIFI_NOT_STARTED;
    }

    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    if (LockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    for (int i = 0; i < WIFI_MAX_EVENT_SIZE; i++) {
        if (g_wifiEvents[i] == NULL) {
            continue;
        }
        DispatchScanStateChangeEvent(NULL, g_wifiEvents[i], WIFI_STATE_NOT_AVALIABLE);
    }
    if (UnlockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    int hiRet;
    int cpyErr;
    hi_wifi_scan_params sp = {0};

    cpyErr = memcpy_s(sp.ssid, sizeof(sp.ssid), params->ssid, params->ssidLen);
    if (cpyErr != EOK) {
        return ERROR_WIFI_UNKNOWN;
    }
    cpyErr = memcpy_s(sp.bssid, sizeof(sp.bssid), params->bssid, sizeof(params->bssid));
    if (cpyErr != EOK) {
        return ERROR_WIFI_UNKNOWN;
    }
    sp.ssid_len = params->ssidLen;
    sp.scan_type = ScanTypeSwitch(params->scanType);
    sp.channel = FrequencyToChannel(params->freqs);

    hiRet = hi_wifi_sta_advance_scan(&sp);
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:Advance Scan failed\n");
        return ERROR_WIFI_UNKNOWN;
    }

    return WIFI_SUCCESS;
}

WifiErrorCode GetScanInfoList(WifiScanInfo* result, unsigned int* size)
{
    if (result == NULL || size == NULL || *size == 0) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    unsigned int num = WIFI_SCAN_HOTSPOT_LIMIT;

    hi_wifi_ap_info *pstResults = malloc(sizeof(hi_wifi_ap_info) * WIFI_SCAN_HOTSPOT_LIMIT);
    if (pstResults == NULL) {
        return ERROR_WIFI_UNKNOWN;
    }

    int hiRet = hi_wifi_sta_scan_results(pstResults, &num);
    if (hiRet != HISI_OK) {
        printf("[wifi_service]:GetScanInfoList hi_wifi_sta_scan_results fail\n");
        free(pstResults);
        return ERROR_WIFI_UNKNOWN;
    }

    if (*size < num) {
        free(pstResults);
        return ERROR_WIFI_INVALID_ARGS;
    }

    int cpyErr;
    for (unsigned int i = 0; i < num; i++) {
        cpyErr = memcpy_s(result[i].ssid, WIFI_MAX_SSID_LEN, pstResults[i].ssid, HI_WIFI_MAX_SSID_LEN + 1);
        if (cpyErr != EOK) {
            free(pstResults);
            printf("[wifi_service]:GetScanInfoList memcpy failed, err = %d\n", cpyErr);
            return ERROR_WIFI_UNKNOWN;
        }

        cpyErr = memcpy_s(result[i].bssid, WIFI_MAC_LEN, pstResults[i].bssid, HI_WIFI_MAC_LEN);
        if (cpyErr != EOK) {
            free(pstResults);
            printf("[wifi_service]:GetScanInfoList memcpy failed, err = %d\n", cpyErr);
            return ERROR_WIFI_UNKNOWN;
        }

        result[i].securityType = HiSecToHoSec(pstResults[i].auth);
        result[i].rssi = pstResults[i].rssi;
        result[i].frequency = ChannelToFrequency(pstResults[i].channel);
    }

    free(pstResults);
    *size = num;

    return WIFI_SUCCESS;
}

WifiErrorCode AddDeviceConfig(const WifiDeviceConfig* config, int* result)
{
    if (config == NULL || result == NULL) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    int netId = WIFI_CONFIG_INVALID;
    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    for (int i = 0; i < WIFI_MAX_CONFIG_SIZE; i++) {
        if (g_wifiConfigs[i].netId != i) {
            netId = i;
            break;
        }
    }

    if (netId == WIFI_CONFIG_INVALID) {
        printf("[wifi_service]:AddDeviceConfig wifi config is full, delete one first\n");
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_BUSY;
    }

    int cpyErr = memcpy_s(&g_wifiConfigs[netId], sizeof(WifiDeviceConfig), config, sizeof(WifiDeviceConfig));
    if (cpyErr != EOK) {
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        printf("[wifi_service]:AddDeviceConfig memcpy failed, err = %d\n", cpyErr);
        return ERROR_WIFI_UNKNOWN;
    }

    g_wifiConfigs[netId].netId = netId;
    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    *result = netId;
    return WIFI_SUCCESS;
}

WifiErrorCode GetDeviceConfigs(WifiDeviceConfig* result, unsigned int* size)
{
    if (result == NULL || size == NULL || *size == 0) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    unsigned int retIndex = 0;

    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    for (int i = 0; i < WIFI_MAX_CONFIG_SIZE; i++) {
        if (g_wifiConfigs[i].netId != i) {
            continue;
        }

        int cpyErr = memcpy_s(&result[retIndex], sizeof(WifiDeviceConfig), &g_wifiConfigs[i], sizeof(WifiDeviceConfig));
        if (cpyErr != EOK) {
            if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
                return ERROR_WIFI_UNKNOWN;
            }
            printf("[wifi_service]:GetDeviceConfig memcpy failed, err = %d\n", cpyErr);
            return ERROR_WIFI_UNKNOWN;
        }

        retIndex++;
        if (*size < retIndex) {
            if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
                return ERROR_WIFI_UNKNOWN;
            }
            return ERROR_WIFI_INVALID_ARGS;
        }
    }

    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    if (retIndex == 0) {
        return ERROR_WIFI_NOT_AVAILABLE;
    }

    *size = retIndex;
    return WIFI_SUCCESS;
}

static WifiErrorCode StaConnect(unsigned int chan, hi_wifi_assoc_request *assocReq, int pskType)
{
    int hiRet = 0;
    int lastState = g_connectState;

    g_connectState = WIFI_STATE_NOT_AVALIABLE;
    if (chan == 0) {
        hiRet = hi_wifi_sta_connect(assocReq);
    } else {
        hi_wifi_fast_assoc_request fastReq = {0};
        fastReq.channel = chan;
        hiRet += memcpy_s(&fastReq.req, sizeof(hi_wifi_assoc_request), assocReq, sizeof(hi_wifi_assoc_request));
        if (pskType == WIFI_PSK_TYPE_HEX) {
            hiRet += memcpy_s(fastReq.req.key, sizeof(fastReq.req.key),
                WIFI_DEFAULT_KEY_FOR_PSK, sizeof(WIFI_DEFAULT_KEY_FOR_PSK));
            hiRet += memcpy_s(fastReq.psk, sizeof(fastReq.psk), assocReq->key, HI_WIFI_STA_PSK_LEN);
            fastReq.psk_flag = HI_WIFI_WPA_PSK_USE_OUTER;
        }
        if (hiRet != EOK) {
            printf("[wifi_service]:StaConnect memcpy failed, err = %d\n", hiRet);
            g_connectState = lastState;
            return ERROR_WIFI_UNKNOWN;
        }
        hiRet = hi_wifi_sta_fast_connect(&fastReq);
        if (memset_s(&fastReq, sizeof(hi_wifi_fast_assoc_request), 0, sizeof(hi_wifi_fast_assoc_request)) != EOK) {
            printf("[wifi_service]:StaConnect memset failed\n");
        }
    }
    if (memset_s(assocReq, sizeof(hi_wifi_assoc_request), 0, sizeof(hi_wifi_assoc_request)) != EOK) {
        printf("[wifi_service]:StaConnect memset failed\n");
    }
    if (hiRet != HISI_OK) {
        g_connectState = lastState;
        return ERROR_WIFI_UNKNOWN;
    }

    return WIFI_SUCCESS;
}

WifiErrorCode ConnectTo(int networkId)
{
    if (networkId >= WIFI_MAX_CONFIG_SIZE || networkId < 0) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    if (g_wifiConfigs[networkId].netId != networkId) {
        if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_NOT_AVAILABLE;
    }

    hi_wifi_assoc_request assocReq = {0};
    assocReq.auth = HoSecToHiSec(g_wifiConfigs[networkId].securityType);

    int cpyErr = memcpy_s(assocReq.ssid, sizeof(assocReq.ssid),
        g_wifiConfigs[networkId].ssid, sizeof(g_wifiConfigs[networkId].ssid));
    cpyErr += memcpy_s(assocReq.key, sizeof(assocReq.key),
        g_wifiConfigs[networkId].preSharedKey, sizeof(g_wifiConfigs[networkId].preSharedKey));
    cpyErr += memcpy_s(assocReq.bssid, sizeof(assocReq.bssid),
        g_wifiConfigs[networkId].bssid, sizeof(g_wifiConfigs[networkId].bssid));
    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    if (cpyErr != EOK) {
        printf("[wifi_service]:ConnectTo memcpy failed, err = %d\n", cpyErr);
        return ERROR_WIFI_UNKNOWN;
    }

    unsigned int chan = FrequencyToChannel(g_wifiConfigs[networkId].freq);
    if (LockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    if (StaConnect(chan, &assocReq, g_wifiConfigs[networkId].wapiPskType) != WIFI_SUCCESS) {
        if (UnlockWifiEventLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_UNKNOWN;
    }
    if (UnlockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    return WIFI_SUCCESS;
}

WifiErrorCode Disconnect(void)
{
    int hiRet = hi_wifi_sta_disconnect();
    if (hiRet != HISI_OK) {
        return ERROR_WIFI_UNKNOWN;
    }
    return WIFI_SUCCESS;
}

WifiErrorCode RemoveDevice(int networkId)
{
    if (networkId >= WIFI_MAX_CONFIG_SIZE || networkId < 0) {
        return ERROR_WIFI_INVALID_ARGS;
    }
    if (LockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    if (memset_s(&g_wifiConfigs[networkId], sizeof(WifiDeviceConfig),
        0, sizeof(WifiDeviceConfig)) != EOK) {
        printf("[wifi_service]:removeDevice memset failed\n");
    }
    g_wifiConfigs[networkId].netId = WIFI_CONFIG_INVALID;
    if (UnlockWifiGlobalLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    return WIFI_SUCCESS;
}

WifiErrorCode GetLinkedInfo(WifiLinkedInfo* result)
{
    if (result == NULL) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    hi_wifi_status connectStatus = {0};
    int hiRet = hi_wifi_sta_get_connect_info(&connectStatus);
    if (hiRet != HISI_OK) {
        return ERROR_WIFI_UNKNOWN;
    }

    int cpyErr = memcpy_s(result->ssid, WIFI_MAX_SSID_LEN, connectStatus.ssid, HI_WIFI_MAX_SSID_LEN + 1);
    if (cpyErr != EOK) {
        printf("[wifi_service]:GetLinkedInfo memcpy failed, err = %d\n", cpyErr);
        return ERROR_WIFI_UNKNOWN;
    }

    cpyErr = memcpy_s(result->bssid, WIFI_MAC_LEN, connectStatus.bssid, HI_WIFI_MAC_LEN);
    if (cpyErr != EOK) {
        printf("[wifi_service]:GetLinkedInfo memcpy failed, err = %d\n", cpyErr);
        return ERROR_WIFI_UNKNOWN;
    }

    if (connectStatus.status == HI_WIFI_CONNECTED) {
        result->connState = WIFI_CONNECTED;
        result->rssi = hi_wifi_sta_get_ap_rssi();
    } else {
        result->connState = WIFI_DISCONNECTED;
    }

    return WIFI_SUCCESS;
}


WifiErrorCode RegisterWifiEvent(WifiEvent* event)
{
    if (event == NULL) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    int emptySlot = WIFI_CONFIG_INVALID;

    if (LockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    for (int i = 0; i < WIFI_MAX_EVENT_SIZE; i++) {
        if (g_wifiEvents[i] == event) {
            if (UnlockWifiEventLock() != WIFI_SUCCESS) {
                return ERROR_WIFI_UNKNOWN;
            }
            return ERROR_WIFI_INVALID_ARGS;
        }

        if (g_wifiEvents[i] != NULL) {
            continue;
        }

        emptySlot = i;
        break;
    }

    if (emptySlot == WIFI_CONFIG_INVALID) {
        if (UnlockWifiEventLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return ERROR_WIFI_BUSY;
    }

    g_wifiEvents[emptySlot] = event;
    if (UnlockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    RegisterHisiCallback();

    return WIFI_SUCCESS;
}

WifiErrorCode UnRegisterWifiEvent(const WifiEvent* event)
{
    if (event == NULL) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    if (LockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }

    for (int i = 0; i < WIFI_MAX_EVENT_SIZE; i++) {
        if (g_wifiEvents[i] != event) {
            continue;
        }

        g_wifiEvents[i] = 0;

        if (UnlockWifiEventLock() != WIFI_SUCCESS) {
            return ERROR_WIFI_UNKNOWN;
        }
        return WIFI_SUCCESS;
    }

    if (UnlockWifiEventLock() != WIFI_SUCCESS) {
        return ERROR_WIFI_UNKNOWN;
    }
    return ERROR_WIFI_UNKNOWN;
}

WifiErrorCode GetDeviceMacAddress(unsigned char* result)
{
    if (result == NULL) {
        return ERROR_WIFI_INVALID_ARGS;
    }

    int hiRet = hi_wifi_get_macaddr((char*)result, WIFI_MAC_LEN);
    if (hiRet != HISI_OK) {
        return ERROR_WIFI_UNKNOWN;
    }
    return WIFI_SUCCESS;
}
