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

#include <unistd.h>

#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"

#include "cmsis_os2.h"
#include "hos_init.h"
#include "hos_types.h"
#include "netcfg_service.h"
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

#define SAMPLE_SEND_BUF_SIZE 400
int g_recvFlag = 0;
char g_buf[SAMPLE_SEND_BUF_SIZE] = {0};
int g_bufLen = 0;

#define SAMPLE_LED_INTERVAL_TIME_US 300000
#define SAMPLE_BIZ_SLEEP_TIME_US    1000000

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

static void PreTransferProc(void)
{
    printf("[sample] oncall pretransfer event.\n");
    g_ledState = LED_SPARK;
}

static void DisconnectEventProc(void)
{
    printf("[sample] oncall disconnect event.\n");
}

static void RecvMessageEventProc(char *msg, int len)
{
    printf("[sample] oncall recv message %s(%d).\n", msg, len);
    if (memcpy_s(g_buf, sizeof(g_buf), msg, len) != 0) {
        printf("[sample] memcpy ctrl msg fail.\n");
    }
    g_recvFlag = 1;
    g_bufLen = len;
}

static void TimeoutProc(void)
{
    printf("[sample] oncall network config service timeout with phone.\n");
}

static void NetCfgResult(signed char result)
{
    printf("[sample] network configure done.(result=%d)\n", result);
    DisableWifi();
    UnRegisterWifiEvent(&g_staEventHandler);
    NotifyConfigWifiResult(result);
    if (result == NETCFG_RST_SUCC) {
        LedOn();
    } else if (result == NETCFG_RST_FAIL) {
        printf("[sample] conn ap fail.\n");
    }
    // -1: fail 0: succ
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
static void WifiConnectionChangedHandler(int state, WifiLinkedInfo *info)
{
    if (state == WIFI_STATE_AVALIABLE) {
        NetCfgResult(NETCFG_RST_SUCC);
        NetCfgResult(TEST_NUM_2);
        NetCfgResult(TEST_NUM_3);
        NetCfgResult(TEST_NUM_4);
        NetCfgResult(TEST_NUM_5);
        printf("[sample] WiFi: Connected.\n");
        netifapi_dhcp_start(g_staNetif);
    } else if (state == WIFI_STATE_NOT_AVALIABLE) {
        printf("[sample] WiFi: Disconnected retry = %d, reason = %d\n", g_connectRetryCount, info->disconnectedReason);
        if (g_connectRetryCount < TEST_CONNECT_RETRY_COUNT) {
            g_connectRetryCount++;
            return;
        }
        NetCfgResult(NETCFG_RST_FAIL);
        netifapi_dhcp_stop(g_staNetif);
        StaResetAddr(g_staNetif);
    }
}

static int StaStart(void)
{
    WifiErrorCode error;
    error = EnableWifi();
    if (error == ERROR_WIFI_BUSY) {
        printf("[sample] Sta had already connnected.\n");
        NetCfgResult(NETCFG_RST_SUCC);
        return -1;
    }
    if (error != WIFI_SUCCESS) {
        printf("[sample] EnableWifi fail, error = %d\n", error);
        return -1;
    }

    g_staNetif = netif_find("wlan0");
    if (g_staNetif == NULL) {
        printf("[sample] Get netif failed\n");
        return -1;
    }

    g_staEventHandler.OnWifiConnectionChanged = WifiConnectionChangedHandler;
    error = RegisterWifiEvent(&g_staEventHandler);
    if (error != WIFI_SUCCESS) {
        printf("[sample] RegisterWifiEvent fail, error = %d\n", error);
        return -1;
    }

    if (IsWifiActive() == 0) {
        printf("[sample] Wifi station is not actived.\n");
        return -1;
    }

    return 0;
}

static int WapStaConnect(const WifiDeviceConfig *config)
{
    int netId = 0;
    WifiErrorCode error;

    error = AddDeviceConfig(config, &netId);
    if (error != WIFI_SUCCESS) {
        printf("[sample] AddDeviceConfig add config failed %d\n", error);
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
        printf("[NAN] Falied to create NanCfgNetTask!\n");
        return -1;
    }

    return 0;
}

static void DealSsidPwd(struct NetCfgConfig *config)
{
    if (config == NULL) {
        printf("[sample] input config is illegal.\n");
        return;
    }

    if (memcpy_s(&g_netCfg, sizeof(WifiDeviceConfig), &(config->config), sizeof(WifiDeviceConfig)) != 0) {
        printf("[sample] memcpy netCfg fail.\n");
        return;
    }
    g_netCfg.securityType = ((config->config.preSharedKey[0] == '\0') ? WIFI_SEC_TYPE_OPEN : WIFI_SEC_TYPE_PSK);
    g_connectRetryCount = 0;
    if (CreateCfgNetTask() != 0) {
        printf("[sample] create cfgnet task fail.\n");
    }
}
#define SAMPLE_NETCFG_DEFAULT_DB (-61)
#define SAMPLE_NETCFG_DEFAULT_ACK_TIMEOUT 3
#define SAMPLE_NETCFG_DEFAULT_HEARTBEAT_TIMEOUT 60;
#define SAMPLE_TIME_COUNT 5
struct DevPara g_devPara = {0};
struct NetCfgPara g_netCfgPara = {0};

static void *SampleBizTask(const char *arg)
{
    (void)arg;
    int ret;
    LedInit();
    struct WifiConfigureEvent event = {0};
    event.OnPreTransferConfig = PreTransferProc;
    event.OnTransferConfig = DealSsidPwd;
    event.OnDisconnected = DisconnectEventProc;
    event.OnMessageReceived = RecvMessageEventProc;
    event.OnTimeout = TimeoutProc;
    ret = RegConfigWifiCallback(&event);
    if (ret != 0) {
        printf("[sample] register event fail.\n");
        return NULL;
    }

    HotspotConfig config = {0};
    if (strcpy_s(config.ssid, sizeof(config.ssid), "netcfg_softap") != 0) {
        printf("[sample] strcpy ssid fail.\n");
        return NULL;
    }
    config.securityType = WIFI_SEC_TYPE_OPEN;

    char *pin = "0123456789012345";
    char *productId = "1";
    char *sn = "01234567890123450123456789012345";

    memset_s(&g_devPara, sizeof(g_devPara), 0, sizeof(g_devPara));
    memcpy_s(g_devPara.pin, sizeof(g_devPara.pin), pin, sizeof(g_devPara.pin));
    memcpy_s(g_devPara.productId, sizeof(g_devPara.productId), productId, sizeof(g_devPara.productId));
    memcpy_s(g_devPara.sn, sizeof(g_devPara.sn), sn, sizeof(g_devPara.sn));

    g_netCfgPara.db = SAMPLE_NETCFG_DEFAULT_DB;
    g_netCfgPara.nanAckTimout = SAMPLE_NETCFG_DEFAULT_ACK_TIMEOUT;
    g_netCfgPara.hbTimout = SAMPLE_NETCFG_DEFAULT_HEARTBEAT_TIMEOUT;
    ret += StartConfigWifi(&config, &g_devPara, &g_netCfgPara);
    if (ret != 0) {
        printf("[sample] start config wifi fail.\n");
        return NULL;
    }

    while (1) {
        printf("[sample] main biz.\n");
        if (g_recvFlag) {
            g_recvFlag = 0;
            printf("[sample] send usr msg.\n");
            SendMessage(g_buf, g_bufLen);
        }
        usleep(SAMPLE_BIZ_SLEEP_TIME_US);
    }

    return NULL;
}

void SampleBiz(void)
{
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
