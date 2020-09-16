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
#ifndef COAP_DISCOVER_H
#define COAP_DISCOVER_H
#include "coap_def.h"
#define COAP_DEVICE_DISCOVER_URI "device_discover"
struct DeviceInfo;
typedef enum {
    CLEAR_IP_EVENT = 0,
    UPDATE_IP_EVENT
}AddressEvent;

typedef void (*WIFI_PROC_FUNC)(unsigned int para);
void CoapGetIp(char *ip, int length, int finite);
int CoapInitSocket(void);
void CoapDeinitSocket(void);
int CoapDeinitDiscovery(void);
void RegisterWifiCallback(WIFI_PROC_FUNC callback);
void CoapWriteMsgQueue(int state);
#endif /* #ifndef COAP_DISCOVER_H */
