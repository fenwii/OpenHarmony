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

#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

pthread_t g_apThread;

char* g_apArg[20] = {0};
int g_apArgc = 0;

static void* ThreadMain()
{
    printf("[HostapdSample]init hostapd.\n");

    void *handleLibWpa = dlopen("/usr/lib/libwpa.so", RTLD_NOW | RTLD_LOCAL);
    if (handleLibWpa == NULL) {
        printf("[HostapdSample]dlopen libwpa failed.\n");
        return NULL;
    }
    int (*func)(int, char **) = NULL;
    func =  dlsym(handleLibWpa, "ap_main");
    if (func == NULL) {
        dlclose(handleLibWpa);
        printf("[HostapdSample]dlsym ap_main failed.\n");
        return NULL;
    }
    int ret = func(g_apArgc, g_apArg);

    printf("[HostapdSample]run ap_main failed, ret:%d.\n", ret);
    for (int i = 0; i < g_apArgc; i++) {
        printf("[HostapdSample]arg %d:%s.\n", i, g_apArg[i]);
    }

    if (dlclose(handleLibWpa) != 0) {
        printf("[HostapdSample]dlclose libwpa failed.\n");
        return NULL;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    g_apArgc = argc;
    for (int i = 0; i < g_apArgc; i++) {
        g_apArg[i] = argv[i];
    }

    int ret = pthread_create(&g_apThread, NULL, ThreadMain, NULL);
    if (ret != 0) {
        printf("[HostapdSample]create thread failed error:%s.\n", strerror(ret));
        return 1;
    }
    pthread_join(g_apThread, NULL);
    return 0;
}
