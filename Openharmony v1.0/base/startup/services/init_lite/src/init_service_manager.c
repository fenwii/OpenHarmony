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
#include "init_service_manager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "init_adapter.h"
#include "init_jobs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

static const int SLEEP_DURATION = 1;

// All serivce processes that init will fork+exec.
static Service* g_services = NULL;
static int g_servicesCnt = 0;

void RegisterServices(Service* services, int servicesCnt)
{
    g_services = services;
    g_servicesCnt = servicesCnt;
}

static int FindServiceByName(const char* servName)
{
    if (servName == NULL) {
        return -1;
    }

    for (int i = 0; i < g_servicesCnt; ++i) {
        if (strlen(g_services[i].name) == strlen(servName) &&
            strncmp(g_services[i].name, servName, strlen(g_services[i].name)) == 0) {
            return i;
        }
    }
    return -1;
}

void StartServiceByName(const char* servName)
{
    // find service by name
    int servIdx = FindServiceByName(servName);
    if (servIdx < 0) {
        printf("[Init] StartServiceByName, cannot find service %s.\n", servName);
        return;
    }

    if (ServiceStart(&g_services[servIdx]) != SERVICE_SUCCESS) {
        printf("[Init] StartServiceByName, service %s start failed!\n", g_services[servIdx].name);
    }

    sleep(SLEEP_DURATION);
    return;
}

void StopAllServices()
{
    for (size_t i = 0; i < g_servicesCnt; i++) {
        if (ServiceStop(&g_services[i]) != SERVICE_SUCCESS) {
            printf("[Init] StopAllServices, service %s stop failed!\n", g_services[i].name);
        }
    }
}

void ReapServiceByPID(int pid)
{
    for (size_t i = 0; i < g_servicesCnt; i++) {
        if (g_services[i].pid == pid) {
            if (g_services[i].attribute & SERVICE_ATTR_IMPORTANT) {
                // important process exit, need to reboot system
                g_services[i].pid = -1;
                StopAllServices();
                RebootSystem();
            }
            ServiceReap(&g_services[i]);
            break;
        }
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
