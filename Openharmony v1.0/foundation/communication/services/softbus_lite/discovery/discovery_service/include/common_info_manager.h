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
#ifndef _COMMON_INFO_MANAGER_H
#define _COMMON_INFO_MANAGER_H
#ifdef __cplusplus
extern "C" {
#endif
#define MAX_DEV_NAME_LEN 64
#define MAX_DEV_TYPE_LEN 64
#define MAX_AUTH_ID_LEN 96
#define MAX_DEV_ID_LEN 96
#define MAX_DEV_VERSION_LEN 16
#define MAX_DEV_NETWORK_LEN 16
#define MAX_CAPABILITY_NUM 1
#define MAX_SERVICE_DATA_LEN 64
#define MAX_PACKAGE_NAME 64
#define MAX_SOFTWARE_VERSION_LEN 64
#define MAX_DEV_IP_LEN 16
#define MAX_DEV_MAC_LEN 6
#define MAX_DEFAULT_SERVICE_DATA_LEN 16
#define DEV_ID_LEN 32
#define MAX_CAPABILITY_DATA_LEN 2

#define MAX_CUST_LEN 64
#define DEVICE_TYPE_PHONE "PHONE"
#define DEVICE_TYPE_PAD "PAD"
#define DEVICE_TYPE_TV "TV"
#define DEVICE_TYPE_PC "PC"
#define DEVICE_TYPE_AUDIO "AUDIO"
#define DEVICE_TYPE_CAR "CAR"

#define L0_DEVICE_NAME "DEV_L0"
#define L1_DEVICE_NAME "DEV_L1"

typedef enum {
    ONLINE = 0,
    OFFLINE,
} NetworkState;
typedef struct DeviceInfo {
    char deviceName[MAX_DEV_NAME_LEN];
    char deviceId[MAX_DEV_ID_LEN];
    char deviceIp[MAX_DEV_IP_LEN];
    char version[MAX_DEV_VERSION_LEN];
    char softwareVersion[MAX_SOFTWARE_VERSION_LEN];
    char networkName[MAX_DEV_NETWORK_LEN];
    int deviceType;
    int devicePort;
    NetworkState networkState;
    int isAccountTrusted;
} DeviceInfo;

typedef struct {
    char deviceName[MAX_DEV_NAME_LEN];
    char deviceId[MAX_DEV_ID_LEN];
    char deviceIp[MAX_DEV_IP_LEN];
    int deviceType;
} DeviceInfoExternal;

#define MAX_VALUE_SIZE 64
DeviceInfo* GetCommonDeviceInfo(void);
int InitCommonManager(void);
void DeinitCommonManager(void);
int UpdateCommonDeviceInfo(void);
typedef struct List {
    struct List *prev;
    struct List *next;
} List;

void ListInitHead(List *head);
void ListInsertHead(List *head, List *node);
void ListInsertTail(List *head, List *node);
void ListRemoveNode(List *node);
int ListIsEmpty(List *head);
List *ListGetFront(List *head);
List *ListPopFront(List *head);
int ListLength(const List *head);
int GetDeviceIdFromFile(char *deviceId, unsigned int len);

#define LIST_FOR_EACH_SAFE(pos, tmp, head) \
    for ((pos) = (head)->next, (tmp) = (pos)->next; (pos) != (head); \
        (pos) = (tmp), (tmp) = (pos)->next)

#ifdef __cplusplus
}
#endif
#endif /* _COMMON_INFO_MANAGER_H */
