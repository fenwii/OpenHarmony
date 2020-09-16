/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bus_manager.h"

#include "auth_conn_manager.h"
#include "discovery_error.h"
#include "os_adapter.h"
#include "session.h"
#include "tcp_session_manager.h"
#include "wifi_auth_manager.h"

BaseListener g_baseLister = {0};
static int g_busStartFlag = 0;

int StartSession(const char *ip)
{
    int port = CreateTcpSessionMgr(true, ip);
    return port;
}

int OnConnectEvent(int fd, const char *ip)
{
    ProcessConnectEvent(fd, ip);
    return 0;
}

int OnDataEvent(int fd)
{
    ProcessDataEvent(fd);
    return 0;
}

int StartBus(void)
{
    if (g_busStartFlag == 1) {
        return 0;
    }
    DeviceInfo *info = GetCommonDeviceInfo();
    if (info == NULL) {
        return ERROR_FAIL;
    }

    g_baseLister.onConnectEvent = OnConnectEvent;
    g_baseLister.onDataEvent = OnDataEvent;
    int authPort = StartListener(&g_baseLister, info->deviceIp);
    if (authPort < 0) {
        SOFTBUS_PRINT("[AUTH] StartBus StartListener fail\n");
        return ERROR_FAIL;
    }
    info->devicePort = authPort;

    int sessionPort = StartSession(info->deviceIp);
    if (sessionPort < 0) {
        SOFTBUS_PRINT("[AUTH] StartBus StartSession fail\n");
        StopListener();
        return ERROR_FAIL;
    }

    AuthMngInit(authPort, sessionPort);
    g_busStartFlag = 1;

    SOFTBUS_PRINT("[AUTH] StartBus ok\n");
    return 0;
}

int StopBus(void)
{
    if (g_busStartFlag == 0) {
        return 0;
    }

    AuthMngDeInit();
    StopListener();

    int ret = RemoveTcpSessionMgr();
    if (ret != 0) {
        return ERROR_FAIL;
    }

    DeviceInfo *info = GetCommonDeviceInfo();
    if (info == NULL) {
        return ERROR_FAIL;
    }
    info->devicePort = -1;

    g_busStartFlag = 0;
    return ERROR_SUCCESS;
}

int BusManager(unsigned int startFlag)
{
    if (startFlag == 1) {
        return StartBus();
    } else {
        return StopBus();
    }
}

DeviceInfo *BusGetLocalDeviceInfo(void)
{
    return GetCommonDeviceInfo();
}

