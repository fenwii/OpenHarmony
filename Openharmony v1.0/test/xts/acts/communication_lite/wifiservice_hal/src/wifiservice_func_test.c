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

#include "hctest.h"
#include "hos_types.h"
#include "wifi_device.h"
#include "wifi_hotspot.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "lwip/ip4_addr.h"
#include "cmsis_os2.h"
#include <unistd.h>

#define DEF_TIMEOUT 15
#define ONE_SECOND 1
#define LEVEL_ERROR (-1)
#define LEVEL_ONE 1
#define LEVEL_TWO 2
#define LEVEL_THREE 3
#define LEVEL_FOUR 4
#define DEF_TASK_STACK 2000
#define DEF_TASK_PRIORITY 20
#define DEPE_AP_SSID "xts_execute"
#define DEF_NET_IF "wlan0"

static int g_apEnableSuccess = 0;
static int g_staScanSuccess = 0;
struct netif *g_wsNetInterface = NULL;
WifiEvent g_wifiEventHandler = {0};

/**
 * callback task for wifi scan
 */
static void WifiScanStateTask(void)
{
    WifiScanInfo* info = malloc(sizeof(WifiScanInfo) * WIFI_SCAN_HOTSPOT_LIMIT);
    if (info == NULL) {
        printf("WifiScanStateTask:malloc fail.\n");
        return;
    }
    unsigned int checkSize = WIFI_SCAN_HOTSPOT_LIMIT;
    WifiErrorCode error = GetScanInfoList(info, &checkSize);
    if (error != WIFI_SUCCESS) {
        printf("WifiScanStateTask:get info fail, error is %d.\n", error);
    } else {
        printf("WifiScanStateTask:get scan size is %d.\n", checkSize);
        g_staScanSuccess = 1;
    }
    free(info);
    info = NULL;
}

/**
 * callback task for connection
 */
static void WifiConnectionStateTask(void)
{
    WifiLinkedInfo linkInfo = {0};
    WifiErrorCode error = GetLinkedInfo(&linkInfo);
    if (error != WIFI_SUCCESS) {
        printf("WifiConnectionChanged:get link info fail, error is %d.\n", error);
        return;
    }
    if (linkInfo.connState != WIFI_CONNECTED) {
        printf("WifiConnectionChanged:connect fail!\n");
        return;
    }
    printf("WifiConnectionChanged:connect success.\n");
}

/**
 * callback function for hotspot
 */
static void HotspotStateTask(void)
{
    StationInfo info[WIFI_MAX_STA_NUM] = {0};
    unsigned int size = WIFI_MAX_STA_NUM;
    WifiErrorCode error = GetStationList(info, &size);
    if (error != WIFI_SUCCESS) {
        printf("HotspotStaJoin:get list fail, error is %d.\n", error);
        return;
    }
    printf("HotspotStaJoin:list size is %d.\n", size);
    g_apEnableSuccess++;
}

/**
 * callback function for wifi scan
 */
static void OnWifiScanStateChangedHandler(int state, int size)
{
    if (state != WIFI_STATE_AVALIABLE) {
        printf("ScanStateChanged:state is unavaliable.\n");
    } else {
        printf("ScanStateChanged:state[%d], size[%d].\n", state, size);
        osThreadAttr_t attr;
        attr.name = "WifiScanStateTask";
        attr.attr_bits = 0U;
        attr.cb_mem = NULL;
        attr.cb_size = 0U;
        attr.stack_mem = NULL;
        attr.stack_size = DEF_TASK_STACK;
        attr.priority = DEF_TASK_PRIORITY;
        if (osThreadNew((osThreadFunc_t)WifiScanStateTask, NULL, &attr) == NULL) {
            printf("ScanStateChanged:create task fail!\n");
        }
    }
}

/**
 * callback function for wifi connection
 */
static void OnWifiConnectionChangedHandler(int state, WifiLinkedInfo* info)
{
    if (info == NULL) {
        printf("WifiConnectionChanged:info is null, stat is %d.\n", state);
    } else {
        osThreadAttr_t attr;
        attr.name = "WifiConnectionStateTask";
        attr.attr_bits = 0U;
        attr.cb_mem = NULL;
        attr.cb_size = 0U;
        attr.stack_mem = NULL;
        attr.stack_size = DEF_TASK_STACK;
        attr.priority = DEF_TASK_PRIORITY;
        if (osThreadNew((osThreadFunc_t)WifiConnectionStateTask, NULL, &attr) == NULL) {
            printf("WifiConnectionStateTask:create task fail!\n");
        }
    }
}

/**
 * callback function for STA join AP
 */
static void OnHotspotStaJoinHandler(StationInfo* info)
{
    if (info == NULL) {
        printf("HotspotStaJoin:info is null.\n");
    }  else {
        osThreadAttr_t attr;
        attr.name = "HotspotStateTask";
        attr.attr_bits = 0U;
        attr.cb_mem = NULL;
        attr.cb_size = 0U;
        attr.stack_mem = NULL;
        attr.stack_size = DEF_TASK_STACK;
        attr.priority = DEF_TASK_PRIORITY;
        if (osThreadNew((osThreadFunc_t)HotspotStateTask, NULL, &attr) == NULL) {
            printf("HotspotStaJoin:create task fail!\n");
        }
    }
}

/**
 * callback function for STA leave AP
 */
static void OnHotspotStaLeaveHandler(StationInfo* info)
{
    if (info == NULL) {
        printf("HotspotStaLeave:info is null.\n");
    } else {
        g_apEnableSuccess--;
    }
}

/**
 * callback function for AP
 */
static void OnHotspotStateChangedHandler(int state)
{
    printf("HotspotStateChanged:state is %d.\n", state);
}

/**
 * common wait scan result
 */
static void WaitSacnResult(void)
{
    int scanTimeout = DEF_TIMEOUT;
    while (scanTimeout > 0) {
        sleep(ONE_SECOND);
        scanTimeout--;
        if (g_staScanSuccess == 1) {
            printf("WaitSacnResult:wait success[%d]s\n", (DEF_TIMEOUT - scanTimeout));
            break;
        }
    }
    if (scanTimeout <= 0) {
        printf("WaitSacnResult:timeout!\n");
    }
}

/**
 * @tc.desc      : register a test suite, this test suite is used to test basic functions
 * @param        : subsystem name is communication
 * @param        : module name is wifiaware
 * @param        : test suit name is WifiAwareReliTestSuite
 */
LITE_TEST_SUIT(communication, wifiservice, WifiServiceFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL WifiServiceFuncTestSuiteSetUp(void)
{
    g_wifiEventHandler.OnWifiScanStateChanged = OnWifiScanStateChangedHandler;
    g_wifiEventHandler.OnWifiConnectionChanged = OnWifiConnectionChangedHandler;
    g_wifiEventHandler.OnHotspotStaJoin = OnHotspotStaJoinHandler;
    g_wifiEventHandler.OnHotspotStaLeave = OnHotspotStaLeaveHandler;
    g_wifiEventHandler.OnHotspotStateChanged = OnHotspotStateChangedHandler;
    WifiErrorCode error = RegisterWifiEvent(&g_wifiEventHandler);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    if (error != WIFI_SUCCESS) {
        return FALSE;
    }
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL WifiServiceFuncTestSuiteTearDown(void)
{
    WifiErrorCode error = UnRegisterWifiEvent(&g_wifiEventHandler);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    printf("+-------------------------------------------+\n");
    if (error != WIFI_SUCCESS) {
        return FALSE;
    }
    return TRUE;
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0100
 * @tc.name      : Test enable and disable wifi interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testEnableDisableWifi, LEVEL2)
{
    int stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);

    WifiErrorCode error = EnableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_AVALIABLE);

    error = EnableWifi();
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_BUSY);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_AVALIABLE);

    error = DisableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);

    error = DisableWifi();
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_NOT_STARTED);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0200
 * @tc.name      : Test scan and get scan info interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testScan, LEVEL2)
{
    unsigned int size = WIFI_SCAN_HOTSPOT_LIMIT;
    WifiErrorCode error = EnableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    int stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_AVALIABLE);

    WifiScanInfo* info = malloc(sizeof(WifiScanInfo) * WIFI_SCAN_HOTSPOT_LIMIT);
    TEST_ASSERT_NOT_NULL(info);
    error = GetScanInfoList(info, &size);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(size, 0);

    g_staScanSuccess = 0;
    error = Scan();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    WaitSacnResult();
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 1);

    size = WIFI_SCAN_HOTSPOT_LIMIT;
    error = GetScanInfoList(info, &size);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_NOT_EQUAL(size, WIFI_SCAN_HOTSPOT_LIMIT);
    free(info);

    error = DisableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0300
 * @tc.name      : Test connect and disconnect interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testConnectDisConnect, LEVEL2)
{
    int netId = 0;
    int ssidLen = 11;
    WifiErrorCode error;
    WifiDeviceConfig config = {0};
    int ret = memcpy_s(config.ssid, WIFI_MAX_SSID_LEN, "xts_execute", ssidLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    config.securityType = WIFI_SEC_TYPE_OPEN;
    error = AddDeviceConfig(&config, &netId);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);

    error = ConnectTo(netId);
    TEST_ASSERT_NOT_EQUAL(error, WIFI_SUCCESS);
    unsigned char mac[WIFI_MAC_LEN];
    error = GetDeviceMacAddress((unsigned char *)mac);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    error = Disconnect();
    TEST_ASSERT_NOT_EQUAL(error, WIFI_SUCCESS);
    error = RemoveDevice(netId);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0400
 * @tc.name      : Test handle device config interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testHandleDeviceConfig, LEVEL2)
{
    int netId = 0;
    int ssidLen = 11;
    int keyLen = 8;
    int freq = 20;
    unsigned char bssid[WIFI_MAC_LEN] = {0xac, 0x75, 0x1d, 0xd8, 0x55, 0xc1};
    WifiDeviceConfig config = {0};
    config.freq = freq;
    config.securityType = WIFI_SEC_TYPE_SAE;
    config.wapiPskType = WIFI_PSK_TYPE_ASCII;
    int ret = memcpy_s(config.ssid, WIFI_MAX_SSID_LEN, "XtsTestWifi", ssidLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    ret = memcpy_s(config.preSharedKey, WIFI_MAX_KEY_LEN, "12345678", keyLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    ret = memcpy_s(config.bssid, WIFI_MAC_LEN, bssid, WIFI_MAC_LEN);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    WifiErrorCode error = AddDeviceConfig(&config, &netId);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);

    ssidLen += 1;
    int addCount = 9;
    for (int i = 0; i < addCount; i++) {
        config.securityType = WIFI_SEC_TYPE_PSK;
        config.wapiPskType = WIFI_PSK_TYPE_HEX;
        ret = memcpy_s(config.ssid, WIFI_MAX_SSID_LEN, "XtsTestWifi2", ssidLen);
        TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
        ret = memcpy_s(config.preSharedKey, WIFI_MAX_KEY_LEN, "01234567", keyLen);
        TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
        error = AddDeviceConfig(&config, &netId);
        TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
        if (error != WIFI_SUCCESS) {
            printf("Add fail[%d].\n", i);
            break;
        }
    }

    ret = memcpy_s(config.ssid, WIFI_MAX_SSID_LEN, "XtsTestWifi3", ssidLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    ret = memcpy_s(config.preSharedKey, WIFI_MAX_KEY_LEN, "01234567", keyLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    config.securityType = WIFI_SEC_TYPE_PSK;
    error = AddDeviceConfig(&config, &netId);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_BUSY);

    WifiDeviceConfig allConfig[WIFI_MAX_CONFIG_SIZE] = {0};
    unsigned int size = WIFI_MAX_CONFIG_SIZE;
    error = GetDeviceConfigs(allConfig, &size);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(size, WIFI_MAX_CONFIG_SIZE);

    for (int i = 0; i < WIFI_MAX_CONFIG_SIZE; i++) {
        error = RemoveDevice(allConfig[i].netId);
        TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    }

    error = GetDeviceConfigs(allConfig, &size);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_NOT_AVAILABLE);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0500
 * @tc.name      : Test handle AP config interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testHandleHotspotConfig, LEVEL2)
{
    int keyLen = 9;
    int ssidLen = 10;
    HotspotConfig config = {0};
    int ret = memcpy_s(config.ssid, WIFI_MAX_SSID_LEN, "XtsTestAp", ssidLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    ret = memcpy_s(config.preSharedKey, WIFI_MAX_KEY_LEN, "12345678", keyLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    config.securityType = WIFI_SEC_TYPE_PSK;
    WifiErrorCode error = SetHotspotConfig(&config);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);

    HotspotConfig getConfig = {0};
    error = GetHotspotConfig(&getConfig);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(config.securityType, WIFI_SEC_TYPE_PSK);

    int band = 11;
    int bandOrig = 11;
    error = SetBand(band);
    TEST_ASSERT_NOT_EQUAL(error, WIFI_SUCCESS);
    error = GetBand(&band);
    TEST_ASSERT_NOT_EQUAL(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(band, bandOrig);

    error = SetBand(HOTSPOT_BAND_TYPE_2G);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    error = GetBand(&band);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(band, HOTSPOT_BAND_TYPE_2G);

    HotspotConfig getConfigAgain = {0};
    error = GetHotspotConfig(&getConfigAgain);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(getConfigAgain.band, HOTSPOT_BAND_TYPE_2G);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0600
 * @tc.name      : Test enable and disable AP interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testEnableDisableHotSpot, LEVEL2)
{
    int ssidLen = 10;
    int keyLen = 9;
    HotspotConfig config = {0};
    int ret = memcpy_s(config.ssid, WIFI_MAX_SSID_LEN, "XtsTestAp", ssidLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    ret = memcpy_s(config.preSharedKey, WIFI_MAX_KEY_LEN, "12345678", keyLen);
    TEST_ASSERT_EQUAL_INT(ret, WIFI_SUCCESS);
    config.securityType = WIFI_SEC_TYPE_PSK;
    WifiErrorCode error = SetHotspotConfig(&config);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);

    int stat = IsHotspotActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_HOTSPOT_NOT_ACTIVE);
    error = EnableHotspot();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsHotspotActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_HOTSPOT_ACTIVE);
    error = EnableHotspot();
    TEST_ASSERT_NOT_EQUAL(error, WIFI_SUCCESS);
    stat = IsHotspotActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_HOTSPOT_ACTIVE);

    int timeout = 3;
    g_apEnableSuccess = 0;
    while (timeout > 0) {
        sleep(ONE_SECOND);
        timeout--;
        if (g_apEnableSuccess >= 1) {
            printf("Wait %d seconds.\n", (DEF_TIMEOUT - timeout));
            break;
        }
    }

    error = DisableHotspot();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsHotspotActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_HOTSPOT_NOT_ACTIVE);
    error = DisableHotspot();
    TEST_ASSERT_NOT_EQUAL(error, WIFI_SUCCESS);
    stat = IsHotspotActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_HOTSPOT_NOT_ACTIVE);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0700
 * @tc.name      : Test get signal Level interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testGetSignalLevel, LEVEL2)
{
    int level;
    int rssiNoLevel = -90;
    int rssiOf2gLevel1 = -88;
    int rssiOf2gLevel2 = -82;
    int rssiOf2gLevel3 = -75;
    int rssiOf5gLevel1 = -85;
    int rssiOf5gLevel2 = -79;
    int rssiOf5gLevel3 = -72;
    int rssiBothLevel4 = -65;

    level = GetSignalLevel(rssiNoLevel, HOTSPOT_BAND_TYPE_2G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_ERROR);
    level = GetSignalLevel(rssiOf2gLevel1, HOTSPOT_BAND_TYPE_2G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_ONE);
    level = GetSignalLevel(rssiOf2gLevel2, HOTSPOT_BAND_TYPE_2G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_TWO);
    level = GetSignalLevel(rssiOf2gLevel3, HOTSPOT_BAND_TYPE_2G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_THREE);
    level = GetSignalLevel(rssiBothLevel4, HOTSPOT_BAND_TYPE_2G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_FOUR);

    level = GetSignalLevel(rssiNoLevel, HOTSPOT_BAND_TYPE_5G);
    TEST_ASSERT_EQUAL_INT(level, -1);
    level = GetSignalLevel(rssiOf5gLevel1, HOTSPOT_BAND_TYPE_5G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_ONE);
    level = GetSignalLevel(rssiOf5gLevel2, HOTSPOT_BAND_TYPE_5G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_TWO);
    level = GetSignalLevel(rssiOf5gLevel3, HOTSPOT_BAND_TYPE_5G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_THREE);
    level = GetSignalLevel(rssiBothLevel4, HOTSPOT_BAND_TYPE_5G);
    TEST_ASSERT_EQUAL_INT(level, LEVEL_FOUR);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0800
 * @tc.name      : test adavance scan interface
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testAdvanceScanType, LEVEL2)
{
    WifiErrorCode error = EnableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    int stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_AVALIABLE);

    int freq = 2460;
    WifiScanParams scanParams = {0};
    char bssid[WIFI_MAC_LEN] = {0xac, 0x75, 0x1d, 0xd8, 0x55, 0xc1};
    strcpy_s(scanParams.ssid, sizeof(scanParams.ssid), "wifi_service_xts");
    scanParams.ssidLen = strlen(scanParams.ssid);
    scanParams.freqs = freq;
    memcpy_s(scanParams.bssid, sizeof(scanParams.bssid), bssid, sizeof(bssid));

    scanParams.scanType = WIFI_SSID_SCAN;
    g_staScanSuccess = 0;
    error = AdvanceScan(&scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    WaitSacnResult();
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 1);

    scanParams.scanType = WIFI_FREQ_SCAN;
    g_staScanSuccess = 0;
    error = AdvanceScan(&scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    WaitSacnResult();
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 1);

    scanParams.scanType = WIFI_BSSID_SCAN;
    g_staScanSuccess = 0;
    error = AdvanceScan(&scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    WaitSacnResult();
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 1);

    scanParams.scanType = WIFI_BAND_SCAN;
    g_staScanSuccess = 0;
    error = AdvanceScan(&scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    WaitSacnResult();
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 1);

    error = DisableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_0900
 * @tc.name      : test adavance scan interface with invalid parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testAdvanceScanInvalidParam01, LEVEL2)
{
    WifiErrorCode error = EnableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    int stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_AVALIABLE);

    g_staScanSuccess = 0;
    error = AdvanceScan(NULL);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    WifiScanParams scanParams = {0};
    error = AdvanceScan(&scanParams);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    error = DisableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);
}

/**
 * @tc.number    : SUB_COMMUNICATION_WIFISERVICE_SDK_1000
 * @tc.name      : test adavance scan interface with invalid parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(WifiServiceFuncTestSuite, testAdvanceScanInvalidParam02, LEVEL2)
{
    WifiErrorCode error = EnableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    int stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_AVALIABLE);

    WifiScanParams* scanParams = malloc(sizeof(WifiScanParams));
    TEST_ASSERT_NOT_NULL(scanParams);
    memset_s(scanParams, sizeof(WifiScanParams), 0, sizeof(WifiScanParams));

    g_staScanSuccess = 0;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    scanParams->scanType = WIFI_BSSID_SCAN;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    scanParams->scanType = WIFI_SSID_SCAN;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    scanParams->scanType = WIFI_FREQ_SCAN;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    scanParams->scanType = WIFI_BAND_SCAN;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    int errorType = -1;
    scanParams->scanType = errorType;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    char bssid[WIFI_MAC_LEN] = {0xac, 0x75, 0x1d, 0xd8, 0x55, 0xc1};
    memcpy_s(scanParams->bssid, sizeof(scanParams->bssid), bssid, sizeof(bssid));
    scanParams->scanType = WIFI_BSSID_SCAN;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    WaitSacnResult();
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 1);

    memset_s(scanParams, sizeof(WifiScanParams), 0, sizeof(WifiScanParams));
    strcpy_s(scanParams->ssid, sizeof(scanParams->ssid), "wifi_service_xts");
    scanParams->scanType = WIFI_SSID_SCAN;
    g_staScanSuccess = 0;
    error = AdvanceScan(scanParams);
    TEST_ASSERT_EQUAL_INT(error, ERROR_WIFI_UNKNOWN);
    TEST_ASSERT_EQUAL_INT(g_staScanSuccess, 0);

    error = DisableWifi();
    TEST_ASSERT_EQUAL_INT(error, WIFI_SUCCESS);
    stat = IsWifiActive();
    TEST_ASSERT_EQUAL_INT(stat, WIFI_STATE_NOT_AVALIABLE);

    free(scanParams);
}

RUN_TEST_SUITE(WifiServiceFuncTestSuite);
