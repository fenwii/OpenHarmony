/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utils/includes.h"
#include "pthread.h"
#include "common/wpa_ctrl.h"
#include "securec.h"


#define WPA_IFACE_NAME "wlan0"
#define WIFI_AUTH_FAILED_REASON_STR "WRONG_KEY"
#define WIFI_AUTH_FAILED_REASON_CODE "reason=2"
#define WPA_CTRL_REQUEST_OK "OK"
#define WPA_CTRL_REQUEST_FAIL "FAIL"

#define SAMPLE_INFO(format, args...) \
    do { \
        fprintf(stderr, "\033[1;32m WpaCliSample(%s:%d):\t\033[0m" format, __func__, __LINE__, ##args); \
        printf("\n"); \
    } while (0)

#define SAMPLE_ERROR(format, args...) \
    do { \
        fprintf(stderr, "\033[1;31m WpaCliSample(%s:%d):\t\033[0m" format, __func__, __LINE__, ##args); \
        printf("\n"); \
    } while (0)


static struct wpa_ctrl *g_monitorConn;
static struct wpa_ctrl *g_ctrlConn;
static pthread_t g_wpaThreadId;
static int g_scanAvailable = 0;

static void DumpString(const char *buf, int len, const char *tag)
{
    SAMPLE_INFO("%s dump start.", tag);
    for (int i = 0; i < len; i++) {
        printf("%c", buf[i]);
    }
    printf("\n");
    SAMPLE_INFO("%s dump end.", tag);
}

static int StrMatch(const char *a, const char *b)
{
    return strncmp(a, b, strlen(b)) == 0;
}

static void WifiEventHandler(char *rawEvent, int len)
{
    char *pos = rawEvent;
    if (*pos == '<') {
        pos = strchr(pos, '>');
        if (pos) {
            pos++;
        } else {
            pos = rawEvent;
        }
    }
    if (StrMatch(pos, WPA_EVENT_CONNECTED)) {
        SAMPLE_INFO("WIFI_EVENT_CONNECTED");
        return;
    }
    if (StrMatch(pos, WPA_EVENT_SCAN_RESULTS)) {
        SAMPLE_INFO("WIFI_EVENT_SCAN_DONE");
        g_scanAvailable = 1;
        return;
    }
    if (StrMatch(pos, WPA_EVENT_TEMP_DISABLED) && strstr(pos, WIFI_AUTH_FAILED_REASON_STR)) {
        SAMPLE_INFO("WIFI_EVENT_WRONG_KEY");
        return;
    }
    if (StrMatch(pos, WPA_EVENT_DISCONNECTED) && !strstr(pos, WIFI_AUTH_FAILED_REASON_CODE)) {
        SAMPLE_INFO("WIFI_EVENT_DISCONNECTED");
        return;
    }
}

static void CliRecvPending(void)
{
    while (wpa_ctrl_pending(g_monitorConn)) {
        char buf[4096];
        size_t len = sizeof(buf) - 1;
        if (wpa_ctrl_recv(g_monitorConn, buf, &len) == 0) {
            buf[len] = '\0';
            SAMPLE_INFO("event received %s", buf);
            WifiEventHandler(buf, len);
        } else {
            SAMPLE_INFO("could not read pending message.");
            break;
        }
    }
}

static void* MonitorTask(void *args)
{
    (void)args;
    int fd, ret;
    fd_set rfd;
    while (1) {
        fd = wpa_ctrl_get_fd(g_monitorConn);
        FD_ZERO(&rfd);
        FD_SET(fd, &rfd);
        ret = select(fd + 1, &rfd, NULL, NULL, NULL);
        if (ret <= 0) {
            SAMPLE_INFO("select failed ret = %d\n", ret);
            break;
        }
        CliRecvPending();
        sleep(1);
    }
    return NULL;
}

static int SendCtrlCommand(const char *cmd, char *reply, size_t *replyLen)
{
    size_t len = *replyLen - 1;
    wpa_ctrl_request(g_ctrlConn, cmd, strlen(cmd), reply, &len, 0);
    DumpString(reply, len, "SendCtrlCommand raw return");
    if (len != 0 && !StrMatch(reply, WPA_CTRL_REQUEST_FAIL)) {
        *replyLen = len;
        return 0;
    }
    SAMPLE_ERROR("send ctrl request [%s] failed.", cmd);
    return -1;
}

static void TestNetworkConfig(void)
{
    char networkId[20] = {0};
    size_t networkIdLen = sizeof(networkId);
    int ret = SendCtrlCommand("DISCONNECT", networkId, &networkIdLen);
    ret += SendCtrlCommand("ADD_NETWORK", networkId, &networkIdLen);
    if (ret != 0) {
        SAMPLE_ERROR("add network failed.");
        return;
    }
    SAMPLE_INFO("add network success, network id [%.*s]", networkIdLen, networkId);
    char reply[100] = {0};
    size_t replyLen = sizeof(reply);
    char cmd[200] = {0};
    sprintf_s(cmd, sizeof(cmd), "SET_NETWORK %.*s ssid \"example\"", networkIdLen, networkId);
    ret += SendCtrlCommand(cmd, reply, &replyLen);
    replyLen = sizeof(reply);
    sprintf_s(cmd, sizeof(cmd), "SET_NETWORK %.*s psk \"012345678\"", networkIdLen, networkId);
    ret += SendCtrlCommand(cmd, reply, &replyLen);
    replyLen = sizeof(reply);
    sprintf_s(cmd, sizeof(cmd), "ENABLE_NETWORK %.*s", networkIdLen, networkId);
    ret += SendCtrlCommand(cmd, reply, &replyLen);
    replyLen = sizeof(reply);
    ret += SendCtrlCommand("RECONNECT", reply, &replyLen);
    replyLen = sizeof(reply);
    if (ret == 0) {
        SAMPLE_INFO("network config success.");
        return;
    }
    sprintf_s(cmd, sizeof(cmd), "REMOVE_NETWORK %.*s", networkIdLen, networkId);
    SendCtrlCommand(cmd, reply, &replyLen);
    SAMPLE_ERROR("network config failed remove network [%.*s].", networkIdLen, networkId);
}

static void TestCliConnection(void)
{
    char reply[100] = {0};
    size_t replyLen = sizeof(reply);
    int ret = SendCtrlCommand("PING", reply, &replyLen);
    if (ret == 0 && StrMatch(reply, "PONG")) {
        SAMPLE_INFO("connect to wpa success.");
        return;
    }
    SAMPLE_INFO("connect to wpa failed, err = %s.", reply);
}

static void TestScan()
{
    char reply[100] = {0};
    size_t replyLen = sizeof(reply);
    g_scanAvailable = 0;
    SendCtrlCommand("SCAN", reply, &replyLen);
    while (1) {
        sleep(1);
        if (g_scanAvailable == 1) {
            SAMPLE_INFO("scan result received.");
            break;
        }
        SAMPLE_INFO("waiting scan result.");
    }
    char scanResult[4096] = {0};
    size_t scanLen = sizeof(scanResult);
    int ret = SendCtrlCommand("SCAN_RESULTS", scanResult, &scanLen);
    if (ret != 0) {
        SAMPLE_ERROR("request scan results failed.");
        return;
    }
    DumpString(scanResult, scanLen, "scan results");
}

static void StartTest()
{
    TestCliConnection(); // test if wpa control interface connected successfully
    TestScan(); // test scan and get scan results
    TestNetworkConfig(); // test config network and connect
}

int InitControlInterface()
{
    g_ctrlConn = wpa_ctrl_open(WPA_IFACE_NAME); // create control interface for send cmd
    g_monitorConn = wpa_ctrl_open(WPA_IFACE_NAME); // create control interface for event monitor
    if (!g_ctrlConn || !g_monitorConn) {
        SAMPLE_ERROR("open wpa control interface failed.");
        return -1;
    }
    if (wpa_ctrl_attach(g_monitorConn) == 0) { // start monitor
        pthread_create(&g_wpaThreadId, NULL, MonitorTask, NULL); // create thread for read event
        return 0;
    }
    return -1;
}

int main()
{
    if (InitControlInterface() != 0) {
        SAMPLE_ERROR("control interface init failed, exit client.");
        return -1;
    }
    SAMPLE_INFO("control interface init success.");
    StartTest();
    pthread_join(g_wpaThreadId, NULL);
    SAMPLE_INFO("test finished, exit client.");
}
