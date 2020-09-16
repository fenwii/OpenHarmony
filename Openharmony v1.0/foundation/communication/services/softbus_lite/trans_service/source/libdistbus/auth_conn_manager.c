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

#include "auth_conn_manager.h"

#include <arpa/inet.h>
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include <los_task.h>
#include <lwip/sockets.h>
#else
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#endif
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

#include "data_bus_error.h"
#include "os_adapter.h"
#include "tcp_socket.h"

#define DEFAULT_BACKLOG    4
#define SESSIONPORT        0
BaseListener *g_callback = NULL;
static int g_listenFd = -1;
static int g_dataFd = -1;
static int g_maxFd = -1;
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
static unsigned int g_uwTskLoID;
#endif

static void RefreshMaxFd(int fd)
{
    if (fd > g_maxFd) {
        g_maxFd = fd;
    }
}

static int InitListenFd(const char *ip, int port)
{
    if (ip == NULL || g_listenFd != -1) {
        return -DBE_BAD_PARAM;
    }

    if (strncmp(ip, "0.0.0.0", strlen(ip) + 1) == 0) {
        return -DBE_BAD_PARAM;
    }

    int rc = OpenTcpServer(ip, port);
    if (rc < 0) {
        SOFTBUS_PRINT("[TRANS] InitListenFd OpenTcpServer fail\n");
        return rc;
    }
    g_listenFd = rc;
    RefreshMaxFd(g_listenFd);

    rc = listen(rc, DEFAULT_BACKLOG);
    if (rc != 0) {
        SOFTBUS_PRINT("[TRANS] InitListenFd listen fail\n");
        StopListener();
        return -DBE_LISTEN_FAIL;
    }

    return DBE_SUCCESS;
}

static bool ProcessAuthData(int listenFd, const fd_set *readSet)
{
    if (readSet == NULL || g_callback == NULL || g_callback->onConnectEvent == NULL ||
        g_callback->onDataEvent == NULL) {
        return false;
    }

    if (FD_ISSET(listenFd, readSet)) {
        struct sockaddr_in addrClient = {0};
        socklen_t addrLen = sizeof(addrClient);

        g_dataFd = accept(listenFd, (struct sockaddr *)(&addrClient), &addrLen);
        if (g_dataFd < 0) {
            CloseAuthSessionFd(listenFd);
            return false;
        }
        RefreshMaxFd(g_dataFd);
        if (g_callback->onConnectEvent(g_dataFd, inet_ntoa(addrClient.sin_addr)) != 0) {
            CloseAuthSessionFd(g_dataFd);
        }
    }

    if (g_dataFd > 0 && FD_ISSET(g_dataFd, readSet)) {
        g_callback->onDataEvent(g_dataFd);
    }

    return true;
}


static void WaitProcess(void)
{
    SOFTBUS_PRINT("[TRANS] WaitProcess begin\n");
    fd_set readSet;
    fd_set exceptfds;

    while (1) {
        FD_ZERO(&readSet);
        FD_ZERO(&exceptfds);
        FD_SET(g_listenFd, &readSet);
        if (g_dataFd >= 0) {
            FD_SET(g_dataFd, &readSet);
            FD_SET(g_dataFd, &exceptfds);
        }
        int ret = select(g_maxFd + 1, &readSet, NULL, &exceptfds, NULL);
        if (ret > 0) {
            if (!ProcessAuthData(g_listenFd, &readSet)) {
                SOFTBUS_PRINT("[TRANS] WaitProcess ProcessAuthData fail\n");
                StopListener();
                break;
            }
        } else if (ret < 0) {
            if (errno == EINTR || (g_dataFd > 0 && FD_ISSET(g_dataFd, &exceptfds))) {
                SOFTBUS_PRINT("[TRANS] errno == EINTR or g_dataFd is in exceptfds set.\n");
                CloseAuthSessionFd(g_dataFd);
                continue;
            }
            SOFTBUS_PRINT("[TRANS] WaitProcess select fail, stop listener\n");
            StopListener();
            break;
        }
    }
}

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
int StartListener(BaseListener *callback, const char *ip)
{
    if (callback == NULL || ip == NULL) {
        return -DBE_BAD_PARAM;
    }

    g_callback = callback;

    int rc = InitListenFd(ip, SESSIONPORT);
    if (rc != DBE_SUCCESS) {
        return -DBE_BAD_PARAM;
    }

    unsigned int ret;
    TSK_INIT_PARAM_S serverTask;

    serverTask.pfnTaskEntry = (TSK_ENTRY_FUNC)WaitProcess;
    serverTask.uwStackSize  = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    serverTask.pcName = "trans_auth_task";
    serverTask.usTaskPrio = LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO;
    serverTask.uwResved   = LOS_TASK_STATUS_DETACHED;

    ret = LOS_TaskCreate(&g_uwTskLoID, &serverTask);
    if (ret != 0) {
        SOFTBUS_PRINT("[TRANS] StartListener task create fail\n");
        return -1;
    }

    SOFTBUS_PRINT("[TRANS] StartListener ok\n");
    return GetSockPort(g_listenFd);
}
#else
#define MIN_STACK_SIZE 0x8000
static pthread_key_t g_localKey = 0;
typedef void *(*Runnable)(void *argv);
typedef struct ThreadAttr ThreadAttr;
struct ThreadAttr {
    const char *name;   // name of the thread
    uint32_t stackSize;   // size of stack
    uint8_t priority;     // initial thread priority
    uint8_t reserved1;    // reserved1 (must be 0)
    uint16_t reserved2;   // reserved2 (must be 0)
};
typedef void *ThreadId;

ThreadId AuthCreate(Runnable run, const ThreadAttr *attr)
{
    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setstacksize(&threadAttr, (attr->stackSize | MIN_STACK_SIZE));
    struct sched_param sched = {attr->priority};
    pthread_attr_setschedparam(&threadAttr, &sched);
    pthread_key_create(&g_localKey, NULL);
    pthread_t threadId = 0;
    int errCode = pthread_create(&threadId, &threadAttr, run, NULL);
    if (errCode != 0) {
        return NULL;
    }
    if (attr->name != NULL) {
        (void)pthread_setname_np(threadId, attr->name);
    }
    return (ThreadId)threadId;
}

int StartListener(BaseListener *callback, const char *ip)
{
    if (callback == NULL || ip == NULL) {
        return -DBE_BAD_PARAM;
    }

    g_callback = callback;

    int rc = InitListenFd(ip, SESSIONPORT);
    if (rc != DBE_SUCCESS) {
        return -DBE_BAD_PARAM;
    }

    signal(SIGPIPE, SIG_IGN);
    ThreadAttr attr = {"auth", 0x800, 20, 0, 0};
    register ThreadId threadId = (ThreadId)AuthCreate((Runnable)WaitProcess, &attr);
    if (threadId == NULL) {
        SOFTBUS_PRINT("[TRANS] StartListener AuthCreate fail\n");
        return -1;
    }
    return GetSockPort(g_listenFd);
}
#endif

// close auth Session must use this function.
void CloseAuthSessionFd(int fd)
{
    if (fd == g_listenFd) {
        CloseFd(g_listenFd);
        g_listenFd = -1;
    }

    if (fd == g_dataFd) {
        CloseFd(g_dataFd);
        g_dataFd = -1;
        g_maxFd = g_listenFd;
    }
}

void StopListener(void)
{
    CloseAuthSessionFd(g_listenFd);
    CloseAuthSessionFd(g_dataFd);
}