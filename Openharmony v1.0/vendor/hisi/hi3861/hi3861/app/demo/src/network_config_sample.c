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
 *
 * Description: Sample file of the power distribution service
 */

#include <unistd.h>

#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "lwip/ip4_addr.h"

#include "base64.h"
#include "cmsis_os2.h"
#include "hos_types.h"
#include "network_config_service.h"
#include "wifi_device_config.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"

enum LedState {
    LED_OFF = 0,
    LED_ON,
    LED_SPARK,
};

WifiDeviceConfig g_netCfg = {0};
WifiEvent g_staEventHandler = {0};
struct netif *g_staNetif = NULL;
int g_ledState = LED_OFF;
int g_connectRetryCount = 0;

const char *g_ssid = "Hi-xxx-Switchs-XXXXX     ";
const char *g_pinCode = "11111111";
const char *g_productId = "1";
const char *g_sn = "01234567890123450123456789012345";

#define SAMPLE_LED_INTERVAL_TIME_US 300000
#define SAMPLE_BIZ_SLEEP_TIME_US    1000000
#define SAMPLE_TIME_COUNT 5
#define DEVICE_INFO_NUM 2
#define POWER_NUM (-52)
#define MAX_DATA_LEN 4096

#define CHANNEL_80211B_ONLY 14
#define FREQ_OF_CHANNEL_1 2412
#define FREQ_OF_CHANNEL_80211B_ONLY 2484
#define WIFI_MIN_CHANNEL 1
#define WIFI_FREQ_INTERVAL 5

static unsigned int ChannelToFrequency(unsigned int channel)
{
    if (channel <= 0) {
        return 0;
    }

    if (channel == CHANNEL_80211B_ONLY) {
        return FREQ_OF_CHANNEL_80211B_ONLY;
    }

    return (((channel - WIFI_MIN_CHANNEL) * WIFI_FREQ_INTERVAL) + FREQ_OF_CHANNEL_1);
}

static void *LedTask(const char *arg)
{
    (void)arg;
    while (1) {
        switch (g_ledState) {
            case LED_OFF:
                GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_9, 1);
                usleep(SAMPLE_LED_INTERVAL_TIME_US);
                break;
            case LED_ON:
                GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_9, 0);
                usleep(SAMPLE_LED_INTERVAL_TIME_US);
                break;
            case LED_SPARK:
                GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_9, 0);
                usleep(SAMPLE_LED_INTERVAL_TIME_US);
                GpioSetOutputVal(WIFI_IOT_IO_NAME_GPIO_9, 1);
                usleep(SAMPLE_LED_INTERVAL_TIME_US);
                break;
            default:
                usleep(SAMPLE_LED_INTERVAL_TIME_US);
                break;
        }
    }

    return NULL;
}

#define SAMPLE_TASK_STACK_SIZE 4048
#define SAMPLE_TASK_PRIO 25

static void LedInit(void)
{
    osThreadAttr_t attr;

    GpioInit();
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_9, WIFI_IOT_IO_FUNC_GPIO_9_GPIO);
    GpioSetDir(WIFI_IOT_IO_NAME_GPIO_9, WIFI_IOT_GPIO_DIR_OUT);

    attr.name = "LedTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = SAMPLE_TASK_STACK_SIZE;
    attr.priority = SAMPLE_TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)LedTask, NULL, &attr) == NULL) {
        printf("[sample] Falied to create LedTask!\n");
    }
}

static void LedOn(void)
{
    printf("[sample] led spark.\n");
    g_ledState = LED_ON;
}

static void LedOff(void)
{
    printf("[sample] led off.\n");
    g_ledState = LED_OFF;
}

static void NetCfgResult(signed char result)
{
    printf("[sample] Network configure done.(result=%d)\n", result);
    UnRegisterWifiEvent(&g_staEventHandler);
    NotifyNetCfgResult(result);
    if (result == 0) {
        LedOff();
        printf("[sample] Led off.\n");
    } else if (result == 1) {
        LedOn();
        printf("[sample] Led on.\n");
    } else if (result == -1) {
        printf("[sample] Connect ap fail.\n");
    }
}

static void StaResetAddr(struct netif *ptrLwipNetif)
{
    ip4_addr_t staGW;
    ip4_addr_t staIpaddr;
    ip4_addr_t staNetmask;

    if (ptrLwipNetif == NULL) {
        printf("[sample] Null param of netdev\r\n");
        return;
    }

    IP4_ADDR(&staGW, 0, 0, 0, 0);
    IP4_ADDR(&staIpaddr, 0, 0, 0, 0);
    IP4_ADDR(&staNetmask, 0, 0, 0, 0);

    netifapi_netif_set_addr(ptrLwipNetif, &staIpaddr, &staNetmask, &staGW);
}

#define TEST_NUM_2 2
#define TEST_NUM_3 3
#define TEST_NUM_4 4
#define TEST_NUM_5 5
#define TEST_CONNECT_RETRY_COUNT 5

static int g_state;

static void *WifiConnectTask(const char *arg)
{
    (void)arg;
    if (g_state == WIFI_STATE_AVALIABLE) {
        NetCfgResult(0);
        printf("[sample] WiFi: Connected.\n");
        netifapi_dhcp_start(g_staNetif);
    } else if (g_state == WIFI_STATE_NOT_AVALIABLE) {
        printf("[sample] WiFi: Disconnected retry = %d\n", g_connectRetryCount);
        if (g_connectRetryCount < TEST_CONNECT_RETRY_COUNT) {
            g_connectRetryCount++;
            return NULL;
        }
        NetCfgResult(-1);
        netifapi_dhcp_stop(g_staNetif);
        StaResetAddr(g_staNetif);
    }
    return NULL;
}

static void WifiConnectionChangedHandler(int state, WifiLinkedInfo *info)
{
    (void)info;
    osThreadAttr_t attr;
    attr.name = "WifiConnectTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = SAMPLE_TASK_STACK_SIZE;
    attr.priority = SAMPLE_TASK_PRIO;
    g_state = state;
    if (osThreadNew((osThreadFunc_t)WifiConnectTask, NULL, &attr) == NULL) {
        printf("[sample] Falied to create WifiConnectTask!\n");
    }
}

static int StaStart(void)
{
    WifiErrorCode error;
    error = EnableWifi();
    if (error == ERROR_WIFI_BUSY) {
        printf("[sample] Sta had already connnected.\n");
        NetCfgResult(0);
    }
    if ((error != ERROR_WIFI_BUSY) && (error != WIFI_SUCCESS)) {
        printf("[sample] EnableWifi failed, error = %d\n", error);
        return -1;
    }

    g_staEventHandler.OnWifiConnectionChanged = WifiConnectionChangedHandler;
    error = RegisterWifiEvent(&g_staEventHandler);
    if (error != WIFI_SUCCESS) {
        printf("[sample] RegisterWifiEvent failed, error = %d\n", error);
        return -1;
    }

    if (IsWifiActive() == 0) {
        printf("[sample] Wifi station is not actived.\n");
        return -1;
    }

    g_staNetif = netif_find("wlan0");
    if (g_staNetif == NULL) {
        printf("[sample] Get netif failed\n");
        return -1;
    }

    return 0;
}

static int WapStaConnect(WifiDeviceConfig *config)
{
    int netId = 0;
    WifiErrorCode error;
    config->securityType = (config->preSharedKey[0] == '\0') ? WIFI_SEC_TYPE_OPEN : WIFI_SEC_TYPE_PSK;
    error = AddDeviceConfig(config, &netId);
    if (error != WIFI_SUCCESS) {
        printf("[sample] AddDeviceConfig add config failed, error=%d\n", error);
        return -1;
    }

    error = ConnectTo(netId);
    if (error != WIFI_SUCCESS) {
        printf("[sample] ConnectTo conn failed %d\n", error);
        return -1;
    }

    printf("[sample] WapSta connecting...\n");
    return 0;
}

static void *CfgNetTask(const char *arg)
{
    (void)arg;

    if (StaStart() != 0) {
        return NULL;
    }

    if (WapStaConnect(&g_netCfg) != 0) {
        return NULL;
    }

    return NULL;
}

static int CreateCfgNetTask(void)
{
    osThreadAttr_t attr;
    attr.name = "CfgNetTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = SAMPLE_TASK_STACK_SIZE;
    attr.priority = SAMPLE_TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)CfgNetTask, NULL, &attr) == NULL) {
        printf("[sample] Falied to create NanCfgNetTask!\n");
        return -1;
    }

    return 0;
}

static void DealSsidPwd(const WifiDeviceConfig *config)
{
    if (config == NULL) {
        printf("[sample] Input config is illegal.\n");
        return;
    }

    if (memcpy_s(&g_netCfg, sizeof(WifiDeviceConfig), config, sizeof(WifiDeviceConfig)) != 0) {
        printf("[sample] memcpy netCfg failed.\n");
        return;
    }
    printf("[sample] DealSsidPwd\n");
    g_connectRetryCount = 0;
    if (CreateCfgNetTask() != 0) {
        printf("[sample] Create cfgnet task failed.\n");
    }
}

int GetPinCode(unsigned char *pinCode, unsigned int size, unsigned int *len)
{
    if (pinCode == NULL) {
    }
    memset_s(pinCode, size, 0, size);
    if (strncpy_s((char *)pinCode, size, g_pinCode, strlen(g_pinCode)) != 0) {
        printf("[sample] GetPinCode copy pinCode failed\n");
        return -1;
    }
    *len = strlen((char *)pinCode);
    return 0;
}

int FastConnect(const struct WifiInfo *wifiInfo, WifiDeviceConfig *destCfg)
{
    if (memcpy_s(destCfg->ssid, sizeof(destCfg->ssid), wifiInfo->ssid, wifiInfo->ssidLen) != EOK) {
        printf("[sample] FastConnect copy ssid failed\n");
        return -1;
    }
    if (memcpy_s(destCfg->preSharedKey, sizeof(destCfg->preSharedKey), wifiInfo->psk, wifiInfo->pskLen) != EOK) {
        printf("[sample] FastConnect copy pwd failed\n");
        return -1;
    }
    if (memcpy_s(destCfg->bssid, sizeof(destCfg->bssid), wifiInfo->bssid, wifiInfo->bssidLen) != EOK) {
        printf("[sample] FastConnect copy bssid failed\n");
        return -1;
    }
    destCfg->securityType = wifiInfo->authMode;
    destCfg->freq = ChannelToFrequency(wifiInfo->channelNumber);
    destCfg->wapiPskType = WIFI_PSK_TYPE_HEX;
    return 0;
}

int NormalConnect(const struct WifiInfo *wifiInfo, WifiDeviceConfig *destCfg)
{
    if (memcpy_s(destCfg->ssid, sizeof(destCfg->ssid), wifiInfo->ssid, wifiInfo->ssidLen) != EOK) {
        printf("[sample] NormalConnect copy ssid failed\n");
        return -1;
    }
    if (memcpy_s(destCfg->preSharedKey, sizeof(destCfg->preSharedKey), wifiInfo->pwd, wifiInfo->pwdLen) != EOK) {
        printf("[sample] NormalConnect copy pwd failed\n");
        return -1;
    }
    return 0;
}

int ParseNetCfgData(const struct WifiInfo *wifiInfo, const unsigned char *vendorData, unsigned int len)
{
    printf("[sample] ParseWifiData vendorData len:%d\n", len);
    if (wifiInfo == NULL) {
        printf("[sample] wifiInfo is NULL\n");
        return -1;
    }

    WifiDeviceConfig netConfig;
    memset_s(&netConfig, sizeof(netConfig), 0, sizeof(netConfig));
    FastConnect(wifiInfo, &netConfig);

    if (vendorData != NULL) {
        /* process vendorData */
    }

    DealSsidPwd(&netConfig);
    return 0;
}

int SendRawEncodeData(const unsigned char *data, size_t len)
{
    size_t writeLen = 0;
    int ret = mbedtls_base64_encode(NULL, 0, &writeLen, (const unsigned char *)data, len);
    if (ret != 0) {
        printf("[sample] SendRawEncodeData base64 encode fial\n");
        return -1;
    }
    size_t encodeBufLen = writeLen;
    if (writeLen > MAX_DATA_LEN) {
        printf("[sample] SendRawEncodeData dataLen overSize\n");
        return -1;
    }
    char *buf = malloc(writeLen + 1);
    if (buf == NULL) {
        printf("[sample] malloc failed\r\n");
        return -1;
    }
    (void)memset_s(buf, writeLen + 1, 0, writeLen + 1);
    if (mbedtls_base64_encode((unsigned char *)buf, encodeBufLen, &writeLen, (const unsigned char *)data, len) != 0) {
        printf("[sample] SendRawEncodeData base64 encode failed\r\n");
        free(buf);
        buf = NULL;
        return -1;
    }

    printf("[sample] SendRawEncodeData encode buf = %s\n", buf);
    SendRawData((const char*)buf);
    if (buf != NULL) {
        free(buf);
    }

    return 0;
}

int RecvRawData(const char *svcId, unsigned int mode, const char *data)
{
    (void)svcId;
    (void)mode;
    if (data == NULL) {
        return -1;
    }
    printf("[sample] RecvRawData data : %s \n", data);

    size_t decodeLen = 0;
    int ret = mbedtls_base64_decode(NULL, 0, &decodeLen, (const unsigned char *)data, strlen(data));
    if ((ret != MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL) || (decodeLen == 0)) {
        printf("[sample] RecvRawData calc decodeLen fail(%d)\n", ret);
        return -1;
    }

    if (decodeLen > MAX_DATA_LEN) {
        printf("[sample] RecvRawData decodeLen overSize\n");
        return -1;
    }
    unsigned char *decodeData = (unsigned char *)malloc(decodeLen);
    if (decodeData == NULL) {
        return -1;
    }
    (void)memset_s(decodeData, decodeLen, 0, decodeLen);
    size_t outLen = 0;
    if (mbedtls_base64_decode(decodeData, decodeLen, &outLen, (const unsigned char *)data, strlen(data)) != 0) {
        printf("[sample] RecvRawData encode data fail\r\n");
        free(decodeData);
        return -1;
    }
    for (int i = 0; i < (int)outLen; i++) {
        printf("%02x ", decodeData[i]);
    }
    printf("\n");
    SendRawEncodeData(decodeData, outLen);
    if (decodeData != NULL) {
        free(decodeData);
    }
    return 0;
}

void NotifyNetCfgStatus(enum NetCfgStatus status)
{
    (void)status;
    return;
}

static void *SampleBizTask(const char *arg)
{
    (void)arg;
    int ret;
    LedInit();

    /* Parameter Settings */
    ret = SetSafeDistancePower(POWER_NUM);
    if (ret != 0) {
        printf("[sample] Set saft distance power failed\n");
        return NULL;
    }

    struct SoftAPParam config = {0};
    memset_s(&config, sizeof(struct SoftAPParam), 0, sizeof(struct SoftAPParam));
    strncpy_s(config.ssid, sizeof(config.ssid), g_ssid, strlen(g_ssid));
    config.authType = WIFI_SECURITY_OPEN;
    ret = SetSoftAPParameter(&config);
    if (ret != 0) {
        printf("[sample] Set softAP parameters failed\n");
        return NULL;
    }

    /* Register callback */
    NetCfgCallback hook;
    memset_s(&hook, sizeof(NetCfgCallback), 0, sizeof(NetCfgCallback));
    hook.GetPinCode = GetPinCode;
    hook.ParseNetCfgData = ParseNetCfgData;
    hook.RecvRawData = RecvRawData;
    hook.NotifyNetCfgStatus = NotifyNetCfgStatus;
    ret = RegNetCfgCallback(&hook);
    if (ret != 0) {
        printf("[sample] Regist config callback failed\n");
        return NULL;
    }

    /* Starting the SoftAP Network Configuration Service */
    struct DevInfo devInfo[DEVICE_INFO_NUM];
    memset_s(&devInfo, sizeof(devInfo), 0, sizeof(devInfo));
    devInfo[0].key = "productId";
    devInfo[1].key = "sn";
    devInfo[0].value = g_productId;
    devInfo[1].value = g_sn;
    ret = StartNetCfg(devInfo, DEVICE_INFO_NUM, NETCFG_SOFTAP_NAN);
    if (ret != 0) {
        printf("[sample] Start config wifi fail.\n");
        return NULL;
    }

    while (1) {
        printf("[sample] main biz.\n");
        usleep(SAMPLE_BIZ_SLEEP_TIME_US * SAMPLE_TIME_COUNT);
    }

    return NULL;
}

void NetCfgSampleBiz(void)
{
    printf("[sample] new demo, NetCfgSampleBiz enter.\n");
    osThreadAttr_t attr;

    attr.name = "samplebiztask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = SAMPLE_TASK_STACK_SIZE;
    attr.priority = SAMPLE_TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)SampleBizTask, NULL, &attr) == NULL) {
        printf("[sample] Falied to create SampleBizTask!\n");
    }
}
